/* AtlArray_CopyElement_450 - 0x0044c740 in the original binary.
 *
 * Named below; still a raw/near-verbatim port of Ghidra's decompiler
 * output rather than a hand-verified reconstruction.  See src/README.md's
 * "Raw/verbatim ports" section for what that status means.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the same two-cell copy as FUN_0042aeb0 with the bases in registers - source EBX (unaff_EBX), dest ESI - at +8 and +0x22c.
 *
 * REGISTERS PROMOTED (2026-08-27).  Both bases were dropped and all three
 * call sites passed nothing.  The record is 0x450 bytes -- fixed
 * independently by FUN_0050a320.cpp's own `unsigned char local_45c[1104]`,
 * which is the destination at one of those sites -- and every caller walks
 * an array of them with an `add esi,0x450` stride.
 *
 * ESI is the destination and EBX the source, which the body already showed
 * (`*(unaff_ESI + 4) = *(unaff_EBX + 4)`) and each call site confirms
 * separately: FUN_0044c630 sets ESI to `uVar1*0x450 + *(int *)param_1` and
 * derives EBX from it by a constant delta; FUN_0050cff0 sets ESI from its
 * own loop counter over `*param_1` and takes EBX straight from param_3; and
 * FUN_0050a320 points ESI at the local_45c scratch record and EBX at
 * `this->[0x94]*0x450 + *(g_clientContext + 0x44e20)`.
 *
 * The assignment operator of the 0x450-byte element held by the four
 * CAtlArrays at g_clientContext + 0x44e20 / 0x44e30 / 0x44e40 / 0x44e50 --
 * the per-element copy behind src/cxx/AtlArray.h:101's `m_pData[m_nSize] =
 * e;`.
 * It copies the record MEMBER-WISE: the guarded bool at +0 (CopyGuardedBool,
 * dst in ECX / src in EAX, that function's own recovered convention), the
 * plain dword at +4, and the two 0x224-byte guarded values at +8 and +0x22c,
 * each moved by VALUE (Peek the source cell, Encode into the destination
 * cell) under g_valueGuardLock.  8 + 0x224 + 0x224 = 0x450 exactly, so those
 * four members ARE the record.  What it does NOT touch is the destination's
 * guard bookkeeping -- the tableHandles at +0x1c/+0x240 and the trailing
 * bytes at +0x228/+0x44c -- because those belong to the live destination
 * guards; that is precisely how it differs from the copy constructor below.
 *
 * NAMED 2026-08-27, from the callers, not the body.  Three binary call
 * sites, three C call sites, two arguments each:
 *
 * - 0x44c673, in FUN_0044c630 = CAtlArray::Append: caches m_nSize, calls
 * AtlArray_SetCount_450(m_nSize + aSrc.m_nSize, this, -1), walks the two
 * arrays in lockstep by 0x450 calling this function per element, and
 * returns the OLD size -- Append's exact contract and return.
 * - 0x50d0f0, in FUN_0050cff0 = CAtlArray::InsertAt(iElement, element,
 * nCount): the iElement >= m_nSize arm is a bare SetCount(iElement +
 * nCount, -1); the other arm is SetCount(m_nSize + nCount, -1), a
 * destructor loop (FUN_00426810) from nOldSize over the nCount slots
 * SetCount just constructed, _memmove of the (nOldSize - iElement) upper
 * elements up nCount slots, then CallConstructors (FUN_0044c870, which
 * loops FUN_00428550 at 0x450 stride) over the vacated hole.  BOTH arms
 * fall into `for (i = iElement; i < iElement + nCount; i++)
 * m_pData[i] = element` -- that last loop is this function.
 * - 0x50a411, in FUN_0050a320 (the Avatar-Store reorder) uses it directly
 * as `E temp; temp = m_pData[dragIndex];`: FUN_00428550 default-
 * constructs the 0x450 scratch local_45c[1104] above it, this copies the
 * record in, RemoveAt + InsertAt move it, and FUN_00426810 destroys the
 * temp at the end.
 *
 * Calling convention: dst arrives in ESI and src in EBX, with a plain `ret`.
 * That is an LTCG custom convention, the same family as
 * AtlArray_SetCount_450's ECX/EDX/EAX (three registers, which __fastcall
 * cannot produce) and AtlArray_RemoveAll_450's EDI -- it carries no
 * information about whether this is a class member, so the C port is a plain
 * two-argument function.
 *
 * It is the element's compiler-generated operator=, not a CAtlArray member:
 * 0x44c7a4 `mov eax,esi` returns the DESTINATION (`return *this`), which
 * every caller discards -- which is why the decompile typed it void.  A
 * whole-image byte scan finds ZERO occurrences of the little-endian dword
 * 0x0044c740 anywhere in the file, so it is non-virtual and reached only by
 * those three direct calls.
 *
 * The sibling AtlArray_SetCount_450 (0x44c7b0) already documents the rest of
 * this instantiation's family (GrowBuffer 0x42af40, CallConstructors
 * 0x44c870, CallDestructors 0x426700, per-element destructor 0x426810), and
 * AtlArray_RemoveAll_450 (0x44c5f0) documents RemoveAll and RemoveAt
 * (0x44c6a0).  It is ATL and not MFC for the reason those files record: this
 * family returns bool and throws E_INVALIDARG
 * (ThrowCxxException(0x80070057))
 * where MFC returns void and asserts.  The _450 suffix is required, not
 * decorative: the unsuffixed AtlArray_RemoveAt (0x415470) and
 * AtlArray_GrowBuffer (0x50ed30) are the 4-byte widget-child instantiation.
 * CArray_CopyElement_1750 (0x4ff2c0) is the naming precedent -- the same
 * element-assignment shape called from CArray_Add_1750's own
 * `m_pData[nIndex] = newElement` -- though nothing in the tree has yet
 * established whether that 0x1750 family is MFC or something else, so no
 * library attribution is claimed for it here.
 *
 * Do NOT confuse this with FUN_0042aeb0, the COPY CONSTRUCTOR of the same
 * element: that one zeroes the guard tableHandles at +0x1c/+0x240 and the
 * bytes at +0x228/+0x44c (exactly the cells the default constructor
 * FUN_00428550 zeroes) before copying.  This function assumes a live,
 * already-constructed destination, which is why InsertAt and Append must
 * construct the slots first and only then call it.
 *
 * The element type itself is still unnamed, which is why the name is the
 * container's and not the record's.  What is known about it from outside:
 * the 0x6002 (GB_OP_AVATAR_INVENTORY_RESPONSE) branch of
 * State07_AvatarStore_ProcessPacket builds one on the stack with +4 = -1,
 * +8 = the wire Item.id and +0x22c = the wire u32 at +0x14 (the reference
 * server's AvatarInventoryResponse.Item.field, documented at that offset);
 * EquipAvatarPart reads +0x22c as the part code, taking bits 16-19 as the
 * category nibble (`sar eax,0x10 / and al,0xf`) and bits 0-14 as the part
 * id; FUN_0044c370 decrements the +4 dword of every record above a
 * threshold and both its call sites pass the removed record's own +4, so +4
 * is a display index renumbered after a removal; and FUN_0044be40, the
 * _qsort comparator FUN_0044bf00 hands the +0x44e40 array with width 0x450,
 * sorts on +8.  The four arrays' roles are already pinned down in
 * AtlArray_RemoveAll_450.c (+0x44e20 owned-item catalog, +0x44e30 pending
 * equip, +0x44e40 purchase list, +0x44e50 the merged list the 0x6004
 * SetAvatarRequest is built from).  When the record type is named, this
 * function should be renamed to <Type>::operator= along with it.
 */
#include "ghidra_types.h"


void AtlArray_CopyElement_450(int dstRecord,int srcRecord)

{
  undefined4 uVar1;
  int unaff_EBX = srcRecord;
  int unaff_ESI = dstRecord;
  
  CopyGuardedBool((byte *)unaff_ESI,(byte *)unaff_EBX);
  *(undefined4 *)(unaff_ESI + 4) = *(undefined4 *)(unaff_EBX + 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 8));
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x44c76a
   * (`lea edi,[esi + 8]`, esi = this file's own `unaff_ESI`, already
   * used as a base pointer above for the `unaff_ESI + 4` write): cell is
   * unaff_ESI+8, matching the same 8/0x22c cell-offset pair confirmed
   * (via tableHandle zero-writes) in the sibling constructors
   * FUN_00428550.c/FUN_0042aeb0.c. `unaff_ESI` is plain `int`, so byte
   * offsets add directly. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(unaff_ESI + 8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0x22c));
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x44c793
   * (`lea edi,[esi + 0x22c]`, esi = unaff_ESI): cell is unaff_ESI+0x22c,
   * the paired second cell offset for this same class. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(unaff_ESI + 0x22c, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

