/* InitConnectionObject - 0x004d2170 in the original binary.
 *
 * The network-connection constructor: builds one of WinMain's three
 * connection objects (index 0/1/2 = direct-link / game-server / broker),
 * allocates its 0x24a70 session sub-object at conn+0x84e0, constructs it
 * via FUN_004e54e0, and spawns the per-connection socket worker thread
 * (SocketWorkerThreadProc). This is the same construction FUN_004058c0 does for the
 * 0x200c auto-connect object at +0x2004 - without the worker thread here,
 * SignalConnectRequest's SetEvent(session+0x10) has nothing to wake and
 * the broker connect() never fires.
 *
 * UN-DROPPED from the bring-up (2026-07-14): previously in bringup_drop.txt
 * with a hand-written MANUAL_STUB that allocated a zeroed session but
 * started no thread, so ServerSelect could reach BeginServerConnect but no
 * TCP connect to the broker ever happened. The stub was needed only
 * because this raw port carried a Ghidra SEH-prologue artifact
 * (unaff_FS_OFFSET, an uninitialized register the exception-frame
 * setup/teardown read+wrote) - stripped here per the entry/InitGame.c
 * idiom, leaving the real object construction + thread spawn intact.
 * EncodeOutgoingPacketField is itself bring-up-stubbed to a no-op, so its
 * four calls here are harmless (BeginServerConnect already calls it too).
 */
#include "ghidra_types.h"


undefined4 * InitConnectionObject(undefined4 *param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  void *pvVar2;
  uintptr_t uVar3;

  *(undefined1 *)(param_1 + 0xa9) = 0;
  param_1[0x26] = 0;
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
   * 0x4d218d/0x4d21ab (`lea esi,[ebp+0x84]` / `lea ebx,[ebp+0x2a8]`,
   * ebp = this file's own param_1): two distinct CValueGuard cells at
   * param_1+0x84 and param_1+0x2a8 (both show the same activeFlag(+0x220)/
   * tableHandle(+0x14) zero-init immediately before their own call here),
   * alternating cell1/cell2/cell1/cell2 across these 4 calls. `param_1` is
   * `undefined4 *` (scales by 4), so byte offsets are taken via `(int)
   * param_1 + N`, matching this file's own existing idiom (see the
   * +0x84e5/+0x84e6 pokes below). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x84, 0);
  *(undefined1 *)(param_1 + 0x132) = 0;
  param_1[0xaf] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x2a8, 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x84, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)param_1 + 0x2a8, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0x133] = param_2;
  uVar1 = DAT_0056dc30[param_2];
  pvVar2 = operator_new(0x210);
  if (pvVar2 == (void *)0x0) {
    pvVar2 = (void *)0x0;
  }
  else {
    *(undefined1 *)((int)pvVar2 + 0x208) = 0;
  }
  *(undefined4 *)((int)pvVar2 + 0x20c) = uVar1;
  param_1[0x213a] = pvVar2;
  *(undefined1 *)(param_1 + 0x2139) = 0;
  *(undefined1 *)((int)param_1 + 0x84e5) = 0;
  *(undefined1 *)((int)param_1 + 0x84e6) = 0;
  *param_1 = 0;
  pvVar2 = operator_new(0x24a70);
  if (pvVar2 == (void *)0x0) {
    pvVar2 = (void *)0x0;
  }
  else {
    /* FUN_004e54e0's 1st arg (unaff_ESI, the object being constructed) is
     * this same freshly-allocated pvVar2 - same pattern as
     * FUN_004058c0.c's identical construction call. */
    FUN_004e54e0(pvVar2,param_2,param_3);
  }
  param_1[0x2138] = pvVar2;
  *(undefined1 *)((int)pvVar2 + 0x18) = 1;
  uVar3 = __beginthread(SocketWorkerThreadProc,0,pvVar2);
  *(uintptr_t *)((int)pvVar2 + 4) = uVar3;
  if (uVar3 == 0) {
    *(undefined1 *)((int)pvVar2 + 0x18) = 0;
  }
  param_1[0x213b] = 0;
  return param_1;
}

