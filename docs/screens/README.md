# Screen documentation — for reimplementation

One document per game screen ("state"), written to be enough to **reimplement
the screen** from scratch: its state, its rendering, its input, and its
network I/O. These distill the relevant parts of [ARCHITECTURE.md](../../ARCHITECTURE.md)
and [PROTOCOL.md](../../PROTOCOL.md) into a per-screen, build-oriented form.
When a doc says "see ARCHITECTURE.md" it means the deep reverse-engineering
evidence lives there; these docs are the actionable summary.

## Index

| State | Screen | Doc | Interactivity |
|---|---|---|---|
| 0 / 15 | Null / Quit | [00_null_and_quit.md](00_null_and_quit.md) | none |
| 5 | Logo 1 (Softnyx splash) | [05_logo1.md](05_logo1.md) | none (auto-advance) |
| 6 | Logo 2 | [06_logo2.md](06_logo2.md) | none (auto-advance) |
| 1 | Title | [01_title.md](01_title.md) | none (auto-advance) |
| 2 | Server / Channel Select | [02_server_select.md](02_server_select.md) | buttons + server list |
| 3 | Game Room List (lobby) | [03_game_room_list.md](03_game_room_list.md) | room grid + buttons |
| 7 | Avatar Store / Shop | [07_avatar_store.md](07_avatar_store.md) | item grid + buttons |
| 9 | Ready Room (pre-battle) | [09_ready_room.md](09_ready_room.md) | char/map/item pickers |
| 10 | Loading | [10_loading.md](10_loading.md) | none (live status) |
| 11 | In-Battle | [11_in_battle.md](11_in_battle.md) | full gameplay |

Boot flow: **Logo1 (5) → Logo2 (6) → Title (1) → ServerSelect (2) →
GameRoomList (3) ⇄ AvatarStore (7)**, and **GameRoomList (3) → ReadyRoom (9)
→ Loading (10) → InBattle (11)**. States 12–14 are reserved/unused.

---

## Shared architecture (read this first)

Everything below is common to all screens; the per-screen docs assume it.

### The state machine

- `g_gameStateVTableArray` (base `0x5b33f8`, aliased `g_gameStateObjects`) is a
  16-slot array of pointers to heap-allocated C++-style state objects, one per
  state. Slots 0 and 15 share a trivial "null-object" vtable (`0x553fb0`).
- `ChangeGameState(int newStateId)` (`0x4122f0`) performs a transition:
  calls the **old** state's `OnExit` (vtable slot 8, `+0x20`), then the **new**
  state's `OnEnter` (vtable slot 7, `+0x1c`), and updates `g_currentGameState`
  (`0x7934d0`).
- Two ways transitions are triggered:
  - **Immediate**: call `ChangeGameState(n)` directly.
  - **Deferred**: set `g_pendingGameState` (`0x5b33ec`) + `g_stateChangeRequested`
    (`0x7934d4`); `GameTick` polls and dispatches next frame.
- **Tick rate ≈ 50 ms** (20 Hz). Frame-count timers throughout assume this
  (e.g. Title auto-advances at 60 ticks ≈ 3 s).

### The `CGameState` base class / vtable

Every state object shares this vtable layout (confirmed across states 1–11).
Slot number does **not** carry a fixed render/input meaning across states past
this base set — slots 9+ are per-state and must be checked individually.

| Slot | Offset | Role |
|---|---|---|
| 0 | +0x00 | scalar-deleting destructor (`CGameState_ScalarDeletingDestructor`, `0x4e5320`; base dtor `CGameState_BaseDestructor` `0x426ac0` re-points the vtable to the null-object vtable when destroyed) |
| 1 | +0x04 | **`ProcessPacket(int payloadLen, ushort opcode, ushort *payload)`** — per-state network dispatcher; no-op (`CGameState_NoOpVirtual_A`, `0x448430`) where a screen needs no networking |
| 2–4 | +0x08..+0x10 | per-state virtuals, usually no-op (`CGameState_NoOpVirtual_B`, `0x4fdef0`) |
| 5 | +0x14 | **keyboard/chat-input dispatcher** (3-arg; dispatches on a Win32 message code as `param_2`, e.g. `0x100`=`WM_KEYDOWN`) |
| 6 | +0x18 | **mouse-input dispatcher** (dispatches on Win32 mouse message codes, `0x202`=`WM_LBUTTONUP`, `0x204`=`WM_RBUTTONDOWN`, …) |
| 7 | +0x1c | **OnEnter** — loads the screen's `.img`/`.mp3` resources, builds widgets |
| 8 | +0x20 | **OnExit** — teardown |
| 9+ | +0x24… | per-state tick/render/update hooks — **no universal meaning** |

### Rendering model

- **No `WM_PAINT`.** `WndProc` (`0x410040`) does zero native painting — the
  DirectDraw7/Direct3D7 pipeline owns 100% of presentation.
- **`GameTick`** locks the back buffer once (`LockBackBuffer`, called only from
  `GameTick`), dispatches the current state's render/tick hooks, then presents
  (`PresentFrame`, `0x4f0070`).
- **Two render paths** (see ARCHITECTURE.md "Rendering"):
  - **Software blitter** (all non-battle screens): `BlitSprite16bpp`,
    `BlitSpriteClipped`, `BlitRLESprite` (bitmap-font/RLE text), operating on
    the locked 16bpp (RGB565) back buffer. Individual draw functions receive
    the already-locked buffer.
  - **Hardware D3D7** (In-Battle only): textured vertex pipeline for the
    battle scene; the HUD/chat overlay still uses the software blitter.
- **Sprites/textures** come from `.xfs` archives (see [FILEFORMATS.md](../../FILEFORMATS.md)).
  A texture is looked up by name via `FindPreloadedTextureByName` /
  `FindSpriteFrame` (cache lookup), then blitted. A negative stored frame index
  (`+0x30` on a widget) is the standard **hidden** sentinel.
- **Text** is drawn with a bitmap font via `BlitRLESprite`; higher-level text
  is prepped via `BlitSpriteText` / `FUN_0041b8c0` (label-text setters) and
  word-wrapped via `RenderWrappedText` (used for server descriptions and dialog
  message bodies).

### The generic UI-widget system

> **See [../widgets.md](../widgets.md)** for the full reusable-widget writeup:
> the container/panel class hierarchy, the shared 12-slot base vtable, the
> `+0x1c` parent-callback event model, the four reusable widget classes
> (panel, label/button, Win32-backed text entry, scrollbar), and the panel-
> builder catalog. The summary below covers the flat `ButtonWidget` layer.

Three layers (all confirmed — see ARCHITECTURE.md "The generic UI-widget system"):

1. **`AppendPersistentButtonName`** (`0x401740`) registers a button-name string
   into a shared, session-wide, count-prefixed array (`&DAT_0067ec70 + session`).
   `ChangeGameState` registers 9 **persistent, cross-screen** widgets on every
   transition: the buddy-list scroll controls (`b_gamelist_buddyup/down`,
   `b_buddy_up/down/exit`) and the global **`b_error_confirm`** dialog button.
2. **`LoadButtonDefinitionFromXFS`** (`0x401440`) loads a named button
   definition from `graphics.xfs`. On-disk record format:
   ```
   uint32 count
   repeat count:
     uint32 nameLen
     char   name[nameLen]      // NOT NUL-terminated on disk
     uint8  typeByte
     uint32 subCount
     uint32 arrayA[subCount]   // likely hit-region / offset data
     uint32 arrayB[subCount]
   ```
3. **`CreateButtonWidget`** (`0x406020`) constructs an **80-byte** button object
   with the shared `vtable_ButtonWidget` (`0x551e44`). Signature (as seen at
   every call site):
   ```c
   CreateButtonWidget(list, group, buttonId, actionCode,
                      imageName, x, y, w, h, enabled, param11);
   ```
   `ButtonWidget` field map (offsets into the 80-byte object):
   | Off | Field |
   |---|---|
   | +0x00 | vtable ptr |
   | +0x04 | group |
   | +0x08 | button ID |
   | +0x18 | action code |
   | +0x1C | texture handle |
   | +0x24 | visual state (`"disable"`/`"active"`/`"ready"`) |
   | +0x30 | current frame index (negative = hidden) |
   | +0x38 / +0x3C | x / y |
   | +0x40 / +0x44 | width / height |
   | +0x4C | "ready" flag byte |

   **`vtable_ButtonWidget` slots** (5): slot 0 scalar-deleting dtor; slot 1
   timing fields; **slot 2** (`0x405e90`) advances animation state via the
   generic sprite-animation ticker `AdvanceSpriteAnimation` (frame timer → frame index
   at `+0x30`); **slot 3** (`0x405ea0`) is the actual draw (reads `+0x30`
   frame, `+0x38`/`+0x3C` position, blits via `FindSpriteFrame` +
   `BlitSprite16bpp`/`BlitSpriteClipped`); slot 4 is a no-op `RET`.
   Animation and drawing are cleanly split (slot 2 = advance, slot 3 = draw).

   Buttons draw themselves through a **generic active-object sweep** (there is
   no per-screen "draw everything" function for widgets); the state's own
   render slot draws the non-widget chrome (background, grids, labels).

### The reusable scrollbar widget (`CreateScrollListWidget`, `0x5080a0`)

A single **vertical-scrollbar** widget class (vtable `0x557e90`, 0x58-byte
object) is reused by every scrollable list in the game. It is created by
`CreateScrollListWidget(container, x, y, w, h, pageSize)` — `w` is always
`0x12` (an 18-px-wide track), and the total item count arrives in a register
(`+0x38`). It builds its own **up/down arrow** child buttons and manages:
`+0x40` scroll position, `+0x38` total, `+0x3c` page size, `+0x28`/`+0x2c`/
`+0x30`/`+0x34` track rect. Input: draggable thumb (`ScrollListWidget_OnMouseDown`
/`OnMouseMove`), ±1 arrow steps (`0x50f7c0`), auto-scroll while held past the
ends. On any change it fires a **`0x2000` + new-position callback** to its
parent panel.

**Confirmed reuse — 7 instances across 5 screens:**
| Builder | Screen / list |
|---|---|
| `BuildWorldListPanel` (`0x5099d0`) | State 2 — server WORLD LIST |
| `BuildBuddyPanel` | shared **buddy list** (lobby / ready room / WndProc) |
| `BuildLobbyChatPanel`, `BuildChannelUserListPanel` | State 3 — lobby panels |
| `BuildReadyRoomChatPanel` | State 9 — Ready Room list |
| `BuildAvatarStorePanel` | State 7 — Avatar Store list |
| `BuildChatLogPanel` | a panel via `FUN_004025e0` |

The widget owns only the scrollbar chrome and the scroll *position*; the
**parent panel owns the list content** and decides what to do on the `0x2000`
callback (draw a different slice locally, or request the next page over the
network as State 2's server list does). That clean split is why one class
serves a network-paginated list, a local buddy list, and item grids unchanged.

### The client context arena (`g_clientContext`)

Most per-screen game data lives at fixed byte offsets inside one large global
arena reached through the base pointer **`g_clientContext`** (formerly
`DAT_005b3484`; a raw address in a `uint32_t`, arena built by `FUN_00415d40`).
It holds the outgoing packet buffer (`+0x4d0`, length cursor `+0x44d0`),
Winsock socket handles (`+0x84e0`), critical sections, room/player/whisper
state, and per-screen scratch (e.g. the server-list SoA at `+0x3f808`). There
appear to be two such arenas double-buffered via `DAT_007934ec` /
`DAT_007934e8` (swapped on server change); `g_clientContext` tracks the active
one. Screen docs give offsets relative to `g_clientContext`.

### Error / message dialog (shared)

Errors surface through a **generic popup**, `ShowErrorDialog`, not per-screen code:
- The screen stores an error/message code, then something calls
  `ShowErrorDialog(closeSockets)` with the message index in `EAX`.
- It looks up a localized message string via `GetLocalizedString(&g_localizedStringTable,
  code + 0xc7)`, word-wraps it with `RenderWrappedText` into buffer `DAT_005b1d70`,
  sets the dialog rect in `_DAT_00e53c24..30` = `{0xf9, 0x229, 0xc1, 0x171}`,
  and creates the shared **`b_error_confirm`** OK button at (0x1c6, 0x14b),
  size 0x4a×0x1a. `ClampCursorToRect()` activates the panel.
- If `closeSockets != 0` it tears down the game sockets.

**Two display forms.** `ShowErrorDialog` is the in-game styled dialog. Separately,
the incoming-packet pump (`ProcessIncomingPackets`) shows some server-reported status/
error codes via a **native Win32 `MessageBoxA`** (same localized-string source,
`GetLocalizedString`). Which one is used depends on the code and whether a target
`HWND` is available.

**Connection errors** don't have their own widget — the async connect result is
reduced to a flag (`conn+0x84e5`, "connected") by the connection-state poller
`ProcessIncomingPackets`, and the owning screen's tick calls `ShowErrorDialog` when that flag
is clear after the attempt finishes. See
[02_server_select.md](02_server_select.md) "Errors" for the worked example.
