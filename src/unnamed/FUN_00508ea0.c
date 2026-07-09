/* FUN_00508ea0 - 0x00508ea0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00508ea0(int param_1)

{
  uchar uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  uchar *puVar5;
  char *_Format;
  uchar *unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  char local_8c [128];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053cf6e;
  *unaff_FS_OFFSET = &local_c;
  puVar3 = *(undefined4 **)(param_1 + 4);
joined_r0x00508ec8:
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = operator_new(0xa8);
    local_4 = 0;
    if (puVar3 == (undefined4 *)0x0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      FUN_00505760(puVar3);
      *puVar3 = &PTR_LAB_00557e40;
    }
    local_4 = 0xffffffff;
    puVar3[9] = 0x2712;
    puVar3[0x13] = 0;
    puVar3[0x11] = 0x2c6;
    puVar3[0x12] = 2;
    puVar3[10] = 0x12d;
    puVar3[0xb] = 0xd9;
    puVar3[0xc] = 200;
    puVar3[0xd] = 0x8a;
    uVar4 = CreateLabelWidget(0,0x2ca,0x44,0x66,0x37,0x1a);
    Widget_AddChild(uVar4);
    uVar4 = CreateLabelWidget(1,0x2cb,0x82,0x66,0x37,0x1a);
    Widget_AddChild(uVar4);
    puVar5 = unaff_EDI;
    if (unaff_EDI != (uchar *)0x0) {
      do {
        uVar1 = *puVar5;
        puVar5 = puVar5 + 1;
      } while (uVar1 != '\0');
    }
    FUN_004056c0(puVar3 + 0x14,unaff_EDI);
    _Format = (char *)GetLocalizedString(&DAT_00796eec,0xfa5);
    _sprintf(local_8c,_Format);
    uVar4 = FUN_00507ff0(0x17,0x2b,0x9a,0x33,local_8c,0xffff);
    Widget_AddChild(uVar4);
    PanelManager_Register(puVar3);
  }
  else {
    iVar2 = puVar3[2];
    puVar3 = (undefined4 *)*puVar3;
    if ((((*(int *)(iVar2 + 0x20) != 0) || (*(int *)(iVar2 + 0x24) != 0x2712)) ||
        (*(int *)(iVar2 + 0x4c) != 0)) ||
       (iVar2 = __mbsicmp(*(uchar **)(iVar2 + 0x50),unaff_EDI), iVar2 != 0))
    goto joined_r0x00508ec8;
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

