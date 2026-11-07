/* DecodeMpegLayerIIIDispatch - 0x00514fa0 in the original binary.
 *
 * Frame-decoder trampoline for Layer III streams: calls whichever Layer III
 * sample decoder SetupMpegLayerIIIDecoder parked in table word 0 of the
 * 0x563da8 table, passing its two stack arguments through and returning its
 * EDX:EAX result untouched.
 *
 * Evidence for the name (all from outside the body):
 * Slot 1 of the frame-decoder table at 0x563aec (raw words 50f8b0 514fa0
 * 50f8b0 5133c0), which DecodeMpegAudioFrame indexes with the header layer
 * bits, so it is the Layer III entry of DecodeMpegFrameDispatch. The body is
 * `mov eax,[esp+8]; mov ecx,[esp+4]; push eax; push ecx; call [0x563da8];
 * add esp,8; ret`: ordinary cdecl, no register argument. Word 0 of the
 * table holds DecodeMpegLayerIIISamples (0x514fc0, its static
 * initial value) for MPEG-1 and DecodeMpegLayerIIISamplesLSF (0x5159d0)
 * otherwise (SetupMpegLayerIIIDecoder, last statements).
 */
#include "ghidra_types.h"


undefined8 DecodeMpegLayerIIIDispatch(undefined4 param_1,undefined4 param_2)

{
  return (*(undefined8 (*)(undefined4,undefined4))PTR_FUN_00563da8[0])(param_1,param_2);
}
