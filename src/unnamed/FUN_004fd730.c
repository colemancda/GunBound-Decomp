/* FUN_004fd730 - 0x004fd730 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall FUN_004fd730(int param_1,undefined4 param_2,char *param_3,char *param_4)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  char local_1778 [8];
  char local_1770 [5988];
  undefined4 uStack_c;
  
  uStack_c = 0x4fd740;
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0x1700;
  }
  _strncpy(local_1778,param_3,8);
  pcVar2 = param_4;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  uVar3 = (int)pcVar2 - (int)(param_4 + 1);
  pcVar2 = local_1770;
  for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar2 = *(undefined4 *)param_4;
    param_4 = param_4 + 4;
    pcVar2 = pcVar2 + 4;
  }
  for (uVar5 = uVar3 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar2 = *param_4;
    param_4 = param_4 + 1;
    pcVar2 = pcVar2 + 1;
  }
  uVar4 = FUN_004fcf10(local_1778,uVar3 + 8);
  return uVar4;
}

