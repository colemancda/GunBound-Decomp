/* MpegDct32Thunk - 0x0051a430 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051a430.)
 *
 * Evidence for the name (all from outside the body):
 * Verified in the binary: 0x51a430 is mov eax,[esp+8]; mov ecx,[esp+4];
 * push eax; push ecx; call 0x51c93a; add esp,8; ret, a cdecl two-argument
 * pass-through to MpegDct32. Eight tree call sites call it
 * (SynthesizeMpeg16FullMono, SynthesizeMpeg8FullMono and the
 * MpegPolyphase16Full / 16FullInterleaved / 8Full / 8FullInterleaved
 * drivers), which pass (source, ring slot).
 * Naming follows MpegSynthWindow16FullThunk and its siblings (short cdecl
 * wrappers over the raw-asm bodies).
 */
#include "ghidra_types.h"


void MpegDct32Thunk(undefined4 param_1,undefined4 param_2)

{
  MpegDct32(param_1,param_2);
  return;
}

