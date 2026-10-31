/* TextEntry_DispatchMouse - 0x00507170 in the original binary.
 *
 * CEditBox (vtable 0x557c84) slot 6: the word at 0x557c9c is 0x507170.
 * Written directly as CEditBox::DispatchMouse (2026-10-30). Before this,
 * the file defined a free extern "C" FUN_00507170 that nothing called,
 * and the C++ CEditBox inherited CWidget::DispatchMouse instead.
 *
 * NAMED 2026-10-31, CERTAIN (was FUN_00507170). The name is the file's
 * and PROGRESS.csv's; the code itself is the member above, so no C
 * symbol carries it. Vtable 0x557c84 is stored only by
 * CreateTextEntryWidget (at 0x507f9f), and slot 6 is
 * CWidget::DispatchMouse, whose base body is
 * Widget_DispatchMouseToChildren (0x50eab0). The TextEntry_ prefix is the
 * one this class's C functions carry (slot 8 is TextEntry_SyncFromControl,
 * slot 5 TextEntry_DispatchKey).
 *
 * Disassembly (34 bytes, ret 4):
 *   push esi / mov esi,ecx          ; this
 *   mov al,[esi+4] / test al,al     ; m_focused
 *   push edi / mov edi,[esp+0xc]    ; the one stack argument
 *   je 0x507185
 *   push edi / call 0x50ea50        ; ECX still this: CWidget::DispatchKey
 *   push edi / mov ecx,esi
 *   call 0x50eab0                   ; CWidget::DispatchMouse
 *   pop edi / pop esi / ret 4       ; AL from 0x50eab0 is the result
 *
 * Both calls are DIRECT calls to the base bodies (0x50ea50 and 0x50eab0
 * are slots 5 and 6 of the base vtables, e.g. 0x557bbc). They are not
 * vtable dispatches. The old port called this_->DispatchKey and
 * this_->DispatchMouse virtually. On a CEditBox, the second call would
 * recurse into this function forever, and the first would reach
 * CEditBox's own slot 5 (0x507090) instead of the child broadcast. Both
 * are qualified CWidget:: calls here. The 0x50ea50 result is discarded.
 *
 * Kept as the body rather than a forward. It needs the non-virtual base
 * members, which only C++ can name, and no C code calls 0x507170
 * (callsite_regs finds no direct calls; the only reference is the vtable
 * word).
 */
#include "../cxx/Widget.h"

bool CEditBox::DispatchMouse(int key)
{
    if (m_focused != '\0') {
        CWidget::DispatchKey(key);
    }
    return CWidget::DispatchMouse(key);
}
