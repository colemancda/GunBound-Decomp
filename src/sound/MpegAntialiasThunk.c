/* MpegAntialiasThunk - 0x00518100 in the original binary.
 *
 * Thin stack-arg wrapper that calls MpegAntialias.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x518100: reloads its two stack arguments and does call
 * 0x51c6a0; it is not a bare jmp, and it is ordinary cdecl (ret). The only
 * caller is DecodeMpegLayerIIIGranule. The target at 0x51c6a0 is the
 * pushal/popal ret-0 variant.
 */
#include "ghidra_types.h"


void MpegAntialiasThunk(undefined4 param_1,undefined4 param_2)

{
  MpegAntialias(param_1,param_2);
  return;
}

