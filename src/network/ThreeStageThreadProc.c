/* ThreeStageThreadProc - 0x004f47e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004f47e0 mean this function.)
 *
 * NAMED (batch 48), LIKELY. The thread start routine passed to
 * __beginthread (push 0x4f47e0 at 0x4e6b53, in
 * ReplayContext_StartWorkerThread, with this as the argument; the image
 * holds no other reference to it). Both ReplayContext_StartWorkerThread's
 * and UdpProbeWorkerThread's headers already describe it as the generic
 * runner that calls this object's vtable slots +8, +4 and +0xc in order
 * and then _endthread; for the g_replayContext object slot +4 is
 * UdpProbeWorkerThread and +8/+0xc are NoOpMethod. The name restates that
 * dispatch shape because no stage role is established from outside;
 * LIKELY on that basis, and it is not asserted to be unique to one class.
 */
#include "ghidra_types.h"


void ThreeStageThreadProc(int *param_1)

{
  (**(code **)(*param_1 + 8))();
  (**(code **)(*param_1 + 4))();
  (**(code **)(*param_1 + 0xc))();
  __endthread();
  param_1[1] = 0;
  return;
}

