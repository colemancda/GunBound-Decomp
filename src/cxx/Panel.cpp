/* CPanel base + CWorldListPanel construction - promoted from the raw C
 * ports src/unnamed/Panel_BaseConstructor.c (the out-of-line CPanel ctor,
 * 0x505760) and src/ui_widget/BuildWorldListPanel.c (0x5099d0).
 * See src/cxx/README.md.
 *
 * score.sh sweep (2026-07-11): HandlePress/CPanel::OnMouseDown are
 * effectively perfect (105/7000, 210/5200); the nine Build*Panel
 * factories (BuildChannelUserListPanel 4535/6000,
 * BuildReadyRoomChatPanel 4185/6100, BuildLobbyChatPanel 13985/21000,
 * BuildAvatarStorePanel 5271/10400, BuildChatLogPanel 5491/11200,
 * BuildWorldListPanel 4675/8000, BuildBuddyPanel 6340/9700,
 * BuildEnterRoomNumberDialog 4590/10200) all carry the same guarded-
 * ctor field-write-scheduling delta already confirmed on
 * CreateLabelWidget/CreateTextEntryWidget/CreateButtonWidget/
 * CreateScrollListWidget/CreateStaticTextWidget - not chased
 * individually, same low-ROI category each time. Three functions are
 * far larger outliers and were NOT diffed in depth this pass:
 * CWorldListPanel::OnMouseDown (6475/12800), CWorldListPanel::OnCommand
 * (30589/33200), and BuildCreateRoomDialog (37925/46000) - all three
 * are dominated by the DAT_00e9be94 flat-ButtonWidget registry walks
 * this file's own comments already flag as "kept literal pending the
 * flat-ButtonWidget reconstruction" (PLAN.md Phase 1's
 * RegisterActiveObject item); revisit once that lands rather than
 * hand-diffing register-convention-heavy code that's expected to change
 * shape anyway. */
#include "Widget.h"
#include "GameState.h"

extern "C" {
/* g_uiPanelManager's list-insert (0x50eea0): allocates a link node and
 * prepends or appends by the panel's m_unk05 front-flag. The manager
 * object arrives in EAX (custom-register family) - now threaded through
 * explicitly (see PanelManager_Register.c); every call site below passes
 * &g_uiPanelManager, the only panel-manager singleton in this codebase. */
void __stdcall PanelManager_Register(void *manager, void *panel);
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
/* The global UI panel manager (0xe53c40): +4 list head, +8 tail - real
 * layout recovered from its own constructor, see globals.c's comment. */
extern unsigned char g_uiPanelManager[0x1c];
extern int g_clientContext;
/* Sprite-lookup/blit primitives - see Widget_DrawSelf.c/FindSpriteFrame.c
 * for the recovered (container,outerKey,innerKey)/(frame,x,y) shapes
 * used by CWorldListPanel::Update() below. */
extern unsigned int DAT_0079352c;
extern unsigned char DAT_00ea0e18[0x20];
int FindSpriteFrame(int container, unsigned int outerKey, unsigned int innerKey);
int BlitSprite16bpp(int frame, int x, int y, int outerKey);
int BlitSpriteClipped(int frame, int x, int y, int outerKey);
void __fastcall RenderWorldListRow(int panel, unsigned int index);
}

static CPanelListNode *PanelListHead()
{
    return *(CPanelListNode **)((unsigned char *)&g_uiPanelManager + 4);
}

extern "C" int RenderWrappedText(void *outBuf, const char *text, int lineBytes,
                                 int charsPerLine, int bufBytes, int flag); /* 0x41b4b0 */
extern "C" int g_currentGameState;

/* Factories defined in Label.cpp / EditBox.cpp - extern "C" linkage since
 * their signatures already exactly match the raw C ports they replace, so
 * raw C callers can link against them directly with no separate shim
 * needed (unlike CreateScrollListWidget, which needs a 6-param shim below
 * since the register-passed spriteBase/total don't fit this shape). */
extern "C" CLabel *CreateLabelWidget(int id, int spriteId, int x, int y, int w, int h);
CScrollBar * __stdcall CreateScrollListWidget(int spriteBase, int total,
                                              int x, int y, int w, int h, int pageSize);
extern "C" CEditBox *CreateTextEntryWidget(int id, int x, int y, int w, int h, int maxLen);

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
    m_dragging = 0;
    m_pinned = 0;
    m_unk05[0] = 1;
    for (int i = 0; i < 16; ++i) {
        m_strings[i] = 0;
    }
}

/* Construction state from the 0x5099d0 builder's guarded section. */
CWorldListPanel::CWorldListPanel()
{
    m_unk90 = -1;
    m_pinned = 1;
    m_unk05[0] = 0;
}

/* 0x50dc40 - CWorldListPanel::Update, vtable slot 9 (CWidget.h's
 * "per-class secondary render/refresh hook"). Ported from the raw C
 * WorldListPanel_Draw.c (never wired into the C++ vtable - this class
 * only ever inherited CWidget::Update()'s base no-op, which is why the
 * panel rendered as a solid black rectangle: its background sprite
 * (m_unk44="server_list.img"'s key 0x2711, m_unk48 as the frame/state)
 * was never drawn). Skips entirely while hidden, matching the original's
 * own `if (*(char*)(this+0x1e) == 0)` guard.
 *
 * The original's Widget_DrawSelf (0x5054b0) tail-calls Widget_DrawChildren-
 * Deep (0x50ecf0), which walks the child array calling each child's OWN
 * vtable +0x24 slot - i.e. Update(), not Draw() - so this recurses via
 * ->Update() on children too, matching that real behavior even though no
 * current child class (CLabel/CScrollBar) overrides it yet.
 *
 * FIXED (2026-07-14): BlitSprite16bpp/BlitSpriteClipped both did their OWN
 * internal FindSpriteFrame() re-lookup with a HARDCODED outerKey=10000,
 * correct only for State06_Logo2_Render's specific sprite set - live-
 * reproduced here: this panel's real outerKey is m_unk44=0x2711
 * ("server_list.img"), so their internal re-lookup silently found the
 * wrong (or no) record and drew nothing even though the outer
 * FindSpriteFrame call right above (with the correct key) succeeded and
 * returned a fully populated record. Both functions promoted to take a
 * real `outerKey` parameter - see their own headers. */
void CWorldListPanel::Update()
{
    if (m_hidden) {
        return;
    }
    if (DAT_0079352c != 0 && m_unk48 >= 0) {
        int rec = FindSpriteFrame((int)DAT_00ea0e18, (unsigned int)m_unk44, (unsigned int)m_unk48);
        if (rec != 0) {
            if (*(unsigned char *)(rec + 0x18) == 1) {
                BlitSprite16bpp(m_unk48, m_x, m_y, m_unk44);
            } else {
                BlitSpriteClipped(m_unk48, m_x, m_y, m_unk44);
            }
        }
    }
    unsigned int childCount = m_children.GetCount();
    for (unsigned int i = 0; i < childCount; ++i) {
        m_children[i]->Update();
    }
    int count = *(unsigned char *)(g_clientContext + 0x3f808);
    for (int i = 0; i < count; ++i) {
        RenderWorldListRow((int)this, (unsigned int)i);
    }
}

/* Construction state from the 0x509d80 builder's guarded section. */
CChannelUserListPanel::CChannelUserListPanel()
{
    m_pinned = 1;
    m_unk05[0] = 0;
}

/* 0x509d80 - BuildChannelUserListPanel (docs/widgets.md: the lobby's
 * channel user list). Key 0x232a at (572,287) 209x259, one page-7
 * scrollbar at (179,63) h 154. Same invisible EAX/EDI scrollbar
 * register args as BuildWorldListPanel - the builder's argument is
 * forwarded as the factory's never-read stack slot and presumably
 * doubles as the EDI total. */
extern "C" CChannelUserListPanel * BuildChannelUserListPanel(int total)
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
    PanelManager_Register(&g_uiPanelManager, p);
    return p;
}

/* Construction state from the 0x5094f0 builder's guarded section: this
 * one starts HIDDEN (+0x1e) and front-inserted (+0x05 stays 1). */
CReadyRoomChatPanel::CReadyRoomChatPanel()
{
    m_pinned = 1;
    m_unk05[0] = 1;
    m_hidden = 1;
}

/* 0x5094f0 - BuildReadyRoomChatPanel (docs/widgets.md: the Ready Room
 * chat log). Key 2000 at (21,385) 480x160, one page-9 scrollbar at
 * (455,51) h 69; +0x48 starts at 0xb (vs 0 in the list panels - likely
 * the visible-row count). */
extern "C" CReadyRoomChatPanel * BuildReadyRoomChatPanel(int total)
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
    PanelManager_Register(&g_uiPanelManager, p);
    return p;
}

/* Construction state from the 0x509af0 builder's guarded section. */
CLobbyChatPanel::CLobbyChatPanel()
{
    m_pinned = 1;
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
extern "C" CLobbyChatPanel * BuildLobbyChatPanel(int selectedTab)
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
    PanelManager_Register(&g_uiPanelManager, p);
    return p;
}

/* Construction state from the 0x509e60 builder's guarded section. */
CAvatarStorePanel::CAvatarStorePanel()
{
    m_pinned = 1;
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
extern "C" CAvatarStorePanel * BuildAvatarStorePanel(int total)
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
    PanelManager_Register(&g_uiPanelManager, p);
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
 * widget's own buffer at creation.
 * score.sh: 1263/5800 - the same guarded-ctor field-write-scheduling
 * delta documented on CreateLabelWidget/CreateTextEntryWidget/
 * CreateButtonWidget/CreateScrollListWidget applies here too (now 5
 * confirmed instances) - not chased further, same low-ROI category. */
extern "C" CStaticText *CreateStaticTextWidget(int x, int y, int w, int h,
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
extern "C" void BuildChatLogPanel(int arg1, int partnerRecord)
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
    PanelManager_Register(&g_uiPanelManager, p);
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
extern "C" void BuildCreateRoomDialog(void *manager, int arg2, int arg3)
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
    PanelManager_Register(&g_uiPanelManager, p);
}

/* 0x509110 - BuildBuddyPanel (docs/widgets.md: the shared buddy list).
 * SINGLETON keyed 20000: if already registered, just set the existing
 * panel's +0x1d reshow flag. Otherwise: (568,11) 211x267 with the
 * close-X (sprite 0x2bf) / Add (0x2bd) / Del (0x2be) labels along the
 * top and the page-7 scrollbar; front-inserted like the dialogs. */
extern "C" void BuildBuddyPanel()
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
    PanelManager_Register(&g_uiPanelManager, p);
}

/* 0x5087b0 - BuildEnterRoomNumberDialog (docs/widgets.md; __fastcall).
 * SINGLETON: if a (typeId 0, key 1) panel is already registered,
 * bring it to front and return. Otherwise: key 1 at (243,202) 314x160,
 * two 4-char CEditBoxes (the room number focused after the manager
 * focus sweep, then the password) and OK (sprite 0x579) / Cancel
 * (0x578) labels. Keeps the base ctor's insert-at-front default. */
extern "C" void __fastcall BuildEnterRoomNumberDialog(int arg)
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
    PanelManager_Register(&g_uiPanelManager, p);
}

/* 0x50e420 - the panel press core (bound as the panel-family slot-2
 * default). Pressed-state (+0x04) follows the rect test; children get
 * the mouse-down broadcast; a miss on both drops focus (a real virtual
 * SetFocus(0) on ourselves); a chrome grab (inside, no child took it,
 * not pinned) arms dragging and the press point becomes the drag
 * reference.
 * score.sh: 105/7000 - effectively perfect. */
bool CPanel::HandlePress(int x, int y)
{
    u8 inside = 0;
    if (!m_hidden &&
        m_x < x && x < m_x + m_width &&
        m_y < y && y < m_y + m_height) {
        inside = 1;
    }
    m_focused = inside;
    bool childTook = MouseDownChildren(x, y);
    if (m_focused == 0 && !childTook) {
        SetFocus(false);
    }
    if (m_focused == 1 && !childTook && m_pinned == 0) {
        m_dragging = 1;
    } else {
        m_dragging = 0;
    }
    m_lastPressX = x;
    m_lastPressY = y;
    return m_focused != 0 || childTook;
}

/* 0x505430 - the CPanel OnMouseDown default: run the press core, and
 * when the press was consumed, auto-focus the panel's FIRST edit box
 * unless some edit box already holds focus.
 * score.sh: 210/5200 - effectively perfect (two unresolved call
 * targets: the AtlThrow guard and the focus-set vtable call). */
bool CPanel::OnMouseDown(int x, int y)
{
    bool consumed = HandlePress(x, y);
    if (consumed) {
        unsigned int first = 0xffffffff;
        unsigned int count = (unsigned int)m_children.GetCount();
        for (unsigned int i = 0; i < count; ++i) {
            if (m_children[i]->m_typeId == 2) {
                if (first == 0xffffffff) {
                    first = i;
                }
                if (m_children[i]->m_focused != 0) {
                    return consumed;
                }
            }
        }
        if (first != 0xffffffff) {
            m_children[first]->SetFocus(true);
        }
    }
    return consumed;
}

/* WorldListRowHitTest - which server row the point lands on. The rows
 * are a 2-column grid inside the panel: cells 223x73 apart starting at
 * (+0x16, +0x2d) panel-relative, each 0xdf x 0x49; a row only counts
 * while its server's onlineFlag (the SoA at g_clientContext+0x3f809)
 * is 1. Returns the slot index or -1.
 * score.sh: 2510 -> 1815/5600. Writing the column/row split as `i % 2`/
 * `i / 2` instead of `i & 1`/`i / 2` matched the original's full signed-
 * modulo codegen (a bit-correction sequence, `andl $0x80000001`/
 * `decl`/`orl $-0x2`/`incl`, not a plain bitwise AND) - the original
 * source apparently used `%` for both column and row, not a mixed `&`/
 * `/` pair. Remaining delta is confirmed structural: `retl $0x4` in the
 * original vs. this compile's `retl $0x8` proves one of (x, y) arrives
 * in a register rather than as a normal stack argument, matching the
 * same "custom register convention" family documented on
 * CScrollBar::IsOverThumb/ThumbHeight. */
int CWorldListPanel::RowHitTest(int x, int y)
{
    int count = (int)*(unsigned char *)(g_clientContext + 0x3f808);
    for (int i = 0; i < count; ++i) {
        int cellX = m_x + 0x16 + (i % 2) * 0xf7;
        int cellY = m_y + 0x2d + (i / 2) * 0x49;
        if (cellX <= x && x <= cellX + 0xdf &&
            cellY <= y && y <= cellY + 0x49 &&
            *(char *)(g_clientContext + 0x3f809 + i) == 1) {
            return i;
        }
    }
    return -1;
}

extern "C" {
extern unsigned int DAT_007934f0;   /* per-connection context base (channel-1 send buffer inside:
                                     * u16 opcode at +0x4d4, write cursor at +0x44d0, payload
                                     * bytes from +0x4d0+cursor) */
extern unsigned int DAT_00e54a9c;   /* buddy/selector record count guard */
extern unsigned char DAT_00e54aa0;  /* selector record storage */
void AppendPacketBytes(void *record);    /* append a selector record to the pending packet */
void SendOutgoingPacket(int channelCtx);  /* flush/send the pending channel-1 packet */
void FUN_00402060(void);            /* buddy-list refresh */
extern const char s_disable_00551e68[];
extern unsigned int DAT_0056d118;
extern unsigned int DAT_00e9be94;   /* flat-ButtonWidget registry header */
extern const char s_active_00551e58[];
extern const char s_ready_00551e80[];
void InvokeWidget(int widgetId, int enabled);     /* connect-button enable, always widgetId=2 in this file (WorldListPanel) */
}
extern "C" CGameState *g_gameStateVTableArray[16]; /* 0x5b33f8 - the C tree
                                     * defines it (globals.c, as char*[16]);
                                     * C linkage so both sides bind the same
                                     * symbol */

/* WorldListPanel_OnMouseDown - the row-selection handler. Runs the
 * CPanel default first (a DIRECT 0x505430 call in the original, not
 * virtual); outside the panel that result stands. Inside, resolve the
 * clicked server row and - while the screen is interactable - store
 * the highlight into the State02 object, refresh the flat ButtonWidget
 * registry's connect button ("active" while the local player's record
 * flag is set, else "ready"; entries keyed <2 in the DAT_00e9be94
 * bucket, state 3/-1 only), and enable it iff a row is selected. The
 * registry walk is kept literal until the flat-ButtonWidget system is
 * reconstructed (PLAN.md Phase 1.6). */
bool CWorldListPanel::OnMouseDown(int x, int y)
{
    bool consumed = CPanel::OnMouseDown(x, y);
    if (m_hidden ||
        x <= m_x || m_x + m_width <= x ||
        y <= m_y || m_y + m_height <= y) {
        return consumed;
    }
    int slot = RowHitTest(x, y);
    CState02ServerSelect *st = (CState02ServerSelect *)g_gameStateVTableArray[2];
    if (st->m_uiDirty == 1) {
        st->m_highlightedSlot = slot;
        st->m_inputEnabled = (u8)(slot != -1);
        DAT_0056d118 = 0xffffffff;
        int *rec;
        if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0 &&
            (rec = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), rec[2] == 0) &&
            (rec[9] == 3 || rec[9] == -1)) {
            if ((char)rec[0x13] == 1) {
                ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(s_active_00551e58);
            } else {
                ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(s_ready_00551e80);
            }
        }
        if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
            rec = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
            unsigned int k = (unsigned int)rec[2];
            while (k < 2) {
                if (k == 1) {
                    if (rec[9] == 3 || rec[9] == -1) {
                        if ((char)rec[0x13] == 1) {
                            ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(s_active_00551e58);
                        } else {
                            ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(s_ready_00551e80);
                        }
                    }
                    break;
                }
                rec = (int *)rec[4];
                k = (unsigned int)rec[2];
            }
        }
        InvokeWidget(2, st->m_highlightedSlot != -1);
    }
    return consumed;
}

/* Set the flat-registry connect button (bucket entries keyed 0 and 1
 * in DAT_00e9be94) to a named state via its vtable slot 1 - the shared
 * shape all the world-list handlers repeat; kept literal pending the
 * flat-ButtonWidget reconstruction (PLAN.md Phase 1.6). */
static void SetRegistryButtonState(const char *stateName)
{
    int *rec;
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0 &&
        (rec = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), rec[2] == 0)) {
        ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(stateName);
    }
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
        rec = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
        unsigned int k = (unsigned int)rec[2];
        while (k < 2) {
            if (k == 1) {
                ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(stateName);
                break;
            }
            rec = (int *)rec[4];
            k = (unsigned int)rec[2];
        }
    }
}

/* WorldListPanel_OnCommand (0x50d810) - the tab switcher. Click (evt
 * 0) on id 0 = View All: reset the view mode/scroll/error array,
 * build and send the 0x1100 server-list page request ({u8 0, u8 0,
 * u16 0} = page 0), clear the highlight, disable the connect button
 * and mark tab 0 selected. Click on id 1 = Friends: view mode 2,
 * buddy refresh; with no selector records the SoA count is cleared
 * and the connect button reflects the local player record
 * (active/ready), otherwise a 0x1101 paged-fetch goes out with a
 * selector record appended and the button is disabled; tab 1 becomes
 * the selected one. EVERYTHING then falls through to the base
 * OnCommand default (focus nav + parent forward), exactly as the
 * original tail-calls 0x50eb10. */
void CWorldListPanel::OnCommand(int evt, int id, int arg)
{
    unsigned char *ctx = (unsigned char *)DAT_007934f0;
    CState02ServerSelect *st = (CState02ServerSelect *)g_gameStateVTableArray[2];
    if (evt == 0 && id == 0) {
        st->m_scrollA = 0;
        st->m_viewMode = 0;
        for (int i = 0; i < 16; ++i) {
            st->m_slotError[i] = 0;
        }
        *(int *)(ctx + 0x44d0) = 6;
        *(unsigned short *)(ctx + 0x4d4) = 0x1100;
        *(unsigned char *)(ctx + 0x4d6) = 0;
        int cur = *(int *)(ctx + 0x44d0);
        *(int *)(ctx + 0x44d0) = cur + 1;
        *(unsigned char *)(ctx + 0x4d1 + cur) = 0;
        *(int *)(ctx + 0x44d0) += 1;
        st->m_scrollA = 0;
        st->m_scrollOffset = 0;
        *(unsigned short *)(ctx + 0x4d0 + *(int *)(ctx + 0x44d0)) = 0;
        *(int *)(ctx + 0x44d0) += 2;
        SendOutgoingPacket((int)ctx);
        st->m_highlightedSlot = -1;
        DAT_0056d118 = 0;
        SetRegistryButtonState(s_disable_00551e68);
        InvokeWidget(2, 0);
        int t = FindChildIndex(1, 0);
        if (t != m_children.GetCount()) {
            ((CLabel *)m_children[(unsigned int)t])->m_tabSelected = 1;
        }
        t = FindChildIndex(1, 1);
        if (t != m_children.GetCount()) {
            ((CLabel *)m_children[(unsigned int)t])->m_tabSelected = 0;
        }
    } else if (evt == 0 && id == 1) {
        st->m_viewMode = 2;
        st->m_scrollA = 0;
        FUN_00402060();
        st->m_highlightedSlot = -1;
        bool enable;
        if (DAT_00e54a9c == 0) {
            *(unsigned char *)(g_clientContext + 0x3f808) = 0;
            st->m_unk1c = (int)(st->m_unk1c & ~0xff); /* byte +0x1c cleared */
            DAT_0056d118 = 0xffffffff;
            int *rec;
            enable = st->m_highlightedSlot != -1;
            if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0 &&
                (rec = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), rec[2] == 0) &&
                (rec[9] == 3 || rec[9] == -1)) {
                ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(
                    (char)rec[0x13] == 1 ? s_active_00551e58 : s_ready_00551e80);
            }
            if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
                rec = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
                unsigned int k = (unsigned int)rec[2];
                while (k < 2) {
                    if (k == 1) {
                        if (rec[9] == 3 || rec[9] == -1) {
                            ((void (__cdecl *)(const char *))*(void **)(rec[0] + 4))(
                                (char)rec[0x13] == 1 ? s_active_00551e58 : s_ready_00551e80);
                        }
                        break;
                    }
                    rec = (int *)rec[4];
                    k = (unsigned int)rec[2];
                }
            }
        } else {
            *(unsigned short *)(ctx + 0x4d4) = 0x1101;
            *(int *)(ctx + 0x44d0) = 6;
            st->m_scrollA = 0;
            st->m_scrollOffset = 0;
            AppendPacketBytes(&DAT_00e54aa0);
            SendOutgoingPacket((int)ctx);
            DAT_0056d118 = 0;
            SetRegistryButtonState(s_disable_00551e68);
            enable = false;
        }
        InvokeWidget(2, enable);
        int t = FindChildIndex(1, 0);
        if (t != m_children.GetCount()) {
            ((CLabel *)m_children[(unsigned int)t])->m_tabSelected = 0;
        }
        t = FindChildIndex(1, 1);
        if (t != m_children.GetCount()) {
            ((CLabel *)m_children[(unsigned int)t])->m_tabSelected = 1;
        }
    }
    CWidget::OnCommand(evt, id, arg);
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
extern "C" CWorldListPanel * BuildWorldListPanel(void *manager)
{
    /* the argument is &g_uiPanelManager (confirmed by State02's
     * OnEnter call site); the original forwards it into the scrollbar
     * factory's never-read first stack slot */
    (void)manager;
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
    p->AddChild(CreateScrollListWidget(0, 0, 0x203, 0x4a, 0x12, 0x179, 0));
    PanelManager_Register(&g_uiPanelManager, p);
    return p;
}

/* TEMPORARY extern "C" compatibility shim - see the note at the bottom of
 * Widget.cpp. src/ui_widget/WorldListRowHitTest.c (0x50df40) was the raw
 * port of this exact function (CWorldListPanel::RowHitTest) - deleted in
 * favor of this shim. Unlike most shims in this file, this one has a
 * clean explicit (this, x, y) signature rather than needing inline-asm
 * register capture: its only remaining caller (src/unnamed/
 * FUN_0050d7a0.cpp) is already a ported .cpp file under this project's
 * control, so the call site itself was updated to pass all three
 * arguments explicitly instead of relying on the original's register-
 * passed this/x (which a raw C caller can't safely be changed to do,
 * but an already-ported C++ caller can). REMOVE once nothing calls this
 * by the old name at all (in which case just call RowHitTest directly). */
extern "C" int WorldListRowHitTest(CWorldListPanel *this_, int x, int y)
{
    return this_->RowHitTest(x, y);
}

