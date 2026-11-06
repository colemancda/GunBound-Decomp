/* PanelManager_Construct - 0x00507dc0 in the original binary.
 *
 * NAMED (batch 35), CERTAIN (was FUN_00507dc0).  The constructor of the global
 * UI panel manager g_uiPanelManager (0xe53c40).  Its only caller is the
 * static-initializer stub at 0x540dc0, the textbook `static T g;` shape:
 * `mov edx,0xe53c40 / call 0x507dc0 / push 0x543250 / call 0x5253ad`
 * (the CRT atexit), where 0x543250 is `mov ecx,0xe53c40 / jmp 0x40d150`,
 * i.e. the destructor registration for the same object (0x40d150 is
 * PanelManager_BaseDestructorThunk).  The vtable it stamps at +0
 * (0x557cfc) has PanelManager_ScalarDtor (0x507e10) in slot 0, and that
 * function calls the same 0x40d150 and then conditionally frees `this` -
 * the scalar-deleting destructor of this very class.  Fields +4..+0x14
 * zeroed and +0x18 = 10 (the node-list head, tail, count, pool and
 * free-list that PanelManager_PruneBelowId and PanelManager_Register
 * maintain; +0x18 the pool grow count).  It also clears the 0x100-byte
 * chat-input scratch table at 0x7933c0 and sets g_chatInputMaxLength to
 * 0x3c; those are inline statics of the same translation unit.
 * Convention: ECX unused, EDX = this (the static-init stub loads EDX).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 * __fastcall PanelManager_Construct(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  param_2[1] = 0;
  param_2[2] = 0;
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[5] = 0;
  param_2[6] = 10;
  *param_2 = &PTR_FUN_00557cfc;
  puVar2 = &g_chatInputText;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  g_chatInputActive = 0;
  g_chatInputMaxLength = 0x3c;
  return param_2;
}

