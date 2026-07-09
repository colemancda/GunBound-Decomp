/* CPanel base + CWorldListPanel construction - promoted from the raw C
 * ports src/unnamed/Panel_BaseConstructor.c (the out-of-line CPanel ctor,
 * 0x505760) and src/ui_widget/BuildWorldListPanel.c (0x5099d0).
 * See src/cxx/README.md. */
#include "Widget.h"

extern "C" {
/* g_uiPanelManager's list-insert (0x50eea0): allocates a link node and
 * prepends or appends by the panel's m_unk05 front-flag. The manager
 * object arrives in EAX (custom-register family) - modeled as a plain
 * extern until the manager class is reconstructed. */
void PanelManager_Register(void *panel);
/* Manager-wide clear-all-focus sweep (0x50efa0): drops every
 * registered panel subtree's +0x04 focus flag (receiver conventions
 * unresolved, same manager family). */
void PanelManager_ClearAllFocus(void *manager);
/* BringToFront (0x509960, __fastcall manager/panel): unlink the
 * panel's manager node and relink it at the head of the z-order. */
void __fastcall PanelManager_BringToFront(void *manager, CPanel *panel);
/* 0x506f60: seed the shared overlay EDIT control's text for a focused
 * CEditBox (SetWindowTextA; empty string when passed null). Receiver
 * and text arrive in EDI/ESI - unresolved custom regs. */
void TextEntry_SetControlText(void);
/* The global UI panel manager (0xe53c40): +4 list head, +8 tail. */
extern unsigned char g_uiPanelManager;
extern int g_clientContext;
}

static CPanelListNode *PanelListHead()
{
    return *(CPanelListNode **)((unsigned char *)&g_uiPanelManager + 4);
}

extern "C" int RenderWrappedText(void *outBuf, const char *text, int lineBytes,
                                 int charsPerLine, int bufBytes, int flag); /* 0x41b4b0 */
extern "C" int g_currentGameState;

/* C++-linkage factories defined in Label.cpp / ScrollBar.cpp */
CLabel * __stdcall CreateLabelWidget(int id, int spriteId, int x, int y, int w, int h);
CScrollBar * __stdcall CreateScrollListWidget(int spriteBase, int total,
                                              int x, int y, int w, int h, int pageSize);
CEditBox * __stdcall CreateTextEntryWidget(int id, int x, int y, int w, int h, int maxLen);

/* 0x505760 - the CPanel base constructor (a real out-of-line function,
 * SEH-framed; every panel builder calls it before installing its own
 * vtable). Panel type id 0; +0x05 insert-at-front defaults ON (the
 * builder for the world list flips it off).
 *
 * DEFERRED: the original then runs _eh_vector_constructor_iterator_
 * over the 16 CString slots at +0x50 (each ctor allocates a nil
 * string through the manager at DAT_005b1444). Reconstructing ATL
 * CString is its own work item; the slots are nulled here instead -
 * revisit when the string class lands. */
CPanel::CPanel()
{
    m_typeId = 0;
    m_unk39 = 0;
    m_unk38 = 0;
    m_unk05[0] = 1;
    for (int i = 0; i < 16; ++i) {
        m_strings[i] = 0;
    }
}

/* Construction state from the 0x5099d0 builder's guarded section. */
CWorldListPanel::CWorldListPanel()
{
    m_unk90 = -1;
    m_unk38 = 1;
    m_unk05[0] = 0;
}

/* Construction state from the 0x509d80 builder's guarded section. */
CChannelUserListPanel::CChannelUserListPanel()
{
    m_unk38 = 1;
    m_unk05[0] = 0;
}

/* 0x509d80 - BuildChannelUserListPanel (docs/widgets.md: the lobby's
 * channel user list). Key 0x232a at (572,287) 209x259, one page-7
 * scrollbar at (179,63) h 154. Same invisible EAX/EDI scrollbar
 * register args as BuildWorldListPanel - the builder's argument is
 * forwarded as the factory's never-read stack slot and presumably
 * doubles as the EDI total. */
CChannelUserListPanel * BuildChannelUserListPanel(int total)
{
    CChannelUserListPanel *p = new CChannelUserListPanel();
    p->m_id = 0x232a;
    p->m_unk4c = 0;
    p->m_unk44 = 0x2712;
    p->m_unk48 = 0;
    p->m_x = 0x23c;
    p->m_y = 0x11f;
    p->m_width = 0xd1;
    p->m_height = 0x103;
    p->AddChild(CreateScrollListWidget(0, total, 0xb3, 0x3f, 0x12, 0x9a, 7));
    PanelManager_Register(p);
    return p;
}

/* Construction state from the 0x5094f0 builder's guarded section: this
 * one starts HIDDEN (+0x1e) and front-inserted (+0x05 stays 1). */
CReadyRoomChatPanel::CReadyRoomChatPanel()
{
    m_unk38 = 1;
    m_unk05[0] = 1;
    m_hidden = 1;
}

/* 0x5094f0 - BuildReadyRoomChatPanel (docs/widgets.md: the Ready Room
 * chat log). Key 2000 at (21,385) 480x160, one page-9 scrollbar at
 * (455,51) h 69; +0x48 starts at 0xb (vs 0 in the list panels - likely
 * the visible-row count). */
CReadyRoomChatPanel * BuildReadyRoomChatPanel(int total)
{
    CReadyRoomChatPanel *p = new CReadyRoomChatPanel();
    p->m_unk4c = 0;
    p->m_id = 2000;
    p->m_unk44 = 10000;
    p->m_unk48 = 0xb;
    p->m_x = 0x15;
    p->m_y = 0x181;
    p->m_width = 0x1e0;
    p->m_height = 0xa0;
    p->AddChild(CreateScrollListWidget(0, total, 0x1c7, 0x33, 0x12, 0x45, 9));
    PanelManager_Register(p);
    return p;
}

/* Construction state from the 0x509af0 builder's guarded section. */
CLobbyChatPanel::CLobbyChatPanel()
{
    m_unk38 = 1;
    m_unk05[0] = 0;
    m_unk90 = -1;
}

/* 0x509af0 - BuildLobbyChatPanel (docs/widgets.md: the lobby chat
 * panel). Key 0x2329 at (23,287) 549x259: the chat-input CEditBox
 * (26,235) 484x12 maxLen 80 - focused immediately after a manager-wide
 * focus sweep, via a real slot-0 SetFocus(1) vtable call in the
 * original - then EIGHT channel-tab labels (ids 0-7, sprites 0x4b0+i,
 * 22x22 at y 9, x from 0x108 stepping 0x20; the original inlines the
 * label factory in the loop) with the selected one marked, then the
 * page-13 scrollbar. selectedTab is the builder's argument. */
CLobbyChatPanel * BuildLobbyChatPanel(int selectedTab)
{
    CLobbyChatPanel *p = new CLobbyChatPanel();
    p->m_id = 0x2329;
    p->m_unk4c = 0;
    p->m_unk44 = 0x2711;
    p->m_unk48 = 0;
    p->m_x = 0x17;
    p->m_y = 0x11f;
    p->m_width = 0x225;
    p->m_height = 0x103;
    CEditBox *input = CreateTextEntryWidget(0, 0x1a, 0xeb, 0x1e4, 0xc, 0x50);
    p->AddChild(input);
    PanelManager_ClearAllFocus(0 /* g_uiPanelManager; receiver convention unresolved */);
    input->SetFocus(true);
    int i = 0;
    for (int x = 0x108; x < 0x208; x += 0x20, ++i) {
        CLabel *tab = new CLabel();
        tab->m_spriteId = 0x4b0 + i;
        tab->m_id = i;
        tab->m_x = x;
        tab->m_y = 9;
        tab->m_width = 0x16;
        tab->m_height = 0x16;
        tab->m_tabSelected = (u8)(i == selectedTab);
        p->AddChild(tab);
    }
    p->AddChild(CreateScrollListWidget(0, 0, 0x20e, 0x3f, 0x12, 0x9a, 0xd));
    PanelManager_Register(p);
    return p;
}

/* Construction state from the 0x509e60 builder's guarded section. */
CAvatarStorePanel::CAvatarStorePanel()
{
    m_unk38 = 1;
    m_unk05[0] = 0;
    m_unk94 = -1;
    m_unk90 = 0;
    m_unk91 = 0;
    m_unk98 = 0;
}

/* 0x509e60 - BuildAvatarStorePanel (docs/widgets.md: the Avatar Store
 * item panel). Key 0x232b at (552,5) 240x541 with the page-14
 * scrollbar; registers with the manager BEFORE adding the three
 * category tab labels (msgs 0x4b0-0x4b2, 64x23 at y 508), each of
 * which starts DISABLED via SetEnabled(false). */
CAvatarStorePanel * BuildAvatarStorePanel(int total)
{
    CAvatarStorePanel *p = new CAvatarStorePanel();
    p->m_id = 0x232b;
    p->m_unk4c = 0;
    p->m_unk44 = 0x2712;
    p->m_unk48 = 0;
    p->m_x = 0x228;
    p->m_y = 5;
    p->m_width = 0xf0;
    p->m_height = 0x21d;
    p->AddChild(CreateScrollListWidget(0, total, 0xcf, 0x8c, 0x12, 0xab, 0xe));
    PanelManager_Register(p);
    CLabel *tab;
    tab = CreateLabelWidget(0, 0x4b0, 0xe, 0x1fc, 0x40, 0x17);
    tab->SetEnabled(false);
    p->AddChild(tab);
    tab = CreateLabelWidget(1, 0x4b1, 0x57, 0x1fc, 0x40, 0x17);
    tab->SetEnabled(false);
    p->AddChild(tab);
    tab = CreateLabelWidget(2, 0x4b2, 0xa0, 0x1fc, 0x40, 0x17);
    tab->SetEnabled(false);
    p->AddChild(tab);
    return p;
}

/* 0x507ff0 - the CStaticText factory (no raw-port name existed;
 * discovered via the chat-log builder). Wraps the text into the
 * widget's own buffer at creation. */
CStaticText *CreateStaticTextWidget(int x, int y, int w, int h,
                                    const char *text, u16 color)
{
    CStaticText *p = new CStaticText();
    p->m_id = 0;
    p->m_x = x;
    p->m_y = y;
    p->m_height = h;
    p->m_color = color;
    p->m_width = w;
    for (int i = 0; i < 0x500; ++i) {
        p->m_wrapped[i] = 0;
    }
    RenderWrappedText(p->m_wrapped, text, 0x80, w / 6, 0x500, 1);
    return p;
}

/* Construction state from the chat-log builder's guarded section. */
CChatLogPanel::CChatLogPanel()
{
    for (int i = 0; i < 4000; ++i) {
        m_history[i] = 0;
    }
    m_unk1048 = 0;
    m_unk104c = 0;
}

/* BuildChatLogPanel (docs/widgets.md; the whisper/direct-message
 * window). Keyed 0x4e21 (20001) at (541,272) 254x291: copies the
 * partner's name out of their record (+0x21), the close-X (sprite
 * 0x2c7), the input CEditBox (maxLen 80) - auto-focused after the
 * manager sweep UNLESS in-battle (state 11 leaves keyboard focus on
 * the game) - the partner-name CStaticText in white (0xffff), and the
 * page-14 scrollbar. */
void BuildChatLogPanel(int arg1, int partnerRecord)
{
    const char *name = (const char *)(partnerRecord + 0x21);
    CChatLogPanel *p = new CChatLogPanel();
    p->m_id = 0x4e21;
    p->m_unk4c = 0;
    p->m_unk44 = 0x2c6;
    p->m_unk48 = 0;
    p->m_x = 0x21d;
    p->m_y = 0x110;
    p->m_width = 0xfe;
    p->m_height = 0x123;
    {
        char *dst = p->m_partnerName;
        const char *src = name;
        while ((*dst++ = *src++) != 0) {}
    }
    p->AddChild(CreateLabelWidget(0, 0x2c7, 0xdf, 7, 0x16, 0x14));
    CEditBox *input = CreateTextEntryWidget(0, 0x13, 0x109, 0xd3, 0xc, 0x50);
    p->AddChild(input);
    PanelManager_ClearAllFocus(0 /* g_uiPanelManager; receiver convention unresolved */);
    if (g_currentGameState != 0xb) {
        input->SetFocus(true);
    }
    p->AddChild(CreateStaticTextWidget(0x57, 0xb, 0x91, 0xc, name, 0xffff));
    p->AddChild(CreateScrollListWidget(0, 0, 0xe3, 0x44, 0x12, 0x9d, 0xe));
    PanelManager_Register(p);
}

/* 0x508190 - BuildCreateRoomDialog (docs/widgets.md; takes the manager
 * plus two values stored into +0x94/+0x98). SINGLETON keyed 0 with the
 * BringToFront exists-path. Fresh build at (243,202) 313x193:
 * room-name CEditBox (maxLen 20; its OS EDIT control seeded via
 * 0x506f60 and focused after the manager sweep), password CEditBox
 * (maxLen 4), the four-cell game-mode grid (ids 0-3, sprites 0x518+i,
 * 27x27 at y 8, default the 4th), four option toggles (ids 4-7,
 * sprites 0x514-0x517, 45x24 in a 2x2 block, id 4 pre-selected), and
 * OK (id 8, sprite 0x51d) / Cancel (id 9, 0x51c). The original
 * inlines the label factory for ids 4-9. */
void BuildCreateRoomDialog(void *manager, int arg2, int arg3)
{
    for (CPanelListNode *n = PanelListHead(); n != 0; n = n->m_next) {
        CPanel *q = n->m_panel;
        if (q->m_typeId == 0 && q->m_id == 0) {
            PanelManager_BringToFront(&g_uiPanelManager, q);
            return;
        }
    }
    CCreateRoomDialog *p = new CCreateRoomDialog();
    p->m_id = 0;
    p->m_unk4c = 0;
    p->m_unk44 = 0x2713;
    p->m_unk48 = 0;
    p->m_x = 0xf3;
    p->m_y = 0xca;
    p->m_width = 0x139;
    p->m_height = 0xc1;
    p->m_unk94 = arg2;
    p->m_unk98 = arg3;
    CEditBox *roomName = CreateTextEntryWidget(0, 0x60, 0x2c, 0xbe, 0xc, 0x14);
    p->AddChild(roomName);
    TextEntry_SetControlText();
    PanelManager_ClearAllFocus(0 /* g_uiPanelManager; receiver convention unresolved */);
    roomName->SetFocus(true);
    p->AddChild(CreateTextEntryWidget(1, 0x60, 0x46, 0xbe, 0xc, 4));
    int i = 0;
    for (int x = 0xad; x < 0x12d; x += 0x20, ++i) {
        CLabel *mode = CreateLabelWidget(i, 0x518 + i, x, 8, 0x1b, 0x1b);
        mode->m_tabSelected = (u8)(i == 3);
        p->AddChild(mode);
    }
    static const struct { int id, sprite, x, y, w, h, sel; } kToggles[] = {
        { 4, 0x514, 0x16, 0x5f, 0x2d, 0x18, 1 },
        { 5, 0x515, 0x45, 0x5f, 0x2d, 0x18, 0 },
        { 6, 0x516, 0x16, 0x7a, 0x2d, 0x18, 0 },
        { 7, 0x517, 0x45, 0x7a, 0x2d, 0x18, 0 },
        { 8, 0x51d, 0xd5, 0x99, 0x52, 0x22, 0 },
        { 9, 0x51c, 0x80, 0x99, 0x52, 0x22, 0 },
    };
    for (int t = 0; t < 6; ++t) {
        CLabel *l = CreateLabelWidget(kToggles[t].id, kToggles[t].sprite,
                                      kToggles[t].x, kToggles[t].y,
                                      kToggles[t].w, kToggles[t].h);
        l->m_tabSelected = (u8)kToggles[t].sel;
        p->AddChild(l);
    }
    PanelManager_Register(p);
}

/* 0x509110 - BuildBuddyPanel (docs/widgets.md: the shared buddy list).
 * SINGLETON keyed 20000: if already registered, just set the existing
 * panel's +0x1d reshow flag. Otherwise: (568,11) 211x267 with the
 * close-X (sprite 0x2bf) / Add (0x2bd) / Del (0x2be) labels along the
 * top and the page-7 scrollbar; front-inserted like the dialogs. */
void BuildBuddyPanel()
{
    for (CPanelListNode *n = PanelListHead(); n != 0; n = n->m_next) {
        CPanel *q = n->m_panel;
        if (q->m_typeId == 0 && q->m_id == 20000) {
            q->m_unk1d = 1;
            return;
        }
    }
    CBuddyPanel *p = new CBuddyPanel();
    p->m_id = 20000;
    p->m_unk4c = 0;
    p->m_unk44 = 700;
    p->m_unk48 = 0;
    p->m_x = 0x238;
    p->m_y = 0xb;
    p->m_width = 0xd3;
    p->m_height = 0x10b;
    p->AddChild(CreateLabelWidget(0, 0x2bf, 0xb4, 7, 0x16, 0x14));
    p->AddChild(CreateLabelWidget(1, 0x2bd, 0x5e, 7, 0x27, 0x14));
    p->AddChild(CreateLabelWidget(2, 0x2be, 0x89, 7, 0x27, 0x14));
    p->AddChild(CreateScrollListWidget(0, 0, 0xb7, 0x49, 0x12, 0x98, 7));
    PanelManager_Register(p);
}

/* 0x5087b0 - BuildEnterRoomNumberDialog (docs/widgets.md; __fastcall).
 * SINGLETON: if a (typeId 0, key 1) panel is already registered,
 * bring it to front and return. Otherwise: key 1 at (243,202) 314x160,
 * two 4-char CEditBoxes (the room number focused after the manager
 * focus sweep, then the password) and OK (sprite 0x579) / Cancel
 * (0x578) labels. Keeps the base ctor's insert-at-front default. */
void __fastcall BuildEnterRoomNumberDialog(int arg)
{
    for (CPanelListNode *n = PanelListHead(); n != 0; n = n->m_next) {
        CPanel *q = n->m_panel;
        if (q->m_typeId == 0 && q->m_id == 1) {
            PanelManager_BringToFront(&g_uiPanelManager, q);
            return;
        }
    }
    CEnterRoomNumberDialog *p = new CEnterRoomNumberDialog();
    p->m_id = 1;
    p->m_unk4c = 0;
    p->m_unk44 = 0x2715;
    p->m_unk48 = 0;
    p->m_x = 0xf3;
    p->m_y = 0xca;
    p->m_width = 0x13a;
    p->m_height = 0xa0;
    CEditBox *roomNo = CreateTextEntryWidget(0, 99, 0x32, 0xb4, 0xc, 4);
    p->AddChild(roomNo);
    PanelManager_ClearAllFocus(0 /* g_uiPanelManager; receiver convention unresolved */);
    roomNo->SetFocus(true);
    p->AddChild(CreateTextEntryWidget(1, 99, 0x54, 0xb4, 0xc, 4));
    p->AddChild(CreateLabelWidget(0, 0x579, 0xd5, 0x76, 0x52, 0x22));
    p->AddChild(CreateLabelWidget(1, 0x578, 0x80, 0x76, 0x52, 0x22));
    PanelManager_Register(p);
}

/* WorldListRowHitTest - which server row the point lands on. The rows
 * are a 2-column grid inside the panel: cells 223x73 apart starting at
 * (+0x16, +0x2d) panel-relative, each 0xdf x 0x49; a row only counts
 * while its server's onlineFlag (the SoA at g_clientContext+0x3f809)
 * is 1. Returns the slot index or -1. */
int CWorldListPanel::RowHitTest(int x, int y)
{
    int count = (int)*(unsigned char *)(g_clientContext + 0x3f808);
    for (int i = 0; i < count; ++i) {
        int cellX = m_x + 0x16 + (i & 1) * 0xf7;
        int cellY = m_y + 0x2d + (i / 2) * 0x49;
        if (cellX <= x && x <= cellX + 0xdf &&
            cellY <= y && y <= cellY + 0x49 &&
            *(char *)(g_clientContext + 0x3f809 + i) == 1) {
            return i;
        }
    }
    return -1;
}

/* 0x5099d0 - BuildWorldListPanel (docs/screens/02_server_select.md's
 * WORLD LIST). Panel key 9000 at (11,13) 545x530, with the View All
 * (id 0, sprite 0x44c) and Friends (id 1, sprite 0x44d) bottom
 * buttons at y 491 and the row scrollbar at (515,74) h 377. The View
 * All label gets its +0x3a byte set - role not yet pinned.
 *
 * NOTE: the original passes the scrollbar factory's register
 * arguments (spriteBase in EAX, total in EDI) invisibly at this call
 * site - Ghidra's flattened call shows only the stack args, with the
 * builder's own argument forwarded as the factory's never-read first
 * stack slot. They're passed as 0 here until the curated Ghidra
 * project pins them; the builder's argument is presumably the world
 * count headed for EDI. */
CWorldListPanel * BuildWorldListPanel(int total)
{
    CWorldListPanel *p = new CWorldListPanel();
    p->m_id = 9000;
    p->m_unk4c = 0;
    p->m_unk44 = 0x2711;
    p->m_unk48 = 0;
    p->m_x = 0xb;
    p->m_y = 0xd;
    p->m_width = 0x221;
    p->m_height = 0x212;
    CLabel *viewAll = CreateLabelWidget(0, 0x44c, 0x145, 0x1eb, 0x4a, 0x1a);
    viewAll->m_tabSelected = 1;
    p->AddChild(viewAll);
    p->AddChild(CreateLabelWidget(1, 0x44d, 0x1a3, 0x1eb, 0x4a, 0x1a));
    p->AddChild(CreateScrollListWidget(0, total, 0x203, 0x4a, 0x12, 0x179, 0));
    PanelManager_Register(p);
    return p;
}
