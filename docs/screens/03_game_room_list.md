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

## Network (see PROTOCOL.md — this state's opcodes are extensive)
Key ones: `0x2103` (bulk room player-list update), `0x2105` (player
info/profile broadcast; defines `RoomPlayerSlot`), `0x2104` (outgoing join
request), `0x2121` (join confirmation), `0x21f0`–`0x21f7` (per-field player
updates), `0x6001`/`0x6002` (→ Avatar Store transition & inventory). Full list
under "State 3" in PROTOCOL.md.

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
