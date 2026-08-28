/* QueueSpriteFrameSpans - 0x004ed870 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SIGNATURE RECOVERY: the real entry takes FOUR inputs, not the two
 * Ghidra declared, and one of the two it did declare was landing in the
 * wrong slot at every site that passed anything.
 *
 * ECX     -> param_1  frame/region index. Ghidra had this one, as the
 *                     __thiscall `this`; guarded by `test esi,esi / jl`
 *                     at 0x4ed886, then handed to FindSpriteFrame as the
 *                     INNER key (`mov esi,ecx` at 0x4ed87e).
 * EDX     -> regEdx   sprite-registry OUTER key (the "group"). Never
 *                     written between 0x4ed870 and the `call 0x4f30c0`
 *                     at 0x4ed893, so it flows straight through into
 *                     FindSpriteFrame's EDX (`cmp ecx,edx` at 0x4f30c9).
 *                     Ghidra lost it because it modelled that call as
 *                     argument-less.
 * EAX     -> regEax   destination Y. `mov ebx,eax` at 0x4ed874, then
 *                     `add ebx,[frame+0x2c]` at 0x4ed8af, clipped
 *                     against g_clipMinY (0x793534) / g_clipMaxY
 *                     (0x56df34), and `inc ebx` at 0x4ed9d4 once per
 *                     scanline of the row loop.
 * [esp+4] -> param_2  destination X. Folded once with the frame's own
 *                     +0x28 (`mov ecx,[eax+0x28]` at 0x4ed8a0 / `add
 *                     edx,ecx` at 0x4ed8ad), stored back into its own
 *                     slot at 0x4ed8b8, then clipped against g_clipMinX
 *                     (0x793530) / g_clipMaxX (0x56df30) and re-read
 *                     once per span at 0x4ed943.
 *
 * FRAME MODEL. The epilogue at 0x4ed9e7 is a bare `ret` (ret 0) and the
 * callers clean with `add esp,4`, so ret N proves nothing about the
 * argument count here. The single stack slot is proved instead by
 * reading it twice at two different push depths: `[esp+0x1c]` at
 * 0x4ed8a3 (esp = entry-0x18, after sub 0x10 + push ebx + push esi) and
 * `[esp+0x24]` at 0x4ed943 (esp = entry-0x20, after push edi + push ebp)
 * both resolve to entry+4. The same model puts `[esp+0x14]` at entry-0xc
 * and `[esp+0x18]` at entry-8 - exactly Ghidra's local_c and local_8,
 * two independently named slots that confirm it. No memory reference in
 * the function reaches above entry+4, so there is exactly one stack
 * argument.
 *
 * RE-SLOT, NOT APPEND. 4 of the 21 sites already passed one argument,
 * but that argument is the PUSHED value - x, i.e. param_2 - which the
 * erased-__thiscall (= cdecl) compile was binding to param_1. The proof
 * is three of them (0x407aac / 0x407b22 / 0x407b88) retaining the SAME
 * constant 0x141 while their ECX differs - 0xb1, 0xb0, 0xb2 - so the
 * retained value cannot be the index; the fourth (0x407c8e) retains
 * iVar2, which the else-branch twin in the same block passes as its own
 * pushed x. Those four move one slot right; the other 17 passed nothing
 * at all.
 *
 * PAIRING. Each site is one basic block that builds ONE argument list
 * and then picks a twin with `cmp byte [node+0x18],1 / jne <0x4ebaf0> /
 * call <here>`: QueueTextureRegionSpans (0x4ebaf0) is this function's
 * exact twin and shares the setup, the push included. The register order
 * inside the block varies, and five DrawWindGauge sites (0x407769,
 * 0x4077d4, 0x40784a, 0x407c8e, 0x407d8f) carry ECX in from the tree
 * walk with no `mov ecx,INDEX` at all - there ECX is pinned instead by
 * the `test ecx,ecx / jl` guard that the C spells `-1 < (int)uVarN`,
 * with the `cmp edx,ecx` direction naming which of Ghidra's two locals
 * is the sought key. That still leaves two independent witnesses per
 * site: Ghidra's kept LAB_004xxxxxx labels ARE the block addresses, and
 * the else-branch QueueTextureRegionSpans call in the SAME source block
 * already spells the x value out (0x2f7, 0x8a, uVar9, iVar2, ...). The
 * group constant is a third check - it always equals the 7000/500/60000
 * key the caller's own tree walk just searched for, a few instructions
 * above (e.g. `cmp edx,0x1b58` at 0x4077ff for the 0x40784a site).
 *
 * SITE COUNT. 21 source sites vs 20 from callsite_regs.py: the 21st is
 * QueueSpriteSpansByContentId's tail forward `jmp 0x4ed870` at 0x4eb92e,
 * which that tool does not see because it scans call instructions only.
 * That forwarder pops its saves at 0x4eb926, restoring esp to the return
 * address, then OVERWRITES the incoming stack slot with EBX (`mov
 * [esp+4],ebx` at 0x4eb92a), so EBX becomes this callee's x. EAX is
 * never written anywhere in that function, and EDX is loaded once from
 * its own param_2 at 0x4eb8e0 and never rewritten - so it forwards
 * (param_1, regEbx, regEax, param_2). Expressing that required promoting
 * QueueSpriteSpansByContentId itself, so its own 12 call sites - all in
 * DrawWindGauge.c, and a re-slot of exactly the same shape - were
 * recovered in the same pass; see that file's header.
 */
#include "ghidra_types.h"


undefined4 __thiscall QueueSpriteFrameSpans(int param_1,int param_2,int regEax,int regEdx)

{
  ushort uVar1;
  int iVar2;
  int in_EAX = regEax;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  ushort *puVar8;
  ushort *puVar9;
  int local_c;
  int local_8;
  
  /* FindSpriteFrame's own three inputs are visible right here at
   * 0x4ed88e-0x4ed893: EAX = the fixed literal 0xea0e18 (&g_spriteRegistry,
   * the container the large majority of its sites use), EDX = regEdx
   * passed straight through, ESI = param_1 (`mov esi,ecx` at 0x4ed87e). Its
   * prototype is deliberately K&R-empty, so filling them here is safe. */
  if (((g_screenSurface != 0) && (-1 < param_1)) &&
     (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,regEdx,param_1), iVar3 != 0)) {
    iVar2 = *(int *)(iVar3 + 0x28);
    iVar7 = in_EAX + *(int *)(iVar3 + 0x2c);
    puVar4 = *(ushort **)(iVar3 + 0x34);
    iVar3 = *(int *)(iVar3 + 0x24);
    iVar5 = 0;
    local_8 = iVar3;
    if (iVar7 < g_clipMinY) {
      iVar5 = g_clipMinY - iVar7;
      iVar7 = iVar7 + iVar5;
      local_8 = iVar3 - iVar5;
    }
    if (g_clipMaxY < local_8 + iVar7) {
      local_8 = (g_clipMaxY - iVar7) + 1;
    }
    if (iVar5 <= iVar3) {
      if (0 < iVar5) {
        do {
          iVar5 = iVar5 + -1;
          puVar4 = puVar4 + *puVar4;
        } while (iVar5 != 0);
      }
      iVar3 = g_clipMaxX;
      if (0 < local_8) {
        do {
          uVar1 = puVar4[1];
          puVar8 = puVar4 + 2;
          puVar4 = puVar4 + *puVar4;
          local_c = 0;
          if (uVar1 != 0) {
            do {
              uVar6 = (uint)puVar8[1];
              iVar7 = (uint)*puVar8 + param_2 + iVar2;
              iVar5 = uVar6 + iVar7;
              if (iVar3 < iVar7) break;
              if (g_clipMinX < iVar5) {
                if (iVar7 < g_clipMinX) {
                  if (iVar3 < iVar5) {
                    iVar5 = iVar3 + 1;
                  }
                  puVar9 = puVar8 + (g_clipMinX - iVar7) + 2;
                  iVar7 = g_clipMinX;
                }
                else {
                  if (iVar3 < iVar5) {
                    QueueCompositorSpan(iVar7,iVar3 + 1,puVar8 + 2,(int)&g_spriteDrawBatchPool);
                    iVar3 = g_clipMaxX;
                    break;
                  }
                  puVar9 = puVar8 + 2;
                }
                QueueCompositorSpan(iVar7,iVar5,puVar9,(int)&g_spriteDrawBatchPool);
                uVar6 = (uint)puVar8[1];
                iVar3 = g_clipMaxX;
              }
              puVar8 = puVar8 + uVar6 + 2;
              local_c = local_c + 1;
            } while (local_c < (int)(uint)uVar1);
          }
          local_8 = local_8 + -1;
        } while (local_8 != 0);
      }
    }
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

