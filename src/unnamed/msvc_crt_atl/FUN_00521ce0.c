/* FUN_00521ce0 - 0x00521ce0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00521ce0(uchar *param_1,DWORD param_2)

{
  char cVar1;
  DWORD DVar2;
  uchar *puVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  DVar2 = GetModuleFileNameA((HMODULE)0x0,(LPSTR)param_1,param_2);
  if (DVar2 != 0) {
    puVar3 = __mbsrchr(param_1,0x5c);
    if (puVar3 != (uchar *)0x0) {
      *puVar3 = '\0';
      return 1;
    }
    uVar4 = 0xffffffff;
    pcVar6 = &DAT_0056a44c;
    do {
      pcVar7 = pcVar6;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    puVar3 = (uchar *)(pcVar7 + -uVar4);
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)param_1 = *(undefined4 *)puVar3;
      puVar3 = puVar3 + 4;
      param_1 = param_1 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *param_1 = *puVar3;
      puVar3 = puVar3 + 1;
      param_1 = param_1 + 1;
    }
    return 1;
  }
  uVar4 = 0xffffffff;
  pcVar6 = &DAT_0056a44c;
  do {
    pcVar7 = pcVar6;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  puVar3 = (uchar *)(pcVar7 + -uVar4);
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)param_1 = *(undefined4 *)puVar3;
    puVar3 = puVar3 + 4;
    param_1 = param_1 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *param_1 = *puVar3;
    puVar3 = puVar3 + 1;
    param_1 = param_1 + 1;
  }
  return 0;
}

