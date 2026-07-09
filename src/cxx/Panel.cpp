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
}

/* C++-linkage factories defined in Label.cpp / ScrollBar.cpp */
CLabel * __stdcall CreateLabelWidget(int id, int spriteId, int x, int y, int w, int h);
CScrollBar * __stdcall CreateScrollListWidget(int spriteBase, int total,
                                              int x, int y, int w, int h, int pageSize);

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
    viewAll->m_unk3a[0] = 1;
    p->AddChild(viewAll);
    p->AddChild(CreateLabelWidget(1, 0x44d, 0x1a3, 0x1eb, 0x4a, 0x1a));
    p->AddChild(CreateScrollListWidget(0, total, 0x203, 0x4a, 0x12, 0x179, 0));
    FUN_0050eea0(p);
    return p;
}
