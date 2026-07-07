/* FUN_00521c90 - 0x00521c90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00521c90(char *param_1,undefined4 param_2)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  
  FUN_00521ce0(param_1,param_2);
  pcVar2 = (char *)FUN_005218c0(&DAT_0056a43c);
  uVar3 = 0xffffffff;
  do {
    pcVar6 = pcVar2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar4 = -1;
  do {
    pcVar2 = param_1;
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    pcVar2 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar2;
  } while (cVar1 != '\0');
  pcVar6 = pcVar6 + -uVar3;
  pcVar2 = pcVar2 + -1;
  for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar2 = pcVar2 + 1;
  }
  return 1;
}

