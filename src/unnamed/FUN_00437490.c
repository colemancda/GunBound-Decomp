/* FUN_00437490 - 0x00437490 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_00437490(void)

{
  uint uVar1;
  int in_EAX;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  uVar2 = in_EAX << 3;
  iVar4 = 0;
  do {
    uVar1 = *(uint *)(*(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c) + 4);
    iVar3 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    if (0x186a3 < uVar1) {
      return uVar2;
    }
    while (uVar1 != 0x186a3) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
      if (0x186a3 < uVar1) {
        return uVar2;
      }
    }
    iVar3 = *(int *)(iVar3 + 0x10);
    bVar5 = *(uint *)(iVar3 + 8) == uVar2;
    if (uVar2 <= *(uint *)(iVar3 + 8) && !bVar5) {
      return uVar2;
    }
    while (!bVar5) {
      iVar3 = *(int *)(iVar3 + 0x10);
      bVar5 = *(uint *)(iVar3 + 8) == uVar2;
      if (uVar2 < *(uint *)(iVar3 + 8)) {
        return uVar2;
      }
    }
    iVar4 = iVar4 + 1;
    uVar2 = uVar2 + 1;
  } while (iVar4 < 8);
  return 0xffffffff;
}

