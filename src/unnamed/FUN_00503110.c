/* FUN_00503110 - 0x00503110 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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


void FUN_00503110(int regEax,int regEdi)

{
  int in_EAX = regEax;
  int unaff_EDI = regEdi;
  
  for (; in_EAX != unaff_EDI; in_EAX = in_EAX + 8) {
    FUN_00415890(in_EAX);
  }
  return;
}

