/* FUN_005061e0 - 0x005061e0 in the original binary.
 *
 * CWidget::OnCommand override (vtable slot 7, +0x1c) shared by the panel
 * vtables 0x557d28 (built by FUN_00509410, panel id 0x7531) and 0x557e18
 * (built by BuildItemTooltipPanel, panel id 0x2713). Carved 2026-10-30
 * from the disassembly (37 bytes, 0x5061e0-0x506204):
 *
 *   mov eax,[esp+4] / test eax,eax / mov edx,[esp+8] / jne 0x5061f4
 *   test edx,edx / jne 0x5061f4
 *   mov byte [ecx+0x1d],1            ; evt 0 from child 0: set +0x1d
 *   push esi / mov esi,[esp+0x10]    ; arg
 *   push esi / push edx / push eax / call 0x50eb10   ; ECX still this
 *   pop esi / ret 0xc
 *
 * So a click from child 0 (each builder's label 0) sets the panel's
 * +0x1d byte, the same byte the singleton builders set on an
 * already-registered panel (BuildItemDescriptionTooltip's
 * `*(iVar2 + 0x1d) = 1`; Widget.h's m_unk1d), and every event then falls
 * through to the base Widget_OnCommandDefault. __thiscall in the original, erased to cdecl
 * here (`this` first), like the sibling OnCommand ports.
 *
 * NOT WIRED: neither vtable has a C++ class. Both builders are raw C and
 * install the placeholder global PTR_LAB_00557d28/PTR_LAB_00557e18,
 * which has no slots.
 */
#include "ghidra_types.h"


void __thiscall FUN_005061e0(int param_1,int param_2,int param_3,int param_4)

{
  if ((param_2 == 0) && (param_3 == 0)) {
    *(undefined1 *)(param_1 + 0x1d) = 1;
  }
  Widget_OnCommandDefault(param_1,param_2,param_3,param_4);
  return;
}
