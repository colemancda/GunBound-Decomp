/* FUN_0040c980 - 0x0040c980 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * __fastcall
FUN_0040c980(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 in_EAX;
  int iVar1;
  undefined4 *puVar2;
  
  param_2[2] = param_1;
  param_2[6] = 0xffffffff;
  param_2[9] = 0xffffffff;
  param_2[0xe] = param_3;
  param_2[0xf] = param_4;
  param_2[0x10] = param_5;
  param_2[0x11] = param_6;
  param_2[0x113] = param_7;
  param_2[1] = in_EAX;
  param_2[0x114] = param_8;
  param_2[3] = 0;
  param_2[4] = 0;
  *(undefined1 *)(param_2 + 5) = 0;
  *(undefined1 *)((int)param_2 + 0x15) = 0;
  param_2[7] = 0;
  *(undefined1 *)(param_2 + 8) = 0;
  param_2[10] = 0;
  param_2[0xb] = 0;
  param_2[0x112] = 0;
  param_2[0x115] = 0;
  *param_2 = &PTR_FUN_0055208c;
  puVar2 = param_2 + 0x12;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return param_2;
}

