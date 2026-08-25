/* FUN_004f4810 - 0x004f4810 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25): `lea ebx,[edx+0xe0]` at FUN_004f3540's entry,
 * where EDX is that __fastcall caller's param_2 -- pinned by the sibling
 * `lea edi,[edx+0x210]`, which its source spells `param_2 + 0x210`.  EBX is
 * never rewritten across the loop (0x4f359a still reads through it), so both
 * the ECX slot and EAX are known at the single call site.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * __fastcall FUN_004f4810(float *param_1,float *regEax)

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

