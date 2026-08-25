/* FUN_00502a90 - 0x00502a90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EBX RECOVERED (2026-08-25) from the single site in FUN_00501770, under the
 * -0x4990 frame constant that function's earlier recoveries established and
 * that four independent slots agree on: `lea ebx,[esp+0x38]` = &local_4958.
 */
#include "ghidra_types.h"


void FUN_00502a90(int regEbx)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(regEbx + 4);
  if (iVar2 != 0) {
    iVar1 = *(int *)(regEbx + 8);
    for (; iVar2 != iVar1; iVar2 = iVar2 + 8) {
      FUN_00415890();
    }
    _free(*(void **)(regEbx + 4));
  }
  *(undefined4 *)(regEbx + 4) = 0;
  *(undefined4 *)(regEbx + 8) = 0;
  *(undefined4 *)(regEbx + 0xc) = 0;
  return;
}

