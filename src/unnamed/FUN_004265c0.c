/* FUN_004265c0 - 0x004265c0 in the original binary.
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
      cVar1 = FUN_00500c00(unaff_ESI,unaff_ESI[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = FUN_00426960(unaff_ESI,in_EAX,local_c);
  }
  return iVar2 + 4;
}

