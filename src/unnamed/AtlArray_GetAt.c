/* AtlArray_GetAt - 0x00415450 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX RECOVERED (2026-08-28): this is a bounds-checked element-address
 * accessor for the same two-field container that the next function,
 * AtlArray_RemoveAt at 0x415470, mutates - element base pointer at +0x00,
 * element count at +0x04, 4-byte stride. ECX is the container (already
 * param_1) and EAX is the index; it returns base + index*4 and throws
 * E_INVALIDARG 0x80070057 through ThrowCxxException when index is not below
 * the count.
 *
 * The whole body is seven instructions at 0x415450-0x415464 with no prologue
 * saves, no sub esp, no __chkstk and no SEH, and it reads no [esp+N] at all,
 * so it takes zero stack arguments; the bare ret is consistent with that.
 * The single push at 0x415455 is the argument to the noreturn throw helper,
 * not a frame adjustment. EDX, EBX, ESI, EDI and EBP are never touched, so
 * the register columns callsite_regs.py prints for them are caller loop
 * temporaries, not inputs.
 *
 * Two independent confirmations of the container layout. First,
 * AtlArray_RemoveAt drives the identical object through EDI - mov
 * eax,[edi+4] for the count, mov ecx,[edi] for the base, lea with an index
 * scaled by 4, and sub [edi+4],ebx to shrink it. Second, the callers read
 * the same count field at absolute addresses exactly four bytes above the
 * pointer they put in ECX: WriteReplayEventRecord loads its loop bound from
 * [ecx+0x6a76f8] at 0x4112b4 while passing ecx+0x6a76f4 at 0x4112d0, and
 * TickJewelFrame loads the divisor from [ebx+0x1e44] at 0x47a8a9 while
 * passing ebx+0x1e40 at 0x47a8bb.
 *
 * This was a full re-slot rather than an append. The prototype in
 * include/functions.h had an empty parameter list, so every one of the four
 * ported call sites was written as an argless call and passed neither the
 * container nor the index; appending would have landed the recovered index
 * in param_1. Binary and source site counts agree at four, and no file under
 * src/cxx declares or calls this function. Sites paired by witness: 0x4112d8
 * by the AtlArray_RemoveAt call in the same block that already spells the
 * container as g_clientContext + 0x6a76f4 and the index as local_d78;
 * 0x421e5e by the already-ported loop bound at DAT_0067ec64 + param_1, four
 * bytes above the container DAT_0067ec60 + param_1, with the index in the
 * uVar10 that the surrounding code masks with 0x80000003; and 0x47a8c7 plus
 * 0x47a8e0 by param_1[0x791], the count that guards the very if/else the two
 * calls sit inside, with the index being the rand() remainder computed once
 * at 0x47a8b9 and held in ESI across both calls.
 *
 * NAMED (2026-08-28): ATL7's CAtlArray<E>::GetAt / operator[] out of
 * VC7.1's atlcoll.h, whose whole body is
 * `if (iElement >= m_nElements) AtlThrow(E_INVALIDARG); return
 * m_pData[iElement];` - the seven instructions here, with the 0x80070057
 * this pushes being that E_INVALIDARG. Both members share one body and
 * the linker folds them, so which of the two names the source wrote
 * cannot be recovered; GetAt is the spellable one.
 *
 * ATL and not MFC, decided by the documented test rather than by feel:
 * out of range this THROWS E_INVALIDARG through ThrowCxxException, where
 * MFC's CArray asserts. The same call is what makes AtlArray_RemoveAt
 * (0x415470), which mutates this identical two-field object, an
 * AtlArray_ and not a CArray_, and the array's growth half is already
 * AtlArray_GrowBuffer - naming the accessor CArray_* would split a
 * matched set across two prefixes.
 *
 * No stride suffix, matching its neighbour AtlArray_RemoveAt: the
 * element is a 4-byte dword and the instantiation is shared. All four
 * call sites dereference the returned pointer immediately - *puVar7 into
 * sprintf's "%15s" in ParseChatSlashCommand, *piVar14 into a
 * FUN_0041c190 lookup in WriteReplayEventRecord, and both TickJewelFrame
 * sites reading it as a char* they strlen and hand to
 * AppendBroadcastString - which is what fixes the return value as `E&`,
 * the address of the element, rather than the element or a count.
 */
#include "ghidra_types.h"


int __fastcall AtlArray_GetAt(int *param_1,uint regEax)

{
  uint in_EAX = regEax;
  
  if ((uint)param_1[1] <= in_EAX) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  return *param_1 + in_EAX * 4;
}

