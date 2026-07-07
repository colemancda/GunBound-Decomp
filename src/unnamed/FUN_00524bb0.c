/* FUN_00524bb0 - 0x00524bb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall
FUN_00524bb0(HCRYPTPROV *param_1,LPCSTR param_2,undefined4 *param_3,uint param_4,BYTE *param_5)

{
  HCRYPTPROV *pHVar1;
  HCRYPTHASH *phHash;
  HCRYPTKEY *phKey;
  HCRYPTPROV *pHVar2;
  HCRYPTPROV HVar3;
  BYTE BVar4;
  HANDLE hFile;
  DWORD DVar5;
  void *lpBuffer;
  LPCSTR pCVar6;
  BOOL BVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  BYTE *pBVar11;
  undefined4 *puVar12;
  HCRYPTPROV *local_4;
  
  local_4 = param_1;
  hFile = CreateFileA(param_2,0x80000000,3,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    param_1[0x11] = 1;
    return 0;
  }
  DVar5 = GetFileSize(hFile,(LPDWORD)0x0);
  param_1[9] = DVar5;
  if (DVar5 == 0xffffffff) {
    CloseHandle(hFile);
    param_1[0x11] = 0xb;
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
    param_1[0x11] = 2;
    return 0;
  }
  ReadFile(hFile,lpBuffer,param_1[9],(LPDWORD)&param_2,(LPOVERLAPPED)0x0);
  pCVar6 = (LPCSTR)param_1[9];
  if (param_2 != pCVar6) {
    CloseHandle(hFile);
    param_1[0x11] = 3;
    return 0;
  }
  pHVar1 = param_1 + 10;
  pHVar2 = (HCRYPTPROV *)(pCVar6 + (param_1[1] - 0x10));
  *pHVar1 = *pHVar2;
  param_1[0xb] = pHVar2[1];
  param_1[0xc] = pHVar2[2];
  param_1[0xd] = pHVar2[3];
  if ((*pHVar1 == 0x32812622) && (param_1[0xd] == 0x32812621)) {
    *(undefined1 *)(param_1 + 7) = 1;
    HVar3 = param_1[0xc] + 0x10 + param_1[0xb];
    param_1[0xe] = param_1[0xb];
    param_1[8] = HVar3;
    param_1[2] = (int)pCVar6 - HVar3;
  }
  else {
    *pHVar1 = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    *(undefined1 *)(param_1 + 7) = 0;
    pCVar6 = (LPCSTR)param_1[9];
    param_1[8] = 0;
    param_1[2] = (HCRYPTPROV)pCVar6;
    param_1[0xe] = 0;
  }
  if (pCVar6 < (LPCSTR)param_1[8]) {
    *(undefined1 *)(param_1 + 7) = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[2] = 0;
    param_1[0xe] = 0;
  }
  CloseHandle(hFile);
  if (*param_1 == 0) {
    BVar7 = CryptAcquireContextA
                      (param_1,(LPCSTR)0x0,s_Microsoft_Base_Cryptographic_Pro_0056ae50,1,0xf0000000)
    ;
    if (BVar7 == 0) {
      param_1[0x11] = 4;
      return 0;
    }
  }
  phHash = param_1 + 0x10;
  if (param_1[0x10] != 0) {
    CryptDestroyHash(param_1[0x10]);
    *phHash = 0;
  }
  BVar7 = CryptCreateHash(*param_1,0x8003,0,0,phHash);
  if (BVar7 == 0) {
    param_1[0x11] = 5;
    return 0;
  }
  uVar8 = 0xffffffff;
  pBVar11 = param_5;
  do {
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    BVar4 = *pBVar11;
    pBVar11 = pBVar11 + 1;
  } while (BVar4 != '\0');
  BVar7 = CryptHashData(*phHash,param_5,~uVar8 - 1,0);
  if (BVar7 == 0) {
    param_1[0x11] = 6;
    return 0;
  }
  phKey = param_1 + 0xf;
  if (param_1[0xf] != 0) {
    CryptDestroyKey(param_1[0xf]);
    *phKey = 0;
  }
  BVar7 = CryptDeriveKey(*param_1,0x6801,*phHash,0,phKey);
  if (BVar7 == 0) {
    param_1[0x11] = 7;
    return 0;
  }
  local_4 = (HCRYPTPROV *)param_1[2];
  BVar7 = CryptDecrypt(*phKey,0,1,0,(BYTE *)param_1[1],(DWORD *)&local_4);
  if (BVar7 == 0) {
    param_1[0x11] = 8;
    return 0;
  }
  uVar8 = param_4;
  if (param_1[2] < param_4) {
    uVar8 = param_1[2];
  }
  puVar10 = (undefined4 *)param_1[1];
  puVar12 = param_3;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *puVar12 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar12 = puVar12 + 1;
  }
  for (uVar9 = uVar8 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined1 *)puVar12 = *(undefined1 *)puVar10;
    puVar10 = (undefined4 *)((int)puVar10 + 1);
    puVar12 = (undefined4 *)((int)puVar12 + 1);
  }
  *(undefined1 *)((int)param_3 + uVar8) = 0;
  if ((void *)param_1[1] != (void *)0x0) {
    _free((void *)param_1[1]);
    param_1[1] = 0;
  }
  return 1;
}

