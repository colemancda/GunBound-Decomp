/* DecodeMpegFrameDispatch - 0x0050f890 in the original binary.
 *
 * Call the current per-layer frame decoder through the pointer at
 * 0x5637d0.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * DecodeMpegAudioFrame stores PTR_FUN_005637d0 = table_0x563aec[layer bits
 * & 3] early in every call, before it branches to the Layer I / III
 * setups. The table (read from .data) is {0x50f8b0, 0x514fa0, 0x50f8b0,
 * 0x5133c0}: slot 2 is DecodeMpegLayerIISamples, slot 1 is the Layer III
 * trampoline (calls through 0x563da8, which SetupMpegLayerIIIDecoder
 * points at DecodeMpegLayerIIISamples), slot 3 is the uncarved Layer I
 * decoder at 0x5133c0. The body (0x50f890) pushes its two stack args and
 * does call [0x5637d0]; DecodeSoundBufferChunk calls it per frame and uses
 * the 64-bit result.
 */
#include "ghidra_types.h"


undefined8 DecodeMpegFrameDispatch(undefined4 param_1,undefined4 param_2)

{
  (*(code *)PTR_FUN_005637d0)(param_1,param_2);
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

