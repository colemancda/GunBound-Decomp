/* QueueSpriteSpansByContentId - 0x004eb8e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): this is a pure key-lookup wrapper that
 * tail-forwards into QueueSpriteFrameSpans (0x4ed870) or its twin
 * QueueTextureRegionSpans (0x4ebaf0), and it carries FOUR inputs, not
 * the two Ghidra declared. ECX is param_1, the content/frame index,
 * compared against the inner key at [node+8]; the single stack slot is
 * param_2, the registry group, loaded into EDX at 0x4eb8e0 and compared
 * against the outer key at [node+4]. EAX is never written anywhere in
 * 0x4eb8e0..0x4eb937 and EBX is never written either, so both are
 * read-before-write live-ins that exist only to be handed on: the
 * forward stores EBX into the outgoing stack slot and leaves EAX alone,
 * which makes EBX the callee's x and EAX its y.
 *
 * The 12 call sites were a RE-SLOT, not an append. Each passed exactly
 * one argument - the group constant 7000 / 500 / 0x1b5a / 0x1b59 - which
 * the erased-__thiscall (= cdecl) compile bound to param_1, while the
 * original pushes that value as param_2 and carries the index in ECX.
 * Every site is in DrawWindGauge.c and each was paired by a witness in
 * its own block rather than by position: LAB_00406f80 and LAB_00407859
 * are literally binary 0x406f80 and 0x407859; the three guard-depth
 * stores (`local_4 = 0xc / 0xd / 0xf`) separate the three otherwise
 * identical 500-group sites, together with their EncodeChecksumDeltaDiv
 * divisors 200 / 0x14 / 2; and the two 0x1b5a/0x1b59 sites take their
 * index from a PeekPacketChecksumState result Ghidra had discarded,
 * spilled to [esp+0x10] one push deep and read back from the same slot
 * after LeaveCriticalSection.
 */
#include "ghidra_types.h"


void __thiscall QueueSpriteSpansByContentId(uint param_1,uint param_2,int regEax,int regEbx)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  while( true ) {
    if (param_2 < uVar1) {
      return;
    }
    if (uVar1 == param_2) break;
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar1 = *(uint *)(iVar2 + 4);
  }
  iVar2 = *(int *)(iVar2 + 0x10);
  uVar1 = *(uint *)(iVar2 + 8);
  if (param_1 < uVar1) {
    return;
  }
  while (uVar1 != param_1) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (param_1 < uVar1) {
      return;
    }
  }
  if ((int)param_1 < 0) {
    return;
  }
  if (*(char *)(iVar2 + 0x18) == '\x01') {
    /* Tail forward, not a call: `mov [esp+4],ebx / jmp 0x4ed870` at
     * 0x4eb92a - which is why callsite_regs.py, scanning call
     * instructions only, reports 20 binary sites for QueueSpriteFrameSpans
     * against 21 in source. The incoming stack slot (param_2) is
     * OVERWRITTEN with EBX, so EBX becomes the callee's x; ECX (param_1),
     * EDX (loaded from param_2 at 0x4eb8e0) and EAX pass through
     * untouched. The same shape repeats at 0x4eb933 into
     * QueueTextureRegionSpans, which is not yet recovered. */
    QueueSpriteFrameSpans((int)param_1,regEbx,regEax,(int)param_2);
    return;
  }
  QueueTextureRegionSpans();
  return;
}

