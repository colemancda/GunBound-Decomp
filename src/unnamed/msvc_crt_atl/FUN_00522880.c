/* FUN_00522880 - 0x00522880 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00522880(int param_1)

{
  int *piVar1;
  byte *_Dest;
  byte bVar2;
  bool bVar3;
  FARPROC pFVar4;
  LPCSTR pCVar5;
  int iVar6;
  char *pcVar7;
  byte *pbVar8;
  HMODULE hModule;
  FARPROC pFVar9;
  FARPROC pFVar10;
  code *pcVar11;
  undefined4 uVar12;
  int iVar13;
  uint uVar14;
  uint unaff_ESI;
  uint unaff_EDI;
  undefined *puVar15;
  DWORD DVar16;
  LPSTR lpClass;
  DWORD DVar17;
  int iVar18;
  REGSAM samDesired;
  LPDWORD pDVar19;
  DWORD dwType;
  LPSECURITY_ATTRIBUTES lpSecurityAttributes;
  LPDWORD pDVar20;
  BYTE *lpData;
  DWORD *pDVar21;
  WORD WVar22;
  HKEY *ppHVar23;
  BYTE *pBVar24;
  WORD WVar25;
  DWORD local_2b8;
  HKEY local_2b4;
  HKEY local_2b0;
  FARPROC apFStack_2ac [2];
  FARPROC local_2a4;
  DWORD local_29c [5];
  BYTE aBStack_288 [4];
  BYTE local_284 [64];
  CHAR local_244 [8];
  CHAR aCStack_23c [128];
  CHAR aCStack_1bc [128];
  char acStack_13c [316];
  
  piVar1 = (int *)(param_1 + 0x24);
  local_2a4 = (FARPROC)param_1;
  FUN_005218c0();
  FUN_00521a90();
  pDVar21 = local_29c;
  ppHVar23 = &local_2b0;
  local_2b4 = (HKEY)0x0;
  lpSecurityAttributes = (LPSECURITY_ATTRIBUTES)0x0;
  samDesired = 0xf003f;
  DVar17 = 0;
  lpClass = (LPSTR)0x0;
  DVar16 = 0;
  bVar3 = false;
  pCVar5 = (LPCSTR)FUN_005218c0(&DAT_0056a924);
  RegCreateKeyExA((HKEY)&DAT_80000001,pCVar5,DVar16,lpClass,DVar17,samDesired,lpSecurityAttributes,
                  ppHVar23,pDVar21);
  if (local_29c[0] == 2) {
    pDVar21 = &local_2b8;
    pBVar24 = local_284;
    pDVar20 = (LPDWORD)0x0;
    pDVar19 = (LPDWORD)0x0;
    local_2b8 = 0x40;
    pCVar5 = (LPCSTR)FUN_005218c0();
    RegQueryValueExA(local_2b0,pCVar5,pDVar19,pDVar20,pBVar24,pDVar21);
    wsprintfA(local_244,(LPCSTR)&PTR_DAT_0056a90c);
    bVar3 = false;
    if ((local_2b8 != 0) && (iVar6 = lstrcmp(), iVar6 == 0)) {
      bVar3 = true;
    }
    pDVar21 = &local_2b8;
    ppHVar23 = &local_2b4;
    pDVar20 = (LPDWORD)0x0;
    pDVar19 = (LPDWORD)0x0;
    local_2b8 = 4;
    pCVar5 = (LPCSTR)FUN_005218c0();
    RegQueryValueExA(local_2b0,pCVar5,pDVar19,pDVar20,(LPBYTE)ppHVar23,pDVar21);
  }
  wsprintfA((LPSTR)local_284,(LPCSTR)&PTR_DAT_0056a90c);
  pBVar24 = local_284;
  iVar6 = lstrlen();
  DVar16 = iVar6 + 1;
  lpData = aBStack_288;
  dwType = 1;
  DVar17 = 0;
  pCVar5 = (LPCSTR)FUN_005218c0();
  RegSetValueExA(local_2b4,pCVar5,DVar17,dwType,lpData,DVar16);
  if (bVar3) {
    local_2b8 = local_2b8 + 1;
  }
  else {
    local_2b8 = 0;
  }
  pDVar21 = &local_2b8;
  WVar22 = 4;
  WVar25 = 0;
  DVar17 = 4;
  DVar16 = 0;
  pCVar5 = (LPCSTR)FUN_005218c0();
  RegSetValueExA(local_2b4,pCVar5,DVar16,DVar17,(BYTE *)pDVar21,CONCAT22(WVar25,WVar22));
  RegCloseKey(local_2b4);
  if (((local_2b8 != 1) && (local_2b8 < 6)) && ((!bVar3 || (DAT_005b158c < 9)))) {
    FUN_005218c0();
    FUN_00521a90();
    if (*piVar1 != -1) {
      GetLocalTime((LPSYSTEMTIME)(param_1 + 0x1040));
      _Dest = (byte *)(param_1 + 0x40);
      pcVar7 = (char *)FUN_005218c0(&DAT_00569db4,((LPSYSTEMTIME)(param_1 + 0x1040))->wYear,
                                    *(undefined2 *)(param_1 + 0x1042));
      _sprintf((char *)_Dest,pcVar7);
      uVar14 = 0xffffffff;
      pbVar8 = _Dest;
      do {
        if (uVar14 == 0) break;
        uVar14 = uVar14 - 1;
        bVar2 = *pbVar8;
        pbVar8 = pbVar8 + 1;
      } while (bVar2 != 0);
      DVar16 = ~uVar14 - 1;
      if (*(int *)(param_1 + 0x1054) == 0) {
        if (0 < (int)DVar16) {
          pbVar8 = _Dest;
          do {
            iVar6 = *(int *)(param_1 + 0x1050) * 3 + 1;
            *(int *)(param_1 + 0x1050) = iVar6;
            *pbVar8 = *pbVar8 ^ (char)iVar6 + 0x46U;
            pbVar8 = pbVar8 + 1;
          } while ((int)(pbVar8 + (-0x1c - (int)piVar1)) < (int)DVar16);
        }
      }
      else if (0 < (int)DVar16) {
        pbVar8 = _Dest;
        do {
          iVar6 = *(int *)(param_1 + 0x1054) + 2;
          *(int *)(param_1 + 0x1054) = iVar6;
          *pbVar8 = *pbVar8 ^ (char)iVar6 + 0x43U;
          pbVar8 = pbVar8 + 1;
        } while ((int)(pbVar8 + (-0x1c - (int)piVar1)) < (int)DVar16);
      }
      if (*(int *)(param_1 + 0x1058) != 999) {
        WriteFile((HANDLE)*piVar1,_Dest,DVar16,(LPDWORD)apFStack_2ac,(LPOVERLAPPED)0x0);
      }
      SetEndOfFile((HANDLE)*piVar1);
      CloseHandle((HANDLE)*piVar1);
      *piVar1 = -1;
      DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x28));
    }
    pCVar5 = (LPCSTR)FUN_005218c0();
    hModule = LoadLibraryA(pCVar5);
    if (hModule != (HMODULE)0x0) {
      pCVar5 = (LPCSTR)FUN_005218c0();
      pFVar9 = GetProcAddress(hModule,pCVar5);
      pCVar5 = (LPCSTR)FUN_005218c0();
      local_2a4 = GetProcAddress(hModule,pCVar5);
      pCVar5 = (LPCSTR)FUN_005218c0();
      pFVar10 = GetProcAddress(hModule,pCVar5);
      pCVar5 = (LPCSTR)FUN_005218c0();
      apFStack_2ac[0] = GetProcAddress(hModule,pCVar5);
      pFVar4 = local_2a4;
      if ((((pFVar9 != (FARPROC)0x0) && (local_2a4 != (FARPROC)0x0)) && (pFVar10 != (FARPROC)0x0))
         && (apFStack_2ac[0] != (FARPROC)0x0)) {
        WVar22 = 0;
        WVar25 = 0;
        iVar18 = 0;
        pcVar11 = (code *)FUN_005218c0();
        iVar6 = (*pFVar9)();
        if (iVar6 != 0) {
          uVar12 = FUN_005218c0(&DAT_0056a858,1,0);
          uVar12 = FUN_005218c0(&DAT_0056a84c,uVar12);
          uVar12 = FUN_005218c0(&DAT_0056a838,0x15,uVar12);
          iVar13 = (*pFVar4)(iVar6,uVar12);
          if (iVar13 == 0) {
            (*pFVar10)(iVar6);
            return;
          }
          aCStack_1bc[0] = '\0';
          GetComputerNameA(aCStack_1bc,(LPDWORD)&stack0xfffffd1c);
          aCStack_23c[0] = '\0';
          GetUserNameA(aCStack_23c,(LPDWORD)&stack0xfffffd1c);
          GetLocalTime((LPSYSTEMTIME)&stack0xfffffd30);
          if (DAT_005b158c == 1) {
            puVar15 = &DAT_0056a82c;
          }
          else if (DAT_005b158c == 2) {
            puVar15 = &DAT_0056a820;
          }
          else if (DAT_005b158c == 3) {
            puVar15 = &DAT_0056a818;
          }
          else if (DAT_005b158c == 4) {
            puVar15 = &DAT_0056a80c;
          }
          else if (DAT_005b158c == 5) {
            puVar15 = &DAT_0056a800;
          }
          else if (DAT_005b158c == 6) {
            puVar15 = &DAT_0056a7f0;
          }
          else if (DAT_005b158c == 7) {
            puVar15 = &DAT_0056a7e4;
          }
          else if (DAT_005b158c == 8) {
            puVar15 = &DAT_0056a7d8;
          }
          else if (DAT_005b158c == 9) {
            puVar15 = &DAT_0056a7cc;
          }
          else {
            puVar15 = &DAT_0056a7c4;
          }
          uVar12 = FUN_005218c0(puVar15);
          pcVar7 = (char *)FUN_005218c0(&DAT_0056a768,iVar18 + 0x10c8,5,uVar12,
                                        *(undefined4 *)(DAT_005b15ac + 0x10),aCStack_1bc,aCStack_23c
                                        ,iVar18 + 0x10f0,WVar22,WVar25,(uint)pBVar24 >> 0x10,
                                        unaff_EDI & 0xffff,unaff_EDI >> 0x10,unaff_ESI & 0xffff,
                                        unaff_ESI >> 0x10);
          _sprintf(acStack_13c,pcVar7);
          (*pcVar11)(iVar13,&DAT_005b147c,acStack_13c,0x4000002,0);
          GetLastError();
          (*pFVar10)(iVar6);
          (*pFVar10)(iVar13);
          FreeLibrary(hModule);
        }
      }
    }
  }
  return;
}

