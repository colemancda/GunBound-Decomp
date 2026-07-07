/* FUN_004db720 - 0x004db720 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004db720(void)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int extraout_ECX;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  char cVar10;
  int iVar11;
  uint uVar12;
  char *pcVar13;
  int local_24;
  int local_20 [8];
  
  FUN_004db570();
  iVar11 = DAT_005b3484;
  uVar7 = *(uint *)(extraout_ECX + 0x490);
  uVar4 = (uint)(*(byte *)(DAT_005b3484 + 0x45124) >> 1);
  uVar12 = uVar4;
  if ((int)uVar4 <= (int)uVar7) {
    uVar12 = uVar7;
  }
  uVar3 = *(uint *)(extraout_ECX + 0x494);
  uVar6 = *(byte *)(DAT_005b3484 + 0x45124) - uVar3;
  if (((int)uVar12 < (int)uVar6) && (uVar6 = uVar4, (int)uVar4 <= (int)uVar7)) {
    uVar6 = uVar7;
  }
  *(uint *)(extraout_ECX + 0x498) = uVar6;
  uVar4 = (uint)(*(byte *)(iVar11 + 0x45124) >> 1);
  uVar12 = uVar4;
  if ((int)uVar4 <= (int)uVar3) {
    uVar12 = uVar3;
  }
  uVar7 = *(byte *)(iVar11 + 0x45124) - uVar7;
  if (((int)uVar12 < (int)uVar7) && (uVar7 = uVar4, (int)uVar4 <= (int)uVar3)) {
    uVar7 = uVar3;
  }
  *(uint *)(extraout_ECX + 0x49c) = uVar7;
  pcVar1 = (char *)(extraout_ECX + 0x4a0);
  pcVar1[0] = -2;
  pcVar1[1] = -2;
  pcVar1[2] = -2;
  pcVar1[3] = -2;
  *(undefined4 *)(extraout_ECX + 0x4a4) = 0xfefefefe;
  iVar8 = 4;
  cVar10 = '\0';
  if (4 < *(int *)(extraout_ECX + 0x49c)) {
    iVar8 = 8 - *(int *)(extraout_ECX + 0x49c);
  }
  if (4 < *(int *)(extraout_ECX + 0x498)) {
    iVar8 = *(int *)(extraout_ECX + 0x498);
  }
  piVar9 = (int *)(iVar11 + 0x47380);
  local_24 = 2;
  do {
    iVar5 = piVar9[-1];
    if (*(char *)(iVar11 + 0x45914 + iVar5) != '\0') {
      cVar2 = *(char *)(iVar11 + 0x4590c + iVar5);
      if (cVar2 == '\0') {
        pcVar1[iVar5] = cVar10;
        cVar10 = cVar10 + '\x01';
      }
      else if (cVar2 == '\x01') {
        pcVar1[iVar5] = (char)iVar8;
        iVar8 = iVar8 + 1;
      }
    }
    iVar5 = *piVar9;
    if (*(char *)(iVar11 + 0x45914 + iVar5) != '\0') {
      cVar2 = *(char *)(iVar11 + 0x4590c + iVar5);
      if (cVar2 == '\0') {
        pcVar1[iVar5] = cVar10;
        cVar10 = cVar10 + '\x01';
      }
      else if (cVar2 == '\x01') {
        pcVar1[iVar5] = (char)iVar8;
        iVar8 = iVar8 + 1;
      }
    }
    iVar5 = piVar9[1];
    if (*(char *)(iVar11 + 0x45914 + iVar5) != '\0') {
      cVar2 = *(char *)(iVar11 + 0x4590c + iVar5);
      if (cVar2 == '\0') {
        pcVar1[iVar5] = cVar10;
        cVar10 = cVar10 + '\x01';
      }
      else if (cVar2 == '\x01') {
        pcVar1[iVar5] = (char)iVar8;
        iVar8 = iVar8 + 1;
      }
    }
    iVar5 = piVar9[2];
    if (*(char *)(iVar11 + 0x45914 + iVar5) != '\0') {
      cVar2 = *(char *)(iVar11 + 0x4590c + iVar5);
      if (cVar2 == '\0') {
        pcVar1[iVar5] = cVar10;
        cVar10 = cVar10 + '\x01';
      }
      else if (cVar2 == '\x01') {
        pcVar1[iVar5] = (char)iVar8;
        iVar8 = iVar8 + 1;
      }
    }
    piVar9 = piVar9 + 4;
    local_24 = local_24 + -1;
  } while (local_24 != 0);
  local_20[0] = 0;
  local_20[1] = 4;
  local_20[2] = 1;
  local_20[3] = 5;
  local_20[4] = 2;
  local_20[5] = 6;
  local_20[6] = 3;
  local_20[7] = 7;
  iVar11 = 8;
  pcVar13 = pcVar1;
  do {
    if (*pcVar13 == -2) {
      piVar9 = local_20;
LAB_004db8f0:
      do {
        iVar8 = *piVar9;
        piVar9 = piVar9 + 1;
        iVar5 = 0;
        do {
          if (pcVar1[iVar5] == iVar8) goto LAB_004db8f0;
          iVar5 = iVar5 + 1;
        } while (iVar5 < 8);
      } while (iVar8 == -1);
      *pcVar13 = (char)iVar8;
    }
    pcVar13 = pcVar13 + 1;
    iVar11 = iVar11 + -1;
    if (iVar11 == 0) {
      return;
    }
  } while( true );
}

