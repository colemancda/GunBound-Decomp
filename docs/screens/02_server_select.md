# State 2 — Server / Channel Select

Where the client receives the server list, lets the player scroll/pick a
server, connect, and transition into the chosen server's room list. The list
is a real **scroll-list widget** (draggable scrollbar + up/down arrows) backed
by **server-side pagination** — see "Rendering & the server-list scroll view"
below. (This corrects an earlier writeup that claimed there was no list UI.)

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
5. **Connect to the broker** (`BeginServerConnect(&DAT_005b2ad0, DAT_005b33e8)`)
   — the registry-configured server-list host: `DAT_005b2ad0`/`DAT_005b33e8`
   are the `"IP"`/`"Port"` values read at startup by
   `LoadClientSettingsFromRegistry` from `HKCU\Software\Softnyx\GunBound`.
   Also tears down any stale socket on the swap context (`DAT_007934e8`).
   The connect is **asynchronous** (handed to a background worker) — nothing
   is shown while it's pending; see "Connection subsystem" in ARCHITECTURE.md.
6. Start channel music, clear the "current server" global (`g_clientContext+0x3f804 = -1`).

## Rendering & the server-list scroll view
> **Correction (supersedes an earlier "no list UI / no scroll view / connects
> to first server" conclusion).** That conclusion was wrong: it only looked at
> the state's own vtable slots + the three `CreateButtonWidget` calls and
> missed that `OnEnter` also calls **`FUN_005099d0(&DAT_00e53c40)`**, which
> builds a full **scroll-list panel** through the generic UI-widget system.
> `FUN_005099d0` is called *only* from this screen's `OnEnter`.

- The state has **no bespoke render slot** (slot 15 is the shared background
  blit `0x443570`, drawing `server_list.img`); the three top-level buttons and
  the whole list panel draw via the generic active-object sweep.
- **`FUN_005099d0`** creates a ~545×530 panel (at `(0xb,0xd)`) with two panel
  buttons (msg `0x44c`/`0x44d`) and a **scroll-list widget** built by
  **`FUN_005080a0`** (class vtable `0x557e90`, 0x58-byte object).
- The scroll-list widget:
  - auto-creates its own **up/down scroll-arrow buttons** (two 18×18 child
    widgets, at the top and bottom of the track);
  - has a **draggable scrollbar thumb** — mouse-down (`FUN_0050f500`) hit-tests
    the thumb rect computed from scroll position (`+0x40`), content total
    (`+0x38`), and track height (`+0x34`) and begins a drag; mouse-move
    (`FUN_0050f460`) recomputes the position during the drag;
  - arrow clicks drive `FUN_0050f7c0`, which steps the scroll position ±1
    (clamped to `total − pageSize`);
  - on any scroll change (drag or arrows) fires a callback to the parent
    panel: **cmd `0x2000` + the new scroll position**.
- The parent panel's handler (`FUN_0050d810`) writes the scroll offset back
  into the **ServerSelect state object** (`g_gameStateVTableArray[2]+0x14`/
  `+0x18`) and issues a **server request** for that page — see below.

**Server-side pagination.** The list is fetched a page at a time. The tick
(`0x4e1960`) and the panel handler send opcode **`0x1100`** carrying the scroll
offset (state `+0x18`); the server replies with that 16-entry page via
`0x1102`. Scrolling past the current page re-requests from the server
(`0x1100`/`0x1101`) rather than being a purely local view.

*(Not fully traced: the exact per-row pixel draw of server names, and whether a
row-click sets the highlighted slot `this+8` directly — the scroll/paging
mechanism itself is confirmed.)*

## Selection → connect
1. `this+8` = highlighted slot. The **Enter handler** (`0x4e1430`) auto-sets it
   to the **first online server** (scans `onlineFlag`, `i < 16`) when `-1`.
2. On confirm (choice-server click → `0x4e1170`, or Enter → `0x4e1430`), after
   checking the slot is online and not full (`currentPlayers ≤ maxCapacity`),
   call **`FUN_004e1bf0(this)`** with the index in `EDI`. That helper:
   - if `this+0x28[slot] != 0` (a prior error) → show error dialog
     `FUN_004124a0` instead of connecting;
   - else `sprintf` the packed IP as `"%d.%d.%d.%d"` from `serverIp[slot]`,
     open a socket to `ip:port` via `BeginServerConnect`, set `this+4 = 1`
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
| `0x1100` | out | **request a server-list page** at the current scroll offset (`+0x18`); driven by the scroll widget, the tick, and the panel handler |
| `0x1101` | out | paged-fetch variant (sends a selector record) used while scrolling |
| `0x1102` | in | server-list page population (16-entry SoA) |
| `0x1012` | in | connect error code (→ per-slot error) |
| `0x2001` (`payload[0]==0`) | in | connect confirmed → transition to state 3 |
| `0x1000`/`0x1001`/`0x101f` | in/out | keepalive / handshake / address reporting |

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
1. Load `server_list.img` + `channel.mp3`; create the three top-level buttons
   (connect disabled) and the scroll-list panel (`FUN_005099d0`).
2. Connect to the broker; request a page (`0x1100`, scroll offset from `+0x18`);
   store each `0x1102` page into the 16-entry SoA.
3. Render the scroll list: visible rows + a draggable scrollbar thumb + up/down
   arrows; scrolling updates `+0x14`/`+0x18` and re-requests via `0x1100`/`0x1101`.
4. Selection: the Enter key auto-highlights the first online server; a real
   scroll-list picker also exists (row selection wiring not fully traced).
5. On connect: validate online & not-full, connect to `serverIp:port`, mark
   the pending slot (`+0x68`).
6. Handle `0x1012` (per-slot error → dialog on retry) and `0x2001` (confirm →
   copy current-server globals, go to room list).
