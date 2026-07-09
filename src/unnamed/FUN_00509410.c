/* FUN_00509410 - 0x00509410 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00509410(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053795b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar1 = operator_new(0x90);
  local_4 = 0;
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    FUN_00505760(puVar1);
    *puVar1 = &PTR_LAB_00557d28;
  }
  local_4 = 0xffffffff;
  puVar1[9] = 0x7531;
  puVar1[0x13] = 0;
  puVar1[0x11] = 800;
  puVar1[0x12] = 1;
  puVar1[10] = 0x11d;
  puVar1[0xb] = 0xdf;
  puVar1[0xc] = 0xe7;
  puVar1[0xd] = 0x72;
  uVar2 = CreateLabelWidget(0,0x323,0x9a,0x55,0x3d,0x17);
  Widget_AddChild(uVar2);
  uVar2 = FUN_00507ff0(0x16,0x27,0xbb,0x25,param_2,0xffff);
  Widget_AddChild(uVar2);
  PanelManager_Register(puVar1);
  return;
}

