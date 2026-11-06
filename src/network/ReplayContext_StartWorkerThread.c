/* ReplayContext_StartWorkerThread - 0x004e6b50 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (batch 40), LIKELY (name only; the port is still the deliberate
 * bring-up stub below and was NOT un-stubbed). In the original it zeroes
 * this+0x3b8 and this+0x3bc, calls __beginthread(0x4f47e0, 0, this) and
 * stores the returned handle at this+4 (disasm 0x4e6b50-0x4e6b83).
 *
 * External evidence: the sole caller InitGame (call at 0x40f3b9) loads
 * ESI = 0xe55ce0 = g_replayContext first. 0x4f47e0 is the generic
 * three-phase thread runner that UdpProbeWorkerThread's header documents:
 * it calls this object's vtable slots +8, +4, +0xc and then _endthread, and
 * for the g_replayContext object (vtable 0x5572f0, same one
 * ReplayContext_Destructor and ReplayContext_ScalarDeletingDestructor
 * belong to) slot +4 is UdpProbeWorkerThread. So this starts the worker
 * thread of the replay/broadcast context. The sibling starters
 * WorkerThread_Start / WorkerThread2_Start are the same
 * __beginthread-and-store-handle shape, called from the same place.
 */
#include "ghidra_types.h"


void ReplayContext_StartWorkerThread(void)

{
  /* BRING-UP WORKAROUND: skip starting this worker thread.
   *
   * Same dropped-ESI situation as WorkerThread_Start/FUN_00415530 (orig
   * 0x40f3b4 loads ESI=&g_replayContext before calling this), but that global
   * is ALREADY a large, widely-referenced struct throughout battle/replay
   * code (PostTurnEvent, FUN_004e7b60/004e80d0/004e84c0, WriteReplayEventRecord,
   * etc. all take &g_replayContext as their own context arg) with other globals
   * declared close behind it (DAT_00e55cf4 only 0x14 bytes later) - this
   * function needs to write as far as +0x3bc, which would require resizing
   * g_replayContext far beyond what's safe without auditing every one of those
   * other call sites. Not required to reach the logo/menu render loop;
   * revisit alongside a proper pass over the whole g_replayContext struct. */
  return;
}

