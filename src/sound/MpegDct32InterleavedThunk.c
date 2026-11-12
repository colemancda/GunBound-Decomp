/* MpegDct32InterleavedThunk - 0x0051a450 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051a450.)
 *
 * Evidence for the name (all from outside the body):
 * Verified in the binary: 0x51a450 is mov eax,[esp+8]; mov ecx,[esp+4];
 * push eax; push ecx; call 0x51d044; add esp,8; ret, a cdecl two-argument
 * pass-through to MpegDct32Interleaved. Eight tree call sites call it, all
 * in stereo-capable drivers that read a channel-interleaved float source:
 * the Stereo, FirstChannel and SecondChannel synthesis drivers of the
 * 16-bit and 8-bit full-band families (the Stereo ones twice per slot, on
 * source and source + 4).
 * Naming follows MpegSynthWindow16FullInterleavedThunk and its siblings.
 */
#include "ghidra_types.h"


void MpegDct32InterleavedThunk(undefined4 param_1,undefined4 param_2)

{
  MpegDct32Interleaved(param_1,param_2);
  return;
}

