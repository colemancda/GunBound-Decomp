/* ApplyMpegMidSideStereo - 0x00518120 in the original binary.
 *
 * Mid/side stereo: replace (m, s) by (m + s, m - s) across the two channel
 * arrays.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Called from DecodeMpegLayerIIIGranule under DAT_005ae348, which
 * DecodeMpegLayerIIISamples derives as mode_extension >> 1 (the ISO
 * mid/side bit), before the intensity-stereo and antialias calls.
 * Arguments are the granule base inside 0xf25f00 and a line count; the
 * granule code itself steps channels by 0x480 floats, the offset this body
 * uses for the second array.
 */
#include "ghidra_types.h"


void ApplyMpegMidSideStereo(float *param_1,int param_2)

{
  float fVar1;
  
  if (0 < param_2) {
    do {
      param_2 = param_2 + -1;
      fVar1 = *param_1;
      *param_1 = param_1[0x480] + *param_1;
      param_1[0x480] = fVar1 - param_1[0x480];
      param_1 = param_1 + 1;
    } while (param_2 != 0);
  }
  return;
}

