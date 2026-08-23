/* FUN_00415470 - 0x00415470 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00415470(undefined4 param_1,int param_2)

{
  int iVar1;
  int unaff_EBX;
  int *unaff_EDI;
  
  if ((uint)unaff_EDI[1] < (uint)(param_2 + unaff_EBX)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (unaff_EDI[1] - param_2) - unaff_EBX;
  if (iVar1 != 0) {
    _memmove((void *)(*unaff_EDI + param_2 * 4),(void *)(*unaff_EDI + (param_2 + unaff_EBX) * 4),
             iVar1 * 4);
  }
  unaff_EDI[1] = unaff_EDI[1] - unaff_EBX;
  return;
}

