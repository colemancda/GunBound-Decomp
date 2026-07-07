/* FUN_004f5e10 - 0x004f5e10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004f5e10(undefined4 param_1,uint *param_2,uint *param_3,int param_4)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint local_1c;
  uint local_18;
  
  if ((*(byte *)(param_4 + 0x208) & 2) == 0) {
    return 0;
  }
  uVar4 = *(uint *)(param_4 + 0x108) ^ *param_2;
  local_1c = *(uint *)(param_4 + 0x10c) ^ param_2[1];
  local_18 = *(uint *)(param_4 + 0x110) ^ param_2[2];
  uVar3 = *(uint *)(param_4 + 0x114) ^ param_2[3];
  iVar1 = *(int *)(param_4 + 4);
  puVar2 = (uint *)(param_4 + 0x118);
  if (iVar1 != 10) {
    if (iVar1 != 0xc) {
      if (iVar1 != 0xe) goto LAB_004f6ee6;
      uVar5 = *(uint *)(&DAT_0054df78 + (uVar3 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e378 + (local_18 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e778 + (local_1c >> 0x18) * 4) ^
              *(uint *)(&DAT_0054db78 + (uVar4 & 0xff) * 4) ^ *puVar2;
      uVar6 = *(uint *)(&DAT_0054e378 + (uVar3 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e778 + (local_18 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054df78 + (uVar4 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054db78 + (local_1c & 0xff) * 4) ^ *(uint *)(param_4 + 0x11c);
      uVar7 = *(uint *)(&DAT_0054e778 + (uVar3 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054df78 + (local_1c >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e378 + (uVar4 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054db78 + (local_18 & 0xff) * 4) ^ *(uint *)(param_4 + 0x120);
      uVar3 = *(uint *)(&DAT_0054df78 + (local_18 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e378 + (local_1c >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e778 + (uVar4 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054db78 + (uVar3 & 0xff) * 4) ^ *(uint *)(param_4 + 0x124);
      uVar4 = *(uint *)(&DAT_0054df78 + (uVar3 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e378 + (uVar7 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e778 + (uVar6 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ *(uint *)(param_4 + 0x128);
      local_1c = *(uint *)(&DAT_0054e378 + (uVar3 >> 0x10 & 0xff) * 4) ^
                 *(uint *)(&DAT_0054e778 + (uVar7 >> 0x18) * 4) ^
                 *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
                 *(uint *)(&DAT_0054db78 + (uVar6 & 0xff) * 4) ^ *(uint *)(param_4 + 300);
      local_18 = *(uint *)(&DAT_0054e778 + (uVar3 >> 0x18) * 4) ^
                 *(uint *)(&DAT_0054df78 + (uVar6 >> 8 & 0xff) * 4) ^
                 *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
                 *(uint *)(&DAT_0054db78 + (uVar7 & 0xff) * 4) ^ *(uint *)(param_4 + 0x130);
      uVar3 = *(uint *)(&DAT_0054df78 + (uVar7 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e378 + (uVar6 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054db78 + (uVar3 & 0xff) * 4) ^ *(uint *)(param_4 + 0x134);
      puVar2 = (uint *)(param_4 + 0x138);
    }
    uVar5 = *(uint *)(&DAT_0054df78 + (uVar3 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e378 + (local_18 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e778 + (local_1c >> 0x18) * 4) ^
            *(uint *)(&DAT_0054db78 + (uVar4 & 0xff) * 4) ^ *puVar2;
    uVar6 = *(uint *)(&DAT_0054e378 + (uVar3 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e778 + (local_18 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054df78 + (uVar4 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054db78 + (local_1c & 0xff) * 4) ^ puVar2[1];
    uVar7 = *(uint *)(&DAT_0054e778 + (uVar3 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054df78 + (local_1c >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e378 + (uVar4 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054db78 + (local_18 & 0xff) * 4) ^ puVar2[2];
    uVar3 = *(uint *)(&DAT_0054df78 + (local_18 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e378 + (local_1c >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e778 + (uVar4 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054db78 + (uVar3 & 0xff) * 4) ^ puVar2[3];
    uVar4 = *(uint *)(&DAT_0054df78 + (uVar3 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e378 + (uVar7 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e778 + (uVar6 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ puVar2[4];
    local_1c = *(uint *)(&DAT_0054e378 + (uVar3 >> 0x10 & 0xff) * 4) ^
               *(uint *)(&DAT_0054e778 + (uVar7 >> 0x18) * 4) ^
               *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
               *(uint *)(&DAT_0054db78 + (uVar6 & 0xff) * 4) ^ puVar2[5];
    local_18 = *(uint *)(&DAT_0054e778 + (uVar3 >> 0x18) * 4) ^
               *(uint *)(&DAT_0054df78 + (uVar6 >> 8 & 0xff) * 4) ^
               *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
               *(uint *)(&DAT_0054db78 + (uVar7 & 0xff) * 4) ^ puVar2[6];
    uVar3 = *(uint *)(&DAT_0054df78 + (uVar7 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e378 + (uVar6 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054db78 + (uVar3 & 0xff) * 4) ^ puVar2[7];
    puVar2 = puVar2 + 8;
  }
  uVar5 = *(uint *)(&DAT_0054df78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (local_18 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (local_1c >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar4 & 0xff) * 4) ^ *puVar2;
  uVar6 = *(uint *)(&DAT_0054e378 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (local_18 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (local_1c & 0xff) * 4) ^ puVar2[1];
  uVar7 = *(uint *)(&DAT_0054e778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (local_1c >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (local_18 & 0xff) * 4) ^ puVar2[2];
  uVar3 = *(uint *)(&DAT_0054df78 + (local_18 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (local_1c >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar3 & 0xff) * 4) ^ puVar2[3];
  uVar4 = *(uint *)(&DAT_0054df78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar7 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar6 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ puVar2[4];
  uVar8 = *(uint *)(&DAT_0054e378 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar7 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar6 & 0xff) * 4) ^ puVar2[5];
  uVar9 = *(uint *)(&DAT_0054e778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar6 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar7 & 0xff) * 4) ^ puVar2[6];
  uVar5 = *(uint *)(&DAT_0054df78 + (uVar7 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar6 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar3 & 0xff) * 4) ^ puVar2[7];
  uVar3 = *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar9 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar8 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar4 & 0xff) * 4) ^ puVar2[8];
  uVar10 = *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
           *(uint *)(&DAT_0054e778 + (uVar9 >> 0x18) * 4) ^
           *(uint *)(&DAT_0054df78 + (uVar4 >> 8 & 0xff) * 4) ^
           *(uint *)(&DAT_0054db78 + (uVar8 & 0xff) * 4) ^ puVar2[9];
  uVar6 = *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar8 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar9 & 0xff) * 4) ^ puVar2[10];
  uVar5 = *(uint *)(&DAT_0054df78 + (uVar9 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar8 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ puVar2[0xb];
  uVar4 = *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar6 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar10 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar3 & 0xff) * 4) ^ puVar2[0xc];
  uVar7 = *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar6 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar10 & 0xff) * 4) ^ puVar2[0xd];
  uVar8 = *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar10 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar6 & 0xff) * 4) ^ puVar2[0xe];
  uVar5 = *(uint *)(&DAT_0054df78 + (uVar6 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar10 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ puVar2[0xf];
  uVar3 = *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar8 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar7 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar4 & 0xff) * 4) ^ puVar2[0x10];
  uVar6 = *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar8 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar7 & 0xff) * 4) ^ puVar2[0x11];
  uVar9 = *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar7 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar8 & 0xff) * 4) ^ puVar2[0x12];
  uVar5 = *(uint *)(&DAT_0054df78 + (uVar8 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar7 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ puVar2[0x13];
  uVar4 = *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar9 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar6 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar3 & 0xff) * 4) ^ puVar2[0x14];
  uVar7 = *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar9 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar6 & 0xff) * 4) ^ puVar2[0x15];
  uVar8 = *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar6 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar9 & 0xff) * 4) ^ puVar2[0x16];
  uVar5 = *(uint *)(&DAT_0054df78 + (uVar9 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar6 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ puVar2[0x17];
  uVar3 = *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar8 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar7 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar4 & 0xff) * 4) ^ puVar2[0x18];
  uVar6 = *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar8 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar7 & 0xff) * 4) ^ puVar2[0x19];
  uVar9 = *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar7 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar8 & 0xff) * 4) ^ puVar2[0x1a];
  uVar5 = *(uint *)(&DAT_0054df78 + (uVar8 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar7 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ puVar2[0x1b];
  uVar4 = *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar9 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar6 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar3 & 0xff) * 4) ^ puVar2[0x1c];
  uVar7 = *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar9 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar6 & 0xff) * 4) ^ puVar2[0x1d];
  uVar8 = *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar6 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar9 & 0xff) * 4) ^ puVar2[0x1e];
  uVar5 = *(uint *)(&DAT_0054df78 + (uVar9 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar6 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ puVar2[0x1f];
  uVar3 = *(uint *)(&DAT_0054df78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar8 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar7 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar4 & 0xff) * 4) ^ puVar2[0x20];
  uVar6 = *(uint *)(&DAT_0054e378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar8 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar7 & 0xff) * 4) ^ puVar2[0x21];
  uVar9 = *(uint *)(&DAT_0054e778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054df78 + (uVar7 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar8 & 0xff) * 4) ^ puVar2[0x22];
  uVar5 = *(uint *)(&DAT_0054df78 + (uVar8 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e378 + (uVar7 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054e778 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054db78 + (uVar5 & 0xff) * 4) ^ puVar2[0x23];
  uVar4 = *(uint *)(&DAT_0054ff78 + (uVar5 >> 8 & 0xff) * 4) ^
          (uint)(&PTR_LAB_00550378)[uVar9 >> 0x10 & 0xff] ^
          *(uint *)(&DAT_00550778 + (uVar6 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054fb78 + (uVar3 & 0xff) * 4) ^ puVar2[0x24];
  local_1c = (uint)(&PTR_LAB_00550378)[uVar5 >> 0x10 & 0xff] ^
             *(uint *)(&DAT_00550778 + (uVar9 >> 0x18) * 4) ^
             *(uint *)(&DAT_0054ff78 + (uVar3 >> 8 & 0xff) * 4) ^
             *(uint *)(&DAT_0054fb78 + (uVar6 & 0xff) * 4) ^ puVar2[0x25];
  local_18 = *(uint *)(&DAT_00550778 + (uVar5 >> 0x18) * 4) ^
             *(uint *)(&DAT_0054ff78 + (uVar6 >> 8 & 0xff) * 4) ^
             (uint)(&PTR_LAB_00550378)[uVar3 >> 0x10 & 0xff] ^
             *(uint *)(&DAT_0054fb78 + (uVar9 & 0xff) * 4) ^ puVar2[0x26];
  uVar3 = puVar2[0x27] ^
          *(uint *)(&DAT_0054ff78 + (uVar9 >> 8 & 0xff) * 4) ^
          (uint)(&PTR_LAB_00550378)[uVar6 >> 0x10 & 0xff] ^
          *(uint *)(&DAT_00550778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054fb78 + (uVar5 & 0xff) * 4);
LAB_004f6ee6:
  param_3[2] = local_18;
  param_3[1] = local_1c;
  *param_3 = uVar4;
  param_3[3] = uVar3;
  return 1;
}

