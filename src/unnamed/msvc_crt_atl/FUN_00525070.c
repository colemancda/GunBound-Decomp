/* FUN_00525070 - 0x00525070 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


char * FUN_00525070(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  cVar1 = *param_1;
  if (cVar1 != '\0') {
    while ((cVar1 != '\r' && (cVar1 != '\n'))) {
      *param_2 = cVar1;
      param_2 = param_2 + 1;
      param_1 = param_1 + 1;
      iVar2 = iVar2 + 1;
      if ((0xfe < iVar2) || (cVar1 = *param_1, cVar1 == '\0')) break;
    }
  }
  *param_2 = '\0';
  if (*param_1 == '\r') {
    param_1 = param_1 + 1;
  }
  if (*param_1 == '\n') {
    param_1 = param_1 + 1;
  }
  return param_1;
}

