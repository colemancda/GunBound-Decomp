/* AvatarStorePanel_HitTest - 0x0050a640 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: CAvatarStorePanel's slot-4 HitTest
 * override. The original's vtable 0x557eb8 holds this at slot 4
 * (+0x10), the slot src/cxx/Widget.h declares as CWidget::HitTest(x, y)
 * ("Widget_HitTest - rect test then child broadcast"); the vtable is
 * installed only by BuildAvatarStorePanel (0x509ea5), and Widget.h
 * records it as CAvatarStorePanel's. The contract matches: `this` in
 * ECX (`mov ebx,ecx` at 0x50a648), `ret 8` for (x, y), and the tail at
 * 0x50a8ac-0x50a8e1 is the m_hidden-gated own-rect test over
 * +0x28/+0x30 and +0x2c/+0x34, returned as the bool result.
 *
 * Like ChannelUserListPanel_HitTest (0x507310), it does double duty:
 * ahead of the rect test, a point inside one of the 14 item rows
 * (x+0x13..x+0xc3, rows from y+0x68 stepping 0x11) that matches the
 * store's selected row acts on that catalog entry (row + the page base
 * at state+0x454, the cell AvatarStorePanel_OnCommand fills from the
 * scrollbar). An entry already equipped in one of the four slots goes
 * to UnequipAvatarSlot (0x50a760); otherwise, if its part code passes
 * the gender/flag test, to EquipAvatarPart (0x50a8a7). Those two
 * already-named callees are what EquipAvatarPart.c and
 * UnequipAvatarSlot.c describe as "the store item-action handler".
 *
 * WIRED (2026-10-30): src/cxx/Panel.cpp's CAvatarStorePanel::HitTest now forwards here
 * (vtable 0x557eb8 slot 4).
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 5 argless PeekPacketChecksumState() calls.  Same store-screen
 * shape as RenderAvatarListRow/RenderAvatarListDragRow: the selected-index cell
 * puVar1+0x228 (0x50a6cf), the equipped array g_clientContext + iVar3 +
 * 0x5f4ab8 (0x50a713, iVar3 being the 0x224-stride cursor the C already
 * carries), and three reads of the catalog record's part-code cell
 * *(ctx+0x44e20) + (*(puVar1+0x454) + iVar9)*0x450 + 0x22c (0x50a7b2,
 * 0x50a829 and its sibling) - the same `imul 0x450` + `+0x44e20` pair the
 * C's own ctx+0x44e24 bounds checks guard on the lines just above.
 */
#include "ghidra_types.h"


undefined4 __thiscall AvatarStorePanel_HitTest(int param_1,int param_2,int param_3)

{
  undefined *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int local_8;
  
  puVar1 = g_gameStateVTableArray[7];
  iVar3 = *(int *)(param_1 + 0x2c) + 0x68;
  if ((*(int *)(param_1 + 0x28) + 0x13 < param_2) && (param_2 < *(int *)(param_1 + 0x28) + 0xc3)) {
    iVar9 = 0;
    iVar8 = *(int *)(param_1 + 0x2c) + 0x79;
    do {
      if ((iVar3 < param_3) && (param_3 < iVar8)) {
        if ((iVar9 != -1) &&
           ((uint)(*(int *)(g_gameStateVTableArray[7] + 0x454) + iVar9) <
            *(uint *)(g_clientContext + 0x44e24))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar3 = PeekPacketChecksumState((void *)(puVar1 + 0x228));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          if (iVar9 == iVar3) {
            iVar3 = 0;
            local_8 = 0;
            goto LAB_0050a700;
          }
        }
        break;
      }
      iVar3 = iVar3 + 0x11;
      iVar8 = iVar8 + 0x11;
      iVar9 = iVar9 + 1;
    } while (iVar9 < 0xe);
  }
  goto LAB_0050a8b0;
  while( true ) {
    local_8 = local_8 + 1;
    iVar3 = iVar3 + 0x224;
    if (0x88f < iVar3) break;
LAB_0050a700:
    iVar8 = *(int *)(puVar1 + 0x454);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = PeekPacketChecksumState((void *)(g_clientContext + iVar3 + 0x5f4ab8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (iVar4 == iVar8 + iVar9) break;
  }
  if (local_8 != 4) {
    UnequipAvatarSlot(puVar1);
    goto LAB_0050a8b0;
  }
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(puVar1 + 0x454) + iVar9)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar5 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + (*(int *)(puVar1 + 0x454) + iVar9) * 0x450 + 0x22c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x3b498));
  if (cVar2 == '\0') {
    if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(puVar1 + 0x454) + iVar9)) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar6 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + (*(int *)(puVar1 + 0x454) + iVar9) * 0x450 + 0x22c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((uVar6 & 0x8000) != 0) goto LAB_0050a89a;
  }
  else {
    if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(puVar1 + 0x454) + iVar9)) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar6 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + (*(int *)(puVar1 + 0x454) + iVar9) * 0x450 + 0x22c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((uVar6 & 0x8000) == 0) {
LAB_0050a89a:
      if ((uVar5 & 0x30000) != 0x30000) goto LAB_0050a8b0;
    }
  }
  EquipAvatarPart(puVar1);
LAB_0050a8b0:
  uVar7 = 0;
  if ((((*(char *)(param_1 + 0x1e) == '\0') && (*(int *)(param_1 + 0x28) < param_2)) &&
      (param_2 < *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28))) &&
     ((*(int *)(param_1 + 0x2c) < param_3 &&
      (param_3 < *(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c))))) {
    uVar7 = 1;
  }
  return uVar7;
}

