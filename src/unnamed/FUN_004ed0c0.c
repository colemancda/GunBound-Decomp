/* FUN_004ed0c0 - 0x004ed0c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall
FUN_004ed0c0(undefined4 param_1,int param_2,int param_3,int param_4,char param_5,int param_6,
            int param_7)

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
  undefined4 unaff_EBX;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  fVar3 = (float)param_6;
  fVar4 = (float)(param_7 / 2 + -1);
  iVar8 = (in_EAX + 0x5a) % 0x168;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar8 * 4);
  iVar8 = in_EAX % 0x168;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + iVar8 * 4);
  _DAT_00ea0e50 = fVar1 * (float)-(param_7 / 2);
  _DAT_00ea0e4c = fVar2 * (float)-(param_7 / 2);
  fVar5 = fVar1 * fVar4;
  DAT_00ea0e28 = (float)param_3 + _DAT_00ea0e4c + fVar1 * _DAT_00557fb4;
  DAT_00ea0e2c = (float)param_4 + fVar2 * _DAT_00557fb4 + _DAT_00ea0e50;
  _DAT_00ea0e4c = (float)param_3 + fVar1 * fVar3 + _DAT_00ea0e4c;
  fVar6 = (float)param_4 + -(fVar2 * fVar3);
  _DAT_00ea0e50 = fVar6 + _DAT_00ea0e50;
  _DAT_00ea0e94 = (float)param_3 + fVar2 * fVar4;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar1 * fVar3;
  DAT_00ea0e74 = fVar6 + fVar5;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar1 * _DAT_00557fb4;
  _DAT_00ea0e98 = (float)param_4 + fVar5 + fVar2 * _DAT_00557fb4;
  DAT_00ea0ea8 = *(float *)(param_2 + 0x80);
  if (param_5 == '\0') {
    _DAT_00ea0e84 = *(float *)(param_2 + 0x88) + *(float *)(param_2 + 0x80);
  }
  else {
    _DAT_00ea0e84 = DAT_00ea0ea8;
    DAT_00ea0ea8 = *(float *)(param_2 + 0x88) + *(float *)(param_2 + 0x80);
  }
  _DAT_00ea0e40 = *(undefined4 *)(param_2 + 0x84);
  iVar8 = g_spriteVertexCount * 0x6c;
  _DAT_00ea0e88 = *(float *)(param_2 + 0x88) / (fVar3 / (float)param_7) + *(float *)(param_2 + 0x84)
  ;
  puVar9 = &DAT_00ea0e28;
  puVar10 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  g_spriteVertexCount = g_spriteVertexCount + 2;
  _DAT_00ea0e38 = unaff_EBX;
  _DAT_00ea0e3c = DAT_00ea0ea8;
  _DAT_00ea0e5c = unaff_EBX;
  _DAT_00ea0e60 = _DAT_00ea0e84;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e80 = unaff_EBX;
  _DAT_00ea0ea4 = unaff_EBX;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar7 = 0x1b; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e70;
  puVar10 = (undefined4 *)(&DAT_006ba1fc + iVar8);
  for (iVar7 = 0x12; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  puVar9 = &DAT_00ea0e28;
  puVar10 = (undefined4 *)(&DAT_006ba244 + iVar8);
  for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar10 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar10 = puVar10 + 1;
  }
  return;
}

