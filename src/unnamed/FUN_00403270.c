/* FUN_00403270 - 0x00403270 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool __fastcall FUN_00403270(char param_1)

{
  char cVar1;
  char *in_EAX;
  int iVar2;
  char local_18;
  char local_17 [23];
  
  local_18 = ((param_1 == '\0') - 1U & 5) + 0x69;
  iVar2 = -(int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[(int)(local_17 + iVar2)] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  iVar2 = FUN_00404b00(&local_18);
  return iVar2 != 0;
}

