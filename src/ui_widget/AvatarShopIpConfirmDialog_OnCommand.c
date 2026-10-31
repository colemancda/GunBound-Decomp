/* AvatarShopIpConfirmDialog_OnCommand - 0x00506e10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED 2026-10-31 (was FUN_00506e10). Slot 7 (OnCommand, +0x1c) of
 * vtable 0x557d78, which only BuildAvatarShopIpConfirmDialog installs
 * (0x5097e5) - the avatar-shop IP confirmation (Language.txt 351: "...
 * To confirm this IP click on "YES" ..."). Label 0, drawn with
 * b_gamelist_yes.img, sends a bare 6-byte opcode 0x1078 (0x506e34) and
 * sets the +0x1d close flag; label 1 (b_gamelist_no.img) only closes.
 * Opcode 0x1078 is not in include/opcodes.h or the reference server's
 * Opcode.swift, so what the server does with it is not established
 * here. Named after the builder, like BuddyRequestDialog_OnCommand.
 */
#include "ghidra_types.h"


void __thiscall AvatarShopIpConfirmDialog_OnCommand(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = g_connectionContextA;
  if (param_2 == 0) {
    if (param_3 == 0) {
      *(undefined2 *)(g_connectionContextA + 0x4d4) = 0x1078;
      *(undefined4 *)(iVar1 + 0x44d0) = 6;
      SendOutgoingPacket(iVar1);
    }
    else if (param_3 != 1) goto LAB_00506e51;
    *(undefined1 *)(param_1 + 0x1d) = 1;
  }
LAB_00506e51:
  Widget_OnCommandDefault(param_1,param_2,param_3,param_4);
  return;
}

