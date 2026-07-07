/* FUN_004ebdd0 - 0x004ebdd0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_004ebdd0(int param_1,int param_2,int param_3,byte param_4,uint param_5,char param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int in_EAX;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  iVar4 = (in_EAX + 0x5a) % 0x168;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0x168;
  }
  fVar1 = *(float *)(&g_sineTable360 + iVar4 * 4);
  iVar4 = in_EAX % 0x168;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 0x168;
  }
  fVar2 = *(float *)(&g_sineTable360 + iVar4 * 4);
  DAT_00ea0e28 = (float)param_2 + fVar2 * _DAT_00558000 + fVar1 * _DAT_00557ffc;
  DAT_00ea0e2c = (float)param_3 + fVar2 * _DAT_0055802c + fVar1 * _DAT_00558000;
  _DAT_00ea0e4c = (float)param_2 + fVar1 * _DAT_00557ff0 + fVar2 * _DAT_00558000;
  fVar3 = (float)param_3 + fVar2 * _DAT_00558028;
  _DAT_00ea0e50 = fVar3 + fVar1 * _DAT_00558000;
  _DAT_00ea0e94 = (float)param_2 + fVar2 * _DAT_00557ff4;
  DAT_00ea0e70 = _DAT_00ea0e94 + fVar1 * _DAT_00557ff0;
  DAT_00ea0e74 = fVar3 + fVar1 * _DAT_00557ff4;
  _DAT_00ea0e94 = _DAT_00ea0e94 + fVar1 * _DAT_00557ffc;
  _DAT_00ea0e98 = (float)param_3 + fVar1 * _DAT_00557ff4 + fVar2 * _DAT_0055802c;
  if (param_6 == '\0') {
    _DAT_00ea0eac = *(float *)(param_1 + 0x84) + *(float *)(param_1 + 0x88);
    DAT_00ea0e64 = *(float *)(param_1 + 0x84);
  }
  else {
    DAT_00ea0e64 = *(float *)(param_1 + 0x84) + *(float *)(param_1 + 0x88);
    _DAT_00ea0eac = *(float *)(param_1 + 0x84);
  }
  _DAT_00ea0e3c = *(undefined4 *)(param_1 + 0x80);
  _DAT_00ea0e60 = *(float *)(param_1 + 0x88) + *(float *)(param_1 + 0x80);
  _DAT_00ea0e38 = (uint)param_4 << 0x18 | param_5;
  puVar5 = &DAT_00ea0e28;
  puVar6 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e40 = DAT_00ea0e64;
  _DAT_00ea0e5c = _DAT_00ea0e38;
  _DAT_00ea0e80 = _DAT_00ea0e38;
  _DAT_00ea0e84 = _DAT_00ea0e60;
  _DAT_00ea0e88 = _DAT_00ea0eac;
  _DAT_00ea0ea4 = _DAT_00ea0e38;
  DAT_00ea0ea8 = _DAT_00ea0e3c;
  for (iVar4 = 0x1b; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar5 = &DAT_00ea0e70;
  puVar6 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar4 = 0x12; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar5 = &DAT_00ea0e28;
  puVar6 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

