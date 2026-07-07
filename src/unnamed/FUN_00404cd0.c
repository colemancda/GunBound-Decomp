/* FUN_00404cd0 - 0x00404cd0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00404cd0(int *param_1)

{
  int iVar1;
  int iVar2;
  int in_EAX;
  
  if (in_EAX == 0) {
    return;
  }
  iVar1 = *(int *)(in_EAX + 0x108);
  *(undefined4 *)(in_EAX + 0x108) = *(undefined4 *)(iVar1 + 0x10c);
  if (*(int *)(iVar1 + 0x10c) != param_1[5]) {
    *(int *)(*(int *)(iVar1 + 0x10c) + 0x110) = in_EAX;
  }
  *(undefined4 *)(iVar1 + 0x110) = *(undefined4 *)(in_EAX + 0x110);
  iVar2 = *(int *)(in_EAX + 0x110);
  if (iVar2 == param_1[5]) {
    *param_1 = iVar1;
    *(int *)(iVar1 + 0x10c) = in_EAX;
    *(int *)(in_EAX + 0x110) = iVar1;
    return;
  }
  if (in_EAX == *(int *)(iVar2 + 0x10c)) {
    *(int *)(iVar2 + 0x10c) = iVar1;
    *(int *)(iVar1 + 0x10c) = in_EAX;
    *(int *)(in_EAX + 0x110) = iVar1;
    return;
  }
  *(int *)(iVar2 + 0x108) = iVar1;
  *(int *)(iVar1 + 0x10c) = in_EAX;
  *(int *)(in_EAX + 0x110) = iVar1;
  return;
}

