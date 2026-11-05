/* BroadcastRing_Pop - 0x004e7660 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the consumer half of the ring
 * BroadcastRing_Push fills: it returns 0 when the tail at ctx+0x40bd4
 * equals the head at ctx+0x40bd0, otherwise copies the 0x200-byte record
 * at ctx+0x3d0 + tail * 0x200 out, reads the slot tag at ctx+0x403d0 +
 * tail * 4, and advances the tail with & 0x1ff. Sole caller is
 * BroadcastRingEvent, which drains the ring after the producer queues a
 * record.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20, no-prototype sweep). __fastcall's two
 * register slots (ECX=param_1, EDX=param_2) plus `ret 8` (2 stack args:
 * param_3/param_4) already account for all 4 declared parameters - no
 * register/decl mismatch. `in_EAX` is read at entry (`uVar2 = in_EAX &
 * 0xffffff00`) but is NOT a formal parameter: it's simply whatever EAX
 * held from the caller's immediately-preceding `lea eax,[esp+0xc]` (the
 * address later pushed as param_4) - the sole caller only ever inspects
 * AL (the bool result), so the high 3 bytes this seeds are never
 * observed. ECX/param_1 is likewise never read by the body. The bug was
 * purely at the sole call site, which had NO prototype in
 * include/functions.h (the header's generator skips this split-line
 * `uint __fastcall` definition, per
 * fastcall-decls-missing-from-functions-h), so a 2-argument call compiled
 * silently instead of erroring, dropping EDX (this function's own
 * param_1 - confirmed via `mov edx,ebp` at orig 0x4e7823, immediately
 * before the call) while leaving param_1(ECX, unused) unset entirely.
 */
#include "ghidra_types.h"


uint __fastcall BroadcastRing_Pop(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 *param_4)

{
  ushort uVar1;
  uint in_EAX;
  uint uVar2;
  ushort *puVar3;
  
  uVar2 = in_EAX & 0xffffff00;
  if (*(int *)(param_2 + 0x40bd4) != *(int *)(param_2 + 0x40bd0)) {
    puVar3 = (ushort *)(*(int *)(param_2 + 0x40bd4) * 0x200 + 0x3d0 + param_2);
    uVar1 = *puVar3;
    for (uVar2 = (uint)(uVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
      *param_3 = *(undefined4 *)puVar3;
      puVar3 = puVar3 + 2;
      param_3 = param_3 + 1;
    }
    for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(char *)param_3 = (char)*puVar3;
      puVar3 = (ushort *)((int)puVar3 + 1);
      param_3 = (undefined4 *)((int)param_3 + 1);
    }
    *param_4 = *(undefined4 *)(param_2 + 0x403d0 + *(int *)(param_2 + 0x40bd4) * 4);
    uVar2 = *(int *)(param_2 + 0x40bd4) + 1U & 0x800001ff;
    if ((int)uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffe00) + 1;
    }
    *(uint *)(param_2 + 0x40bd4) = uVar2;
    uVar2 = CONCAT31((int3)(uVar2 >> 8),1);
  }
  return uVar2;
}

