/* CommEngineCloseConnection - 0x004fe6a0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): close one connection - fire the engine's notify
 * virtual (vtable 0x5575b8 slot 2), verify the node is still on the
 * engine's list, closesocket the SOCKET at node+8, and erase the node
 * via CommConnectionList_Erase (was FUN_004ff720). Six call sites make
 * it the engine's one shared close routine: CommEngineRecv's and
 * CommEngineSend's error paths (three sites), the FD_CLOSE (0x20) arm
 * of CommEngineNotifyWndProc, the failed-shutdown fallback in
 * CommEngineShutdownConnection (was FUN_004fdda0), and the owner's
 * destructor DestroyCommP2POwner (was FUN_004fd230).
 *
 *
 * DROPPED-REG FIX (2026-08-28): EAX is the connection NODE to close and
 * erase - held in EDI for the whole body (`mov edi,eax` at 0x4fe6a2),
 * verified present in the engine's list before its socket at +8 is
 * closed and FUN_004ff720 unlinks it. param_2 is the vtable'd ENGINE
 * object: the virtual through *param_2+8 fires first, then `add esi,4`
 * at 0x4fe6b2 steps to the raw list at engine+4 for the walk and the
 * erase - which is why the FUN_004ff720 call passes param_2 + 1.
 *
 * The virtual call was also short: the binary pushes EDI then ECX
 * (0x4fe6a8/0x4fe6a9), so it receives (param_1, node), not the single
 * argument the port showed.
 *
 * Six call sites. Five load ECX with 0; the sixth,
 * CommEngineNotifyWndProc's 0x20 arm at 0x4fe7ba, leaves ECX stale in
 * the original - the recovered call passes 0 there to match the other
 * five rather than reproduce an uninitialised read.
 *
 * DISPATCH `this` RESTORED (2026-10-30): the slot-2 call also loads ECX
 * with the engine object (`mov esi,edx` at 0x4fe6a4, `mov ecx,esi` at
 * 0x4fe6aa, `call [eax+8]` at 0x4fe6ac); the port passed only the two
 * stack values and dropped ECX.  Slot 2 of the engine's derived vtable
 * 0x5575b8 is CommP2POwner_OnConnectionClosed (0x5016d0, read from
 * .rdata), the only engine-derived vtable in the image (the base
 * 0x557598 has the `ret 8` no-op 0x4fdef0 there, which reads nothing).
 * That port is declared `void __fastcall (int param_1)` - ECX only; its
 * body never reads the two pushed dwords (see its header), so the call
 * now goes through CommEngineClosedNotifyFn, the same __fastcall(int)
 * shape, passing the engine as ECX and nothing on the stack.  param_1
 * (the pushed ECX value) is no longer forwarded; the prototype is
 * unchanged.
 */
#include "ghidra_types.h"

/* Slot 2 of the engine vtable 0x5575b8: CommP2POwner_OnConnectionClosed,
 * declared __fastcall(int this) in this tree - match it exactly. */
typedef void (__fastcall *CommEngineClosedNotifyFn)(int self);


void __fastcall CommEngineCloseConnection(undefined4 param_1,int *param_2,int *regEax)

{
  int *in_EAX = regEax;
  int *piVar1;
  
  /* 0x4fe6aa: ECX = engine (param_2), call [vtbl+8] */
  ((CommEngineClosedNotifyFn)*(code **)(*param_2 + 8))((int)param_2);
  piVar1 = (int *)param_2[1];
  if (piVar1 != (int *)0x0) {
    while (in_EAX != piVar1) {
      piVar1 = (int *)*piVar1;
      if (piVar1 == (int *)0x0) {
        return;
      }
    }
    if (in_EAX[2] != 0xffffffff) {
      closesocket(in_EAX[2]);
    }
    CommConnectionList_Erase(param_2 + 1,in_EAX);
  }
  return;
}

