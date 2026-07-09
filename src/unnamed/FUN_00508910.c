/* FUN_00508910 - 0x00508910 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00508910(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  puVar2 = *(undefined4 **)(unaff_EDI + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0x90);
      local_4 = 0;
      if (puVar2 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        FUN_00505760(puVar2);
        *puVar2 = &PTR_LAB_00557dc8;
        puVar5 = puVar2;
      }
      local_4 = 0xffffffff;
      puVar5[9] = 2;
      puVar5[0x13] = 0;
      puVar5[0x11] = 0x2714;
      puVar5[0x12] = 0;
      puVar5[10] = 0xf3;
      puVar5[0xb] = 0xca;
      puVar5[0xc] = 0x139;
      puVar5[0xd] = 0xa0;
      puVar3 = (undefined4 *)FUN_00507f60(0,99,0x38,0xbe,0xc,4);
      FUN_0050e670(puVar3);
      FUN_0050efa0(unaff_EDI);
      (**(code **)*puVar3)(1);
      uVar4 = CreateLabelWidget(0,0x5dd,0xd5,0x76,0x52,0x22);
      FUN_0050e670(uVar4);
      uVar4 = CreateLabelWidget(1,0x5dc,0x80,0x76,0x52,0x22);
      FUN_0050e670(uVar4);
      FUN_0050eea0(puVar5);
      *unaff_FS_OFFSET = puVar2;
      return;
    }
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(*piVar1 + 0x20) != 0) || (*(int *)(*piVar1 + 0x24) != 2));
  FUN_00509960();
  *unaff_FS_OFFSET = local_c;
  return;
}

