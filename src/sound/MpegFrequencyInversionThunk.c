/* MpegFrequencyInversionThunk - 0x005180b0 in the original binary.
 *
 * Thin stack-arg wrapper that calls MpegFrequencyInversion.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x5180b0: reloads its two stack arguments and does call
 * 0x51c568; it is not a bare jmp, and it is ordinary cdecl (ret). Called
 * from the hybrid synthesis stage at 0x514cc0. The target at 0x51c568 is
 * the pushal/popal ret-0 variant.
 */
#include "ghidra_types.h"


void MpegFrequencyInversionThunk(undefined4 param_1,undefined4 param_2)

{
  MpegFrequencyInversion(param_1,param_2);
  return;
}

