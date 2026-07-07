/* FUN_004ec430 - 0x004ec430 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004ec430(int param_1,int param_2,int param_3,byte param_4,uint param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int in_EAX;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  iVar7 = (in_EAX + 0x5a) % 0x168;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 0x168;
  }
  iVar8 = in_EAX % 0x168;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar5 = *(float *)(&g_sineTable360 + iVar7 * 4) * _DAT_00558010;
  fVar2 = _DAT_00558010 * *(float *)(&g_sineTable360 + iVar8 * 4);
  fVar6 = *(float *)(&g_sineTable360 + iVar7 * 4) * _DAT_00557fc4;
  fVar3 = *(float *)(&g_sineTable360 + iVar8 * 4) * _DAT_00557fc4;
  _DAT_00ea0e94 = (float)param_2;
  DAT_00ea0e28 = _DAT_00ea0e94 + fVar2 + fVar5;
  fVar1 = (float)param_3;
  DAT_00ea0e2c = fVar1 + -fVar2 + fVar5;
  _DAT_00ea0e4c = _DAT_00ea0e94 + fVar6 + fVar2;
  fVar4 = -fVar3 + fVar1;
  _DAT_00ea0e50 = fVar5 + fVar4;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar3;
  DAT_00ea0e70 = fVar6 + _DAT_00ea0e94;
  DAT_00ea0e74 = fVar4 + fVar6;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar5;
  _DAT_00ea0e98 = fVar1 + fVar6 + -fVar2;
  _DAT_00ea0e3c = *(undefined4 *)(param_1 + 0x80);
  _DAT_00ea0e40 = *(undefined4 *)(param_1 + 0x84);
  _DAT_00ea0e60 = *(float *)(param_1 + 0x88) + *(float *)(param_1 + 0x80);
  _DAT_00ea0e88 = *(float *)(param_1 + 0x88) + *(float *)(param_1 + 0x84);
  _DAT_00ea0e38 = (uint)param_4 << 0x18 | param_5;
  puVar9 = &DAT_00ea0e28;
  puVar10 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e5c = _DAT_00ea0e38;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e80 = _DAT_00ea0e38;
  _DAT_00ea0e84 = _DAT_00ea0e60;
  _DAT_00ea0ea4 = _DAT_00ea0e38;
  DAT_00ea0ea8 = _DAT_00ea0e3c;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar7 = 0x1b; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e70;
  puVar10 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e28;
  puVar10 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

