/* FUN_00401d50 - 0x00401d50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall
FUN_00401d50(char *param_1,int param_2,char param_3,undefined4 param_4,short param_5,
            undefined4 *param_6,char *param_7)

{
  int *piVar1;
  char cVar2;
  char *in_EAX;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  
  iVar3 = FUN_00401bb0(param_2);
  if (iVar3 == 0) {
    puVar4 = operator_new(0x5c);
    if (puVar4 != (undefined4 *)0x0) {
      puVar4[3] = 0;
      puVar4[4] = 0;
      puVar4[1] = param_4;
      puVar4[2] = 0xffffffff;
      *(undefined1 *)(puVar4 + 5) = 0;
      *(undefined1 *)((int)puVar4 + 0x15) = 0;
      *puVar4 = &PTR_FUN_00551cb4;
      *(undefined1 *)(puVar4 + 0xc) = 0;
      *(undefined4 *)((int)puVar4 + 0x31) = 0xffffffff;
      *(undefined4 *)((int)puVar4 + 0x35) = 0xffffffff;
      *(undefined4 *)((int)puVar4 + 0x39) = 0xffffffff;
      *(undefined4 *)((int)puVar4 + 0x3d) = 0xffffffff;
      iVar3 = 0x18 - (int)param_1;
      do {
        cVar2 = *param_1;
        param_1[(int)puVar4 + iVar3] = cVar2;
        param_1 = param_1 + 1;
      } while (cVar2 != '\0');
      iVar3 = 0x21 - (int)in_EAX;
      do {
        cVar2 = *in_EAX;
        in_EAX[(int)puVar4 + iVar3] = cVar2;
        in_EAX = in_EAX + 1;
      } while (cVar2 != '\0');
      iVar3 = 0x41 - (int)param_7;
      do {
        cVar2 = *param_7;
        param_7[(int)puVar4 + iVar3] = cVar2;
        param_7 = param_7 + 1;
      } while (cVar2 != '\0');
      *(short *)((int)puVar4 + 0x2e) = param_5 + 4;
      *(undefined4 *)((int)puVar4 + 0x31) = *param_6;
      *(undefined4 *)((int)puVar4 + 0x35) = param_6[1];
      *(undefined4 *)((int)puVar4 + 0x39) = param_6[2];
      *(undefined4 *)((int)puVar4 + 0x3d) = param_6[3];
      cVar2 = RegisterActiveObject();
      if (cVar2 != '\0') {
        iVar3 = *(int *)(param_2 + 0xc10) + 1;
        *(int *)(param_2 + 0xc10) = iVar3;
        piVar5 = DAT_00e53c44;
        if (DAT_00e53c44 != (int *)0x0) {
          while( true ) {
            piVar1 = (int *)*piVar5;
            if ((*(int *)(piVar5[2] + 0x20) == 0) && (*(int *)(piVar5[2] + 0x24) == 20000)) break;
            piVar5 = piVar1;
            if (piVar1 == (int *)0x0) {
              return;
            }
          }
          Widget_SetChildRange(iVar3,7);
          return;
        }
      }
    }
  }
  else if (param_3 != '\0') {
    iVar6 = iVar3 - (int)param_1;
    do {
      cVar2 = *param_1;
      param_1[iVar6 + 0x18] = cVar2;
      param_1 = param_1 + 1;
    } while (cVar2 != '\0');
    iVar6 = iVar3 - (int)in_EAX;
    do {
      cVar2 = *in_EAX;
      in_EAX[iVar6 + 0x21] = cVar2;
      in_EAX = in_EAX + 1;
    } while (cVar2 != '\0');
    *(short *)(iVar3 + 0x2e) = param_5 + 4;
    *(undefined4 *)(iVar3 + 0x31) = *param_6;
    *(undefined4 *)(iVar3 + 0x35) = param_6[1];
    *(undefined4 *)(iVar3 + 0x39) = param_6[2];
    *(undefined4 *)(iVar3 + 0x3d) = param_6[3];
  }
  return;
}

