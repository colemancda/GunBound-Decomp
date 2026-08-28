/* Vector_DestroyRange_8 - 0x00503110 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the destroy-[first,last) member of the 8-byte
 * {CStringA, CStringA} vector family, joining the Vector_*_34 / _1e
 * sets named 2026-08-25/28; suffix 8 = the element stride, per the
 * family convention. In the VC7.1 <vector> this tree's Vector_* shapes
 * come from, this is the member the library itself calls
 * _Destroy(_First, _Last); DestroyRange spells that out the way
 * UninitCopy spells _Ucopy. The destroy-everything sibling (sweep +
 * free + null the base/end/cap trio, the library's _Tidy) is
 * Vector_Tidy_8 at 0x502a90.
 *
 * (The note below predates the renames of 2026-08-28: FUN_00415890 is
 * now CStringPair_Destroy, FUN_00503130 is Vector_InsertN_8.)
 *
 * DROPPED-REG FIX (2026-08-28): destroys the 8-byte {CStringA,CStringA}
 * elements in [regEax, regEdi) via FUN_00415890 - the destroy half of
 * the 8-byte vector family whose insert is FUN_00503130. Both inputs
 * are read before written (`mov esi,eax` at 0x503111, `cmp esi,edi` at
 * 0x503113).
 *
 * THREE binary call sites but ONE source site, and the gap is fully
 * explained: 0x5032a1 and 0x50332d-0x503340 are C++ exception-unwind
 * funclets inside FUN_00503130's body, each referenced only from the EH
 * unwind map (raw file offsets 0x1583dc / 0x1583ec hold their
 * addresses) - compiler-regenerated cleanup with no source statement,
 * the same class as FUN_004f1770's funclets. The one real site is the
 * grow path's destroy-the-old-buffer at 0x50326f: EAX = the old begin
 * (the C's iVar3 = *(param_1+4), tested by the guard above the call)
 * and EDI = the old end (`mov edi,[esi+8]` at 0x50326c).
 */
#include "ghidra_types.h"


void Vector_DestroyRange_8(int regEax,int regEdi)

{
  int in_EAX = regEax;
  int unaff_EDI = regEdi;
  
  for (; in_EAX != unaff_EDI; in_EAX = in_EAX + 8) {
    CStringPair_Destroy(in_EAX);
  }
  return;
}

