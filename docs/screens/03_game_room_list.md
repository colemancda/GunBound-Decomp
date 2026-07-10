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
From STRINGS.md's `b_gamelist_*` / `gamelist_*` clusters (`0x553xxx`–`0x5544xx`):
- **Background / chrome sheets**: `gamelist_back.img` (main frame), plus
  `gamelist_channel.img`, `gamelist_chat.img`, `gamelist_create.img`,
  `gamelist_directgo.img`, `gamelist_password.img`, `gameliststage.img` (the
  create-room / direct-go / password sub-dialogs).
- **Bottom-bar buttons** (via `State03_GameRoomList_CreateButtons`; IDs/positions in the button map
  below): `b_gamelist_exit`, `b_gamelist_buddy`, `b_gamelist_ranking`,
  `b_gamelist_avatar`, `b_gamelist_create`, `b_gamelist_join`,
  `b_gamelist_viewall`, `b_gamelist_wait`, `b_gamelist_prev`,
  `b_gamelist_next`, `b_gamelist_friend`, `b_gamelist_directgo`.
- **Persistent nav** (registered by `ChangeGameState`): `b_gamelist_buddyup`/
  `b_gamelist_buddydown`, `b_gamelist_channelup`/`b_gamelist_channeldown`.
- **Dialog buttons**: `b_gamelist_yes.img`, `b_gamelist_no.img`.
- **Room-card frames** (the per-room card background + icons, sprite indices
  1–15 below) are drawn via `FindSpriteFrame` frame lookups — they live in a
  gamelist sprite sheet (most likely `gamelist_back.img`); the renderer keys
  them by frame index, not filename, so the exact sheet isn't named in code.

## Rendering — the room-card grid
`RenderRoomLabel` (slot 15, called by `GameTick`) draws the static chrome, then
loops up to **6 room slots** (`g_clientContext+0x4464c`..`+0x44664`, 4-byte
stride, skipping the client's own room) calling **`RenderRoomCard(slot)`** per
occupied slot. Full geometry from that function:

**Grid:** `slot/3` selects the **column** (slots 0–2 = left, X base `0x18`;
slots 3–5 = right, X base `0x144`); `slot%3` selects the **row** (Y = `slot%3 ·
0x3c`, 60 px pitch). So a **2-column × 3-row** browser. Card background frame:
base `1` (left) / `4` (right); **`+2`** if this is the joined room (`this+4`),
**`+1`** if it's the hovered/selected room (`this+8`) → frames 1–6.

**Per-card elements** — each is a `FindSpriteFrame` frame lookup + blit; positions
are relative to the card's column X (`Xc`) and row Y (`Yr`):
| Element | Pos (x, y) | Sprite frame | Source field (`g_clientContext + … + slot`) |
|---|---|---|---|
| Card background | `(Xc, Yr+0x3a)` | 1–6 (col/state) | `this+4`/`this+8` |
| Small icon | `(Xc+0xb1, Yr+0x42)` | `0xe` (if flag set) | `+0x449b4` |
| Flag icon A | `(Xc+0xc3, Yr+0x46)` | `10+val` | `+0x4499c` |
| Flag icon B | `(Xc+0xd2, Yr+0x46)` | `10+val` | `+0x449a2` |
| Mode/map icon | `(Xc+0x6a, Yr+0x5b)` | `(b&3)·11 + b2` | `+0x44986` (÷4) & `+0x4497c` |
| Status icon | `(Xc+0x13, Yr+0x55)` | `7`/`8`/`9` | `+0x449a8` (7 if set; else 8 if A==B; else 9) |
| Lock (private) | `(Xc+0xea, −6 right; Yr+0x52)` | `0xf` (if flag set) | `+0x449ae` |
| Room number | `(≈0x14, Yr+0x44)` | text, white `0xffff` | `+0x44664` (÷4) `+1`, fmt `PTR_DAT_00551ecc` |
| Fullness dial | `(Xc+0xb1, Yr+0x5b)` | `10 + bits[18:19]` | `+0x44984` (÷4) dword |

Buttons draw separately via the generic active-object sweep.

### Per-room field offsets (indexed by room slot 0–5, off `g_clientContext`)
| Offset | Stride | Meaning |
|---|---|---|
| `+0x44664` | 4 | room number / ID (shown as `+1`) |
| `+0x4497c` | 1 | map/type sub-byte (feeds mode/map icon) |
| `+0x44984` | 4 | per-room info dword; **bits 18–19 = fullness**, byte 2 (`+0x44986`) = mode flag |
| `+0x4499c` | 1 | flag → icon A |
| `+0x449a2` | 1 | flag → icon B |
| `+0x449a8` | 1 | status flag → status icon 7/8/9 |
| `+0x449ae` | 1 | private/password flag → padlock icon `0xf` (also gates join) |
| `+0x449b4` | 1 | flag → icon `0xe` |
| `+0x4464c`..`+0x44664` | 4 | the 6 room-slot index array walked by `RenderRoomLabel` |

## Input — room selection & join
Room cards are **not** `ButtonWidget`s. The state's own **mouse slot**
(`0x428b90`) hit-tests the same 6-slot grid via `FUN_0042ada0`:
- **Left-click** → select/highlight a room (drives the 3-state background).
- **Right-click** (not double-click) → **join**: sends outgoing opcode `0x2104`.

## The command dispatcher — `State03_GameRoomList_OnCommand` (vtable slot 5)
Every lobby button/menu/list event funnels through this one function,
`(this, eventType, param_3, buttonId)`:
- `eventType==0` → a button was clicked, dispatch on `buttonId` (table below;
  confirmed against the real button-creation call `State03_GameRoomList_CreateButtons`, not the
  widget's own 1000-range "action code" field — see ARCHITECTURE.md).
- `eventType==0xa` → confirm/commit (branches on pending-op flags `+0xc/+0xd/+0xe`).
- `eventType==0xb` → cancel/dismiss the active dialog (`FUN_0050ef10`).

**Button map** (`buttonId` when `eventType==0`):

| ID | Image | Action | Effect |
|---|---|---|---|
| 0 | `b_gamelist_exit` | Exit lobby | `ChangeGameState(2)` → Server Select |
| 1 | `b_gamelist_buddy` | (Re)build buddy-list panel | `BuildBuddyPanel` (also in OnEnter) |
| 2 | `b_gamelist_ranking` | — | no case; no-op in this build |
| 3 | `b_gamelist_avatar` | Enter Avatar Store | send `0x6000` (if inventory loaded) |
| 4 | `b_gamelist_create` | **Open Create Room dialog** | `OpenCreateRoomDialog` → `BuildCreateRoomDialog`, title msg `0x62b2`, room-name/password fields |
| 5 | `b_gamelist_join` | Join selected room (checked) | `SendJoinRoomChecked` → `0x2110`; skips if already in that room |
| 0xa | `b_gamelist_viewall` | Filter mode 1 ("view all") | request room list `0x2100` (mode=1) |
| 0xb | `b_gamelist_wait` | Filter mode 2 ("waiting only") | request room list `0x2100` (mode=2) |
| 0xc | `b_gamelist_prev` | Page prev | `0x2100`/`0x2101` (page `-0x118`) |
| 0xd | `b_gamelist_next` | Page next | `0x2100`/`0x2101` (page `+0x118`) |
| 0xe | `b_gamelist_friend` | **Find Friend** — locate a buddy's room | `FindBuddyRoomsForServer` scans active rooms (filter param not fully pinned down); found → `0x2101`; not found → clears `+0x44648` |
| 0xf | `b_gamelist_directgo` | Open the **"DIRECT GO"** dialog (go straight to a room) | `BuildEnterRoomNumberDialog` (`0x557df0`, id 1), msg `0x2715`; runtime-confirmed to hold **Room No.** + **Password** text-entry fields (ids 0/1) + Ok/Cancel — so it's a jump-to-room-by-number-with-password, not just a number entry |

**Dialog-internal codes** (reached via a dialog's own OK/Cancel, not a
top-level button): `0x1e`/`0x20`/`0x28` = Cancel (`FUN_0050ef10`); `0x1f` =
`SendJoinRoomSelected` → `0x2110`; `0x21` = `SendJoinRoomByNumber` → `0x2110`;
`0x29` (and the `eventType==0xa && flag@+0xc` path) = **`SendCreateRoom`, the
Create Room dialog's submit handler** → sends `0x2120` (room name + password).

## List navigation, scrolling, and the (vestigial) channel buttons
There is **no scrollbar** on the room list — the grid is a fixed **2×3 (6 card)**
page. You move through the list/channels with the bottom-bar buttons:
- **Prev / Next** (`b_gamelist_prev`/`next`, ids `0xc`/`0xd`) — page the list;
  they adjust the page index (`+0x118`) and re-request via `0x2100`/`0x2101`.
- **View All / Waiting** (`b_gamelist_viewall`/`wait`, ids `0xa`/`0xb`) — filter
  the list (all rooms vs. waiting-only), re-requesting with a mode byte.
- **Find Friend** (`b_gamelist_friend`, id `0xe`) — jump to a buddy's room.

### The filter toggle and its "active" (yellow) highlight
The three filter buttons (**View All / Waiting / Find Friend**) are a
**mutually-exclusive toggle**: the current filter is a persistent byte at
**`this+0x115`** — `1` = View All, `2` = Waiting, `6` = Friend (clicking Friend
also runs `FindBuddyRoomsForServer`). One value is always set, and **OnEnter
seeds it (default View All / `1`)**, so exactly one filter is always current.

The active button is shown highlighted via the **button-widget visual-state**
system, *not* a hard-coded colour. Each `ButtonWidget`'s **vtable slot 4** is a
`SetState(name)` that swaps the button's sprite frame by name — the confirmed
state strings are `"normal"` (`0x552230`), `"active"` (`0x551e58`), `"select"`
(`0x551e60`), `"ready"` (`0x551e80`), and `"disable"` (`0x551e68`). The
**`"active"` state is the highlighted (yellow) frame**. Consistent with this,
the toggle buttons' art carries an extra frame: `b_gamelist_viewall.img` and
`b_gamelist_friend.img` have **5 frames** each, versus **4** for the non-toggle
`b_gamelist_exit.img` — the 5th is the active/selected look. After every filter
change (and at the end of `CreateButtons`), **`FUN_0042a090`** re-walks the
button list and re-applies the states so the newly-chosen filter shows `"active"`
and the others revert. (`CreateButtonWidget` itself sets `"active"` at creation
when a button's toggle flag `field[0x13]` is set.) The exact yellow tint lives
in the sprite art, so it isn't an RGB constant in the code.

**The dedicated channel up/down buttons are vestigial in this build.**
`ChangeGameState` name-registers nine persistent cross-screen button images via
`AppendPersistentButtonName` — `b_gamelist_buddyup`/`buddydown`,
`b_gamelist_channelup`/`channeldown`, `b_buddy_up`/`down`/`exit`, and
`b_error_confirm` — which preloads their `.img` definitions. But of these, only
**`b_error_confirm` is ever actually instantiated** (`CreateButtonWidget` in the
error/message dialogs `ShowErrorDialog`/`ShowErrorDialogFmt`/`ShowMessageDialog`). The four
scroll names and the three buddy names are **never passed to `CreateButtonWidget`
anywhere** — they're registered/preloaded but no widget is created and no click
handler exists for them. So `b_gamelist_channelup`/`channeldown` explain why the
images ship, but there is **no functional channel *up/down scroll* control**.

**However, there IS a channel picker — corrected by a live dump.** The lobby's
chat panel (`BuildLobbyChatPanel`, `0x557cd4`, id 9001) contains **8 channel
tabs "CH 1–8" as `CLabel` widgets** (`0x557da0`, `typeId 1`, ids 0–7, 22×22 at
`y=296`, `x` = 287,319,…,511 on a 32-px stride) — the row of numbered tabs
across the top of the CHATTING panel. So channel switching *does* exist; it's
just these panel labels (built by the chat-panel builder), not the vestigial
`b_gamelist_channelup/down` bottom-bar buttons. (This supersedes the earlier
"no direct channel picker" note.) The buddy list's own scrolling (right-hand panel, built by
`BuildBuddyPanel`) uses the generic scroll-list widget with its own arrow children,
not these named buttons.

## OnEnter (`0x428d00`) notes
- Registers ~40 button definitions + 12 persistent buttons.
- Sends the initial `0x2100` room-list request (mode from `+0x115`).
- **Ends any active replay recording** (writes final `0x03` byte, `fclose`).
- Shows up to 4 carried-over status messages (localized `0xc351`–`0xc354`,
  gated on `PeekPacketChecksumState` bits `0x100000`–`0x800000` — e.g. kicked/
  disconnected notices on return from battle).

## Network (see PROTOCOL.md — this state's opcodes are extensive)

### Room-list lifecycle
All over the game-server TCP connection (the connection subsystem). The room
grid holds **up to 6 rooms** (`+0x4464c` occupied flags, `+0x44664` numbers)
plus per-room fields; the channel's user list is separate (`0x2105`).

1. **Request** — the client sends **`0x2100`** (filter mode `+0x115` + page) or
   **`0x2101`** (Find Friend), driven by `State03_GameRoomList_OnCommand` on the
   View All / Waiting / Prev / Next / Friend buttons.
2. **Bulk fill** — the server replies with **`0x2103`** (`payload[0]==0`): the
   whole grid in one packet — per room: `roomNumber, name, map, info (fullness
   in bits 18-19), flagA, flagB, status, lock` (wire format in PROTOCOL.md).
3. **Incremental updates** — as individual rooms change, **`0x21f3`–`0x21f7`**
   update single per-room grid fields (map/info/flags/status) without a full
   refresh; **`0x21f1`** removes a room slot.
4. **Render** — `RenderRoomCard` draws each occupied slot from those fields.
5. **Join** — left-click selects a room (`this+8`); **right-click sends
   `0x2104`** (or `0x2110` by number). The server confirms with **`0x2121`**
   (initializes the joined room's player slots) → `ChangeGameState(9)` (Ready
   Room).
6. **Channel users** — **`0x2105`** broadcasts per-player info (the channel
   user-list panel, `BuildChannelUserListPanel`).

**Outgoing** (dispatcher / mouse): `0x2100`, `0x2101`, `0x2104`, `0x2110`
(join, three emitters — see below), `0x2120` (**Create Room**, from
`SendCreateRoom`), `0x6000` (Avatar Store).
**Incoming**: `0x2103` (bulk grid), `0x21f1`/`0x21f3`–`0x21f7` (per-room
updates), `0x2105` (channel user), `0x2121` (join confirm), `0x6001`/`0x6002`
(Avatar Store transition + inventory). Full list under "State 3" in PROTOCOL.md.

### Create Room dialog — 10 widgets, fully laid out (`BuildCreateRoomDialog`)
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

**Submit** (`SendCreateRoom`) only visibly copies the **name and password**
fields into the `0x2120` payload — whether the player-limit/mode selections
are sent at all (bundled some other way, or via a separate opcode) is not
confirmed.

Field offsets (x/y/w/h at `+0x28`/`+0x2c`/`+0x30`/`+0x34`) are confirmed via
the widget class's own hit-test method, not just positional inference — see
ARCHITECTURE.md's "Create Room dialog" writeup for the full derivation and
the same class's use (with an OK/Cancel pair sized identically to this
dialog's) in the "enter room by number" dialog (`BuildEnterRoomNumberDialog`).

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
image). `FindBuddyRoomsForServer(currentServerId)` scans active room objects (type
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
