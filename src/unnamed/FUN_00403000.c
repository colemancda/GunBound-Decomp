/* FUN_00403000 - 0x00403000 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00403000(ushort *param_1,undefined4 param_2)

{
  int iVar1;
  short in_AX;
  uint uVar2;
  ushort *puVar3;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 uStack_30;
  undefined1 local_2f;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14;
  undefined1 local_13;
  
  if (in_AX == 0x1021) {
    if (*param_1 == 0) {
      local_40 = *(undefined4 *)(param_1 + 7);
      SUBFIELD(local_1c,1,undefined3) = (undefined3)*(undefined4 *)(param_1 + 3);
      local_1c = CONCAT31(SUBFIELD(local_1c,1,undefined3),(char)((uint)*(undefined4 *)(param_1 + 1) >> 0x18));
      uStack_3c = *(undefined4 *)(param_1 + 9);
      SUBFIELD(local_18,1,undefined3) = (undefined3)*(undefined4 *)(param_1 + 5);
      local_18 = CONCAT31(SUBFIELD(local_18,1,undefined3),(char)((uint)*(undefined4 *)(param_1 + 3) >> 0x18));
      local_14 = (undefined1)((uint)*(undefined4 *)(param_1 + 5) >> 0x18);
      uStack_38 = *(undefined4 *)(param_1 + 0xb);
      uStack_34 = *(undefined4 *)(param_1 + 0xd);
      local_20 = CONCAT31((int3)*(undefined4 *)(param_1 + 1),0x6e);
      local_13 = 0;
      uStack_30 = 0;
      FUN_00403170(param_2,&local_20,&local_40);
      iVar1 = g_clientContext;
      FUN_00426620(&DAT_006aa41c + g_clientContext,&local_40);
      FUN_00426620(&DAT_006aa44c + iVar1,(int)&local_20 + 1);
      return;
    }
  }
  else if (in_AX == 0x1023) {
    puVar3 = param_1 + 1;
    for (uVar2 = (uint)*param_1; uVar2 != 0; uVar2 = uVar2 - 1) {
      SUBFIELD(uStack_3c,1,undefined3) = (undefined3)*(undefined4 *)(puVar3 + 2);
      uStack_3c = CONCAT31(SUBFIELD(uStack_3c,1,undefined3),(char)((uint)*(undefined4 *)puVar3 >> 0x18));
      SUBFIELD(uStack_38,1,undefined3) = (undefined3)*(undefined4 *)(puVar3 + 4);
      uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),(char)((uint)*(undefined4 *)(puVar3 + 2) >> 0x18));
      local_20 = *(undefined4 *)(puVar3 + 8);
      SUBFIELD(uStack_34,1,undefined3) = (undefined3)*(undefined4 *)(puVar3 + 6);
      uStack_34 = CONCAT31(SUBFIELD(uStack_34,1,undefined3),(char)((uint)*(undefined4 *)(puVar3 + 4) >> 0x18));
      uStack_30 = (undefined1)((uint)*(undefined4 *)(puVar3 + 6) >> 0x18);
      local_1c = *(undefined4 *)(puVar3 + 10);
      local_18 = *(undefined4 *)(puVar3 + 0xc);
      local_40 = CONCAT31((int3)*(undefined4 *)puVar3,0x69);
      local_2f = 0;
      local_14 = 0;
      puVar3 = puVar3 + 0xe;
      FUN_00403170(param_2,&local_40,&local_20);
      iVar1 = g_clientContext;
      FUN_00426620(&DAT_006aa41c + g_clientContext,(int)&local_40 + 1);
      FUN_00426620(&DAT_006aa44c + iVar1,&local_20);
    }
  }
  return;
}

