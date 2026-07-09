/* CEditBox methods - promoted from the raw C port
 * src/ui_widget/TextEntry_SyncFromControl.c (0x507030).
 * See src/cxx/README.md. */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "Widget.h"
#include <string.h>

extern "C" {
/* The shared overlay EDIT-control singleton (one Win32 EDIT reused by
 * whichever text field has focus): +0x04 holds its HWND, +0x08 a
 * live/visible byte flag. Object layout not reconstructed yet, so the
 * raw-port global keeps its untyped uint form here. */
extern unsigned int DAT_007934e4;
}

/* 0x507f60 - the text-entry factory (docs' CreateTextEntryWidget;
 * real signature (id, x, y, w, h, maxLen) - no msgId is stored). Same
 * guarded-default-ctor + unguarded-pokes split as CreateLabelWidget. */
CEditBox * __stdcall CreateTextEntryWidget(int id, int x, int y, int w, int h, int maxLen)
{
    CEditBox *p = new CEditBox();
    p->m_id = id;
    p->m_x = x;
    p->m_y = y;
    p->m_width = w;
    p->m_height = h;
    p->m_maxLen = maxLen;
    return p;
}

/* 0x507030 (TextEntry_SyncFromControl), vtable slot 8. When this field
 * is active (+0x04 base flag) and the shared EDIT control is live,
 * pull the OS control's current text into m_text; if the field is
 * active but the control is gone/empty, clear m_text. Then the usual
 * container draw broadcast to the children. */
void CEditBox::Draw()
{
    if (m_unk04 != '\0') {
        int got = 0;
        if (*(char *)(DAT_007934e4 + 8) != '\0') {
            got = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4), m_text, 0x80);
        }
        if (got == 0) {
            m_text[0] = '\0';
        }
    }
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
        do {
            m_children[i]->Draw();
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}
