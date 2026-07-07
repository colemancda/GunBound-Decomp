/* FUN_005099d0 - 0x005099d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


undefined4 * FUN_005099d0(undefined4 param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  puVar1 = operator_new(0x94);
  local_4 = 0;
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    FUN_00505760(puVar1);
    *puVar1 = &PTR_LAB_00557f08;
    puVar1[0x24] = 0xffffffff;
    *(undefined1 *)(puVar1 + 0xe) = 1;
    *(undefined1 *)((int)puVar1 + 5) = 0;
  }
  local_4 = 0xffffffff;
  puVar1[9] = 9000;
  puVar1[0x13] = 0;
  puVar1[0x11] = 0x2711;
  puVar1[0x12] = 0;
  puVar1[10] = 0xb;
  puVar1[0xb] = 0xd;
  puVar1[0xc] = 0x221;
  puVar1[0xd] = 0x212;
  iVar2 = FUN_00507ee0(0,0x44c,0x145,0x1eb,0x4a,0x1a);
  *(undefined1 *)(iVar2 + 0x3a) = 1;
  FUN_0050e670(iVar2);
  uVar3 = FUN_00507ee0(1,0x44d,0x1a3,0x1eb,0x4a,0x1a);
  FUN_0050e670(uVar3);
  uVar3 = FUN_005080a0(param_1,0x203,0x4a,0x12,0x179,0);
  FUN_0050e670(uVar3);
  FUN_0050eea0(puVar1);
  *unaff_FS_OFFSET = local_c;
  return puVar1;
}

