/* FUN_004068d0 - 0x004068d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004068d0(void)

{
  int in_EAX;
  int iVar1;
  
  iVar1 = *(int *)(in_EAX + 0xc) + *(int *)(in_EAX + 8);
  *(int *)(in_EAX + 0xc) = iVar1;
  if ((6 < iVar1) && (*(int *)(in_EAX + 8) != 0)) {
    *(undefined4 *)(in_EAX + 0xc) = 7;
    *(undefined4 *)(in_EAX + 8) = 0;
    *(undefined1 *)(in_EAX + 4) = 1;
  }
  if ((*(int *)(in_EAX + 0xc) < 1) && (*(int *)(in_EAX + 8) != 0)) {
    *(undefined4 *)(in_EAX + 8) = 0;
    *(undefined4 *)(in_EAX + 0xc) = 0;
  }
  iVar1 = *(int *)(in_EAX + 0x18) + *(int *)(in_EAX + 0x14);
  *(int *)(in_EAX + 0x18) = iVar1;
  if ((0 < iVar1) && (*(int *)(in_EAX + 0x14) != 0)) {
    *(undefined4 *)(in_EAX + 0x18) = 1;
    *(undefined4 *)(in_EAX + 0x14) = 0;
    *(undefined1 *)(in_EAX + 0x10) = 1;
  }
  if ((*(int *)(in_EAX + 0x18) < 1) && (*(int *)(in_EAX + 0x14) != 0)) {
    *(undefined4 *)(in_EAX + 0x14) = 0;
    *(undefined4 *)(in_EAX + 0x18) = 0;
  }
  iVar1 = *(int *)(in_EAX + 0x24) + *(int *)(in_EAX + 0x20);
  *(int *)(in_EAX + 0x24) = iVar1;
  if ((2 < iVar1) && (*(int *)(in_EAX + 0x20) != 0)) {
    *(undefined4 *)(in_EAX + 0x24) = 3;
    *(undefined4 *)(in_EAX + 0x20) = 0;
    *(undefined1 *)(in_EAX + 0x1c) = 1;
  }
  if ((*(int *)(in_EAX + 0x24) < 1) && (*(int *)(in_EAX + 0x20) != 0)) {
    *(undefined4 *)(in_EAX + 0x20) = 0;
    *(undefined4 *)(in_EAX + 0x24) = 0;
  }
  iVar1 = *(int *)(in_EAX + 0x30) + *(int *)(in_EAX + 0x2c);
  *(int *)(in_EAX + 0x30) = iVar1;
  if (0 < iVar1) {
    *(undefined4 *)(in_EAX + 0x2c) = 0;
    *(undefined4 *)(in_EAX + 0x30) = 1;
  }
  if (*(int *)(in_EAX + 0x30) < 1) {
    *(undefined4 *)(in_EAX + 0x2c) = 0;
    *(undefined4 *)(in_EAX + 0x30) = 0;
  }
  return;
}

