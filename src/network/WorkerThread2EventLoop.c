/* WorkerThread2EventLoop - 0x00415810 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00415810 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. The wait loop that WorkerThread2ProcThunk
 * forwards to, the second block's counterpart of WorkerThreadEventLoop
 * (0x4157b0) with the same dispatch: it rechecks the running flag (at +0xc
 * in this block, the offset globals.c records for DAT_007a767c and
 * WorkerThread2_Start sets) before every step, calls vtable slot 1 on a
 * timeout and slot 0 with the wait result followed by slot 1 on a signalled
 * handle, and ends with __endthread. It differs from the first loop in
 * waiting on ONE handle (the wait handle at +8, count 1) with a 10 second
 * timeout, where the first waits on two with 10 ms. Which subsystem the
 * vtable belongs to is not asserted, as in the first loop's header.
 */
#include "ghidra_types.h"


void WorkerThread2EventLoop(int *unaff_ESI)

{
  DWORD DVar1;

  if ((char)unaff_ESI[3] != '\0') {
    do {
      DVar1 = WaitForMultipleObjects(1,(HANDLE *)(unaff_ESI + 2),0,10000);
      if (DVar1 == 0xffffffff) break;
      if (DVar1 != 0) {
        if (DVar1 == 0x102) {
          if ((char)unaff_ESI[3] == '\0') break;
          (**(code **)(*unaff_ESI + 4))();
        }
        else {
          if ((char)unaff_ESI[3] == '\0') break;
          (**(code **)*unaff_ESI)(DVar1);
          (**(code **)(*unaff_ESI + 4))();
        }
      }
    } while ((char)unaff_ESI[3] != '\0');
  }
  __endthread();
  return;
}

