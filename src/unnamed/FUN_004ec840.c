/* FUN_004ec840 - 0x004ec840 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004ec840(int param_1,int param_2,int param_3,int param_4,byte param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int in_EAX;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  
  fVar3 = (float)-(in_EAX / 2);
  fVar4 = (float)(in_EAX / 2 + -1);
  iVar7 = (param_2 + 0x5a) % 0x168;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar7 * 4);
  param_2 = param_2 % 0x168;
  if (param_2 < 0) {
    param_2 = param_2 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + param_2 * 4);
  _DAT_00ea0e38 = (uint)param_5 << 0x18 | 0xffffff;
  _DAT_00ea0e94 = (float)param_3;
  DAT_00ea0e28 = _DAT_00ea0e94 + fVar2 * fVar3 + fVar1 * fVar3;
  fVar6 = (float)param_4;
  DAT_00ea0e2c = fVar6 + -(fVar2 * fVar3) + fVar1 * fVar3;
  _DAT_00ea0e4c = _DAT_00ea0e94 + fVar1 * fVar4 + fVar2 * fVar3;
  fVar5 = fVar6 + -(fVar2 * fVar4);
  _DAT_00ea0e50 = fVar5 + fVar1 * fVar3;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar2 * fVar4;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar1 * fVar4;
  DAT_00ea0e74 = fVar5 + fVar1 * fVar4;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar1 * fVar3;
  _DAT_00ea0e98 = fVar6 + fVar1 * fVar4 + -(fVar2 * fVar3);
  _DAT_00ea0e3c = *(undefined4 *)(param_1 + 0x80);
  _DAT_00ea0e40 = *(undefined4 *)(param_1 + 0x84);
  _DAT_00ea0e60 = *(float *)(param_1 + 0x80) + *(float *)(param_1 + 0x88);
  _DAT_00ea0e88 = *(float *)(param_1 + 0x84) + *(float *)(param_1 + 0x88);
  puVar8 = &DAT_00ea0e28;
  puVar9 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e5c = _DAT_00ea0e38;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e80 = _DAT_00ea0e38;
  _DAT_00ea0e84 = _DAT_00ea0e60;
  _DAT_00ea0ea4 = _DAT_00ea0e38;
  DAT_00ea0ea8 = _DAT_00ea0e3c;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar7 = 0x1b; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar9 = puVar9 + 1;
  }
  puVar8 = &DAT_00ea0e70;
  puVar9 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar9 = puVar9 + 1;
  }
  puVar8 = &DAT_00ea0e28;
  puVar9 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar9 = puVar9 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

