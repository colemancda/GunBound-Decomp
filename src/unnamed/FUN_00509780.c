/* FUN_00509780 - 0x00509780 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00509780(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar4;
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
      puVar2 = operator_new(0x90);
      local_4 = 0;
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        FUN_00505760(puVar2);
        *puVar2 = &PTR_LAB_00557d78;
      }
      local_4 = 0xffffffff;
      uVar4 = 0xffff;
      puVar2[9] = 50000;
      puVar2[0x13] = 0;
      puVar2[0x11] = 10000;
      puVar2[0x12] = 0x12;
      puVar2[10] = 0x115;
      puVar2[0xb] = 0xac;
      puVar2[0xc] = 0xf8;
      puVar2[0xd] = 0xf9;
      uVar3 = GetLocalizedString(&DAT_00796eec,0x15e);
      uVar3 = FUN_00507ff0(0x14,0xf,0xd2,0xf,uVar3,uVar4);
      FUN_0050e670(uVar3);
      uVar4 = 0xffff;
      uVar3 = GetLocalizedString(&DAT_00796eec,0x15f);
      uVar3 = FUN_00507ff0(0x14,0x32,0xce,0x8a,uVar3,uVar4);
      FUN_0050e670(uVar3);
      uVar3 = CreateLabelWidget(0,0x640,0x48,0xd0,0x51,0x21);
      FUN_0050e670(uVar3);
      uVar3 = CreateLabelWidget(1,0x641,0x9d,0xd0,0x51,0x21);
      FUN_0050e670(uVar3);
      FUN_0050eea0(puVar2);
      break;
    }
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
  } while ((*(int *)(*piVar1 + 0x20) != 0) || (*(int *)(*piVar1 + 0x24) != 50000));
  *unaff_FS_OFFSET = local_c;
  return;
}

