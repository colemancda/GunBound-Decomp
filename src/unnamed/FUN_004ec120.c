/* FUN_004ec120 - 0x004ec120 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004ec120(int param_1,int param_2,int param_3,int param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int in_EAX;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  
  iVar11 = (in_EAX + 0x5a) % 0x168;
  if (iVar11 < 0) {
    iVar11 = iVar11 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar11 * 4);
  iVar11 = in_EAX % 0x168;
  if (iVar11 < 0) {
    iVar11 = iVar11 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + iVar11 * 4);
  DAT_00ea0ea8 = 0x3b23d70a;
  fVar4 = fVar1 * _DAT_00558010;
  fVar6 = _DAT_00558010 * fVar2;
  fVar5 = fVar1 * _DAT_00557fd4;
  fVar1 = fVar1 * _DAT_00557fc4;
  fVar7 = _DAT_00558020 * fVar2;
  fVar2 = fVar2 * _DAT_00557fc4;
  fVar9 = (float)param_4;
  fVar8 = (float)param_2;
  DAT_00ea0e28 = fVar9 * fVar6 * _DAT_0055801c + fVar8;
  fVar3 = (float)param_3;
  DAT_00ea0e2c = fVar9 * fVar4 * _DAT_0055801c + fVar3;
  _DAT_00ea0e94 = fVar9 * fVar2 * _DAT_0055801c + fVar8;
  _DAT_00ea0e98 = fVar9 * fVar1 * _DAT_0055801c + fVar3;
  _DAT_00ea0e38 = param_1 << 0x18 | 0xffffff;
  _DAT_00ea0e3c = 0x3b23d70a;
  _DAT_00ea0e84 = 0x3f7f5c29;
  _DAT_00ea0e60 = 0x3f7f5c29;
  puVar12 = &DAT_00ea0e28;
  puVar13 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e5c = _DAT_00ea0e38;
  _DAT_00ea0e80 = _DAT_00ea0e38;
  _DAT_00ea0ea4 = _DAT_00ea0e38;
  for (iVar11 = 0x1b; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  puVar12 = &DAT_00ea0e70;
  puVar13 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar11 = 0x12; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  puVar12 = &DAT_00ea0e28;
  puVar13 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar11 = 9; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  iVar11 = (g_spriteVertexCount + 2) * 0x6c;
  _DAT_00ea0e4c = (fVar5 + fVar6) * fVar9 * _DAT_0055801c + fVar8;
  DAT_00ea0e64 = 0x3f00a3d7;
  _DAT_00ea0e40 = 0x3f00a3d7;
  _DAT_00ea0eac = 0x3f7f5c29;
  _DAT_00ea0e88 = 0x3f7f5c29;
  _DAT_00ea0e50 = (fVar7 + fVar4) * fVar9 * _DAT_0055801c + fVar3;
  DAT_00ea0e70 = (fVar2 + fVar5) * fVar9 * _DAT_0055801c + fVar8;
  DAT_00ea0e74 = (fVar7 + fVar1) * fVar9 * _DAT_0055801c + fVar3;
  puVar12 = &DAT_00ea0e28;
  puVar13 = &g_spriteVertexBuffer + (g_spriteVertexCount + 2) * 0x1b;
  for (iVar10 = 0x1b; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  puVar12 = &DAT_00ea0e70;
  puVar13 = (undefined4 *)(&DAT_006ba1fc + iVar11);
  for (iVar10 = 0x12; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  puVar12 = &DAT_00ea0e28;
  puVar13 = (undefined4 *)(&DAT_006ba244 + iVar11);
  for (iVar10 = 9; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar13 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar13 = puVar13 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 4;
  return;
}

