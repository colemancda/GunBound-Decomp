/* FUN_004475c0 - 0x004475c0 in the original binary.
 *
 * CState07AvatarStore's vtable slot 6 (+0x18): the store's keydown/mouse
 * message dispatch, reached from WndProc's slot-6 forward for
 * WM_KEYDOWN / WM_MOUSEMOVE / the 0xf060 close command (see the
 * `[esp+4]-0x112` / `-0xef` / `-2` ladder in the original). Not yet
 * ported - the real body is ~0x19b bytes and pulls in the store's hit
 * test / button / close-confirm chain (0x44c3d0, 0x449250, 0x44bf00,
 * ...), none of which is exercised until the store screen is
 * interactive.
 *
 * CONVENTION-CORRECT STUB (2026-08-09): this MUST NOT be the plain-cdecl
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
 * signature so the stack stays balanced; returns 0 (no-op) until the
 * real handler is ported. */
#include "ghidra_types.h"

void __fastcall FUN_004475c0(void *thisPtr, int dummyEDX, uint msg, uint wParam,
                             uint lParam)
{
  (void)thisPtr;
  (void)dummyEDX;
  (void)msg;
  (void)wParam;
  (void)lParam;
  return;
}
