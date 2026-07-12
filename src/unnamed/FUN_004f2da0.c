/* FUN_004f2da0 - 0x004f2da0 in the original binary.
 *
 * Pushes a 3-field event record onto a ring buffer (queueObj[0]=write
 * cursor, queueObj[1]=read cursor, then 3 parallel 0x200-entry arrays at
 * +8/+0x808/+0x1008 for the 3 fields) - drops the record if the ring is
 * full (write cursor would collide with the read cursor).
 *
 * queueObj (in_EAX) is a dropped EAX register - orig 0x4f2da0 has no
 * `mov eax,` of its own, so it arrives from each caller's own context.
 * For network/HandleSocketEvent.c specifically, orig 0x4e57fa/0x4e5833
 * show `mov eax,[esi+0x20]` staying live (unclobbered) all the way to
 * every `call 0x4f2da0` in that function - i.e. queueObj = conn+0x20,
 * which HandleSocketEvent.c already null-checks before each call site
 * without ever passing it. Promoted to an explicit 1st parameter here;
 * HandleSocketEvent.c's call sites updated to match. Other callers
 * (ReceiveFramedPackets.c, SendSocketData.c, and a dozen+ unnamed/state
 * files) still need their own per-call-site EAX recovery - not yet
 * done, tracked separately.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f2da0(uint *queueObj, uint param_1,uint param_2,uint param_3)

{
  uint *in_EAX = queueObj;
  uint uVar1;

  uVar1 = *in_EAX + 1 & 0x800001ff;
  if ((int)uVar1 < 0) {
    uVar1 = (uVar1 - 1 | 0xfffffe00) + 1;
  }
  if (uVar1 != in_EAX[1]) {
    in_EAX[*in_EAX + 2] = param_1;
    in_EAX[*in_EAX + 0x202] = param_2;
    in_EAX[*in_EAX + 0x402] = param_3;
    *in_EAX = uVar1;
  }
  return;
}

