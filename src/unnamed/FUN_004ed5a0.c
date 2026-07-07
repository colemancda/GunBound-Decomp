/* FUN_004ed5a0 - 0x004ed5a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ed5a0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11,
                 undefined4 param_12,undefined4 param_13,undefined4 param_14)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  DAT_00ea0e28 = (float)param_1;
  _DAT_00ea0e60 = param_9;
  DAT_00ea0e2c = (float)param_2;
  _DAT_00ea0e3c = param_9;
  DAT_00ea0ea8 = param_11;
  _DAT_00ea0e84 = param_11;
  _DAT_00ea0e4c = (float)param_3;
  _DAT_00ea0eac = param_10;
  _DAT_00ea0e40 = param_10;
  _DAT_00ea0e50 = (float)param_4;
  _DAT_00ea0e88 = param_12;
  DAT_00ea0e64 = param_12;
  _DAT_00ea0e80 = param_14;
  DAT_00ea0e70 = (float)param_5;
  _DAT_00ea0e5c = param_14;
  DAT_00ea0e74 = (float)param_6;
  _DAT_00ea0e94 = (float)param_7;
  _DAT_00ea0e98 = (float)param_8;
  _DAT_00ea0ea4 = param_13;
  _DAT_00ea0e38 = param_13;
  puVar2 = &DAT_00ea0e28;
  puVar3 = &g_spriteVertexBuffer + g_spriteVertexCount * 0x1b;
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

