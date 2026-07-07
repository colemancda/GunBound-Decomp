/* FUN_004e5480 - 0x004e5480 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


ulong __fastcall FUN_004e5480(undefined4 param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  ulong uVar4;
  hostent *phVar5;
  
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)pcVar2 - (int)(param_2 + 1);
  if ((iVar3 != 0) && (param_2[iVar3 + -1] != '.')) {
    do {
      iVar3 = iVar3 + -1;
      if ((iVar3 < 0) || (cVar1 = param_2[iVar3], cVar1 == '.')) {
        uVar4 = inet_addr(param_2);
        return uVar4;
      }
    } while (('/' < cVar1) && (cVar1 < ':'));
    phVar5 = gethostbyname(param_2);
    if (phVar5 != (hostent *)0x0) {
      return *(ulong *)*phVar5->h_addr_list;
    }
  }
  return 0xffffffff;
}

