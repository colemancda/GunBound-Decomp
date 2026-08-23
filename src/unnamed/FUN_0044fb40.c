/* FUN_0044fb40 - 0x0044fb40 in the original binary.
 *
 * Constructor of the widget embedded in CState07AvatarStore at +0x30bbc
 * (called only by FUN_00443c20, the state-7 ctor, as
 * `FUN_0044fb40(param_1 + 0xc2ef)`): zero-fills the fields, sets the
 * vtable to &PTR_FUN_00555b38 and initialises 4 CValueGuard cells. No
 * confirmed real class name yet.
 *
 * SEH-PROLOGUE ARTIFACT FIX (2026-08-06): same bug class already fixed
 * in WidgetChildArray_Destroy.c and FUN_00443c20.c - Ghidra's
 * `unaff_FS_OFFSET` was an UNINITIALISED pointer that the very first
 * statement READ through (`local_c = *unaff_FS_OFFSET`), faulting
 * before the vtable was ever assigned. The fault is swallowed during
 * InitGame, so the embedded object silently stayed vtable-NULL, and
 * State07_AvatarStore_OnEnter's slot-1 dispatch on it crashed reading
 * [0+4] the moment the AVATAR click reached it (live-reproduced).
 * The original's `push -1 / push <handler> / mov fs:[0],esp` is a
 * standard MSVC exception frame; per the established idiom we don't
 * reproduce __try/__except frames in a bring-up port - stripped along
 * with the (write-only, SEH-unwind-only) `local_4` state marker. */
#include "ghidra_types.h"


undefined4 * FUN_0044fb40(undefined4 *param_1)

{
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined1 *)((int)param_1 + 0x15) = 0;
  param_1[6] = 0xffffffff;
  param_1[7] = 0;
  *(undefined1 *)(param_1 + 8) = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[9] = 0xffffffff;
  *param_1 = &PTR_FUN_00555b38;
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x44fb9f/
   * 0x44fbb9/0x44fbd3/0x44fbed/0x44fc05/0x44fc29/0x44fc47/0x44fc65 (edi
   * loaded from ebp/esi+0x25c/esi+0x480/esi+0x6a4/ebp/esi+0x25c/esi+0x480/
   * esi+0x6a4 respectively). The zero-write pairs above the first 4 calls
   * match tableHandle(+0x14)/activeFlag(+0x220) for cell bases
   * param_1+0x38, +0x25c, +0x480, +0x6a4 - an array of 4 CValueGuard cells
   * (stride 0x224 = sizeof(CValueGuard)); the esi+0x25c/+0x480/+0x6a4
   * sites confirm esi==param_1 and pin cells 1/2/3 directly. Calls 5-8
   * repeat cells 0/1/2/3 (ebp reused from call 1). `param_1` is
   * `undefined4 *` (scales by 4), so byte offsets are taken via `(int)
   * param_1 + N`. See tools/encodeoutgoingpacketfield_sites.json. */
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x13] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x38, 0);
  *(undefined1 *)(param_1 + 0x11f) = 0;
  param_1[0x9c] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x25c, 0);
  *(undefined1 *)(param_1 + 0x1a8) = 0;
  param_1[0x125] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x480, 0);
  *(undefined1 *)(param_1 + 0x231) = 0;
  param_1[0x1ae] = 0;
  EncodeOutgoingPacketField((int)param_1 + 0x6a4, 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((int)param_1 + 0x38, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((int)param_1 + 0x25c, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((int)param_1 + 0x480, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((int)param_1 + 0x6a4, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined1 *)(param_1 + 0x232) = 0;
  return param_1;
}

