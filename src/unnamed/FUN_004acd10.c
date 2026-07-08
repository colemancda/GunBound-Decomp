/* FUN_004acd10 - 0x004acd10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004acd10(int param_1)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  byte *pbVar9;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int local_45c [2];
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00540806;
  *unaff_FS_OFFSET = &local_c;
  iVar7 = *(int *)(param_1 + 0x3fa0) + 1;
  *(int *)(param_1 + 0x3fa0) = iVar7;
  if (iVar7 < 0x15) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    switch(*(undefined4 *)(param_1 + 0x3fa0)) {
    case 2:
    case 4:
    case 6:
    case 8:
    case 10:
    case 0xc:
    case 0xe:
    case 0x10:
      iVar7 = *(int *)(param_1 + 0x3f9c) * 0x343fd;
      local_45c[0] = (uint)((iVar7 + 0x5809316) * 0x61) % 0xf4241 + *(int *)(param_1 + 0x3f9c);
      *(uint *)(param_1 + 0x3f9c) =
           (uint)((local_45c[0] * 0x343fd + 0x5809316) * 0x61) % 0xf4241 + local_45c[0];
      FUN_0040a5f0(param_1 + 0x1178,local_230,
                   (local_45c[0] * 0x343fd + 0x5809315U) % uVar6 - (int)uVar6 / 2);
      local_4 = 0;
      FUN_0040a5f0(param_1 + 0xf54,local_454,(iVar7 + 0x5809315U) % uVar6 - (int)uVar6 / 2);
      local_4 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_45c[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar12 = 1;
      uVar11 = 2;
      uVar10 = 0xff;
      uVar4 = 0;
      iVar7 = local_45c[0];
      FUN_004065a0(0,local_45c[0],0xff,2,1);
      FUN_00431d90(*(undefined1 *)(param_1 + 0x3c),3,0,uVar4,iVar7,uVar10,uVar11,uVar12);
      local_4 = 0;
      if (local_440 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_45c);
      }
      local_4 = 0xffffffff;
      if (local_21c != 0) {
        FUN_0040a240();
        FUN_0040b540(local_45c);
      }
    }
    goto switchD_004ad044_caseD_3;
  }
  *(undefined1 *)(param_1 + 0x14) = 1;
  cVar3 = FUN_004065a0();
  if ((cVar3 != '\0') && (cVar3 = FUN_0043a530(), cVar3 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar4);
    iVar7 = g_clientContext;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar7) = 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_45c[0] = PeekPacketChecksumState();
  iVar7 = PeekPacketChecksumState();
  local_45c[0] = CONCAT31(local_45c[0]._1_3_,local_45c[0] < iVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar3 = FUN_00406610(local_45c[0]);
  if (cVar3 != '\0') {
    local_45c[0] = g_clientContext + 0x5b85c;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar7 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar7 < 1) goto LAB_004ace87;
LAB_004aced3:
    cVar3 = FUN_004065a0();
    if (cVar3 == '\0') {
      FUN_00406500(1);
    }
  }
  else {
LAB_004ace87:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar7) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar7 < 0) goto LAB_004aced3;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_45c[0] = PeekPacketChecksumState();
  iVar7 = PeekPacketChecksumState();
  bVar2 = iVar7 <= local_45c[0];
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((bVar2) || (cVar3 = FUN_0040b490(param_1 + 0x3b48,param_1 + 0x3d6c), cVar3 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_45c[0] = PeekPacketChecksumState();
    iVar7 = PeekPacketChecksumState();
    bVar2 = local_45c[0] <= iVar7;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((bVar2) ||
       ((cVar3 = FUN_0040b410(param_1 + 0x3b48,param_1 + 0x3d6c), cVar3 == '\0' ||
        (*(int *)(param_1 + 0x3b44) < 6)))) goto switchD_004ad044_caseD_3;
  }
  iVar7 = g_clientContext;
  pbVar9 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *pbVar9 = (byte)iVar5;
  iVar5 = _rand();
  bVar1 = *pbVar9;
  *(byte *)(iVar7 + 0x62144) = (byte)iVar5;
  bVar8 = '\x01' << (bVar1 & 7);
  bVar1 = *pbVar9;
  bVar8 = ~bVar8 & (byte)iVar5 | bVar8;
  *(byte *)(iVar7 + 0x62144) = bVar8;
  *(byte *)(iVar7 + 0x62145) = bVar8 + bVar1 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
switchD_004ad044_caseD_3:
  *unaff_FS_OFFSET = local_c;
  return;
}

