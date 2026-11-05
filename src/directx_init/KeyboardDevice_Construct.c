/* KeyboardDevice_Construct - 0x004edd10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the CRT static-init stub at 0x540de0 loads
 * EDX = 0xe52810 (the keyboard singleton, the same address GameTick and
 * InitGame use as the keyboard device) and calls this function, then
 * registers an atexit handler. The 16 bytes it copies into obj+8 from
 * 0x557318 are 6F1D2B61-D5A0-11CF-BFC7-444553540000, which is
 * GUID_SysKeyboard (the mouse twin copies 6F1D2B60 from 0x557328,
 * GUID_SysMouse). It stamps vtable 0x55745c, whose slot 1 (0x4edd70) is
 * the CreateDevice/SetDataFormat(c_dfDIKeyboard) initializer.
 *
 * Not the IDirectInput8::EnumDevices callback: that is
 * EnumInputDevicesCallback (0x4edc10).
 */
#include "ghidra_types.h"


undefined4 * __fastcall KeyboardDevice_Construct(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  uVar1 = DAT_00557318;
  param_2[1] = 0;
  *(undefined1 *)((int)param_2 + 0x4b) = 0;
  *(undefined1 *)((int)param_2 + 0x4a) = 0;
  *(undefined1 *)((int)param_2 + 0x49) = 0;
  *(undefined1 *)(param_2 + 0x12) = 0;
  param_2[0x13] = 0;
  *(undefined1 *)(param_2 + 0x15) = 0;
  param_2[2] = uVar1;
  param_2[3] = DAT_0055731c;
  param_2[4] = DAT_00557320;
  param_2[5] = DAT_00557324;
  param_2[0x14] = 10;
  *param_2 = &PTR_FUN_0055745c;
  puVar3 = param_2 + 0x96;
  for (iVar2 = 0x100; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  return param_2;
}

