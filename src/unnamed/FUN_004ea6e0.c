/* FUN_004ea6e0 - 0x004ea6e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004ea6e0(void)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  
  uVar2 = FUN_004ea1b0();
  bVar1 = (&DAT_0056dd30)[uVar2 & 0xffff];
  for (iVar3 = (byte)(&DAT_0056de30)[uVar2 & 0xffff] - 2; iVar3 != 0; iVar3 = iVar3 + -1) {
    uVar2 = uVar2 * 2;
    if (*(char *)(unaff_ESI + 0xf6b2) == '\0') {
      iVar4 = FUN_004ea120();
      uVar2 = uVar2 + iVar4;
    }
    else {
      *(char *)(unaff_ESI + 0xf6b2) = *(char *)(unaff_ESI + 0xf6b2) + -1;
      if (*(short *)(unaff_ESI + 0xf6b0) < 0) {
        uVar2 = uVar2 + 1;
      }
      *(short *)(unaff_ESI + 0xf6b0) = *(short *)(unaff_ESI + 0xf6b0) * 2;
    }
  }
  return uVar2 & 0x3f | (uint)bVar1 << 6;
}

