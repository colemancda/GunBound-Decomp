/* StringMap_Rehash_1c - 0x00500440 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::Rehash(nBins) for the 0x1c-node
 * maps - the same member as StringMap_Rehash_10 (see that file for the
 * atlcoll.h statement-by-statement match), instruction for instruction,
 * with only the node offsets moved: the relink reads m_pNext at
 * node+0x14 (0x500508) and m_nHash at node+0x18 (0x500500), the
 * stride-8/stride-4 CNode tail of a 0x1c-byte node.  Map in [ebp+8],
 * nBins in [ebp+0xc], `ret 8`.
 *
 * The instantiation is fixed by the callers, not the body.  All three
 * binary sites push (PickSize result, map) from the shared
 * NewNode/FreeNode threshold arm: StringMap_Insert_1c (0x500630) - the
 * insert half of StringMap_Find_1c - StringMap_FreeNode_1c (0x500679)
 * and StringMap_RemoveAll_1c's inlined FreeNode (0x4ff08d).  The prefix
 * follows those siblings.
 *
 * Promoted from a K&R prototype to (int *map, uint nBins) like
 * StringMap_Rehash_10; every C site already passed exactly those two
 * values, and the int-typed map register is cast.  The port
 * carried Ghidra's unaff_FS_OFFSET SEH-frame artifact (stripped below).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * SEH-PROLOGUE ARTIFACT STRIPPED (2026-10-29): the body registered an SEH
 * frame through Ghidra's `unaff_FS_OFFSET`, an uninitialised local pointer,
 * so every call read and wrote through garbage.  The original's
 * `push 0x5377d0` / `mov eax,fs:[0]` / `mov fs:[0],esp` (0x500445-0x500451) is
 * the compiler-generated EH registration, not program logic; stripped per
 * the ConstructStringFromText.c / StringMap_Insert_Int.c idiom, including
 * the unregister writes on each return path.
 *
 * HashMap_PickSize ARGS RECOVERED (2026-10-29): the call at 0x500475
 * passed nothing.  Inside this Rehash's nBins == 0 arm: EAX = `mov
 * eax,[esi+4]` (m_nElements), ECX = `mov ecx,esi`, ESI = [ebp+8] =
 * param_1, the map being rehashed.  Now passes (param_1,
 * (uint)param_1[1]).
 *
 * REHASH THRESHOLDS RECOVERED (2026-10-30): the port computed
 * m_nHiRehashThreshold (+0x18) and m_nLoRehashThreshold (+0x1c) through
 * two FloatToInt64() calls, which convert an uninitialised x87 ST0, so
 * both thresholds were garbage after every rehash.  The tail is ATL's
 * UpdateRehashThresholds over the new bin count: `fild [ebp+0xc]`
 * (param_2, already stored as m_nBins) at 0x500538, the UINT fix-up
 * `fadd [0x557fac]` (4294967296.0f) at 0x500542, then
 * `fld st(0); fmul [esi+0x14]` (m_fHiThreshold) at 0x50054a and _ftol2
 * (0x53753c, truncating) at 0x50054d stored to +0x18 at 0x500555, and
 * `fmul [esi+0x10]` (m_fLoThreshold) at 0x500552 and _ftol2 at 0x500558
 * stored to +0x1c at 0x500560, before the existing under-17 clamp.  Now
 * spelled out as (uint)(longlong)((double)param_2 * m_f*Threshold), the
 * form HashMap_PickSize uses.
 */
#include "ghidra_types.h"


void StringMap_Rehash_1c(int *param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_005377d0) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (param_2 == 0) {
    param_2 = HashMap_PickSize(param_1,(uint)param_1[1]);
  }
  if (param_2 != param_1[2]) {
    if (*param_1 == 0) {
      HashMap_InitHashTable(param_1,param_2,0);
      return;
    }
    local_8 = 0;
    puVar2 = operator_new(param_2 * 4);
    local_8 = 0xffffffff;
    uVar6 = param_2;
    puVar5 = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    for (; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    uVar6 = 0;
    if (param_1[2] != 0) {
      do {
        iVar3 = *(int *)(*param_1 + uVar6 * 4);
        while (iVar3 != 0) {
          uVar4 = *(uint *)(iVar3 + 0x18) % param_2;
          iVar1 = *(int *)(iVar3 + 0x14);
          *(undefined4 *)(iVar3 + 0x14) = puVar2[uVar4];
          puVar2[uVar4] = iVar3;
          iVar3 = iVar1;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < (uint)param_1[2]);
    }
    _free((void *)*param_1);
    *param_1 = (int)puVar2;
    param_1[2] = param_2;
    /* UpdateRehashThresholds, 0x500538-0x500560: nBins (param_2) as UINT */
    param_1[6] = (uint)(longlong)((double)param_2 * (double)*(float *)(param_1 + 5));
    uVar6 = (uint)(longlong)((double)param_2 * (double)*(float *)(param_1 + 4));
    param_1[7] = uVar6;
    if (uVar6 < 0x11) {
      param_1[7] = 0;
    }
  }
  return;
}

