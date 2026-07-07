/* FUN_00521ea0 - 0x00521ea0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_00521ea0(LPVOID param_1,undefined4 param_2)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  char *pcVar4;
  DWORD DVar5;
  HMODULE hModule;
  FARPROC pFVar6;
  HANDLE pvVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  char *pcVar11;
  char *pcVar12;
  undefined *puVar13;
  DWORD local_108;
  char local_104 [260];
  
  if (*(char *)((int)param_1 + 0x18) != '\0') {
    return 1;
  }
  iVar1 = (int)param_1 + 0x24;
  uVar3 = FUN_005218c0(&DAT_0056a5a4);
  FUN_00521a90(iVar1,uVar3);
  FUN_00521c90(local_104,0x104);
  uVar8 = 0xffffffff;
  pcVar4 = &DAT_0056a3bc;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  iVar9 = -1;
  pcVar4 = local_104;
  do {
    pcVar11 = pcVar4;
    if (iVar9 == 0) break;
    iVar9 = iVar9 + -1;
    pcVar11 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar2 != '\0');
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = pcVar11 + -1;
  for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  pcVar4 = (char *)FUN_005218c0(&DAT_0056a594);
  uVar8 = 0xffffffff;
  do {
    pcVar12 = pcVar4;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar12;
  } while (cVar2 != '\0');
  uVar8 = ~uVar8;
  iVar9 = -1;
  pcVar4 = local_104;
  do {
    pcVar11 = pcVar4;
    if (iVar9 == 0) break;
    iVar9 = iVar9 + -1;
    pcVar11 = pcVar4 + 1;
    cVar2 = *pcVar4;
    pcVar4 = pcVar11;
  } while (cVar2 != '\0');
  pcVar4 = pcVar12 + -uVar8;
  pcVar12 = pcVar11 + -1;
  for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar12 = pcVar12 + 1;
  }
  iVar9 = FUN_00528c4a(local_104,0);
  if (iVar9 == -1) {
    FUN_00521c90(local_104,0x104);
    uVar8 = 0xffffffff;
    pcVar4 = &DAT_0056a3bc;
    do {
      pcVar12 = pcVar4;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      pcVar12 = pcVar4 + 1;
      cVar2 = *pcVar4;
      pcVar4 = pcVar12;
    } while (cVar2 != '\0');
    uVar8 = ~uVar8;
    iVar9 = -1;
    pcVar4 = local_104;
    do {
      pcVar11 = pcVar4;
      if (iVar9 == 0) break;
      iVar9 = iVar9 + -1;
      pcVar11 = pcVar4 + 1;
      cVar2 = *pcVar4;
      pcVar4 = pcVar11;
    } while (cVar2 != '\0');
    pcVar4 = pcVar12 + -uVar8;
    pcVar12 = pcVar11 + -1;
    for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar12 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar12 = pcVar12 + 1;
    }
    pcVar4 = (char *)FUN_005218c0(&DAT_0056a584);
    uVar8 = 0xffffffff;
    do {
      pcVar12 = pcVar4;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      pcVar12 = pcVar4 + 1;
      cVar2 = *pcVar4;
      pcVar4 = pcVar12;
    } while (cVar2 != '\0');
    uVar8 = ~uVar8;
    iVar9 = -1;
    pcVar4 = local_104;
    do {
      pcVar11 = pcVar4;
      if (iVar9 == 0) break;
      iVar9 = iVar9 + -1;
      pcVar11 = pcVar4 + 1;
      cVar2 = *pcVar4;
      pcVar4 = pcVar11;
    } while (cVar2 != '\0');
    pcVar4 = pcVar12 + -uVar8;
    pcVar12 = pcVar11 + -1;
    for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar12 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar12 = pcVar12 + 1;
    }
  }
  uVar3 = FUN_005218c0(&DAT_0056a578,local_104);
  FUN_00521a90(iVar1,uVar3);
  cVar2 = FUN_005247a0(local_104,1);
  if (cVar2 == '\0') {
    GetLastError();
    uVar3 = *(undefined4 *)((int)param_1 + 0x10c0);
    DVar5 = GetLastError();
    uVar3 = FUN_005218c0(&DAT_0056a558,uVar3,DVar5);
    FUN_00521a90(iVar1,uVar3);
    return 0;
  }
  hModule = LoadLibraryA(local_104);
  *(HMODULE *)((int)param_1 + 0x10e8) = hModule;
  if (hModule == (HMODULE)0x0) {
    DVar5 = GetLastError();
    puVar13 = &DAT_0056a53c;
  }
  else {
    pFVar6 = GetProcAddress(hModule,(LPCSTR)0x2);
    *(FARPROC *)((int)param_1 + 0x1144) = pFVar6;
    pFVar6 = GetProcAddress(*(HMODULE *)((int)param_1 + 0x10e8),(LPCSTR)0x1);
    *(FARPROC *)((int)param_1 + 0x1148) = pFVar6;
    if ((*(int *)((int)param_1 + 0x1144) == 0) || (pFVar6 == (FARPROC)0x0)) {
      DVar5 = GetLastError();
      puVar13 = &DAT_0056a484;
    }
    else {
      pvVar7 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
      *(HANDLE *)((int)param_1 + 0x14) = pvVar7;
      if (pvVar7 == (HANDLE)0x0) {
        DVar5 = GetLastError();
        puVar13 = &DAT_0056a514;
      }
      else {
        *(undefined1 *)((int)param_1 + 0x18) = 1;
        pvVar7 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_00522270,param_1,0,&local_108);
        *(HANDLE *)((int)param_1 + 0x10ec) = pvVar7;
        if (pvVar7 == (HANDLE)0x0) {
          DVar5 = GetLastError();
          puVar13 = &DAT_0056a4f0;
        }
        else {
          uVar3 = FUN_005218c0(&DAT_0056a4cc,local_108);
          FUN_00521a90(iVar1,uVar3);
          DVar5 = (**(code **)((int)param_1 + 0x1144))
                            (*(undefined4 *)((int)param_1 + 0x10c4),0,param_2,
                             *(undefined4 *)((int)param_1 + 0x14));
          if (DVar5 == 0x6b) {
            uVar3 = FUN_005218c0(&DAT_0056a49c);
            FUN_00521a90(iVar1,uVar3);
            return 1;
          }
          puVar13 = &DAT_0056a4b0;
        }
      }
    }
  }
  uVar3 = FUN_005218c0(puVar13,DVar5);
  FUN_00521a90(iVar1,uVar3);
  return 0;
}

