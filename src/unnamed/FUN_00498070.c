/* FUN_00498070 - 0x00498070 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00498070(int *param_1)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  undefined4 *unaff_FS_OFFSET;
  uint local_8c8;
  int local_8c4 [2];
  int local_8bc [2];
  undefined *local_8b4;
  uint local_8b0;
  int local_8ac;
  int local_8a8 [2];
  int local_8a0;
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005397f2;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_8b4 = &DAT_00989680;
  local_8b0 = 0xffffffff;
  local_8c8 = 0;
  do {
    iVar3 = GetPlayerRecordBySlot(g_clientContext);
    if ((iVar3 != 0) && (cVar2 = PeekPacketChecksumBool(), cVar2 != '\x01')) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 != '\0') {
        iVar4 = iVar4 / 5 + iVar4;
      }
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 != '\0') {
        iVar4 = iVar4 - iVar4 / 2;
      }
      local_8ac = iVar4 * iVar4;
      local_8bc[0] = iVar3 + 0x90c;
      EncodeChecksumPairDiff(param_1 + 0x10,local_678,local_8bc[0]);
      local_4 = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_8c4[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if ((*(int *)(local_678 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_8a8);
      }
      EncodeChecksumPairDiff(param_1 + 0x99,local_454,iVar3 + 0xb30);
      local_4 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if ((*(int *)(local_454 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_8a8);
      }
      puVar5 = (undefined *)(iVar3 * iVar3 + local_8c4[0] * local_8c4[0]);
      if (((int)puVar5 < local_8ac) && ((int)puVar5 < (int)local_8b4)) {
        local_8b0 = local_8c8;
        local_8b4 = puVar5;
        EncodeChecksumPairDiff(param_1 + 0x10,local_89c,local_8bc[0]);
        local_4 = 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        local_8a0 = iVar3;
        if ((*(int *)(local_89c + 0x14)) != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_8a8);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        param_1[0xff0] = iVar3;
      }
    }
    local_8c8 = local_8c8 + 1;
  } while ((int)local_8c8 < 8);
  local_8c8 = 0;
  do {
    iVar3 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar1 = *(uint *)(iVar3 + 4);
    while (uVar1 < 0x186a7) {
      if (uVar1 == 0x186a6) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar1 = *(uint *)(iVar3 + 8);
        if (uVar1 <= local_8c8) goto LAB_00498381;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
    }
LAB_00498629:
    local_8c8 = local_8c8 + 1;
    if (7 < (int)local_8c8) {
      if (local_8b0 == 0xffffffff) {
        if (param_1[9] != 0) {
          (**(code **)(*param_1 + 4))(s_normal_00552230);
        }
      }
      else {
        if (param_1[9] != 1) {
          (**(code **)(*param_1 + 4))(s_active_00551e58);
        }
        param_1[0xfea] = (uint)(local_8a0 < 0);
      }
      *unaff_FS_OFFSET = local_c;
      return;
    }
  } while( true );
LAB_00498381:
  if (uVar1 != local_8c8) goto code_r0x00498383;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8ac = iVar4 * iVar4;
  EncodeChecksumPairDiff(param_1 + 0x10,local_89c,iVar3 + 0x25c);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8a8[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = (*(int *)(local_89c + 0x14));
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    local_8bc[0] = (*(int *)(local_89c + 0x14)) << 4;
    local_8c4[0] = 0x10;
    do {
      iVar6 = _rand();
      *(char *)(local_8bc[0] + DAT_0079376c) = (char)iVar6;
      local_8bc[0] = local_8bc[0] + 1;
      local_8c4[0] = local_8c4[0] + -1;
    } while (local_8c4[0] != 0);
    local_8c4[0] = iVar4;
    TreeLowerBound(local_8bc);
  }
  EncodeChecksumPairDiff(param_1 + 0x99,local_678,iVar3 + 0x480);
  local_4 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_8bc[0] = (*(int *)(local_678 + 0x14));
  if ((*(int *)(local_678 + 0x14)) != 0) {
    iVar6 = (*(int *)(local_678 + 0x14)) << 4;
    local_8c4[0] = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar7;
      iVar6 = iVar6 + 1;
      local_8c4[0] = local_8c4[0] + -1;
    } while (local_8c4[0] != 0);
    local_8c4[0] = local_8bc[0];
    TreeLowerBound(local_8bc);
  }
  puVar5 = (undefined *)(iVar4 * iVar4 + local_8a8[0] * local_8a8[0]);
  if (((int)puVar5 < local_8ac) && ((int)puVar5 < (int)local_8b4)) {
    local_8b0 = local_8c8;
    local_8b4 = puVar5;
    EncodeChecksumPairDiff(param_1 + 0x10,local_230,iVar3 + 0x25c);
    local_4 = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = (*(int *)(local_230 + 0x14));
    local_4 = 0xffffffff;
    local_8a0 = iVar4;
    if ((*(int *)(local_230 + 0x14)) != 0) {
      iVar4 = (*(int *)(local_230 + 0x14)) << 4;
      local_8c4[0] = 0x10;
      do {
        iVar6 = _rand();
        *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
        iVar4 = iVar4 + 1;
        local_8c4[0] = local_8c4[0] + -1;
      } while (local_8c4[0] != 0);
      local_8a8[0] = iVar3;
      TreeLowerBound(local_8c4);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_1[0xff0] = iVar3;
  }
  goto LAB_00498629;
code_r0x00498383:
  iVar3 = *(int *)(iVar3 + 0x10);
  uVar1 = *(uint *)(iVar3 + 8);
  if (local_8c8 < uVar1) goto LAB_00498629;
  goto LAB_00498381;
}

