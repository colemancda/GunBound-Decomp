/* RewindXFSEntryStream - 0x004f0960 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): callers DecodeSoundBufferChunk and
 * SoundChannel_FillBufferChunk (sound streaming) use it to restart the open entry stream.
 * It resets the position at +0x1014 to 0 and the remaining counter at
 * +0x1010 to the entry's value, then decodes the first block through
 * DecodeXFSEntryBlock when the entry is compressed.
 */
#include "ghidra_types.h"


void __fastcall RewindXFSEntryStream(int param_1)

{
  if (*(char *)(param_1 + 0x1018) != '\0') {
    *(undefined4 *)(param_1 + 0x1010) = *(undefined4 *)(*(int *)(param_1 + 0x1004) + 0x74);
    *(undefined4 *)(param_1 + 0x1014) = 0;
    if (*(int *)(*(int *)(param_1 + 0x1004) + 0x70) == 0) {
      DecodeXFSEntryBlock();
      return;
    }
  }
  return;
}

