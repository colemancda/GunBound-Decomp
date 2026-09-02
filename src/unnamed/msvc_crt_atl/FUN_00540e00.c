/* FUN_00540e00 - 0x00540e00 in the original binary.
 *
 * The CRT static-initializer thunk for the DirectInput mouse/cursor
 * singleton: `mov eax,0xe53698 / call 0x4ee120 / push dtor / call
 * _atexit`. FIXED (2026-09-01): passes the coalesced
 * g_mouseDeviceTimerBlock now that FUN_004ee120's regEax is promoted.
 * (The bring-up build also runs the ctor from crt_shims_msvc.c's
 * startup hook since this thunk is not wired into a real .CRT$XCU
 * table; calling twice is idempotent - every store is a constant.)
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"

/* functions.h's generator skips this directory, so declare the atexit
 * dtor thunk locally (pre-existing gap surfaced by gating this file). */
void FUN_00543270(void);


void FUN_00540e00(void)

{
  FUN_004ee120((undefined4 *)g_mouseDeviceTimerBlock);
  _atexit(FUN_00543270);
  return;
}

