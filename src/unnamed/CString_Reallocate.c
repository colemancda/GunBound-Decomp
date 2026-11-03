/* CString_Reallocate - 0x00405890 in the original binary.
 * (Historical notes below: FUN_004057c0 is now CString_PrepareWrite2.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): sole caller is the unshared grow arm of
 * CString_PrepareWrite2 (0x405801), ESI = the CString, EDI = the new
 * capacity. It calls the header manager's Reallocate (vtable +8), throws
 * via AtlThrowOutOfMemory on NULL and stores the new data pointer, which
 * is ATL7 CSimpleStringT::Reallocate(nLength).
 *
 * FIX (2026-11-03): ESI and EDI were dropped.  One binary caller, 0x405801
 * in FUN_004057c0: ESI = the CString* (FUN_004057c0's `mov esi,ecx`,
 * 0x4057c1, still live) and EDI = the new capacity.  Reallocate
 * (`push 1 / push edi / push hdr / call [edx+8]`, 0x40589a-0x40589e) the
 * buffer through its own manager; a NULL result jumps to 0x4058b0 (throws),
 * otherwise the text pointer (result + 0x10) is stored into the CString
 * (0x4058aa-0x4058ad).  Manager vtable calls use the shims' ABI (no
 * `this`).  Declared cdecl: ESI then EDI as parameters.
 */
#include "ghidra_types.h"


void CString_Reallocate(int *regEsi,int regEdi)

{
  int iVar1;

  iVar1 = (**(code **)(**(int **)(*regEsi + -0x10) + 8))(*regEsi + -0x10,regEdi,1);
  if (iVar1 == 0) {
    FUN_004058b0();
    return;
  }
  *regEsi = iVar1 + 0x10;
  return;
}
