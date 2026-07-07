/* FUN_00506f30 - 0x00506f30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00506f30(void)

{
  int iVar1;
  int unaff_ESI;
  undefined4 *puVar2;
  
  if (*(char *)(unaff_ESI + 4) != '\0') {
    SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
  }
  puVar2 = (undefined4 *)(unaff_ESI + 0x38);
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(unaff_ESI + 0x13c) = 0;
  return;
}

