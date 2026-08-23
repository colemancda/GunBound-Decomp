/* WorkerThread_Shutdown - 0x0040d1c0 in the original binary.
 *
 * Signals a worker thread to stop and joins it, with a one-second timeout.
 *
 * Operates on the control block whose layout globals_sized.c records for
 * g_workerThreadBlock: vtable at +0, thread handle at +4, stop event at +8,
 * run flag at +0xc.  It installs a final vtable, clears the run flag, sets
 * the event, waits on the thread handle for 1000 ms, and closes the event.
 *
 * Reached through the CRT atexit chain (FUN_005437d0), so it is a static
 * object's destructor -- which is why the thread handle it waits on is the
 * same one Shutdown.c waits on as DAT_00e9c9c8, that being +4 of this block.
 *
 * At least four functions in this tree share the shape exactly, each writing
 * a different vtable first (FUN_004011b0, FUN_0043d9b0, FUN_004ef820): the
 * same stop-and-join destructor for different classes.  Only this one is
 * named, because only this one has its object identified; naming the others
 * from the shape alone would assert a class this has not established.
 */
#include "ghidra_types.h"


void WorkerThread_Shutdown(undefined4 *regEsi)

{
  
  *regEsi = &PTR_LAB_005520a4;
  *(undefined1 *)(regEsi + 3) = 0;
  SetEvent((HANDLE)regEsi[2]);
  if ((HANDLE)regEsi[1] != (HANDLE)0x0) {
    WaitForSingleObject((HANDLE)regEsi[1],1000);
  }
  CloseHandle((HANDLE)regEsi[2]);
  return;
}

