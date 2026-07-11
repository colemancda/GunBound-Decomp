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
    item's value appears in the table verbatim). **What indexes it —
    resolved:** `this+0x518` holds the compact item index 0–63 (also the
    `DAT_0056dc40` index and the ownership-bitmask bit). The loadout builder
    `FUN_004dbd50` scans the 64-bit item-ownership bitmask the server pushes
    to `g_clientContext+0x457a1` and packs each owned index into `+0x518`
    (count `+0x61c`, cap 11); items 0–10 are battle-usable. Per-cell quantity
    is a guarded lookup (`FUN_0041e9a0`) keyed by the icon value. The
    ordinal→item identity is recovered from client data by matching each
    `DAT_0056dc40` icon code to a record's `0x30` field in `itemdata.dat`
    (`tools/lzhuf/decode_item.py`): **ord 0–10 = Dual, Blood, Energy up 2,
    Energy up 1, Dual+, Change Wind, Team Teleport, Bunge shot, Power up,
    Thunder, Teleport**. See PROTOCOL.md "Item availability" and ARCHITECTURE.md.
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
- **`0x3101` — room-options bitfield dword** (cases `0xa`–`0x3e`): each control
  is a radio group that reads the guarded settings dword
  (`PeekChecksumStateUnderLock(this+0x26c)`), clears its own bit field, ORs in the
  chosen value, and re-sends the whole dword with opcode `0x3101`. **Full bit
  layout + per-case values decoded** from `State09_ReadyRoom_OnCommand`
  (`0x4d54e0`):

  | Bits | Mask | Group | Case → value |
  |---|---|---|---|
  | 0–3 | `0x0000000f` | A (3-way) | `0x2a`→0 · `0x28`→1 · `0x29`→2 |
  | 8–11 | `0x00000f00` | B (4-way) | `0x21`→0 · `0x1e`→1 · `0x1f`→2 · `0x20`→3 |
  | 12–13 | `0x00003000` | C (3-way) | `0x32`/`0x35`→1 · `0x33`→2 · `0x34`→3 |
  | 14–15 | `0x0000c000` | D (2-way) | `0x3c`/`0x3e`→1 (`0x4000`) · `0x3d`→2 (`0x8000`) |
  | 16–17 | `0x00030000` | map-variant | cases `0x46`–`0x48`: cycles `(cur+1) % N`, `N = DAT_0056d350[mapId]` |
  | 18–23 | `0x00fc0000` | E — game mode | `0xd`→0 · `0xb`→`0x80000` · `0xc`→`0xc0000` · `0xa`→`0x440000` |

  So the *encode* is fully pinned — a reimplementation can read `this+0x26c`,
  extract each group by its mask, and drive the buttons. What is **not** in the
  code is which on-screen label (**A SIDE / SSDEATH / ATTACK / DEATH72**) is which
  group: the host room-config toggles are **image-mapped hit regions in a popup**,
  not `CreateButtonWidget` widgets, so there's no sprite→label→case link to trace
  (the toggle art is in the option `.img`, keyed by hit-test coordinates). Binding
  label→group is a one-shot live correlation: click each labeled toggle and read
  which bit field of `this+0x26c` changes. (Group E = the game-mode radio is the
  one already inferred; the 16–17 field tracks a per-map variant count from
  `DAT_0056d350`.)

## Still open
- **Label→group binding** for `0x3101` groups A–D (A SIDE / SSDEATH / ATTACK /
  DEATH72): the encode + bit masks are decoded (above); only the human label per
  group is unmapped, and it's UI-art (popup hit regions), not a code string —
  resolve with a one-shot live click-and-diff on `this+0x26c`.
- Vtable slots 18 (`0x40ca00`) / 19 (`0x461c60`) are **inherited base-class
  infra**, not Ready-Room UI: slot 18 is a secondary scalar-deleting destructor
  thunk (→ `FUN_004711e0`), slot 19 (`0x461c60`) a small resource/connection
  poll (reads `+0x1c`, calls `FindStringNoCase`, sets `+0x20`/`+0x24`/`+0x34` — the
  same field shape as the connection object). Neither is screen-specific.
