/* FUN_004ebff0 - 0x004ebff0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ebff0(int param_1,int param_2)

{
  int in_EAX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  DAT_00ea0e28 = (float)param_1 - _DAT_00557fd0;
  DAT_00ea0e2c = (float)param_2 - _DAT_00557fcc;
  _DAT_00ea0e4c = (float)param_1 + _DAT_00557fc8;
  DAT_00ea0e70 = (float)param_1 + _DAT_00557fc8;
  DAT_00ea0e74 = (float)param_2 + _DAT_00557fc4;
  _DAT_00ea0e98 = (float)param_2 + _DAT_00557fc4;
  _DAT_00ea0e3c = *(undefined4 *)(in_EAX + 0x80);
  _DAT_00ea0e40 = *(undefined4 *)(in_EAX + 0x84);
  _DAT_00ea0e60 = *(float *)(in_EAX + 0x80) + *(float *)(in_EAX + 0x88);
  _DAT_00ea0e88 = *(float *)(in_EAX + 0x84) + *(float *)(in_EAX + 0x88);
  _DAT_00ea0ea4 = 0xffffffff;
  _DAT_00ea0e80 = 0xffffffff;
  _DAT_00ea0e5c = 0xffffffff;
  _DAT_00ea0e38 = 0xffffffff;
  puVar2 = &DAT_00ea0e28;
  puVar3 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
  _DAT_00ea0e50 = DAT_00ea0e2c;
  DAT_00ea0e64 = _DAT_00ea0e40;
  _DAT_00ea0e84 = _DAT_00ea0e60;
  _DAT_00ea0e94 = DAT_00ea0e28;
  DAT_00ea0ea8 = _DAT_00ea0e3c;
  _DAT_00ea0eac = _DAT_00ea0e88;
  for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_00ea0e70;
  puVar3 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
  for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_00ea0e28;
  puVar3 = (undefined4 *)(&DAT_006ba244 + g_spriteVertexCount * 0x6c);
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  g_spriteVertexCount = g_spriteVertexCount + 2;
  return;
}

