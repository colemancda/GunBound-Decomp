/* FUN_00503e30 - 0x00503e30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00503e30(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *unaff_ESI;
  int *unaff_EDI;
  undefined4 local_8;
  undefined1 local_4 [4];
  
  iVar2 = FUN_004fef70(param_1,&param_1,local_4);
  if (iVar2 == 0) {
    if (*unaff_EDI == 0) {
      cVar1 = FUN_00500c00(unaff_EDI,unaff_EDI[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = FUN_00504480(local_8,param_1);
  }
  *(undefined4 *)(iVar2 + 0x12) = *unaff_ESI;
  *(undefined4 *)(iVar2 + 0x16) = unaff_ESI[1];
  *(undefined4 *)(iVar2 + 0x1a) = unaff_ESI[2];
  *(undefined2 *)(iVar2 + 0x1e) = *(undefined2 *)(unaff_ESI + 3);
  return;
}

