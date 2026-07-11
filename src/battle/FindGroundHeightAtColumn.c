/* FindGroundHeightAtColumn - 0x004e4340 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FindGroundHeightAtColumn(undefined4 param_1,int param_2)

{
  int iVar1;
  int in_EAX;
  char *pcVar2;
  int unaff_EDI;
  
  if ((-1 < unaff_EDI) && (iVar1 = *(int *)(param_2 + 0x18), unaff_EDI < iVar1)) {
    if (in_EAX < 0) {
      in_EAX = 0;
    }
    pcVar2 = (char *)(iVar1 * in_EAX + *(int *)(param_2 + 0x34) + unaff_EDI);
    while( true ) {
      if (*(int *)(param_2 + 0x1c) <= in_EAX) {
        return 10000;
      }
      if (*pcVar2 != '\0') break;
      pcVar2 = pcVar2 + iVar1;
      in_EAX = in_EAX + 1;
    }
    return in_EAX;
  }
  return 10000;
}

