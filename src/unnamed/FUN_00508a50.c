/* FUN_00508a50 - 0x00508a50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00508a50(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  puVar2 = *(undefined4 **)(param_1 + 4);
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0x90);
      local_4 = 0;
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        FUN_00505760(puVar2);
        *puVar2 = &PTR_LAB_00557c0c;
        *(undefined1 *)(puVar2 + 0xe) = 1;
      }
      local_4 = 0xffffffff;
      puVar2[9] = 3;
      puVar2[0x13] = 0;
      puVar2[0x11] = 10000;
      puVar2[0x12] = 8;
      puVar2[10] = 0x139;
      puVar2[0xb] = 0xa0;
      puVar2[0xc] = 0xf3;
      puVar2[0xd] = 0xca;
      puVar3 = (undefined4 *)FUN_00507f60(0,0x6a,0x48,0xb6,0xc,0x14);
      FUN_0050e670(puVar3);
      FUN_0050efa0(param_1);
      (**(code **)*puVar3)(1);
      FUN_00506f60();
      uVar4 = FUN_00507ee0(0,0x4ba,0xd5,0x76,0x52,0x22);
      FUN_0050e670(uVar4);
      uVar4 = FUN_00507ee0(1,0x4bb,0x80,0x76,0x52,0x22);
      FUN_0050e670(uVar4);
      FUN_0050eea0(puVar2);
      break;
    }
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(*piVar1 + 0x20) != 0) || (*(int *)(*piVar1 + 0x24) != 3));
  *unaff_FS_OFFSET = local_c;
  return;
}

