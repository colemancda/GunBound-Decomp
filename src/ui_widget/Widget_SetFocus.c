/* Widget_SetFocus - 0x0050e860 in the original binary.
 *
 * CWidget's vtable slot 0 (see src/cxx/Widget.h), referenced by 23 vtables.
 * NEW CARVE (2026-08-19): Ghidra never carved this range as a function - it
 * is reachable only through the widget vtables - so this port is hand-derived
 * from the capstone disassembly of 0x50e860..0x50e869.  It is three
 * instructions:
 *
 *     0050e860  mov al, byte ptr [esp + 4]     ; the one stack argument
 *     0050e864  mov byte ptr [ecx + 4], al     ; this->m_focused = it
 *     0050e867  ret 4
 *
 * Its brevity is the whole point of Widget.h's slot-0 correction: a
 * three-instruction one-byte setter is NOT a destructor, so this vtable has
 * no virtual dtor slot at all, and slot 10 resolving to the same address is
 * identical-code folding of another trivial setter rather than a "secondary
 * destructor".  Matches CWidget::SetFocus in src/cxx/Widget.cpp exactly.
 *
 * Raw/near-verbatim hand port - not hand-verified against a running client.
 * See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void __fastcall Widget_SetFocus(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 4) = param_2;
  return;
}
