/* AccumulateFloatArray - 0x00518080 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_00518080.)
 *
 * Evidence for the name (all from outside the body):
 * Verified in the binary: cdecl (dst, src, n); for n > 0 it does
 * dst[i] = src[i] + dst[i] on 4-byte floats (fld [src+i]; fadd [dst+i]; fstp
 * [dst+i]). Its single caller, SynthesizeMpegLayerIIIMixDown, passes the
 * channel 0 spectrum row (0xf25f00 + granule * 0x240 words) as dst and the
 * channel 1 row (0xf25f00 + 0x480 + granule * 0x240) as src with n = the
 * larger of the two channels' band limits, which is the "spectra are summed"
 * step of the mix-down path described in that function's header. The name
 * stays generic (an element-wise float accumulate) because nothing outside the
 * function shows it is spectrum specific; it has one caller.
 */
#include "ghidra_types.h"


void AccumulateFloatArray(float *param_1,int param_2,int param_3)

{
  float *pfVar1;
  
  if (0 < param_3) {
    pfVar1 = param_1;
    do {
      param_3 = param_3 + -1;
      *pfVar1 = *(float *)((param_2 - (int)param_1) + (int)pfVar1) + *pfVar1;
      pfVar1 = pfVar1 + 1;
    } while (param_3 != 0);
  }
  return;
}

