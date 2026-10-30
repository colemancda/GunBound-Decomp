/* RefreshConnectionStatusLabel - 0x0050ce60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CI COMPILE-ERR FIX (2026-07-30): both `Widget_RemoveChild()` calls
 * dropped its now-real 2 args (see that file's own header for the full
 * derivation). Confirmed via objdump (orig 0x50cf3d-0x50cf45 and
 * 0x50cfa7-0x50cfaf, both call sites the same shape): `this`=param_1,
 * `child`=`*(void**)(param_1[3] + index*4)` where index is the same
 * `uVar3` this file's own Widget_FindChildIndex call just computed.
 * Those four calls take ECX = EBP = param_1 and (ESI id, EDI 1): (3,1)
 * then (0,1) on the je path at 0x50cf8e/0x50cfbd, (0,1) then (3,1) at
 * 0x50cf24/0x50cf56; recovered 2026-10-30.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 3 argless Peeks.  This is ANOTHER store-catalog reader:
 * puVar1 = g_gameStateVTableArray[7] is the State07 avatar-store panel,
 * the first two Peeks read its selected-row cell at +0x228 (-1 = no
 * selection), and the third reads the selected catalog record's
 * guarded part-code field - *(ctx+0x44e20) + (row + pageBase)*0x450 +
 * 0x22c, the exact expression Equip/UnequipAvatarSlot use - then tests
 * its high bits (& 0xe0000000).  The file name predates this
 * understanding and looks wrong for what it does; not renamed here.
 *
 * Widget_AddChild `this` RECOVERED (2026-10-30): 0x50e670 takes the
 * parent in EBX and the child on the stack. At 0x50cf7d/0x50cfe0
 * EBX = ebp = param_1 (`mov ebx,ebp` at 0x50cf7a and 0x50cfdd);
 * each call now passes it as regEbx.
 */
#include "ghidra_types.h"


void RefreshConnectionStatusLabel(int param_1)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  puVar1 = g_gameStateVTableArray[7];
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(puVar1 + 0x228));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 != -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)(puVar1 + 0x228));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(puVar1 + 0x454) + iVar2)) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + (*(int *)(puVar1 + 0x454) + iVar2) * 0x450 + 0x22c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((uVar3 & 0xe0000000) == 0) {
      uVar3 = Widget_FindChildIndex(param_1,3,1);
      if (uVar3 != 0xffffffff) {
        if (*(uint *)(param_1 + 0x10) <= uVar3) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        Widget_RemoveChild((int *)param_1,
                           *(void **)(*(int *)(param_1 + 0xc) + uVar3 * 4));
      }
      iVar2 = Widget_FindChildIndex(param_1,0,1);
      if (iVar2 == -1) {
        uVar4 = CreateLabelWidget(0,0x4b0,0xe,0x1fc,0x40,0x17);
        Widget_AddChild(uVar4,param_1);
      }
    }
    else {
      uVar3 = Widget_FindChildIndex(param_1,0,1);
      if (uVar3 != 0xffffffff) {
        if (*(uint *)(param_1 + 0x10) <= uVar3) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        Widget_RemoveChild((int *)param_1,
                           *(void **)(*(int *)(param_1 + 0xc) + uVar3 * 4));
      }
      iVar2 = Widget_FindChildIndex(param_1,3,1);
      if (iVar2 == -1) {
        uVar4 = CreateLabelWidget(3,0x4b3,0xe,0x1fc,0x40,0x17);
        Widget_AddChild(uVar4,param_1);
        return;
      }
    }
  }
  return;
}

