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

## The `CGameState` base class and virtual dispatch

**High confidence.** Every state object shares a common base class whose vtable
layout (confirmed across states 1–11) is:

| Slot | Offset | Role | Evidence |
|---|---|---|---|
| 0 | +0x00 | scalar-deleting destructor | `CGameState_ScalarDeletingDestructor` (`0x4e5320`) on every state; calls `CGameState_BaseDestructor` (`0x426ac0`), which resets the vtable ptr to the shared null-object vtable (`0x553fb0`) — a "poisoned after destroy" idiom. |
| 1 | +0x04 | **`ProcessPacket(int payloadLen, ushort opcode, ushort *payload)`** | Virtual, overridden per state. No-op in states that don't need network handling (`CGameState_NoOpVirtual_A`, `0x448430`). Real overrides confirmed for state 2 (`State02_ServerSelect_ProcessPacket`, `0x4e02b0`), state 3 (`State03_GameRoomList_ProcessPacket`, `0x426ad0`), state 7 (`State07_AvatarStore_ProcessPacket`, `0x4440c0`) — all three share the identical `(this,int,ushort,ushort*)` signature, confirmed via decompiler param commit. |
| 2–4 | +0x08..+0x10 | other per-state virtuals, usually no-op (`CGameState_NoOpVirtual_B`, `0x4fdef0`) except where overridden (e.g. state 3 slots 5–6 at `0x4285c0`/`0x428b90`) | input handlers? (untested) |
| 7 | +0x1c | **OnEnter** | confirmed for all named states — loads that screen's `.img`/`.mp3` resources |
| 8 | +0x20 | **OnExit** | confirmed for all named states |
| 9 | +0x24 | another per-state virtual, present past OnExit | untested |

Each screen effectively has its **own protocol dispatcher** — decompiling
state N's slot-1 override is the way to find that screen's opcode handling
(server list ops live in state 2's handler, avatar-store purchases in state
7's, etc.), not just the room-list one.

## Network protocol — `State03_GameRoomList_ProcessPacket` (`0x426ad0`)

This is the channel-lobby/room-list screen's packet handler — the most fully
mapped of the three known `ProcessPacket` overrides. Confirmed opcodes:

| Opcode | Behavior |
|---|---|
| `0x2001` | Branches on `*payload==0`; calls one of two cleanup/notify helpers, then `FUN_00507cc0(1, ...)`. |
| `0x201f` | Looks up a slot via `FUN_004259d0`; on miss, calls `FUN_0041b8c0` with derived offsets — looks like a per-slot record insert (chat line? item?). |
| `0x2103` | Populates a per-player-slot array (name/flags/stats) up to `playerCount` slots — **room player list update**. |
| `0x2105` | Copies a string + several small fields into a per-slot 0x80-byte display buffer at `+0x4467c` (slot stride 0x80), then mirrors it into `this+300`/`this+0x1ac`/`this+0x1b0` — **player info/profile broadcast for a target slot** (`this+0x124` holds the target slot index, set by a prior packet). |
| `0x2111` | separate branch, not yet decompiled |
| `0x2121` | `*payload==0` path: increments a counter at `+0x4739c`, sets `this+0x115=2` (a status/mode byte), copies this client's name into a persistent buffer — looks like **"you joined/were assigned to a game" confirmation**. |
| `0x21f0` | Writes into the same per-slot 0x80-byte display buffer as `0x2105`, gated on `FUN_0041c290() != -1` (find-my-slot helper) — companion write path to `0x2105`. |
| `0x21f1` | Searches the room's player-ID array (`+0x44664`) for `*payload`; on match, clears that slot (`+0x4464c + idx*4 = 0`), and if it's this client's own slot, resets `this+4` to -1 — **player left the room**. |
| `0x6001` | Unpacks 4 uint fields, builds an array of per-"player" 3-byte tuples using `rand()` (seed/roll generation?), then `ChangeGameState(7)` = **enter Avatar Store**. |
| (unlabeled, reaches `ChangeGameState(9)`) | Large per-slot stat-accumulation loop (20 elements × 0x224 bytes) summing what look like equipped-item stat bonuses per player/team slot, resets viewport to `(0,0,799,599)`, then `ChangeGameState(9)` = **enter Ready Room**. |

The per-slot 0x80-byte display buffer at `+0x4467c` (name + a handful of stat
bytes/dwords) is a good anchor for reconstructing a `struct RoomPlayerSlot`.

**Confirmed opcode-range-per-screen pattern**: state 3 (room list) uses
`0x20xx`/`0x21xx`, state 2 (server select) uses `0x10xx`/`0x11xx`, state 7
(avatar store) uses `0x60xx`. Opcode value `0x2001` is reused verbatim between
state 3 and state 7's dispatchers with the same generic-cleanup meaning, and
`0x6001` is reused between the room-list and store dispatchers with different
meanings — the opcode namespace is scoped by which screen is active, matching
how the server tracks each client's current context.

## Network protocol — `State02_ServerSelect_ProcessPacket` (`0x4e02b0`)

| Opcode | Behavior |
|---|---|
| `0x1001` | **Outgoing packet builder** (not a received-opcode branch in the usual sense — triggered by the server's request). Writes opcode `0x1010` into the send buffer at `DAT_007934ec+0x4d4`, appends this client's own info via `FUN_004d2570`, then calls `getsockname()` **twice** to grab the local socket's bound address, appending both into the outgoing packet, then finalizes/sends via `FUN_004d25e0`/`FUN_004d2680`. **This is the P2P NAT-traversal handshake** — the client reports its own local `IP:port` back to the server (ties to the `CCommP2P<>` notify window found in Phase 1; GunBound uses server-mediated P2P for actual battle traffic). |
| `0x101f` | Sets `DAT_00e55e3c=1`, `DAT_007934f8=1` (login/session flags), stores `*payload` and `payload[2]` into globals `DAT_005b2b54`/`DAT_005b343c` — likely session ID / server address handoff after channel selection. |
| `0x1012` | Error-code translator: maps server error codes `0x5001/0x5011/0x5012/0x5013` to sequential internal reason codes `0x1d..0x20` stored per-slot, then calls `FUN_004065a0()` (room-membership check) — likely drives a "can't join: <reason>" error dialog. |
| `0x1102` | Zeros a 4 KB buffer then parses a list of variable-length entries (2-byte + 1-byte + length-prefixed string) into a table at `+0x3f84a` — **server/channel list population** for the "choiceserver" screen. |

## Network protocol — `State07_AvatarStore_ProcessPacket` (`0x4440c0`)

| Opcode | Behavior |
|---|---|
| `0x600f` | Builds and sends an outgoing `0x6000` request (empty payload) — likely "give me my inventory," triggered on entering the store. |
| `0x6002` | Parses a list of **owned-item entries**: each has a timestamp (parsed via `_localtime` → day/month/year, i.e. an **expiration date**), item-id fields, and a variable-length blob, stored into a per-item array at `+0x44be8` with a **confirmed 0x9c (156)-byte stride**. This is the **inventory/purchased-items list**. |
| `0x6017` (`*payload==0`) | Builds a **purchase confirmation dialog**: loads localized strings by resource ID (`FUN_0043dc70(&DAT_00796eec, 0xea6a..0xea6d)`), formats item name/price via `sprintf`, shows the `b_storewindow_confirm` popup image. |
| `0x6017` (`*payload==0x6003`) | Sends a `0x6000` reply packet — likely the purchase confirmation's "yes" response. |
| `0x6037` (`*payload==0`) | Guards on a slot-count check (`FUN_004010c0(0x80070057)` fatal-errors if out of range) then calls `FUN_0044c370()` — a purchase-commit path, not fully traced. |

## Network protocol — `State09_ReadyRoom_ProcessPacket` (`0x4d38c0`)

Opcodes `0x30xx`/`0x31xx`/`0x32xx`/`0x34xx`/`0x44xx`. This handler is also where
the **replay-recording system** (see below) is driven from — most branches
call `Replay_AppendEvent` with a distinct event-type code.

| Opcode | Behavior |
|---|---|
| `0x2001` | **Leave ready room.** If a flag (`DAT_00793522`) is set, force-exits state 11 (In-Battle) via its own vtable exit-hook (`g_gameStateObjects[0xb]+0x20`) — i.e. this can tear down an in-progress battle. Then `g_pendingGameState = 3` (back to Game Room List). |
| `0x3010` | Calls `FUN_004db720()` (start/ready toggle?) then `FUN_004dc200(*payload)` with a byte value (character or team selection) and `FUN_004dc5c0()` (finalize). |
| `0x3020` | Calls `FUN_004db720()` only — simpler ready/unready toggle. |
| `0x3105` | Records replay event `0x8102` (self) or `0x8000`+player-id+position fields (others), and sends `WM_USER+...` (`0xc5`) UI notification — **player joined ready room**. |
| `0x3151` | Records replay event `0x8200` with `payload[2]` — likely **team change**. |
| `0x3201` | Records replay event `0x8100` with two fields from `this` — likely **weapon/character selection change**. |
| `0x3211` | Records replay event `0x8101` — likely **map vote/selection**. |
| `0x3231` | Records replay event `0x8102` — **ready-status toggle**. |
| `0x3fff` | Sends outgoing packet opcode `0x2000` with payload `0xffff` — **leave/cancel notification to server**. |
| `0x3432` | Closes the open replay file (`fclose`) if one is open — **match/session end, stop recording**. |
| `0x4410` (only if not already leaving) | Replies with outgoing opcode `0x3232` — looks like a **server keepalive/ping ack**. |

## Network protocol — `State11_InBattle_ProcessPacket` (`0x4b4100`)

Opcodes shared with the ready room (`0x2001`, `0x3020`, `0x3233`, `0x3400`,
`0x3fff`, `0x4410`) plus battle-specific ones (`0x4102`, `0x4413`).

| Opcode | Behavior |
|---|---|
| `0x2001` | **Leave battle** → `g_pendingGameState = 3` (Game Room List). |
| `0x3020` | **Player disconnected mid-match**: removes the player from the 8-slot array (shifts remaining slots down, matching the confirmed `0x224`-byte stride: `slot * 0x224`), records replay event `0x307`/`0x8500` with the departed player's stats, and — if the departed player held the active turn — reassigns it (`FUN_00413bf0`, likely `AdvanceTurn`). |
| `0x3233` | **Match ends** → `g_pendingGameState = 9` (back to Ready Room). Writes a terminator byte (`2`) to the replay file and closes it — matches state 9's `0x3432` as the recording bookend. |
| `0x3400` | separate branch, not fully traced |
| `0x3fff` | Same "leave/cancel" outgoing `0x2000`/`0xffff` packet as the ready room. |

## Battle action protocol — `State11_InBattle_ProcessBattleAction` (`0x4b5460`)

**Answers the open question from the previous round**: the actual move/aim/
fire/damage traffic is *not* handled by `State11_InBattle_ProcessPacket`
(`0x4b4100`) — it's a **separate `CGameState` virtual method, vtable slot 2**
(`+0x08`, right after `ProcessPacket` at slot 1). Confirmed via decompile +
`bsfire`/`bfire1`/`bfire2`/`bifire`/`ifire`/`sfire` (weapon-firing cursor
images) and `sudden.mp3` (sudden-death music) string references — this is
unambiguously the core battle simulation, and the largest function in the
binary (11,718 bytes).

**This is a real, second protocol channel, not an isolated one-off.** Slot 2
is the shared `CGameState_NoOpVirtual_B` no-op for every state *except*
Loading (`0x43e440`), Ready Room (`0x4d4ea0`), and In-Battle (`0x4b5460`) —
exactly the three states where P2P connection setup and real-time sync would
matter. All three share the *identical* packet header format and an
overlapping action-code namespace (confirmed: action `3` = `ShowMessage` in
both Loading and In-Battle; action `0x8100` in Ready Room matches a replay
event code also used elsewhere). Working theory: **slot 1 (`ProcessPacket`)
is the reliable server-relayed protocol; slot 2 is the real-time P2P channel**
(`recvfrom`/`sendto`, the `CCommP2P<>` notify window from Phase 1) — not
proven at the socket-receive level, but the state-coverage pattern alone is
strong evidence.

A striking confirmation of the cross-state design: Loading's slot 2 handles
action `0xc301` by writing directly into the **In-Battle object's fields**
(`g_gameStateVTableArray[0xb]`, i.e. state 11, `+0x10a4` and `+0x2302`)
*before* state 11 is even the active state — pre-populating battle setup data
(a turn-timer value, checked against `60000`/`0xffff` — 60000 ms matches
GunBound's classic 60-second turn limit — and an 8-element array, likely
wind/spawn data) while still on the loading screen.

**Packet header** (`packetBuf`, `packetLen`):
- `+0x02` (ushort): action type — families seen: `0x3`, `0x40xx`, `0x84xx`,
  `0x85xx`, `0xc4xx`, `0xc801`.
- `+0x05` (byte): source player slot, **validated `<= 7`** (confirms the
  8-player cap independently again).
- `+0x21` (33): payload start.

Action `0x8500` matches a replay-log event code exactly — strong evidence this
function processes **both live network packets and recorded replay events**
through the same code path (i.e. replay playback re-feeds logged `0x8xxx`
events into this same dispatcher rather than having a separate player).

| Action | Behavior |
|---|---|
| `3` | Calls the `ShowMessage`-style virtual at `this vtable +0x28` with a formatted string — a generic in-battle notification/toast. |
| `0x4001` | Single-byte flag toggle (only when the acting slot isn't this client) — cheap status flag, not yet identified precisely. |
| `0x4002` | **Chat message with spatial proximity filtering**: computes the distance between the sender and each of the 8 player slots, delivering the message only within ~150 units — positional/proximity chat during battle. |
| `0x4003`, `0x4004` | Similar per-player text-record lookups/inserts (`FUN_004259d0`/`FUN_0041b8c0`, the same helpers seen in the room-list handler) — likely other chat/notification variants (team chat? system message?). |
| `0x8402`, `0x8406` | Relay two ushort fields + a boolean flag from the packet, re-encoding them into an outgoing packet via `QueueOutgoingPacketField`/`EncodeOutgoingPacketField` — likely an **aim/angle+power update being forwarded to other clients**. |
| `0x8403` | **Fire.** The richest payload: 2 fields, 2 bool flags, 2 more fields, then **8 sequential shorts** (`+0x2c`..`+0x3a`, 16 bytes — likely trajectory waypoints or arc sample points), forwarded via the same outgoing-encode helpers, then plays the `ifire` sound effect. This is the confirmed weapon-fire action; exact waypoint semantics not yet decoded. |
| `0x8404` | Appends a new entry across four parallel per-slot arrays at `+0x27`/`+0xa7`/`+0x127`/`+0x1a7` (a *different*, smaller set of parallel arrays than `0x8408`'s) — some other per-shot or per-projectile record, calls `FUN_004ccbb0`. |
| `0x8405` | Plays one of three weapon-select sounds (`b_play_weapon1/2/3`) based on which weapon slot was chosen — **weapon selection**. |
| `0x8407` | Selects one of three lookup tables by a mode byte (1/2/3) — purpose unclear, possibly per-weapon or per-stage table selection. |
| `0x8408` | **Player spawn into battle**: appends a new entry across four parallel per-slot arrays at `+0x228`/`+0x2a8`/`+0x328`/`+0x3a8` (position/id/slot fields), calls `FUN_004ccc60` (spawn visual?), increments the player count. These are the *same* parallel arrays that `0x3020`'s disconnect handler shifts down — confirms a structure-of-arrays layout for the 8 battle slots. |
| `0xc300` | **Turn start** (best guess): posts three chained sub-events via `PostTurnEvent(&DAT_00e55ce0, code)` — `0xc300` (self), `0xc306`, `0xc40b` — a genuine turn/round event-dispatch mechanism. The `0xc306`/`0xc40b` handlers are the natural next lead for finding the actual physics tick. |
| `0xc301` | **Turn timer/setup** — shared verbatim with `State10_Loading_ProcessBattleAction`: writes the turn-timer field (`+0x10a4`, checked against `60000`ms) and copies an 8-element setup array (`+0x2302`, likely wind/spawn data). |

**On `QueueOutgoingPacketField`/`EncodeOutgoingPacketField`** (`0x40a470`/
`0x40a380`, renamed from `FUN_0040a470`/`FUN_0040a380`): initially mistaken for
a physics event queue. Decompiling in full showed it's a **critical-section-
protected packet encoder that XORs each field against a rolling 16-byte table**
indexed by a counter — i.e. GunBound lightly **obfuscates/checksums its
outgoing packets**. So actions like `0x8403`/`0x8406` that call this are
re-encoding received data into a *new outgoing packet* (relay/forward/ack),
not feeding a local simulation queue.

**Rendering vs. physics, disambiguated.** `GameTick` calls a sequence of
In-Battle-specific vtable slots every simulation tick (fixed **50 ms / 20 Hz**,
confirmed via `(now - lastTick) / 50`). Traced all of them: slots 9, 11–17
(`+0x24` through `+0x44`) resolve to texture loading, the main render function
(confirmed via `ThorTexture`/`BulletTexture`/`LaserEffect` strings — this is
literally the sprite renderer, not physics), a post-match slot-machine
minigame, and a results-scoreboard formatter. **None of them contain the
gravity/trajectory integration** — that logic is not in this per-frame vtable
pipeline. Also ruled out: the game's `sin`/`cos` CRT calls (only 4 tiny
generic-math callers, not game code) and a very FPU-dense function cluster at
`0x51xxxx` (almost certainly compiler-generated C++ `<complex>` arithmetic,
sitting among confirmed CRT/exception-handling functions).

**Confirmed real finding along the way**: `g_sineTable360` (`0x54c240`) is a
360-entry precomputed sine lookup table, indexed via `angle % 360` (cosine via
`(angle+90) % 360`) — the classic technique for this era. Used by the render
function for sprite rotation/orientation (turret angle, etc.) — confirmed
caller is the render pipeline, not a physics function, but the same table is
almost certainly reused by whatever function does compute trajectories.

## The turn state machine (inside `ProcessBattleAction`)

Fully read through this function's remaining branches this round. `param_1[0x42e]`
is a **turn-phase field** (values 0/3/4 seen). `PostTurnEvent` (`0x4e7d30`,
delegating to `0x4e86f0`) inserts into a **sorted STL-style tree keyed by
trigger time** — a scheduled/delayed event queue, not a direct dispatch. This
confirms turn progression is driven by a chain of timed sub-events, not a
single function call:

| Action | Behavior |
|---|---|
| `0xc300` | **Turn/round start.** Posts a long chain of scheduled sub-events: `0x8005`, `0x8006`, `0xc306`, `0xc400`, `0xc401`, `0x8403` (Fire), `0x8405` (weapon sound), `0xc409`. |
| `0xc303` (sub-switch on a byte) | `0`/`1`/`2` set the turn-phase field to `3`/`4`/`0`. `0xe`/`0xf` (near-identical bodies) do full turn-setup (viewport data, sound) then post the *same* `0xc300` event chain — i.e. these are two slightly different "advance to next turn" triggers (normal end vs. timeout/surrender, unconfirmed which). |
| `0xc304` | **Movement.** Sub-cases on a 4-bit direction value (1/2/3, and a `&0x10` "running" flag) each: look up a per-player name/label buffer (confirmed **0x1120-byte stride**, a second parallel per-player array distinct from the 0x224-byte one), play a directional movement sound, call `FUN_004368f0` with a magnitude (`1`/`-4`/`0xffffffff`) — **this turned out to be a sound/cursor-effect trigger, not velocity application** (its object's vtable calls the same cursor-set function used elsewhere for `normal`/`wnormal` cursors). The actual position delta write wasn't isolated in this branch. |
| `0xc305` | Turn timeout/expiry: resets the turn-phase-related byte, sets a duration constant (`0x11`/`0x10`/`0xb5` depending on a difficulty flag) into a countdown global, shows a "turn's up" style message. |
| `0xc306` | Aim/direction confirm — reads a final ushort field into the turn-timer slot (`+0x429`), clears a per-slot cooldown field. |

**`ProcessBattleAction` now fully read, end to end** (all ~1,290 lines). The
remaining branches:
- `0xc400`: **no handler at all** in this switch — a pure scheduling
  checkpoint with zero payload logic (its only role is being a named point in
  the `0xc300` event chain, presumably for timing/ordering).
- `0xc401`: one-line delegation to `FUN_004cc1e0(this, param)` — not yet
  decompiled, small.
- `0xc409`: **same payload shape as `0x8403` Fire** (2 fields, 2 flags, 2
  fields, 8 shorts) but plays a *different* sound (`sfire` vs `ifire`) and
  resets two flags (`DAT_005f3768=1`, `DAT_005f376c=0`) plus a per-player flag
  — reads as "fire confirmed/committed" following the initial `0x8403`, not a
  new computation.
- `0x8404`: appends an entry to a **third** parallel-array set (`+0x27`/
  `+0xa7`/`+0x127`/`+0x1a7`, stride `0x80`) distinct from `0x8408`'s spawn
  arrays — plausibly a hit/damage event log (4 fields: value, id, byte, byte),
  feeding a UI update (`FUN_004ccbb0`) — a kill-feed/combat-log candidate, not
  physics.
- `0xc40a`: writes two raw ints per-slot from the packet directly — plausibly
  a final-position sync, not a live simulation step.
- `0xc40b`: iterates all 8 player slots doing turn-timeout/notification
  bookkeeping — administrative, not physics.

**No gravity/velocity integration exists anywhere in this function.**

**Followed the thread to the send side instead.** Found and decompiled
`State11_InBattle_HandleFireInput` (`0x45f910`, was `FUN_0045f910`) — the
*local* handler that decides a fire attempt's outcome and sends the resulting
action code. Confirmed: `this+0x243` and `this+0x2cc` are the first two
payload fields sent (matching `ProcessBattleAction`'s Fire field order) —
almost certainly **angle and power**. Critically: **this function also has no
floating-point instructions**, and rather than computing a trajectory, it
**selects between pre-existing outcome codes** (`0x8403`/`0xc400`/`0xc409`)
based on turn-state conditions.

**Ran the systematic `operator_new` sweep** (hypothesis (c) above) to check
for a standalone per-shot projectile object: found and resolved a duplicate
symbol issue (the compiler emitted a thunk at `0x520228` pointing to the real
`operator_new` at `0x52022d`; naive xref search on just one missed most call
sites) and collected all 270 allocation call sites across the binary with
their sizes and calling functions. **Neither `HandleFireInput` nor
`ProcessBattleAction` appears anywhere in that list** — no object is
allocated anywhere in the fire pathway. This rules out hypothesis (c): there
is no standalone projectile/shot class instantiated per-fire.

(Side finding from the sweep: a run of ~40 near-identical ~16 KB allocations
across addresses `0x42bbb0`–`0x4b1810`, confirmed via strings as per-character
weapon effect/bullet sprite-name tables — e.g. `bullet1n`/`bullet1s`,
`bullet1p`..`bullet15p`, `flame%d%d`. This is the character/weapon visual
asset table system, useful context for the render side later, not physics.)

**Also fully decompiled `GameTick`'s unconditional per-tick hook**
(`FUN_004bd8b0`, called every 50 ms regardless of network activity for
Ready Room/Store/In-Battle — the most plausible place for local, tick-driven
physics if it existed). 2,071 lines, zero floating-point instructions. Its
actual logic (not just its strings) is confirmed to be an **8-directional
screen-edge cursor/camera-scroll system**: a bitmask (`bVar13`) built from
comparing the cursor position against edge thresholds selects one of 9 cursor
handles and accumulates a camera-scroll offset. The slot-machine minigame
strings found earlier are a different branch of this same function. No
trajectory code here either.

**Conclusion, now reasonably well-supported rather than speculative**: across
every angle checked — the packet receive handler, the local fire-input
handler, the unconditional per-tick hook, an FPU-density scan of all 2,300+
functions, and a complete `operator_new` audit — **no client-side
gravity/trajectory integration was found, and no standalone shot object is
ever allocated.** The remaining live hypothesis is that **trajectory
resolution is server-authoritative**: the client sends angle/power (and
possibly receives back either resolved final positions or a precomputed
waypoint sequence to animate through, matching the Fire payload's 8 shorts).
Confirming this with certainty would require either the server binary (not
available) or dynamic analysis (attach a debugger to the running client while
firing a shot and watch what actually executes) — both out of reach for
further static analysis of this client binary alone. I'm treating this
physics thread as closed for static analysis purposes unless new evidence
surfaces elsewhere.

## Packet-checksum utility family (broadly recurring)

A cluster of tiny functions, called from nearly every packet handler decompiled
so far, all wrapping the same critical-section-protected state (accessed via
an implicit register "this", not a normal parameter — same custom-calling-
convention pattern as `ChangeGameState`):
- `PeekPacketChecksumState` (`0x40a2e0`) — read current value.
- `AddToPacketChecksum` / `SubFromPacketChecksum` (`0x40aab0`/`0x40aaf0`) —
  read, add/subtract, re-encode.
- `PacketChecksumEquals` / `PacketChecksumNotEquals` (`0x40b270`/`0x40b2a0`) —
  equality checks against the same state (previously mis-characterized in
  earlier notes as generic "flag checks").
- `EncodeChecksumState` / `EncodeChecksumStateXored` (`0x40a4a0`/`0x40a440`) —
  push the current or XOR-mixed value through `EncodeOutgoingPacketField`.

Also named this round: `GetPlayerRecordBySlot` (`0x4206f0`) — a per-slot
player-record accessor called throughout the battle/room code.

## The replay-recording system

**High confidence.** GunBound records matches to a local replay file:

- File handle: a global `FILE*` at `DAT_006a9b68` (not yet given a clean name —
  it's accessed via `&DAT_006a9b68 + DAT_005b3484`, an odd indexing pattern
  worth double-checking), opened somewhere in the Ready Room's entry flow
  (filename format confirmed as `%s%s - %s.sv`, `%Y%m%d %H%M` timestamp style,
  found in state 9's string references).
- Event buffer: `g_replayEventBuffer` (`0xe9aacc`) is a flat byte buffer;
  `g_replayEventCursor` (`0xe9accc`) is the write cursor.
- `Replay_AppendEvent(code)` (`0x4e6c90`, was `FUN_004e6c90`) appends a
  known event-type code (a ushort, values seen: `0x307`, `0x8000`, `0x8100`,
  `0x8101`, `0x8102`, `0x8103`, `0x8200`, `0x8500`) — callers then manually
  append the event's payload bytes to the same buffer before calling...
- `Replay_FlushEvent()` (`0x4e6fc0`, was `FUN_004e6fc0`) — writes the buffered
  event out (presumably to `DAT_006a9b68`) and resets the cursor.
- `Replay_AppendString(str)` (`0x4e6db0`, was `FUN_004e6db0`) — a string
  variant of the same append pattern (used for name fields).
- The file is closed with a small terminator byte (`2`) written first — seen
  at both `State09`'s `0x3432` (session end) and `State11`'s `0x3233` (match
  end back to ready room), i.e. **recording spans from ready-room entry
  through match end**, not just the battle itself.

This is a strong, self-contained subsystem — reconstructing the `.sv` file
format (event-code table + per-event payload layouts) would be a good
standalone follow-up, and is probably the most "shippable" single feature to
fully decompile (a replay parser/viewer) independent of the rest of the game.

## Recurring structure sizes (useful anchors for further work)

- **0x9c (156) bytes** — confirmed per-item inventory entry struct (id fields +
  expiration timestamp + variable blob), array at `DAT_005b3484+0x44be8`.
- **0x224 (548) bytes** — recurring per-player-slot structure size (seen in the
  state-7 object's 8-element array, and in a 20-element accumulation loop in
  `ProcessPacket`). Likely the core per-player game-data struct.
- **0x80 (128) bytes** — per-room-slot player display buffer (name + stats),
  confirmed via opcodes `0x2105`/`0x21f0` in the room-list handler.
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

1. **DONE** — all 16 game states identified and named.
2. **DONE** — `CGameState` base class vtable layout confirmed (dtor, virtual
   `ProcessPacket`, OnEnter, OnExit); three per-state `ProcessPacket` overrides
   found and their opcode spaces mapped (room list, server select, avatar
   store).
3. Slots 2–6 and 9+ in each vtable are still mostly un-named `FUN_*` —
   probably per-state input/update/render virtuals. Same technique (decompile
   + look for distinguishing calls/strings) applies; lower priority than the
   protocol work since screens are already identified via OnEnter.
4. **DONE** — states 9 and 11's `ProcessPacket` overrides found, named, and
   mapped. Discovered the client-side **replay-recording system** as a
   byproduct (`.sv` files, typed event log, `Replay_AppendEvent`/
   `Replay_FlushEvent`).
5. **DONE** — found and mapped the second virtual channel: `CGameState`
   vtable slot 2 (`ProcessBattleAction`), overridden only by Loading, Ready
   Room, and In-Battle (every other state uses the shared no-op) — strong
   confirmation this is a real-time/P2P-adjacent protocol distinct from
   `ProcessPacket`. Found a concrete cross-state data handoff (Loading writes
   turn-timer + setup data directly into the In-Battle object before it's
   even active). Socket-level proof (which recv path feeds slot 1 vs slot 2)
   is still unconfirmed — would need to trace `recv`/`recvfrom` callers
   forward rather than working backward from the vtables. Also still open:
   most of the `0x84xx`/`0xc4xx` action codes beyond `0x8406`/`0x8407`/
   `0x8408`, and the meaning of `+0x10a4`/`+0x2302` on the In-Battle object
   beyond "turn timer" / "8-element setup array."
6. **DONE** — all opcodes across every `ProcessPacket`/`ProcessBattleAction`
   handler mapped; see [PROTOCOL.md](PROTOCOL.md) for the full packet
   reference (this superseded the original opcode-mapping goal here).
7. Five `ChangeGameState` call sites (`0x443350`, `0x443561`, `0x4b9ebe`,
   `0x4e0c68`, `0x4e5421`) are switch/jump fragments *inside* larger functions
   whose auto-analysis was truncated — no standalone prologue nearby. They need
   manual function-boundary repair in the Ghidra GUI. Low priority.
8. Reconstruct concrete structs from confirmed strides: `struct InventoryItem`
   (0x9c/156 bytes: id fields + expiry date + variable blob), `struct
   RoomPlayerSlot` (0x80/128 bytes: name + stats), `struct PlayerGameSlot`
   (0x224/548 bytes, purpose/fields still unknown beyond size and that it's
   per-player). Cross-reference against `itemdata.dat`/`characterdata.dat`
   samples in `orig/` for field-level layout hints.

## Rendering / DirectDraw (first pass)

Started per the user's explicit priority order (networking → state machine →
physics → rendering last). This is a first pass, not exhaustive — rendering
is a large subsystem.

### DirectDraw setup (`InitDirectDraw`, `0x4efaa0`)

Confirmed via call-argument shape (no dedicated DirectX type archive ships
with Ghidra 12.1.2, so exact vtable method names are inferred from argument
patterns, not memorized offsets):

- `LoadLibraryA("ddraw.dll")` + `GetProcAddress("DirectDrawCreateEx")`,
  called directly (not through a typed function pointer) — matches
  `InitDirectDraw`'s already-confirmed dynamic-load pattern from Phase 1.
- A COM call at vtable `+0x50` (likely `SetCooperativeLevel`) then `+0x54`
  (likely `SetDisplayMode`) — branches on a global flag (`DAT_00588f4c`)
  between **fullscreen-exclusive** (hardcoded **800×600**, matching every
  other confirmed viewport reference in this codebase) and **windowed**
  mode (uses `GetClientRect`/`ClientToScreen` to size the surface to the
  actual window instead).
- `CreateSurface`-shaped calls (`+0x18`, taking a `DDSURFACEDESC2`-like
  struct) create a **primary surface** and, in fullscreen mode, a **complex/
  flip back-buffer chain** (`dwBackBufferCount=1`); windowed mode instead
  attaches a clipper (`+0x10` on the surface, `+0x20` on the clipper object,
  `+0x70` — `SetHWnd`-shaped).
- A separate global `DAT_00793604` is acquired late in this function
  (`+0x10` with a callback function pointer, `EnumObjects`-shaped) and reused
  extensively elsewhere (see below) — **identity not conclusively resolved**;
  call shape (callback enumeration, zero-check gating resembling `Poll()`,
  `(code,value)` pairs resembling `SetProperty`) is most consistent with a
  **DirectInput8 device**, but it also appears inside the confirmed render
  function (`State11_InBattle_Render`) interleaved with sprite-drawing code —
  plausibly just input polling calls sprinkled through the render loop to
  keep input responsive, rather than evidence it's a rendering object itself.
  Flagged as open rather than force-fit to a specific interface.

### Texture/asset system

Two distinct, confirmed lookup mechanisms — not one cache, two:

- **`FindPreloadedTextureByName`** (`0x4017d0`, was `FUN_004017d0`): linear
  scan through a **fixed-size, pre-populated table** (case-insensitive
  `stricmp`, 24-byte records), returns null on miss with **no disk-load
  fallback**. This is why the Loading screen exists as a distinct game
  state: **`State10_Loading_PreloadAssets`** (`0x43f0e0`, was `FUN_0043f0e0`,
  12,346 bytes) loads every character/weapon/effect texture (`tank1.img`,
  `bullet1n.img`, `flame11.img`, etc. — hundreds of filenames) into this
  table up front, so **no texture load ever happens mid-battle**.
- **`FindTextureCacheEntryByName`** (`0x4f4650`, was `FUN_004f4650`): a
  string-keyed chain/tree lookup (root at `+0x1b4`, `next` pointer at
  `+0x98`), used by `State11_InBattle_Render` to resolve a sprite-effect name
  to a cache entry, then write computed **sprite-sheet UV coordinates**
  directly into that entry's fields (`+0x80`/`+0x84`/`+0x88`) before drawing.
  Likely a *second*, more general-purpose named-object registry (effects,
  not just textures) distinct from the fixed preload table above.

### Sprite-sheet frame selection

Confirmed pattern, seen dozens of times throughout `State11_InBattle_Render`:
```
entry->u = (frameIndex & mask) * cellSize;
entry->v = (frameIndex >> shift) * cellSize;
```
i.e. treating a loaded texture as a fixed-size grid and computing a sub-rect
by frame index — standard sprite-sheet/tile-atlas animation. Grid sizes seen:
2×N (mask `&1`), 3×3 (`%3`/`/3`), 4×N (`&3`/`>>2`), 8×N (`&7`).

### Turret/sprite rotation

`g_sineTable360` (`0x54c240`, confirmed in the physics investigation) — a
360-entry precomputed sine table indexed by `angle % 360` (cosine via
`(angle+90) % 360`) — is used by rendering to orient sprites (e.g. turret
angle) via the classic 2D rotation formula
`x' = x + sin(a)*A + cos(a)*B`. Its only confirmed caller so far
(`0x4ebbc0`) is called from `State11_InBattle_Render`.

### Open threads for a deeper rendering pass

1. `DAT_00793604`'s true identity (input device vs. something else) —
   resolving this would clarify a lot of interleaved calls across
   `InitDirectDraw`, `GameTick`, and the render function.
2. The actual `Blt`/`Flip` call(s) that present a completed frame haven't
   been isolated yet — this pass found surface *setup* and the sprite/UV
   computation, not the final blit-to-screen call.
3. Only `State11_InBattle_Render` has been read in detail. The other states'
   equivalent render paths (if they have dedicated ones, vs. relying on
   Windows `WM_PAINT`/GDI for simpler static screens like Title/Logo) are
   unexplored.
4. The `+0x98`-chained cache structure behind `FindTextureCacheEntryByName`
   (hash bucket chain vs. simple linked list vs. tree) isn't confirmed.
