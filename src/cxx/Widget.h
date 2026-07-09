/* CWidget - the container/panel UI-widget hierarchy (the 0x557bxx-0x557fxx
 * vtable family). Reconstruction of docs/widgets.md; see src/cxx/README.md
 * for conventions and confidence levels.
 *
 * CONFIRMED: the 12-slot vtable order, the field offsets, the composite
 * child list, the OnCommand(evt,id,arg) child->parent callback chain, the
 * concrete object sizes (CLabel 0x40, CEditBox 0x140, CScrollBar 0x58).
 * GUESSED: every name; literal single inheritance.
 *
 * NOTE: this is the rich panel hierarchy, NOT the flat 80-byte ButtonWidget
 * (vtable 0x551e44, ctor CreateButtonWidget 0x406020) - that is a separate,
 * simpler system.
 */
#ifndef GB_CXX_WIDGET_H
#define GB_CXX_WIDGET_H

#include "gb_common.h"
#include "AtlArray.h"

/* Base of the composite tree. Every widget can hold children; containers
 * are just widgets that do. Declaration order below IS the confirmed
 * binary vtable order (dumped from the label/text-entry/scrollbar/panel
 * vtables). Base impls named where shared verbatim across classes. */
class CWidget {
public:
    /* The base construction state, inlined into every factory
     * (CreateLabelWidget 0x507ee0, CreateTextEntryWidget, ...): child
     * array and parent null, +0x04 clear, +0x1c gate DEFAULT ON,
     * +0x1d/+0x1e clear. The type id, id and rect are deliberately NOT
     * initialized here - every factory assigns them from its arguments
     * (matching the binary, which leaves them uninitialized in between). */
    CWidget() : m_focused(0), m_parent(0), m_enabled(1), m_unk1d(0), m_hidden(0) {}

    /* SLOT 0/10 CORRECTION (supersedes docs/widgets.md's original
     * table): 0x50e860, freshly exported from Ghidra, is three
     * instructions - `this->m_focused = arg` - so slot 0 is
     * SetFocus(bool), NOT a destructor (the focus mover 0x50eb10 calls
     * it with 0/1 on the loser/gainer). Slot 10 resolving to the same
     * address is identical-code folding of another trivial one-byte
     * setter, not a "secondary destructor"; this vtable has NO virtual
     * dtor slot at all. */
    virtual void SetFocus(bool active);                 /* slot 0  +0x00: 0x50e860 - promoted, Widget.cpp */
    virtual bool OnMouseMove(int x, int y);             /* slot 1  +0x04: per-class */
    virtual bool OnMouseDown(int x, int y);             /* slot 2  +0x08: per-class (Label_OnMouseDown, scrollbar 0x50f500) */
    virtual bool OnMouseUp(int x, int y);               /* slot 3  +0x0c: per-class */
    virtual bool HitTest(int x, int y);                 /* slot 4  +0x10: Widget_HitTest - rect test then child broadcast */
    virtual bool DispatchKey(int key);                  /* slot 5  +0x14: Widget_DispatchKeyToChildren */
    virtual bool DispatchMouse(int msg);                /* slot 6  +0x18: Widget_DispatchMouseToChildren */
    virtual void OnCommand(int evt, int id, int arg);   /* slot 7  +0x1c: THE event spine - children call
                                                         * parent->OnCommand(evt, childId, arg): evt 0 = click,
                                                         * 0x2000 = scroll change, 0x1100/0x1101 = focus move,
                                                         * 10/0xb = text commit/cancel. Leaf default 0x50eb10;
                                                         * panels override and forward to the owning state's
                                                         * command dispatcher. */
    virtual void Draw();                                /* slot 8  +0x20: self + child broadcast (Widget_DrawChildren) */
    virtual void Update();                              /* slot 9  +0x24: per-class hook (e.g. panel row-loop 0x50dc40) */
    virtual void v10(bool b);                           /* slot 10 +0x28: same 0x50e860 body as SetFocus
                                                         * (identical-code folded); distinct role unknown */
    virtual bool OnDragMove(int x, int y);              /* slot 11 +0x2c: base drag, FUN_0050e3a0 */

    /* Non-virtual base helpers (real member functions in the binary,
     * called by subclass handlers): */
    bool ResetPressState(int x, int y);   /* 0x50e2f0 - promoted, Widget.cpp: clears the +0x38/+0x04
                                           * flags, broadcasts mouse-UP to children, returns
                                           * consumed-or-inside (shared tail of leaf press handlers) */
    bool MouseMoveChildren(int x, int y); /* 0x50e870 - promoted, Widget.cpp */
    void MoveBy(int dx, int dy);          /* 0x50e730 - promoted, Widget.cpp */
    void AddChild(CWidget *child);        /* 0x50e670 - promoted, Widget.cpp: append (grow-or-throw),
                                           * shift the child from parent-relative to absolute
                                           * coordinates, set its m_parent. Ghidra shows this
                                           * arriving in EBX (custom-register family). */
    void SetEnabled(bool enabled);        /* 0x50e7d0 - promoted, Widget.cpp: recursive; clears the
                                           * +0x04 active flag when disabling */
    int FindChildIndex(int typeId, int id); /* 0x50e620 - promoted, Widget.cpp. NOTE: Ghidra shows
                                             * the args arriving in EDI/ESI (custom-register family);
                                             * returns child count when not found. */
    bool MouseDownChildren(int x, int y); /* 0x50e8e0 - promoted, Widget.cpp */
    bool MouseUpChildren(int x, int y);   /* 0x50e950 - promoted, Widget.cpp */

    /* field offsets confirmed in docs/widgets.md; m_unk* are the
     * undocumented gaps, kept explicit so everything else lands exactly */
    u8       m_focused;      /* +0x04: THE focus/active flag - set by
                              * SetFocus (0x50e860), read by CEditBox::Draw,
                              * dropped by SetEnabled/ResetPressState and
                              * CScrollBar::OnMouseUp */
    u8       m_unk05[3];     /* +0x05 */
    CWidget *m_parent;       /* +0x08: callback target for OnCommand */
    CAtlArray<CWidget *> m_children; /* +0x0c..+0x1b: ATL7 CAtlArray - grow
                              * helper 0x50ed30 IS its GrowBuffer, and the
                              * broadcast loops' inlined AtlThrow guard IS
                              * its checked operator[] (see AtlArray.h) */
    u8       m_enabled;      /* +0x1c: set recursively by SetEnabled (0x50e7d0),
                              * default 1; gates click reporting in
                              * CLabel::OnMouseDown alongside +0x38 */
    u8       m_unk1d;        /* +0x1d */
    u8       m_hidden;       /* +0x1e: short-circuits HitTest and Draw */
    u8       m_unk1f;        /* +0x1f */
    int      m_typeId;       /* +0x20: widget class/type id - focus
                              * navigation (0x50eb10) scans children with
                              * m_typeId == 2 (the text-entry class) */
    int      m_id;           /* +0x24: reported to the parent's OnCommand */
    int      m_x;            /* +0x28 */
    int      m_y;            /* +0x2c */
    int      m_width;        /* +0x30 */
    int      m_height;       /* +0x34 */
    /* +0x38 onward is class-specific (the base drag helpers use +0x39 /
     * +0x3c / +0x40 in classes that enable dragging) */
};

/* Clickable sprite/text cell - tabs, icons, grid cells (Ready Room
 * character grid, Avatar Store category tabs). On hit, mouse-down fires
 * m_parent->OnCommand(0, m_id, 0). */
class CLabel : public CWidget {      /* vtable 0x557da0, size 0x40; factory CreateLabelWidget 0x507ee0 */
public:
    /* Default ctor, inlined (null-guarded) into the 0x507ee0 factory;
     * the factory then pokes id/sprite/rect UNGUARDED - see Label.cpp. */
    CLabel() : m_unk38(0), m_unk39(0) { m_typeId = 1; m_tabSelected = 0; }

    virtual bool OnMouseDown(int x, int y);  /* 0x5052e0 - promoted, Label.cpp */
    virtual void Draw();                     /* 0x50e350 - promoted, Label.cpp: reports evt 1 upward
                                              * (the parent panel blits for it), then child broadcast */

    u8  m_unk38;                     /* +0x38: armed/held flag - gates click AND the per-frame
                                      * evt-1 reports from Draw (the scrollbar arrows' auto-
                                      * repeat rides on this); cleared by ResetPressState */
    u8  m_unk39;                     /* +0x39: (base drag flag slot per docs/widgets.md) */
    u8  m_tabSelected;               /* +0x3a: tab/radio selected flag - WorldListPanel's
                                      * OnCommand flips it between the View All/Friends
                                      * labels, and the builder pre-sets the default tab */
    u8  m_unk3b;                     /* +0x3b */
    int m_spriteId;                  /* +0x3c: sprite/message id; Draw (0x50e350) blits via FindSpriteFrame */
};

/* Editable text field backed by a REAL Win32 EDIT control overlaid on the
 * DirectDraw surface. Update (TextEntry_SyncFromControl) pulls the OS
 * control's text: GetWindowTextA(hwnd, m_text, 0x80). Used for Create Room
 * name/password, enter-room-by-number, chat input. */
class CEditBox : public CWidget {    /* vtable 0x557c84, size 0x140; factory CreateTextEntryWidget.
                                      * Its real signature is (id, x, y, w, h, maxLen) - the msgId in
                                      * docs/widgets.md's sketch isn't stored anywhere. */
public:
    /* Default ctor, inlined into the 0x507f60 factory (same
     * guarded-ctor + unguarded-arg-pokes split as CLabel's). */
    CEditBox() : m_maxLen(0), m_unk13c(0)
    {
        m_typeId = 2;
        for (int i = 0; i < 0x100; ++i) m_text[i] = 0;
    }

    virtual void Draw();             /* 0x507030 TextEntry_SyncFromControl - promoted, EditBox.cpp */

    char m_text[0x100];              /* +0x38: synced from the EDIT control */
    int  m_maxLen;                   /* +0x138: factory's 6th argument */
    int  m_unk13c;                   /* +0x13c */
};

/* Fixed 18-px-wide vertical scrollbar (w is 0x12 in every call). Owns its
 * up/down arrow children and the scroll position; the PARENT owns the list
 * content and decides what a scroll means. Fires
 * m_parent->OnCommand(0x2000, m_id, m_scrollPos) on change. */
class CScrollBar : public CWidget {  /* vtable 0x557e90, size 0x58; ctor CreateScrollListWidget 0x5080a0 */
public:
    /* Default ctor, inlined (null-guarded) into the 0x5080a0 factory:
     * type id 4, total -1, pageSize/scrollPos 0, both press modes clear. */
    CScrollBar() : m_total(-1), m_pageSize(0), m_scrollPos(0), m_pressed(0), m_dragging(0)
    {
        m_typeId = 4;
    }

    virtual bool OnMouseDown(int x, int y);  /* 0x50f500 - promoted, ScrollBar.cpp */
    virtual bool OnMouseUp(int x, int y);    /* 0x50f5f0 - promoted, ScrollBar.cpp */
    virtual void OnCommand(int evt, int id, int arg); /* 0x50f7c0 - promoted, ScrollBar.cpp: the +/-1
                                              * arrow stepper (exported via Ghidra DecompileAt) */
    virtual void Draw();                     /* 0x50f660 - promoted, ScrollBar.cpp. Bound to slot 8
                                              * from its shape (ends in the child +0x20 draw
                                              * broadcast, same as the other Draw overrides);
                                              * dumping vtable 0x557e90 to pin slot 8 vs 9 is
                                              * still open. */

    bool IsOverThumb(int x, int y);  /* 0x50f770 - promoted, ScrollBar.cpp. NOTE: Ghidra shows y
                                      * arriving in EBX (custom register use); see ThumbHeight. */
    int ThumbHeight();               /* 0x50e050 - promoted, ScrollBar.cpp. NOTE: Ghidra shows the
                                      * original receiving this in EAX (in_EAX), not ECX - a custom
                                      * convention to sort out when byte-matching this one. */

    int m_total;                     /* +0x38: total items (arrives in a register) */
    int m_pageSize;                  /* +0x3c */
    int m_scrollPos;                 /* +0x40 */
    u8  m_pressed;                   /* +0x44: armed on press outside the thumb (arrow auto-repeat) */
    u8  m_dragging;                  /* +0x45: thumb grabbed */
    u8  m_pad46[2];                  /* +0x46 */
    int m_grabOffset;                /* +0x48: thumbTop - mouseY at grab time */
    int m_lastX;                     /* +0x4c: last mouse x (stored by both handlers) */
    int m_lastY;                     /* +0x50: last mouse y */
    int m_unk54;                     /* +0x54: (spriteBase*5 + 300)*2, set by the factory -
                                      * role not yet pinned */
};

/* Container/dialog base - each concrete panel is its own class (own
 * vtable) sharing the container behavior. The base is a REAL class
 * with its own vtable (0x557bbc) and out-of-line constructor
 * (0x505760, called by every builder), sized exactly 0x90:
 * CWidget (0x38) + the panel state below + a 16-slot embedded array
 * of ATL CString handles at +0x50 (the base ctor runs
 * _eh_vector_constructor_iterator_ over it; each slot's ctor
 * allocates through the string manager at DAT_005b1444 and stores
 * body+0x10 - ATL7 CStringData's 16-byte header - and the dtor is a
 * refcounted release). All panels register with g_uiPanelManager
 * (0x50eea0): a doubly-linked list, prepended or appended by the
 * m_insertAtFront flag. */
class CPanel : public CWidget {
public:
    /* 0x505760 - promoted, Panel.cpp (the CString slot construction
     * is deferred pending a CString reconstruction; see there). */
    CPanel();

    u8    m_unk38;           /* +0x38: builders override (WorldList sets 1) */
    u8    m_unk39;           /* +0x39: base drag flag slot; ctor clears */
    u8    m_unk3a[2];        /* +0x3a */
    int   m_unk3c;           /* +0x3c */
    int   m_unk40;           /* +0x40 */
    int   m_unk44;           /* +0x44 */
    int   m_unk48;           /* +0x48 */
    int   m_unk4c;           /* +0x4c */
    char *m_strings[16];     /* +0x50: ATL CString handles (see class comment) */
};

/* State 2's server WORLD LIST panel (docs/screens/02_server_select.md):
 * two bottom buttons (View All / Friends) + the row-list scrollbar.
 * Size 0x94 = CPanel + the +0x90 field. */
class CWorldListPanel : public CPanel {   /* vtable 0x557f08; builder 0x5099d0 */
public:
    CWorldListPanel();                    /* inlined in the builder */

    virtual bool OnMouseDown(int x, int y);           /* WorldListPanel_OnMouseDown - port pending */
    virtual void OnCommand(int evt, int id, int arg); /* 0x50d810 WorldListPanel_OnCommand - port pending */

    int m_unk90;             /* +0x90: builder inits to -1 (selection?) */
};

/* State 3's lobby channel-user-list (rows drawn by
 * RenderChannelUserRow: status flag + rank icon + name). Plain-sized
 * CPanel; key 0x232a at (572,287) 209x259 with a page-7 scrollbar. */
class CChannelUserListPanel : public CPanel {  /* vtable 0x557cac; builder 0x509d80 */
public:
    CChannelUserListPanel();                   /* inlined in the builder */
};

/* State 9's Ready Room chat log (rows drawn by RenderReadyRoomChatRow,
 * color-coded by message type). Plain-sized CPanel; key 2000 at
 * (21,385) 480x160 with a page-9 scrollbar; starts HIDDEN and is
 * front-inserted in the manager's z-order. */
class CReadyRoomChatPanel : public CPanel {    /* vtable 0x557ee0; builder 0x5094f0 */
public:
    CReadyRoomChatPanel();                     /* inlined in the builder */
};

/* State 3's lobby chat panel: the focused chat input (Win32 EDIT,
 * maxLen 80), eight channel-tab labels (sprites 0x4b0+i, the selected
 * one marked via m_tabSelected), and a page-13 scrollbar. */
class CLobbyChatPanel : public CPanel {        /* vtable 0x557cd4; builder 0x509af0 */
public:
    CLobbyChatPanel();                         /* inlined in the builder */
    int m_unk90;                               /* +0x90: builder inits to -1 (same slot as
                                                * CWorldListPanel's) */
};

/* State 7's Avatar Store item panel: page-14 scrollbar + three
 * category tab labels (msgs 0x4b0-0x4b2) that start DISABLED. */
class CAvatarStorePanel : public CPanel {      /* vtable 0x557eb8; builder 0x509e60 */
public:
    CAvatarStorePanel();                       /* inlined in the builder */
    u8  m_unk90;                               /* +0x90 */
    u8  m_unk91;                               /* +0x91 */
    u8  m_pad92[2];                            /* +0x92 */
    int m_unk94;                               /* +0x94: builder inits to -1 */
    int m_unk98;                               /* +0x98 */
};

/* g_uiPanelManager's doubly-linked list node (allocated by 0x50f350,
 * linked by the 0x50eea0 insert; the singleton builders walk these). */
struct CPanelListNode {
    CPanelListNode *m_next;   /* +0x00 */
    CPanelListNode *m_prev;   /* +0x04 */
    CPanel         *m_panel;  /* +0x08 */
};

/* State 3's "enter room by number" dialog: two 4-char text entries
 * (room number / password) + OK/Cancel labels. A SINGLETON: the
 * builder walks the manager list for (typeId 0, key 1) and brings the
 * existing dialog to front instead of rebuilding. Keeps the base
 * ctor's insert-at-front default - dialogs land on top. */
class CEnterRoomNumberDialog : public CPanel { /* vtable 0x557df0; builder 0x5087b0 */
public:
    CEnterRoomNumberDialog() {}                /* base defaults only */
};

/* The remaining confirmed concrete panels (identity + vtable confirmed;
 * field maps not yet reconstructed, so no size asserts yet):
 *   CBuddyPanel            vtable 0x557be4  BuildBuddyPanel 0x509110 (shared; SINGLETON key
 *                                           20000 - the builder walks g_uiPanelManager's list
 *                                           first and returns the existing panel; size 0x94)
 *   CChatLogPanel          vtable 0x557b94  BuildChatLogPanel (~0x1050 bytes)
 *   CCreateRoomDialog      vtable 0x557c34  BuildCreateRoomDialog (state 3) */
class CBuddyPanel            : public CPanel {};
class CChatLogPanel          : public CPanel {};
class CCreateRoomDialog      : public CPanel {};

#endif /* GB_CXX_WIDGET_H */
