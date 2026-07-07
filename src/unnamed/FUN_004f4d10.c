/* FUN_004f4d10 - 0x004f4d10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall FUN_004f4d10(undefined4 param_1,uint *param_2,uint *param_3,int param_4)

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
  
  if ((*(byte *)(param_4 + 0x208) & 1) == 0) {
    return param_4 + 8U & 0xffff0000;
  }
  uVar4 = *(uint *)(param_4 + 8U) ^ *param_2;
  local_1c = *(uint *)(param_4 + 0xc) ^ param_2[1];
  uVar5 = *(uint *)(param_4 + 0x10) ^ param_2[2];
  uVar3 = *(uint *)(param_4 + 0x14) ^ param_2[3];
  iVar1 = *(int *)(param_4 + 4);
  puVar2 = (uint *)(param_4 + 0x18);
  if (iVar1 != 10) {
    if (iVar1 != 0xc) {
      if (iVar1 != 0xe) goto LAB_004f5df1;
      uVar6 = *(uint *)(&DAT_0054d778 + (uVar3 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054d378 + (uVar5 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cf78 + (local_1c >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cb78 + (uVar4 & 0xff) * 4) ^ *puVar2;
      uVar7 = *(uint *)(&DAT_0054d378 + (uVar3 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cf78 + (uVar5 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054d778 + (uVar4 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054cb78 + (local_1c & 0xff) * 4) ^ *(uint *)(param_4 + 0x1c);
      uVar8 = *(uint *)(&DAT_0054cf78 + (uVar3 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054d778 + (local_1c >> 0x18) * 4) ^
              *(uint *)(&DAT_0054d378 + (uVar4 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cb78 + (uVar5 & 0xff) * 4) ^ *(uint *)(param_4 + 0x20);
      uVar3 = *(uint *)(&DAT_0054d778 + (uVar5 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054d378 + (local_1c >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cf78 + (uVar4 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cb78 + (uVar3 & 0xff) * 4) ^ *(uint *)(param_4 + 0x24);
      uVar4 = *(uint *)(&DAT_0054d778 + (uVar3 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054d378 + (uVar8 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cf78 + (uVar7 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cb78 + (uVar6 & 0xff) * 4) ^ *(uint *)(param_4 + 0x28);
      local_1c = *(uint *)(&DAT_0054d378 + (uVar3 >> 0x10 & 0xff) * 4) ^
                 *(uint *)(&DAT_0054cf78 + (uVar8 >> 8 & 0xff) * 4) ^
                 *(uint *)(&DAT_0054d778 + (uVar6 >> 0x18) * 4) ^
                 *(uint *)(&DAT_0054cb78 + (uVar7 & 0xff) * 4) ^ *(uint *)(param_4 + 0x2c);
      uVar5 = *(uint *)(&DAT_0054cf78 + (uVar3 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054d778 + (uVar7 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054d378 + (uVar6 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cb78 + (uVar8 & 0xff) * 4) ^ *(uint *)(param_4 + 0x30);
      uVar3 = *(uint *)(&DAT_0054d778 + (uVar8 >> 0x18) * 4) ^
              *(uint *)(&DAT_0054d378 + (uVar7 >> 0x10 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cf78 + (uVar6 >> 8 & 0xff) * 4) ^
              *(uint *)(&DAT_0054cb78 + (uVar3 & 0xff) * 4) ^ *(uint *)(param_4 + 0x34);
      puVar2 = (uint *)(param_4 + 0x38);
    }
    uVar6 = *(uint *)(&DAT_0054d778 + (uVar3 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054d378 + (uVar5 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cf78 + (local_1c >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cb78 + (uVar4 & 0xff) * 4) ^ *puVar2;
    uVar7 = *(uint *)(&DAT_0054d378 + (uVar3 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cf78 + (uVar5 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054d778 + (uVar4 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054cb78 + (local_1c & 0xff) * 4) ^ puVar2[1];
    uVar8 = *(uint *)(&DAT_0054cf78 + (uVar3 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054d778 + (local_1c >> 0x18) * 4) ^
            *(uint *)(&DAT_0054d378 + (uVar4 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cb78 + (uVar5 & 0xff) * 4) ^ puVar2[2];
    uVar3 = *(uint *)(&DAT_0054d778 + (uVar5 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054d378 + (local_1c >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cf78 + (uVar4 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cb78 + (uVar3 & 0xff) * 4) ^ puVar2[3];
    uVar4 = *(uint *)(&DAT_0054d778 + (uVar3 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054d378 + (uVar8 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cf78 + (uVar7 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cb78 + (uVar6 & 0xff) * 4) ^ puVar2[4];
    local_1c = *(uint *)(&DAT_0054d378 + (uVar3 >> 0x10 & 0xff) * 4) ^
               *(uint *)(&DAT_0054cf78 + (uVar8 >> 8 & 0xff) * 4) ^
               *(uint *)(&DAT_0054d778 + (uVar6 >> 0x18) * 4) ^
               *(uint *)(&DAT_0054cb78 + (uVar7 & 0xff) * 4) ^ puVar2[5];
    uVar5 = puVar2[6] ^
            *(uint *)(&DAT_0054cf78 + (uVar3 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054d778 + (uVar7 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054d378 + (uVar6 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cb78 + (uVar8 & 0xff) * 4);
    uVar3 = *(uint *)(&DAT_0054d778 + (uVar8 >> 0x18) * 4) ^
            *(uint *)(&DAT_0054d378 + (uVar7 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cf78 + (uVar6 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_0054cb78 + (uVar3 & 0xff) * 4) ^ puVar2[7];
    puVar2 = puVar2 + 8;
  }
  uVar6 = *(uint *)(&DAT_0054d778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (local_1c >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar4 & 0xff) * 4) ^ *puVar2;
  uVar7 = *(uint *)(&DAT_0054d378 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054cb78 + (local_1c & 0xff) * 4) ^ puVar2[1];
  uVar8 = *(uint *)(&DAT_0054cf78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (local_1c >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar5 & 0xff) * 4) ^ puVar2[2];
  uVar3 = *(uint *)(&DAT_0054d778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (local_1c >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar3 & 0xff) * 4) ^ puVar2[3];
  uVar5 = *(uint *)(&DAT_0054d778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar8 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar7 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar6 & 0xff) * 4) ^ puVar2[4];
  uVar9 = *(uint *)(&DAT_0054d378 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar8 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar6 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar7 & 0xff) * 4) ^ puVar2[5];
  uVar10 = *(uint *)(&DAT_0054cf78 + (uVar3 >> 8 & 0xff) * 4) ^
           *(uint *)(&DAT_0054d778 + (uVar7 >> 0x18) * 4) ^
           *(uint *)(&DAT_0054d378 + (uVar6 >> 0x10 & 0xff) * 4) ^
           *(uint *)(&DAT_0054cb78 + (uVar8 & 0xff) * 4) ^ puVar2[6];
  uVar6 = *(uint *)(&DAT_0054d778 + (uVar8 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar7 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar6 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar3 & 0xff) * 4) ^ puVar2[7];
  uVar3 = *(uint *)(&DAT_0054d778 + (uVar6 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar10 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar9 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar5 & 0xff) * 4) ^ puVar2[8];
  uVar4 = *(uint *)(&DAT_0054d378 + (uVar6 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar10 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar9 & 0xff) * 4) ^ puVar2[9];
  uVar7 = *(uint *)(&DAT_0054cf78 + (uVar6 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar9 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar10 & 0xff) * 4) ^ puVar2[10];
  uVar5 = *(uint *)(&DAT_0054d778 + (uVar10 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar9 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar6 & 0xff) * 4) ^ puVar2[0xb];
  uVar6 = *(uint *)(&DAT_0054d778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar7 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar3 & 0xff) * 4) ^ puVar2[0xc];
  uVar8 = *(uint *)(&DAT_0054d378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar7 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar4 & 0xff) * 4) ^ puVar2[0xd];
  uVar9 = *(uint *)(&DAT_0054cf78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar7 & 0xff) * 4) ^ puVar2[0xe];
  uVar5 = *(uint *)(&DAT_0054d778 + (uVar7 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar5 & 0xff) * 4) ^ puVar2[0xf];
  uVar3 = *(uint *)(&DAT_0054d778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar9 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar8 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar6 & 0xff) * 4) ^ puVar2[0x10];
  uVar4 = *(uint *)(&DAT_0054d378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar9 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar6 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar8 & 0xff) * 4) ^ puVar2[0x11];
  uVar7 = *(uint *)(&DAT_0054cf78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar8 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar6 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar9 & 0xff) * 4) ^ puVar2[0x12];
  uVar5 = *(uint *)(&DAT_0054d778 + (uVar9 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar8 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar6 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar5 & 0xff) * 4) ^ puVar2[0x13];
  uVar6 = *(uint *)(&DAT_0054d778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar7 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar3 & 0xff) * 4) ^ puVar2[0x14];
  uVar8 = *(uint *)(&DAT_0054d378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar7 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar4 & 0xff) * 4) ^ puVar2[0x15];
  uVar9 = *(uint *)(&DAT_0054cf78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar7 & 0xff) * 4) ^ puVar2[0x16];
  uVar5 = *(uint *)(&DAT_0054d778 + (uVar7 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar5 & 0xff) * 4) ^ puVar2[0x17];
  uVar3 = *(uint *)(&DAT_0054d778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar9 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar8 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar6 & 0xff) * 4) ^ puVar2[0x18];
  uVar4 = *(uint *)(&DAT_0054d378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar9 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar6 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar8 & 0xff) * 4) ^ puVar2[0x19];
  uVar7 = *(uint *)(&DAT_0054cf78 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar8 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar6 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar9 & 0xff) * 4) ^ puVar2[0x1a];
  uVar5 = *(uint *)(&DAT_0054d778 + (uVar9 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar8 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar6 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar5 & 0xff) * 4) ^ puVar2[0x1b];
  uVar8 = *(uint *)(&DAT_0054d778 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar7 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar3 & 0xff) * 4) ^ puVar2[0x1c];
  uVar9 = *(uint *)(&DAT_0054d378 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar7 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar4 & 0xff) * 4) ^ puVar2[0x1d];
  uVar10 = *(uint *)(&DAT_0054cf78 + (uVar5 >> 8 & 0xff) * 4) ^
           *(uint *)(&DAT_0054d778 + (uVar4 >> 0x18) * 4) ^
           *(uint *)(&DAT_0054d378 + (uVar3 >> 0x10 & 0xff) * 4) ^
           *(uint *)(&DAT_0054cb78 + (uVar7 & 0xff) * 4) ^ puVar2[0x1e];
  uVar4 = *(uint *)(&DAT_0054d778 + (uVar7 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar5 & 0xff) * 4) ^ puVar2[0x1f];
  uVar3 = *(uint *)(&DAT_0054d778 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar10 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar9 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar8 & 0xff) * 4) ^ puVar2[0x20];
  uVar6 = *(uint *)(&DAT_0054d378 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar10 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar8 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar9 & 0xff) * 4) ^ puVar2[0x21];
  uVar7 = *(uint *)(&DAT_0054cf78 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054d778 + (uVar9 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar8 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar10 & 0xff) * 4) ^ puVar2[0x22];
  uVar8 = *(uint *)(&DAT_0054d778 + (uVar10 >> 0x18) * 4) ^
          *(uint *)(&DAT_0054d378 + (uVar9 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cf78 + (uVar8 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054cb78 + (uVar4 & 0xff) * 4) ^ puVar2[0x23];
  uVar4 = *(uint *)(&DAT_0054f778 + (uVar8 >> 0x18) * 4) ^
          (uint)(&PTR_DAT_0054f378)[uVar7 >> 0x10 & 0xff] ^
          *(uint *)(&DAT_0054ef78 + (uVar6 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054eb78 + (uVar3 & 0xff) * 4) ^ puVar2[0x24];
  local_1c = (uint)(&PTR_DAT_0054f378)[uVar8 >> 0x10 & 0xff] ^
             *(uint *)(&DAT_0054ef78 + (uVar7 >> 8 & 0xff) * 4) ^
             *(uint *)(&DAT_0054f778 + (uVar3 >> 0x18) * 4) ^
             *(uint *)(&DAT_0054eb78 + (uVar6 & 0xff) * 4) ^ puVar2[0x25];
  uVar5 = *(uint *)(&DAT_0054ef78 + (uVar8 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054f778 + (uVar6 >> 0x18) * 4) ^
          (uint)(&PTR_DAT_0054f378)[uVar3 >> 0x10 & 0xff] ^
          *(uint *)(&DAT_0054eb78 + (uVar7 & 0xff) * 4) ^ puVar2[0x26];
  uVar3 = puVar2[0x27] ^
          *(uint *)(&DAT_0054f778 + (uVar7 >> 0x18) * 4) ^
          (uint)(&PTR_DAT_0054f378)[uVar6 >> 0x10 & 0xff] ^
          *(uint *)(&DAT_0054ef78 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_0054eb78 + (uVar8 & 0xff) * 4);
LAB_004f5df1:
  param_3[1] = local_1c;
  param_3[2] = uVar5;
  *param_3 = uVar4;
  param_3[3] = uVar3;
  return CONCAT22((short)((uint)puVar2 >> 0x10),1);
}

