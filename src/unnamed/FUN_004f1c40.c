/* FUN_004f1c40 - 0x004f1c40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * __fastcall FUN_004f1c40(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  param_1[0x43] = 0;
  param_1[0x42] = 0;
  param_1[0x41] = 0;
  param_1[0x40] = 0x3f800000;
  param_1[0x44] = 0x3f800000;
  param_1[0x47] = 0;
  param_1[0x46] = 0;
  param_1[0x45] = 0;
  param_1[0x48] = 0x3f800000;
  param_1[0x4b] = 0;
  param_1[0x4a] = 0;
  param_1[0x49] = 0;
  param_1[0x4c] = 0x3f800000;
  param_1[0x4f] = 0;
  param_1[0x4e] = 0;
  param_1[0x4d] = 0;
  puVar2 = param_1;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = param_1 + 0x20;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[0x43] = 0x3f4ccccd;
  param_1[0x42] = 0x3f4ccccd;
  param_1[0x41] = 0x3f4ccccd;
  param_1[0x47] = 0x3f400000;
  param_1[0x46] = 0x3f400000;
  param_1[0x45] = 0x3f400000;
  param_1[0x4f] = 0;
  param_1[0x4e] = 0;
  param_1[0x4d] = 0;
  param_1[0x52] = 0;
  param_1[0x53] = 0;
  param_1[0x54] = 0;
  param_1[0x4b] = 0x3f000000;
  param_1[0x4a] = 0x3f000000;
  param_1[0x49] = 0x3f000000;
  param_1[0x50] = 0x3f000000;
  param_1[0x51] = 0x3f800000;
  return param_1;
}

