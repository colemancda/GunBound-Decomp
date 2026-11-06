/* GetMpegOutputFormat - 0x005133a0 in the original binary.
 *
 * Copies the MPEG decoder's current output-format block, six dwords at
 * 0x00f25ee0, into the caller's buffer (cdecl, one stack argument; the
 * destination is an argument, not a return). Evidence from outside the
 * body: 0x00f25ee0 and its neighbours are written only by the decoder
 * setup paths (DecodeMpegAudioFrame, SetupMpegLayerIDecoder,
 * SetupMpegLayerIIIDecoder): +0 is the channel count (1 or 2), +4 the
 * samples per frame, +8 the sample rate shifted down for MPEG-2 LSF,
 * +0xc the sample width 0x10 or 8, +0x10 the frame function's param_2.
 * DecodeSoundBufferChunk calls it right after DecodeMpegAudioFrame has
 * parsed a first frame header (arguments 0, 0, 0), and the other binary
 * caller, the unported MusicChannel vtable slot at 0x004eed10 (call at
 * 0x004eee24), compares dword 0 with the word at 0x00588f38, which
 * InitDirectSound stores as waveFmt.nChannels. LIKELY: the field
 * meanings are read off the writers, the last dword is not identified.
 * The port's only caller declared its destination as a 1-byte Ghidra
 * stack artifact; it is now a 6-dword local.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void GetMpegOutputFormat(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00f25ee0;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}

