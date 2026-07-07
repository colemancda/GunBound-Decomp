/* FUN_0044c630 - 0x0044c630 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_0044c630(int param_1)

{
  undefined4 uVar1;
  int in_EAX;
  int iVar2;
  
  uVar1 = *(undefined4 *)(param_1 + 4);
  FUN_0044c7b0();
  iVar2 = *(int *)(in_EAX + 4);
  if (iVar2 == 0) {
    return uVar1;
  }
  do {
    FUN_0044c740();
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return uVar1;
}

