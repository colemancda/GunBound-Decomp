# GunBound Client — Reverse-Engineered Architecture Notes

Findings from static analysis in Ghidra (`ghidra_proj/`), confirmed via decompiled
pseudocode, cross-referenced call sites, and data-layout inspection — not guesses.
Confidence is noted per finding. This complements [PROGRESS.csv](PROGRESS.csv)
(the flat function worklist) with structural/behavioral understanding.

## Dependencies

Everything the client links against or vendors internally, gathered from
the import table, the string table ([STRINGS.md](STRINGS.md)'s "Windows
DLLs referenced" section), and decompiled subsystem-init code.

### Windows system DLLs (dynamically linked)

| DLL | Used for | Confirmed via |
|---|---|---|
| `ddraw.dll` | DirectDraw7 **and** Direct3D7 — DirectX 7 packages D3D inside `ddraw.dll`, obtained by `QueryInterface`-ing the DirectDraw7 object for `IID_IDirect3D7` rather than loading a separate D3D DLL | `InitDirectDraw` (`0x4efaa0`): `LoadLibraryA("ddraw.dll")` + `DirectDrawCreateEx`; GUID-decoded `QueryInterface` chain confirmed in the rendering section below |
| `dsound.dll` | DirectSound8 audio | `InitDirectSound` (`0x4ee5b0`): `LoadLibraryA("dsound.dll")` + `DirectSoundCreate8` |
| `dinput8.dll` | DirectInput8 (keyboard/controller input) | `InitDirectInput` (`0x4edc50`): `LoadLibraryA("dinput8.dll")` + `DirectInput8Create` |
| `ws2_32.dll` | Winsock — UDP networking (`recvfrom`/`sendto`), the entire game protocol described in [PROTOCOL.md](PROTOCOL.md) | `WSAStartup` call in `WinMain`, `CCommP2P<>` notify window (`InitCommP2PNotifyWindow`, `0x4fdf00`) |
| `winmm.dll` | Windows multimedia — timing-related, specific API not isolated | Import table only |
| `gdi32.dll` | GDI — window/menu chrome outside the D3D-owned client area | Import table only |
| `user32.dll` | Window management, message loop (`WndProc` at `0x410040`) | `WinMain` |
| `advapi32.dll` | Registry access — display-mode persistence (`Software\Softnyx\GunBound`) and the hardware-fingerprint/anti-cheat registry reads found while investigating the replay `fopen` call site | `ReadRegistryDword`/`WriteRegistryDword`/`GetDisplayConfigFromRegistry` (`0x40c470`/`0x40c550`/`0x40c620`); registry-scanning functions at `0x5207d0`/`0x523530`/`0x524bb0` |
| `imm32.dll` | IME (Input Method Editor) — Korean text input in chat | Import table only |
| `shell32.dll` | Shell utility calls | Import table only, specific calls not isolated |
| `ole32.dll` / `oleaut32.dll` | COM infrastructure underlying the DirectX7 COM interfaces (`IDirectDraw7`, `IDirect3D7`, `IDirect3DDevice7`, etc.) | Import table, consistent with the confirmed COM vtable chain in the rendering section |
| `kernel32.dll` / `ntdll.dll` | Core Win32/NT — process/thread management, critical sections, file I/O (`CreateFileA`, `fopen` chain) | Throughout; e.g. `__tsopen_lk`/`__openfile`/`__fsopen` CRT chain traced during the replay-file investigation |
| `mscoree.dll` | .NET CLR | **Not used by `GunBound.gme`** — this dependency belongs to the separate **`GunBound.exe` launcher stub** (a small .NET assembly, source `GunBound.cs`) that decrypts/injects and starts the real native game; it is not linked into the decompilation target itself |

No other DLLs (no `d3d8.dll`/`d3d9.dll`, no `xinput`, no third-party
middleware DLLs) were found in the import table or string table.

### Vendored/embedded open-source code

Unlike the DLLs above (dynamically linked at runtime), this is code **compiled
directly into `GunBound.gme`** — no separate library file, just functions
living in `.text` alongside the game's own code.

- **LZHUF (`LZHUF.C`)** — a public-domain LZSS+adaptive-Huffman compression
  codec written by Haruhiko Okumura and Haruyasu Yoshizaki (released ~1988,
  the same lineage used by LHA `.lzh` archives), copied wholesale into the
  engine to compress `.xfs` archives (both the table of contents and
  individual entries) and `.dat` game-data files — see
  [FILEFORMATS.md](FILEFORMATS.md) for the full algorithm confirmation.
  Identified via an exact constants/structure match rather than just a
  family resemblance: `InitLZHUFTree` (`0x4ea300`) initializes `N_CHAR=314`
  symbols and a `T=627`-node tree (`2*N_CHAR-1`, the reference formula), and
  `DecodeLZHUFBlock`/`FUN_004ea670`/`FUN_004ea6e0` (`0x4eaba0`/`0x4ea670`/
  `0x4ea6e0`) are structurally identical to the reference source's
  `Decode`/`DecodeChar`/`DecodePosition` functions, right down to the
  4096-byte sliding window and space-initialized ring buffer. Being
  public-domain, its inclusion here carries no licensing complication for
  this decompilation project — only the surrounding game-specific code
  calling it is proprietary.
- No other vendored open-source code (no zlib, no libpng, no Boost, no
  scripting-language runtime) has been found anywhere in the binary.

### Compiler/runtime

Statically-linked **Visual C++ 2003 (linker version 7.10)** CRT — confirmed
by the full set of `R6002`-`R6029` runtime-error strings, `TLOSS`/`SING`/
`DOMAIN` math-error messages, and the CRT internals traced during the
replay-file investigation (`__fsopen`→`__openfile`→`__sopen`→`__tsopen_lk`,
the fopen implementation at `FUN_00525fac`). See
[STRINGS.md](STRINGS.md#systemcrt-boilerplate-summarized-not-itemized) for
the full boilerplate-string inventory.

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

### `RoomPlayerSlot` — confirmed structure (opcode `0x2105`)

Decompiled the `0x2105` handler in full to nail this down. The per-slot
data is **not one contiguous struct** — it's split across a name buffer
plus several separate parallel arrays, all indexed by the same slot index
(`this+0x124`, set by a prior packet):

| Storage | Stride | Base offset | Contents |
|---|---|---|---|
| Name buffer | 0x80 bytes/slot | `DAT_005b3484 + 0x4467c` | Variable-length name copied from the packet (length given by a length-prefix byte), NUL-terminated. Also mirrored into `this+300` for the "currently viewed" slot. |
| Ready/ID byte | 1 byte/slot | `+0x4497c` | Single byte (also mirrored to `this+0x1ac`) |
| A 4-byte value | 4 bytes/slot | `+0x44984` | Mirrored to `this+0x1b0` |
| Byte flag | 1 byte/slot | `+0x4499c` | Mirrored to `this+0x1b4` — **also doubles as the equipped-item count** (see below) |
| Byte flag | 1 byte/slot | `+0x449a2` | Mirrored to `this+0x1b5` |
| Byte flag | 1 byte/slot | `+0x449a8` | Mirrored to `this+0x1b6` |
| Byte flag | 1 byte/slot | `+0x449ae` | Mirrored to `this+0x1b7` |

Immediately following these 9 bytes in the packet is a **variable-length
equipped-item list**, present only when the `+0x1b4`/`+0x4499c` byte
(reused as a count) is non-zero. Each item entry is **32 bytes** in the
wire format, decomposed on receipt into two separate destination arrays
(13-byte stride and 9-byte stride respectively — i.e. this is a "struct of
arrays" layout matching the top-level slot fields, not a flat per-item
struct). Per entry, the code reads: two NUL-terminated string-like fields
(up to ~4 raw bytes each, likely short item/mobile codes), a masked
24-or-32-bit bitfield (`& 0xffffff` applied conditionally based on its top
bits — possibly a signed/special-value sentinel check), and two more raw
4-byte values. The exact field-level meaning of each of these 8 dwords
wasn't decoded further in this pass (would need cross-referencing against
`itemdata.dat`'s record layout, once that's independently reconstructed),
but the container shape (32 bytes/entry, count-prefixed, split into two
parallel destination arrays) is confirmed directly from the decompiled
loop.

This resolves the earlier vaguer note ("0x80-byte display buffer, name +
a handful of stat bytes") — the `0x80`-byte buffer is actually **just the
name**, with all other per-slot state living in separate same-indexed
arrays rather than one packed struct.

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
| `0x6002` | Parses a list of **owned-item entries**: each has a timestamp (parsed via `_localtime` → day/month/year, i.e. an **expiration date**), item-id fields, and a variable-length blob, stored into a per-item array at `+0x44be8` with a **confirmed 0x9c (156)-byte stride**. This is the **inventory/purchased-items list**. Full struct layout confirmed by mapping the decompiled stack-local offsets — see below. |
| `0x6017` (`*payload==0`) | Builds a **purchase confirmation dialog**: loads localized strings by resource ID (`FUN_0043dc70(&DAT_00796eec, 0xea6a..0xea6d)`), formats item name/price via `sprintf`, shows the `b_storewindow_confirm` popup image. |
| `0x6017` (`*payload==0x6003`) | Sends a `0x6000` reply packet — likely the purchase confirmation's "yes" response. |
| `0x6037` (`*payload==0`) | Guards on a slot-count check (`FUN_004010c0(0x80070057)` fatal-errors if out of range) then calls `FUN_0044c370()` — a purchase-commit path, not fully traced. |

### `InventoryItem` — confirmed structure (opcode `0x6002`, resolves the size-only note in ARCHITECTURE.md's earlier struct list)

The wire format (per item, read sequentially from the packet payload) and
the in-memory destination struct (0x9c/156 bytes, array at
`DAT_005b3484+0x44be8`) were both traced from the decompiled `0x6002`
handler. The destination offsets were recovered by mapping each
decompiler-assigned stack-local's address back to its position relative to
the local array's base (e.g. `local_4f0` sits `0x508-0x4f0 = 0x18 = 24`
bytes into the destination struct, since the struct's base local is
`local_508`):

| Dest offset | Size | Field | Wire source |
|---|---|---|---|
| `0x00` | 4 | id field 0 | `payload[0..3]` — also fed to `EncodeOutgoingPacketField` (part of the outgoing-packet checksum) and tracked as a running min/max (`this+0x32f98`/`this+0x32f94`) — likely an item ID or price |
| `0x04` | 4 | id field 1 | `payload[4..7]` |
| `0x08` | 4 | id field 2 | `payload[8..11]` |
| `0x0C` | 4 | id field 3 | `payload[12..15]` |
| `0x10`-`0x11` | 2 | unaccounted (likely padding — the raw `time_t` used to derive the date fields below isn't itself stored, only its parsed components) | `payload[16..19]` is the wire `time_t` (4 bytes), consumed by `_localtime()` but not copied into the struct directly |
| `0x12`-`0x13` | 2 | expiration year (`tm_year + 1900`) | derived from the same wire `time_t` above |
| `0x14` | 1 | expiration month (`tm_mon + 1`) | derived |
| `0x15` | 1 | expiration day (`tm_mday`) | derived |
| `0x16`-`0x17` | 2 | unaccounted (padding) | — |
| `0x18` | 4 | id field 4 | `payload[20..23]` — also fed to `EncodeOutgoingPacketField` alongside id field 0, suggesting these two together form some kind of transaction/verification pair |
| `0x1C` onward | up to ~124 bytes | variable-length blob | length-prefixed: a single byte at wire offset 24 gives the blob length, blob bytes follow at wire offset 25 onward, copied into the struct starting at `0x1C` |

The variable blob's internal field-level meaning (item name string? serialized
equip-slot/color data?) wasn't decoded further in this pass — only its
existence, length-prefix mechanism, and destination offset are confirmed.

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
| `0x3020` | **Player disconnected mid-match**: shift-compacts three of the four small per-slot spawn arrays (see action `0x8408`'s row below — **not** a `0x224`-byte stride, corrected from an earlier pass), separately reads that player's **packet-checksum state** from a per-player array at `playerId*0x224 + 0xebef4` (confirmed via `PeekPacketChecksumState`, see the packet-checksum utility section below), records replay event `0x307` with the departed player's stats, and — if the departed player held the active turn — reassigns it (`FUN_00413bf0`, likely `AdvanceTurn`). Full writeup in [PROTOCOL.md](PROTOCOL.md). |
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
| `0x8408` | **Player spawn into battle**: appends a new entry across four parallel per-slot `uint` arrays at `+0x228`/`+0x2a8`/`+0x328`/`+0x3a8`, indexed by a shared active-slot counter (`+0x227`). Confirmed sources: `+0x228` = current packet parse cursor value (position-dependent, no fixed payload offset), `+0x2a8` = fixed payload offset `0x23` (ushort), `+0x3a8` = fixed payload offset `0x25` (full 32-bit value), `+0x328` = the team/slot byte read once at the start of `ProcessBattleAction` (`payload+5`). Calls `FUN_004ccc60` (spawn visual?), increments the player count. Opcode `0x3020`'s disconnect handler shifts down three of these four arrays (`+0x228`/`+0x2a8`/`+0x328` — notably *not* `+0x3a8`) — confirms a structure-of-arrays layout for the active battle slots, distinct from the unrelated, genuinely `0x224`-byte, player-ID-indexed array also touched by `0x3020` (see that row above). |
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

**Per-player instances confirmed.** Most call sites use the implicit/default
state, but `PeekPacketChecksumState` is also called with an **explicit
pointer argument** at several sites — a whole-binary scan for every
instruction referencing the constant `0xebef4` (34 hits across ~15
functions, including `0x3020`'s disconnect handler and
`State11_InBattle_ProcessBattleAction`) found a consistent pattern:
`playerId * 0x224 + 0xebef4` computes a pointer into an **array of
per-player packet-checksum-state objects** (0x224/548 bytes each),
passed directly into `PeekPacketChecksumState` (sometimes via the thin
wrapper `FUN_0040a4d0`, which is just `EnterCriticalSection` +
`PeekPacketChecksumState` + `LeaveCriticalSection`). This resolves what
several earlier passes had flagged as an unidentified `0x224`-byte
"`PlayerGameSlot`" struct spawned by action `0x8408` — that was a
conflation; `0x8408` never touches this array at all (it populates four
separate small `uint` arrays instead, see [PROTOCOL.md](PROTOCOL.md)'s
action `0x8408` writeup). Whether the *other* `0x224`-byte sightings
elsewhere (the room-list's 20-element loop, the Avatar Store's 8-element
array) are this same checksum-state struct, or an unrelated struct that
happens to share the size, is still unresolved.

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

- **0x9c (156) bytes** — **fully confirmed** `InventoryItem` struct (4 id
  fields, expiration date parsed from a wire timestamp, a variable-length
  trailing blob), array at `DAT_005b3484+0x44be8` — full field-offset
  layout now documented in the Avatar Store section above.
- **0x224 (548) bytes** — **confirmed to be (at least) two unrelated things
  that happen to share a size.** (1) An array of per-player
  **packet-checksum-state** objects at `+0xebef4` (see the packet-checksum
  utility section above) — not a gameplay struct. (2) The state-7 Avatar
  Store's 8-element array uses a *different*, much more minimal
  constructor/destructor pair (`FUN_0040a280`/`FUN_0040a2a0`, size 24/53
  bytes) — decompiled this pass: the constructor just zeroes a byte at
  `+0x220` and a dword at `+0x14`, then calls `EncodeOutgoingPacketField(0)`;
  the destructor conditionally frees whatever the `+0x14` field points to.
  This is a **generic lightweight container** (an optional owned pointer +
  an active/flag byte + checksum-encoding participation), not obviously
  gameplay-specific — likely a reusable engine primitive for "a slot that
  may or may not own a heap sub-object," used here for per-avatar-slot data
  but probably reused elsewhere too (this exact ctor/dtor pair, with the
  same `0x224` stride, also appears in `FUN_00415d40`'s huge object-init
  function from earlier session work). (3) The room-list's 20-element
  loop **doesn't cleanly match either identity** — checked this pass: its
  loop counter increments by `0x224` up to `0x2ad0` (confirming 20
  iterations, `20*0x224 = 0x2ad0`), but the actual per-element field
  reads/writes inside the loop use a completely different stride
  (`index*0x14`, i.e. a 20-multiplier, not `0x224`), and repeatedly call
  `PeekPacketChecksumState` on a **fixed, non-array-indexed** address
  rather than walking anything at `counter`'s stride. This reads like
  `iVar24`'s `0x224` increment is tracking consumption of a conceptual
  20-record-of-0x224-bytes-each *wire/source* buffer (similar to the
  wire-vs-destination split already confirmed for `InventoryItem` and
  `RoomPlayerSlot`'s equipped-item list) rather than indexing a real
  in-memory `0x224`-byte struct array here. Inconclusive — not resolved
  either way this pass.
- **0x80 (128) bytes** — per-room-slot player **name buffer only** (not a
  combined name+stats struct as originally thought — the other per-slot
  fields live in separate same-indexed parallel arrays), confirmed via
  opcode `0x2105` in the room-list handler — see the dedicated
  `RoomPlayerSlot` section above.
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
5. **DONE, and further advanced this pass** — found and mapped the second
   virtual channel: `CGameState` vtable slot 2 (`ProcessBattleAction`),
   overridden only by Loading, Ready Room, and In-Battle (every other state
   uses the shared no-op) — strong confirmation this is a real-time/
   P2P-adjacent protocol distinct from `ProcessPacket`. Found a concrete
   cross-state data handoff (Loading writes turn-timer + setup data
   directly into the In-Battle object before it's even active). Socket-level
   proof (which recv path feeds slot 1 vs slot 2) is still unconfirmed —
   would need to trace `recv`/`recvfrom` callers forward rather than working
   backward from the vtables. Two more action codes decompiled and
   documented this pass: `0x8104` (shows the end-of-match "confirm result"
   button) and `0x8500` (a player-position/status relay, also independently
   confirmed as a replay-event code logged elsewhere — see
   [PROTOCOL.md](PROTOCOL.md)). Almost all `0x84xx`/`0xc3xx`/`0xc4xx` action
   codes are now documented; a handful of smaller gaps remain (`0xc302`,
   `0xc307`, `0xc309`, and most of `0xc402`-`0xc408`), plus the meaning of
   `+0x10a4`/`+0x2302` on the In-Battle object beyond "turn timer" /
   "8-element setup array."
6. **DONE** — all opcodes across every `ProcessPacket`/`ProcessBattleAction`
   handler mapped; see [PROTOCOL.md](PROTOCOL.md) for the full packet
   reference (this superseded the original opcode-mapping goal here).
7. Five `ChangeGameState` call sites (`0x443350`, `0x443561`, `0x4b9ebe`,
   `0x4e0c68`, `0x4e5421`) are switch/jump fragments *inside* larger functions
   whose auto-analysis was truncated — no standalone prologue nearby. They need
   manual function-boundary repair in the Ghidra GUI. Low priority.
8. Reconstruct concrete structs from confirmed strides. **`RoomPlayerSlot`
   and `InventoryItem` both resolved this pass** — see the dedicated
   sections above. `RoomPlayerSlot` turned out to be a "struct of arrays"
   rather than one packed struct (a 0x80-byte name buffer plus several
   separate same-indexed parallel arrays for stats, plus a count-prefixed
   variable-length equipped-item list); `InventoryItem` is a genuine packed
   0x9c/156-byte struct with a fully-mapped field layout (4 id fields,
   expiration date, variable blob), though the blob's internal contents and
   two of the "unaccounted" 2-byte gaps remain unresolved. **`PlayerGameSlot`
   turned out not to exist as originally framed**: traced actions
   `0x8408`/`0x3020` in full and found the active-battle-slot data is a
   struct-of-arrays (four small 4-byte-per-slot `uint` arrays, not one
   `0x224`-byte struct), and the `0x224`-byte, player-ID-indexed array at
   `+0xebef4` that a previous pass suspected was `PlayerGameSlot` is
   actually an array of **per-player packet-checksum-state** objects
   (confirmed via `PeekPacketChecksumState`, see the packet-checksum
   utility section above) — not gameplay data at all. What remains
   genuinely open: whether a *real* per-player gameplay struct (position,
   HP, weapon, etc.) exists as a single packed struct anywhere, or whether
   GunBound's engine simply always uses this struct-of-arrays style
   (consistent with what was found for both `RoomPlayerSlot` and the
   battle-spawn arrays). Followed up further this pass: the state-7
   8-element array turned out to be a **third, distinct** `0x224`-sized
   thing — a generic minimal container (owned-pointer-plus-flag, ctor/dtor
   `FUN_0040a280`/`FUN_0040a2a0`), not obviously gameplay data either, and
   reused elsewhere in the engine (same ctor/dtor pair, same stride, seen in
   `FUN_00415d40`'s object-init too) — see the recurring-structures list
   above. The room-list's 20-element loop is **inconclusive**: its `0x224`
   loop-counter increment doesn't match either the checksum-state or the
   generic-container identity, and looks more like it's tracking a wire/
   source buffer's conceptual size than indexing a real struct array (see
   the dedicated note above). Net result after three rounds of digging:
   **no confirmed single packed "PlayerGameSlot" struct exists** — every
   `0x224`-sized thing found so far turned out to be something else
   (checksum state, a generic container, or an unresolved wire-format
   accumulator). This thread is likely exhausted for static analysis
   without a fresh, more targeted lead. Cross-referencing against
   `itemdata.dat`/`characterdata.dat` samples in `orig/` remains blocked on
   the LZHUF decoder bug (see [FILEFORMATS.md](FILEFORMATS.md)).

## Rendering — Direct3D 7 + software hybrid

**Key finding: GunBound is not a plain DirectDraw blitter — it's a hybrid
Direct3D 7 hardware renderer with a software (Lock/write) rasterizer layer.**
This corrects the earlier "DirectDraw Blt" assumption.

### The COM object chain (confirmed via GUID, not just call shape)

`InitDirectDraw` (`0x4efaa0`) builds this chain — vtable method identities
below are now **confirmed**, not inferred, because the `QueryInterface` GUID
argument at `0x5573e8` decodes to
`{F5049E77-4861-11D2-A407-00A0C90629A8}` = **`IID_IDirect3D7`**, which
anchors the whole interface identification:

| Global (renamed) | Interface | Created by |
|---|---|---|
| `g_hDDrawDll` (`0x79363c`) | `HMODULE` for `ddraw.dll` | `LoadLibraryA` |
| `g_pDirectDraw7` (`0x7935f0`) | `IDirectDraw7` | `GetProcAddress("DirectDrawCreateEx")` |
| `g_pDirect3D7` (`0x793600`) | `IDirect3D7` | `g_pDirectDraw7->QueryInterface(IID_IDirect3D7)` |
| `g_pPrimarySurface` (`0x7935f4`) | `IDirectDrawSurface7` (primary, + flip chain in fullscreen) | `CreateSurface` |
| `g_pBackBufferSurface` (`0x7935f8`) | `IDirectDrawSurface7` (back buffer / D3D render target) | `GetAttachedSurface` off the primary |
| `g_pD3DDevice7` (`0x793604`) | `IDirect3DDevice7` | `g_pDirect3D7->CreateDevice(guid, backBuffer, &device)` |
| `g_pClipper` (`0x6790b8`) | `IDirectDrawClipper` | `CreateClipper` (windowed present) |

`ShutdownDirectDraw` (`0x4eff90`, was `FUN_004eff90`) `Release`s all six COM
objects (vtable `+8`) then `FreeLibrary(g_hDDrawDll)` — this teardown function
is what let the whole chain be identified together.

The device's `IDirect3DDevice7` vtable is used throughout with textbook
offsets (all now confirmed against the standard vtable): `+0x10`
EnumTextureFormats (the callback `EnumTextureFormatsCallback`/`0x4ef8e0` that
was *wrongly* guessed as DirectInput last pass), `+0x14` BeginScene, `+0x18`
EndScene, `+0x20` SetRenderTarget, `+0x28` Clear (called as
`Clear(0,0,TARGET|ZBUFFER, color, z=1.0f, 0)`), `+0x34` SetViewport, `+0x50`
SetRenderState, `+0x64` DrawPrimitive, `+0x8c` SetTexture, `+0x94`
SetTextureStageState. `InitDirectDraw`'s tail sets up **alpha blending**:
`SetRenderState(SRCBLEND=SRCALPHA)`, `SetRenderState(DESTBLEND=INVSRCALPHA)`,
`SetRenderState(ALPHABLENDENABLE=1)` — i.e. sprites are drawn as alpha-blended
textured quads on the GPU.

Fullscreen vs. windowed still branches on `DAT_00588f4c` (fullscreen =
hardcoded 800×600 exclusive; windowed = `GetClientRect`/`ClientToScreen`).

### Frame presentation (`PresentFrame`, `0x4f0070`)

Called once at the end of every `GameTick`. Confirmed:
`g_pPrimarySurface->SetClipper(g_pClipper)` then
`g_pPrimarySurface->Blt(&destRect, g_pBackBufferSurface, NULL, DDBLT_WAIT, NULL)`
— a **clipped Blt of the back buffer onto the primary** (windowed-mode
present). On `DDERR_SURFACELOST` (`0x887601C2`, matched exactly in the code)
it `Restore`s all three surfaces and re-`SetRenderTarget`s the device.

### The software rasterizer layer (hybrid rendering)

Alongside the D3D device, the game **locks the back buffer and writes pixels
directly** for a large class of content:

- **`LockBackBuffer`** (`0x4f02c0`, was `FUN_004f02c0`):
  `g_pBackBufferSurface->Lock(NULL, &ddsd, 0, 0)`, returns the surface
  **pitch** and **pixel pointer**. Paired with an `Unlock` (surface `+0x80`)
  at the end of each render layer in `GameTick`.
- **`BlitRLESprite`** (`0x4eb450`, was `FUN_004eb450`): decodes a **run-length
  encoded** sprite byte-stream (high bit of each control byte = run vs.
  literal) into the locked buffer. This confirms the on-disk `.img` sprite
  format is **RLE-compressed**.
- **`BlitSprite16bpp`** (`0x4ed6a0`, was `FUN_004ed6a0`): operates on
  `unsigned short*` pixels → the surfaces are **16-bit color** (555/565).
- **`BlitSpriteClipped`** (`0x4eb9c0`, was `FUN_004eb9c0`): clips against the
  active clip rect (`DAT_00793534`/`DAT_0056df34`) before blitting.

So the pipeline per frame is roughly: `Clear` (D3D) → Lock back buffer →
software-blit map/terrain/UI sprites (RLE, 16bpp) → Unlock → `BeginScene` /
draw hardware sprite quads / `EndScene` (D3D) → `PresentFrame` (Blt to
primary). The `GameTick` present loop runs at a fixed ~50 ms cadence with a
`Sleep`-based frame cap.

### Texture/asset system

Two distinct, confirmed lookup mechanisms:

- **`FindPreloadedTextureByName`** (`0x4017d0`): linear scan through a
  **fixed-size, pre-populated table** (case-insensitive `stricmp`, 24-byte
  records), returns null on miss with **no disk-load fallback**. This is why
  the Loading screen is its own game state: **`State10_Loading_PreloadAssets`**
  (`0x43f0e0`, 12,346 bytes) loads every character/weapon/effect texture
  (`tank1.img`, `bullet1n.img`, `flame11.img`, … hundreds of filenames) into
  this table up front, so **no texture load happens mid-battle**.
- **`FindTextureCacheEntryByName`** (`0x4f4650`): a string-keyed chain lookup
  (root at `+0x1b4`, `next` at `+0x98`), used by `State11_InBattle_Render` to
  resolve a sprite-effect name to a cache entry, then write computed sprite-
  sheet UV coordinates into it (`+0x80`/`+0x84`/`+0x88`) before drawing.

### Sprite-sheet frame selection

Seen dozens of times in `State11_InBattle_Render`:
```
entry->u = (frameIndex & mask) * cellSize;
entry->v = (frameIndex >> shift) * cellSize;
```
Standard sprite-sheet/atlas animation — sub-rect from a frame index. Grid
sizes seen: 2×N (`&1`), 3×3 (`%3`/`/3`), 4×N (`&3`/`>>2`), 8×N (`&7`).

### Turret/sprite rotation → hardware vertex pipeline (now connected end to end)

`g_sineTable360` (`0x54c240`) — 360-entry precomputed sine table indexed by
`angle % 360` (cosine via `(angle+90) % 360`) — feeds **`BuildRotatedSpriteQuad`**
(`0x4ebbc0`, was `FUN_004ebbc0`), which computes a rotated sprite's 4 corner
positions via `x' = x + sin(a)*A + cos(a)*B` and writes a **27-dword (108-byte)
"vertex work record"** — 4 rotated corners plus color/alpha fields — into
**`g_spriteVertexBuffer`** (`0x6ba190`) at index **`g_spriteVertexCount`**
(`0x793658`, an incrementing per-frame sprite counter, stride `0x1b` dwords).

This buffer is exactly what `IDirect3DDevice7::DrawPrimitive` consumes later
in the same frame:
```
DrawPrimitive(device, D3DPT_TRIANGLELIST /*4*/, FVF=0x244,
              &g_spriteVertexBuffer[...], vertexCount, flags)
```
confirmed via raw disassembly of the call site (the decompiler couldn't
recover these arguments — Ghidra showed empty parens — so this required
reading x86 `PUSH`/`CALL` sequences directly). This closes the loop: rotation
math → vertex buffer → GPU draw call, all inside `State11_InBattle_Render`.
The `g_spriteVertexBuffer` entry's internal field layout (which floats map to
which FVF component) isn't broken down byte-by-byte, but the pipeline shape
is now solid.

### `DAT_007935fc` — resolved: the Z-buffer

Traced its creation in `SetupZBuffer` (`0x4ef9a0`, was `FUN_004ef9a0`):
`IDirect3D7::EnumZBufferFormats` finds a supported depth format, then
`IDirectDraw7::CreateSurface` builds `g_pZBufferSurface`, which gets
`AddAttachedSurface`'d onto the back buffer and the device's render target is
re-set. A Z-buffer for what's fundamentally 2D sprite rendering — plausibly
just a HAL-device requirement of this D3D7 code path, or used for
depth-sorted overlapping sprites (not confirmed which).

### Hardware rendering is In-Battle-only — resolved

Checked every function in the binary that touches `g_pD3DDevice7` (17 total).
Fifteen are core D3D infrastructure (init/shutdown/present/z-buffer — all
already documented above). Of the remaining two, **both are In-Battle
content**: `State11_InBattle_Render` (the main render function) and
**`State11_InBattle_RenderModeIcons`** (`0x4caed0`, was `FUN_004caed0`,
944 bytes — draws special-mode indicator icons, confirmed via `TagTexture`/
`YesooriTexture` strings, i.e. Tag-mode and Yesoori-mode battle indicators).

**Conclusion: the Direct3D 7 hardware pipeline (rotated textured quads,
alpha blending, the vertex buffer) is used exclusively during In-Battle
rendering.** Every other screen — Title, Server Select, Room List, Avatar
Store, Ready Room, Loading, both Logo screens — renders entirely through the
**software blitter** (`LockBackBuffer`/`BlitRLESprite`/`BlitSprite16bpp`/
`BlitSpriteClipped`/`Unlock`), never touching the D3D device. This makes
sense architecturally: menus/lobbies are static-positioned 2D UI with no
rotation needs, while battle requires rotated, alpha-blended, numerous
dynamic sprites (tanks, projectiles, explosion effects) where GPU
acceleration earns its keep. This closes the "other states' render paths"
open thread — there isn't a separate hardware path to find for them.

### Software-blitter callers: non-battle states do have real render content

Checked who calls the four software blit primitives (`BlitRLESprite`,
`BlitSprite16bpp`, `BlitSpriteClipped`, ~29-30 callers each). Two confirmed,
concrete results:

- **`LockBackBuffer` is called only from `GameTick`** — the buffer lock is
  centralized; individual draw functions receive/operate on the already-
  locked pixel buffer rather than locking it themselves.
- **`State03_GameRoomList_RenderRoomLabel`** (`0x429810`, was `FUN_00429810`)
  — confirmed via vtable-offset arithmetic (`0x5536ac` − `0x553670` = `0x3c`
  = slot 15 on State 3's vtable) — draws room name/player-count labels using
  the **same `%s[%3d/%3d]` bitmap-font text format** as the In-Battle
  scoreboard (`State11...`'s slot-15 function, `0x408180`'s caller). This
  confirms non-battle screens **do** render real per-state content through
  the software path, using shared text-rendering infrastructure — they
  aren't merely static.

However, checking the same vtable slot across other states (State 2's slot
15 is a distinct 62-byte function with no identifying strings; State 7's is
the shared no-op) confirms — consistent with the earlier finding for slot 9
— that **these vtable slots are generic per-state hooks with no fixed
semantic**; "slot 15 = UI label" is true for State 3 specifically, not a
universal rendering slot. Mapping each state's actual render entry point
would mean checking each vtable slot individually per state rather than
assuming a shared slot index — noted as future work, not completed here.

### Per-state vtable slot survey — Ready Room and Loading

Dumped every vtable slot for the remaining states and created/checked the
previously-unexamined ones. Findings:

- **Title, Logo1, ServerSelect share the identical slot-15 function**
  (`0x443570`) — confirms it's a lightweight shared utility, not a
  state-specific render override (Logo2 differs slightly, `0x443360`).
  Reinforces the earlier finding that vtable slots have no fixed meaning
  across states.
- **`State09_ReadyRoom_RenderCharacterPreview`** (`0x4d90c0`, was
  `FUN_004d90c0`, 2,575 bytes) — loads `AvataTexture1/2`,
  `CharacterTexture1/2`, `AvataEffectTexture1/2`, `CharEffectTexture1/2` —
  the exact same texture families used by In-Battle rendering, confirming
  the Ready Room draws a live character/avatar preview before battle starts.
- **`State09_ReadyRoom_HandleChatInput`** (`0x4d6210`, was `FUN_004d6210`)
  and its Loading-screen counterpart **`State10_Loading_HandleChatInput`**
  (`0x43e720`, was `FUN_0043e720`) — confirmed as **Win32 message handlers**
  (dispatch on `param_2==0x100`=`WM_KEYDOWN`, checking `param_3==0xd`=Enter),
  not render functions. On Enter, reads the chat textbox, and if the text
  isn't a recognized command, **logs it to the replay stream**
  (`Replay_AppendEvent(1)` + `Replay_AppendString`) — confirms replays
  capture chat messages, not just game actions.
  - **Notable side-find**: both functions embed a list of hardcoded
    developer names/handles (`comsik` — "Game Programmer - comsik",
    `CozY` — "Oh~! It's CozY here ^-^*", plus `yesoori`, `oorusa`, `jaeyong`,
    `yaong2`, `jchlee75`, `reddragon`) alongside real chat commands (`guide`,
    `message`, `mutelist`, `loudall`, `enddream`). Reads like a **developer
    easter egg** (typing a dev's name/handle as a chat command likely
    triggers a special response) — not traced in detail, flagged as a fun
    curiosity rather than pursued further.
- Ready Room's remaining slots: a small (20-byte) ready-status check
  (`0x4d54c0`), a larger (3,167-byte) button enable/disable UI updater
  (`0x4d54e0`), and a texture-preload list identical to Loading's
  (`0x4d7b20`) — consistent with Ready Room needing the same battle assets
  available for its character preview.

### Slot 9 ("generic tick hook") is often just timer logic, not render

Ruled out one hypothesis and confirmed another. `WndProc` (`0x410040`) has
**no `WM_PAINT` handling at all** — the DirectDraw/D3D pipeline owns 100% of
presentation, so simple screens are *not* drawn via Windows' native paint
mechanism. But decompiling `State01_Title`'s slot-9 function (`0x4e5400`)
in full shows it's genuinely just a **frame counter**: increments a field
each tick, and at count `0x3c` (60 ticks ≈ 3 seconds at the confirmed 50 ms
tick rate) auto-transitions `ChangeGameState(2)` (Server Select). No drawing
at all. `State01_Title_OnEnter` likewise contains no blit calls — just audio
setup (starts title music via `FUN_004f1790(&DAT_00ea0e18, 10000)`).

### The generic UI-widget system — found and confirmed

Traced the `b_gamelist_buddyup`-style button-name strings back to their
actual reference: not a data table, but a genuine (if decompiler-obscured)
instruction — `MOV EAX, <string address>` immediately followed by a `CALL`,
inside `ChangeGameState` itself. Ghidra's decompiler failed to surface this
particular call's string argument (the value is passed via `EAX`, a register
the decompiler didn't associate with the callee's parameter list — the same
class of issue seen elsewhere in this codebase with custom/register-based
calling conventions), which is why a full prior decompile of `ChangeGameState`
never showed it. Reading the raw x86 disassembly directly resolved it.

**Confirmed architecture, three layers**:

1. **`AppendPersistentButtonName`** (`0x401740`, was `FUN_00401740`) appends
   a button name string into a growable, count-prefixed array (128-byte/
   `0x20`-dword records) at `&DAT_0067ec70 + <session offset>`. `ChangeGameState`
   calls this **9 times in a row on every single state transition**,
   registering a fixed set of persistent button names — the buddy-list
   scroll controls (`b_gamelist_buddyup/down`, `b_buddy_up/down/exit`) and a
   generic error-confirm button (`b_error_confirm`) — confirming these are
   **global, persistent UI elements available across virtually every
   screen**, not per-screen widgets. This same array (`DAT_0067ec70`) is also
   populated by nearly every individual state's own `OnEnter`/`OnExit`
   (547 total cross-references found), plus every per-character weapon-effect
   constructor function found during the earlier rendering pass — it's a
   single, shared, session-wide registry, not one array per screen.
2. **`LoadButtonDefinitionFromXFS`** (`0x401440`, was `FUN_00401440`) is
   called for each registered name and loads that button's actual definition
   from **a named entry inside `graphics.xfs`** (via `FindXFSEntry`/
   `ReadXFSEntryByte` — the exact same archive-reading primitives documented
   in [FILEFORMATS.md](FILEFORMATS.md)), parsing a small binary structure:
   a count, then that many sub-records each with a length-prefixed name
   string followed by several more fields and two dynamically-sized arrays
   — a genuine, distinct **widget-definition micro-format** living inside
   the XFS archive, parsed byte-by-byte like `ChooseEvent.txt` but binary
   rather than text. Not decoded field-by-field in this pass.
3. **`CreateButtonWidget`** (`0x406020`, was `FUN_00406020`) is the actual
   per-button object constructor — allocates an 80-byte heap object with a
   **shared vtable** (`vtable_ButtonWidget`, `0x551e44`), storing position/
   size, resolving its texture via `FindPreloadedTextureByName`, and setting
   an initial visual state (`"disable"`/`"active"`/`"ready"` — the same
   state-name strings recurring throughout the whole codebase). Confirmed
   called from nearly every state's `OnEnter` (Server Select, Room List,
   Avatar Store, Ready Room, Loading — Title is a notable exception, matching
   its earlier-confirmed lack of any UI beyond the splash timer).
4. Every constructed button is registered via **`RegisterActiveObject`**
   (`0x4f2fb0`, was `FUN_004f2fb0`) into a **sorted tree/list structure**
   keyed by two levels (a layer/z-order value, then a secondary key) — and
   this insertion logic structurally matches the *exact same* sorted-
   container pattern already confirmed for `PostTurnEvent`'s underlying
   insert function (the turn-event scheduler). This is a genuinely elegant,
   unifying architectural finding: **the engine has one reusable generic
   sorted-container primitive, reused for both the time-keyed turn-event
   queue and this layer-keyed active-object/render registry** — not two
   independently-implemented data structures.

**This answers the original open question**: Title/Logo/ServerSelect (and
every other screen) don't need bespoke per-state render code because their
buttons/dialogs are just objects registered into one shared active-object
list during `OnEnter`, and — while the exact function that *iterates* this
list once per frame to call each object's draw method wasn't isolated in
this pass — the architecture is now clear enough that this is a "find one
more function" task rather than an open architectural question. The
movement-related cursor/sound-effect object found earlier in the physics
investigation (`FUN_004368f0`) registers into this same list via the same
`RegisterActiveObject` call, confirming buttons, dialogs, and transient
sound/cursor effects are all instances of one common "active game object"
concept in this engine, not separate systems.

### Remaining open threads

1. `g_spriteVertexBuffer`'s exact per-vertex field layout (byte offsets for
   position/color/UV within each 108-byte record) isn't broken down.
2. Whether the Z-buffer is actually used for depth-sorting (vs. just present
   because the HAL device requires one) is unconfirmed.
3. The developer-name chat easter egg (see above) — what it actually does
   when triggered isn't traced.
4. The function that **iterates** the active-object registry once per frame
   (calling each registered widget/effect's draw method) wasn't isolated —
   the registration side (`RegisterActiveObject`, the sorted-tree insert)
   is fully confirmed, but its consuming iteration loop is the one piece
   left to find to fully close this thread.
5. `LoadButtonDefinitionFromXFS`'s binary widget-definition format (the
   count-prefixed sub-record structure read from `graphics.xfs`) isn't
   decoded field-by-field.
