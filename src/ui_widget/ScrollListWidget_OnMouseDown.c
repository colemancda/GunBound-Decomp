/* ScrollListWidget_OnMouseDown - 0x0050f500 in the original binary.
 *
 * Scroll-list widget mouse-down handler (class vtable PTR_LAB_00557e90).
 * Records the click position and, if it lands on the scrollbar thumb rect
 * (computed from scroll position +0x40, content total +0x38, track height
 * +0x34), begins a drag: stores the grab offset at +0x48 and sets the
 * dragging flag +0x45. Otherwise records a plain press at +0x44.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall ScrollListWidget_OnMouseDown(int param_1,int param_2,int param_3)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char local_1;
  
  *(int *)(param_1 + 0x4c) = param_2;
  *(int *)(param_1 + 0x50) = param_3;
  local_1 = '\0';
  if ((((*(char *)(param_1 + 0x1e) == '\0') && (*(int *)(param_1 + 0x28) < param_2)) &&
      (param_2 < *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28))) &&
     ((*(int *)(param_1 + 0x2c) < param_3 &&
      (param_3 < *(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c))))) {
    local_1 = '\x01';
  }
  if ((*(int *)(param_1 + 0x28) <= param_2) &&
     (param_2 <= *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28))) {
    iVar1 = *(int *)(param_1 + 0x38);
    iVar4 = *(int *)(param_1 + 0x2c);
    iVar5 = iVar4;
    if (0 < iVar1) {
      iVar5 = iVar4 + (*(int *)(param_1 + 0x40) * *(int *)(param_1 + 0x34)) / iVar1;
    }
    if ((iVar5 <= param_3) && (iVar3 = FUN_0050e050(), param_3 <= iVar3 + iVar5)) {
      if (0 < iVar1) {
        iVar4 = iVar4 + (*(int *)(param_1 + 0x40) * *(int *)(param_1 + 0x34)) / iVar1;
      }
      *(int *)(param_1 + 0x48) = iVar4 - param_3;
      *(undefined1 *)(param_1 + 0x45) = 1;
      *(undefined1 *)(param_1 + 0x44) = 0;
      goto LAB_0050f5bf;
    }
  }
  *(char *)(param_1 + 0x44) = local_1;
LAB_0050f5bf:
  cVar2 = FUN_0050e8e0(param_2,param_3);
  if ((cVar2 == '\0') && (local_1 == '\0')) {
    return 0;
  }
  return 1;
}

