/* FUN_004264d0 - 0x004264d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004264d0(int param_1,int regEsi)

{
  int iVar1;
  int iVar2;
  int *unaff_EBX;
  
  if ((uint)unaff_EBX[1] < (uint)(param_1 + regEsi)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (unaff_EBX[1] - param_1) - regEsi;
  for (iVar2 = regEsi; iVar2 != 0; iVar2 = iVar2 + -1) {
    FUN_00405320();
  }
  if (iVar1 != 0) {
    _memmove((void *)(*unaff_EBX + param_1 * 4),(void *)(*unaff_EBX + (param_1 + regEsi) * 4),
             iVar1 * 4);
  }
  unaff_EBX[1] = unaff_EBX[1] - regEsi;
  return;
}

