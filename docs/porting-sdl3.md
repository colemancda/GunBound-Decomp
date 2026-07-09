# Porting the GunBound client to SDL3

A reimplementation guide that maps this client's DirectX / Win32 usage to SDL3,
keyed to the **actual function and class names** recovered in this project. It
pairs with the reimplementation-focused [screen docs](screens/README.md) and the
[widget system](widgets.md).

## The one idea that makes this easy
The game is **2D throughout**, even where it uses "3D" hardware. The in-battle
Direct3D 7 path emits `XYZRHW` (pre-transformed, screen-space) vertices — i.e.
textured 2D quads on the GPU, no world/view/projection transform. So SDL3's
**2D renderer maps almost 1:1** and you never need `SDL_GPU` or shaders.

**Use `SDL_Renderer` + `SDL_RenderGeometry`, not `SDL_GPU`.** There are no
meshes, lighting, or 3D transforms — only screen-space textured quads with
alpha/additive blending, which is exactly what `SDL_Renderer` provides (and it
back-ends onto D3D11/Vulkan/Metal/OpenGL for you).

## Subsystem mapping

| This client (recovered names) | SDL3 |
|---|---|
| `InitDirectDraw` (`DirectDrawCreateEx`), `WndProc` window | `SDL_CreateWindow` + `SDL_CreateRenderer` |
| `IDirectDrawSurface7` surfaces | `SDL_Texture` (GPU) / `SDL_Surface` (CPU) |
| `PresentFrame` (surface Flip/restore) | `SDL_RenderPresent` (double-buffered) |
| `FlushSpriteBatch` → `DrawPrimitive(TRIANGLELIST, FVF 0x244)` | **`SDL_RenderGeometry`** (one call per batch) |
| `g_spriteVertexBuffer` (36-byte XYZRHW/DIFFUSE/TEX2 verts) | an `SDL_Vertex[]` (`position`, `color`, `tex_coord`) |
| `BlitSprite16bpp` / `BlitSpriteClipped` (locked RGB565 buffer) | streaming `SDL_Texture` + `SDL_LockTexture`, **or** per-sprite `SDL_Texture` |
| `BlitRLESprite` (RLE bitmap font) | a glyph atlas texture + `SDL_RenderGeometry` |
| `LockBackBuffer` | `SDL_LockTexture` (streaming target) — or gone, if GPU-composited |
| RGB565 back buffer | `SDL_PIXELFORMAT_RGB565`, or convert to RGBA8888 on upload |
| `SetupZBuffer` / `g_pZBufferSurface` | **drop it** — SDL uses draw order (Z was a HAL requirement here) |
| additive blend (`SetRenderState DESTBLEND=ONE`) | `SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_ADD)` |
| sine-table sprite rotation (`g_sineTable360`) | keep the quad math → `SDL_RenderGeometry`, or `SDL_RenderTextureRotated` |
| DirectSound8 buffers | `SDL_AudioStream` (SDL3 audio) |
| `.mp3` music / `channel.mp3` etc. | **SDL_mixer** `Mix_Music` (core SDL doesn't decode mp3) |
| DirectInput8 + `WndProc` messages | `SDL_Event` loop |
| Win32 `EDIT` controls (`CEditBox`, chat/name/password) | `SDL_StartTextInput` + `SDL_EVENT_TEXT_INPUT` (implement the field) |
| `timeGetTime`, the ~50 ms `GameTick` | `SDL_GetTicks()` / `SDL_GetTicksNS()` |
| Winsock (`ws2_32`) — the connection subsystem | not DirectX; keep sockets or use SDL_net |

## The rendering path, ported

The hardware path ports mechanically. Today:
```
State11_InBattle_Render        // walk layers
  -> FindTextureCacheEntryByName(...)
  -> BuildRotatedSpriteQuad / BuildScaledSpriteQuad / BuildSizedSpriteQuad /
     BuildSpriteQuad           // append 2 triangles to g_spriteVertexBuffer
FlushSpriteBatch               // one DrawPrimitive for the whole frame
```
Under SDL3, the `Build*SpriteQuad` family stops writing D3D vertices and appends
`SDL_Vertex`es instead (`position` = corner, `tex_coord` = UV, `color` =
diffuse). The rotation math, the two-triangles-per-quad structure, and even the
horizontal-flip flag (which swaps UVs) carry over unchanged. `FlushSpriteBatch`
becomes essentially one line:
```c
SDL_RenderGeometry(renderer, atlasTexture, verts, vertCount, NULL, 0);
```
Every draw helper writes into a shared batch keyed by texture; flush when the
texture changes or at frame end (SDL_Renderer also batches internally, so even
naive per-quad `SDL_RenderGeometry` calls coalesce).

## The composite widget tree
`CWidget`/`CPanel` ([widgets.md](widgets.md)) is a composite tree with `Draw`
broadcasting to children. That maps cleanly to SDL either way — keep the tree
and, at each node's `Draw`, emit geometry. The `+0x1c` `OnCommand(evt,id,arg)`
callback bubble-up stays identical; only the leaf rendering changes. The flat
`ButtonWidget` (bottom-bar buttons) and the panel hierarchy both just become
"emit a textured quad (or a few) per widget."

## What's easy vs. what needs real work

**Easy / mechanical**
- The in-battle GPU renderer (`Build*SpriteQuad` → `SDL_Vertex`, `FlushSpriteBatch` → `SDL_RenderGeometry`).
- The `CGameState` screen state machine (`ChangeGameState`) — pure logic, no DX.
- The widget composite tree, event model, networking (`ws2_32` is portable), file formats (`.xfs`/`.img`/LZHUF).

**Needs real work**
1. **The software blitter.** `BlitSprite16bpp`/`Clipped`/`BlitRLESprite` write
   pixels directly into a locked RGB565 buffer and drive **all non-battle
   screens**. Two options:
   - *Faithful:* one full-screen streaming `SDL_Texture`, `SDL_LockTexture`
     each frame, run the same blit code, upload. Matches the original exactly.
   - *Idiomatic:* upload each `.img` sprite as an `SDL_Texture`, draw via
     `SDL_RenderTexture`/`SDL_RenderGeometry`, let the GPU composite. Faster,
     but changes the drawing model and the RLE font becomes a glyph atlas.
2. **Audio.** DirectSound gave mixing + hardware buffers for free; SDL3 audio is
   PCM streams. Use SDL_mixer (mp3 + mixing) or write a mixer over
   `SDL_AudioStream`. mp3 decode is not in core SDL.
3. **Text input.** The chat / room-name / password fields are real Win32 `EDIT`
   controls (`CEditBox`, slot `TextEntry_SyncFromControl` = `GetWindowTextA`).
   SDL3 has no native text widget — handle `SDL_EVENT_TEXT_INPUT`, render the
   string and caret yourself.

## Suggested milestones
1. Window + `SDL_Renderer`; port the software blitter as a streaming texture →
   get the logo/title/server-select screens drawing (no GPU path needed).
2. Port `SDL_Event` input + the widget hit-test/`OnCommand` flow → clickable UI.
3. Port the networking (`ws2_32` is already portable) → reach the lobby.
4. Port the in-battle `Build*SpriteQuad` family → `SDL_RenderGeometry` → battle.
5. Audio (SDL_mixer) last.
