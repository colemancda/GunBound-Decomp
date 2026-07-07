/* FUN_004fd680 - 0x004fd680 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall
FUN_004fd680(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,char *param_5)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_1778;
  undefined4 local_1774;
  undefined4 local_1770;
  undefined4 local_176c;
  undefined4 local_1768;
  undefined4 local_1764;
  char local_1760 [5972];
  undefined4 uStack_c;
  
  uStack_c = 0x4fd690;
  if (*(char *)(param_1 + 0x1a70) != '\0') {
    pcVar2 = param_5;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    uVar3 = (int)pcVar2 - (int)(param_5 + 1);
    if ((int)uVar3 < 0x81) {
      local_1778 = *param_4;
      local_1774 = param_4[1];
      local_1770 = param_4[2];
      local_176c = param_4[3];
      local_1768 = param_4[4];
      local_1764 = param_4[5];
      pcVar2 = local_1760;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar2 = *(undefined4 *)param_5;
        param_5 = param_5 + 4;
        pcVar2 = pcVar2 + 4;
      }
      for (uVar4 = uVar3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar2 = *param_5;
        param_5 = param_5 + 1;
        pcVar2 = pcVar2 + 1;
      }
      FUN_004fcf70(param_2,0xc051,&local_1778,
                   local_1760 + CONCAT22((short)(uVar3 >> 0x10),(short)uVar3 - (short)&local_1778));
    }
  }
  return;
}

