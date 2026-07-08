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
- **Buttons** (all via `FUN_0042aba0`, the real button-creation call — see
  the button map below for IDs/positions): `b_gamelist_exit`,
  `b_gamelist_buddy`, `b_gamelist_ranking`, `b_gamelist_avatar`,
  `b_gamelist_create`, `b_gamelist_join`, `b_gamelist_viewall`,
  `b_gamelist_wait`, `b_gamelist_prev`, `b_gamelist_next`,
  `b_gamelist_friend`, `b_gamelist_directgo` (plus the persistent
  buddy-scroll controls registered by `ChangeGameState`).

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
`(this, eventType, param_3, buttonId)`:
- `eventType==0` → a button was clicked, dispatch on `buttonId` (table below;
  confirmed against the real button-creation call `FUN_0042aba0`, not the
  widget's own 1000-range "action code" field — see ARCHITECTURE.md).
- `eventType==0xa` → confirm/commit (branches on pending-op flags `+0xc/+0xd/+0xe`).
- `eventType==0xb` → cancel/dismiss the active dialog (`FUN_0050ef10`).

**Button map** (`buttonId` when `eventType==0`):

| ID | Image | Action | Effect |
|---|---|---|---|
| 0 | `b_gamelist_exit` | Exit lobby | `ChangeGameState(2)` → Server Select |
| 1 | `b_gamelist_buddy` | (Re)build buddy-list panel | `FUN_00509110` (also in OnEnter) |
| 2 | `b_gamelist_ranking` | — | no case; no-op in this build |
| 3 | `b_gamelist_avatar` | Enter Avatar Store | send `0x6000` (if inventory loaded) |
| 4 | `b_gamelist_create` | **Open Create Room dialog** | `FUN_00429c30` → `FUN_00508190`, title msg `0x62b2`, room-name/password fields |
| 5 | `b_gamelist_join` | Join selected room (checked) | `SendJoinRoomChecked` → `0x2110`; skips if already in that room |
| 0xa | `b_gamelist_viewall` | Filter mode 1 ("view all") | request room list `0x2100` (mode=1) |
| 0xb | `b_gamelist_wait` | Filter mode 2 ("waiting only") | request room list `0x2100` (mode=2) |
| 0xc | `b_gamelist_prev` | Page prev | `0x2100`/`0x2101` (page `-0x118`) |
| 0xd | `b_gamelist_next` | Page next | `0x2100`/`0x2101` (page `+0x118`) |
| 0xe | `b_gamelist_friend` | **Find Friend** — locate a buddy's room | `FUN_004021b0` scans active rooms (filter param not fully pinned down); found → `0x2101`; not found → clears `+0x44648` |
| 0xf | `b_gamelist_directgo` | Open "enter room by number" dialog | `FUN_005087b0`, msg `0x2715` |

**Dialog-internal codes** (reached via a dialog's own OK/Cancel, not a
top-level button): `0x1e`/`0x20`/`0x28` = Cancel (`FUN_0050ef10`); `0x1f` =
`SendJoinRoomSelected` → `0x2110`; `0x21` = `SendJoinRoomByNumber` → `0x2110`;
`0x29` (and the `eventType==0xa && flag@+0xc` path) = **`FUN_00429c60`, the
Create Room dialog's submit handler** → sends `0x2120` (room name + password).

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
(request/refresh room list, filter mode + page), `0x2101` (buddy-room-locator
record — sends one 12-byte record from the selector table, see below),
`0x2104` (right-click quick-join from the room grid, via `FUN_00428b90`),
`0x2110` (join room — three emitters, see below), `0x2120` (**Create Room** —
room name + password, from `FUN_00429c60`), `0x6000` (enter Avatar Store).
Full list under "State 3" in PROTOCOL.md.

### Create Room dialog — 10 widgets, fully laid out (`FUN_00508190`)
Opened by button `4` (`b_gamelist_create`); title msg `0x62b2`. Widgets, in
creation order:

| Widget | Position (x,y) w×h | Msg ID(s) | Role |
|---|---|---|---|
| Text entry (id 0) | (0x60,0x2c) 0xbe×0xc | — | **Room name** |
| Text entry (id 1) | (0x60,0x46) 0xbe×0xc | — | **Password** |
| 8 small boxes | y=8 (top row), x stepping 32px from 0xad | `0x518`–`0x51f` | Likely **player-limit picker** (2–8); box index 3 defaults selected → limit 4 |
| 2×2 grid (4 boxes) | y=0x5f/0x7a, x=0x16/0x45 | `0x514`–`0x517` | Unconfirmed — likely a room-mode toggle |
| Button (id 8) | (0xd5,0x99) 0x52×0x22 | `0x51d` | OK/Cancel (right) |
| Button (id 9) | (0x80,0x99) 0x52×0x22 | `0x51c` | OK/Cancel (left) |

**Submit** (`FUN_00429c60`) only visibly copies the **name and password**
fields into the `0x2120` payload — whether the player-limit/mode selections
are sent at all (bundled some other way, or via a separate opcode) is not
confirmed.

Field offsets (x/y/w/h at `+0x28`/`+0x2c`/`+0x30`/`+0x34`) are confirmed via
the widget class's own hit-test method, not just positional inference — see
ARCHITECTURE.md's "Create Room dialog" writeup for the full derivation and
the same class's use (with an OK/Cancel pair sized identically to this
dialog's) in the "enter room by number" dialog (`FUN_005087b0`).

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

### `0x2101` — buddy-room-locator record
Triggered by the **Find Friend** button (`b_gamelist_friend`, ID `0xe`), not
a general channel picker (see the two-stage correction in PROTOCOL.md's
`0x2100` section — first thought absent, then thought a free channel
selector, now confirmed as a buddy-locate feature from the real button
image). `FUN_004021b0(currentServerId)` scans active room objects (type
`0x12`) filtered by a second, uncaptured parameter (plausibly a buddy ID, not
confirmed), building a deduplicated result list. If any match, sends one
**12-byte record** verbatim from the standalone selector table
(`g_serverSelectRecords`, indexed by `idx*0xc`; count/valid flag in
`g_serverSelectRecordCount`) via this opcode; if none, clears a "found" flag
instead. The record is three u32 words; their meaning is not yet confirmed
(the populator, on the server-list receive path, is unported). Wire:
`[u16 0x2101][12-byte record]`.

There is **no direct "pick any channel" control** in this lobby after all —
`0x2100`'s mode byte is a room-list *filter* (view-all/waiting-only), and
`0x2101` is specifically the buddy-locator's result-send, not free browsing.

## Transitions
- **In**: from Server Select (confirmed connect).
- **Out**: → Ready Room (state 9) on room join; ⇄ Avatar Store (state 7);
  Ranking / buddy sub-flows.

## Reimplementation checklist
1. Load `gamelist_back.img` + the 12 lobby buttons (button map above).
2. Maintain a 6-slot room array (`+0x4464c`) with per-room info dwords/flags,
   `this+8` = hovered slot, `this+4` = joined room.
3. Render: chrome + per-card renderer (grid math above), buttons via the sweep.
4. Mouse: hit-test grid; left = select, right = send `0x2104` join.
5. Dialogs: Create Room (name+password → `0x2120`) and Enter Room By Number
   (`_atol` → `0x2110`), both closeable via Cancel.
6. Handle the State-3 opcode set (room list updates, join confirm, player fields).
