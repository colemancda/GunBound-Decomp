/* State07_AvatarStore_OnTick - 0x00448370 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00448370).  Slot 9 (+0x24) of
 * State07's vtable 0x5555f8, read from the original's .rdata.  That slot
 * is the one GameTick calls on the current state once per tick
 * (`*(vtable + 0x24)` on g_gameStateVTableArray[g_currentGameState],
 * src/entry/GameTick.c), and every named sibling fills it with its
 * OnTick: State01_Title_OnTick, State02_ServerSelect_OnTick,
 * State06_Logo2_OnTick, State09_ReadyRoom_OnTick, State11_InBattle_OnTick.
 * Like State09_ReadyRoom_OnTick it hit-tests g_cursorAnchorX/Y each
 * tick (here through the still-unnamed FUN_0044c3d0) and keeps the hit
 * index and a same-index tick counter at +0x3478c/+0x34790.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)(param_1 + 0x325b0)), from tools/guard_cell_resolve.py.
 *
 * WIDGET TICK `this` RECOVERED (2026-10-30): the first thing the tick does
 * is `mov esi,ecx / mov eax,[esi+0x30bbc] / lea ecx,[esi+0x30bbc] /
 * call [eax+8]` (0x448372-0x448380): slot 2 of the avatar-preview widget
 * embedded at +0x30bbc, with that sub-object's ADDRESS in ECX. Slot 2 of
 * its vtable 0x555b38 is 0x44fcb0, which starts `push esi / mov esi,ecx`
 * and is ported as FUN_0044fcb0, a genuine __fastcall(int *) that the port's
 * PTR_FUN_00555b38 table points at directly. The raw `code *` call passed
 * nothing, so the tick advanced whatever ECX held. It now passes
 * param_1 + 0x30bbc through a __fastcall pointer (no dummy EDX: the callee
 * takes no stack arguments).
 */
#include "ghidra_types.h"

/* Slot 2 of the embedded avatar-preview widget (vtable PTR_FUN_00555b38,
 * slot 2 = FUN_0044fcb0): a real __fastcall(int *this) in the port. */
typedef void (__fastcall *AvatarWidgetTickFn)(int *thisPtr);


void __fastcall State07_AvatarStore_OnTick(int param_1)

{
  char cVar1;
  int iVar2;
  
  (*(AvatarWidgetTickFn *)(*(int *)(param_1 + 0x30bbc) + 8))((int *)(param_1 + 0x30bbc));
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x325b0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 == 0) {
    cVar1 = PeekPacketChecksumBool((byte *)(param_1 + 0x32c54));
    if (cVar1 != '\x01') {
      cVar1 = PeekPacketChecksumBool((byte *)(param_1 + 0x32e63));
      if ((cVar1 != '\x01') && (g_stateChangeInProgress == 0)) {
        iVar2 = FUN_0044c3d0(param_1,g_cursorAnchorX,g_cursorAnchorY);
        if (iVar2 != -1) {
          if (*(int *)(param_1 + 0x3478c) == iVar2) {
            *(int *)(param_1 + 0x34790) = *(int *)(param_1 + 0x34790) + 1;
            return;
          }
          *(int *)(param_1 + 0x3478c) = iVar2;
          *(undefined4 *)(param_1 + 0x34790) = 0;
          return;
        }
      }
    }
  }
  *(undefined4 *)(param_1 + 0x3478c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x34790) = 0;
  return;
}

