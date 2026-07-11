/* FUN_004f7210 - 0x004f7210 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004f7210(undefined4 param_1,int param_2,int param_3)

{
  short sVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  
  iVar2 = in_EAX / 0xc;
  if ((in_EAX % 0xc == 0) && (iVar2 * 0x10 <= param_3)) {
    iVar3 = 0;
    if (0 < iVar2) {
      do {
        sVar1 = EncodeCipherBlock(param_2,param_1);
        if (sVar1 != 1) {
          return 0;
        }
        iVar3 = iVar3 + 1;
        param_2 = param_2 + 0x10;
      } while (iVar3 < iVar2);
    }
    return 1;
  }
  return 0;
}

