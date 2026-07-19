/* FUN_004fd0f0 - 0x004fd0f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004fd0f0(undefined4 *param_1,undefined4 param_2)

{
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537bc6) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  *param_1 = &PTR_LAB_00557610;
  FUN_004fdc80();
  /* orig 0x4fd11c `lea edi, [ebp + 0x2c]` (EBP = param_1) -
   * InitCommP2PNotifyWindow's recovered EDI `self` argument. */
  InitCommP2PNotifyWindow(param_1 + 0xb);
  param_1[0xbd] = &PTR_LAB_00557594;
  param_1[1] = &PTR_LAB_005575b8;
  *param_1 = &PTR_LAB_005575c8;
  param_1[0xb] = &PTR_LAB_005575ac;
  param_1[0xbd] = &PTR_FUN_005575a8;
  param_1[0x69b] = 1;
  *(undefined1 *)(param_1 + 0x69c) = 0;
  *(undefined1 *)((int)param_1 + 0x1a71) = 0;
  param_1[0x69d] = 0;
  param_1[0x69e] = 0;
  param_1[0x6a9] = 0;
  param_1[0x6aa] = 0;
  param_1[0x6ab] = 0;
  param_1[0x6ac] = param_2;
  param_1[0x6ad] = 0;
  param_1[0x6ae] = 0;
  FUN_004fe420(0x3f400000,0x3e800000,0x40100000);
  FUN_004fe420(0x3f400000,0x3e800000,0x40100000);
  *(undefined1 *)(param_1 + 0x74a) = 0;
  FUN_00504c10();
  param_1[0x767] = 0;
  param_1[0x768] = 0;
  *(undefined1 *)(param_1 + 0x7eb) = 0;
  FUN_00504c10();
  param_1[0x808] = 0;
  param_1[0x809] = 0;
  return param_1;
}

