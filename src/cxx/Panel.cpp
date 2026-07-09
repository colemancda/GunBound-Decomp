/* CPanel base + CWorldListPanel construction - promoted from the raw C
 * ports src/unnamed/FUN_00505760.c (the out-of-line CPanel ctor,
 * 0x505760) and src/ui_widget/BuildWorldListPanel.c (0x5099d0).
 * See src/cxx/README.md. */
#include "Widget.h"

extern "C" {
/* g_uiPanelManager's list-insert (0x50eea0): allocates a link node and
 * prepends or appends by the panel's m_unk05 front-flag. The manager
 * object arrives in EAX (custom-register family) - modeled as a plain
 * extern until the manager class is reconstructed. */
void FUN_0050eea0(void *panel);
/* Manager-wide clear-all-focus sweep (0x50efa0): drops every
 * registered panel subtree's +0x04 focus flag (receiver conventions
 * unresolved, same manager family). */
void FUN_0050efa0(void *manager);
}

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
    FUN_0050eea0(p);
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
    FUN_0050eea0(p);
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
    FUN_0050efa0(0 /* g_uiPanelManager; receiver convention unresolved */);
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
    FUN_0050eea0(p);
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
    FUN_0050eea0(p);
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
    FUN_0050eea0(p);
    return p;
}
