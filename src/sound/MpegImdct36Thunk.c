/* MpegImdct36Thunk - 0x0051c680 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051c680.)
 *
 * Evidence for the name (all from outside the body):
 * Verified in the binary: 0x51c680 is mov eax,[esp+4]; push eax; call
 * 0x51b030; pop ecx; ret, a cdecl one-argument pass-through to MpegImdct36.
 * Its only caller is MpegImdctViaKernels (0x517d40), which passes the
 * current 18-float block pointer. Naming follows the MpegAntialiasThunk and
 * MpegFrequencyInversionThunk wrappers of the same hybrid-synthesis chain.
 */
#include "ghidra_types.h"


void MpegImdct36Thunk(undefined4 param_1)

{
  MpegImdct36(param_1);
  return;
}

