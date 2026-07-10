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
| 0 (`+0x00`) | **SetFocus(bool)** — **confirmed by decompiling `0x50e860`** (headless Ghidra export; the function is vtable-only-referenced so no raw port existed): its whole body is `this->+0x04 = arg`. The base slot-7 focus mover (`0x50eb10`) calls it with `0`/`1` on the focus loser/gainer; `CEditBox`'s `+0x04` flag is the state it toggles. | `0x50e860` |
| 1 (`+0x04`) | mouse-move | per-class; base drag = `FUN_0050e3a0` (slot 11 in some) |
| 2 (`+0x08`) | mouse-down | per-class (e.g. label `Label_OnMouseDown`, scrollbar `FUN_0050f500`) |
| 3 (`+0x0c`) | mouse-up | per-class |
| 4 (`+0x10`) | **hit-test** | `Widget_HitTest` — rect test (`+0x28`/`+0x2c`/`+0x30`/`+0x34`) then broadcast to children |
| 5 (`+0x14`) | keyboard input | `Widget_DispatchKeyToChildren` — broadcast to children's slot 5 |
| 6 (`+0x18`) | mouse input | `Widget_DispatchMouseToChildren` — broadcast to children's slot 6 |
| 7 (`+0x1c`) | **command/callback + focus-nav** | `FUN_0050eb10` (leaf) — receives child callbacks (`0x2000` scroll, `0x1100`/`0x1101` focus move); panels override (e.g. `WorldListPanel_OnCommand`) |
| 8 (`+0x20`) | **draw** | per-class; also broadcasts draw to children (container base `Widget_DrawChildren`) |
| 9 (`+0x24`) | secondary render / per-class hook | per-class (e.g. panel row-loop `0x50dc40`) |
| 10 (`+0x28`) | unknown trivial one-byte setter — `0x50e860`'s decompile (`this->+0x04 = arg`, 3 instructions) rules out any destructor reading; slot 10 resolving to the same address as slot 0 is identical-code folding of another trivial setter. This vtable has **no virtual destructor slot**. | `0x50e860` (folded) |
| 11 (`+0x2c`) | base drag mouse-move | `FUN_0050e3a0` |

### The event model — the `+0x1c` callback
This is the spine of the whole system. When a leaf widget is activated it calls
its **parent's** slot-7 method (`parent.vtable[+0x1c]`) with
`(eventType, widgetId, extra)`:

- **Label / button click** → `Label_OnMouseDown` (mouse-down) fires
  `parent[+0x1c](0, id, 0)` — event type **0** = "clicked", `id` = the widget's
  `+0x24`.
- **Scrollbar change** → fires `parent[+0x1c](0x2000, id, newScrollPos)`.
- **Text-entry / dialog commit / cancel** → event types **10** / **0xb**.
- **Focus navigation** → the leaf slot-7 default (`0x50eb10`) handles
  **0x1100** (next) / **0x1101** (prev) / **0x1102** (set-with-wraparound)
  by scanning children whose `+0x20` type id is **2** (the text-entry
  class) and calling slot 0 (`SetFocus`) with 0/1 on the loser/gainer;
  when focus runs off the end it reports **0x1000** through its own
  (virtual) slot 7. Child lookup is by `(+0x20 type, +0x24 id)` via
  `0x50e620`. The object-field **`+0x20` type id** (not to be confused with
  the vtable's `+0x20` *draw* slot) is **runtime-confirmed** from a live panel
  dump: **`0` = panel/container, `1` = label/button (`0x557da0`), `2` =
  text-entry (`0x557c84`), `3` = static text / message block (`0x557f30`, the
  multi-line prompt text in dialogs), `4` = scroll-list (`0x557e90`)**. `+0x24` is the
  per-widget id used for command routing. The `+0x0c` child list is an
  **ATL7 `CAtlArray`**
  (`0x50ed30` is its `GrowBuffer` byte-for-byte, `+0x18` its
  `m_nGrowBy`); the C++ reconstruction lives in src/cxx/.

A **panel's** slot-7 either handles the event itself or forwards it to the
**owning game state's command dispatcher** — which is exactly why those
dispatchers have the shape `(this, eventType, _, id)` and switch on
`eventType`+`id`:
- Lobby: `State03_GameRoomList_OnCommand` (State 3).
- Ready Room: `State09_ReadyRoom_OnCommand` (`0x4d54e0`).
- Server select panel: `WorldListPanel_OnCommand` (`0x50d810`).

### Render model
`GameTick` walks the active panels; each panel's **slot 8** draws itself and
broadcasts draw to its children (container base `Widget_DrawChildren` calls each
child's `+0x20`). Leaf widgets blit through the shared sprite-frame resolver
`FindSpriteFrame` + `BlitSprite16bpp`/`BlitSpriteClipped`. There is no per-screen
"draw everything" function — the tree draws itself.

---

## The reusable widget classes

### Container / panel
The tree nodes. Hold a child array (`+0xc`/`+0x10`), broadcast input and draw to
children, and forward child callbacks upward via slot 7. Each concrete panel is
its own class (own vtable) but shares the container base behavior. Built by the
panel-builder catalog below.

### Label / small button — `CreateLabelWidget` (`0x557da0`, 0x40 bytes)
A sprite/text cell. Constructor `(id, spriteOrMsgId, x, y, w, h)` → stores
`id`→`+0x24`, `spriteId`→`+0x3c`, rect→`+0x28..+0x34`. Mouse-down
(`Label_OnMouseDown`) hit-tests and fires `parent[+0x1c](0, id, 0)` on click — this
is how menu/tab/grid cells report clicks. Used for tabs, icons, grid cells
(e.g. the Ready Room character grid, the Avatar Store category tabs).

### Text entry — `CreateTextEntryWidget` (`0x557c84`, 0x140 bytes)
An editable text field **backed by a real Win32 `EDIT` control** overlaid on the
DirectDraw surface. Slot 8 (`TextEntry_SyncFromControl`) syncs the OS control's text into the
widget's internal buffer at `+0x38` via `GetWindowTextA(hwnd, this+0x38, 0x80)`.
Constructor `(id, msgId, x, y, w, maxLen)`. Used for the Create Room name/
password fields, the "enter room by number" field, and chat input.

### Static text / message block — `0x557f30` (`typeId 3`)
A non-interactive multi-line **text block** used for a dialog's prompt/message
(e.g. the add-buddy dialog's "To add your friends' ID, click his/her ID in the
channel."). Runtime-confirmed as `+0x20` type id `3`; sits in dialog panels as a
plain display element (no click handler). Distinct from the `0x557da0`
label/button (`typeId 1`), which is a clickable sprite/text cell.

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
| `BuildBuddyPanel` | `0x557be4` | shared — **buddy list** (lobby / ready room / WndProc); singleton keyed 20000, at (568,11) 211×267 | Add (`0x2bd`) / Del (`0x2be`) / close-X (`0x2bf`) label buttons + a page-7 scrollbar; res IDs `0x2bc`–`0x2bf` |
| `BuildLobbyChatPanel` | `0x557cd4` | State 3 — lobby **chat** panel (549×259, id 9001) — runtime-confirmed | a 484×12 chat-input `CEditBox` (`0x557c84`, maxLen 80) + **8 "CH 1–8" channel-tab labels** (`0x557da0`, ids 0–7, 22×22) + a page-13 scrollbar |
| `BuildChannelUserListPanel` (`0x509d80`) | `0x557cac` | State 3 — lobby **channel user list** (209-wide) | scrollbar (page 7); rows (`RenderChannelUserRow`) = status flag + rank icon + name per user |
| `BuildReadyRoomChatPanel` (`0x5094f0`) | `0x557ee0` | State 9 — Ready Room **chat log** (480×160, bottom) | scrollbar (page 9); rows (`RenderReadyRoomChatRow`) = color-coded messages by type byte |
| `BuildAvatarStorePanel` | `0x557eb8` | State 7 — Avatar Store item panel | 3 category labels (msg `0x4b0`–`0x4b2`) + scrollbar (page 0xe) |
| `BuildChatLogPanel` | `0x557b94` | **chat log** panel (via `FUN_004025e0`), 0x1050-byte object with a ~4 KB history buffer | label + text-entry |
| `BuildEnterRoomNumberDialog` | `0x557df0` | State 3 — the **"DIRECT GO"** dialog (opened by the "Go To"/`directgo` button, id `0xf`); id 1 at (459,33) 314×160 — runtime-confirmed | **two** text-entry fields (`0x557c84`) — **Room No.** (id 0) + **Password** (id 1) — plus **Ok** (id 0) / **Cancel** (id 1) label buttons |
| (add-buddy dialog) | `0x557e68` | **"add buddy ID" dialog** (from the buddy panel's Add button); id 10000 at (281,206) 241×148 — runtime-confirmed | a `typeId 3` message block (`0x557f30`, "To add your friends' ID…") + a text-entry field (`0x557c84`, id 0) + **ADD** (id 0) / **CLOSE** (id 1) label buttons |
| `BuildCreateRoomDialog` | `0x557c34` | State 3 — Create Room dialog | name/password text fields + option grid + OK/Cancel |

Confidence: the widget classes, slot layout, and event model are confirmed by
decompilation. All nine panel *identities* are now confirmed — the two formerly
"inferred" list panels were pinned by tracing their slot-9 row renderers to the
data they read: `BuildChannelUserListPanel` draws users (status/rank/name from
`g_clientContext+0x44248/+0x42949/+0x43e48`), and `BuildReadyRoomChatPanel`
draws color-coded chat (message-type byte at `+0x3c4d8`). Register-passed
constructor arguments (e.g. the scrollbar item count, some panel keys) aren't
always visible in the decompile.

---

## Runtime-verified panel & dialog layouts

Captured live by walking the widget tree (`tools/debug/gbstate.py`). Each node
reports `(typeId, vtable, id, rect{x,y,w,h}, enabled, focused, hidden)`; rects
are screen pixels on the 800×600 back buffer; ids are per-widget command ids.

**Widget class map** (`+0x20` type id — runtime-confirmed):

| typeId | vtable | class | size |
|---|---|---|---|
| `0` | per-panel (`0x557f08`, `0x557be4`, `0x557cd4`, `0x557cac`, `0x557df0`, `0x557e68`, …) | container / panel | varies |
| `1` | `0x557da0` | label / button (clickable sprite/text cell) | `0x40` |
| `2` | `0x557c84` | text-entry (Win32 `EDIT`-backed) | `0x140` |
| `3` | `0x557f30` | static text / message block | — |
| `4` | `0x557e90` | scroll-list (18-px scrollbar + up/down arrows) | `0x58` |

Every scroll-list auto-owns two 18×18 arrow children (`up` id 0, `down` id 1),
omitted below for brevity except where noted.

### WORLD LIST — `BuildWorldListPanel` (`0x557f08`, id 9000) — State 2
```
panel 9000                         (11,13,545,530)
├─ [1] label   id 0  "View All"    (336,504,74,26)
├─ [1] label   id 1  "Friends"     (430,504,74,26)
└─ [4] scroll  id 0                (526,87,18,377)   disabled when list empty
      up (526,59,18,18) · down (526,474,18,18)
   (server rows are custom-drawn by RenderWorldListRow — not widgets)
```

### Buddy list — `BuildBuddyPanel` (`0x557be4`, id 20000) — shared
```
panel 20000                        (568,11,211,267)
├─ [1] label   id 0  close-X       (748,18,22,20)
├─ [1] label   id 1  "Add"         (662,18,39,20)
├─ [1] label   id 2  "Del"         (705,18,39,20)
└─ [4] scroll  id 0                (751,84,18,152)
      up (751,56,18,18) · down (751,246,18,18)
```

### Add-buddy dialog — `0x557e68`, id 10000
```
panel 10000                        (281,206,241,148)
├─ [3] message id 0  prompt text   (302,251,200,30)  "To add your friends' ID…"
├─ [2] edit    id 0  ID input      (331,294,140,12)  focused
├─ [1] label   id 0  "ADD"         (347,313,74,26)
└─ [1] label   id 1  "CLOSE"       (432,313,74,26)
```

### Lobby chat — `BuildLobbyChatPanel` (`0x557cd4`, id 9001) — State 3
```
panel 9001                         (23,287,549,259)
├─ [2] edit    id 0  chat input    (49,522,484,12)   maxLen 80
├─ [1] label   id 0  tab "CH 1"    (287,296,22,22)
├─ [1] label   id 1  tab "CH 2"    (319,296,22,22)
├─ … ids 2–6 …                     (x = 351,383,415,447,479 · 32-px stride)
├─ [1] label   id 7  tab "CH 8"    (511,296,22,22)
└─ [4] scroll  id 0  chat scrollbar(549,350,18,154)
```

### Channel user list — `BuildChannelUserListPanel` (`0x557cac`, id 9002) — State 3
```
panel 9002                         (572,287,209,259)
└─ [4] scroll  id 0                (751,350,18,154)
   (user rows custom-drawn by RenderChannelUserRow)
```

### DIRECT GO dialog — `BuildEnterRoomNumberDialog` (`0x557df0`, id 1) — State 3
Children are placed at **fixed offsets from the panel origin**, so the whole
dialog can be positioned anywhere (two captures put the panel at `(459,33)` and
`(243,202)` with byte-identical relative layout):
```
panel 1                       (w 314, h 160)   (opened by "Go To"/directgo, id 0xf)
├─ [2] edit    id 0  "Room No."   +(99,50)  180×12   focused
├─ [2] edit    id 1  "Password"   +(99,84)  180×12
├─ [1] label   id 0  "Ok"         +(213,118) 82×34
└─ [1] label   id 1  "Cancel"     +(128,118) 82×34
```

**Layout conventions observed across panels:** panels register in
`g_uiPanelManager` and stack (a modal dialog sits on top of the persistent
panels — e.g. the add-buddy dialog over the buddy + world-list panels).
**Child rects are absolute screen coords, but the invariant is each child's
offset from the panel top-left** — the same dialog captured at two positions
keeps identical child offsets (see DIRECT GO), so persistent panels use the
fixed on-screen positions listed above while transient dialogs are re-placed
per open. Scroll-lists are `enabled:false` while their content is empty. The
panel `id` scheme is loose — persistent lobby panels use `9000`/`9001`/`9002`,
shared panels a round `10000`/`20000`, and transient dialogs a small local id
(`1`).

---

## Speculative C++ reconstruction

**This section is an educated guess, not confirmed decompilation.** The offsets,
vtable slots, the composite child-list, the callback chain, `CEditBox` being a
Win32 `EDIT`, and the concrete vtable addresses are all real; every method/
member *name* below is invented, and the exact class relationship is inferred.
Target compiler: MSVC 7.1 (VC++ 2003), `__thiscall`, one 12-entry vtable/class.
The design reads as a textbook **Composite pattern** — every widget can hold
children, and containers are just widgets that do.

```cpp
// Base of the container/panel hierarchy (NOT the flat ButtonWidget).
// ~0x38-0x40 bytes; the CLabel subclass is exactly 0x40.
class CWidget {
public:
    virtual void SetFocus(bool active);                // slot 0  (+0x00)  focus/activate hook (0x50e860 trivial default) - see corrected table above
    virtual bool OnMouseMove(int x, int y);            // slot 1  (+0x04)
    virtual bool OnMouseDown(int x, int y);            // slot 2  (+0x08)
    virtual bool OnMouseUp  (int x, int y);            // slot 3  (+0x0c)
    virtual bool HitTest    (int x, int y);            // slot 4  (+0x10)  Widget_HitTest
    virtual bool DispatchKey (int key);                // slot 5  (+0x14)  Widget_DispatchKeyToChildren (broadcasts to children)
    virtual bool DispatchMouse(int msg);               // slot 6  (+0x18)  Widget_DispatchMouseToChildren (broadcasts to children)
    virtual void OnCommand(int evt, int id, int arg);  // slot 7  (+0x1c)  the child->parent callback
    virtual void Draw();                               // slot 8  (+0x20)  self + broadcast to children (Widget_DrawChildren)
    virtual void Update();                             // slot 9  (+0x24)
    virtual ~CWidget();                                // slot 10 (+0x28)  scalar-deleting dtor (0x50e860) - see corrected table above
    virtual bool OnDragMove(int x, int y);             // slot 11 (+0x2c)  FUN_0050e3a0
protected:
    // vtable                                          // +0x00
    CWidget*  m_parent;          // +0x08  callback target for OnCommand
    CWidget** m_children;        // +0x0c  \
    int       m_childCount;      // +0x10   > growable array (ptr / size / capacity; grow = FUN_0050ed30)
    int       m_childCap;        // +0x14  /
    bool      m_hidden;          // +0x1e  short-circuits HitTest/Draw
    int       m_id;              // +0x24  reported to OnCommand
    int       m_x, m_y;          // +0x28, +0x2c
    int       m_width, m_height; // +0x30, +0x34
};

// Clickable sprite/text cell, 0x40 bytes.
class CLabel : public CWidget {          // vtable 0x557da0, ctor CreateLabelWidget(id, sprite, x,y,w,h)
    int m_spriteId;   // +0x3c
    // OnMouseDown (Label_OnMouseDown): if hit, m_parent->OnCommand(0, m_id, 0)
    // Draw (FUN_0050e350): blit sprite via FindSpriteFrame
};

// Win32 EDIT-backed text field, 0x140 bytes.
class CEditBox : public CWidget {        // vtable 0x557c84, ctor CreateTextEntryWidget(id, msg, x,y,w,maxLen)
    char m_text[0x100];  // +0x38  synced from the OS control
    // Update (TextEntry_SyncFromControl): GetWindowTextA(hEdit, m_text, 0x80) - a real Win32
    // EDIT control is overlaid on the DirectDraw surface
};

// Vertical scrollbar, 0x58 bytes.
class CScrollBar : public CWidget {      // vtable 0x557e90, ctor FUN_005080a0(parent, x,y, 0x12, h, pageSize)
    int  m_total;      // +0x38  (arrives in a register)
    int  m_pageSize;   // +0x3c
    int  m_scrollPos;  // +0x40
    bool m_pressed;    // +0x44
    bool m_dragging;   // +0x45
    int  m_grabOffset; // +0x48
    // owns two CLabel up/down arrow children
    // on change: m_parent->OnCommand(0x2000, m_id, m_scrollPos)
};

// Container/dialog - each panel builder subclasses this (own vtable, own fields).
class CPanel : public CWidget {          // e.g. 0x557f08 (world list), 0x557be4 (buddy), 0x557c34 (create room)
    // OnCommand override handles/forwards child events (e.g. WorldListPanel_OnCommand 0x50d810);
    // dialog sizes 0x90-0x9c; the chat-log panel is ~0x1050 (embeds a ~4 KB history buffer)
};
```

### What's solid vs. guessed
- **Solid** (decompiled): all offsets, the 12-slot vtable, the composite
  child-list, the `OnCommand(evt,id,arg)` callback chain, `CEditBox` being a
  Win32 `EDIT`, `CScrollBar`'s fields, the concrete vtable addresses.
- **Guessed**: every method/member *name*; that it is literally
  single-inheritance `CWidget` — slot 0 **and** slot 10 both resolve to
  `0x50e860`, which could indicate a small multiple-inheritance base or just a
  shared trivial destructor (can't tell); whether `m_children` is a raw array or
  an STL/custom `vector` (the grow helper `FUN_0050ed30` looks hand-rolled
  `ptr/size/cap`, so probably a custom `CArray`-style template).
- The flat **`ButtonWidget`** (vtable `0x551e44`, 5 slots) is a *separate,
  simpler* class, not part of this hierarchy — the client had (at least) two UI
  widget systems.
