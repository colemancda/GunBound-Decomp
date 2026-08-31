/* AvatarListRowHitTest - 0x0050cdb0 in the original binary.
 *
 * Which row of the Avatar Store's item list a point lands on - named
 * after the WorldListRowHitTest (0x50df40) / RoomCardHitTest (0x42ada0)
 * pattern.  The list identity comes from the callers, not the geometry:
 * its only two call sites are the store widget's mouse handlers
 * (FUN_0050a1b0 mouse-down, FUN_0050a320 mouse-up), which key every
 * branch off g_gameStateVTableArray[7] - the State07 Avatar Store object
 * - and use the returned row as pageBase (+0x454) + row, bounds-checked
 * against the avatar-catalog count at g_clientContext+0x44e24: the same
 * base-plus-row indexing EquipAvatarPart / UnequipAvatarSlot /
 * RefreshConnectionStatusLabel apply to the 0x450-stride catalog records
 * at g_clientContext+0x44e20.  The mouse-down caller then transmits the
 * selected row via QueueOutgoingPacketField; the mouse-up caller uses it
 * as the drop target of a catalog-record reorder.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): maps a point to a ROW INDEX in a
 * 14-row list: param_1 is the widget (x window at +0x28+0x14..+0xc3,
 * first row top at +0x2c+0x68, 0x11 pixels per row), param_2 the X, and
 * ESI - now regEsi - the Y; returns 0..13 or -1. Both call sites are
 * C++ ports carrying their own file-local K&R externs, both fixed:
 * FUN_0050a1b0 passes its own (x,y) mouse args, and FUN_0050a320 asks
 * which row sits at an in-bounds probe X of widget-left + 0x14 and the
 * incoming y (`mov edx,[ebp+0x28] / add edx,0x14` at 0x50a360, ebp =
 * this via `mov ebp,ecx` at 0x50a33d, ECX unwritten to the call).
 */
#include "ghidra_types.h"


int __fastcall AvatarListRowHitTest(int param_1,int param_2,int regEsi)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_ESI = regEsi;
  
  iVar2 = *(int *)(param_1 + 0x2c) + 0x68;
  if ((*(int *)(param_1 + 0x28) + 0x13 < param_2) && (param_2 < *(int *)(param_1 + 0x28) + 0xc3)) {
    iVar1 = 0;
    iVar3 = *(int *)(param_1 + 0x2c) + 0x79;
    do {
      if ((iVar2 < unaff_ESI) && (unaff_ESI < iVar3)) {
        return iVar1;
      }
      iVar2 = iVar2 + 0x11;
      iVar3 = iVar3 + 0x11;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0xe);
  }
  return -1;
}

