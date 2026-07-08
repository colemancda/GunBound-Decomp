/* FUN_00429730 - 0x00429730 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00429730(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar3 = FUN_0042ada0(DAT_0056d110,0);
  iVar1 = g_clientContext;
  *(undefined4 *)(param_1 + 8) = uVar3;
  iVar4 = 0;
  if (*(char *)(iVar1 + 0x44648) != '\0') {
    do {
      uVar2 = FUN_00402160(*(undefined4 *)(iVar1 + 0x3f804));
      *(undefined1 *)(iVar1 + 0x449b4 + iVar4) = uVar2;
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)(uint)*(byte *)(iVar1 + 0x44648));
  }
  if (g_stateChangeInProgress != 0) {
    if (*(char *)(param_1 + 0xc) != '\0') {
      FUN_0050ef10(&DAT_00e53c40);
    }
    if (*(char *)(param_1 + 0xe) != '\0') {
      FUN_0050ef10(&DAT_00e53c40);
    }
    if (*(char *)(param_1 + 0xd) != '\0') {
      FUN_0050ef10(&DAT_00e53c40);
    }
  }
  return;
}

