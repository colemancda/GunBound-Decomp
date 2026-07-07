/* FUN_0041b410 - 0x0041b410 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall FUN_0041b410(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  int iVar2;
  char *in_EAX;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  
  uVar3 = 0;
  iVar4 = param_3 + 1;
  iVar2 = 0;
  while ((iVar4 < param_5 && (iVar2 < param_4))) {
    cVar1 = *in_EAX;
    pcVar5 = in_EAX + 1;
    iVar6 = iVar2 + 1;
    if (cVar1 == '\0') {
      *(undefined1 *)(uVar3 + param_2) = 0;
      return 0;
    }
    if (cVar1 < '\0') {
      if (param_5 < (int)(uVar3 + 2 + param_3)) {
        *(undefined1 *)(uVar3 + param_2) = 0;
        return uVar3;
      }
      *(char *)(uVar3 + param_2) = cVar1;
      *(char *)(uVar3 + 1 + param_2) = *pcVar5;
      uVar3 = uVar3 + 2;
      iVar4 = iVar4 + 2;
      iVar2 = iVar2 + 2;
      in_EAX = in_EAX + 2;
    }
    else {
      iVar2 = iVar6;
      in_EAX = pcVar5;
      if ((cVar1 != '\r') && (cVar1 != '\n')) {
        *(char *)(uVar3 + param_2) = cVar1;
        uVar3 = uVar3 + 1;
        iVar4 = iVar4 + 1;
      }
    }
  }
  *(undefined1 *)(uVar3 + param_2) = 0;
  return uVar3 & (param_4 <= iVar2) - 1;
}

