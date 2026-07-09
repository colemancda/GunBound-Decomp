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
    /* SLOT 0/10 CORRECTION (supersedes docs/widgets.md's original table):
     * the base OnCommand (0x50eb10) moves focus by calling child slot 0
     * with an explicit 0 (loser) / 1 (gainer) argument - slot 0 is
     * SetFocus(bool), NOT the destructor. The scalar-deleting dtor is
     * slot 10 (which is why both slots resolved to 0x50e860 in classes
     * with a trivial SetFocus). CEditBox's +0x04 active flag is the
     * state this toggles. */
    virtual void SetFocus(bool active);                 /* slot 0  +0x00: 0x50e860 trivial impl on most classes */
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
    virtual ~CWidget();                                 /* slot 10 +0x28: the real scalar-deleting dtor */
    virtual bool OnDragMove(int x, int y);              /* slot 11 +0x2c: base drag, FUN_0050e3a0 */

    /* Non-virtual base helpers (real member functions in the binary,
     * called by subclass handlers): */
    bool ResetPressState(int x, int y);   /* 0x50e2f0 - promoted, Widget.cpp: clears the +0x38/+0x04
                                           * flags, broadcasts mouse-UP to children, returns
                                           * consumed-or-inside (shared tail of leaf press handlers) */
    bool MouseMoveChildren(int x, int y); /* 0x50e870 - promoted, Widget.cpp */
    void MoveBy(int dx, int dy);          /* 0x50e730 - promoted, Widget.cpp */
    int FindChildIndex(int typeId, int id); /* 0x50e620 - promoted, Widget.cpp. NOTE: Ghidra shows
                                             * the args arriving in EDI/ESI (custom-register family);
                                             * returns child count when not found. */
    bool MouseDownChildren(int x, int y); /* 0x50e8e0 - promoted, Widget.cpp */
    bool MouseUpChildren(int x, int y);   /* 0x50e950 - promoted, Widget.cpp */

    /* field offsets confirmed in docs/widgets.md; m_unk* are the
     * undocumented gaps, kept explicit so everything else lands exactly */
    u8       m_unk04;        /* +0x04: read as a byte flag by CEditBox::Draw
                              * (skip the EDIT-control sync when clear);
                              * cleared by CScrollBar::OnMouseUp */
    u8       m_unk05[3];     /* +0x05 */
    CWidget *m_parent;       /* +0x08: callback target for OnCommand */
    CAtlArray<CWidget *> m_children; /* +0x0c..+0x1b: ATL7 CAtlArray - grow
                              * helper 0x50ed30 IS its GrowBuffer, and the
                              * broadcast loops' inlined AtlThrow guard IS
                              * its checked operator[] (see AtlArray.h) */
    u8       m_unk1c;        /* +0x1c: byte flag; gates click reporting in
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
class CLabel : public CWidget {      /* vtable 0x557da0, size 0x40; ctor CreateLabelWidget(id, sprite, x, y, w, h) */
public:
    virtual bool OnMouseDown(int x, int y);  /* 0x5052e0 - promoted, Label.cpp */
    virtual void Draw();                     /* 0x50e350 - promoted, Label.cpp: reports evt 1 upward
                                              * (the parent panel blits for it), then child broadcast */

    u8  m_unk38;                     /* +0x38: byte flag; gates click reporting with +0x1c */
    u8  m_unk39;                     /* +0x39: (base drag flag slot per docs/widgets.md) */
    u8  m_unk3a[2];                  /* +0x3a */
    int m_spriteId;                  /* +0x3c: sprite/message id; Draw (0x50e350) blits via FindSpriteFrame */
};

/* Editable text field backed by a REAL Win32 EDIT control overlaid on the
 * DirectDraw surface. Update (TextEntry_SyncFromControl) pulls the OS
 * control's text: GetWindowTextA(hwnd, m_text, 0x80). Used for Create Room
 * name/password, enter-room-by-number, chat input. */
class CEditBox : public CWidget {    /* vtable 0x557c84, size 0x140; ctor CreateTextEntryWidget(id, msg, x, y, w, maxLen) */
public:
    virtual void Draw();             /* 0x507030 TextEntry_SyncFromControl - promoted, EditBox.cpp */

    char m_text[0x100];              /* +0x38: synced from the EDIT control */
    u8   m_unk138[8];                /* +0x138 */
};

/* Fixed 18-px-wide vertical scrollbar (w is 0x12 in every call). Owns its
 * up/down arrow children and the scroll position; the PARENT owns the list
 * content and decides what a scroll means. Fires
 * m_parent->OnCommand(0x2000, m_id, m_scrollPos) on change. */
class CScrollBar : public CWidget {  /* vtable 0x557e90, size 0x58; ctor CreateScrollListWidget 0x5080a0 */
public:
    virtual bool OnMouseDown(int x, int y);  /* 0x50f500 - promoted, ScrollBar.cpp */
    virtual bool OnMouseUp(int x, int y);    /* 0x50f5f0 - promoted, ScrollBar.cpp */
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
    u8  m_unk54[4];                  /* +0x54 */
};

/* Container/dialog base - each concrete panel is its own class (own
 * vtable) sharing the container behavior: broadcast input/draw to
 * children, forward child OnCommand events up (often into the owning
 * game state's command dispatcher). Built by the panel-builder catalog
 * in docs/widgets.md; all register with g_uiPanelManager. */
class CPanel : public CWidget {
public:
    /* per-panel fields vary; dialog sizes run 0x90-0x9c, the chat-log
     * panel is ~0x1050 (embeds a ~4 KB history buffer) */
};

/* The nine confirmed concrete panels (identity + vtable confirmed; field
 * maps not yet reconstructed, so no size asserts yet):
 *   CWorldListPanel        vtable 0x557f08  BuildWorldListPanel 0x5099d0 (state 2)
 *   CBuddyPanel            vtable 0x557be4  BuildBuddyPanel (shared; singleton key 20000)
 *   CLobbyChatPanel        vtable 0x557cd4  BuildLobbyChatPanel (state 3)
 *   CChannelUserListPanel  vtable 0x557cac  BuildChannelUserListPanel 0x509d80 (state 3)
 *   CReadyRoomChatPanel    vtable 0x557ee0  BuildReadyRoomChatPanel 0x5094f0 (state 9)
 *   CAvatarStorePanel      vtable 0x557eb8  BuildAvatarStorePanel (state 7)
 *   CChatLogPanel          vtable 0x557b94  BuildChatLogPanel (~0x1050 bytes)
 *   CEnterRoomNumberDialog vtable 0x557df0  BuildEnterRoomNumberDialog (state 3)
 *   CCreateRoomDialog      vtable 0x557c34  BuildCreateRoomDialog (state 3) */
class CWorldListPanel        : public CPanel {};   /* OnCommand override: WorldListPanel_OnCommand 0x50d810 */
class CBuddyPanel            : public CPanel {};
class CLobbyChatPanel        : public CPanel {};
class CChannelUserListPanel  : public CPanel {};
class CReadyRoomChatPanel    : public CPanel {};
class CAvatarStorePanel      : public CPanel {};
class CChatLogPanel          : public CPanel {};
class CEnterRoomNumberDialog : public CPanel {};
class CCreateRoomDialog      : public CPanel {};

#endif /* GB_CXX_WIDGET_H */
