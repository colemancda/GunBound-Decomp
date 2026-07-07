/* FUN_00450650 - 0x00450650 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00450650(int param_1,uint param_2)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  
  uVar6 = param_2;
  param_2 = 0;
  if (0 < (int)uVar6) {
    pcVar5 = (char *)(param_1 + 0x44);
    do {
      if (*pcVar5 == '\0') {
        return param_2;
      }
      pcVar2 = pcVar5;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      pcVar3 = pcVar5;
      if ((uint)((int)pcVar2 - (int)(pcVar5 + 1)) < uVar6) {
        do {
          cVar1 = *pcVar3;
          pcVar3[0x298] = cVar1;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        pcVar2 = pcVar5;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        uVar6 = uVar6 - ((int)pcVar2 - (int)(pcVar5 + 1));
      }
      else {
        pcVar2 = pcVar5;
        pcVar3 = pcVar5 + 0x298;
        for (uVar4 = uVar6 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
          *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
          pcVar2 = pcVar2 + 4;
          pcVar3 = pcVar3 + 4;
        }
        for (uVar4 = uVar6 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar3 = *pcVar2;
          pcVar2 = pcVar2 + 1;
          pcVar3 = pcVar3 + 1;
        }
        if (pcVar5[uVar6] < '\0') {
          pcVar5[uVar6 + 0x299] = pcVar5[uVar6 + 1];
        }
        uVar6 = 0;
      }
      param_2 = param_2 + 1;
      pcVar5 = pcVar5 + 0x14;
    } while (0 < (int)uVar6);
  }
  return param_2;
}

