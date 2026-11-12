/* HeartbeatWorker_Destruct - 0x004011b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004011b0 mean this function.)
 *
 * NAMED (batch 48), LIKELY. Destructor of the control block at 0x7a767c:
 * registered through atexit by the 0x540e80 initializer (routine 0x5432b0:
 * mov esi,0x7a767c; call 0x4011b0, sole caller FUN_005432b0). It walks the
 * vtable chain back down (0x54b458 then 0x54b450), clears the run flag,
 * signals the event, waits 1000 ms on the thread handle at +4 and closes
 * the event: the same stop-and-join shape WorkerThread_Shutdown has for
 * the other block (its header already lists this address as one of the
 * shape's twins). Heartbeat prefix carried from HeartbeatWorker_OnTimeout;
 * LIKELY on that basis.
 */
#include "ghidra_types.h"


void HeartbeatWorker_Destruct(undefined4 *regEsi)

{
  
  *regEsi = &PTR_LAB_0054b458;
  *(undefined1 *)(regEsi + 3) = 0;
  SetEvent((HANDLE)regEsi[2]);
  *regEsi = &PTR_LAB_0054b450;
  *(undefined1 *)(regEsi + 3) = 0;
  SetEvent((HANDLE)regEsi[2]);
  if ((HANDLE)regEsi[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)regEsi[1],1000);
  }
  CloseHandle((HANDLE)regEsi[2]);
  return;
}

