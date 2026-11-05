/* TransformCoordToScratch - 0x004f4810 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004f4810 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Leaf maths
 * routine; the operand shapes are corroborated by its only caller
 * FUN_004f3540. That caller loops 8 times over the 0x10-byte points at
 * (object + 0xc4)->+0x258, transforms each by the 0x40-byte matrix at its
 * own param_2 + 0xe0, copies the four-float result into a table at param_2
 * + 0x210, and then builds further tables from the matrix. The arithmetic
 * is x' = (x*m0 + y*m4 + z*m8 + m12) * w', and so on, with w' = 1 / (x*m3
 * + y*m7 + z*m11 + m15): the D3DXVec3TransformCoord identity with the
 * reciprocal w also left in the fourth output slot. The result is returned
 * as a pointer to the fixed scratch block DAT_005a9550, the 'ToScratch'
 * convention of MultiplyMatrix4x4ToScratch and
 * MultiplyQuaternionsToScratch. LIKELY (a single caller supplies the shape
 * evidence).
 *
 * EAX RECOVERED (2026-08-25): `lea ebx,[edx+0xe0]` at FUN_004f3540's entry,
 * where EDX is that __fastcall caller's param_2 -- pinned by the sibling
 * `lea edi,[edx+0x210]`, which its source spells `param_2 + 0x210`.  EBX is
 * never rewritten across the loop (0x4f359a still reads through it), so both
 * the ECX slot and EAX are known at the single call site.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __fastcall TransformCoordToScratch(float *param_1,float *regEax)

{
  
  _DAT_005a955c =
       _DAT_00557fb0 /
       (regEax[7] * param_1[1] + regEax[3] * *param_1 + regEax[0xb] * param_1[2] + regEax[0xf]);
  _DAT_005a9550 =
       (*regEax * *param_1 + regEax[4] * param_1[1] + regEax[8] * param_1[2] + regEax[0xc]) *
       _DAT_005a955c;
  _DAT_005a9554 =
       _DAT_005a955c *
       (regEax[5] * param_1[1] + regEax[1] * *param_1 + regEax[9] * param_1[2] + regEax[0xd]);
  _DAT_005a9558 =
       (regEax[6] * param_1[1] + regEax[2] * *param_1 + regEax[10] * param_1[2] + regEax[0xe]) *
       _DAT_005a955c;
  return &DAT_005a9550;
}

