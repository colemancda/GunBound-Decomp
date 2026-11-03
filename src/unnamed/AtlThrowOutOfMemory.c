/* AtlThrowOutOfMemory - 0x004058b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): every caller is an allocation-failure arm
 * (CString_Fork, CString_Reallocate, CString_CloneData, none returns after
 * the call) and the body throws 0x8007000e, E_OUTOFMEMORY, the code ATL's
 * AtlThrowOutOfMemory raises through AtlThrowImpl. Kept cdecl and void as
 * ported.
 */
#include "ghidra_types.h"


void AtlThrowOutOfMemory(void)

{
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x8007000e);
}

