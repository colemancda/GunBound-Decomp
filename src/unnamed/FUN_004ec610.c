/* FUN_004ec610 - 0x004ec610 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004ec610(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int in_EAX;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  iVar8 = (in_EAX + 0x5a) % 0x168;
  _DAT_00ea0e4c = _DAT_00558018 * (_DAT_00557fb0 / (float)param_4);
  fVar3 = (float)(param_4 / 2 + -1);
  fVar7 = (_DAT_00557fb0 / (float)param_4) * _DAT_00558014 - _DAT_00557fb0;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar8 * 4);
  iVar8 = in_EAX % 0x168;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + iVar8 * 4);
  fVar5 = fVar1 * (float)-(param_4 / 2);
  _DAT_00ea0e38 = (uint)param_5 << 0x18 | 0xffffff;
  _DAT_00ea0e50 = fVar1 * _DAT_00ea0e4c;
  _DAT_00ea0e98 = -(fVar2 * (float)-(param_4 / 2));
  _DAT_00ea0e4c = fVar2 * _DAT_00ea0e4c;
  fVar6 = fVar1 * fVar3;
  fVar1 = fVar1 * fVar7;
  _DAT_00ea0e94 = (float)param_2;
  DAT_00ea0e28 = _DAT_00ea0e94 + _DAT_00ea0e4c + fVar5;
  fVar4 = (float)param_3;
  DAT_00ea0e2c = fVar4 + _DAT_00ea0e98 + _DAT_00ea0e50;
  _DAT_00ea0e4c = _DAT_00ea0e94 + fVar6 + _DAT_00ea0e4c;
  fVar3 = fVar4 + -(fVar2 * fVar3);
  _DAT_00ea0e50 = fVar3 + _DAT_00ea0e50;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar2 * fVar7;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar6;
  DAT_00ea0e74 = fVar3 + fVar1;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar5;
  _DAT_00ea0e98 = fVar4 + fVar1 + _DAT_00ea0e98;
  _DAT_00ea0e3c = *(undefined4 *)(param_1 + 0x80);
  _DAT_00ea0e40 = *(undefined4 *)(param_1 + 0x84);
  _DAT_00ea0e60 = *(float *)(param_1 + 0x80) + *(float *)(param_1 + 0x88);
  _DAT_00ea0e88 = *(float *)(param_1 + 0x84) + *(float *)(param_1 + 0x88);
  puVar9 = &DAT_00ea0e28;
  puVar10 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e5c = _DAT_00ea0e38;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e80 = _DAT_00ea0e38;
  _DAT_00ea0e84 = _DAT_00ea0e60;
  _DAT_00ea0ea4 = _DAT_00ea0e38;
  DAT_00ea0ea8 = _DAT_00ea0e3c;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar8 = 0x1b; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e70;
  puVar10 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar8 = 0x12; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e28;
  puVar10 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar8 = 9; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

