/* HeartbeatWorker_Construct - 0x00401180 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00401180 mean this function.)
 *
 * NAMED (batch 48), LIKELY. Constructor of the control block at 0x7a767c
 * (the block WorkerThread2_Start starts and WorkerThread2EventLoop
 * drives). Its sole caller is the dynamic initializer at 0x540e80 (mov
 * esi,0x7a767c; call 0x401180), whose paired atexit routine 0x5432b0 calls
 * 0x4011b0 on the same block. Stamps vtable 0x54b450 then 0x54b458,
 * creates the wait event at +8, clears the stop flag at +0xc and +0x10 =
 * 0, matching the 0x10-byte block globals.c declares (flag at +0xc). The
 * Heartbeat prefix is carried from HeartbeatWorker_OnTimeout, the only
 * non-trivial slot of its vtable (see that note); LIKELY on that basis.
 */
#include "ghidra_types.h"


void HeartbeatWorker_Construct(undefined4 *regEsi)

{
  HANDLE pvVar1;
  
  *regEsi = &PTR_LAB_0054b450;
  regEsi[1] = 0;
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  regEsi[2] = pvVar1;
  *(undefined1 *)(regEsi + 3) = 0;
  *regEsi = &PTR_LAB_0054b458;
  *(undefined1 *)(regEsi + 4) = 0;
  return;
}

