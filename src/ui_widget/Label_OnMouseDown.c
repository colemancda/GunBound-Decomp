/* Label_OnMouseDown - 0x005052e0 in the original binary.
 *
 * Label/button widget mouse-down (vtable slot 3): on a hit, fires the parent's OnCommand(0, id, 0) - the click event that reaches each screen's command dispatcher. See docs/widgets.md. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall Label_OnMouseDown(int *param_1,int param_2,int param_3)

{
  char cVar1;
  
  if (((((*(char *)((int)param_1 + 0x1e) == '\0') && (param_1[10] < param_2)) &&
       (param_2 < param_1[0xc] + param_1[10])) &&
      ((param_1[0xb] < param_3 && (param_3 < param_1[0xd] + param_1[0xb])))) &&
     (((char)param_1[0xe] != '\0' && ((char)param_1[7] != '\0')))) {
    (**(code **)(*param_1 + 0x1c))(0,param_1[9],0);
  }
  cVar1 = FUN_0050e2f0(param_2,param_3);
  if ((cVar1 == '\0') &&
     (((*(char *)((int)param_1 + 0x1e) != '\0' || (param_2 <= param_1[10])) ||
      ((param_1[0xc] + param_1[10] <= param_2 ||
       ((param_3 <= param_1[0xb] || (param_1[0xd] + param_1[0xb] <= param_3)))))))) {
    return 0;
  }
  return 1;
}

