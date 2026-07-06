# GunBound Client — Reverse-Engineered Architecture Notes

Findings from static analysis in Ghidra (`ghidra_proj/`), confirmed via decompiled
pseudocode, cross-referenced call sites, and data-layout inspection — not guesses.
Confidence is noted per finding. This complements [PROGRESS.csv](PROGRESS.csv)
(the flat function worklist) with structural/behavioral understanding.

## Entry point and top-level flow

`WinMain` (`0x40d8e0`) — registry checks, single-instance mutex, window
registration/creation (`WndProc` at `0x410040`), `WSAStartup`, then:
- `InitGame` (`0x40eaa0`, hWnd, hInstance) — sets up DirectDraw/DirectSound/
  DirectInput and constructs the 16-slot game-state object array (see below).
- Standard Win32 message loop: `PeekMessage` when idle calls `GameTick`
  (`0x413130`) every idle cycle (the per-frame update/render tick);
  `GetMessage`/`DispatchMessage` otherwise.
- `Shutdown` (`0x40f400`) tears down sockets/DirectX on exit.

## The game-state machine

**High confidence**, fully evidence-backed:

- `g_gameStateVTableArray` (a.k.a. `g_gameStateObjects`, base `0x5b33f8`) is a
  **16-element array of pointers to heap-allocated C++-style objects**, one per
  game state. Confirmed by: `ChangeGameState`'s special-case
  `newStateId == 0xf` (15, quit) landing exactly on array element 15
  (`0x5b33f8 + 15*4 = 0x5b3434`), and that element sharing the *same* trivial
  vtable (`0x553fb0`) as element 0 — a null-object pattern for the two states
  that need no real enter/exit behavior (pre-init and quit).
- `ChangeGameState(int newStateId)` (`0x4122f0`) is the state transition
  function. It calls `object[oldState]->vtable[+0x20]()` (exit hook) then
  `object[newState]->vtable[+0x1c]()` (enter hook), and updates
  `g_currentGameState`. Originally took its argument via the **ESI register**
  (a custom calling convention Ghidra didn't infer) — this has been fixed in
  the Ghidra project so the parameter now shows as a normal `int`.
  - Two call patterns exist: **immediate** (`WinMain`, some `GameTick` paths
    call it directly) and **deferred** (scattered game-logic code sets
    `g_pendingGameState` + `g_stateChangeRequested`, and `GameTick` polls and
    dispatches it next frame).
- Related globals: `g_currentGameState` (`0x7934d0`), `g_pendingGameState`
  (`0x5b33ec`), `g_stateChangeRequested` (`0x7934d4`),
  `g_stateChangeInProgress` (`0x793508`).

### The 16 game states — CONFIRMED by resource strings

Each state's `OnEnter` hook (vtable slot 7, offset `+0x1c`) loads a named
`.img`/`.mp3` resource set that identifies the screen unambiguously. Names in
the Ghidra project follow `StateNN_Name_OnEnter/OnExit`; vtables are
`vtable_StateNN_Name`.

| Id | Screen | Identifying resources | Object size / ctor |
|---|---|---|---|
| 0 | Null/pre-init | (shared trivial vtable `0x553fb0`) | 4 |
| 1 | **Title** | `titlemode.img`, `title.mp3` | 8 |
| 2 | **Server / Channel select** | `server_list.img`, `b_server_choiceserver.img`, `channel.mp3` | 0x6c |
| 3 | **Game Room List** (channel lobby) | `gamelist_back.img`, `gamelist_create.img`, `b_gamelist_join/ranking/avatar/buddy.img` | 0x294 — **owns `ProcessPacket`** (see below) |
| 5 | **Logo screen 1** | `logomode.img`, `logo.mp3` | 8 |
| 6 | **Logo screen 2** | `logomode2.img`, `logo2.mp3` | 8 |
| 7 | **Avatar Store / Shop** | `store_*.img`, `b_store_buy/cap/cloth/glasse/flag.img` | 0x34818 (215 KB); ctor `FUN_00443c20` builds an 8×0x224-byte array (per-avatar slots) |
| 9 | **Ready Room** (pre-battle) | `ready_selectmap.img`, `ready_selectcharacter.img`, `b_ready_startgame.img` | 0x78c; ctor `FUN_004d3770` |
| 10 | **Loading** | `loadmode.img`, `loadstage.img` | 0x150 |
| 11 | **In-Battle / Playing** | `stage%d.mp3`, `b_play_weapon2/weapon3/skip/tag/all` | 0x2408 (9 KB); ctor `FUN_004b3f90` |
| 12–14 | (unused/reserved) | none constructed | — |
| 15 | **Quit** | shares null vtable `0x553fb0`; `ChangeGameState(0xf)` calls `PostQuitMessage(0)` directly | 4 |

**Screen flow** (from `ChangeGameState` targets): Logo1(5) → Logo2(6) →
Title(1) → ServerSelect(2) → GameRoomList(3) ⇄ AvatarStore(7), and
GameRoomList(3) → ReadyRoom(9) → InBattle(11), with Loading(10) interstitial.
States 0 and 15 use a shared trivial "null object" vtable — the null-object
pattern for states needing no enter/exit behavior.

## Network protocol (via `ProcessPacket`)

`ProcessPacket` (`0x426ad0`, was `FUN_00426ad0`) — **high confidence**: virtual
method on the **state-3 Game Room List** object (which doubles as the
network-session owner while in the channel lobby), signature
`void ProcessPacket(int payloadLen, unsigned short opcode, unsigned short *payload)`
(this-pointer auto-parameter + 3 named params, confirmed via decompiler commit).
Dispatches purely on `opcode`; this is the client's incoming-packet handler.

Confirmed/observed opcodes (all tentative on *meaning*, confirmed on *existence
and branch target*):

| Opcode | Behavior |
|---|---|
| `0x2001` | Branches on `*payload==0`; calls one of two cleanup/notify helpers, then `FUN_00507cc0(1, ...)`. |
| `0x201f` | Looks up a slot via `FUN_004259d0`; on miss, calls `FUN_0041b8c0` with derived offsets — looks like a per-slot record insert (chat line? item?). |
| `0x2103` | Populates a per-player-slot array (name/flags/stats) up to `playerCount` slots — **room player list update**. |
| `0x2105` | separate branch, not yet decompiled in detail |
| `0x2111`, `0x2121` | Same `0x21xx` cluster as `0x2103`/`0x21f0`/`0x21f1` — likely room/lobby-related. |
| `0x21f0` | Writes into a per-slot buffer at `object + slot*0x80`, gated on `FUN_0041c290() != -1`. |
| `0x21f1` | separate branch, not yet decompiled in detail |
| `0x6001` | Unpacks 4 uint fields, builds an array of per-"player" 3-byte tuples using `rand()` (seed/roll generation?), then `ChangeGameState(7)` = **enter Avatar Store**. (Earlier notes guessed "room→game"; the target state is the store, per confirmed state IDs.) |
| (unlabeled, reaches `ChangeGameState(9)`) | Large per-slot stat-accumulation loop (20 elements × 0x224 bytes) summing what look like equipped-item stat bonuses per player/team slot, resets viewport to `(0,0,799,599)`, then `ChangeGameState(9)` = **enter Ready Room**. |

The `0x20xx` cluster looks like lobby/session-level opcodes, `0x21xx` looks like
room-level opcodes, `0x60xx` looks like in-game/battle opcodes — consistent
with a classic tens-of-opcodes-per-category protocol design, but this
categorization is a pattern observation, not confirmed from source.

## Recurring structure sizes (useful anchors for further work)

- **0x224 (548) bytes** — recurring per-player-slot structure size (seen in the
  state-7 object's 8-element array, and in a 20-element accumulation loop in
  `ProcessPacket`). Likely the core per-player game-data struct.
- **0x17e4 (6,116) bytes** — two large arrays (9 and 21 elements) inside the
  state-7 object, constructor `FUN_00425350` / destructor `FUN_004254a0`.
  Purpose unknown; possibly per-round history, per-map-tile, or animation data.

## Subsystem init functions (confirmed)

- `InitDirectDraw` (`0x4efaa0`) — `LoadLibraryA("ddraw.dll")` + `DirectDrawCreateEx`.
- `InitDirectSound` (`0x4ee5b0`) — `LoadLibraryA("dsound.dll")` + `DirectSoundCreate8`.
- `InitDirectInput` (`0x4edc50`) — `LoadLibraryA("dinput8.dll")` + `DirectInput8Create`.
- `InitCommP2PNotifyWindow` (`0x4fdf00`) — hidden `STATIC` window
  ("CCommP2P<> Notify Window") used as a `WSAAsyncSelect`/event-notify target.
- `ReadRegistryDword` / `WriteRegistryDword` / `GetDisplayConfigFromRegistry`
  (`0x40c470`/`0x40c550`/`0x40c620`) — persist display bit-depth setting under
  `Software\Softnyx\GunBound`.

## Open threads / good next targets

1. **DONE** — all 16 game states identified and named (see table above).
2. Each state object's vtable is ~18 slots with a common layout (slot 0 shared
   base method `0x4e5320`; slot 2 = no-op stub `0x4fdef0`; slot 7 = OnEnter;
   slot 8 = OnExit). Slots 3–6, 9+ are per-state input/update/render handlers,
   mostly still `FUN_*`. Naming these per state (using the OnEnter resource
   context) is the next systematic pass.
3. Five `ChangeGameState` call sites (`0x443350`, `0x443561`, `0x4b9ebe`,
   `0x4e0c68`, `0x4e5421`) are switch/jump fragments *inside* larger functions
   whose auto-analysis was truncated — no standalone prologue nearby. They need
   manual function-boundary repair in the Ghidra GUI (force-disassemble the
   containing region); forcing a Function object at the fragment start would
   yield wrong decompilation. Low priority — they don't block anything.
4. Map the rest of `0x2xxx`/`0x21xx`/`0x60xx` opcode space by finishing the
   `ProcessPacket` decompile (only partially read here).
5. Confirm the 0x224-byte per-player struct layout — cross-reference against
   the same stride appearing in other subsystems (rendering, item/character
   data files) to build a canonical `struct Player`.
6. Identify the shared base-class methods (`0x4e5320` = every state's vtable
   slot 0; `0x448430` = slot-1 in several) — likely `CGameState` base
   ctor/dtor/type-id; naming them documents the state base class.
