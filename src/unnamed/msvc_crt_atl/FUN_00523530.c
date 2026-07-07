/* FUN_00523530 - 0x00523530 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00523530(void)

{
  char cVar1;
  LPCSTR pCVar2;
  LSTATUS LVar3;
  undefined4 uVar4;
  char *pcVar5;
  HANDLE hFile;
  HMODULE hModule;
  FARPROC pFVar6;
  void *_Memory;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  char *pcVar11;
  char *pcVar12;
  undefined *puVar13;
  LPDWORD pDVar14;
  DWORD DVar15;
  LPDWORD pDVar16;
  DWORD dwType;
  REGSAM RVar17;
  BYTE *pBVar18;
  HKEY *ppHVar19;
  DWORD *pDVar20;
  CHAR *pCVar21;
  DWORD cbData;
  BYTE aBStack_2b0 [136];
  HKEY local_228;
  DWORD local_224;
  FARPROC local_220;
  DWORD local_21c;
  FARPROC local_218;
  undefined4 local_214;
  int *piStack_210;
  BYTE local_208;
  undefined1 uStack_207;
  undefined1 uStack_206;
  undefined1 uStack_205;
  CHAR local_104 [260];
  
  ppHVar19 = &local_228;
  uVar10 = 0;
  RVar17 = 1;
  DVar15 = 0;
  pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056adc4);
  LVar3 = RegOpenKeyExA((HKEY)&DAT_80000002,pCVar2,DVar15,RVar17,ppHVar19);
  if (LVar3 == 0) {
    pDVar20 = &local_224;
    pBVar18 = &local_208;
    pDVar16 = (LPDWORD)0x0;
    pDVar14 = (LPDWORD)0x0;
    local_224 = 0x104;
    pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056adb8);
    LVar3 = RegQueryValueExA(local_228,pCVar2,pDVar14,pDVar16,pBVar18,pDVar20);
    if ((LVar3 == 0) && (DAT_005b15ac != 0)) {
      uVar4 = FUN_005218c0(&DAT_0056ada4,&local_208);
      FUN_00521a90(DAT_005b15ac + 0x24,uVar4);
    }
  }
  RegCloseKey(local_228);
  ppHVar19 = &local_228;
  RVar17 = 3;
  DVar15 = 0;
  pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056ad40);
  LVar3 = RegOpenKeyExA((HKEY)&DAT_80000002,pCVar2,DVar15,RVar17,ppHVar19);
  if (LVar3 == 0) {
    pDVar20 = &local_224;
    pBVar18 = &local_208;
    pDVar16 = (LPDWORD)0x0;
    pDVar14 = (LPDWORD)0x0;
    local_224 = 0x104;
    pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056ad30);
    LVar3 = RegQueryValueExA(local_228,pCVar2,pDVar14,pDVar16,pBVar18,pDVar20);
    if ((LVar3 == 0) && (DAT_005b15ac != 0)) {
      uVar4 = FUN_005218c0(&DAT_0056ad0c,local_208,uStack_207,uStack_206,uStack_205);
      FUN_00521a90(DAT_005b15ac + 0x24,uVar4);
    }
    GetSystemDirectoryA(local_104,0x104);
    pcVar5 = (char *)FUN_005218c0(&DAT_0056acf8);
    uVar7 = 0xffffffff;
    do {
      pcVar12 = pcVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar12 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar12;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar8 = -1;
    pcVar5 = local_104;
    do {
      pcVar11 = pcVar5;
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      pcVar11 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar11;
    } while (cVar1 != '\0');
    pcVar5 = pcVar12 + -uVar7;
    pcVar12 = pcVar11 + -1;
    for (uVar9 = uVar7 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar12 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar12 = pcVar12 + 1;
    }
    local_21c = 0;
    hFile = CreateFileA(local_104,0x80000000,3,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
    if (hFile == (HANDLE)0xffffffff) {
      if (DAT_005b15ac != 0) {
        pCVar21 = local_104;
        DVar15 = GetLastError();
        uVar4 = FUN_005218c0(&DAT_0056a208,DVar15,pCVar21);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar4);
      }
    }
    else {
      local_21c = GetFileSize(hFile,(LPDWORD)0x0);
      if (DAT_005b15ac != 0) {
        uVar4 = FUN_005218c0(&DAT_0056a1f8,local_21c);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar4);
      }
      CloseHandle(hFile);
    }
    pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056ace8);
    hModule = LoadLibraryA(pCVar2);
    if (hModule != (HMODULE)0x0) {
      pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056accc);
      pFVar6 = GetProcAddress(hModule,pCVar2);
      pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056acb4);
      local_220 = GetProcAddress(hModule,pCVar2);
      pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056aca0);
      local_218 = GetProcAddress(hModule,pCVar2);
      if (((pFVar6 != (FARPROC)0x0) && (local_220 != (FARPROC)0x0)) && (local_218 != (FARPROC)0x0))
      {
        uVar7 = (*pFVar6)(local_104,&local_214);
        if (uVar7 != 0) {
          _Memory = operator_new(uVar7);
          (*local_220)(local_104,local_214,uVar7,_Memory);
          (*(code *)local_228)(_Memory,&DAT_0056a3bc,&local_220,&local_21c);
          if ((*piStack_210 == -0x110fb43) && (DAT_005b15ac != 0)) {
            uVar4 = FUN_005218c0(&DAT_0056ac88,(uint)piStack_210[2] >> 0x10,(short)piStack_210[2],
                                 (uint)piStack_210[3] >> 0x10,(short)piStack_210[3]);
            FUN_00521a90(DAT_005b15ac + 0x24,uVar4);
          }
          _free(_Memory);
        }
      }
      FreeLibrary(hModule);
    }
    if (local_21c == 0x18d10) {
      if (DAT_005b15ac != 0) {
        uVar10 = FUN_005218c0(&DAT_0056ac6c);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar10);
      }
      aBStack_2b0[1] = 199;
      aBStack_2b0[0x11] = 199;
      aBStack_2b0[0x33] = 0xf2;
      aBStack_2b0[0x26] = 0x16;
      aBStack_2b0[0x37] = 0xf2;
      aBStack_2b0[0x44] = 0x16;
      aBStack_2b0[0] = '*';
      aBStack_2b0[2] = 0xe;
      aBStack_2b0[3] = 0x10;
      aBStack_2b0[4] = 6;
      aBStack_2b0[5] = 0xbe;
      aBStack_2b0[6] = 0xa7;
      aBStack_2b0[7] = 0xcd;
      aBStack_2b0[8] = 0xf5;
      aBStack_2b0[9] = 0xfa;
      aBStack_2b0[10] = 0x66;
      aBStack_2b0[0xb] = 0xf;
      aBStack_2b0[0xc] = 0x86;
      aBStack_2b0[0xd] = 0xa3;
      aBStack_2b0[0xe] = 0x8a;
      aBStack_2b0[0xf] = 0x41;
      aBStack_2b0[0x10] = 0x58;
      aBStack_2b0[0x12] = 0xaf;
      aBStack_2b0[0x13] = 0x6e;
      aBStack_2b0[0x14] = 0xf5;
      aBStack_2b0[0x15] = 0xc1;
      aBStack_2b0[0x16] = 0x92;
      aBStack_2b0[0x17] = 0x3d;
      aBStack_2b0[0x18] = 0xf5;
      aBStack_2b0[0x19] = 0x56;
      aBStack_2b0[0x1a] = 0xa8;
      aBStack_2b0[0x1b] = 0x81;
      aBStack_2b0[0x1c] = 0x48;
      aBStack_2b0[0x1d] = 0x2e;
      aBStack_2b0[0x1e] = 0x89;
      aBStack_2b0[0x1f] = 0x7c;
      aBStack_2b0[0x20] = 4;
      aBStack_2b0[0x21] = 0x36;
      aBStack_2b0[0x22] = 0x53;
      aBStack_2b0[0x23] = 0xe3;
      aBStack_2b0[0x24] = 100;
      aBStack_2b0[0x25] = 0x79;
      aBStack_2b0[0x27] = 0x34;
      aBStack_2b0[0x28] = 0x7d;
      aBStack_2b0[0x29] = 0xe8;
      aBStack_2b0[0x2a] = 0xb0;
      aBStack_2b0[0x2b] = 0xae;
      aBStack_2b0[0x2c] = 0xd7;
      aBStack_2b0[0x2d] = 0x3c;
      aBStack_2b0[0x2e] = 0xc5;
      aBStack_2b0[0x2f] = 0xeb;
      aBStack_2b0[0x30] = 0x7a;
      aBStack_2b0[0x31] = 0x25;
      aBStack_2b0[0x32] = 0x2d;
      aBStack_2b0[0x34] = 0xb8;
      aBStack_2b0[0x35] = 0xe4;
      aBStack_2b0[0x36] = 0xf4;
      aBStack_2b0[0x38] = 0xcd;
      aBStack_2b0[0x39] = 0x95;
      aBStack_2b0[0x3a] = 0xb;
      aBStack_2b0[0x3b] = 0xdd;
      aBStack_2b0[0x3c] = 0x4f;
      aBStack_2b0[0x3d] = 10;
      aBStack_2b0[0x3e] = 0x9f;
      aBStack_2b0[0x3f] = 0x27;
      aBStack_2b0[0x40] = 0x19;
      aBStack_2b0[0x41] = 0xb5;
      aBStack_2b0[0x42] = 0xf6;
      aBStack_2b0[0x43] = 0x52;
      aBStack_2b0[0x45] = 0x77;
      aBStack_2b0[0x46] = 1;
      aBStack_2b0[0x47] = 0x2c;
      aBStack_2b0[0x48] = 0xf6;
      aBStack_2b0[0x49] = 0xae;
      aBStack_2b0[0x4a] = 0x9a;
      aBStack_2b0[0x65] = 0xf5;
      aBStack_2b0[0x4b] = 0xd3;
      aBStack_2b0[0x4c] = 0x7f;
      aBStack_2b0[0x4d] = 0xbf;
      aBStack_2b0[0x4e] = 0x6a;
      aBStack_2b0[0x4f] = 0x22;
      aBStack_2b0[0x50] = 0x91;
      aBStack_2b0[0x51] = 0x6b;
      aBStack_2b0[0x52] = 0xf3;
      aBStack_2b0[0x53] = 0xdb;
      aBStack_2b0[0x54] = 0x93;
      aBStack_2b0[0x55] = 0xd;
      aBStack_2b0[0x56] = 0x1c;
      aBStack_2b0[0x57] = 0xd2;
      aBStack_2b0[0x58] = 0;
      aBStack_2b0[0x59] = 0xb5;
      aBStack_2b0[0x5a] = 0xb8;
      aBStack_2b0[0x5b] = 0x14;
      aBStack_2b0[0x5c] = 0x1c;
      aBStack_2b0[0x5d] = 0x3e;
      aBStack_2b0[0x5e] = 0x9e;
      aBStack_2b0[0x5f] = 0x94;
      aBStack_2b0[0x60] = 0x7b;
      aBStack_2b0[0x61] = 0xa9;
      aBStack_2b0[0x62] = 0x8e;
      aBStack_2b0[99] = 0xc6;
      aBStack_2b0[100] = 0x84;
      aBStack_2b0[0x66] = 0x2b;
      aBStack_2b0[0x67] = 0xfa;
      aBStack_2b0[0x68] = 0xb5;
      aBStack_2b0[0x69] = 0x95;
      aBStack_2b0[0x6a] = 0;
      aBStack_2b0[0x6b] = 0xa5;
      aBStack_2b0[0x6c] = 0x95;
      aBStack_2b0[0x6d] = 0xb2;
      aBStack_2b0[0x6e] = 0x65;
      aBStack_2b0[0x6f] = 0x8c;
      aBStack_2b0[0x70] = 0x31;
      aBStack_2b0[0x71] = 0x19;
      aBStack_2b0[0x72] = 0x77;
      aBStack_2b0[0x73] = 0;
      aBStack_2b0[0x74] = 0xcd;
      aBStack_2b0[0x75] = 0x5b;
      aBStack_2b0[0x76] = 0x4e;
      aBStack_2b0[0x77] = 0x92;
      aBStack_2b0[0x78] = 0x68;
      aBStack_2b0[0x79] = 0xe4;
      aBStack_2b0[0x7a] = 0x42;
      aBStack_2b0[0x7b] = 0x66;
      aBStack_2b0[0x7c] = 0x17;
      aBStack_2b0[0x7d] = 0xb5;
      aBStack_2b0[0x7e] = 0xd4;
      aBStack_2b0[0x7f] = 0x93;
      puVar13 = &DAT_0056ac5c;
    }
    else {
      if (local_21c != 0x17110) goto LAB_00523fa1;
      if (DAT_005b15ac != 0) {
        uVar10 = FUN_005218c0(&DAT_0056ac40);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar10);
      }
      aBStack_2b0[0x13] = 7;
      aBStack_2b0[0x28] = 7;
      aBStack_2b0[0x2f] = 7;
      aBStack_2b0[0] = '_';
      aBStack_2b0[1] = 0x71;
      aBStack_2b0[2] = 0x69;
      aBStack_2b0[3] = 0x53;
      aBStack_2b0[4] = 0x8a;
      aBStack_2b0[5] = 0x8e;
      aBStack_2b0[6] = 0x54;
      aBStack_2b0[7] = 0xac;
      aBStack_2b0[8] = 9;
      aBStack_2b0[9] = 0x3f;
      aBStack_2b0[10] = 0x65;
      aBStack_2b0[0xb] = 0x5a;
      aBStack_2b0[0xc] = 0x26;
      aBStack_2b0[0xd] = 0x8d;
      aBStack_2b0[0xe] = 0x77;
      aBStack_2b0[0xf] = 0x15;
      aBStack_2b0[0x10] = 0x9e;
      aBStack_2b0[0x11] = 0x68;
      aBStack_2b0[0x12] = 0xbb;
      aBStack_2b0[0x14] = 0xed;
      aBStack_2b0[0x15] = 0x8f;
      aBStack_2b0[0x16] = 0xf0;
      aBStack_2b0[0x17] = 0xb7;
      aBStack_2b0[0x18] = 0xf1;
      aBStack_2b0[0x19] = 0x99;
      aBStack_2b0[0x1a] = 5;
      aBStack_2b0[0x1b] = 0x15;
      aBStack_2b0[0x1c] = 0x80;
      aBStack_2b0[0x1d] = 100;
      aBStack_2b0[0x1e] = 0xa8;
      aBStack_2b0[0x1f] = 0xd8;
      aBStack_2b0[0x20] = 0x87;
      aBStack_2b0[0x21] = 0xc3;
      aBStack_2b0[0x22] = 0x58;
      aBStack_2b0[0x23] = 0xa9;
      aBStack_2b0[0x24] = 0xce;
      aBStack_2b0[0x25] = 0x26;
      aBStack_2b0[0x26] = 0xfe;
      aBStack_2b0[0x27] = 0xb3;
      aBStack_2b0[0x29] = 0xd7;
      aBStack_2b0[0x2a] = 0xa3;
      aBStack_2b0[0x2b] = 0x81;
      aBStack_2b0[0x2c] = 0xbe;
      aBStack_2b0[0x2d] = 0xb8;
      aBStack_2b0[0x2e] = 0x6e;
      aBStack_2b0[0x30] = 0x15;
      aBStack_2b0[0x31] = 0x68;
      aBStack_2b0[0x32] = 0x44;
      aBStack_2b0[0x33] = 0x17;
      aBStack_2b0[0x34] = 0xbe;
      aBStack_2b0[0x35] = 0x81;
      aBStack_2b0[0x36] = 0x80;
      aBStack_2b0[0x37] = 0x75;
      aBStack_2b0[0x38] = 0xa1;
      aBStack_2b0[0x39] = 0xdb;
      aBStack_2b0[0x3a] = 0xab;
      aBStack_2b0[0x3b] = 0x21;
      aBStack_2b0[0x3c] = 0xd1;
      aBStack_2b0[0x3d] = 0x1f;
      aBStack_2b0[0x3e] = 0xbc;
      aBStack_2b0[0x3f] = 0x9c;
      aBStack_2b0[0x40] = 0x1d;
      aBStack_2b0[0x41] = 0x49;
      aBStack_2b0[0x42] = 0xf0;
      aBStack_2b0[0x43] = 0xe5;
      aBStack_2b0[0x44] = 0xdd;
      aBStack_2b0[0x45] = 0x49;
      aBStack_2b0[0x46] = 0x7f;
      aBStack_2b0[0x47] = 0xb5;
      aBStack_2b0[0x48] = 0xe4;
      aBStack_2b0[0x49] = 9;
      aBStack_2b0[0x4a] = 0xf0;
      aBStack_2b0[0x4b] = 0x39;
      aBStack_2b0[0x4c] = 0x94;
      aBStack_2b0[0x5a] = 0x20;
      aBStack_2b0[0x7c] = 0x20;
      aBStack_2b0[0x4d] = 0x2a;
      aBStack_2b0[0x66] = 0x2a;
      aBStack_2b0[0x4e] = 0x6b;
      aBStack_2b0[0x4f] = 0x83;
      aBStack_2b0[0x50] = 0xf;
      aBStack_2b0[0x51] = 0xdb;
      aBStack_2b0[0x52] = 0x56;
      aBStack_2b0[0x53] = 0xe;
      aBStack_2b0[0x54] = 0xa3;
      aBStack_2b0[0x55] = 0x61;
      aBStack_2b0[0x56] = 0x9f;
      aBStack_2b0[0x57] = 0x12;
      aBStack_2b0[0x58] = 0xd4;
      aBStack_2b0[0x59] = 0xd7;
      aBStack_2b0[0x5b] = 0x90;
      aBStack_2b0[0x5c] = 0x54;
      aBStack_2b0[0x5d] = 0x9b;
      aBStack_2b0[0x5e] = 0xc6;
      aBStack_2b0[0x5f] = 0x99;
      aBStack_2b0[0x60] = 0xc;
      aBStack_2b0[0x61] = 0x44;
      aBStack_2b0[0x62] = 3;
      aBStack_2b0[99] = 0xd5;
      aBStack_2b0[100] = 0x1b;
      aBStack_2b0[0x65] = 0x9a;
      aBStack_2b0[0x67] = 0xa0;
      aBStack_2b0[0x68] = 0xa2;
      aBStack_2b0[0x69] = 0x8c;
      aBStack_2b0[0x6a] = 0x1c;
      aBStack_2b0[0x6b] = 0xf6;
      aBStack_2b0[0x6c] = 0x68;
      aBStack_2b0[0x6d] = 0xa5;
      aBStack_2b0[0x6e] = 0x57;
      aBStack_2b0[0x6f] = 0x2e;
      aBStack_2b0[0x70] = 0x11;
      aBStack_2b0[0x71] = 0x40;
      aBStack_2b0[0x72] = 0xa5;
      aBStack_2b0[0x73] = 0x8f;
      aBStack_2b0[0x74] = 0x77;
      aBStack_2b0[0x75] = 0x71;
      aBStack_2b0[0x76] = 0xec;
      aBStack_2b0[0x77] = 0x6a;
      aBStack_2b0[0x78] = 0x69;
      aBStack_2b0[0x79] = 0xa0;
      aBStack_2b0[0x7a] = 0xcb;
      aBStack_2b0[0x7b] = 0x1e;
      aBStack_2b0[0x7d] = 0x8e;
      aBStack_2b0[0x7e] = 0xe0;
      aBStack_2b0[0x7f] = 5;
      puVar13 = &DAT_0056ac30;
    }
    pBVar18 = aBStack_2b0;
    aBStack_2b0[0x87] = 0;
    aBStack_2b0[0x86] = 0;
    aBStack_2b0[0x85] = 0;
    aBStack_2b0[0x84] = 0;
    aBStack_2b0[0x83] = 0;
    aBStack_2b0[0x82] = 0;
    aBStack_2b0[0x81] = 0;
    aBStack_2b0[0x80] = 0;
    cbData = 0x88;
    dwType = 3;
    DVar15 = 0;
    pCVar2 = (LPCSTR)FUN_005218c0(puVar13);
    RegSetValueExA(local_228,pCVar2,DVar15,dwType,pBVar18,cbData);
    uVar10 = 1;
  }
LAB_00523fa1:
  RegCloseKey(local_228);
  return uVar10;
}

