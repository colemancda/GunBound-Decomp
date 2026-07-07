/* FUN_00509e60 - 0x00509e60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00509e60(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  puVar1 = operator_new(0x9c);
  local_4 = 0;
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    FUN_00505760(puVar1);
    *puVar1 = &PTR_LAB_00557eb8;
    *(undefined1 *)(puVar1 + 0xe) = 1;
    *(undefined1 *)((int)puVar1 + 5) = 0;
    puVar1[0x25] = 0xffffffff;
    *(undefined1 *)(puVar1 + 0x24) = 0;
    *(undefined1 *)((int)puVar1 + 0x91) = 0;
    puVar1[0x26] = 0;
  }
  local_4 = 0xffffffff;
  puVar1[9] = 0x232b;
  puVar1[0x13] = 0;
  puVar1[0x11] = 0x2712;
  puVar1[0x12] = 0;
  puVar1[10] = 0x228;
  puVar1[0xb] = 5;
  puVar1[0xc] = 0xf0;
  puVar1[0xd] = 0x21d;
  uVar2 = FUN_005080a0(param_1,0xcf,0x8c,0x12,0xab,0xe);
  FUN_0050e670(uVar2);
  FUN_0050eea0(puVar1);
  uVar2 = FUN_00507ee0(0,0x4b0,0xe,0x1fc,0x40,0x17);
  FUN_0050e7d0(0);
  FUN_0050e670(uVar2);
  uVar2 = FUN_00507ee0(1,0x4b1,0x57,0x1fc,0x40,0x17);
  FUN_0050e7d0(0);
  FUN_0050e670(uVar2);
  uVar2 = FUN_00507ee0(2,0x4b2,0xa0,0x1fc,0x40,0x17);
  FUN_0050e7d0(0);
  FUN_0050e670(uVar2);
  *unaff_FS_OFFSET = local_c;
  return puVar1;
}

