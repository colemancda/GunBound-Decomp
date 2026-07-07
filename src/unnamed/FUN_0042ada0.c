/* FUN_0042ada0 - 0x0042ada0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0042ada0(int param_1,char param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int unaff_ESI;
  
  iVar2 = 0;
  piVar4 = (int *)(DAT_005b3484 + 0x4464c);
  while( true ) {
    iVar1 = (iVar2 / 3) * 300;
    iVar3 = (iVar2 % 3) * 0x3c;
    if (((((iVar1 + 0x18 < unaff_ESI) && (unaff_ESI < iVar1 + 0x119)) && (iVar3 + 0x3a < param_1))
        && (param_1 < iVar3 + 0x74)) &&
       ((param_2 != '\0' ||
        (((*piVar4 == 1 && (*(char *)(DAT_005b3484 + 0x449a8 + iVar2) == '\0')) &&
         (*(char *)(DAT_005b3484 + 0x4499c + iVar2) != *(char *)(DAT_005b3484 + 0x449a2 + iVar2)))))
       )) break;
    iVar2 = iVar2 + 1;
    piVar4 = piVar4 + 1;
    if (5 < iVar2) {
      return -1;
    }
  }
  return iVar2;
}

