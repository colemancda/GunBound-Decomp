/* FUN_00509410 - 0x00509410 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Widget_AddChild `this` RECOVERED (2026-10-30): 0x50e670 takes the
 * parent in EBX and the child on the stack. At 0x5094ae/0x5094ce
 * EBX = the new panel (`mov ebx,eax` at 0x509431, `xor ebx,ebx` at 0x509454), puVar1 here;
 * each call now passes it as regEbx.
 *
 * SEH ARTIFACT STRIPPED (2026-10-30): 0x509410-0x50941e links a C++ EH
 * frame (push -1 / push 0x53795b / mov eax,fs:[0] / push eax /
 * mov fs:[0],esp) and the exit unlinks it (0x5094dd-0x5094e2). An earlier
 * pass had removed the fs:[0] writes but left the frame's locals and the
 * try-state stores; those are removed too, as in 7d662190.
 */
#include "ghidra_types.h"


void FUN_00509410(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;

  puVar1 = operator_new(0x90);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    Panel_BaseConstructor(puVar1);
    *puVar1 = &PTR_LAB_00557d28;
  }
  puVar1[9] = 0x7531;
  puVar1[0x13] = 0;
  puVar1[0x11] = 800;
  puVar1[0x12] = 1;
  puVar1[10] = 0x11d;
  puVar1[0xb] = 0xdf;
  puVar1[0xc] = 0xe7;
  puVar1[0xd] = 0x72;
  uVar2 = CreateLabelWidget(0,0x323,0x9a,0x55,0x3d,0x17);
  Widget_AddChild(uVar2,(int)puVar1);
  uVar2 = CreateStaticTextWidget(0x16,0x27,0xbb,0x25,param_2,0xffff);
  Widget_AddChild(uVar2,(int)puVar1);
  /* 0x5094d3-0x5094d8: mov eax,[esp+0x18] (param_1), push ebx (the panel). */
  PanelManager_Register((void *)param_1,(int)puVar1);
  return;
}

