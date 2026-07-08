/* FUN_005094f0 - 0x005094f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_005094f0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053ca9b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar1 = operator_new(0x90);
  local_4 = 0;
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    FUN_00505760(puVar1);
    *puVar1 = &PTR_LAB_00557ee0;
    *(undefined1 *)(puVar1 + 0xe) = 1;
    *(undefined1 *)((int)puVar1 + 5) = 1;
    *(undefined1 *)((int)puVar1 + 0x1e) = 1;
  }
  local_4 = 0xffffffff;
  puVar1[0x13] = 0;
  puVar1[9] = 2000;
  puVar1[0x11] = 10000;
  puVar1[0x12] = 0xb;
  puVar1[10] = 0x15;
  puVar1[0xb] = 0x181;
  puVar1[0xc] = 0x1e0;
  puVar1[0xd] = 0xa0;
  uVar2 = FUN_005080a0(param_1,0x1c7,0x33,0x12,0x45,9);
  FUN_0050e670(uVar2);
  FUN_0050eea0(puVar1);
  return puVar1;
}

