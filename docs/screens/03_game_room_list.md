# State 3 — Game Room List (channel lobby)

The busiest screen: a grid of joinable game rooms, plus create/refresh/ranking/
avatar/buddy buttons. Owns the largest protocol handler in the game.

## Identity
- **State ID**: 3
- **vtable**: `vtable_State3_NetworkSession` (`0x553670`)
- **Object size**: 0x294 (660) bytes
- **ProcessPacket**: `State03_GameRoomList_ProcessPacket` (`0x426ad0`, 6,736
  bytes — the biggest handler in the protocol)
- **OnEnter**: `0x428d00` · **OnExit**: `0x429480`
- **Input slots**: keyboard `0x4285c0` (slot 5), **mouse `0x428b90`** (slot 6)
- **Render slot**: slot 15 = `State03_GameRoomList_RenderRoomLabel` (`0x429810`)

## Resources / images
- **Frame**: `gamelist_back.img`
- **Buttons**: `gamelist_create.img`, `b_gamelist_join`, `b_gamelist_ranking`,
  `b_gamelist_avatar`, `b_gamelist_buddy` (plus the persistent buddy-scroll
  controls registered by `ChangeGameState`).

## Rendering — the room-card grid
`RenderRoomLabel` (slot 15, called by `GameTick`) draws the static chrome, then
loops up to **6 room slots** (`g_clientContext+0x4464c`..`+0x44664`, 4-byte
stride, skipping the client's own room) calling **`FUN_0042a220(roomIndex)`**
per occupied slot. Each room "card":
- **Grid layout**: `roomIndex/3` → column (X base `0x18` or `0x144`, 2 columns);
  `roomIndex%3` → row (`*0x3c` = 60 px). Classic **3-row × 2-column** browser.
- **3-state background**: base sprite; `+1` if hovered/selected (`this+8`);
  `+2` if it's the room the client joined (`this+4`).
- Room-type/flag icon; two small byte-flag icons; a combined mode/map icon
  `(flagByte & 3)*11 + otherByte`.
- **Status icon** (waiting/in-progress/full, sprites 7/8/9).
- **Conditional lock icon** (private/password-protected padlock) if a byte flag set.
- **Room number** (`sprintf("%d", roomIndex+1)` via `FUN_004ed9f0`) and
  **player count** (`%s[%3d/%3d]` via `BlitRLESprite`, the bitmap-font path).
- **Fullness icon** (4 states from bits 18–19 of a per-room info dword).

Buttons draw separately via the generic active-object sweep.

## Input — room selection & join
Room cards are **not** `ButtonWidget`s. The state's own **mouse slot**
(`0x428b90`) hit-tests the same 6-slot grid via `FUN_0042ada0`:
- **Left-click** → select/highlight a room (drives the 3-state background).
- **Right-click** (not double-click) → **join**: sends outgoing opcode `0x2104`.

## The command dispatcher — `FUN_004285c0` (vtable slot 5)
Every lobby button/menu/list event funnels through this one function,
`(this, eventType, param_3, actionCode)`:
- `eventType==0` → button/menu action, dispatch on `actionCode` (table below).
- `eventType==0xa` → confirm/commit (branches on pending-op flags `+0xc/+0xd/+0xe`).
- `eventType==0xb` → cancel/dismiss the active dialog (`FUN_0050ef10`).

**Action-code map** (`actionCode` when `eventType==0`):

| Code | Action | Effect |
|---|---|---|
| 0 | Exit lobby | `ChangeGameState(2)` → Server Select |
| 1 | (Re)build lobby list/dialog panel | `FUN_00509110` (also in OnEnter) |
| 3 | Enter Avatar Store | send `0x6000` (if inventory loaded) |
| 4 | Open text-input dialog | `FUN_00429c30` (msg `0x62b2`) |
| 5 | Join selected room (checked) | `SendJoinRoomChecked` → `0x2110`; skips if already in that room |
| 0xa | Channel/tab mode 1 | request room list `0x2100` (mode=1) |
| 0xb | Channel/tab mode 2 | request room list `0x2100` (mode=2) |
| 0xc | Page prev | `0x2100`/`0x2101` (page `-0x118`) |
| 0xd | Page next | `0x2100`/`0x2101` (page `+0x118`) |
| 0xe | Open channel selector (mode 6) | build sorted channel list, send `0x2101` |
| 0x1f | Join selected room | `SendJoinRoomSelected` → `0x2110` (room# from list table) |
| 0x21 | Join room by typed number | `SendJoinRoomByNumber` → `0x2100` then `0x2110` (room# via `_atol`, 1..1000) |
| 0xf, 0x1e, 0x20, 0x28, 0x29 | list scroll/refresh/leave | minor UI plumbing; `0x29` sends `0x2120` |

## OnEnter (`0x428d00`) notes
- Registers ~40 button definitions + 12 persistent buttons.
- Sends the initial `0x2100` room-list request (mode from `+0x115`).
- **Ends any active replay recording** (writes final `0x03` byte, `fclose`).
- Shows up to 4 carried-over status messages (localized `0xc351`–`0xc354`,
  gated on `PeekPacketChecksumState` bits `0x100000`–`0x800000` — e.g. kicked/
  disconnected notices on return from battle).

## Network (see PROTOCOL.md — this state's opcodes are extensive)
**Incoming**: `0x2103` (bulk room player-list update), `0x2105` (player
info/profile broadcast; defines `RoomPlayerSlot`), `0x2121` (join
confirmation), `0x21f0`–`0x21f7` (per-field player updates), `0x6001`/`0x6002`
(→ Avatar Store transition & inventory).
**Outgoing** (from the command dispatcher / mouse handler): `0x2100`
(request/refresh room list, channel+page), `0x2101` (channel selector/nav —
sends one 12-byte record from the selector table, see below), `0x2104`
(right-click quick-join from the room grid, via `FUN_00428b90`), `0x2110`
(enter/join a room — three emitters, see below), `0x2120` (leave/refresh,
tentative), `0x6000` (enter Avatar Store). Full list under "State 3" in
PROTOCOL.md.

### `0x2110` — join room (three emitters, one wire layout)
All three write the same fixed 8-byte packet; only the source of the two
fields differs:

```
[u16 opcode=0x2110][u16 roomNumber][u32 payload]
```

| Emitter | `roomNumber` source | `payload` (u32) | Trigger |
|---|---|---|---|
| `SendJoinRoomSelected` (`0x429fd0`) | room-id table `g_clientContext+0x44664+sel*4` | node field `+0x50` | action `0x1f` |
| `SendJoinRoomChecked` (`0x429b50`) | same room-id table | `_DAT_00551cb1` | action `5`; dedups against rooms already joined |
| `SendJoinRoomByNumber` (`0x429de0`) | `_atol` of a typed field, clamped 1..1000 | node field `+0x54` | action `0x21`; preceded by a `0x2100` |

> The `payload` is a **fixed 4-byte field**, not a player-name string — an
> earlier note misread it as a variable-length name.

### `0x2101` — channel/server selector record
Emitted only in selector mode (`this+0x115 == 6`). Copies one **12-byte
record** verbatim from the standalone selector table
(`g_serverSelectRecords`, indexed by `idx*0xc`; count/valid flag in
`g_serverSelectRecordCount`). The record is three u32 words; their meaning is
not yet confirmed (the populator, on the server-list receive path, is
unported). Wire: `[u16 0x2101][12-byte record]`.

> **Correction**: channel switching *does* exist in the lobby — it's an
> outgoing mechanic (`0x2100` mode byte / `0x2101` selector), which an earlier
> incoming-only scan missed. See PROTOCOL.md's `0x2100` section.

## Transitions
- **In**: from Server Select (confirmed connect).
- **Out**: → Ready Room (state 9) on room join; ⇄ Avatar Store (state 7);
  Ranking / buddy sub-flows.

## Reimplementation checklist
1. Load `gamelist_back.img` + the 5 lobby buttons.
2. Maintain a 6-slot room array (`+0x4464c`) with per-room info dwords/flags,
   `this+8` = hovered slot, `this+4` = joined room.
3. Render: chrome + per-card renderer (grid math above), buttons via the sweep.
4. Mouse: hit-test grid; left = select, right = send `0x2104` join.
5. Handle the State-3 opcode set (room list updates, join confirm, player fields).
