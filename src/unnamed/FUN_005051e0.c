/* FUN_005051e0 - 0x005051e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_005051e0(int param_1,int param_2)

{
  char *in_EAX;
  undefined4 uVar1;
  void *pvVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char *local_14;
  char local_10 [16];
  
  uVar4 = 0;
  do {
    uVar1 = FUN_00504d80();
    *(undefined4 *)(local_10 + uVar4 * 4) = uVar1;
    uVar4 = uVar4 + 1;
  } while (uVar4 < 4);
  FUN_004f48b0(3);
  iVar5 = (int)(param_1 + 0x10 + (param_1 + 0x10 >> 0x1f & 0xfU)) >> 4;
  pvVar2 = _realloc(*(void **)(param_2 + 0x27c),iVar5 << 4);
  iVar3 = 0;
  *(int *)(param_2 + 0x280) = param_1;
  *(void **)(param_2 + 0x27c) = pvVar2;
  local_14 = in_EAX;
  if (0 < iVar5) {
    do {
      if (iVar3 == iVar5 + -1) {
        _strncpy(local_10,local_14,0x10);
        EncodeCipherBlock(pvVar2,param_2);
      }
      else {
        EncodeCipherBlock(pvVar2,param_2);
      }
      iVar3 = iVar3 + 1;
      local_14 = local_14 + 0x10;
      pvVar2 = (void *)((int)pvVar2 + 0x10);
    } while (iVar3 < iVar5);
  }
  return;
}

