/* FUN_00404c40 - 0x00404c40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00404c40(int *param_1)

{
  int iVar1;
  int iVar2;
  int in_EAX;
  
  if (in_EAX == 0) {
    return;
  }
  iVar1 = *(int *)(in_EAX + 0x10c);
  *(undefined4 *)(in_EAX + 0x10c) = *(undefined4 *)(iVar1 + 0x108);
  if (*(int *)(iVar1 + 0x108) != param_1[5]) {
    *(int *)(*(int *)(iVar1 + 0x108) + 0x110) = in_EAX;
  }
  *(undefined4 *)(iVar1 + 0x110) = *(undefined4 *)(in_EAX + 0x110);
  iVar2 = *(int *)(in_EAX + 0x110);
  if (iVar2 == param_1[5]) {
    *param_1 = iVar1;
    *(int *)(iVar1 + 0x108) = in_EAX;
    *(int *)(in_EAX + 0x110) = iVar1;
    return;
  }
  if (in_EAX == *(int *)(iVar2 + 0x108)) {
    *(int *)(iVar2 + 0x108) = iVar1;
    *(int *)(iVar1 + 0x108) = in_EAX;
    *(int *)(in_EAX + 0x110) = iVar1;
    return;
  }
  *(int *)(iVar2 + 0x10c) = iVar1;
  *(int *)(iVar1 + 0x108) = in_EAX;
  *(int *)(in_EAX + 0x110) = iVar1;
  return;
}

