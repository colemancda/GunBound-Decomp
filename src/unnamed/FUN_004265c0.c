/* FUN_004265c0 - 0x004265c0 in the original binary.
 *
 * STILL-OPEN regEax (2026-09-01 workflow triage): both callers pass
 * EAX/ESI values that exist in NEITHER caller's C - FUN_00426030 and
 * FUN_00426090 forward their own dead-coded in_EAX (key string) and
 * in_ECX (+0x6aa41c / +0x6aa44c object base); their outer caller
 * 0x403c43 (unported fn 0x403c00) passes EAX=[esp+0x30] name string,
 * ECX=[0x5b3484]. Prerequisite: promote FUN_00426030/FUN_00426090
 * with their own regEax/regEcx first.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004265c0(void)

{
  char cVar1;
  undefined4 in_EAX;
  int iVar2;
  int *unaff_ESI;
  undefined4 local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar2 = FUN_00426780(local_8,&local_c,local_4);
  if (iVar2 == 0) {
    if (*unaff_ESI == 0) {
      cVar1 = HashMap_InitHashTable(unaff_ESI,unaff_ESI[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = FUN_00426960(unaff_ESI,in_EAX,local_c);
  }
  return iVar2 + 4;
}

