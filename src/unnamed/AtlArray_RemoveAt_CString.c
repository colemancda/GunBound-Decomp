/* AtlArray_RemoveAt_CString - 0x004264d0 in the original binary.
 *
 * Named below; still a raw/near-verbatim port of Ghidra's decompiler
 * output rather than a hand-verified reconstruction.  See src/README.md's
 * "Raw/verbatim ports" section for what that status means.
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
 *
 * ATL7 CAtlArray<CStringA>::RemoveAt(iElement, nElements) over a 4-byte
 * element: bounds-check iElement + nElements against m_nSize and
 * AtlThrow(E_INVALIDARG), destroy each removed element, memmove the tail
 * down, shrink m_nSize.  param_1 (ECX) is iElement, regEsi is nElements,
 * regEbx is `this`.
 *
 * NAMED 2026-08-27.  The suffix is load-bearing: 0x415470
 * (AtlArray_RemoveAt) is the SAME template member for a POD dword element,
 * and both are 4-byte stride, so a numeric stride suffix cannot separate
 * them the way CArray_Grow_1750 separates its siblings.  Element type is
 * the only distinguishing axis, and it is settled from outside the body.
 *
 * THE ELEMENT IS AN ATL CStringA, from two independent directions.  (1) The
 * array is g_clientContext + 0x67ec60, and its Add is 0x415bc0
 * (AppendWordFilterEntry) - `lea ecx,[edi+0x67ec60]; call 0x415bc0` at
 * 0x425887 - whose element constructor is ConstructStringFromText
 * (0x405510).  That writes `*slot = DAT_005b1444->slot3() + 0x10`;
 * DAT_005b1444 is the ATL::CAtlStringMgr vtable pointer (include/globals.h,
 * src/globals.c), IAtlStringMgr slot 3 is GetNilString returning a
 * CStringData*, and +0x10 is its character data.  So an element is one
 * CStringT<char>::m_pszData with a CStringData header at -0x10.  (2) The
 * per-element destructor this function calls, FUN_00405320, consumes
 * exactly that: InterlockedDecrement of [p-4] (CStringData::nRefs) and, at
 * zero, a virtual call through [p-0x10] slot 1 (IAtlStringMgr::Free) -
 * CStringData::Release, i.e. ~CStringA.
 *
 * ATL AND NOT MFC, per src/cxx/AtlArray.h's rule: the guard throws
 * E_INVALIDARG (0x80070057 pushed at 0x4264e2) where MFC's CArray asserts,
 * the element is CAtlStringMgr-backed, and the grow half of this very
 * family is already AtlArray_GrowBuffer.  The body constants are ATL7
 * atlcoll.h in order - check, CallDestructors, memmove (0x525790 =
 * _memmove), `m_nSize -= nElements`.
 *
 * NOT ROLE-NAMED, DELIBERATELY.  Binary-wide there is exactly one call site,
 * 0x42590b inside FUN_004258e0, and that array is the client-side chat mute
 * list: ParseChatSlashCommand dispatches "mute" (0x5535a4) to FUN_00425840
 * (add, message 0x1fe), "loud" (0x553588) to FUN_004258e0 (remove, message
 * 0x1ff - this call), "mutelist" (0x553598) to an inline enumeration via
 * 0x415450, and "loudall" (0x553580) to FUN_00425960 (clear, message
 * 0x200).  MuteList_RemoveAt was still rejected: the sibling members of this
 * family are shared instantiations - 0x415bc0 is called on BOTH
 * g_wordFilterArrayHeader and this array, and 0x415450 (checked
 * operator[]) on three different arrays - so an array-specific name here
 * would repeat the misattribution already frozen into
 * "AppendWordFilterEntry", which is not word-filter-specific.  The
 * reference server has no mute/ignore opcode; the list never leaves the
 * client, so there is no server-side evidence to cite either way.
 *
 * OPEN BUG, NOT A NAMING MATTER.  The destructor loop calls
 * `FUN_00405320()` with no argument, but the original is `mov ecx,edi; call
 * 0x405320` at 0x426510 with edi = m_pData + iElement*4, stepping 4 per
 * iteration - the element pointer is dropped, so the port releases whatever
 * is in ECX.  It compiles only because functions.h declares FUN_00405320
 * K&R-empty.  Live on the /loud path.  The `unaff_EBX`/`unaff_ESI` locals
 * are dead aliases of the parameters and can go with it. */
#include "ghidra_types.h"


void __fastcall AtlArray_RemoveAt_CString(int param_1,int *regEbx,int regEsi)

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

