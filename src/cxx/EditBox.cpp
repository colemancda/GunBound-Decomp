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
extern unsigned int g_sharedTextInputControl;
/* 0x506e70: points the shared EDIT control at a field (EAX = the field in
 * the original; promoted to a parameter in the C port). */
void ActivateLegacyTextInputField(int thisObj);
/* 0x507090, slot 5. __thiscall in the original; ghidra_types.h erases
 * that to cdecl in the C definition, so `this` is the first stack
 * argument here. */
unsigned int TextEntry_DispatchKey(int this_, int key);
/* 0x5071a0, slot 9. __fastcall(int) in C: `this` in ECX, as in the
 * original (`mov ebx,ecx` at 0x5071a4, plain ret). */
void __fastcall TextEntry_Update(int this_);
}

/* 0x507090, vtable 0x557c84 slot 5 (word at 0x557c98). The body
 * replaces the inherited child key broadcast and does not call it, so the
 * forward does not call the base either. The result is AL. */
bool CEditBox::DispatchKey(int key)
{
    return (TextEntry_DispatchKey((int)this, key) & 0xff) != 0;
}

/* 0x5071a0, vtable 0x557c84 slot 9 (word at 0x557ca8). Draws the field
 * itself and makes no virtual calls. The original has no child Update
 * broadcast (no call to 0x50ecf0 between 0x5071a0 and its ret at
 * 0x50730f), so the forward does not add CWidget::Update. */
void CEditBox::Update()
{
    TextEntry_Update((int)this);
}

/* 0x506fb0, vtable 0x557c84 slot 0 (SetFocus). Carved 2026-10-30 from
 * the disassembly (21 bytes, ends in ret 4):
 *
 *   mov eax,ecx / mov cl,[esp+4] / test cl,cl
 *   mov [eax+4],cl                  ; the base store, m_focused = active
 *   je  0x506fc2
 *   call 0x506e70                   ; EAX = this
 *   ret 4
 *
 * So gaining focus also hands the shared EDIT control to this field.
 * Losing it is only the store, like the base 0x50e860. */
void CEditBox::SetFocus(bool active)
{
    m_focused = active;
    if (active) {
        ActivateLegacyTextInputField((int)this);
    }
}

/* 0x506fd0, vtable 0x557c84 slot 2 (OnMouseDown). Carved 2026-10-30
 * from the disassembly (88 bytes, ret 8 at 0x507013/0x507025).
 * esi = x ([esp+8] after one push), edx = y. If m_hidden (+0x1e) is clear
 * and the point is strictly inside the rect (the jge pairs at
 * 0x506fe4-0x506fff against +0x28/+0x30 and +0x2c/+0x34), it sets
 * m_focused = 1 (0x507003), calls 0x506e70 with EAX = this (0x507007),
 * and returns 1. Otherwise it returns the result of the non-virtual
 * child broadcast `call 0x50e8e0` (ECX still this, x and y pushed). */
bool CEditBox::OnMouseDown(int x, int y)
{
    if (m_hidden == '\0' && m_x < x && x < m_x + m_width &&
        m_y < y && y < m_y + m_height) {
        m_focused = 1;
        ActivateLegacyTextInputField((int)this);
        return true;
    }
    return MouseDownChildren(x, y);
}

/* 0x507f60 - the text-entry factory (docs' CreateTextEntryWidget;
 * real signature (id, x, y, w, h, maxLen) - no msgId is stored). Same
 * guarded-default-ctor + unguarded-pokes split as CreateLabelWidget.
 * score.sh: 1780/4200 - the m_text zero-loop (rep stosl) and later field
 * pokes all match; remaining delta is field-write ordering/register
 * choice within the inlined default ctor (same category of issue as
 * CreateLabelWidget's ctor - vtable-pointer-write scheduling, not a
 * logic difference). Not chased further - same low ROI as
 * CreateLabelWidget's equivalent delta. */
extern "C" CEditBox *CreateTextEntryWidget(int id, int x, int y, int w, int h, int maxLen)
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
 * container draw broadcast to the children.
 * score.sh: 315/3800 (660 -> 315) - effectively perfect. Caching
 * `m_text` into a local pointer up front (used for both the
 * GetWindowTextA call and the fallback clear) matches the original's
 * single early address computation, reused both places; loop-hoist fix
 * also applied. Remaining score is the two unresolved external call
 * targets (GetWindowTextA import, AtlThrow guard). */
void CEditBox::Draw()
{
    if (m_focused != '\0') {
        char *text = m_text;
        int got = 0;
        if (*(char *)(g_sharedTextInputControl + 8) != '\0') {
            got = GetWindowTextA(*(HWND *)(g_sharedTextInputControl + 4), text, 0x80);
        }
        if (got == 0) {
            text[0] = '\0';
        }
    }
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            m_children[i]->Draw();
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}
