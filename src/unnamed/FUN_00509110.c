/* FUN_00509110 - 0x00509110 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00509110(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  puVar2 = *(undefined4 **)(unaff_ESI + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0x94);
      local_4 = 0;
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        FUN_00505760(puVar2);
        *puVar2 = &PTR_LAB_00557be4;
        puVar2[0x24] = 0xffffffff;
      }
      local_4 = 0xffffffff;
      puVar2[9] = 20000;
      puVar2[0x13] = 0;
      puVar2[0x11] = 700;
      puVar2[0x12] = 0;
      puVar2[10] = 0x238;
      puVar2[0xb] = 0xb;
      puVar2[0xc] = 0xd3;
      puVar2[0xd] = 0x10b;
      uVar3 = FUN_00507ee0(0,0x2bf,0xb4,7,0x16,0x14);
      FUN_0050e670(uVar3);
      uVar3 = FUN_00507ee0(1,0x2bd,0x5e,7,0x27,0x14);
      FUN_0050e670(uVar3);
      uVar3 = FUN_00507ee0(2,0x2be,0x89,7,0x27,0x14);
      FUN_0050e670(uVar3);
      uVar3 = FUN_005080a0(unaff_ESI,0xb7,0x49,0x12,0x98,7);
      FUN_0050e670(uVar3);
      FUN_0050eea0(puVar2);
      *unaff_FS_OFFSET = local_c;
      return;
    }
    iVar1 = puVar2[2];
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(iVar1 + 0x20) != 0) || (*(int *)(iVar1 + 0x24) != 20000));
  *(undefined1 *)(iVar1 + 0x1d) = 1;
  *unaff_FS_OFFSET = local_c;
  return;
}

