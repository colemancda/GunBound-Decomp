/* AtlArray_Append_450 - 0x0044c630 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlArray<E>::Append(const CAtlArray& aSrc)
 * for the 0x450-byte avatar-item record - the member
 * AtlArray_RemoveAll_450's and AtlArray_CopyElement_450's headers already
 * identified at this address.  atlcoll.h's body in order: nOldSize =
 * m_nSize (`mov ebp,[ebx+4]`); SetCount(m_nSize + aSrc.m_nSize, -1)
 * (AtlArray_SetCount_450, 0x44c64a); CopyElements inlined as a lockstep
 * 0x450-stride walk calling the element operator=
 * (AtlArray_CopyElement_450, 0x44c673); return nOldSize (`mov
 * eax,ebp` / the [esp+0x10] spill).  Destination array in ECX (the
 * __fastcall param_1 here), source array in EAX.
 *
 * What fixes the member from outside is the callers.  FUN_0044bf00 runs
 * AtlArray_RemoveAll_450 on g_clientContext + 0x44e50 and then calls
 * this twice into that same array, from +0x44e30 (0x44c0dd) and then
 * +0x44e40 (0x44c0f4) - clear, then concatenate two arrays: Append's
 * use, not Add's.  The third site, 0x444886 in State07's avatar-store
 * handler, appends +0x44e50 onto +0x44e30 (`lea eax,[ecx+0x44e50]; add
 * ecx,0x44e30`).
 *
 * NOT TO BE CONFUSED with AtlArray_AppendCString (0x415bc0): despite
 * its name that one adds ONE constructed element and returns its index,
 * i.e. it is ATL's Add, the member AtlArray_Add_450 is for this
 * instantiation.  This function is ATL's Append (array onto array); the
 * two are not the same member at two instantiations.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX RECOVERED (2026-08-25), and the ECX slot filled with it: all three sites
 * pass two client-context sub-objects, `mov ecx,[0x5b3484]` then a lea and an
 * add off the same base, so nothing here needs a caller local.  The three
 * pairs are (+0x44e30, +0x44e50) in State07_AvatarStore_ProcessPacket and
 * (+0x44e50, +0x44e30) then (+0x44e50, +0x44e40) in FUN_0044bf00.
 *
 * The two FUN_0044bf00 sites are adjacent source lines inside one
 * straight-line run with no branch between them, which is the one case where
 * VA order and source order are the same thing.
 */
#include "ghidra_types.h"


undefined4 __fastcall AtlArray_Append_450(int param_1,int regEax)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = *(undefined4 *)(param_1 + 4);
  /* DROPPED ARGUMENTS RECOVERED (2026-08-27): 0x44c63b-0x44c64a is
     `mov ecx,[esi+4]; add ecx,ebp` = *(regEax+4) + uVar1 (ebp holds uVar1,
     callee-saved across this call), `mov edx,ebx` = param_1, and
     `or eax,0xffffffff` = the -1 nGrowBy default. */
  AtlArray_SetCount_450(*(int *)(regEax + 4) + (int)uVar1,(int *)param_1,-1);
  iVar2 = *(int *)(regEax + 4);
  if (iVar2 == 0) {
    return uVar1;
  }
  /* DROPPED POINTER WALK RECOVERED (2026-08-27).  Ghidra kept the counter
     and dropped the two cursors entirely, so AtlArray_CopyElement_450 was called with
     nothing.  0x44c664-0x44c67f: ESI starts at `ebp*0x450 + *(int *)param_1`
     (ebp = uVar1, still live across the AtlArray_SetCount_450 call) and steps by one
     0x450 record per iteration; EDI is pre-biased by `sub edi,eax` so that
     the loop's `lea ebx,[edi+esi]` yields `*(int *)regEax + k*0x450` -- i.e.
     the two arrays are walked in lockstep, destination in ESI. */
  iVar3 = (int)uVar1 * 0x450 + *(int *)param_1;
  iVar4 = *(int *)regEax;
  do {
    AtlArray_CopyElement_450(iVar3,iVar4);
    iVar3 = iVar3 + 0x450;
    iVar4 = iVar4 + 0x450;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return uVar1;
}

