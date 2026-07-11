/* FUN_0044c6a0 - 0x0044c6a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0044c6a0(int *param_1)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_EDI;
  
  if ((uint)param_1[1] < (uint)(in_EAX + unaff_EDI)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (param_1[1] - in_EAX) - unaff_EDI;
  iVar2 = *param_1 + in_EAX * 0x450;
  for (iVar3 = unaff_EDI; iVar3 != 0; iVar3 = iVar3 + -1) {
    FUN_00426810(iVar2);
    iVar2 = iVar2 + 0x450;
  }
  if (iVar1 != 0) {
    _memmove((void *)(*param_1 + in_EAX * 0x450),(void *)((in_EAX + unaff_EDI) * 0x450 + *param_1),
             iVar1 * 0x450);
  }
  param_1[1] = param_1[1] - unaff_EDI;
  return;
}

