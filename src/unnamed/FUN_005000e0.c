/* FUN_005000e0 - 0x005000e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ESI RECOVERED (2026-08-24): it is callerThis + 0x290, FUN_004fe8d0's
 * __thiscall param_1 plus a fixed offset (`lea esi,[ebx+0x290]`, EBX never
 * written after the caller's entry).
 *
 * unaff_EDI is a SECOND dropped register and stays open: at the call site it
 * is `mov edi,[esp+0x1a]` -- a caller stack local, which needs the esp model
 * and a witness this function does not have.
 */
#include "ghidra_types.h"


void FUN_005000e0(int *regEsi)

{
  char cVar1;
  int iVar2;
  undefined4 unaff_EDI;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4 [4];
  
  iVar2 = FUN_00500ef0(unaff_EDI,&local_c,local_4);
  if (iVar2 == 0) {
    if (*regEsi == 0) {
      cVar1 = FUN_00500c00(regEsi,regEsi[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    FUN_00501420(local_8,local_c);
  }
  return;
}

