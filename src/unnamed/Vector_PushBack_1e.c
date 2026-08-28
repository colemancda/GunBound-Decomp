/* Vector_PushBack_1e - 0x00502920 in the original binary.
 *
 * Named above (2026-08-28, from its Vector_*_34 twin), but still a
 * raw/near-verbatim port of Ghidra's decompiler output, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 *
 * EAX RECOVERED (2026-08-25) from the single site in FUN_00501770, under the
 * -0x4990 frame constant that function's earlier recoveries established and
 * that four independent slots agree on: `lea eax,[esp+0x3c]` with no push
 * pending = &local_4954.
 */
#include "ghidra_types.h"


void Vector_PushBack_1e(undefined4 param_1,int regEax)

{
  int iVar1;
  
  iVar1 = *(int *)(regEax + 4);
  if ((iVar1 != 0) &&
     ((uint)((*(int *)(regEax + 8) - iVar1) / 0x1e) <
      (uint)((*(int *)(regEax + 0xc) - iVar1) / 0x1e))) {
    iVar1 = *(int *)(regEax + 8);
    /* DROPPED-REG FIX 2026-08-28: mis-slotted, not just short - the
       original is `mov ecx,1` (count) / `mov edx,ebp` (the element,
       param_1) / `mov eax,esi` (the end = dest) / `push [esp+0x14]`
       (the never-read allocator word) at 0x502971-0x50297e; the port
       had param_1 landing in the count. */
    Vector_UninitFillN_1e(1,(undefined4 *)param_1,param_1,(undefined4 *)iVar1);
    *(int *)(regEax + 8) = iVar1 + 0x1e;
    return;
  }
  Vector_Insert_1e((int *)&param_1,*(undefined4 *)(regEax + 8),(undefined4 *)param_1,regEax);
  return;
}

