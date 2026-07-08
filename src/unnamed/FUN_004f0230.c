/* FUN_004f0230 - 0x004f0230 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool __fastcall FUN_004f0230(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_88 [18];
  undefined4 local_40 [8];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_10;
  
  puVar2 = local_88;
  for (iVar1 = 0x1f; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_88[3] = 0x100;
  local_88[2] = 0x100;
  local_88[0] = 0x7c;
  local_88[1] = 0x101007;
  local_20 = 0x4001000;
  local_1c = 0x10;
  local_10 = 1;
  iVar1 = 8;
  puVar2 = &DAT_006777e8;
  if (param_3 == '\0') {
    puVar2 = &DAT_00677544;
  }
  puVar3 = local_40;
  for (; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  (**(code **)(*g_pDirectDraw7 + 0x18))(g_pDirectDraw7,local_88,param_2,0);
  return -1 < iVar1;
}

