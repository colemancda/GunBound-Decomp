/* ScrollListWidget_OnMouseUp - 0x0050f5f0 in the original binary.
 *
 * Scroll-list widget mouse-up / release handler (class vtable
 * PTR_LAB_00557e90). Records the position and clears the press/drag state
 * flags (+0x44/+0x45/+4), ending any in-progress scrollbar-thumb drag, then
 * returns whether the release was inside the widget rect.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall ScrollListWidget_OnMouseUp(int param_1,int param_2,int param_3)

{
  char cVar1;
  
  *(int *)(param_1 + 0x4c) = param_2;
  *(int *)(param_1 + 0x50) = param_3;
  *(undefined1 *)(param_1 + 0x44) = 0;
  *(undefined1 *)(param_1 + 0x45) = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  cVar1 = FUN_0050e950(param_2,param_3);
  if ((cVar1 == '\0') &&
     ((((*(char *)(param_1 + 0x1e) != '\0' || (param_2 <= *(int *)(param_1 + 0x28))) ||
       (*(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28) <= param_2)) ||
      ((param_3 <= *(int *)(param_1 + 0x2c) ||
       (*(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c) <= param_3)))))) {
    return 0;
  }
  return 1;
}

