/* FUN_004c1b90 - 0x004c1b90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004c1b90(int param_1,char *param_2,char param_3,undefined2 param_4)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = DAT_005b3484;
  if (8 < *(int *)(DAT_005b3484 + 0x58b60)) {
    FUN_0041ee10();
  }
  *(undefined1 *)(*(int *)(iVar2 + 0x58b60) * 9 + 0x58b64 + iVar2) = 0;
  *(undefined1 *)((*(int *)(iVar2 + 0x58b60) + 0x6569) * 0xe + iVar2) = 0;
  if (param_3 == '\x02') {
    cVar1 = *param_2;
    if (cVar1 != '!') {
      if (cVar1 == '@') {
        param_3 = '\n';
      }
      else if (cVar1 == '#') {
        param_3 = '\v';
      }
      else if (cVar1 == '$') {
        param_3 = '\f';
      }
      else if (cVar1 == '%') {
        param_3 = '\r';
      }
      else if (cVar1 == '^') {
        param_3 = '\x0e';
      }
      else if (cVar1 == '&') {
        param_3 = '\x0f';
      }
      else {
        if (cVar1 != '*') goto LAB_004c1c21;
        param_3 = '\x10';
      }
    }
    param_2 = param_2 + 1;
  }
LAB_004c1c21:
  *(char *)(iVar2 + 0x58c4a + *(int *)(iVar2 + 0x58b60)) = param_3;
  *(int *)(iVar2 + 0x59154 + *(int *)(iVar2 + 0x58b60) * 4) = *(int *)(param_1 + 0xc) + 300;
  *(undefined2 *)(iVar2 + 0x5917c + *(int *)(iVar2 + 0x58b60) * 2) = param_4;
  pcVar3 = (char *)(*(int *)(iVar2 + 0x58b60) * 0x80 + 0x58c54 + iVar2);
  do {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    *pcVar3 = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  *(int *)(iVar2 + 0x58b60) = *(int *)(iVar2 + 0x58b60) + 1;
  return;
}

