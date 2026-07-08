/* FUN_0050df40 - 0x0050df40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_0050df40(int param_1)

{
  int iVar1;
  int iVar2;
  int in_EAX;
  uint uVar3;
  uint uVar4;
  int unaff_EDI;
  
  uVar4 = 0;
  if (*(byte *)(g_clientContext + 0x3f808) != 0) {
    do {
      uVar3 = uVar4 & 0x80000001;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
      }
      iVar1 = uVar3 * 0xf7 + 0x16 + *(int *)(in_EAX + 0x28);
      iVar2 = ((int)uVar4 / 2) * 0x49 + 0x2d + *(int *)(in_EAX + 0x2c);
      if ((((iVar1 <= unaff_EDI) && (unaff_EDI <= iVar1 + 0xdf)) && (iVar2 <= param_1)) &&
         ((param_1 <= iVar2 + 0x49 && (*(char *)(g_clientContext + 0x3f809 + uVar4) == '\x01')))) {
        return uVar4;
      }
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < (int)(uint)*(byte *)(g_clientContext + 0x3f808));
  }
  return 0xffffffff;
}

