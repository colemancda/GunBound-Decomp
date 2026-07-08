# State 2 — Server / Channel Select

Where the client receives the server list, lets the player connect, and
transitions into the chosen server's room list. The list **data and the
select→connect→confirm flow are fully implemented**; what's missing in this
build is only a UI to highlight an arbitrary row (see "Selection" below).

## Identity
- **State ID**: 2
- **vtable**: `vtable_State02_ServerSelect` (`0x5570f0`, 18 slots)
- **Object size**: 0x6c (108) bytes; allocated in `InitGame` with `+0x68`
  initialized to `0xffffffff` (-1)
- **ProcessPacket**: `State02_ServerSelect_ProcessPacket` (`0x4e02b0`)
- **OnEnter**: `0x4e14b0` · **OnExit**: `0x4e17f0`

## Vtable slots (state-2-specific)
| Slot | Addr | Role |
|---|---|---|
| 0 | `0x4e5320` | scalar-deleting destructor (shared) |
| 1 | `0x4e02b0` | ProcessPacket |
| 3 | `0x4e1200` | click dispatcher for button IDs 3/4 (exit-game / buddy-game) |
| 5 | `0x4e1170` | click/action handler (server connect on action `param_4==2`) |
| 6 | `0x4e1430` | keydown handler (Enter = connect) |
| 7 | `0x4e14b0` | OnEnter |
| 8 | `0x4e17f0` | OnExit |
| 9 | `0x4e1960` | per-frame tick: resends keepalive/status packets, animates per-slot byte array |
| 2,4,10–17 | — | shared no-op / generic stubs |

Non-vtable helper: **`FUN_004e1bf0`** — the connect-request builder (called by
slots 5 and 6).

## Resources / images
| Purpose | Image | Position (x,y) w×h |
|---|---|---|
| Screen frame/background | `server_list.img` | full-screen |
| Exit-game button | `b_server_exitgame` | (0x28, 0x227) 0x6b×0x2d |
| Buddy-game button | `b_server_buddygame` | (0xa3, 0x227) 0x6b×0x2d |
| Connect button | `b_server_choiceserver` | (0x199, 0x227) 0x6b×0x2d, **created disabled** |
| Error dialog OK | `b_error_confirm` (shared) | (0x1c6, 0x14b) 0x4a×0x1a |
- **Audio**: `channel.mp3`

## State object fields (offsets into the 0x6c object)
| Offset | Field |
|---|---|
| +0x04 | connecting flag (set to 1 while a connect is in progress) |
| +0x06 | UI-dirty / redraw flag |
| +0x08 | **highlighted slot** (UI cursor), init `-1` |
| +0x24 | input-enabled flag |
| +0x28 | **per-slot error-code array** (16 × `int`), values `0x1d`–`0x20` |
| +0x68 | **slot currently being connected to**, init `-1` |
| +0x14/+0x18 | scroll/paging value (derived from a global at OnEnter) |
| +0x20 | tick counter |

## The server list — where it's stored
Received via **opcode `0x1102`** and unpacked into a **structure-of-arrays**
inside `g_clientContext`, 16 entries each, packed contiguously from `+0x3f808`:

| Arena offset | Field | Type×16 |
|---|---|---|
| +0x3f808 | `count` (u8 scalar) | — |
| +0x3f809 | `onlineFlag[16]` | u8 |
| +0x3f81a | `serverId[16]` | u16 |
| +0x3f83a | `regionOrType[16]` | u8 |
| +0x3f84a | `name[16][128]` | char |
| +0x4004a | `desc[16][256]` | char (word-wrapped via `FUN_0041b4b0`) |
| +0x4104a | `serverIp[16]` | u32 (packed IPv4) |
| +0x4108a | `port[16]` | u16 |
| +0x410aa | `unknownField2[16]` | u16 |
| +0x410ca | `currentPlayers[16]` | u16 |
| +0x410ea | `maxCapacity[16]` | u16 |
| +0x4110a | `animState[16]` | u8 (per-slot blink, written by tick) |

Full wire format in [PROTOCOL.md](../../PROTOCOL.md) (opcode `0x1102`). Max 16
entries (the `desc` table is exactly 16×256 = 0x1000).

## OnEnter (`0x4e14b0`)
1. Register button definitions (`FUN_004f1790` ×7; `AppendPersistentButtonName` ×3).
2. Create the three buttons above (`b_server_choiceserver` disabled).
3. Reset `this+8 = -1`; **zero the entire server-list SoA** (`+0x3f808`…`+0x4111a`).
4. Compute an initial scroll/paging value into `+0x14`/`+0x18`.
5. Open the channel/whisper connection (`FUN_004d2480(&DAT_005b2ad0, DAT_005b33e8)`)
   and tear down any stale socket on the swap context (`DAT_007934e8`).
6. Start channel music, clear the "current server" global (`g_clientContext+0x3f804 = -1`).

## Rendering
- **No bespoke render function** — background via the shared slot-15 blit
  (`0x443570`, draws `server_list.img`); the three buttons draw themselves via
  the generic active-object sweep; the per-frame tick (`0x4e1960`) animates a
  per-slot byte at `+0x4110a`.
- **There are no per-server row widgets** — the list rows are not rendered as
  individual clickable widgets in this build.

## Selection → connect
1. `this+8` = highlighted slot. The **Enter handler** (`0x4e1430`) auto-sets it
   to the **first online server** (scans `onlineFlag`, `i < 16`) when `-1`.
2. On confirm (choice-server click → `0x4e1170`, or Enter → `0x4e1430`), after
   checking the slot is online and not full (`currentPlayers ≤ maxCapacity`),
   call **`FUN_004e1bf0(this)`** with the index in `EDI`. That helper:
   - if `this+0x28[slot] != 0` (a prior error) → show error dialog
     `FUN_004124a0` instead of connecting;
   - else `sprintf` the packed IP as `"%d.%d.%d.%d"` from `serverIp[slot]`,
     open a socket to `ip:port` via `FUN_004d2480`, set `this+4 = 1`
     (connecting), disable the button, and record **`this+0x68 = slot`**.

## Errors
- **Opcode `0x1012`** with sub-code `0x5001`/`0x5011`/`0x5012`/`0x5013` maps to
  error code `0x1d`/`0x1e`/`0x1f`/`0x20` and stores it in `this+0x28[slot]`.
  It re-enables the connect button (retry). The **error dialog** appears on the
  next connect attempt (via `FUN_004e1bf0`'s guard → `FUN_004124a0`), which
  looks up message string `code + 0xc7` and shows it with the `b_error_confirm`
  OK button. See README "Error / message dialog".

## Confirm & transition
- **Opcode `0x2001`, `payload[0]==0`**: reads the entry at `this+0x68`, copies
  its `serverId` → `g_clientContext+0x3f804` and `name` → the global
  current-server-name buffer (`g_clientContext+0x3b8e8`), swaps the
  double-buffered context (`DAT_007934ec`⇄`DAT_007934e8`), then
  `ChangeGameState(3)` → Game Room List.

## Network summary (see PROTOCOL.md)
| Opcode | Dir | Meaning |
|---|---|---|
| `0x1102` | in | server-list population (16-entry SoA) |
| `0x1012` | in | connect error code (→ per-slot error) |
| `0x2001` (`payload[0]==0`) | in | connect confirmed → transition to state 3 |
| `0x1000`/`0x1100`/`0x1001`/`0x101f` | in/out | keepalive / handshake / address reporting |

> **Selector-record table** (`g_serverSelectRecords`, `0xe54ca8`): a
> standalone global (12-byte records, count in `g_serverSelectRecordCount`),
> separate from the SoA above. The Game Room List's channel-selector emits one
> record verbatim as opcode `0x2101` — see
> [03_game_room_list.md](03_game_room_list.md). The populator lives on the
> (still-unported) server-list receive path, so the three u32 fields per
> record are not yet named.

## Transitions
- **In**: from Title (state 1).
- **Out**: to Game Room List (state 3) on confirmed connect; to Quit via the
  exit button; buddy-game path via button ID 4.

## Reimplementation checklist
1. Load `server_list.img` + `channel.mp3`; create three buttons (connect disabled).
2. Open the channel connection; wait for opcode `0x1102`; store the SoA list.
3. Highlight logic: default highlight = first online server.
4. On connect: validate online & not-full, connect to `serverIp:port`, mark
   the pending slot.
5. Handle `0x1012` (per-slot error → dialog on retry) and `0x2001` (confirm →
   copy current-server globals, go to room list).
- **Open item**: no code sets the highlight to a non-first row, so this build
  effectively connects to the first online server. A faithful reimplementation
  can add row selection, but the original binary has no such UI.
