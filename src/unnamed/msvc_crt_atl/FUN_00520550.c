/* FUN_00520550 - 0x00520550 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00520550(DWORD param_1)

{
  byte *_Dest;
  byte bVar1;
  undefined *puVar2;
  char *_Format;
  byte *pbVar3;
  uint uVar4;
  DWORD nNumberOfBytesToWrite;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *unaff_FS_OFFSET;
  DWORD local_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  puStack_8 = &LAB_005376f9;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 1;
  local_10 = param_1;
  FUN_00524730();
  local_4 = local_4 & 0xffffff00;
  thunk_FUN_00524360();
  puVar6 = (undefined4 *)(param_1 + 0x24);
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x24) != -1) {
    GetLocalTime((LPSYSTEMTIME)(param_1 + 0x1040));
    if ((*(uint *)(param_1 + 0x1058) == 0) ||
       (puVar2 = &DAT_00569e0c, *(uint *)(param_1 + 0x105c) <= *(uint *)(param_1 + 0x1058))) {
      puVar2 = &DAT_005b15d4;
    }
    _Dest = (byte *)(param_1 + 0x40);
    _Format = (char *)FUN_005218c0(&DAT_00569db4,((LPSYSTEMTIME)(param_1 + 0x1040))->wYear,
                                   *(undefined2 *)(param_1 + 0x1042),
                                   *(undefined2 *)(param_1 + 0x1046),
                                   *(undefined2 *)(param_1 + 0x1048),
                                   *(undefined2 *)(param_1 + 0x104a),
                                   *(undefined2 *)(param_1 + 0x104c),
                                   *(undefined2 *)(param_1 + 0x104e),puVar2);
    _sprintf((char *)_Dest,_Format);
    uVar4 = 0xffffffff;
    pbVar3 = _Dest;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      bVar1 = *pbVar3;
      pbVar3 = pbVar3 + 1;
    } while (bVar1 != 0);
    nNumberOfBytesToWrite = ~uVar4 - 1;
    if (*(int *)(param_1 + 0x1054) == 0) {
      if (0 < (int)nNumberOfBytesToWrite) {
        pbVar3 = _Dest;
        do {
          iVar5 = *(int *)(param_1 + 0x1050) * 3 + 1;
          *(int *)(param_1 + 0x1050) = iVar5;
          *pbVar3 = *pbVar3 ^ (char)iVar5 + 0x46U;
          pbVar3 = pbVar3 + 1;
        } while ((int)(pbVar3 + (-0x1c - (int)puVar6)) < (int)nNumberOfBytesToWrite);
      }
    }
    else if (0 < (int)nNumberOfBytesToWrite) {
      pbVar3 = _Dest;
      do {
        iVar5 = *(int *)(param_1 + 0x1054) + 2;
        *(int *)(param_1 + 0x1054) = iVar5;
        *pbVar3 = *pbVar3 ^ (char)iVar5 + 0x43U;
        pbVar3 = pbVar3 + 1;
      } while ((int)(pbVar3 + (-0x1c - (int)puVar6)) < (int)nNumberOfBytesToWrite);
    }
    if (*(int *)(param_1 + 0x1058) != 999) {
      WriteFile((HANDLE)*puVar6,_Dest,nNumberOfBytesToWrite,&local_10,(LPOVERLAPPED)0x0);
    }
    SetEndOfFile((HANDLE)*puVar6);
    CloseHandle((HANDLE)*puVar6);
    *puVar6 = 0xffffffff;
    DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x28));
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

