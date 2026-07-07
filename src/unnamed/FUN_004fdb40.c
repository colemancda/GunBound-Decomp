/* FUN_004fdb40 - 0x004fdb40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool FUN_004fdb40(int param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_1c [10];
  char local_12 [17];
  byte local_1;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + param_1) == '\0') break;
    bVar1 = bVar1 + 1;
    local_12[uVar2] = *(char *)(uVar2 + param_1);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x10);
  local_1 = bVar1;
  local_12[bVar1] = '\0';
  iVar3 = FUN_004ff130(local_12,local_1c,&param_1);
  return iVar3 == 0;
}

