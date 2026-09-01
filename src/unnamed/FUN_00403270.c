/* FUN_00403270 - 0x00403270 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool __fastcall FUN_00403270(int param_1,int param_2,char *regEax)

{
  char cVar1;
  int iVar2;
  char local_18;
  char local_17 [23];
  
  local_18 = ((param_1 == '\0') - 1U & 5) + 0x69;
  iVar2 = -(int)regEax;
  do {
    cVar1 = *regEax;
    regEax[(int)(local_17 + iVar2)] = cVar1;
    regEax = regEax + 1;
  } while (cVar1 != '\0');
  iVar2 = FUN_00404b00(&local_18,(int *)(param_2 + 0x1be4));
  return iVar2 != 0;
}

