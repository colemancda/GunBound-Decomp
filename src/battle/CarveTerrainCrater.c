/* CarveTerrainCrater - 0x004e4450 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 6 argless PeekPacketChecksumState() calls (6 C : 6 orig,
 * goto-free zip), from tools/guard_cell_resolve.py over
 * 0x4e4460-0x4e4940.  All six read the SAME cell, &DAT_00796aa0 -
 * loaded as an immediate at every site, so there is nothing
 * path-dependent here despite the branching around them.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27).  ApplyCraterExcavation is the only
 * caller, and its three call sites are the three arms of the
 * PeekChecksumStateUnderLock(...) == 0 / 1 / 2 switch.  VA order is NOT source
 * order there: MSVC puts the == 2 arm in the fall-through at 0x4e49d6, then
 * == 1 at 0x4e4a4f, then == 0 at 0x4e4b28, while the C is written 0, 1, 2.
 *
 * The frame settles which is which, and does it three times independently.
 * ApplyCraterExcavation saves ebp and esi only, so esp is E-8 at all three
 * arms, making [esp+0x20], [esp+0x1c] and [esp+0x18] param_6, param_5 and
 * param_4 -- exactly the third argument each arm's own CarveTerrainCrater
 * line already passes.  Its EBP is [esp+0x14] = param_3 in the == 2 arm,
 * [esp+0x10] = param_2 in the == 1 arm, and in the == 0 arm the prologue's
 * own `mov ebp,[esp+8]` = param_1, never reloaded -- again matching what each
 * arm's C already uses.  `mov eax,ebp / cdq / sar eax,1` right after each
 * call is that arm's `param_N / 2`.
 *
 * So in_EAX is param_1, param_2 or param_3 by arm -- a value that is NOT
 * among this function's own arguments, so it becomes a real parameter.
 *
 * ESI PROMOTED (2026-08-27).  unaff_ESI was already declared and already used
 * for real pointer arithmetic -- `*(int *)(unaff_ESI + 0x1c)` and
 * `*(int *)(unaff_ESI + 0x34)` in the scanline loop -- so the function was
 * indexing a terrain context through an uninitialised local.  It is genuinely
 * live-in: ESI is never written anywhere in this function's 1300 bytes
 * (0x4e4450-0x4e4964), and the sole caller sets it in its own prologue,
 * `mov esi,eax` at 0x4e4978, from the terrainCtx it received in EAX -- the
 * same ESI it then writes `[esi+0x858]` through, which ApplyCraterExcavation
 * already spells `*(int *)(terrainCtx + 0x858)`.
 *
 * STILL OPEN, analysed here so the next pass need not redo it: the five
 * DarkenTerrainScorchRow calls are MIS-SLOTTED, not merely short.  That
 * callee is `__fastcall(param_1, param_2, param_3)` plus a dropped EAX, and
 * the single argument the C passes lands in param_1 (ECX) when it is really
 * the pushed param_3 -- `lea ecx,[eax+eax]` / `push`, which is the `* 2` the
 * C already writes.  The full map, with Ghidra's local_N == frame E-N
 * (confirmed twice: `mov [esp+0xc],eax` -> local_38, and `mov [esp+0x18],ebx`
 * -> local_30 with ebx = in_EAX/2 = iVar8):
 *
 *   param_1 = regEsi at all five sites (`mov ecx,esi`)
 *   param_2 = param_1 - q, where q is the quotient the C already computes
 *   param_3 = q * 2, i.e. the value the C currently passes
 *   in_EAX  = param_2                (0x4e47fd, the line-218 call)
 *             local_30 + param_2     (0x4e48da, first of the 239/240 pair)
 *             a slot at E-0xc        (0x4e48e8, second of that pair)
 *             param_2 + local_34     (0x4e492e, first of the 245/246 pair)
 *             local_14               (0x4e493c, second of that pair)
 *
 * So the two calls that look like exact duplicates in each pair are not: they
 * darken different rows, and only the dropped EAX distinguishes them.  What
 * blocks finishing it is the E-0xc slot, which Ghidra never modelled at all
 * (there is no local_c in this function), so it has to be reintroduced along
 * with whichever store feeds it -- the same shape as FUN_0044c630's dropped
 * pointer walk. */
#include "ghidra_types.h"


void CarveTerrainCrater(int param_1,int param_2,int param_3,int regEax,int regEsi)

{
  int iVar1;
  char cVar2;
  int in_EAX = regEax;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int unaff_ESI = regEsi;
  int iVar9;
  undefined4 *puVar10;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int iVarQ; /* the quotient the calls below need un-doubled */
  
  iVar8 = in_EAX / 2;
  local_38 = 1 - iVar8;
  iVar9 = iVar8 * -2 + 5;
  local_34 = 0;
  local_2c = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar3 = PeekPacketChecksumState((void *)&DAT_00796aa0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_18 = iVar8 * param_3;
  uVar5 = (local_18 / iVar3) * 2;
  iVar3 = param_1 - local_18 / iVar3;
  if ((-1 < param_2) && (param_2 < *(int *)(unaff_ESI + 0x1c))) {
    if (iVar3 < 0) {
      uVar5 = uVar5 + iVar3;
      iVar3 = 0;
    }
    if (*(int *)(unaff_ESI + 0x18) < (int)(uVar5 + iVar3)) {
      uVar5 = *(int *)(unaff_ESI + 0x18) - iVar3;
    }
    puVar10 = (undefined4 *)
              (*(int *)(unaff_ESI + 0x18) * param_2 + *(int *)(unaff_ESI + 0x34) + iVar3);
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined1 *)puVar10 = 0;
      puVar10 = (undefined4 *)((int)puVar10 + 1);
    }
  }
  if (-1 < iVar8) {
    local_1c = param_2 + iVar8;
    local_14 = param_2;
    local_28 = param_2 - iVar8;
    local_20 = 0;
    local_30 = iVar8;
    do {
      local_34 = local_34 + 1;
      local_20 = local_20 + param_3;
      local_14 = local_14 + 1;
      param_2 = param_2 + -1;
      iVar4 = iVar9;
      iVar3 = local_2c;
      if (-1 < local_38) {
        local_30 = local_30 + -1;
        local_1c = local_1c + -1;
        local_28 = local_28 + 1;
        local_18 = local_18 - param_3;
        iVar4 = iVar9 + 2;
        iVar3 = iVar9;
      }
      local_38 = local_38 + iVar3;
      local_2c = local_2c + 2;
      iVar9 = iVar4 + 2;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00796aa0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = (local_20 / iVar3) * 2;
      iVar3 = param_1 - local_20 / iVar3;
      if ((-1 < local_1c) && (local_1c < *(int *)(unaff_ESI + 0x1c))) {
        iVar4 = iVar3;
        uVar6 = uVar5;
        if (iVar3 < 0) {
          uVar6 = uVar5 + iVar3;
          iVar4 = 0;
        }
        iVar1 = *(int *)(unaff_ESI + 0x18);
        if (iVar1 < (int)(uVar6 + iVar4)) {
          uVar6 = iVar1 - iVar4;
        }
        puVar10 = (undefined4 *)(local_1c * iVar1 + *(int *)(unaff_ESI + 0x34) + iVar4);
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined1 *)puVar10 = 0;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
      }
      if ((-1 < local_28) && (local_28 < *(int *)(unaff_ESI + 0x1c))) {
        if (iVar3 < 0) {
          uVar5 = uVar5 + iVar3;
          iVar3 = 0;
        }
        iVar4 = *(int *)(unaff_ESI + 0x18);
        if (iVar4 < (int)(iVar3 + uVar5)) {
          uVar5 = iVar4 - iVar3;
        }
        puVar10 = (undefined4 *)(local_28 * iVar4 + *(int *)(unaff_ESI + 0x34) + iVar3);
        for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar10 = 0;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00796aa0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = (local_18 / iVar3) * 2;
      iVar3 = param_1 - local_18 / iVar3;
      if ((-1 < local_14) && (local_14 < *(int *)(unaff_ESI + 0x1c))) {
        iVar4 = iVar3;
        uVar6 = uVar5;
        if (iVar3 < 0) {
          uVar6 = uVar5 + iVar3;
          iVar4 = 0;
        }
        iVar1 = *(int *)(unaff_ESI + 0x18);
        if (iVar1 < (int)(uVar6 + iVar4)) {
          uVar6 = iVar1 - iVar4;
        }
        puVar10 = (undefined4 *)(local_14 * iVar1 + *(int *)(unaff_ESI + 0x34) + iVar4);
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined1 *)puVar10 = 0;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
      }
      if ((-1 < param_2) && (param_2 < *(int *)(unaff_ESI + 0x1c))) {
        if (iVar3 < 0) {
          uVar5 = uVar5 + iVar3;
          iVar3 = 0;
        }
        iVar4 = *(int *)(unaff_ESI + 0x18);
        if (iVar4 < (int)(iVar3 + uVar5)) {
          uVar5 = iVar4 - iVar3;
        }
        puVar10 = (undefined4 *)(param_2 * iVar4 + *(int *)(unaff_ESI + 0x34) + iVar3);
        for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar10 = 0;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
      }
    } while (local_34 <= local_30);
  }
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if ((cVar2 != '\x01') && ((&DAT_005f2f54)[g_clientContext] != '\x01')) {
    local_30 = iVar8 + 3;
    local_38 = 1 - local_30;
    local_34 = 0;
    iVar8 = local_30 * -2 + 5;
    local_2c = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    local_10 = local_30 * param_3;
    /* RE-SLOTTED (2026-08-27).  0x4e47ed-0x4e47fd: edx = [esp+0x48] = param_1
       minus the quotient, `lea ecx,[eax+eax]` = the doubled quotient is the
       PUSHED argument, ecx = esi = regEsi, and eax = [esp+0x50] with one
       push pending = param_2 -- the centre row. */
    iVarQ = local_10 / iVar3;
    DarkenTerrainScorchRow(regEsi,param_1 - iVarQ,iVarQ * 2,param_2);
    if (-1 < local_30) {
      iVar3 = 0;
      do {
        local_34 = local_34 + 1;
        iVar3 = iVar3 + param_3;
        iVar4 = iVar8;
        iVar9 = local_2c;
        if (-1 < local_38) {
          local_30 = local_30 + -1;
          local_10 = local_10 - param_3;
          iVar4 = iVar8 + 2;
          iVar9 = iVar8;
        }
        local_38 = local_38 + iVar9;
        local_2c = local_2c + 2;
        iVar8 = iVar4 + 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar9 = PeekPacketChecksumState((void *)&DAT_00796aa0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        /* RE-SLOTTED (2026-08-27).  The two calls are NOT duplicates: only
           the dropped EAX separates them, and it is the mirrored row pair
           about the centre.  0x4e48cf reads [esp+0x14] = local_30 and adds
           [esp+0x4c] = param_2; 0x4e48df reads the slot at frame E-0xc,
           which Ghidra never modelled but which holds param_2 - local_30
           identically throughout: it is seeded `param_2 - local_30` before
           the loop (0x4e4824) and incremented (0x4e4885) in the same branch
           that decrements local_30 (0x4e4881), and neither is touched
           anywhere else in the loop. */
        iVarQ = iVar3 / iVar9;
        iVar9 = iVarQ * 2;
        DarkenTerrainScorchRow(regEsi,param_1 - iVarQ,iVar9,param_2 + local_30);
        DarkenTerrainScorchRow(regEsi,param_1 - iVarQ,iVar9,param_2 - local_30);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar9 = PeekPacketChecksumState((void *)&DAT_00796aa0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        /* RE-SLOTTED (2026-08-27).  The mirrored pair again: 0x4e491a reads
           [esp+0x10] = local_34 and adds param_2, while 0x4e4933 reads
           [esp+0x30] = local_14 -- which is seeded to param_2 (0x4e481a,
           where local_34 is 0) and decremented (0x4e4850) in lockstep with
           local_34's increment (0x4e4841), so it equals param_2 - local_34
           at every iteration.  Ghidra dropped local_14's second-loop seed
           and decrement along with these arguments, so the invariant is
           used rather than the variable. */
        iVarQ = local_10 / iVar9;
        iVar9 = iVarQ * 2;
        DarkenTerrainScorchRow(regEsi,param_1 - iVarQ,iVar9,param_2 + local_34);
        DarkenTerrainScorchRow(regEsi,param_1 - iVarQ,iVar9,param_2 - local_34);
      } while (local_34 <= local_30);
    }
    puVar10 = (undefined4 *)(unaff_ESI + 0x51);
    for (iVar3 = 0x200; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
  }
  return;
}

