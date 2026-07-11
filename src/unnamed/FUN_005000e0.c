/* FUN_005000e0 - 0x005000e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005000e0(void)

{
  char cVar1;
  int iVar2;
  int *unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4 [4];
  
  iVar2 = FUN_00500ef0(unaff_EDI,&local_c,local_4);
  if (iVar2 == 0) {
    if (*unaff_ESI == 0) {
      cVar1 = FUN_00500c00(unaff_ESI,unaff_ESI[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    FUN_00501420(local_8,local_c);
  }
  return;
}

