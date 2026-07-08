/* FUN_0043de70 - 0x0043de70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0043de70(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  FUN_0043e0f0();
  *(undefined4 *)(iVar2 + 8) = 0;
  iVar3 = iVar2;
  if (iVar2 != *param_1) {
    do {
      iVar4 = *(int *)(iVar3 + 0x14);
      if (*(int *)(iVar4 + 8) != 0) break;
      iVar5 = *(int *)(*(int *)(iVar4 + 0x14) + 0xc);
      if (iVar4 == iVar5) {
        iVar5 = *(int *)(*(int *)(iVar4 + 0x14) + 0x10);
        if ((iVar5 == 0) || (*(int *)(iVar5 + 8) != 0)) {
          if ((iVar3 == *(int *)(iVar4 + 0x10)) && (iVar3 = iVar4, iVar4 != 0)) {
            iVar3 = *(int *)(iVar4 + 0x10);
            *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(iVar3 + 0xc);
            if (*(int *)(iVar3 + 0xc) != param_1[5]) {
              *(int *)(*(int *)(iVar3 + 0xc) + 0x14) = iVar4;
            }
            *(undefined4 *)(iVar3 + 0x14) = *(undefined4 *)(iVar4 + 0x14);
            iVar5 = *(int *)(iVar4 + 0x14);
            if (iVar5 == param_1[5]) {
              *param_1 = iVar3;
            }
            else if (iVar4 == *(int *)(iVar5 + 0xc)) {
              *(int *)(iVar5 + 0xc) = iVar3;
            }
            else {
              *(int *)(iVar5 + 0x10) = iVar3;
            }
            *(int *)(iVar3 + 0xc) = iVar4;
            *(int *)(iVar4 + 0x14) = iVar3;
            iVar3 = iVar4;
          }
          *(undefined4 *)(*(int *)(iVar3 + 0x14) + 8) = 1;
          *(undefined4 *)(*(int *)(*(int *)(iVar3 + 0x14) + 0x14) + 8) = 0;
          iVar4 = *(int *)(*(int *)(iVar3 + 0x14) + 0x14);
          if (iVar4 != 0) {
            iVar5 = *(int *)(iVar4 + 0xc);
            *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar5 + 0x10);
            if (*(int *)(iVar5 + 0x10) != param_1[5]) {
              *(int *)(*(int *)(iVar5 + 0x10) + 0x14) = iVar4;
            }
            *(undefined4 *)(iVar5 + 0x14) = *(undefined4 *)(iVar4 + 0x14);
            iVar1 = *(int *)(iVar4 + 0x14);
            if (iVar1 == param_1[5]) {
              *param_1 = iVar5;
              *(int *)(iVar5 + 0x10) = iVar4;
            }
            else if (iVar4 == *(int *)(iVar1 + 0x10)) {
              *(int *)(iVar1 + 0x10) = iVar5;
              *(int *)(iVar5 + 0x10) = iVar4;
            }
            else {
              *(int *)(iVar1 + 0xc) = iVar5;
              *(int *)(iVar5 + 0x10) = iVar4;
            }
LAB_0043e02f:
            *(int *)(iVar4 + 0x14) = iVar5;
          }
        }
        else {
LAB_0043dec6:
          *(undefined4 *)(*(int *)(iVar3 + 0x14) + 8) = 1;
          *(undefined4 *)(iVar5 + 8) = 1;
          *(undefined4 *)(*(int *)(*(int *)(iVar3 + 0x14) + 0x14) + 8) = 0;
          iVar3 = *(int *)(*(int *)(iVar3 + 0x14) + 0x14);
        }
      }
      else {
        if ((iVar5 != 0) && (*(int *)(iVar5 + 8) == 0)) goto LAB_0043dec6;
        if ((iVar3 == *(int *)(iVar4 + 0xc)) && (iVar3 = iVar4, iVar4 != 0)) {
          iVar3 = *(int *)(iVar4 + 0xc);
          *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar3 + 0x10);
          if (*(int *)(iVar3 + 0x10) != param_1[5]) {
            *(int *)(*(int *)(iVar3 + 0x10) + 0x14) = iVar4;
          }
          *(undefined4 *)(iVar3 + 0x14) = *(undefined4 *)(iVar4 + 0x14);
          iVar5 = *(int *)(iVar4 + 0x14);
          if (iVar5 == param_1[5]) {
            *param_1 = iVar3;
          }
          else if (iVar4 == *(int *)(iVar5 + 0x10)) {
            *(int *)(iVar5 + 0x10) = iVar3;
          }
          else {
            *(int *)(iVar5 + 0xc) = iVar3;
          }
          *(int *)(iVar3 + 0x10) = iVar4;
          *(int *)(iVar4 + 0x14) = iVar3;
          iVar3 = iVar4;
        }
        *(undefined4 *)(*(int *)(iVar3 + 0x14) + 8) = 1;
        *(undefined4 *)(*(int *)(*(int *)(iVar3 + 0x14) + 0x14) + 8) = 0;
        iVar4 = *(int *)(*(int *)(iVar3 + 0x14) + 0x14);
        if (iVar4 != 0) {
          iVar5 = *(int *)(iVar4 + 0x10);
          *(undefined4 *)(iVar4 + 0x10) = *(undefined4 *)(iVar5 + 0xc);
          if (*(int *)(iVar5 + 0xc) != param_1[5]) {
            *(int *)(*(int *)(iVar5 + 0xc) + 0x14) = iVar4;
          }
          *(undefined4 *)(iVar5 + 0x14) = *(undefined4 *)(iVar4 + 0x14);
          iVar1 = *(int *)(iVar4 + 0x14);
          if (iVar1 == param_1[5]) {
            *param_1 = iVar5;
          }
          else if (iVar4 == *(int *)(iVar1 + 0xc)) {
            *(int *)(iVar1 + 0xc) = iVar5;
          }
          else {
            *(int *)(iVar1 + 0x10) = iVar5;
          }
          *(int *)(iVar5 + 0xc) = iVar4;
          goto LAB_0043e02f;
        }
      }
    } while (iVar3 != *param_1);
  }
  *(undefined4 *)(*param_1 + 8) = 1;
  *(int *)(*param_1 + 0x14) = param_1[5];
  return iVar2;
}

