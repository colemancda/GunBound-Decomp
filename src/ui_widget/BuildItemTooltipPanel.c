/* BuildItemTooltipPanel - 0x00509030 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Widget_AddChild `this` RECOVERED (2026-10-30): 0x50e670 takes the
 * parent in EBX and the child on the stack. At 0x5090ce/0x5090ee
 * EBX = the new panel (`mov ebx,eax` at 0x509051, `xor ebx,ebx` at 0x509074), puVar1 here;
 * each call now passes it as regEbx.
 */
#include "ghidra_types.h"


void BuildItemTooltipPanel(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  puVar1 = operator_new(0x90);
  local_4 = 0;
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    Panel_BaseConstructor(puVar1);
    *puVar1 = &PTR_LAB_00557e18;
  }
  local_4 = 0xffffffff;
  puVar1[9] = 0x2713;
  puVar1[0x13] = 0;
  puVar1[0x11] = 0x2c6;
  puVar1[0x12] = 2;
  puVar1[10] = 0x12d;
  puVar1[0xb] = 0xd9;
  puVar1[0xc] = 200;
  puVar1[0xd] = 0x8a;
  uVar2 = CreateLabelWidget(0,0x2ca,0x82,0x66,0x37,0x1a);
  Widget_AddChild(uVar2,(int)puVar1);
  uVar2 = CreateStaticTextWidget(0x17,0x2b,0x9a,0x33,param_2,0xffff);
  Widget_AddChild(uVar2,(int)puVar1);
  PanelManager_Register(puVar1);
  *unaff_FS_OFFSET = local_c;
  return;
}

