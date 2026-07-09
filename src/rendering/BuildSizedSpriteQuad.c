/* BuildSizedSpriteQuad - 0x004ecc70 in the original binary.
 *
 * Rotated textured-quad emitter drawn to an explicit width x height (params w,h) with a horizontal-flip flag; rotates the corners via g_sineTable360 and appends two triangles to g_spriteVertexBuffer. See ARCHITECTURE.md rendering section. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void BuildSizedSpriteQuad(int param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6)

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
  int iVar9;
  int iVar10;
  int unaff_EBX;
  undefined4 *puVar11;
  undefined4 *puVar12;
  
  fVar3 = (float)(param_4 / 2 + -1);
  fVar4 = (float)(param_5 / 2 + -1);
  iVar10 = (in_EAX + 0x5a) % 0x168;
  if (iVar10 < 0) {
    iVar10 = iVar10 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar10 * 4);
  iVar10 = in_EAX % 0x168;
  if (iVar10 < 0) {
    iVar10 = iVar10 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + iVar10 * 4);
  fVar6 = fVar1 * (float)-(param_4 / 2);
  _DAT_00ea0e50 = fVar1 * (float)-(param_5 / 2);
  _DAT_00ea0e98 = -(fVar2 * (float)-(param_4 / 2));
  _DAT_00ea0e4c = fVar2 * (float)-(param_5 / 2);
  fVar7 = fVar1 * fVar3;
  fVar1 = fVar1 * fVar4;
  _DAT_00ea0e94 = (float)param_1;
  DAT_00ea0e28 = _DAT_00ea0e94 + _DAT_00ea0e4c + fVar6;
  fVar5 = (float)param_2;
  DAT_00ea0e2c = fVar5 + _DAT_00ea0e98 + _DAT_00ea0e50;
  _DAT_00ea0e4c = _DAT_00ea0e94 + fVar7 + _DAT_00ea0e4c;
  fVar3 = fVar5 + -(fVar2 * fVar3);
  _DAT_00ea0e50 = fVar3 + _DAT_00ea0e50;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar2 * fVar4;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar7;
  DAT_00ea0e74 = fVar3 + fVar1;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar6;
  _DAT_00ea0e98 = fVar5 + fVar1 + _DAT_00ea0e98;
  DAT_00ea0ea8 = *(float *)(unaff_EBX + 0x80);
  if (param_3 == '\0') {
    _DAT_00ea0e84 = *(float *)(unaff_EBX + 0x88) + *(float *)(unaff_EBX + 0x80);
  }
  else {
    _DAT_00ea0e84 = DAT_00ea0ea8;
    DAT_00ea0ea8 = *(float *)(unaff_EBX + 0x88) + *(float *)(unaff_EBX + 0x80);
  }
  _DAT_00ea0e40 = *(undefined4 *)(unaff_EBX + 0x84);
  iVar8 = g_spriteVertexCount * 0x6c;
  iVar10 = g_spriteVertexCount * 0x1b;
  g_spriteVertexCount = g_spriteVertexCount + 2;
  _DAT_00ea0e88 =
       *(float *)(unaff_EBX + 0x88) / ((float)param_4 / (float)param_5) +
       *(float *)(unaff_EBX + 0x84);
  _DAT_00ea0ea4 = param_6;
  _DAT_00ea0e80 = param_6;
  _DAT_00ea0e5c = param_6;
  _DAT_00ea0e38 = param_6;
  puVar11 = &DAT_00ea0e28;
  puVar12 = &g_spriteVertexBuffer + iVar10;
  _DAT_00ea0e3c = DAT_00ea0ea8;
  _DAT_00ea0e60 = _DAT_00ea0e84;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar9 = 0x1b; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  puVar11 = &DAT_00ea0e70;
  puVar12 = (undefined4 *)(&DAT_006ba1fc + iVar8);
  for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  puVar11 = &DAT_00ea0e28;
  puVar12 = (undefined4 *)(&DAT_006ba244 + iVar8);
  for (iVar10 = 9; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  return;
}

