/* FUN_005247a0 - 0x005247a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_005247a0(HCRYPTPROV *param_1,char *param_2,char param_3)

{
  HCRYPTPROV *pHVar1;
  HCRYPTKEY *phKey;
  HCRYPTHASH *phHash;
  HCRYPTPROV *pHVar2;
  HCRYPTPROV HVar3;
  HANDLE hFile;
  DWORD DVar4;
  void *lpBuffer;
  HCRYPTPROV *pHVar5;
  undefined4 *puVar6;
  BOOL BVar7;
  char *pcVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *puVar12;
  HCRYPTPROV *local_4;
  
  if (param_2 == (LPCSTR)0x0) {
    param_1[0x11] = 1;
    return 0;
  }
  if (*param_2 == '\0') {
    param_1[0x11] = 2;
    return 0;
  }
  local_4 = param_1;
  hFile = CreateFileA(param_2,0x80000000,3,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    param_1[0x11] = 3;
    return 0;
  }
  DVar4 = GetFileSize(hFile,(LPDWORD)0x0);
  param_1[9] = DVar4;
  if (DVar4 == 0xffffffff) {
    CloseHandle(hFile);
    param_1[0x11] = 0x21;
    return 0;
  }
  if ((void *)param_1[1] != (void *)0x0) {
    _free((void *)param_1[1]);
    param_1[1] = 0;
  }
  lpBuffer = _malloc(param_1[9]);
  param_1[1] = (HCRYPTPROV)lpBuffer;
  if (lpBuffer == (void *)0x0) {
    CloseHandle(hFile);
    param_1[0x11] = 4;
    return 0;
  }
  ReadFile(hFile,lpBuffer,param_1[9],(LPDWORD)&local_4,(LPOVERLAPPED)0x0);
  pHVar5 = (HCRYPTPROV *)param_1[9];
  if (local_4 != pHVar5) {
    CloseHandle(hFile);
    param_1[0x11] = 5;
    return 0;
  }
  pHVar1 = param_1 + 10;
  pHVar2 = (HCRYPTPROV *)((param_1[1] - 0x10) + (int)pHVar5);
  *pHVar1 = *pHVar2;
  param_1[0xb] = pHVar2[1];
  param_1[0xc] = pHVar2[2];
  param_1[0xd] = pHVar2[3];
  if ((*pHVar1 == 0x32812622) && (param_1[0xd] == 0x32812621)) {
    *(undefined1 *)(param_1 + 7) = 1;
    HVar3 = param_1[0xc] + 0x10 + param_1[0xb];
    param_1[0xe] = param_1[0xb];
    param_1[8] = HVar3;
    param_1[2] = (int)pHVar5 - HVar3;
  }
  else {
    *pHVar1 = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    pHVar5 = (HCRYPTPROV *)param_1[9];
    *(undefined1 *)(param_1 + 7) = 0;
    param_1[8] = 0;
    param_1[2] = (HCRYPTPROV)pHVar5;
    param_1[0xe] = 0;
  }
  if (pHVar5 < (HCRYPTPROV *)param_1[8]) {
    *(undefined1 *)(param_1 + 7) = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[2] = 0;
    param_1[0xe] = 0;
  }
  CloseHandle(hFile);
  if ((char)param_1[7] == '\0') {
    param_1[0x11] = 6;
    return 0;
  }
  param_1[6] = param_1[0xc];
  if ((void *)param_1[5] != (void *)0x0) {
    _free((void *)param_1[5]);
    param_1[5] = 0;
  }
  puVar6 = _malloc(param_1[6]);
  param_1[5] = (HCRYPTPROV)puVar6;
  if (puVar6 == (undefined4 *)0x0) {
    param_1[0x11] = 7;
    return 0;
  }
  uVar11 = param_1[6];
  puVar12 = (undefined4 *)(param_1[2] + param_1[1] + param_1[0xe]);
  for (uVar10 = uVar11 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
    *puVar6 = *puVar12;
    puVar12 = puVar12 + 1;
    puVar6 = puVar6 + 1;
  }
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined1 *)puVar6 = *(undefined1 *)puVar12;
    puVar12 = (undefined4 *)((int)puVar12 + 1);
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
  if ((*param_1 == 0) &&
     (BVar7 = CryptAcquireContextA
                        (param_1,(LPCSTR)0x0,s_Microsoft_Base_Cryptographic_Pro_0056ae50,1,
                         0xf0000000), BVar7 == 0)) {
    param_1[0x11] = 8;
    return 0;
  }
  phKey = param_1 + 4;
  if (param_1[4] != 0) {
    CryptDestroyKey(param_1[4]);
    *phKey = 0;
  }
  BVar7 = CryptImportKey(*param_1,&DAT_0056adf8,DAT_0056ae4c,0,0,phKey);
  if (BVar7 == 0) {
    DVar4 = GetLastError();
    if (DVar4 != 0x57) {
LAB_00524a54:
      param_1[0x11] = 9;
      return 0;
    }
    BVar7 = CryptAcquireContextA
                      (param_1,(LPCSTR)0x0,s_Microsoft_Base_Cryptographic_Pro_0056ae50,1,0xf0000000)
    ;
    if (BVar7 == 0) {
      param_1[0x11] = 0x62;
      return 0;
    }
    BVar7 = CryptImportKey(*param_1,&DAT_0056adf8,DAT_0056ae4c,0,0,phKey);
    if (BVar7 == 0) goto LAB_00524a54;
  }
  phHash = param_1 + 3;
  if (param_1[3] != 0) {
    CryptDestroyHash(param_1[3]);
    *phHash = 0;
  }
  BVar7 = CryptCreateHash(*param_1,0x8003,0,0,phHash);
  if (BVar7 == 0) {
    param_1[0x11] = 10;
    return 0;
  }
  BVar7 = CryptHashData(*phHash,(BYTE *)param_1[1],param_1[2] + param_1[0xe],0);
  if (BVar7 == 0) {
    param_1[0x11] = 0xb;
    return 0;
  }
  BVar7 = CryptVerifySignatureA(*phHash,(BYTE *)param_1[5],param_1[6],*phKey,(LPCSTR)0x0,0);
  if (BVar7 != 0) {
LAB_00524b44:
    if (param_3 != '\0') {
      pcVar8 = _strrchr(param_2,0x5c);
      if (pcVar8 != (char *)0x0) {
        param_2 = pcVar8 + 1;
      }
      iVar9 = __strnicmp(param_2,(char *)(param_1[2] + param_1[1]),param_1[0xe]);
      if (iVar9 != 0) {
        param_1[0x11] = 0xd;
        return 0;
      }
    }
    if ((void *)param_1[1] != (void *)0x0) {
      _free((void *)param_1[1]);
      param_1[1] = 0;
    }
    return 1;
  }
  DVar4 = GetLastError();
  if (DVar4 == 0x57) {
    BVar7 = CryptAcquireContextA
                      (param_1,(LPCSTR)0x0,s_Microsoft_Base_Cryptographic_Pro_0056ae50,1,0xf0000000)
    ;
    if (BVar7 == 0) {
      param_1[0x11] = 0x80;
      return 0;
    }
    BVar7 = CryptVerifySignatureA(*phHash,(BYTE *)param_1[5],param_1[6],*phKey,(LPCSTR)0x0,0);
    if (BVar7 != 0) goto LAB_00524b44;
  }
  param_1[0x11] = 0xc;
  return 0;
}

