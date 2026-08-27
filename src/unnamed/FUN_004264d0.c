/* FUN_004264d0 - 0x004264d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * WHAT IT IS.  CAtlArray<T>::RemoveAt for a 4-byte element: bounds-check
 * `index + count` against m_nSize and throw E_INVALIDARG, run the element
 * destructor `count` times, memmove the tail down, then shrink m_nSize.  It
 * is AtlArray_RemoveAt (0x415470) plus the destructor loop -- same layout,
 * same 4-byte stride, same E_INVALIDARG.
 *
 * DROPPED REGISTERS RECOVERED (2026-08-27).  A previous pass stopped here
 * saying only ESI was determined, because EDI's value was "live from earlier
 * still".  It does not need to be: the sole call site is inside
 * FUN_004258e0, whose OWN prologue sets it -- `mov edi,eax` at 0x4258ef,
 * where eax is that function's regEax parameter, and nothing rewrites edi
 * before the call.  So EBX is `regEax + 0x67ec60`.  ECX is likewise not
 * out of reach: its `cmp eax,-1` is the test on FUN_004259d0's return value
 * two lines up, which the C already names iVar1 -- the same value the
 * `if (iVar1 != -1)` guard around the call tests.  ESI is the literal 1.
 *
 * The frame check that ties the call site to the C: `mov ebp,[esp+0x88]`
 * at 0x4258e7, with one push pending against a 0x80 frame, is E+4 =
 * param_1, which is what FUN_004259d0 is called with on the line above.
 */
#include "ghidra_types.h"


void __fastcall FUN_004264d0(int param_1,int *regEbx,int regEsi)

{
  int iVar1;
  int iVar2;
  int *unaff_EBX = regEbx;
  int unaff_ESI = regEsi;
  
  if ((uint)unaff_EBX[1] < (uint)(param_1 + unaff_ESI)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (unaff_EBX[1] - param_1) - unaff_ESI;
  for (iVar2 = unaff_ESI; iVar2 != 0; iVar2 = iVar2 + -1) {
    FUN_00405320();
  }
  if (iVar1 != 0) {
    _memmove((void *)(*unaff_EBX + param_1 * 4),(void *)(*unaff_EBX + (param_1 + unaff_ESI) * 4),
             iVar1 * 4);
  }
  unaff_EBX[1] = unaff_EBX[1] - unaff_ESI;
  return;
}

