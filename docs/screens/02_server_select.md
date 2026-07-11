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

Non-vtable helper: **`ConnectToSelectedServer`** — the connect-request builder (called by
slots 5 and 6).

## Resources / images
| Purpose | Image | Position (x,y) w×h |
|---|---|---|
| Screen frame/background | `server_list.img` | full-screen |
| Exit-game button | `b_server_exitgame` | (0x28, 0x227) 0x6b×0x2d |
| Buddy-game button | `b_server_buddygame` | (0xa3, 0x227) 0x6b×0x2d |
| Connect button | `b_server_choiceserver` | (0x199, 0x227) 0x6b×0x2d, **created disabled** |
| Error dialog OK | `b_error_confirm` (shared) | (0x1c6, 0x14b) 0x4a×0x1a |
- **Audio**: `channel.mp3` (started by `PlayMusicTrack(1)`)

### Images loaded by resource ID
Only the three bottom buttons appear as string literals in `OnEnter`; every
other resource is preloaded **by numeric ID** via `LoadSpriteSet(&DAT_00ea0e18,
id)` (an XFS-defined resource loader), then bound to a widget. The seven IDs
`OnEnter` preloads:

| Resource ID | Image / resource | Bound to |
|---|---|---|
| `10000` (`0x2710`) | screen background — **`server_list.img`** | drawn by the shared slot-15 blit; same "main background" ID slot Logo1 uses for `logomode.img` |
| `0x2711` | companion screen-frame/overlay resource | not pinned to a specific `.img` |
| `1000` (`0x3e8`) | **`b_server_exitgame.img`** | Exit button (id 0, action `1000`) |
| `0x3e9` | **`b_server_buddygame.img`** | Buddy button (id 1, action `0x3e9`) |
| `0x3ea` | **`b_server_choiceserver.img`** | Connect button (id 2, action `0x3ea`) |
| `0x44c` | **`b_server_all.img`** | "View All" panel button (`BuildWorldListPanel`) |
| `0x44d` | **`b_server_friend.img`** | "Friends" panel button (`BuildWorldListPanel`) |

The `.img` filenames come from the archive TOC (STRINGS.md, cluster
`0x557144`–`0x5571f8`), not from this state's code. The per-row sprites (row
background, F/E population dial, scroll arrows) are drawn via texture-cache
lookups at render time and are most likely frames within `server_list.img`
rather than separate files (inferred, not confirmed by name). `10000`/`0x2711`
are the least certain — `10000` maps to the background by analogy with other
screens; `0x2711`'s exact target isn't confirmed.

## State object fields (offsets into the 0x6c object)
**Runtime-confirmed** — every field below was verified against a live debugger
dump of the object (`vtable 0x5570f0`); names/semantics match the
`CState02ServerSelect` reconstruction in `src/cxx/GameState.h`.

| Offset | Field | Notes |
|---|---|---|
| +0x04 | `m_connecting` | 1 while a connect attempt is in flight |
| +0x05 | `m_sendHandshake` | connect succeeded → send `0x1000` next tick |
| +0x06 | `m_uiDirty` | UI-dirty / interactable gate (row select needs `==1`) |
| +0x07 | `m_wantInitialList` | set by OnEnter → tick sends the first `0x1100` page request |
| +0x08 | `m_highlightedSlot` | selected server slot, `-1` = none. **Confirmed live**: clicking the row set it `-1 → 0` |
| +0x0c | `m_selectedSlot` (was `m_unk0c`) | tracks the selection alongside `+0x08` — moved `-1 → 0` in lockstep on the same row-click |
| +0x10 | **`m_viewMode`** | **the World List View All / Friends toggle: `0` = View All, `2` = Friends** |
| +0x14 / +0x18 | `m_scrollA` / `m_scrollOffset` | scroll/paging (offset sent in `0x1100`) |
| +0x20 | `m_tickCounter` | free-running tick counter |
| +0x24 | `m_inputEnabled` | set to `(highlightedSlot != -1)` on row click — **gates the SERVER button**. Confirmed live: `0 → 1` when the row was selected |
| +0x28 | `m_slotError[16]` | per-slot connect error codes `0x1d`–`0x20` |
| +0x68 | `m_connectingSlot` | slot a connect targets, `-1` = none |

**Selection flow (runtime-confirmed).** `OnEnter` seeds `m_highlightedSlot` /
`m_selectedSlot` = `-1` and `m_inputEnabled` = 0 (nothing selected → the bottom
**SERVER** button is disabled/grey). Clicking a server row hit-tests to a slot
and sets both slot fields to that index and `m_inputEnabled = 1`, which
**enables the SERVER button** (the connect trigger). A live capture of a
selected row shows exactly `m_highlightedSlot = m_selectedSlot = 0`,
`m_inputEnabled = 1`.

**The "View All / Friends" toggle** (the two buttons at the bottom of the WORLD
LIST) is `m_viewMode` (`+0x10`): **`0` = View All** (default), **`2` = Friends**.
That is this screen's server-filter toggle — distinct from State 3's
room-filter buttons. **Both values confirmed live**: one capture shows
`m_viewMode = 0`, and after clicking Friends another shows `m_viewMode = 2` with
the Friends button rendered **yellow**. Note the yellow "active" highlight is
**not a widget-tree flag** — in both captures the two label buttons are
`enabled = true` and neither is `focused`; the panel picks which one to draw
active purely from `m_viewMode`.

## The WORLD LIST panel (runtime-confirmed structure)
Built by `BuildWorldListPanel` (`0x5099d0`) and registered in
`g_uiPanelManager` (`0xe53c40`). A live dump shows the tree (widget `typeId` is
the `+0x20` class id — `0` = panel, `1` = label/button, `4` = scroll-list):

- **Panel** `vtable 0x557f08`, `typeId 0`, id **9000**, rect `(11,13,545,530)` — the framed list area. Children:
  - **View All** — label button (`0x557da0`, `typeId 1`), id **0**, rect `(336,504,74,26)`
  - **Friends** — label button (`0x557da0`, `typeId 1`), id **1**, rect `(430,504,74,26)`
  - **Scroll-list** (`0x557e90`, `typeId 4`), id 0, rect `(526,87,18,377)` — 18 px wide at the right edge; `enabled=false` when the list is empty. Children:
    - **Up** arrow — label (`0x557da0`), id 0, rect `(526,59,18,18)`
    - **Down** arrow — label (`0x557da0`), id 1, rect `(526,474,18,18)`

The View All/Friends buttons here are **`CLabel`-based** (`0x557da0`), *not* the
flat `ButtonWidget` used by State 3's `CreateButtons` — the two screens build
their bottom bars with different widget classes.

**Rows are not widgets — confirmed with a populated list.** A live capture with
the world list showing an actual server (name + fullness dial) has the WORLD
LIST panel still holding **exactly its 3 children** (View All, Friends,
scrollbar) — no per-row widget appears in the tree. So each server row is
**custom-drawn by `RenderWorldListRow`** straight from the server SoA
(`+0x3f808`, below), not built as child widgets; the scroll-list widget only
provides the scrollbar/arrows. (Same capture confirms `BuildBuddyPanel`'s
`0x557be4` panel, id 20000 at `(568,11) 211×267`, opening beside it with its
Add/Del/close-X buttons + buddy scrollbar.)

## The server list — where it's stored
Received via **opcode `0x1102`** and unpacked into a **structure-of-arrays**
inside `g_clientContext`, 16 entries each, packed contiguously from `+0x3f808`.
**Confirmed live**: a client-context dump has `g_clientContext = 0x7a7ae0` and
the SoA base at `0x7e72e8` (= `+0x3f808`), decoding entry 0 as `name`
"OptiPlex 7020", `desc` "GunBound World Server", `ip` `100.65.243.48`,
`port` 8370, `online` 1, `players` 0, `maxCapacity` 100, with `count` = 1 —
matching this layout field-for-field. (The local account name lives separately
at `g_clientContext+0x2331c` = "colemancda2".)

| Arena offset | Field | Type×16 |
|---|---|---|
| +0x3f808 | `count` (u8 scalar) | — |
| +0x3f809 | `onlineFlag[16]` | u8 |
| +0x3f81a | `serverId[16]` | u16 |
| +0x3f83a | `regionOrType[16]` | u8 |
| +0x3f84a | `name[16][128]` | char |
| +0x4004a | `desc[16][256]` | char (word-wrapped via `RenderWrappedText`) |
| +0x4104a | `serverIp[16]` | u32 (packed IPv4) |
| +0x4108a | `port[16]` | u16 |
| +0x410aa | `unknownField2[16]` | u16 |
| +0x410ca | `currentPlayers[16]` | u16 |
| +0x410ea | `maxCapacity[16]` | u16 — **big-endian / network order**: slot 0 = 100 is stored as bytes `00 64`, so a little-endian read gives `0x6400` (25600); byte-swap to get the real cap |
| +0x4110a | `animState[16]` | u8 (per-slot blink, written by tick) |

Full wire format in [PROTOCOL.md](../../PROTOCOL.md) (opcode `0x1102`). Max 16
entries (the `desc` table is exactly 16×256 = 0x1000).

## OnEnter (`0x4e14b0`)
1. Register button definitions (`LoadSpriteSet` ×7; `AppendPersistentButtonName` ×3).
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
> missed that `OnEnter` also calls **`BuildWorldListPanel(&DAT_00e53c40)`**, which
> builds a full **scroll-list panel** through the generic UI-widget system.
> `BuildWorldListPanel` is called *only* from this screen's `OnEnter`.

- The state has **no bespoke render slot** (slot 15 is the shared background
  blit `0x443570`, drawing `server_list.img`); the three top-level buttons and
  the whole list panel draw via the generic active-object sweep.
- **`BuildWorldListPanel`** creates a ~545×530 panel (at `(0xb,0xd)`) with two panel
  buttons (msg `0x44c`/`0x44d`) and a **scroll-list widget** built by
  **`CreateScrollListWidget`** (class vtable `0x557e90`, 0x58-byte object).
- The scroll-list widget:
  - auto-creates its own **up/down scroll-arrow buttons** (two 18×18 child
    widgets, at the top and bottom of the track);
  - has a **draggable scrollbar thumb** — mouse-down (`ScrollListWidget_OnMouseDown`) hit-tests
    the thumb rect computed from scroll position (`+0x40`), content total
    (`+0x38`), and track height (`+0x34`) and begins a drag; mouse-move
    (`FUN_0050f460`) recomputes the position during the drag;
  - arrow clicks drive `FUN_0050f7c0`, which steps the scroll position ±1
    (clamped to `total − pageSize`);
  - on any scroll change (drag or arrows) fires a callback to the parent
    panel: **cmd `0x2000` + the new scroll position**.
- The parent panel's handler (`WorldListPanel_OnCommand`) writes the scroll offset back
  into the **ServerSelect state object** (`g_gameStateVTableArray[2]+0x14`/
  `+0x18`) and issues a **server request** for that page — see below.

**Server-side pagination.** The list is fetched a page at a time. The tick
(`0x4e1960`) and the panel handler send opcode **`0x1100`** carrying the scroll
offset (state `+0x18`); the server replies with that 16-entry page via
`0x1102`. Scrolling past the current page re-requests from the server
(`0x1100`/`0x1101`) rather than being a purely local view.

### Per-row rendering (now traced)
**`WorldListPanel_Draw`** (`0x50dc40`) loops `count` (`g_clientContext+0x3f808`)
calling **`RenderWorldListRow`** (`0x50dc80`) once per server. Each row:
- **2-column grid layout** — x = `(i%2)·0xf7 + 0x16 + panelX`, y =
  `(i/2)·0x49 + 0x2d + panelY` (247px column pitch, 73px row pitch), matching
  the screenshot.
- **Row background sprite by selection state**: base state from the online
  flag; **state `3` if `i == g_gameStateVTableArray[2]+8`** (the highlighted
  row), state `2` if `i == +0xc`. So the highlighted slot `+8` is read here at
  draw time to shade the selected row.
- **Server number** — `sprintf("%d", serverId+1)` → `BlitSpriteText` +
  `BlitRLESprite` (white `0xffff`).
- **Name + two description lines** — `BlitRLESprite` (colour `0xb77f`) at
  y+0x1e, 14px line pitch (text sourced from the SoA name/`desc` arrays,
  register-passed so not visible in the decompile).
- **Population gauge** — `currentPlayers·100 / maxCapacity` bucketed against
  thresholds at `g_fullnessGaugeThresholds` (5 levels) to choose a gauge sprite; drawn via
  `BlitSprite16bpp`/`BlitSpriteClipped`. This is the F/E dial in the UI.

## Selection → connect
1. `this+8` = highlighted slot. **Two ways it's set:**
   - **Row click** — the panel's mouse-down (`WorldListPanel_OnMouseDown`,
     `0x50d5a0`) calls **`WorldListRowHitTest`** (`0x50df40`), which maps the
     click to a row using the *same* grid geometry as the renderer and returns
     the index only if that server is **online**. It then writes
     `g_gameStateVTableArray[2]+8 = <clicked row>` and enables the connect
     button (`+0x24 = (row != -1)`). This is the real picker.
   - **Enter key** (`0x4e1430`) auto-sets `+8` to the **first online server**
     when nothing is highlighted.
2. On confirm (SERVER/choice-server button → `0x4e1170`, or Enter →
   `0x4e1430`), after checking the slot is online and not full
   (`currentPlayers ≤ maxCapacity`), call **`ConnectToSelectedServer(this)`** with the
   index in `EDI`. That helper:
   - if `this+0x28[slot] != 0` (a prior error) → show error dialog
     `ShowErrorDialog` instead of connecting;
   - else `sprintf` the packed IP as `"%d.%d.%d.%d"` from `serverIp[slot]`,
     open a socket to `ip:port` via `BeginServerConnect`, set `this+4 = 1`
     (connecting), disable the button, and record **`this+0x68 = slot`**.

## Errors
Three distinct error paths, all surfacing through the shared in-game dialog
`ShowErrorDialog` (the `b_error_confirm` OK button + a word-wrapped localized
message from the string table, `GetLocalizedString(&g_localizedStringTable, id)`):

- **Communication / connection failure** — the async connect is resolved by the
  connection-state poller `ProcessIncomingPackets`: while a connect is in progress
  (`conn+0x84e4`) and the connection object's state field (`conn+0x22c`) leaves
  "dialing" (3), it clears `+0x84e4` and sets `+0x84e5 = (state == 2)`
  ("connected"). The ServerSelect **tick** (`0x4e1960`) polls this: when the
  attempt finishes and `+0x84e5 == 0` (didn't connect), it calls
  **`ShowErrorDialog(0)`** → the error dialog. A mid-session socket failure (e.g.
  a keepalive `sendto` failing in `FUN_00401200`) instead calls
  **`ShowErrorDialog(1)`** — the `1` also tears the game sockets down.
- **Server-reported errors while communicating** — the packet pump
  `ProcessIncomingPackets` dispatches received packets; various server error codes (under
  opcode `0x2001`, e.g. sub-code `0x20`) call `ShowErrorDialog`, while some other
  status codes are shown via a **native Win32 `MessageBoxA`** with a localized
  string. (On the worker thread, a socket `FD_CLOSE`/connect-fail also enqueues
  status code `0x65` to the owning UI object's event queue as a softer signal.)
- **Retry of a slot that already errored** — `0x1012` with sub-code
  `0x5001`/`0x5011`/`0x5012`/`0x5013` maps to error code `0x1d`–`0x20` and
  stores it in `this+0x28[slot]`, then re-enables the connect button; the
  dialog appears on the *next* connect attempt (via `ConnectToSelectedServer`'s guard →
  `ShowErrorDialog`, message string `code + 0xc7`).

See README "Error / message dialog" for the dialog's layout.

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
   (connect disabled) and the scroll-list panel (`BuildWorldListPanel`).
2. Connect to the broker; request a page (`0x1100`, scroll offset from `+0x18`);
   store each `0x1102` page into the 16-entry SoA.
3. Render the scroll list: visible rows + a draggable scrollbar thumb + up/down
   arrows; scrolling updates `+0x14`/`+0x18` and re-requests via `0x1100`/`0x1101`.
4. Selection: clicking a row hit-tests the grid (`WorldListRowHitTest`, online
   rows only) and sets the highlighted slot `+8`; the Enter key auto-highlights
   the first online server when none is selected. Draw each row via
   `RenderWorldListRow` (number, name, 2 desc lines, population gauge; highlight
   the row whose index == `+8`).
5. On connect: validate online & not-full, connect to `serverIp:port`, mark
   the pending slot (`+0x68`).
6. Handle `0x1012` (per-slot error → dialog on retry) and `0x2001` (confirm →
   copy current-server globals, go to room list).
