/* FUN_005207d0 - 0x005207d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00521007) */
/* WARNING: Removing unreachable block (ram,0x0052101d) */
/* WARNING: Removing unreachable block (ram,0x00521046) */
/* WARNING: Removing unreachable block (ram,0x0052106b) */
/* WARNING: Removing unreachable block (ram,0x0052106d) */
/* WARNING: Removing unreachable block (ram,0x0052107f) */
/* WARNING: Removing unreachable block (ram,0x00521081) */
/* WARNING: Removing unreachable block (ram,0x00521087) */
/* WARNING: Removing unreachable block (ram,0x00521089) */
/* WARNING: Removing unreachable block (ram,0x00521095) */
/* WARNING: Removing unreachable block (ram,0x00521097) */
/* WARNING: Removing unreachable block (ram,0x005210a0) */
/* WARNING: Removing unreachable block (ram,0x005210a2) */
/* WARNING: Removing unreachable block (ram,0x005210af) */
/* WARNING: Removing unreachable block (ram,0x005210b1) */
/* WARNING: Removing unreachable block (ram,0x005210b7) */
/* WARNING: Removing unreachable block (ram,0x005210b9) */
/* WARNING: Removing unreachable block (ram,0x005210be) */
/* WARNING: Removing unreachable block (ram,0x005210c0) */
/* WARNING: Removing unreachable block (ram,0x005210cf) */
/* WARNING: Removing unreachable block (ram,0x005210d1) */
/* WARNING: Removing unreachable block (ram,0x005210e5) */
/* WARNING: Removing unreachable block (ram,0x005210e7) */
/* WARNING: Removing unreachable block (ram,0x005210ed) */
/* WARNING: Removing unreachable block (ram,0x005210ef) */
/* WARNING: Removing unreachable block (ram,0x005210fd) */
/* WARNING: Removing unreachable block (ram,0x005210ff) */
/* WARNING: Removing unreachable block (ram,0x00521111) */
/* WARNING: Removing unreachable block (ram,0x0052114c) */
/* WARNING: Removing unreachable block (ram,0x0052117f) */
/* WARNING: Removing unreachable block (ram,0x005211ba) */
/* WARNING: Removing unreachable block (ram,0x00521218) */
/* WARNING: Removing unreachable block (ram,0x00521241) */
/* WARNING: Removing unreachable block (ram,0x00521332) */
/* WARNING: Removing unreachable block (ram,0x00521334) */
/* WARNING: Removing unreachable block (ram,0x00521341) */
/* WARNING: Removing unreachable block (ram,0x00521343) */
/* WARNING: Removing unreachable block (ram,0x00521349) */
/* WARNING: Removing unreachable block (ram,0x0052134b) */
/* WARNING: Removing unreachable block (ram,0x00521350) */
/* WARNING: Removing unreachable block (ram,0x00521352) */
/* WARNING: Removing unreachable block (ram,0x00521366) */
/* WARNING: Removing unreachable block (ram,0x00521368) */
/* WARNING: Removing unreachable block (ram,0x0052137c) */
/* WARNING: Removing unreachable block (ram,0x0052137e) */
/* WARNING: Removing unreachable block (ram,0x00521384) */
/* WARNING: Removing unreachable block (ram,0x00521386) */
/* WARNING: Removing unreachable block (ram,0x00521391) */
/* WARNING: Removing unreachable block (ram,0x00521393) */
/* WARNING: Removing unreachable block (ram,0x005213b3) */
/* WARNING: Removing unreachable block (ram,0x005213d8) */
/* WARNING: Removing unreachable block (ram,0x005213da) */
/* WARNING: Removing unreachable block (ram,0x005213ec) */
/* WARNING: Removing unreachable block (ram,0x005213ee) */
/* WARNING: Removing unreachable block (ram,0x005213f4) */
/* WARNING: Removing unreachable block (ram,0x005213f6) */
/* WARNING: Removing unreachable block (ram,0x005213fb) */
/* WARNING: Removing unreachable block (ram,0x005213fd) */
/* WARNING: Removing unreachable block (ram,0x00521410) */
/* WARNING: Removing unreachable block (ram,0x00521412) */
/* WARNING: Removing unreachable block (ram,0x00521420) */
/* WARNING: Removing unreachable block (ram,0x00521422) */
/* WARNING: Removing unreachable block (ram,0x00521428) */
/* WARNING: Removing unreachable block (ram,0x0052142a) */
/* WARNING: Removing unreachable block (ram,0x00521437) */
/* WARNING: Removing unreachable block (ram,0x00521439) */
/* WARNING: Removing unreachable block (ram,0x00521446) */
/* WARNING: Removing unreachable block (ram,0x00521481) */
/* WARNING: Removing unreachable block (ram,0x0052149a) */
/* WARNING: Removing unreachable block (ram,0x005214e7) */
/* WARNING: Removing unreachable block (ram,0x0052150e) */
/* WARNING: Removing unreachable block (ram,0x0052152f) */
/* WARNING: Removing unreachable block (ram,0x00521531) */
/* WARNING: Removing unreachable block (ram,0x0052156a) */
/* WARNING: Removing unreachable block (ram,0x005215a8) */
/* WARNING: Removing unreachable block (ram,0x005215bd) */
/* WARNING: Removing unreachable block (ram,0x005215eb) */
/* WARNING: Removing unreachable block (ram,0x00521678) */
/* WARNING: Removing unreachable block (ram,0x005216bb) */
/* WARNING: Removing unreachable block (ram,0x0052171f) */
/* WARNING: Removing unreachable block (ram,0x00521766) */
/* WARNING: Removing unreachable block (ram,0x00521796) */
/* WARNING: Removing unreachable block (ram,0x005217cd) */
/* WARNING: Removing unreachable block (ram,0x005217f6) */
/* WARNING: Removing unreachable block (ram,0x00521801) */
/* WARNING: Removing unreachable block (ram,0x0052180d) */
/* WARNING: Removing unreachable block (ram,0x0052182c) */
/* WARNING: Removing unreachable block (ram,0x0052183e) */
/* WARNING: Removing unreachable block (ram,0x00521871) */
/* WARNING: Removing unreachable block (ram,0x005216ec) */
/* WARNING: Removing unreachable block (ram,0x00521504) */
/* WARNING: Removing unreachable block (ram,0x005216f1) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_005207d0(char *param_1,uchar *param_2)

{
  char *pcVar1;
  byte bVar2;
  bool bVar3;
  char cVar4;
  DWORD DVar5;
  int iVar6;
  BOOL BVar7;
  undefined4 uVar8;
  uchar *puVar9;
  HANDLE pvVar10;
  char *pcVar11;
  byte *_Dest;
  LPCSTR pCVar12;
  uint uVar13;
  uint uVar14;
  uchar *puVar15;
  byte *pbVar16;
  char *pcVar17;
  char *pcVar18;
  _STARTUPINFOA *p_Var19;
  CHAR *pCVar20;
  uint uStack_da0;
  undefined4 uStack_d9c;
  _SECURITY_ATTRIBUTES _Stack_d98;
  DWORD DStack_d8c;
  _STARTUPINFOA a_Stack_d88 [5];
  char acStack_c20 [520];
  CHAR aCStack_a18 [256];
  uchar auStack_918 [2316];
  undefined4 uStack_c;
  
  if (*param_1 != '\0') {
    return 0x755;
  }
  cVar4 = FUN_00521bf0();
  param_1[0x1131] = cVar4;
  DVar5 = GetCurrentProcessId();
  *(DWORD *)(param_1 + 0x10c4) = DVar5;
  DAT_005b1590 = GetCurrentThreadId();
  __mbsnbcpy((uchar *)(param_1 + 0x10c8),param_2,0x20);
  param_1[0x10e7] = '\0';
  FUN_00521c90(&DAT_005b147c,0x104);
  iVar6 = FUN_00528c4a(&DAT_005b147c,0);
  if ((iVar6 == -1) &&
     (BVar7 = CreateDirectoryA(&DAT_005b147c,(LPSECURITY_ATTRIBUTES)0x0), BVar7 == 0)) {
    GetLastError();
    DVar5 = GetLastError();
    uVar8 = FUN_005218c0(&DAT_0056a3c0,DVar5);
    FUN_00521a90(param_1 + 0x24,uVar8);
    return 0x6f;
  }
  lstrcat(&DAT_005b147c,&DAT_0056a3bc);
  uVar8 = FUN_005218c0(&DAT_0056a3ac);
  lstrcat(&DAT_005b147c,uVar8);
  pcVar1 = param_1 + 0x24;
  if (*(int *)(param_1 + 0x24) != -1) goto LAB_00520a98;
  uVar13 = 0xffffffff;
  param_1[0x1054] = '\0';
  param_1[0x1055] = '\0';
  param_1[0x1056] = '\0';
  param_1[0x1057] = '\0';
  param_1[0x1058] = -0x18;
  param_1[0x1059] = '\x03';
  param_1[0x105a] = '\0';
  param_1[0x105b] = '\0';
  pcVar11 = &DAT_005b147c;
  do {
    if (uVar13 == 0) break;
    uVar13 = uVar13 - 1;
    cVar4 = *pcVar11;
    pcVar11 = pcVar11 + 1;
  } while (cVar4 != '\0');
  if ((~uVar13 - 1 < 4) || (DAT_005b147d == ':')) {
LAB_0052092a:
    puVar15 = auStack_918;
  }
  else {
    GetModuleFileNameA((HMODULE)0x0,(LPSTR)auStack_918,0x104);
    puVar9 = __mbsrchr(auStack_918,0x5c);
    puVar15 = puVar9 + 1;
    if (puVar9 == (uchar *)0x0) goto LAB_0052092a;
  }
  uVar13 = 0xffffffff;
  pcVar11 = &DAT_005b147c;
  do {
    pcVar18 = pcVar11;
    if (uVar13 == 0) break;
    uVar13 = uVar13 - 1;
    pcVar18 = pcVar11 + 1;
    cVar4 = *pcVar11;
    pcVar11 = pcVar18;
  } while (cVar4 != '\0');
  uVar13 = ~uVar13;
  puVar9 = (uchar *)(pcVar18 + -uVar13);
  for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
    *(undefined4 *)puVar15 = *(undefined4 *)puVar9;
    puVar9 = puVar9 + 4;
    puVar15 = puVar15 + 4;
  }
  for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
    *puVar15 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar15 = puVar15 + 1;
  }
  pvVar10 = CreateFileA((LPCSTR)auStack_918,0xc0000000,3,(LPSECURITY_ATTRIBUTES)0x0,2,0x80000080,
                        (HANDLE)0x0);
  *(HANDLE *)pcVar1 = pvVar10;
  if (pvVar10 != (HANDLE)0xffffffff) {
    GetLocalTime((LPSYSTEMTIME)(param_1 + 0x1040));
    _Dest = (byte *)(param_1 + 0x40);
    pcVar11 = (char *)FUN_005218c0(&DAT_0056a35c,((LPSYSTEMTIME)(param_1 + 0x1040))->wYear,
                                   *(undefined2 *)(param_1 + 0x1042),
                                   *(undefined2 *)(param_1 + 0x1046),
                                   *(undefined2 *)(param_1 + 0x1048),
                                   *(undefined2 *)(param_1 + 0x104a),
                                   *(undefined2 *)(param_1 + 0x104c),
                                   *(undefined2 *)(param_1 + 0x104e));
    _sprintf((char *)_Dest,pcVar11);
    uVar13 = 0xffffffff;
    pbVar16 = _Dest;
    do {
      if (uVar13 == 0) break;
      uVar13 = uVar13 - 1;
      bVar2 = *pbVar16;
      pbVar16 = pbVar16 + 1;
    } while (bVar2 != 0);
    DVar5 = ~uVar13 - 1;
    if (*(int *)(param_1 + 0x1058) == 999) {
      DVar5 = 0;
    }
    if (*(int *)(param_1 + 0x1054) == 0) {
      param_1[0x1050] = -0x76;
      param_1[0x1051] = '\x05';
      param_1[0x1052] = '\0';
      param_1[0x1053] = '\0';
      if (0 < (int)DVar5) {
        do {
          iVar6 = *(int *)(param_1 + 0x1050) * 3 + 1;
          *(int *)(param_1 + 0x1050) = iVar6;
          *_Dest = *_Dest ^ (char)iVar6 + 0x46U;
          _Dest = _Dest + 1;
        } while ((int)(_Dest + (-0x1c - (int)pcVar1)) < (int)DVar5);
      }
    }
    else if (0 < (int)DVar5) {
      do {
        iVar6 = *(int *)(param_1 + 0x1054);
        *(int *)(param_1 + 0x1054) = iVar6 + 2;
        *_Dest = *_Dest ^ (char)(iVar6 + 2) + 0x43U;
        _Dest = _Dest + 1;
      } while ((int)(_Dest + (-0x1c - (int)pcVar1)) < (int)DVar5);
    }
    WriteFile(*(HANDLE *)pcVar1,param_1 + 0x40,DVar5,&uStack_da0,(LPOVERLAPPED)0x0);
    InitializeCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x28));
  }
LAB_00520a98:
  uVar8 = FUN_005218c0(&DAT_0056a314,5,s_Wed_Feb_18_10_55_39_2004_0056a340);
  FUN_00521a90(pcVar1,uVar8);
  uVar8 = FUN_005218c0(&DAT_0056a2d4,*(undefined4 *)(param_1 + 0x10c4),uStack_c,FUN_00520380);
  FUN_00521a90(pcVar1,uVar8);
  FUN_00522f20();
  FUN_00523000();
  iVar6 = FUN_00522330();
  if (iVar6 == 0) {
    uVar8 = FUN_005218c0(&DAT_0056a2b8);
    FUN_00521a90(pcVar1,uVar8);
    return 0x73;
  }
  iVar6 = FUN_00522430(0);
  if (iVar6 == 0) {
    pCVar12 = (LPCSTR)FUN_005218c0(&DAT_0056a2ac);
    pvVar10 = OpenEventA(0x100002,0,pCVar12);
    if (pvVar10 == (HANDLE)0x0) {
      return 0x6e;
    }
    SetEvent(pvVar10);
    CloseHandle(pvVar10);
    iVar6 = FUN_00522430(0x251c);
    if (iVar6 == 0) {
      return 0x6e;
    }
    uVar8 = FUN_005218c0(&DAT_0056a28c);
    FUN_00521a90(pcVar1,uVar8);
  }
  DVar5 = GetTickCount();
  uStack_da0 = DVar5 & 0xfff00000;
  _Stack_d98.nLength = 0xc;
  _Stack_d98.lpSecurityDescriptor = (LPVOID)0x0;
  _Stack_d98.bInheritHandle = 1;
  pvVar10 = CreateEventA(&_Stack_d98,1,0,(LPCSTR)0x0);
  *(HANDLE *)(param_1 + 0x113c) = pvVar10;
  if (pvVar10 == (HANDLE)0x0) {
    GetLastError();
    DVar5 = GetLastError();
    uVar8 = FUN_005218c0(&DAT_0056a268,DVar5);
    FUN_00521a90(pcVar1,uVar8);
    DAT_005b158c = 2;
    return 0xab;
  }
  FUN_00521a90(pcVar1,&DAT_0056a264);
  FUN_00521ce0(acStack_c20,0x104);
  uVar13 = 0xffffffff;
  pcVar11 = &DAT_0056a3bc;
  do {
    pcVar18 = pcVar11;
    if (uVar13 == 0) break;
    uVar13 = uVar13 - 1;
    pcVar18 = pcVar11 + 1;
    cVar4 = *pcVar11;
    pcVar11 = pcVar18;
  } while (cVar4 != '\0');
  uVar13 = ~uVar13;
  iVar6 = -1;
  pcVar11 = acStack_c20;
  do {
    pcVar17 = pcVar11;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar17 = pcVar11 + 1;
    cVar4 = *pcVar11;
    pcVar11 = pcVar17;
  } while (cVar4 != '\0');
  pcVar11 = pcVar18 + -uVar13;
  pcVar18 = pcVar17 + -1;
  for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
    *(undefined4 *)pcVar18 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar18 = pcVar18 + 4;
  }
  for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
    *pcVar18 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar18 = pcVar18 + 1;
  }
  pcVar11 = (char *)FUN_005218c0(&DAT_0056a250);
  uVar13 = 0xffffffff;
  do {
    pcVar18 = pcVar11;
    if (uVar13 == 0) break;
    uVar13 = uVar13 - 1;
    pcVar18 = pcVar11 + 1;
    cVar4 = *pcVar11;
    pcVar11 = pcVar18;
  } while (cVar4 != '\0');
  uVar13 = ~uVar13;
  iVar6 = -1;
  pcVar11 = acStack_c20;
  do {
    pcVar17 = pcVar11;
    if (iVar6 == 0) break;
    iVar6 = iVar6 + -1;
    pcVar17 = pcVar11 + 1;
    cVar4 = *pcVar11;
    pcVar11 = pcVar17;
  } while (cVar4 != '\0');
  pcVar11 = pcVar18 + -uVar13;
  pcVar18 = pcVar17 + -1;
  for (uVar14 = uVar13 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
    *(undefined4 *)pcVar18 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar18 = pcVar18 + 4;
  }
  for (uVar13 = uVar13 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
    *pcVar18 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar18 = pcVar18 + 1;
  }
  iVar6 = FUN_00528c4a(acStack_c20,0);
  if (iVar6 == -1) {
    uVar8 = FUN_005218c0(&DAT_0056a23c,acStack_c20);
    FUN_00521a90(pcVar1,uVar8);
    return 0x99;
  }
  cVar4 = FUN_005247a0(acStack_c20,1);
  if (cVar4 == '\0') {
    bVar3 = false;
    if ((*(int *)(param_1 + 0x10c0) == 8) && (DVar5 = GetLastError(), DVar5 == 0x80090006)) {
      bVar3 = true;
    }
    GetLastError();
    uVar8 = *(undefined4 *)(param_1 + 0x10c0);
    pcVar11 = acStack_c20;
    DVar5 = GetLastError();
    uVar8 = FUN_005218c0(&DAT_0056a220,uVar8,DVar5,pcVar11);
    FUN_00521a90(pcVar1,uVar8);
    pvVar10 = CreateFileA(acStack_c20,0x80000000,3,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
    if (pvVar10 == (HANDLE)0xffffffff) {
      pcVar11 = acStack_c20;
      DVar5 = GetLastError();
      uVar8 = FUN_005218c0(&DAT_0056a208,DVar5,pcVar11);
      FUN_00521a90(pcVar1,uVar8);
    }
    else {
      DVar5 = GetFileSize(pvVar10,(LPDWORD)0x0);
      uVar8 = FUN_005218c0(&DAT_0056a1f8,DVar5);
      FUN_00521a90(pcVar1,uVar8);
      SetFilePointer(pvVar10,-4,(PLONG)0x0,2);
      uStack_d9c = 0;
      ReadFile(pvVar10,&uStack_d9c,4,&DStack_d8c,(LPOVERLAPPED)0x0);
      uVar8 = FUN_005218c0(&DAT_0056a1e8,uStack_d9c);
      FUN_00521a90(pcVar1,uVar8);
      CloseHandle(pvVar10);
    }
    if (bVar3) {
      if (((param_1[0x1131] != '\0') || (cVar4 = FUN_00523530(), cVar4 == '\0')) ||
         ((cVar4 = FUN_005247a0(acStack_c20,1), cVar4 == '\0' &&
          ((*(int *)(param_1 + 0x10c0) == 8 && (DVar5 = GetLastError(), DVar5 == 0x80090006)))))) {
        return 0x9b;
      }
      uVar8 = FUN_005218c0(&DAT_0056a1d0);
      FUN_00521a90(pcVar1,uVar8);
    }
  }
  FUN_00521a90(pcVar1,&DAT_0056a1cc);
  uVar8 = *(undefined4 *)(param_1 + 0x113c);
  p_Var19 = a_Stack_d88;
  for (iVar6 = 0x11; iVar6 != 0; iVar6 = iVar6 + -1) {
    p_Var19->cb = 0;
    p_Var19 = (_STARTUPINFOA *)&p_Var19->lpReserved;
  }
  a_Stack_d88[0].cb = 0x44;
  pCVar12 = (LPCSTR)FUN_005218c0(&DAT_0056a1bc,uStack_da0,param_1 + 0x10c8,uVar8);
  wsprintfA(aCStack_a18,pCVar12);
  BVar7 = CreateProcessA(acStack_c20,aCStack_a18,(LPSECURITY_ATTRIBUTES)0x0,
                         (LPSECURITY_ATTRIBUTES)0x0,1,0,(LPVOID)0x0,(LPCSTR)0x0,a_Stack_d88,
                         (LPPROCESS_INFORMATION)&stack0xfffff250);
  if (BVar7 == 0) {
    pCVar20 = aCStack_a18;
    DVar5 = GetLastError();
    uVar8 = FUN_005218c0(&DAT_0056a194,acStack_c20,DVar5,pCVar20);
    FUN_00521a90(pcVar1,uVar8);
    DAT_005b158c = 2;
    return 0xaa;
  }
  FUN_00521a90(pcVar1,&DAT_0056a190);
  WaitForSingleObject((HANDLE)0x0,0xffffffff);
  FUN_00521a90(pcVar1,&DAT_0056a18c);
  GetExitCodeProcess((HANDLE)0x0,(LPDWORD)&stack0xfffff24c);
  FUN_00521a90(pcVar1,&DAT_0056a188);
  CloseHandle((HANDLE)0x0);
  CloseHandle((HANDLE)0x0);
  FUN_00521a90(pcVar1,s_g6__gg_ret___d_0056a178,0);
  uVar8 = FUN_005218c0(&DAT_0056a160,0);
  FUN_00521a90(pcVar1,uVar8);
  return 0;
}

