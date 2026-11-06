/* MpegSynthWindow16QuarterThunk - 0x0051af30 in the original binary.
 *
 * Stack-argument pass-through that calls MpegSynthWindow16Quarter.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x51af30: reloads its three stack arguments, pushes them
 * again and does call 0x51e3c4, then add esp,0xc and ret; it is ordinary
 * cdecl and not a bare jmp. Called from the single-output drivers
 * 0x516d50, 0x516e60, 0x516ec0 and 0x516f20, which pass the ring buffer
 * base 0x5af144, the ring offset and the output pointer. The target is named MpegSynthWindow16Quarter from
 * its own callers (the window geometry the drivers impose).
 */
#include "ghidra_types.h"


void MpegSynthWindow16QuarterThunk(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  MpegSynthWindow16Quarter(param_1,param_2,param_3);
  return;
}

