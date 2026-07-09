# Porting the GunBound client to SpriteKit

A reimplementation guide mapping this client to Apple's **SpriteKit** (2D scene
graph, Swift/Obj-C, iOS/macOS/tvOS), keyed to the recovered names. Pairs with
the [screen docs](screens/README.md), the [widget system](widgets.md), and the
[SDL3 guide](porting-sdl3.md).

## The one idea that makes this a great fit
SpriteKit **is** a scene graph with the composite pattern built in — and this
client is *already* structured that way:

- The game is a **state machine of screens** (`CGameState`, `ChangeGameState`).
  → each screen is an **`SKScene`**; `ChangeGameState(n)` → `view.presentScene`.
- The UI is a **composite tree of widgets** (`CWidget`/`CPanel`, `Draw`
  broadcasting to children — see [widgets.md](widgets.md)).
  → the widget tree becomes an **`SKNode` subtree**; SpriteKit does the
  broadcast render/hit-test for you.
- Sprites are textured quads with rotation/scale/blend.
  → **`SKSpriteNode`** with `zRotation`, `xScale`/`yScale`, `blendMode`.

So unlike the SDL3 port (which mirrors the original's low-level pixel pipeline),
SpriteKit is a **re-expression at a higher level**: you throw away the manual
vertex batching, the software blitter, and the Z-buffer, and let the scene graph
own rendering. It's more "reimagine idiomatically" than "faithful port."

## Subsystem mapping

| This client (recovered names) | SpriteKit / Apple frameworks |
|---|---|
| `CGameState` screen (State 1–11) | an **`SKScene`** subclass per screen |
| `ChangeGameState(n)` | `skView.presentScene(scene, transition:)` |
| `GameTick` (~50 ms loop) | `SKScene.update(_ currentTime:)` (per-frame); use a fixed-timestep accumulator for the 50 ms tick |
| `CWidget` / `CPanel` composite tree | an **`SKNode`** hierarchy (`addChild`) |
| leaf `CLabel` / `ButtonWidget` | `SKSpriteNode` (+ `SKLabelNode` for text) |
| `CScrollBar` / `CreateScrollListWidget` | a cropped `SKCropNode` + a draggable thumb node (no built-in scroller) |
| `CEditBox` (Win32 EDIT text field) | overlay a `UITextField`/`NSTextField` on the `SKView`, or `UITextInput` |
| `FindSpriteFrame` / sprite-sheet frames | `SKTexture` + `SKTextureAtlas` (frames by name) |
| `Build*SpriteQuad` + `FlushSpriteBatch` (manual GPU batch) | **gone** — set `SKSpriteNode.position/zRotation/scale`; SpriteKit batches |
| sine-table rotation (`g_sineTable360`) | `node.zRotation` (radians) |
| additive blend (`DESTBLEND=ONE`) | `spriteNode.blendMode = .add` |
| diffuse color / tint | `node.color` + `node.colorBlendFactor` |
| Z-buffer / draw order | `node.zPosition` (explicit; replaces the HAL Z-buffer) |
| `BlitSprite16bpp` software blit | **gone** — every `.img` sprite becomes an `SKTexture` |
| `BlitRLESprite` bitmap font | `SKLabelNode` (system/bundled font) or a bitmap-font atlas |
| `PresentFrame` / DirectDraw surfaces | handled by `SKView`; you never touch surfaces |
| DirectSound8 + `.mp3` | `SKAudioNode` / `SKAction.playSoundFileNamed` (SFX); `AVAudioPlayer` for streamed mp3 music |
| DirectInput8 + `WndProc` mouse/keys | `touchesBegan`/`mouseDown` on the scene, or `UIGestureRecognizer` |
| the `+0x1c` `OnCommand(evt,id,arg)` callbacks | Swift closures / delegate protocol / `NotificationCenter` |
| Winsock connection subsystem | `Network.framework` (`NWConnection`) or BSD sockets |
| `.xfs`/`.img`/LZHUF asset loading | keep the loaders; decode to `CGImage` → `SKTexture` |

## How the pieces re-express

**Screens.** Each `CGameState` becomes an `SKScene`. `OnEnter` → `didMove(to:)`
(build the node tree, load textures, start music). `OnExit` → `willMove(from:)`.
`OnTick`/render slots → `update(_:)` and the scene graph's automatic render.
`ProcessPacket` stays as-is (network logic, framework-independent).

**Widgets.** Rebuild each panel's composition (documented per builder in
[widgets.md](widgets.md)) as `SKNode`s:
- `BuildWorldListPanel` → an `SKNode` with two button `SKSpriteNode`s
  (View All / Friends) + a scroll region; the 16 server rows become child
  nodes instead of the direct-blit `RenderWorldListRow` loop.
- `BuildBuddyPanel`, `BuildCreateRoomDialog`, etc. → the same child lists.
- Hit-testing: `SKNode.contains(point)` / `nodes(at:)` replaces `Widget_HitTest`;
  a tap runs the node's action closure — the SpriteKit-native form of the
  `OnCommand(0, id, 0)` click callback.

**Scrolling.** SpriteKit has no scroll view. Put list rows under an `SKCropNode`
(clips to the panel rect) and move the content node's `position.y`, driven by a
draggable thumb `SKSpriteNode`. This replaces `CScrollBar` and its `0x2000`
callback; server-side pagination (`0x1100`/`0x1102`) is unchanged.

**The battle scene.** `State11_InBattle_Render`'s per-layer
`FindTextureCacheEntryByName` → `Build*SpriteQuad` loop becomes a set of
persistent `SKSpriteNode`s (terrain, mobiles, projectiles, effects) whose
`position`/`zRotation`/`texture` you update each `update(_:)`. Effect textures
that used additive blend → `blendMode = .add`. No vertex buffers, no flush.

## What's easy vs. what needs real work

**Easy / idiomatic**
- Screens → `SKScene`, widgets → `SKNode`, sprites → `SKSpriteNode`. The
  composite-and-state-machine shape of the original maps directly.
- Rotation/scale/blend/tint are one property each.
- Networking, file formats, and game logic are framework-independent.

**Needs real work / caveats**
1. **You lose exact-pixel fidelity.** The original is RGB565 with hand-written
   blits; SpriteKit is a modern compositor. It'll look *cleaner*, not
   pixel-identical. If bit-exact reproduction matters, prefer the SDL3 path.
2. **No native scroll view or text field.** Reimplement the scrollbar
   (`SKCropNode`) and text entry (`UITextField` overlay). These were "free"
   Win32/DirectDraw features.
3. **Fixed timestep.** `update(_:)` runs at display refresh (60/120 Hz), not the
   game's 50 ms tick. Use an accumulator so physics/turn logic still step at
   20 Hz while rendering interpolates.
4. **Audio format.** SpriteKit SFX want short files; stream mp3 music through
   `AVAudioPlayer`/`AVAudioEngine`, not `SKAudioNode`.
5. **Platform.** Apple-only. Input is touch (iOS) or mouse (macOS) — the mouse
   message handling maps to macOS `mouseDown`; a touch UI is a redesign.

## When to choose this vs. SDL3
- **SpriteKit** — you want an idiomatic Apple-platform reimplementation, are
  happy to modernize the look, and value the near-1:1 scene-graph/state-machine
  fit. Least code, most re-expression.
- **SDL3** ([porting-sdl3.md](porting-sdl3.md)) — you want a faithful,
  cross-platform port that mirrors the original's pixel pipeline (RGB565
  blitter, batched quads) closely.
