/* MpegAntialias - 0x0051c6a0 in the original binary.
 *
 * Layer III alias-reduction butterflies at each subband boundary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Reached through MpegAntialiasThunk (0x518100) from
 * DecodeMpegLayerIIIGranule once per channel with (samples, number of
 * subbands). Each iteration does the eight ISO 11172-3 butterflies
 * (xr[-1-i], xr[i]) with the cs and ca pairs at 0xf25ac0..0xf25afc,
 * advancing 18 samples (0x48 bytes) per subband boundary; those cs/ca
 * values are produced by InitMpegLayerIIITables from the ISO ci
 * coefficients.
 *
 * SIGNATURE CORRECTED (2026-08-25).  Same hand-written-asm shape as
 * MpegSynthWindow8HalfInterleaved and its two siblings: entry `push ebp; lea ebp,[esp+8];
 * pushal`, exit `popal; pop ebp; ret`, ret 0 with the caller cleaning up.
 * Every general register is saved and restored, so ECX, EDX and EAX are all
 * written before any read -- phantoms, not arguments -- and Ghidra's
 * `return CONCAT44(param_2,in_EAX)` is popal restoring EDX:EAX, not a value.
 * The real arguments are the 2 stack slot(s) its caller already passes.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl MpegAntialias(int param_3,int param_4)
{
  float fVar1;
  
  for (; param_4 != 0; param_4 = param_4 + -1) {
    fVar1 = *(float *)(param_3 + 0x44);
    *(float *)(param_3 + 0x44) = fVar1 * _DAT_00f25ac0 - *(float *)(param_3 + 0x48) * _DAT_00f25ac4;
    *(float *)(param_3 + 0x48) = fVar1 * _DAT_00f25ac4 + *(float *)(param_3 + 0x48) * _DAT_00f25ac0;
    fVar1 = *(float *)(param_3 + 0x40);
    *(float *)(param_3 + 0x40) = fVar1 * _DAT_00f25ac8 - *(float *)(param_3 + 0x4c) * _DAT_00f25acc;
    *(float *)(param_3 + 0x4c) = fVar1 * _DAT_00f25acc + *(float *)(param_3 + 0x4c) * _DAT_00f25ac8;
    fVar1 = *(float *)(param_3 + 0x3c);
    *(float *)(param_3 + 0x3c) = fVar1 * _DAT_00f25ad0 - *(float *)(param_3 + 0x50) * _DAT_00f25ad4;
    *(float *)(param_3 + 0x50) = fVar1 * _DAT_00f25ad4 + *(float *)(param_3 + 0x50) * _DAT_00f25ad0;
    fVar1 = *(float *)(param_3 + 0x38);
    *(float *)(param_3 + 0x38) = fVar1 * _DAT_00f25ad8 - *(float *)(param_3 + 0x54) * _DAT_00f25adc;
    *(float *)(param_3 + 0x54) = fVar1 * _DAT_00f25adc + *(float *)(param_3 + 0x54) * _DAT_00f25ad8;
    fVar1 = *(float *)(param_3 + 0x34);
    *(float *)(param_3 + 0x34) = fVar1 * _DAT_00f25ae0 - *(float *)(param_3 + 0x58) * _DAT_00f25ae4;
    *(float *)(param_3 + 0x58) = fVar1 * _DAT_00f25ae4 + *(float *)(param_3 + 0x58) * _DAT_00f25ae0;
    fVar1 = *(float *)(param_3 + 0x30);
    *(float *)(param_3 + 0x30) = fVar1 * _DAT_00f25ae8 - *(float *)(param_3 + 0x5c) * _DAT_00f25aec;
    *(float *)(param_3 + 0x5c) = fVar1 * _DAT_00f25aec + *(float *)(param_3 + 0x5c) * _DAT_00f25ae8;
    fVar1 = *(float *)(param_3 + 0x2c);
    *(float *)(param_3 + 0x2c) = fVar1 * _DAT_00f25af0 - *(float *)(param_3 + 0x60) * _DAT_00f25af4;
    *(float *)(param_3 + 0x60) = fVar1 * _DAT_00f25af4 + *(float *)(param_3 + 0x60) * _DAT_00f25af0;
    fVar1 = *(float *)(param_3 + 0x28);
    *(float *)(param_3 + 0x28) = fVar1 * _DAT_00f25af8 - *(float *)(param_3 + 100) * _DAT_00f25afc;
    *(float *)(param_3 + 100) = fVar1 * _DAT_00f25afc + *(float *)(param_3 + 100) * _DAT_00f25af8;
    param_3 = param_3 + 0x48;
  }
  return;
}

