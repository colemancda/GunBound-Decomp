/* MpegSynthWindow16FullInterleavedThunk - 0x0051aed0 in the original binary.
 *
 * Stack-argument pass-through that calls MpegSynthWindow16FullInterleaved.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Disassembly of 0x51aed0: reloads its three stack arguments, pushes them
 * again and does call 0x51dae5, then add esp,0xc and ret; it is ordinary
 * cdecl and not a bare jmp. Called from the both-channel driver 0x516930,
 * which pass the ring buffer base 0x5af144 (or 0x5ae940 for the second
 * channel), the ring offset and the output pointer. The target is named
 * MpegSynthWindow16FullInterleaved from its own callers (the window
 * geometry the drivers impose).
 */
#include "ghidra_types.h"


void MpegSynthWindow16FullInterleavedThunk(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  MpegSynthWindow16FullInterleaved(param_1,param_2,param_3);
  return;
}

