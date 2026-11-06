/* MpegSynthWindow8HalfThunk - 0x0051afb0 in the original binary.
 *
 * Stack-argument pass-through that calls MpegSynthWindow8Half.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x51afb0: reloads its three stack arguments, pushes them
 * again and does call 0x51f184, then add esp,0xc and ret; it is ordinary
 * cdecl and not a bare jmp. Called from the single-output drivers
 * 0x5171c0, 0x5172d0, 0x517330 and 0x517390, which pass the ring buffer
 * base 0x5af144, the ring offset and the output pointer. The target is named MpegSynthWindow8Half from its
 * own callers (the window geometry the drivers impose).
 */
#include "ghidra_types.h"


void MpegSynthWindow8HalfThunk(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  MpegSynthWindow8Half(param_1,param_2,param_3);
  return;
}

