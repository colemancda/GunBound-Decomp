/* FUN_004e5cc0 - 0x004e5cc0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e5cc0(int regEbx,int regEax)

{
  int iVar1;
  int *unaff_EDI;
  
  if ((uint)unaff_EDI[1] < (uint)(regEax + regEbx)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (unaff_EDI[1] - regEax) - regEbx;
  if (iVar1 != 0) {
    _memmove((void *)(regEax * 0x4004 + *unaff_EDI),
             (void *)((regEax + regEbx) * 0x4004 + *unaff_EDI),iVar1 * 0x4004);
  }
  unaff_EDI[1] = unaff_EDI[1] - regEbx;
  return;
}

