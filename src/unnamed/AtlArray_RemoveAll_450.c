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
 * RemoveAll() { SetCount( 0, -1 ); }` with the inline call constant-folded,
 * which is why the body is instruction-for-instruction the `nNewSize == 0`
 * arm of AtlArray_SetCount_450 (0x44c7c2-0x44c805): the `if (m_pData)` test,
 * the destructor loop over m_nSize at 0x450 stride into FUN_00426810, _free,
 * m_pData cleared, then m_nSize and m_nMaxSize cleared. m_nGrowBy at +0x0c
 * is left alone, as ATL leaves it. SetCount's copy of that arm ends `mov
 * al,1` for its bool contract; this one falls through to `ret` at 0x44c629
 * with no return value and takes no size argument at any call site.
 *
 * NAMED 2026-08-27.
 *
 * (1) IT IS NOT THE DESTRUCTOR, and the binary settles that without appeal
 * to the ATL header. FUN_00418dc0 (the client-context destructor) carries
 * the INLINED ~CAtlArray for these very four arrays, four times in a row at
 * 0x44e50 / 0x44e40 / 0x44e30 / 0x44e20, and each copy is only `if (m_pData)
 * { dtor loop at 0x450 stride into FUN_00426810; free; }` -- it never writes
 * m_nSize or m_nMaxSize. This function does write them, and writes them
 * UNCONDITIONALLY: the `je 0x44c621` at 0x44c5f8 skips only `*m_pData = 0`
 * at 0x44c61f, while `[edi+4] = 0` at 0x44c622 and `[edi+8] = 0` at 0x44c625
 * execute on both paths. An empty array still gets its counts stamped. That
 * single fact separates it from the inlined destructor and from nothing
 * else.
 *
 * (2) THE FOUR-FIELD LAYOUT AND THE ARRAY COUNT COME FROM THE CONSTRUCTOR,
 * not from inference. FUN_00415d40 zeroes four consecutive 0x10-byte headers
 * at g_clientContext + 0x44e20 / 0x44e30 / 0x44e40 / 0x44e50 -- {m_pData,
 * m_nSize, m_nMaxSize, m_nGrowBy} each, exactly src/cxx/AtlArray.h's layout.
 *
 * (3) THE INSTANTIATION IS COMPLETE AROUND IT, so the class is not in
 * question: 0x44c630 is Append (returns nOldSize, SetCounts to nOldSize +
 * src.m_nSize, then copies element by element with AtlArray_CopyElement_450), 0x44c6a0
 * is RemoveAt with ATL's `iElement + nElements > m_nSize ->
 * AtlThrow(E_INVALIDARG)` intact as ThrowCxxException(0x80070057), 0x44c7b0
 * is SetCount, 0x44c870 is CallConstructors (SEH-guarded placement-new loop
 * over FUN_00428550), 0x426700 is CallDestructors, 0x42af40 is GrowBuffer.
 * It is ATL and not MFC on four behavioural tests, not on vibe: GrowBuffer
 * is a SEPARATE function returning bool with ATL's `clamp(m_nSize/8, 4,
 * 1024)` policy (MFC folds growth into SetSize); SetCount returns bool where
 * MFC's SetSize returns void and throws CMemoryException; RemoveAt throws
 * E_INVALIDARG where MFC asserts; and the release is _free (0x5250c0) where
 * MFC uses `delete[] (BYTE*)m_pData`.
 *
 * (4) THE CALLERS USE IT AS EMPTY-THEN-REFILL, NEVER AS A RESIZE. All five
 * sites materialise the base the same way, `mov edi,[0x5b3484]` then `add
 * edi,0x44eN0`, with a different constant each time, so every site carries
 * its own witness and no VA-to-source pairing is needed: 0x4441da
 * (+0x44e20), 0x4441eb (+0x44e30), 0x44485e (+0x44e30), 0x44486f (+0x44e40),
 * 0x44c0c6 (+0x44e50). State07_AvatarStore_ProcessPacket clears +0x44e20 and
 * +0x44e30 on GB_OP_GET_AVATAR_RESPONSE and then rebuilds both record by
 * record from the payload (CAtlArray::Add, 0x42ae30, at 0x44426d and
 * 0x444286); on GB_OP_SET_AVATAR_RESPONSE it clears +0x44e30 and +0x44e40
 * and immediately Appends +0x44e30 <- +0x44e50 (0x444886, ecx = dest).
 * FUN_0044bf00 -- which writes opcode 0x6004, the reference server's
 * SetAvatarRequest -- does qsort(+0x44e40), RemoveAll(+0x44e50),
 * Append(+0x44e50 <- +0x44e30), Append(+0x44e50 <- +0x44e40).
 *
 * The four arrays: +0x44e20 is the owned-item list every renderer indexes;
 * +0x44e30 the working/equip set (RemoveAt is applied to it and to +0x44e20
 * at 0x4450xx); +0x44e40 the purchase list, which is Added to at 0x44464e
 * inside the GB_OP_BUY_RESPONSE success arm; +0x44e50 the merged list the
 * 0x6004 request is built from. The element is the avatar-item record
 * already characterised elsewhere: EquipAvatarPart, UnequipAvatarSlot,
 * RefreshConnectionStatusLabel, FUN_0050a030, RenderAvatarListRow, RenderAvatarListDragRow and
 * FUN_00424400 all index *(g_clientContext + 0x44e20) by 0x450 and read the
 * guarded part-code cell at +0x22c, bounds-checked against the count at
 * +0x44e24 -- the m_pData/m_nSize pair at +0/+4 of the struct this function
 * zeroes. Its destructor FUN_00426810 releases the record's two CValueGuard
 * handles at +0x1c and +0x240 (the value cells the copy helper moves are the
 * paired +8 and +0x22c).
 *
 * The _450 suffix is required, not decorative: the unsuffixed
 * AtlArray_GrowBuffer (0x50ed30) and AtlArray_RemoveAt (0x415470) are a
 * DIFFERENT instantiation of this same template, the 4-byte-element
 * widget-child array, and the same-element sibling already carries the
 * suffix (AtlArray_SetCount_450). That is the whole point of the
 * CArray_Grow_1750/_4004/_206 convention. (The CAtlMap::RemoveAll
 * instantiations HashMap_RemoveAll_2c / FUN_00415600 and the since-named
 * StringMap_RemoveAll_CString are a different container and would take a
 * map prefix, so they are not the collision risk here.)
 *
 * Not renamed to an owner-flavoured name (AvatarCatalogArray_Clear and the
 * like, on the InventoryItemArray_Reserve precedent): that would split one
 * template instantiation across two prefixes from its own SetCount, and
 * "catalog" is wrong at three of the five sites.
 *
 * No vtable references (tools/find_vtable_refs.py 0x44c5f0 is empty). 5
 * binary call sites, 5 C call sites, 1 argument each.
 */
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

