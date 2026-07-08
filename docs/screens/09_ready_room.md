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

## Rendering (three panels)
- **Character preview** — `State09_ReadyRoom_RenderCharacterPreview` (`0x4d90c0`,
  2,575 bytes): draws a live preview of the **currently selected** character/
  avatar using the avatar/character/effect texture families.
- **Roster + item picker** — slot 13 (`FUN_004d7db0`, 4,854 bytes):
  - **8-player ready roster**, 2 rows × 4 cols, using the per-slot
    `PeekPacketChecksumState()` bit idiom (same as Loading) to show who's ready.
  - **Paginated item-loadout grid**: 9 slots/page (3×3, spacing
    `(i%3)*0x46+0x210` / `(i/3)*0x2d+0x193`), item IDs from `this+0x518`,
    sprite via the global item-ID→sprite table `&DAT_0056dc40`, labels via
    `FUN_004ed9f0`. Current page at `this+0x620`, item count at `this+0x61c`.
- **Map thumbnails** — slot 15 (`FUN_004d9ae0`, 2,406 bytes): draws content at
  six fixed screen positions — most plausibly the map-selection thumbnails
  (strong inference; not cross-checked against `ready_selectmap.img`).
- Remaining slots: `0x4d54c0` (20-byte ready-status check), `0x4d54e0`
  (3,167-byte button enable/disable updater), `0x4d7b20` (texture preload).

## Input
- **Keyboard/chat** (`0x4d6210`): Win32 handler (`WM_KEYDOWN`, Enter). On Enter,
  reads the chat textbox; non-command text is logged to the replay stream
  (`Replay_AppendEvent(1)` + `Replay_AppendString` + `Replay_FlushEvent`) and
  the textbox cleared. **Note**: the actual chat-packet *send* call is not on
  this path — see the open item below.
- **`/`-commands**: shared parser `FUN_004218c0` — staff-credits easter eggs
  (`/comsik`, etc.), GM/debug commands (`noack`, `clear`, `logging`), and three
  Korean-2beolsik-encoded GM commands gated on `g_currentGameState==9`.

## Network (see PROTOCOL.md — "State 9")
`0x3010` (match-start replay snapshot + team-based spawn setup), `0x3020`
(ready/unready toggle), `0x3105` (player joined ready room), plus the
per-field player updates. Full list in PROTOCOL.md.

## Transitions
- **In**: from Game Room List (room join).
- **Out**: → Loading (state 10) → In-Battle when the match starts.

## Reimplementation checklist
1. Construct the 0x78c state object; preload avatar/character/effect textures;
   load `ready_selectmap.img` / `ready_selectcharacter.img` / `b_ready_startgame`.
2. Render: character preview + 8-slot roster (ready bits) + paginated item grid
   (3×3, page at `+0x620`) + map thumbnails.
3. Item lookup: item ID → sprite via `&DAT_0056dc40`.
4. Chat: Enter → command parse (`/`) else log-to-replay + send; ready toggle
   sends `0x3020`; handle `0x3010` match-start.

## Open items
- **Character/mobile selection picker** (chooses *which* character
  `RenderCharacterPreview` shows) was not located — the preview renders the
  current selection but the click-driven picker UI wasn't found.
- **Normal chat-message send call** not found on the chat path (likely a raw
  Winsock `send()` outside the queued-packet API). Whisper/`/message` uses a
  separate TCP "Channel 3" (`FUN_00402720`) — see PROTOCOL.md.
