/* AtlArray_RemoveAll_450 - 0x0044c5f0 in the original binary.
 *
 * Named below; still a raw/near-verbatim port of Ghidra's decompiler
 * output rather than a hand-verified reconstruction.  See src/README.md's
 * "Raw/verbatim ports" section for what that status means.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_EDI is the array, and it is
 * `g_clientContext + 0x44e20 / 0x44e30 / 0x44e40 / 0x44e50` -- four separate
 * arrays of the same 0x450-byte element.  Every site has the identical
 * two-instruction shape `mov edi,[0x5b3484]` (g_clientContext) then
 * `add edi,0x44eN0` directly before the call, and the constant differs per
 * site, so each one carries its own witness and no ordering assumption is
 * needed.  The two pairs of back-to-back calls take consecutive arrays.
 *
 * The body is CAtlArray<T>::RemoveAll for that element -- destructor loop
 * over m_nSize, free(m_pData), then m_pData/m_nSize/m_nMaxSize zeroed --
 * i.e. exactly the `nNewSize == 0` arm of AtlArray_SetCount_450 (0x44c7b0),
 * which walks the same 0x450 stride and calls the same FUN_00426810
 * per-element destructor.  The callers corroborate the container reading:
 * both files pass these same bases to FUN_0044c630 on the next line, and
 * FUN_0044bf00 _qsort's `*(void **)(g_clientContext + 0x44e40)` with
 * `*(size_t *)(g_clientContext + 0x44e44)` as the count and 0x450 as the
 * element width -- the m_pData/m_nSize pair at +0/+4 of one of them.
 *
 * ATL7 CAtlArray<T>::RemoveAll() for the 0x450-byte element -- `void
 * RemoveAll() { SetCount(0, -1); }` with the inline call constant-folded,
 * which is why the body is instruction-for-instruction the `nNewSize == 0`
 * arm of AtlArray_SetCount_450 (0x44c7b0): the `if (m_pData)` test, the
 * destructor loop over m_nSize at 0x450 stride into FUN_00426810, _free,
 * then m_pData/m_nSize/m_nMaxSize zeroed. m_nGrowBy at +0x0c is left alone,
 * as ATL leaves it.
 *
 * NAMED 2026-08-27. Three pieces of evidence outside the body settle it.
 *
 * (1) The whole instantiation is present around it, so the class is not in
 * doubt: 0x44c630 is Append (returns nOldSize, SetCounts to nOldSize +
 * src.m_nSize, then copies with FUN_0044c740), 0x44c6a0 is RemoveAt (with
 * ATL's `iElement + nElements > m_nSize -> AtlThrow(E_INVALIDARG)` intact as
 * ThrowCxxException(0x80070057)), 0x44c7b0 is SetCount, 0x44c870 is
 * CallConstructors, 0x426700 is CallDestructors, 0x42af40 is GrowBuffer. It
 * is ATL and not MFC for the same reason recorded in
 * AtlArray_SetCount_450.c: this family throws E_INVALIDARG and returns bool
 * where MFC asserts and returns void.
 *
 * (2) It is RemoveAll and not the destructor or SetCount. ATL7's ~CAtlArray
 * does only CallDestructors + free and never resets the counts, whereas
 * 0x44c61f/0x44c622/0x44c625 write all three fields. SetCount's identical
 * arm ends `mov al,1` for its bool contract; this one falls through to `ret`
 * at 0x44c629 with no return value, and takes no size argument at any call
 * site -- the void signature RemoveAll has after the fold.
 *
 * (3) The callers use it as empty-then-refill, never as a resize. All five
 * sites pass an array base in EDI, `mov edi,[0x5b3484]` then `add
 * edi,0x44eN0`, so each carries its own witness: g_clientContext + 0x44e20
 * (owned-item catalog), + 0x44e30 (pending equip), + 0x44e40 (purchase
 * list), + 0x44e50 (the merged list the 0x6004 SetAvatarRequest is built
 * from). State07_AvatarStore_ProcessPacket clears +0x44e20/+0x44e30 on
 * GB_OP_GET_AVATAR_RESPONSE and then rebuilds them from the payload, and
 * clears +0x44e30/+0x44e40 on GB_OP_SET_AVATAR_RESPONSE and then Appends
 * into +0x44e30; FUN_0044bf00 does qsort(+0x44e40), RemoveAll(+0x44e50),
 * Append(+0x44e50 <- +0x44e30), Append(+0x44e50 <- +0x44e40).
 *
 * The element is the avatar-item record already characterised elsewhere in
 * the tree: EquipAvatarPart, UnequipAvatarSlot,
 * RefreshConnectionStatusLabel, FUN_0050a030, FUN_0050ae40 and FUN_00424400
 * all index *(g_clientContext + 0x44e20) by 0x450 and read the guarded
 * part-code cell at +0x22c, bounds-checked against the count at +0x44e24 --
 * the m_pData/m_nSize pair at +0/+4 of the struct this function zeroes. Its
 * destructor FUN_00426810 releases the record's two CValueGuard cells at
 * +0x1c and +0x240.
 *
 * The _450 suffix is required, not decorative: the unsuffixed
 * AtlArray_GrowBuffer (0x50ed30) and AtlArray_RemoveAt (0x415470) are the
 * 4-byte-element widget-child instantiation, and the sibling
 * CAtlMap::RemoveAll instantiations (FUN_00404b90, FUN_00415560,
 * FUN_00415600) are still unnamed and would collide.
 *
 * Not renamed to an owner-flavoured name (AvatarCatalogArray_Clear and the
 * like, on the InventoryItemArray_Reserve precedent): that would split one
 * template instantiation across two prefixes from its own SetCount, and
 * "catalog" is wrong at three of the five sites.
 *
 * No vtable references (tools/find_vtable_refs.py 0x44c5f0 is empty). 5
 * binary call sites, 5 C call sites, 1 argument each. */
#include "ghidra_types.h"


void AtlArray_RemoveAll_450(int *regEdi)

{
  int iVar1;
  int iVar2;
  int *unaff_EDI = regEdi;
  
  iVar2 = *unaff_EDI;
  if (iVar2 != 0) {
    for (iVar1 = unaff_EDI[1]; iVar1 != 0; iVar1 = iVar1 + -1) {
      FUN_00426810(iVar2);
      iVar2 = iVar2 + 0x450;
    }
    _free((void *)*unaff_EDI);
    *unaff_EDI = 0;
  }
  unaff_EDI[1] = 0;
  unaff_EDI[2] = 0;
  return;
}

