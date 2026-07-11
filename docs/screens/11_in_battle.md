# State 11 — In-Battle / Playing

The gameplay screen: the turn-based artillery match itself. The only screen
that uses the **hardware Direct3D 7** path (for the battle scene); its HUD/chat
overlay still uses the software blitter. The most complex state.

## Identity
- **State ID**: 11
- **vtable**: `vtable_State11_InBattle` (`0x5566d8`, 18 slots — fully mapped)
- **Object size**: 0x2408 (~9 KB) — constructed by `FUN_004b3f90`
- **ProcessPacket**: `State11_InBattle_ProcessPacket` (`0x4b4100`)
- **ProcessBattleAction**: `State11_InBattle_ProcessBattleAction` (`0x4b5460`)
- **OnEnter**: `0x4bb730` · **OnExit**: `0x4bcd00` · **OnTick**: `State11_InBattle_OnTick` (`0x4bd8b0`)

## Full vtable map
| Slot | Addr | Role |
|---|---|---|
| 0 | `0x4b4060` | `State11_InBattle_Delete` — scalar-deleting destructor (→ `State11_InBattle_Destroy` body `0x4b4080` + conditional `free`) |
| 1 | `0x4b4100` | ProcessPacket |
| 2 | `0x4b5460` | ProcessBattleAction (battle-action channel) |
| 3,4 | `0x4fdef0` | shared no-op |
| 5 | `0x4b82b0` | `State11_InBattle_HandleKeyInput` — **keyboard/chat-input dispatcher** (message-code switch) |
| 6 | `0x4b97d0` | `State11_InBattle_HandleMouseInput` — **mouse-input dispatcher** (Win32 mouse codes) |
| 7 | `0x4bb730` | OnEnter |
| 8 | `0x4bcd00` | OnExit |
| 9 | `0x4bd8b0` | **`State11_InBattle_OnTick`** — the per-frame update (largest function in the binary, 17 KB). Structurally confirmed as the OnTick slot: State02's vtable has the identical slot-7/8/9 = OnEnter/OnExit/OnTick layout. 8-dir screen-edge camera-scroll cursor logic, chat-input field poll (`GetWindowTextA`), outgoing-packet field encoding, broadcast-event logging, per-tick active-object GC (`FUN_004f3100`), turn-phase bookkeeping |
| 10 | `0x4c1b90` | chat character-input helper (emoticon/control-char remap: `@→0x0a`…`*→0x10`) |
| 11 | `0x4c1c90` | `RenderWindGaugeTick` — draws the wind gauge each tick: a rotating direction vane (8 frames) plus a digit-sprite wind-strength number, via `DrawWindGauge` (`0x406990`). Composited through the span-based HUD compositor (see ARCHITECTURE.md "The span-based HUD compositor"). |
| 12 | `0x4c1d10` | one-line delegate → `RenderWeatherHazards` (`0x4508a0`) — D3D pass for stage hazards (Tornado/Firewall/Lightning textures + additive-glow blend states) |
| 13 | `0x4c1d30` | `State11_InBattle_ClearEffectTextures` — **per-frame dynamic-texture clear**: Lock/zero-fill/Unlock (`DDSURFACEDESC2` 0x7c) across ~24 named effect textures (`AvataTexture`, `BulletTexture`, `FlameTexture1-4`, `ThorTexture`, …) |
| 14 | `0x4c3020` | `State11_InBattle_Render` (the D3D battle scene) |
| 15 | `0x4c8890` | `State11_InBattle_RenderHud` — **software-blit HUD/chat-log renderer** (see below) |
| 16 | `0x4caed0` | `State11_InBattle_RenderModeIcons` |
| 17 | `0x429800` | genuine no-op (state-specific empty override) |

## Rendering
- **Battle scene** (slot 14, `State11_InBattle_Render` `0x4c3020`, ~2250 lines)
  via the D3D7 hardware pipeline. It is a sequence of **~20 layer phases**, each:
  set blend mode if changed → `FindTextureCacheEntryByName(name)` → per-instance
  cull to the 800×600 clip rect + write atlas UV → `SetTexture` → one
  `DrawPrimitive(TRIANGLELIST, FVF 0x244)` flush. So **each layer is its own draw
  call** and the phase order is the back-to-front paint order:
  - background atlas (8-slot grid, per-player culled) → mobile/marker layers →
    animated **Flame** (`FlameTexture%d`, `FlameTexture2/3/4`) → **Rayon1/2**
    (rotated beam effects) → **Jewel** (*only when game mode == 3* — this gates
    the Jewel draw, confirming **mode 3 = Jewel**; drawn alpha + additive glow)
    → **Special1/2** (single object, alpha + additive) → main mobile block.
  - **Blend-state cache** (`g_currentBlendMode`): `1` = normal alpha
    (`SRCALPHA`/`INVSRCALPHA`), `2` = additive glow (`SRCALPHA`/`ONE`); only
    reprogrammed on change.
  - **Camera scroll** subtracted from world positions (`camX`=`g_nCameraX`,
    `camY`=`g_nCameraY`), biased by +400 / +0x12a (half of 800×600).
  - **Anti-cheat value guard**: the main mobile's gameplay values are read via
    `PeekPacketChecksumState` (×110) under `EnterCriticalSection(&DAT_005a9068)`;
    each value is a `(a,b,check)` triple validated as `check==(a+b-0x34)&0xff`,
    decoded as `(b>>(a&7))&1`, tamper → `g_valueGuardTamperFlag=1`, and the backing store
    (`DAT_0079376c`) is re-`rand()`-scrambled every frame. See ARCHITECTURE.md
    "The quad-emitter family and the in-battle scene composer".
  - **Teardown**: advance two particle-trail history ring buffers (trails fade
    over 15 / 7 frames), clear transient effect flags, optional full-screen 50%
    dim overlay for fade/pause.
- **Effect-texture clear** (slot 13) each frame before compositing effects.
- **HUD / chat log** (slot 15, `0x4c8890`, software blit): up to **10 chat
  history lines**, each with sender (`+0x58b64`, 9-byte stride), text
  (`+0x58bbe`, 14-byte stride), length (`+0x5917c`, u16), and a **message-type
  byte** (`+0x58c4a`) selecting an RGB565 color via switch (green `0x7e0`, blue
  `0x1f`, white `0xffff`, …) — team/system/normal chat are **color-coded**.
  Types 0/1/7 get a double-draw outline pass. Scoreboard uses the `%s[%3d/%3d]`
  bitmap-font format (`BlitRLESprite`).
- **Mode icons** (slot 16).

## Input
- **Keyboard** (slot 5) / **mouse** (slot 6) dispatch on Win32 message codes.
- **Fire input**: `State11_InBattle_HandleFireInput` (`0x45f910`).
- **Chat char append** (slot 10) with the emoticon/control-char remap table.

## Battle logic
- **Turn state machine** lives inside `ProcessBattleAction` (`0x4b5460`) — see
  ARCHITECTURE.md "The turn state machine". Ballistics (wind/angle/power),
  turn ordering, and per-mobile state are handled here.
- **Recording/broadcast**: actions and chat are written to the local `.sv`
  match record (`WriteReplayEventRecord`) *and* separately broadcast to peers
  over UDP (`QueueBroadcastEvent`/`BroadcastQueuedEvent`) — two distinct
  systems, see ARCHITECTURE.md "Two separate systems previously conflated as
  'replay'".

### Firing & projectile spawning
Each mobile's **slot-7 `MainAction`** is a `switch(animEvent)` weapon-fire
dispatcher (type 0 = `Mobile00_MainAction` `0x44e920`). At the fire frame it
reads the fire angle/power `CValueGuard`s (`+0x90c`/`+0xb30`) and position, then
calls one of three shared **projectile spawners** with the mobile's bullet type
(0–0xF) and a shot flag:
- **`SpawnPrimaryShot`** (`0x42bbb0`) — the main Shot-1/Shot-2 projectile;
  `switch(bulletType)` picks the per-type projectile class + `bullet{N}n`
  (normal) / `bullet{N}s` (super, `param_4`) texture.
- **`SpawnSuperShot`** (`0x42de70`) — the SS variant (`bullet{N}p` textures).
- **`SpawnItemProjectile`** (`0x4317b0`) — item-drop projectile (`bulletitem`).

All three `operator_new` the projectile, resolve its texture via
`FindPreloadedTextureByName`, serialize position + the **velocity vector**
(`power × g_sineTable360[angle]`, a 360-entry sine LUT indexed by
`(angle+90)%360` for the x/cos term and `angle%360` for the y/sin term, via
`FloatToInt64`) into the outgoing packet, append a **`0xf000`** broadcast event, and
register the object (`RegisterActiveObject` + `FUN_0041da80`). The per-projectile
constructors (`FUN_00454dc0`, `FUN_00468860`, …, one per bullet class) remain
`FUN_`-named. `g_sineTable360` is the ballistics sine table referenced above.

## Network (see PROTOCOL.md — "State 11")
- `State11_InBattle_ProcessPacket` (`0x4b4100`) for lobby-style opcodes and
  the dedicated **battle-action channel** via `ProcessBattleAction` (a second
  network path, direct `recvfrom` handling outside the queued-field API).

## Transitions
- **In**: from Loading (state 10).
- **Out**: back to Ready Room / Room List at match end.

## Reimplementation checklist
1. Construct the 0x2408 state object; assets are already preloaded by Loading.
2. Per frame: clear effect textures (slot 13) → render battle scene via D3D
   (slot 14) → render mode icons (16) → render HUD/chat overlay via software
   blit (15).
3. Input: keyboard/mouse dispatch on Win32 codes; fire input `0x45f910`; chat
   char append with the emoticon remap.
4. Drive the turn state machine in `ProcessBattleAction`; handle the battle
   action channel separately from the lobby opcodes.
5. Log actions + chat to the replay stream.
- This screen is large; each subsystem (D3D scene, turn machine, chat, replay)
  is documented in depth in ARCHITECTURE.md — this doc is the map, not the
  full territory.
