/* Widget_OnMouseUp - 0x0050e4c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall Widget_OnMouseUp(int param_1,int param_2,int param_3)

{
  char cVar1;
  
  *(undefined1 *)(param_1 + 0x39) = 0;
  cVar1 = Widget_MouseUpChildren(param_2,param_3);
  if ((cVar1 == '\0') &&
     ((((*(char *)(param_1 + 0x1e) != '\0' || (param_2 <= *(int *)(param_1 + 0x28))) ||
       (*(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28) <= param_2)) ||
      ((param_3 <= *(int *)(param_1 + 0x2c) ||
       (*(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c) <= param_3)))))) {
    return 0;
  }
  return 1;
}

