/* SpawnDamagePopup - 0x00436860 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED (2026-09-21). Finds or creates a per-frame class-id-0x30d54
 * "hit total" widget (frame index = param_1; the class-id-0x30d54
 * constructor is FUN_00468620) and accumulates param_2 into its +0x48
 * field, resetting its +0x40 age counter - the merge/create idiom of a
 * floating damage number that keeps rising while more hits land in the
 * same frame. Confirmed by the class's own vtable-slot-2 Tick
 * (0x468660, UNCARVED in docs/vtable_census.txt): every tick it
 * increments +0x40/+0x44, decrements +0x3c (the screen Y offset) by 3
 * once +0x44 passes 10 (the number floats upward), marks itself dead
 * (+0x14=1) after 30 ticks, and eases +0x4c one quarter of the way
 * toward the +0x48 target each tick (a display-value catch-up curve).
 * Slot 3 (0x4686b0) confirms the payload is TEXT: it sprintfs the
 * eased +0x4c value (format string 0x551ed4), measures the resulting
 * digit string, and walks it character by character with a leading
 * '-'-sign check before drawing at (+0x38,+0x3c). All 5 real callers
 * feed param_2 from the return of an `EncodeChecksumDeltaSub(...,
 * 0xf)` or `EncodeChecksumDeltaSub(..., N*0xf)` call on the same
 * object's health-delta cell immediately above (a fixed 15-per-hit
 * chain-damage idiom), so param_2 is the damage just dealt.
 *
 * 2026-09-02: FindSpriteFrame's register args recovered from orig
 * 0x436877-0x436886 - see the site comment.
 *
 * DROPPED-ARGUMENT FIX (2026-09-21): the declaration below was already
 * correct (4 real params: ECX=param_1, EDX=param_2, `ret 8` at
 * 0x4368e2/0x4368a0 confirming 2 real stack dwords beyond the 2
 * registers, read at 0x4368bc `mov edx,[esp+0x10]` / `mov ecx,[esp+0xc]`
 * and stored into the new/found object's +0x3c/+0x38 fields) - but had
 * no functions.h prototype, so all 6 call sites in the tree (every one
 * of them) silently compiled passing only param_3/param_4 on the stack
 * and dropped param_1/param_2 (the two registers) entirely. Each site's
 * ECX/EDX reconstructed independently from its own disasm - see each
 * call site's own comment (src/unnamed/FUN_00478cb0.c,
 * src/unnamed/FUN_0045db20.c, src/unnamed/FUN_0045ea40.c (x1),
 * src/unnamed/FUN_0048f300.c (x2), src/battle/ExplodeSuperShot_Bullet2.c).
 * Pattern: ECX is always `*(int *)(obj + 8)` (sometimes `+ 0x32` on top),
 * where `obj` is that call site's own object/this pointer; EDX is
 * usually `-` the count last passed to the *first* EncodeChecksumDeltaSub
 * in the same block (negated at the call site) - except
 * ExplodeSuperShot_Bullet2's site, which passes that value un-negated
 * (no `neg` instruction on that path).
 */
#include "ghidra_types.h"


void __fastcall SpawnDamagePopup(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    if (param_1 != -1) {
      /* RECOVERED (2026-09-02), orig 0x436877-0x436886: EAX =
       * [0x5b3484]+0x6a7f88 = g_clientContext + 0x6a7f88 (the active-object
       * layer registry), EDX = 0x30d54 (class id), ESI = ecx = param_1
       * (frame; `mov esi,ecx` @0x436865, the same value guarded by the
       * `param_1 != -1` test @0x436872).  Cached scan: tools/
       * findspriteframe_sites.json call_addr 0x436886. */
      iVar2 = FindSpriteFrame(g_clientContext + 0x6a7f88,0x30d54,param_1);
      if (iVar2 != 0) {
        *(undefined4 *)(iVar2 + 0x40) = 0;
        *(int *)(iVar2 + 0x48) = *(int *)(iVar2 + 0x48) + param_2;
        return;
      }
    }
    pvVar3 = operator_new(0x50);
    if (pvVar3 == (void *)0x0) {
      iVar2 = 0;
    }
    else {
      FUN_00468620();
    }
    *(undefined4 *)(iVar2 + 0x3c) = param_4;
    *(int *)(iVar2 + 0x48) = param_2;
    *(undefined4 *)(iVar2 + 0x38) = param_3;
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

