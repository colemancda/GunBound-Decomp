/* MpegImdct12Thunk - 0x0051c690 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051c690.)
 *
 * Evidence for the name (all from outside the body):
 * Verified in the binary: 0x51c690 is mov eax,[esp+4]; push eax; call
 * 0x51b436; pop ecx; ret, a cdecl one-argument pass-through to MpegImdct12.
 * Its only caller is MpegImdctViaKernels (0x517d40). Counterpart of
 * MpegImdct36Thunk.
 */
#include "ghidra_types.h"


void MpegImdct12Thunk(undefined4 param_1)

{
  MpegImdct12(param_1);
  return;
}

