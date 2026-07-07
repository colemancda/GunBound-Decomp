/* FUN_004eb290 - 0x004eb290 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004eb290(int param_1,int param_2,int param_3)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  byte *in_EAX;
  byte bVar4;
  int iVar5;
  byte bVar6;
  int iVar7;
  int local_18;
  byte local_10 [16];
  
  iVar3 = DAT_0056df30;
  local_10[0xd] = in_EAX[0xb] >> 1;
  iVar7 = 1;
  do {
    if (iVar7 == 1) {
      bVar4 = 0;
    }
    else {
      bVar4 = in_EAX[-1] >> 1;
    }
    bVar2 = *in_EAX;
    bVar4 = bVar2 >> 2 | bVar2 | bVar4;
    local_10[iVar7] = bVar4;
    if (iVar7 == 0xc) {
      bVar6 = 0;
    }
    else {
      bVar6 = in_EAX[1] >> 1;
    }
    local_10[iVar7] = ~(bVar2 >> 1) & (bVar4 | bVar6);
    if (iVar7 == 0) {
      bVar4 = 0;
    }
    else {
      bVar4 = *in_EAX >> 1;
    }
    bVar2 = in_EAX[1];
    bVar4 = bVar2 >> 2 | bVar2 | bVar4;
    local_10[iVar7 + 1] = bVar4;
    if (iVar7 == 0xb) {
      bVar6 = 0;
    }
    else {
      bVar6 = in_EAX[2] >> 1;
    }
    local_10[iVar7 + 1] = ~(bVar2 >> 1) & (bVar4 | bVar6);
    if (iVar7 == -1) {
      bVar4 = 0;
    }
    else {
      bVar4 = in_EAX[1] >> 1;
    }
    bVar2 = in_EAX[2];
    bVar4 = bVar2 >> 2 | bVar2 | bVar4;
    local_10[iVar7 + 2] = bVar4;
    if (iVar7 == 10) {
      bVar6 = 0;
    }
    else {
      bVar6 = in_EAX[3] >> 1;
    }
    local_10[iVar7 + 2] = ~(bVar2 >> 1) & (bVar4 | bVar6);
    if (iVar7 == -2) {
      bVar4 = 0;
    }
    else {
      bVar4 = in_EAX[2] >> 1;
    }
    bVar2 = in_EAX[3];
    bVar4 = bVar2 >> 2 | bVar2 | bVar4;
    local_10[iVar7 + 3] = bVar4;
    if (iVar7 == 9) {
      bVar6 = 0;
    }
    else {
      bVar6 = in_EAX[4] >> 1;
    }
    local_10[iVar7 + 3] = ~(bVar2 >> 1) & (bVar4 | bVar6);
    iVar7 = iVar7 + 4;
    in_EAX = in_EAX + 4;
  } while (iVar7 < 0xd);
  iVar7 = param_2 + -1;
  local_18 = 0xe;
  do {
    bVar4 = local_10[(iVar7 - param_2) + 1];
    if (bVar4 != 0) {
      iVar5 = 0;
      do {
        if (((((bVar4 >> (7U - (char)iVar5 & 0x1f) & 1) != 0) &&
             (iVar1 = iVar5 + -1 + param_1, iVar1 <= iVar3)) && (DAT_00793530 <= iVar1)) &&
           ((iVar7 <= DAT_0056df34 && (DAT_00793534 <= iVar7)))) {
          *(undefined2 *)(DAT_0079352c + (iVar7 * DAT_005b3620 + iVar1) * 2) = param_3;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 8);
    }
    iVar7 = iVar7 + 1;
    local_18 = local_18 + -1;
  } while (local_18 != 0);
  return;
}

