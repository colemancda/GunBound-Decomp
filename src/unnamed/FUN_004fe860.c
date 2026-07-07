/* FUN_004fe860 - 0x004fe860 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004fe860(undefined4 param_1,int *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int unaff_ESI;
  undefined1 local_1c [10];
  char local_12 [17];
  byte local_1;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + unaff_ESI) == '\0') break;
    bVar1 = bVar1 + 1;
    local_12[uVar2] = *(char *)(uVar2 + unaff_ESI);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x10);
  local_1 = bVar1;
  local_12[bVar1] = '\0';
  iVar3 = FUN_00500ef0(local_12,local_1c,&param_1);
  if (iVar3 != 0) {
    *param_2 = iVar3 + 0x14;
    return CONCAT31((int3)((uint)(iVar3 + 0x14) >> 8),1);
  }
  return 0;
}

