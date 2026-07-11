/* Widget_DispatchMouseToChildren - 0x0050eab0 in the original binary.
 *
 * Base widget mouse-input broadcast (vtable slot 6): forwards the event to each child's slot 6. See docs/widgets.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall Widget_DispatchMouseToChildren(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  
  if (*(char *)(param_1 + 0x1e) != '\0') {
    return 0;
  }
  uVar2 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      (**(code **)(**(int **)(*(int *)(param_1 + 0xc) + uVar2 * 4) + 0x18))(param_2);
      if (cVar1 != '\0') {
        return 1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_1 + 0x10));
  }
  return 0;
}

