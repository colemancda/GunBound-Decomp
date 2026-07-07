/* FUN_00404d60 - 0x00404d60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00404d60(int param_1,int *param_2)

{
  int iVar1;
  int in_EAX;
  
  *(undefined4 *)(in_EAX + 0x110) = *(undefined4 *)(param_1 + 0x110);
  iVar1 = *(int *)(param_1 + 0x110);
  if (*(int *)(iVar1 + 0x108) == param_1) {
    *(int *)(iVar1 + 0x108) = in_EAX;
  }
  else {
    *(int *)(iVar1 + 0x10c) = in_EAX;
  }
  *(undefined4 *)(in_EAX + 0x10c) = *(undefined4 *)(param_1 + 0x10c);
  *(undefined4 *)(in_EAX + 0x108) = *(undefined4 *)(param_1 + 0x108);
  *(undefined4 *)(in_EAX + 0x104) = *(undefined4 *)(param_1 + 0x104);
  *(int *)(*(int *)(in_EAX + 0x10c) + 0x110) = in_EAX;
  *(int *)(*(int *)(in_EAX + 0x108) + 0x110) = in_EAX;
  if (*param_2 == param_1) {
    *param_2 = in_EAX;
  }
  return;
}

