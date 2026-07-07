/* FUN_00504790 - 0x00504790 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00504790(char *param_1)

{
  int iVar1;
  int iVar2;
  int unaff_ESI;
  uint uVar3;
  
  uVar3 = 0;
  iVar2 = 0;
  while( true ) {
    if (*(int *)(unaff_ESI + 0x1aa4) == 0) {
      return 0;
    }
    if ((uint)((*(int *)(unaff_ESI + 0x1aa8) - *(int *)(unaff_ESI + 0x1aa4)) / 0x12) <= uVar3)
    break;
    iVar1 = __strnicmp((char *)(*(int *)(unaff_ESI + 0x1aa4) + iVar2),param_1,0x10);
    if (iVar1 == 0) {
      return 1;
    }
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + 0x12;
  }
  return 0;
}

