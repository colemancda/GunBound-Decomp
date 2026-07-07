/* FUN_0052ddf8 - 0x0052ddf8 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __isindst_lk
   
   Library: Visual Studio 2003 Release */

bool __isindst_lk(void)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int *unaff_EBX;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  
  if (DAT_0056c87c == 0) {
    return false;
  }
  iVar1 = unaff_EBX[5];
  if ((iVar1 != DAT_0056c910) || (iVar1 != DAT_0056c91c)) {
    if (DAT_005b19ec == 0) {
      cvtdate(1,1,iVar1,1,0,0,0,0,0);
      cvtdate(0,1,iVar1,5,0,0,0,0,0);
    }
    else {
      if (DAT_005b19d8 != 0) {
        uVar5 = 0;
        uVar4 = 0;
        uVar6 = DAT_005b19de;
      }
      else {
        uVar5 = DAT_005b19dc;
        uVar4 = DAT_005b19de;
        uVar6 = 0;
      }
      cvtdate(1,DAT_005b19d8 == 0,iVar1,uVar4,uVar5,uVar6,DAT_005b19e2,DAT_005b19e4,DAT_005b19e6);
      if (DAT_005b1984 != 0) {
        uVar5 = 0;
        uVar4 = 0;
        uVar6 = DAT_005b198a;
      }
      else {
        uVar5 = DAT_005b1988;
        uVar4 = DAT_005b198a;
        uVar6 = 0;
      }
      cvtdate(0,DAT_005b1984 == 0,iVar1,uVar4,uVar5,uVar6,DAT_005b198e,DAT_005b1990,DAT_005b1992);
    }
  }
  iVar1 = unaff_EBX[7];
  if (DAT_0056c914 < DAT_0056c920) {
    if ((iVar1 < DAT_0056c914) || (DAT_0056c920 < iVar1)) {
      return false;
    }
    if ((DAT_0056c914 < iVar1) && (iVar1 < DAT_0056c920)) {
      return true;
    }
  }
  else {
    if (iVar1 < DAT_0056c920) {
      return true;
    }
    if (DAT_0056c914 < iVar1) {
      return true;
    }
    if ((DAT_0056c920 < iVar1) && (iVar1 < DAT_0056c914)) {
      return false;
    }
  }
  iVar3 = ((unaff_EBX[2] * 0x3c + unaff_EBX[1]) * 0x3c + *unaff_EBX) * 1000;
  if (iVar1 == DAT_0056c914) {
    bVar2 = DAT_0056c918 <= iVar3;
  }
  else {
    bVar2 = iVar3 < DAT_0056c924;
  }
  return bVar2;
}

