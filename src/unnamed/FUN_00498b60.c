/* FUN_00498b60 - 0x00498b60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00498b60(int *param_1)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *unaff_FS_OFFSET;
  bool bVar8;
  uint local_8c4;
  int local_8b8 [2];
  int local_8b0 [2];
  undefined1 local_8a8 [20];
  int local_894;
  undefined1 local_684 [20];
  int local_670;
  undefined1 local_460 [20];
  int local_44c;
  undefined1 auStack_23c [20];
  int iStack_228;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_0053c0d4;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  FUN_004986a0(param_1);
  AdvanceSpriteAnimation();
  FUN_00498070(param_1);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a6e0(param_1 + 0x99,local_8a8,uVar3);
  local_c = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8c4 = FUN_004e4340();
  local_c = 0xffffffff;
  if (local_894 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_8b0);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < (int)local_8c4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((int)(local_8c4 + -0xf) <= iVar4) goto LAB_00498f85;
    if ((char)param_1[0xfed] == '\0') {
      *(undefined1 *)(param_1 + 0xfed) = 1;
      param_1[0xfec] = 0;
      param_1[0xfee] = 0;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0040a6e0(param_1 + 0x99,local_8a8,uVar3);
    local_c = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_c = 0xffffffff;
    if (local_894 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8b0);
    }
    if (local_8c4 == iVar4) {
      FUN_0040a6e0(param_1 + 0x99,local_8a8,0x1e);
      local_c = 2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_8b8[0] = FUN_004e4340();
      local_c = 0xffffffff;
      if (local_894 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_8b0);
      }
      FUN_0040a6e0(param_1 + 0x99,local_8a8,0x1e);
      local_c = 3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      bVar8 = local_8b8[0] == iVar4;
      local_c = 0xffffffff;
      if (local_894 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_8b0);
      }
      if (bVar8) {
        uVar3 = FUN_0040a5f0(param_1 + 0x99,local_8a8,1);
        local_c = 4;
        FUN_0040a4d0(uVar3);
        FUN_0040a4d0(param_1 + 0x10);
        local_8c4 = FUN_004e4340();
        local_c = 0xffffffff;
        FUN_0040a2a0();
        uVar3 = FUN_0040a5f0(param_1 + 0x99,local_8a8,1);
        local_c = 5;
        iVar4 = FUN_0040a4d0(uVar3);
        local_c = 0xffffffff;
        FUN_0040a2a0();
        if (local_8c4 == iVar4) {
          local_8c4 = FUN_0040a4d0(param_1 + 0x99);
        }
      }
    }
LAB_00498f85:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(local_8c4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar4 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar4 = param_1[0xfe8];
  param_1[0xfe8] = iVar4 + 1;
  if (iVar4 + 1 == 5) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  if ((char)param_1[0xfed] != '\0') {
    FUN_0040a5f0(param_1 + 0x99,local_8a8,param_1[0xfee]);
    local_c = 6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_c = 0xffffffff;
    if (local_894 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8b0);
    }
    if (iVar4 < (int)local_8c4) {
      iVar4 = param_1[0xfee];
      param_1[0xfee] = iVar4 + 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(iVar5 + iVar4 + 1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else if (param_1[0xfee] < 5) {
      QueueOutgoingPacketField(local_8c4);
      param_1[0xfee] = 0;
      *(undefined1 *)(param_1 + 0xfed) = 0;
    }
    else {
      QueueOutgoingPacketField(local_8c4 - param_1[0xfee]);
      param_1[0xfee] = 1;
    }
  }
  if ((char)param_1[0xff1] != '\0') {
    iVar4 = param_1[0xff2];
    param_1[0xff2] = iVar4 + 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar5 - (iVar4 + 1));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (-1 < iVar4) {
    iVar4 = *(int *)(&DAT_006a7720 + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 < iVar4) {
      iVar4 = *(int *)(&DAT_006a7724 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((iVar5 < iVar4) && (cVar2 = FUN_0040b330(param_1 + 0x99,0xffffff38), cVar2 == '\0'))
      goto LAB_00499217;
    }
  }
  *(undefined1 *)(param_1 + 5) = 1;
LAB_00499217:
  FUN_0040ada0(param_1 + 0xc66,local_8a8,param_1 + 0xc66);
  local_c = 7;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 0xffffffff;
  if (local_894 != 0) {
    FUN_0040a240();
    local_8b8[0] = local_894;
    FUN_0040b540(local_8b0);
  }
  local_8c4 = 0;
  do {
    iVar5 = GetPlayerRecordBySlot(g_clientContext);
    if ((iVar5 != 0) && (cVar2 = PeekPacketChecksumBool(), cVar2 != '\x01')) {
      FUN_0040aca0(param_1 + 0x10,local_684,iVar5 + 0x90c);
      local_c = 8;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_c = 0xffffffff;
      local_8b8[0] = local_670;
      if (local_670 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_8b0);
      }
      FUN_0040aca0(param_1 + 0x99,local_460,iVar5 + 0xb30);
      local_c = 9;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_c = 0xffffffff;
      local_8b8[0] = local_44c;
      if (local_44c != 0) {
        FUN_0040a240();
        FUN_0040b540(local_8b0);
      }
      if (iVar5 * iVar5 + iVar6 * iVar6 < iVar4) {
        (**(code **)(*param_1 + 0x20))();
      }
    }
    local_8c4 = local_8c4 + 1;
  } while ((int)local_8c4 < 8);
  local_8c4 = 0;
  do {
    iVar5 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar1 = *(uint *)(iVar5 + 4);
    while (uVar1 < 0x186a7) {
      if (uVar1 == 0x186a6) {
        iVar5 = *(int *)(iVar5 + 0x10);
        uVar1 = *(uint *)(iVar5 + 8);
        if (uVar1 <= local_8c4) goto LAB_00499440;
        break;
      }
      iVar5 = *(int *)(iVar5 + 0x1c);
      uVar1 = *(uint *)(iVar5 + 4);
    }
LAB_004995d6:
    local_8c4 = local_8c4 + 1;
    if (7 < (int)local_8c4) {
      if ((char)param_1[0xff1] == '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = FUN_00451030(uVar3);
        if (iVar4 != 0) {
          *(undefined1 *)(param_1 + 0xfed) = 0;
          *(undefined1 *)(param_1 + 0xff1) = 1;
          param_1[0xff2] = 0;
        }
      }
      *unaff_FS_OFFSET = uStack_14;
      return;
    }
  } while( true );
LAB_00499440:
  if (uVar1 != local_8c4) goto code_r0x00499442;
  FUN_0040aca0(param_1 + 0x10,local_684,iVar5 + 0x25c);
  local_c = 10;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_8b0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 0xffffffff;
  if (local_670 != 0) {
    iVar6 = local_670 << 4;
    local_8b8[0] = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar7;
      iVar6 = iVar6 + 1;
      local_8b8[0] = local_8b8[0] + -1;
    } while (local_8b8[0] != 0);
    FUN_0040b540(local_8b8);
  }
  FUN_0040aca0(param_1 + 0x99,auStack_23c,iVar5 + 0x480);
  local_c = 0xb;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_c = 0xffffffff;
  if (iStack_228 != 0) {
    iVar6 = iStack_228 << 4;
    local_8b8[0] = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar7;
      iVar6 = iVar6 + 1;
      local_8b8[0] = local_8b8[0] + -1;
    } while (local_8b8[0] != 0);
    FUN_0040b540(local_8b8);
  }
  if (local_8b0[0] * local_8b0[0] + iVar5 * iVar5 < iVar4) {
    (**(code **)(*param_1 + 0x20))();
  }
  goto LAB_004995d6;
code_r0x00499442:
  iVar5 = *(int *)(iVar5 + 0x10);
  uVar1 = *(uint *)(iVar5 + 8);
  if (local_8c4 < uVar1) goto LAB_004995d6;
  goto LAB_00499440;
}

