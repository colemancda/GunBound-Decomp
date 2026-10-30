/* FUN_004475c0 - 0x004475c0 in the original binary.
 *
 * CState07AvatarStore's vtable slot 6 (+0x18): the store's keydown/mouse
 * message dispatch, reached from WndProc's slot-6 forward. It handles
 * WM_SYSCOMMAND (the 0xf060 close command), WM_LBUTTONDOWN and
 * WM_LBUTTONDBLCLK (the `[esp+4]-0x112` / `-0xef` / `-2` ladder in the
 * original).
 *
 * CONVENTION (2026-08-09): this MUST NOT be the plain-cdecl
 * bring-up auto-stub. WndProc dispatches slot 6 as
 * `StateSlot6DispatchFn` = __fastcall(this, dummyEDX, msg, wParam,
 * lParam) - `this` in ECX, a dummy EDX, and THREE stack args the callee
 * is expected to pop (the original ends every path in `ret 0xc`). The
 * auto-stub was `int FUN_004475c0(){return 0;}` (cdecl, `ret`, cleans
 * 0), so each time state 7 received a mouse/key/nc message WndProc's own
 * frame leaked 12 bytes; after enough messages WndProc returned through
 * a stack slot holding a stale stack address and executed it as code
 * (live crash: EIP on the stack at 0x76efcc, reached via WndProc's
 * `ret 0x10` running 0xc too deep - confirmed by a slot-6-dispatch
 * trace). Same calling-convention class as the State03/State11 slot-6
 * fix in commit 2f60aa7; State07's slot was a stub then, so it was
 * missed. Declared here with the matching __fastcall + dummy-EDX
 * signature so the stack stays balanced.
 *
 * BODY PORTED (2026-10-30) from 0x4475c0-0x44775b. ECX = this (ESI from
 * 0x4475ca), msg at [esp+4]:
 *
 *   0x112 WM_SYSCOMMAND (0x447739): if wParam == 0xf060 (SC_CLOSE) and the
 *         byte this+0x30bb8 is clear, set it and call FUN_0044bf00(this)
 *         (push esi / call 0x44bf00, which ends in ret 4).
 *   0x201 WM_LBUTTONDOWN (0x44769a) and 0x203 WM_LBUTTONDBLCLK (0x4475e7)
 *         share a gate: return if the guarded dword this+0x325b0 is nonzero
 *         (PeekPacketChecksumState under the guard lock, `setne bl`), or if
 *         either guarded bool this+0x32c54 / this+0x32e63 reads 1
 *         (PeekPacketChecksumBool 0x4065a0, cell in EAX), or if
 *         g_stateChangeInProgress ([0x793508]) is set. Then the item cell
 *         under the cursor: FUN_0044c3d0(this, LOWORD(lParam),
 *         HIWORD(lParam)) (push ecx = lParam>>16 / push edx = lParam&0xffff
 *         / push esi), -1 for none.
 *   0x201: on a hit, QueueOutgoingPacketField(this+0x228, -1) (0x447707,
 *         cell in EAX), QueueOutgoingPacketField(this+4, cell) (0x447714),
 *         and RadioGroup_RefreshEnableStates([this+0x34784]) at 0x447724
 *         with BL = 0 (the `setne bl` above was 0 or the jne at 0x4476c2
 *         would have left). Hit or not, FUN_00449250(this, 1, 0) at
 *         0x44772e (push 0 / push 1 / push esi).
 *   0x203: on a hit, if IsWidgetEnabled(registry 0xe9be90, layer EDX = 0,
 *         id ESI = 0xf) returns 1 (0x447665-0x447678), the incoming frame
 *         is overwritten with (0, 0, 0xf) and `mov eax,0x795070 /
 *         jmp 0x4f2da0` tail-calls EnqueueInputEvent; its ret 0xc pops this
 *         function's three stack words. Same shape as
 *         State03_GameRoomList_HandleMouseInput's 0x428c3c.
 *
 * Every other message falls through to `ret 0xc`.
 */
#include "ghidra_types.h"

void __fastcall FUN_004475c0(void *thisPtr, int dummyEDX, uint msg, uint wParam,
                             uint lParam)
{
  int self;
  int iVar1;
  char cVar2;

  (void)dummyEDX;
  self = (int)thisPtr;
  if (msg == 0x112) {
    if ((wParam == 0xf060) && (*(char *)(self + 0x30bb8) == '\0')) {
      *(undefined1 *)(self + 0x30bb8) = 1;
      FUN_0044bf00(self);
    }
    return;
  }
  if ((msg != 0x201) && (msg != 0x203)) {
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(self + 0x325b0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 != 0) {
    return;
  }
  cVar2 = PeekPacketChecksumBool((byte *)(self + 0x32c54));
  if (cVar2 == '\x01') {
    return;
  }
  cVar2 = PeekPacketChecksumBool((byte *)(self + 0x32e63));
  if (cVar2 == '\x01') {
    return;
  }
  if (g_stateChangeInProgress != 0) {
    return;
  }
  iVar1 = FUN_0044c3d0(self,lParam & 0xffff,lParam >> 0x10);
  if (msg == 0x203) {
    if (iVar1 == -1) {
      return;
    }
    cVar2 = IsWidgetEnabled(0,0,(int)&g_activeObjectRegistry,0xf);
    if (cVar2 == '\x01') {
      EnqueueInputEvent((uint *)g_inputEventRing,0,0,0xf);
    }
    return;
  }
  if (iVar1 != -1) {
    QueueOutgoingPacketField((void *)(self + 0x228),0xffffffff);
    QueueOutgoingPacketField((void *)(self + 4),iVar1);
    RadioGroup_RefreshEnableStates(*(int *)(self + 0x34784),0);
  }
  FUN_00449250(self,1,0);
  return;
}
