/* FUN_004e73e0 - 0x004e73e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e73e0(int param_1)

{
  char cVar1;
  u_short uVar2;
  int iVar3;
  int unaff_ESI;
  char *unaff_EDI;
  
  *(undefined4 *)(unaff_ESI + 0x150) = 0x100007f;
  uVar2 = htons(0x20ab);
  *(u_short *)(unaff_ESI + 0x158) = uVar2;
  *(undefined2 *)(unaff_ESI + 0x15a) = param_1;
  *(undefined4 *)(unaff_ESI + 0x154) = 0xffffffff;
  iVar3 = (unaff_ESI + 0x15d) - (int)unaff_EDI;
  do {
    cVar1 = *unaff_EDI;
    unaff_EDI[iVar3] = cVar1;
    unaff_EDI = unaff_EDI + 1;
  } while (cVar1 != '\0');
  return;
}

