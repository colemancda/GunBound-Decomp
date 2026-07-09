/* FUN_00504970 - 0x00504970 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __fastcall
FUN_00504970(uint param_1,char *param_2,int param_3,undefined4 param_4,undefined4 param_5,
            uint param_6)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffe868;
  int *piVar1;
  char cVar2;
  uint uVar3;
  ushort uVar4;
  char *pcVar5;
  char *pcVar6;
  char cVar7;
  char acStack_178c [6016];
  undefined4 uStack_c;
  
  uStack_c = 0x504980;
  uVar3 = param_6;
  cVar2 = (**(code **)**(undefined4 **)(param_3 + 0x1ab0))(param_4,param_5,param_6,param_2,param_1);
  cVar7 = (char)uVar3;
  if (cVar2 != '\0') {
    switch(param_6 & 0xffff) {
    case 0xc011:
      pcVar5 = acStack_178c;
      for (uVar3 = param_1 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)param_2;
        param_2 = param_2 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar3 = param_1 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar5 = *param_2;
        param_2 = param_2 + 1;
        pcVar5 = pcVar5 + 1;
      }
      piVar1 = *(int **)(param_3 + 0x1ab0);
      acStack_178c[param_1] = '\0';
      (**(code **)(*piVar1 + 0x18))(param_4,0,acStack_178c,param_5);
      return;
    case 0xc018:
      pcVar5 = acStack_178c;
      for (uVar3 = param_1 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)param_2;
        param_2 = param_2 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar3 = param_1 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar5 = *param_2;
        param_2 = param_2 + 1;
        pcVar5 = pcVar5 + 1;
      }
      piVar1 = *(int **)(param_3 + 0x1ab0);
      acStack_178c[param_1] = '\0';
      (**(code **)(*piVar1 + 0x18))(param_4,1,acStack_178c,param_5);
      return;
    case 0xc041:
      pcVar5 = param_2 + 8;
      pcVar6 = acStack_178c;
      for (uVar3 = param_1 - 8 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar6 = pcVar6 + 4;
      }
      for (uVar3 = param_1 - 8 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar6 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar6 = pcVar6 + 1;
      }
      piVar1 = *(int **)(param_3 + 0x1ab0);
      acStack_178c[param_1 - 8] = '\0';
      (**(code **)(*piVar1 + 0x24))(param_4,&stack0xffffe868,acStack_178c);
      return;
    case 0xc042:
      cVar2 = *param_2;
      acStack_178c[param_1 - 1] = '\0';
      (**(code **)(**(int **)(param_3 + 0x1ab0) + 0x28))(param_4,cVar2 != '\0');
      if (cVar7 != '\0') {
        FUN_004fcee0();
        return;
      }
      break;
    case 0xc043:
      (**(code **)(**(int **)(param_3 + 0x1ab0) + 0x30))(param_4);
      FUN_004fceb0(0x3002);
      return;
    case 0xc051:
      uVar4 = (short)param_1 - 0x18;
      if (uVar4 < 0x81) {
        (param_2 + 0x18)[uVar4] = '\0';
        (**(code **)(**(int **)(param_3 + 0x1ab0) + 0x1c))(param_4,param_2,param_2 + 0x18);
        return;
      }
      break;
    case 0xc053:
      (**(code **)(**(int **)(param_3 + 0x1ab0) + 0x20))(param_4);
    }
  }
  return;
}

