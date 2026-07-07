/* FUN_0044c3d0 - 0x0044c3d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0044c3d0(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = 0xe1;
  do {
    iVar3 = 0;
    iVar1 = 0xb5;
    do {
      if ((((iVar1 + -0xa0 < param_2) && (param_2 < iVar1)) && (iVar2 + -0x9c < param_3)) &&
         ((param_3 < iVar2 &&
          (iVar3 + (iVar4 + *(int *)(param_1 + 0x450) * 3) * 3 < *(int *)(param_1 + 0x2d110))))) {
        return iVar3 + iVar4 * 3;
      }
      iVar1 = iVar1 + 0xa3;
      iVar3 = iVar3 + 1;
    } while (iVar1 < 0x29e);
    iVar2 = iVar2 + 0xa1;
    iVar4 = iVar4 + 1;
    if (0x2c3 < iVar2) {
      return -1;
    }
  } while( true );
}

