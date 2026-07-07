/* FUN_00409990 - 0x00409990 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Type propagation algorithm not settling */

void FUN_00409990(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  CHAR local_100 [256];
  
  if (*(char *)(DAT_007934e4 + 8) != '\0') {
    iVar2 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),local_100,0x80);
    if (iVar2 != 0) goto LAB_004099bf;
  }
  local_100[0] = '\0';
LAB_004099bf:
  pcVar3 = local_100;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  *(bool *)(param_1 + 5) = pcVar3 != (char *)((int)local_100 + 1U);
  if (param_2 == '\0') {
    SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
  }
  return;
}

