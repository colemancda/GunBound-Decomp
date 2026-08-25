/* FUN_00502920 - 0x00502920 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25) from the single site in FUN_00501770, under the
 * -0x4990 frame constant that function's earlier recoveries established and
 * that four independent slots agree on: `lea eax,[esp+0x3c]` with no push
 * pending = &local_4954.
 */
#include "ghidra_types.h"


void FUN_00502920(undefined4 param_1,int regEax)

{
  int iVar1;
  
  iVar1 = *(int *)(regEax + 4);
  if ((iVar1 != 0) &&
     ((uint)((*(int *)(regEax + 8) - iVar1) / 0x1e) <
      (uint)((*(int *)(regEax + 0xc) - iVar1) / 0x1e))) {
    iVar1 = *(int *)(regEax + 8);
    FUN_00504270(param_1);
    *(int *)(regEax + 8) = iVar1 + 0x1e;
    return;
  }
  FUN_00502b00(&param_1,*(undefined4 *)(regEax + 8),param_1);
  return;
}

