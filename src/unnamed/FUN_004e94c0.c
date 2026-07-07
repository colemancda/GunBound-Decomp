/* FUN_004e94c0 - 0x004e94c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * __fastcall FUN_004e94c0(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_2;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_2 + 0x20;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_2[0x48] = 0xffffffff;
  param_2[0x45] = 0xffffffff;
  param_2[0x42] = 0xffffffff;
  param_2[0x49] = 0;
  param_2[0x46] = 0;
  param_2[0x43] = 0;
  param_2[0x44] = 0;
  param_2[0x47] = 0;
  param_2[0x4a] = 0;
  return param_2;
}

