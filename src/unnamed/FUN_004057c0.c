/* FUN_004057c0 - 0x004057c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004057c0(int *param_1)

{
  int iVar1;
  int in_EAX;
  
  iVar1 = *param_1;
  if (in_EAX < *(int *)(iVar1 + -0xc)) {
    in_EAX = *(int *)(iVar1 + -0xc);
  }
  if (1 < *(int *)(iVar1 + -4)) {
    FUN_00405810(param_1);
    return;
  }
  if (*(int *)(iVar1 + -8) < in_EAX) {
    FUN_00405890();
  }
  return;
}

