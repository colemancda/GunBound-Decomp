/* FUN_004068d0 - 0x004068d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004068d0(int regEax)

{
  int iVar1;
  
  iVar1 = *(int *)(regEax + 0xc) + *(int *)(regEax + 8);
  *(int *)(regEax + 0xc) = iVar1;
  if ((6 < iVar1) && (*(int *)(regEax + 8) != 0)) {
    *(undefined4 *)(regEax + 0xc) = 7;
    *(undefined4 *)(regEax + 8) = 0;
    *(undefined1 *)(regEax + 4) = 1;
  }
  if ((*(int *)(regEax + 0xc) < 1) && (*(int *)(regEax + 8) != 0)) {
    *(undefined4 *)(regEax + 8) = 0;
    *(undefined4 *)(regEax + 0xc) = 0;
  }
  iVar1 = *(int *)(regEax + 0x18) + *(int *)(regEax + 0x14);
  *(int *)(regEax + 0x18) = iVar1;
  if ((0 < iVar1) && (*(int *)(regEax + 0x14) != 0)) {
    *(undefined4 *)(regEax + 0x18) = 1;
    *(undefined4 *)(regEax + 0x14) = 0;
    *(undefined1 *)(regEax + 0x10) = 1;
  }
  if ((*(int *)(regEax + 0x18) < 1) && (*(int *)(regEax + 0x14) != 0)) {
    *(undefined4 *)(regEax + 0x14) = 0;
    *(undefined4 *)(regEax + 0x18) = 0;
  }
  iVar1 = *(int *)(regEax + 0x24) + *(int *)(regEax + 0x20);
  *(int *)(regEax + 0x24) = iVar1;
  if ((2 < iVar1) && (*(int *)(regEax + 0x20) != 0)) {
    *(undefined4 *)(regEax + 0x24) = 3;
    *(undefined4 *)(regEax + 0x20) = 0;
    *(undefined1 *)(regEax + 0x1c) = 1;
  }
  if ((*(int *)(regEax + 0x24) < 1) && (*(int *)(regEax + 0x20) != 0)) {
    *(undefined4 *)(regEax + 0x20) = 0;
    *(undefined4 *)(regEax + 0x24) = 0;
  }
  iVar1 = *(int *)(regEax + 0x30) + *(int *)(regEax + 0x2c);
  *(int *)(regEax + 0x30) = iVar1;
  if (0 < iVar1) {
    *(undefined4 *)(regEax + 0x2c) = 0;
    *(undefined4 *)(regEax + 0x30) = 1;
  }
  if (*(int *)(regEax + 0x30) < 1) {
    *(undefined4 *)(regEax + 0x2c) = 0;
    *(undefined4 *)(regEax + 0x30) = 0;
  }
  return;
}

