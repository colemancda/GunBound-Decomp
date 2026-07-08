# The reusable UI-widget system

GunBound's screens are built from a small set of **reusable widget classes**
plus per-screen **panel compositions**. This document covers the widget classes
themselves (the reusable part); per-screen usage lives in
[docs/screens/](screens/README.md).

There are actually **two** widget systems in the client:

1. **`ButtonWidget`** (vtable `0x551e44`, ctor `CreateButtonWidget` `0x406020`)
   — the flat 80-byte sprite buttons used for the bottom-bar buttons on most
   screens. Documented in [screens/README.md](screens/README.md#the-generic-ui-widget-system).
2. **The container/panel widget hierarchy** (the `0x557bxx`–`0x557fxx` vtable
   family) — a richer, composable tree of panels, lists, labels, text fields,
   and scrollbars. **This document is about that second system.**

---

## The base widget class

Every widget in the container hierarchy shares a **12-slot vtable** and a common
object header. Concrete classes override the input/render slots; the base
methods (hit-test, child broadcast, drag, callback dispatch) are shared verbatim
across classes.

### Common object fields
| Offset | Field |
|---|---|
| `+0x00` | vtable pointer |
| `+0x08` | **parent** object pointer (callback target) |
| `+0x0c` | children array pointer (containers) |
| `+0x10` | children count (containers) |
| `+0x1e` | hidden/disabled flag (short-circuits hit-tests and draw) |
| `+0x24` | **widget id** (passed to the parent callback) |
| `+0x28` / `+0x2c` | x / y |
| `+0x30` / `+0x34` | width / height |
| `+0x38` | class-specific (text buffer / scrollbar total items) |
| `+0x39` | dragging flag (base drag support) |
| `+0x3c` / `+0x40` | class-specific (base: last drag x/y; label: sprite/msg id; scrollbar: page size / scroll position) |

### Vtable slots (12)
Confirmed by dumping the label (`0x557da0`), text-entry (`0x557c84`),
scrollbar (`0x557e90`), and panel (`0x557f08`) vtables:

| Slot (off) | Role | Shared base impl |
|---|---|---|
| 0 (`+0x00`) | destructor | `0x50e860` (most classes) |
| 1 (`+0x04`) | mouse-move | per-class; base drag = `FUN_0050e3a0` (slot 11 in some) |
| 2 (`+0x08`) | mouse-down | per-class (e.g. label `FUN_005052e0`, scrollbar `FUN_0050f500`) |
| 3 (`+0x0c`) | mouse-up | per-class |
| 4 (`+0x10`) | **hit-test** | `FUN_0050e9c0` — rect test (`+0x28`/`+0x2c`/`+0x30`/`+0x34`) then broadcast to children |
| 5 (`+0x14`) | keyboard input | `FUN_0050ea50` — broadcast to children's slot 5 |
| 6 (`+0x18`) | mouse input | `FUN_0050eab0` — broadcast to children's slot 6 |
| 7 (`+0x1c`) | **command/callback + focus-nav** | `FUN_0050eb10` (leaf) — receives child callbacks (`0x2000` scroll, `0x1100`/`0x1101` focus move); panels override (e.g. `WorldListPanel_OnCommand`) |
| 8 (`+0x20`) | **draw** | per-class; also broadcasts draw to children (container base `FUN_0050e520`) |
| 9 (`+0x24`) | secondary render / per-class hook | per-class (e.g. panel row-loop `0x50dc40`) |
| 10 (`+0x28`) | secondary destructor | `0x50e860` |
| 11 (`+0x2c`) | base drag mouse-move | `FUN_0050e3a0` |

### The event model — the `+0x1c` callback
This is the spine of the whole system. When a leaf widget is activated it calls
its **parent's** slot-7 method (`parent.vtable[+0x1c]`) with
`(eventType, widgetId, extra)`:

- **Label / button click** → `FUN_005052e0` (mouse-down) fires
  `parent[+0x1c](0, id, 0)` — event type **0** = "clicked", `id` = the widget's
  `+0x24`.
- **Scrollbar change** → fires `parent[+0x1c](0x2000, id, newScrollPos)`.
- **Text-entry / dialog commit / cancel** → event types **10** / **0xb**.

A **panel's** slot-7 either handles the event itself or forwards it to the
**owning game state's command dispatcher** — which is exactly why those
dispatchers have the shape `(this, eventType, _, id)` and switch on
`eventType`+`id`:
- Lobby: `FUN_004285c0` (State 3).
- Ready Room: `State09_ReadyRoom_OnCommand` (`0x4d54e0`).
- Server select panel: `WorldListPanel_OnCommand` (`0x50d810`).

### Render model
`GameTick` walks the active panels; each panel's **slot 8** draws itself and
broadcasts draw to its children (container base `FUN_0050e520` calls each
child's `+0x20`). Leaf widgets blit through the shared sprite-frame resolver
`FUN_004f30c0` + `BlitSprite16bpp`/`BlitSpriteClipped`. There is no per-screen
"draw everything" function — the tree draws itself.

---

## The reusable widget classes

### Container / panel
The tree nodes. Hold a child array (`+0xc`/`+0x10`), broadcast input and draw to
children, and forward child callbacks upward via slot 7. Each concrete panel is
its own class (own vtable) but shares the container base behavior. Built by the
panel-builder catalog below.

### Label / small button — `FUN_00507ee0` (`0x557da0`, 0x40 bytes)
A sprite/text cell. Constructor `(id, spriteOrMsgId, x, y, w, h)` → stores
`id`→`+0x24`, `spriteId`→`+0x3c`, rect→`+0x28..+0x34`. Mouse-down
(`FUN_005052e0`) hit-tests and fires `parent[+0x1c](0, id, 0)` on click — this
is how menu/tab/grid cells report clicks. Used for tabs, icons, grid cells
(e.g. the Ready Room character grid, the Avatar Store category tabs).

### Text entry — `FUN_00507f60` (`0x557c84`, 0x140 bytes)
An editable text field **backed by a real Win32 `EDIT` control** overlaid on the
DirectDraw surface. Slot 8 (`FUN_00507030`) syncs the OS control's text into the
widget's internal buffer at `+0x38` via `GetWindowTextA(hwnd, this+0x38, 0x80)`.
Constructor `(id, msgId, x, y, w, maxLen)`. Used for the Create Room name/
password fields, the "enter room by number" field, and chat input.

### Scrollbar — `FUN_005080a0` = `CreateScrollListWidget` (`0x557e90`, 0x58 bytes)
A fixed **18-px-wide vertical scrollbar** (the `w` argument is `0x12` in every
call). Owns scroll position (`+0x40`), total items (`+0x38`, via register), page
size (`+0x3c`), and auto-creates its own up/down arrow child buttons. Draggable
thumb (`ScrollListWidget_OnMouseDown`/`_OnMouseMove`), ±1 arrow steps
(`0x50f7c0`), auto-scroll while held past the ends. Fires `parent[+0x1c](0x2000,
id, pos)` on change. **The widget owns only the scrollbar and position; the
parent panel owns the list content** and decides what a scroll means (redraw a
local slice, or request the next network page). See
[screens/README.md](screens/README.md) "reusable scrollbar widget".

---

## Panel-builder catalog

Each builder allocates a container of its own class and populates it with the
leaf widgets above. All register with the global UI panel manager
(`g_uiPanelManager`, formerly `DAT_00e53c40`).

| Builder | vtable | Screen — panel | Composition |
|---|---|---|---|
| `BuildWorldListPanel` (`0x5099d0`) | `0x557f08` | State 2 — server WORLD LIST | 2 buttons (View All / Friends) + scrollbar; rows drawn by `RenderWorldListRow` |
| `FUN_00509110` | `0x557be4` | shared — **buddy list** (lobby / ready room / WndProc) | buddy list + scrollbar |
| `FUN_00509af0` | `0x557cd4` | State 3 — lobby **chat** panel | wide text-entry (`0x1e4` px) + label + scrollbar |
| `FUN_00509d80` | `0x557cac` | State 3 — lobby list panel (user/room list; content not fully pinned) | scrollbar (page 7) |
| `FUN_005094f0` | `0x557ee0` | State 9 — Ready Room list panel | scrollbar (page 9) |
| `FUN_00509e60` | `0x557eb8` | State 7 — Avatar Store item panel | 3 category labels (msg `0x4b0`–`0x4b2`) + scrollbar (page 0xe) |
| `FUN_00509260` | `0x557b94` | **chat log** panel (via `FUN_004025e0`), 0x1050-byte object with a ~4 KB history buffer | label + text-entry |
| `FUN_005087b0` | `0x557df0` | State 3 — "enter room by number" dialog | labels + OK/Cancel + text field |
| `FUN_00508190` | `0x557c34` | State 3 — Create Room dialog | name/password text fields + option grid + OK/Cancel |

Confidence: the widget classes, slot layout, and event model are confirmed by
decompilation. Panel *identities* are confirmed for the ones cross-referenced to
a screen's `OnEnter`/dispatcher; the exact list *content* of `FUN_00509d80` and
`FUN_005094f0` (which of several lists each holds) is inferred from position/
page-size and not fully pinned. Register-passed constructor arguments (e.g. the
scrollbar item count, some panel keys) aren't always visible in the decompile.
