/* FUN_004edd10 - 0x004edd10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * __fastcall FUN_004edd10(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  uVar1 = DAT_00557318;
  param_2[1] = 0;
  *(undefined1 *)((int)param_2 + 0x4b) = 0;
  *(undefined1 *)((int)param_2 + 0x4a) = 0;
  *(undefined1 *)((int)param_2 + 0x49) = 0;
  *(undefined1 *)(param_2 + 0x12) = 0;
  param_2[0x13] = 0;
  *(undefined1 *)(param_2 + 0x15) = 0;
  param_2[2] = uVar1;
  param_2[3] = DAT_0055731c;
  param_2[4] = DAT_00557320;
  param_2[5] = DAT_00557324;
  param_2[0x14] = 10;
  *param_2 = &PTR_FUN_0055745c;
  puVar3 = param_2 + 0x96;
  for (iVar2 = 0x100; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  return param_2;
}

