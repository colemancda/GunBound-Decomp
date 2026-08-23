/* WorkerThreadProcThunk - 0x004156b0 in the original binary.
 *
 * __beginthread entry thunk: forwards the thread argument to
 * WorkerThreadEventLoop.
 *
 * Same shape as the thunk in front of AudioStreamThreadProc, and named to
 * match it.
 */
#include "ghidra_types.h"


/* __beginthread thread proc; receives the control-block pointer __beginthread
 * was given (see WorkerThread_Start.c) as its normal __cdecl argument and forwards
 * it to the wait loop. */
void WorkerThreadProcThunk(void *param_1)

{
  WorkerThreadEventLoop(param_1);
  return;
}

