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
- **OnEnter**: `0x4bb730` · **OnExit**: `0x4bcd00`

## Full vtable map
| Slot | Addr | Role |
|---|---|---|
| 0 | `0x4b4060` | destructor |
| 1 | `0x4b4100` | ProcessPacket |
| 2 | `0x4b5460` | ProcessBattleAction (battle-action channel) |
| 3,4 | `0x4fdef0` | shared no-op |
| 5 | `0x4b82b0` | **keyboard/chat-input dispatcher** (message-code switch) |
| 6 | `0x4b97d0` | **mouse-input dispatcher** (Win32 mouse codes) |
| 7 | `0x4bb730` | OnEnter |
| 8 | `0x4bcd00` | OnExit |
| 9 | `0x4bd8b0` | large multi-purpose per-tick hook: 8-dir screen-edge camera-scroll cursor logic, outgoing-packet field encoding, replay event logging, per-tick active-object GC (`FUN_004f3100`), turn-phase bookkeeping |
| 10 | `0x4c1b90` | chat character-input helper (emoticon/control-char remap: `@→0x0a`…`*→0x10`) |
| 11 | `0x4c1c90` | small per-tick counter/update helper |
| 12 | `0x4c1d10` | one-line delegate → `FUN_004508a0` at `+0x6a7f88` |
| 13 | `0x4c1d30` | **per-frame dynamic-texture clear**: Lock/zero-fill/Unlock (`DDSURFACEDESC2` 0x7c) across ~24 named effect textures (`AvataTexture`, `BulletTexture`, `FlameTexture1-4`, `ThorTexture`, …) |
| 14 | `0x4c3020` | `State11_InBattle_Render` (the D3D battle scene) |
| 15 | `0x4c8890` | **software-blit HUD/chat-log renderer** (see below) |
| 16 | `0x4caed0` | `State11_InBattle_RenderModeIcons` |
| 17 | `0x429800` | genuine no-op (state-specific empty override) |

## Rendering
- **Battle scene** (slot 14) via the D3D7 hardware pipeline — textured vertex
  path for terrain, mobiles, projectiles, rotation (turret/sprite rotation →
  hardware vertex pipeline; see ARCHITECTURE.md "Rendering").
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
- **Replay recording**: actions and chat are logged to the replay stream
  (see ARCHITECTURE.md "The replay-recording system").

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
