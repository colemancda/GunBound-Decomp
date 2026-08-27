/* AtlArray_RemoveAt - 0x00415470 in the original binary.
 *
 * CAtlArray::RemoveAt(iElement, nElements) over 4-byte elements.
 *
 * NAMED 2026-08-26.  The class is settled by an already-named function on the
 * SAME array: its one call site passes g_clientContext + 0x6a76f4, and that
 * object is grown by AtlArray_GrowBuffer (0x50ed30) at
 * State11_InBattle_OnTick's 0x4c0c51 -- `mov ebx,[esi+4]; cmp ebx,[esi+8]`,
 * count at +4 against capacity at +8.  src/cxx/AtlArray.h documents that
 * layout and ATL's E_INVALIDARG throw.
 *
 * The routine is ATL7's RemoveAt with its constants intact and in order:
 * `if (iElement + nElements > m_nElements) AtlThrow(E_INVALIDARG)` -- the
 * 0x80070057 push at 0x41547b -- then memmove of the tail, then
 * `m_nElements -= nElements` at 0x4154a1.  The destructor pass ATL emits
 * between the check and the move is absent because the element is a POD
 * dword; FUN_004264d0 is the same routine WITH that loop still present,
 * calling the refcounted CString release, i.e. the non-trivial-element
 * instantiation of the same template.
 *
 * Named AtlArray_ rather than CArray_ deliberately.  MFC's CArray::RemoveAt
 * asserts where ATL throws E_INVALIDARG, and the grow half of this very array
 * is already AtlArray_GrowBuffer -- naming the removal CArray_* would split a
 * matched pair across two prefixes.  (The CArray_* names elsewhere in this
 * tree are a different, genuinely MFC-shaped container: they carry
 * CArray::SetSize's clamp(count/8, 4, 1024) growth rule, which ATL has not.)
 *
 * DROPPED REGISTERS ANALYSED, NOT APPLIED.  `ret 0` puts nothing on the stack,
 * so param_1 (ECX) and param_2 (EDX) are registers, and EBX and EDI are two
 * more that Ghidra did not declare.  At the sole call site (0x004113c1):
 *
 *   ecx  PHANTOM   -- the entry writes it (`mov ecx,[edi]`) before any read
 *   edx  = esi, where esi = [esp + 0x10]     <- a caller stack local
 *   ebx  = 1
 *   edi  = <something> + 0x6a76f4            <- context-relative
 *
 * Blocked on param_2: its value lives in a caller spill slot, and naming a
 * spill needs a stack-depth model over the CFG that does not exist here (see
 * tools/guard_dominator_base.py, which resolves 0 of 49 such cases).
 *
 * NOT filled with the two known values alone: appending them puts EDI's value
 * in param_1 and EBX's in param_2, which is what an earlier pass on this
 * branch did before it was reverted.  Three of four arguments right is not
 * three quarters correct -- it is wrong, in a shape that looks recovered.
 *
 * EBX and EDI RECOVERED, CALL RE-SLOTTED (2026-08-26).  CArray::RemoveAt over
 * 4-byte elements: EDI is the array (data at +0, count at +4), param_2 the
 * index, EBX the number of elements to remove.  It bounds-checks
 * index + count against the count and throws E_INVALIDARG, memmoves the tail
 * down, then shrinks the count -- RemoveAt's shape exactly.
 *
 * The source passed NOTHING to a two-parameter __fastcall, so this is a
 * re-slot.  ECX is a phantom (`mov ecx,[edi]` at the entry, written before any
 * read), so param_1 takes 0.  At the single site EDX is `mov esi,[esp+0x10];
 * mov edx,esi` with no pushes pending, which under WriteReplayEventRecord's
 * -0xd88 frame is local_d78 -- the very counter the line AFTER the call
 * decrements (`local_d78 = local_d78 - 1`).  EBX is the immediate 1: one
 * element.  EDI is g_clientContext + 0x6a76f4.
 */
#include "ghidra_types.h"


void __fastcall AtlArray_RemoveAt(undefined4 param_1,int param_2,int regEbx,int *regEdi)

{
  int iVar1;
  
  if ((uint)regEdi[1] < (uint)(param_2 + regEbx)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (regEdi[1] - param_2) - regEbx;
  if (iVar1 != 0) {
    _memmove((void *)(*regEdi + param_2 * 4),(void *)(*regEdi + (param_2 + regEbx) * 4),
             iVar1 * 4);
  }
  regEdi[1] = regEdi[1] - regEbx;
  return;
}

