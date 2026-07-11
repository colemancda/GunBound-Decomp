# State 9 — Ready Room (pre-battle)

The pre-battle staging screen: shows the player roster, a live character/avatar
preview, map selection, and the item/loadout picker before the match starts.

## Identity
- **State ID**: 9
- **vtable**: `vtable_State09_ReadyRoom` (`0x5569f8`)
- **Object size**: 0x78c bytes — constructed by `FUN_004d3770`
- **ProcessPacket**: `State09_ReadyRoom_ProcessPacket` (`0x4d38c0`)
- **OnEnter**: `0x4d6810` · **OnExit**: `0x4d7630`
- **Chat/keyboard input**: `State09_ReadyRoom_HandleChatInput` (`0x4d6210`)

## Resources / images
- `ready_selectmap.img`, `ready_selectcharacter.img`, `b_ready_startgame`
  (plus shared persistent buttons).
- Textures: `AvataTexture1/2`, `CharacterTexture1/2`, `AvataEffectTexture1/2`,
  `CharEffectTexture1/2` (same families as In-Battle — preloaded via
  `0x4d7b20`, identical to Loading's preload list).

## Rendering (three render slots)
These are the state's own **render slots** (custom-drawn regions), *not*
composite widget panels. **Runtime-confirmed**: a live view dump of the Ready
Room shows exactly **one** `g_uiPanelManager` panel — the chat log
(`BuildReadyRoomChatPanel` `0x557ee0`, id 2000, at `(21,385) 480×160`; its
`hidden` flag toggles between captures — seen both hidden and visible with the
same center popup on screen, so the trigger isn't the popup; not yet pinned).
Everything else — the character preview, the
team slots, the mobile-select grid, the item/avatar shop, the game-mode option
buttons, CHANGE/START — is drawn by these slots and by `CreateButtonWidget`
buttons in the flat `DAT_00e9be90` registry (see the button table below), not
by the widget tree.

- **Character preview** — `State09_ReadyRoom_RenderCharacterPreview` (`0x4d90c0`,
  2,575 bytes): draws a live preview of the **currently selected** character/
  avatar using the avatar/character/effect texture families.
- **Roster + item picker** — slot 13
  (`State09_ReadyRoom_RenderRosterAndItems`, `0x4d7db0`, was `FUN_004d7db0`,
  4,854 bytes):
  - **8-player ready roster**, 2 rows × 4 cols, using the per-slot
    `PeekPacketChecksumState()` bit idiom (same as Loading) to show who's ready.
    Backed by the **room-slot array at `ctx+0x457f1`** (0xD-byte records: a
    12-byte NUL-terminated name + a status/flag byte at record `+0xc`;
    `Ctx_roomSlotName` in `src/cxx/ClientContext.h`). Runtime-confirmed from a
    live dump: `colemancda2` @ slot 0, `admin` @ slot 1, both `+0xc == 0`. The
    same array is indexed by `slot*0xd + 0x457f1` in State03's 0x2105 handler
    (which populates it), State09 chat/battle-action, and State10 loading — so
    the roster persists Ready Room → Loading → Battle.
  - **Paginated item-loadout grid**: 9 slots/page (3×3, spacing
    `(i%3)*0x46+0x210` / `(i/3)*0x2d+0x193`), item IDs from `this+0x518`,
    sprite via the global item-ID→sprite table `&DAT_0056dc40`, labels via
    `FUN_004ed9f0`. Current page at `this+0x620`, item count at `this+0x61c`.
    **Table encoding decoded** (see ARCHITECTURE.md's Ready Room section):
    40 `uint16` entries, packed `(sheet_flag:8)(icon_pair_index:8)` —
    low byte selects an enabled/disabled frame pair (`*2`, `-2`/`-1`),
    high byte (`0x00`/`0xff`) selects texture `0x2713`/`0x2714`. Confirmed
    against `itemdata.dat`'s own `0x30` field (same encoding, every real
    item's value appears in the table verbatim) — but what actually
    indexes the table at runtime is still open (ruled out: item type ID
    and record slot number, both fail cross-reference), so the shelf
    icon↔item-name mapping itself is still not fully resolved, only the
    table's format is.
- **Map thumbnails** — slot 15 (`FUN_004d9ae0`, 2,406 bytes): draws content at
  six fixed screen positions — most plausibly the map-selection thumbnails
  (strong inference; not cross-checked against `ready_selectmap.img`).
- Remaining slots: `0x4d54c0` (20-byte ready-status check), **`0x4d54e0` =
  `State09_ReadyRoom_OnCommand`** (the command dispatcher — *not* a "UI updater"
  as an earlier draft guessed; see below), `0x4d7b20` (texture preload).

## Buttons (`OnEnter`, `0x4d6810`)
`CreateButtonWidget` calls, by button ID:
| ID | Image | Purpose |
|---|---|---|
| 0 | `b_ready_ready` | Ready toggle (guest) |
| 1 | `b_ready_startgame` | Start Game (host) — same slot as Ready |
| 2 | `b_ready_changeteam` | Change Team |
| 3 | `b_ready_exit` | Exit room |
| 4–7 | `b_ready_scroll` | map/list scroll arrows |
| 8, 500 | `b_ready_button` | small toggles |
| 300 | `b_ready_buddy` | buddy panel (disabled) |
| **100+i** | `b_ready_character` | **character/mobile picker** — a 5-column grid (`(i%5)·0x42+0x21`, `(i/5)·0x32+0x184`), 66×50 cells; `i==0xd` disabled |

## Input & the command dispatcher — `State09_ReadyRoom_OnCommand` (`0x4d54e0`)
Every button/control/chat-commit funnels through this (slot 5),
`(this, eventType, _, buttonId)`:
- `eventType==0` → button `buttonId` (table below).
- `eventType==10` → **chat commit**: copies the typed text and, if not a
  slash-command (`FUN_00415b00`), **sends it as chat — opcode `0x3104`** (via
  `FUN_004d2530`/`FUN_004d2680`). *(This resolves the earlier "chat-send call
  not found" item — it's a normal queued packet, not raw Winsock.)*
- `eventType==0xb` → cancel/dismiss.

**buttonId → action / outgoing opcode:**
| ID | Action | Opcode |
|---|---|---|
| 0 | Ready toggle | `0x3230` |
| 1 | Start Game (host) | `0x3430` |
| 2 | Change Team | `0x3210` |
| 3 | Exit room | `0x2000` |
| 4/5 | map/list scroll | `0x3100` |
| 0x14–0x17 | room setting | `0x3103` |
| 0x3c–0x3e | room setting (settings-dword bits) | `0x3101` |
| 0xb–0x3e (various) | room-option toggles → bit-pack a room-settings dword via `QueueOutgoingPacketField` | — |
| 0x46/0x47 | change map (map index) | (`QueueOutgoingPacketField`) |
| **100–113** | **select character** (`id−100`) | **`0x3200`** |
| 0x72 | select random/none | `0x3200` (0xff) |
| 300 | buddy panel (`BuildBuddyPanel`) | — |

- **`/`-commands**: shared parser `FUN_004218c0` — staff-credits easter eggs
  (`/comsik`, etc.), GM/debug commands (`noack`, `clear`, `logging`), and three
  Korean-2beolsik-encoded GM commands gated on `g_currentGameState==9`.
- **`State09_ReadyRoom_HandleChatInput`** (`0x4d6210`, slot 6): the raw
  `WM_KEYDOWN`/Enter textbox handler that also logs chat to the replay stream;
  the committed text reaches the dispatcher's `eventType==10` path above.

## Network (see PROTOCOL.md — "State 9")
**Outgoing (from the command dispatcher):** `0x3230` (ready), `0x3430` (start,
host), `0x3210` (change team), `0x3200` (select character), `0x3104` (chat),
`0x3101`/`0x3103` (room-option changes), `0x3100` (map/list scroll), `0x2000`
(exit). Incoming player/room updates arrive via `State09_ReadyRoom_ProcessPacket`
(`0x4d38c0`). All new to PROTOCOL.md's "State 9" section.

## Transitions
- **In**: from Game Room List (room join).
- **Out**: → Loading (state 10) → In-Battle when the match starts.

## Reimplementation checklist
1. Construct the 0x78c state object; preload avatar/character/effect textures;
   load `ready_selectmap.img` / `ready_selectcharacter.img` / `b_ready_startgame`.
2. Render: character preview + 8-slot roster (ready bits) + paginated item grid
   (3×3, page at `+0x620`) + map thumbnails.
3. Item lookup: item ID → sprite via `&DAT_0056dc40`.
4. Character picker: grid of `b_ready_character` buttons (id `100+i`) → select
   sends `0x3200`. Ready → `0x3230`, Start → `0x3430`, Team → `0x3210`.
5. Chat: Enter → command parse (`/`) else send via the dispatcher's chat-commit
   path → opcode `0x3104` (and log to replay).

## Resolved (were open items)
- **Character/mobile picker — found.** It's the `b_ready_character` button grid
  (ids `100+i`); clicking one sends **`0x3200`** with the character index.
  `RenderCharacterPreview` then shows the selected mobile.
- **Chat-send call — found.** Ready-room chat is a normal queued packet,
  **opcode `0x3104`**, sent from `State09_ReadyRoom_OnCommand`'s chat-commit
  path — not the raw-Winsock guess in the earlier draft. (Whisper/`/message`
  still uses the separate TCP "Channel 3", `FUN_00402720`.)

## Room-option controls (host) — `0x3101` / `0x3103`
The host-only room-config controls dispatch to two different sends:

- **`0x3103` — room player capacity** (cases `0x14`–`0x17`): sets a byte at
  `this+0x230` to `4` / `6` / `8` (case `0x17` computes `((count+1)/2)*2`) and
  sends it — the 4/6/8-player room-size selector.
- **`0x3101` — room-options bitfield dword** (cases `0xb`–`0x3e`): each control
  is a radio group that clears its own bit range and sets the chosen value in a
  single settings dword (read via `FUN_0040a4d0(this+0x26c)`), pushed with
  `QueueOutgoingPacketField`. Confirmed **bit-group layout** (values written by
  consecutive case IDs; exact per-option *labels* need the config-panel strings
  and aren't decoded):
  | Dword bits | Mask | Control (cases) |
  |---|---|---|
  | 0–3 | `0x0000000f` | option group A (`0x28`–`0x2a`) |
  | 8–11 | `0x00000f00` | option group B (`0x1e`–`0x21`) |
  | 12–13 | `0x00003000` | option group C (`0x32`–`0x35`) |
  | 14–15 | `0x0000c000` | option group D (`0x3c`–`0x3e`); `0x3c` also commits |
  | ~18–23 | `0x00fc0000` | option group E (`0xb`–`0xd`) |

  These are the classic GunBound room settings (game type, item/tank
  restrictions, etc.); which group is which isn't determinable from the
  bit-packing alone.

## Still open
- Per-option semantics of the `0x3101` bitfield groups above (need the
  room-config panel's button labels/strings).
- Vtable slots 18 (`0x40ca00`) / 19 (`0x461c60`) are **inherited base-class
  infra**, not Ready-Room UI: slot 18 is a secondary scalar-deleting destructor
  thunk (→ `FUN_004711e0`), slot 19 (`0x461c60`) a small resource/connection
  poll (reads `+0x1c`, calls `FindStringNoCase`, sets `+0x20`/`+0x24`/`+0x34` — the
  same field shape as the connection object). Neither is screen-specific.
