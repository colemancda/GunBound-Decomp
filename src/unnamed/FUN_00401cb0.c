/* FUN_00401cb0 - 0x00401cb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00401cb0(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int unaff_ESI;
  
  pcVar2 = (char *)(unaff_ESI + 0xc + *(int *)(unaff_ESI + 0xc0c) * 0x18);
  do {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  *(int *)(unaff_ESI + 0xc0c) = *(int *)(unaff_ESI + 0xc0c) + 1;
  return;
}

