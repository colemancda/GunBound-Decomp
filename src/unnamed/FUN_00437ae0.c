/* FUN_00437ae0 - 0x00437ae0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00437ae0(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 < 0x186a5) {
    while (uVar1 != 0x186a4) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (0x186a4 < uVar1) {
        return;
      }
    }
    puVar3 = *(undefined4 **)(iVar2 + 0x10);
    uVar1 = puVar3[2];
    if (uVar1 <= param_2) {
      while (uVar1 != param_2) {
        puVar3 = (undefined4 *)puVar3[4];
        uVar1 = puVar3[2];
        if (param_2 < uVar1) {
          return;
        }
      }
      *(undefined4 *)(puVar3[3] + 0x10) = puVar3[4];
      *(undefined4 *)(puVar3[4] + 0xc) = puVar3[3];
      (**(code **)*puVar3)(1);
    }
  }
  return;
}

