/* FUN_004cb280 - 0x004cb280 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004cb280(int param_1)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff8dc;
  undefined stack0xfffff8e4;
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  byte bVar11;
  byte *pbVar12;
  int unaff_EBP;
  undefined4 *puVar13;
  code *pcVar14;
  char *pcVar15;
  undefined4 *puVar16;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar17;
  undefined *puVar18;
  uint local_718;
  int local_714;
  int local_710;
  int local_70c;
  uint local_708;
  undefined1 local_700 [8];
  char local_6f8 [108];
  undefined1 auStack_68c [32];
  undefined4 uStack_66c;
  int local_664;
  undefined1 auStack_46c [12];
  undefined1 uStack_460;
  int iStack_45c;
  undefined1 auStack_244 [12];
  int iStack_238;
  int *piStack_28;
  undefined1 uStack_20;
  undefined1 uStack_1c;
  undefined1 uStack_18;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053e001;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  pcVar14 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 == 3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar4 < iVar3) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar4 < iVar3) goto LAB_004cb8d4;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = DAT_007934e8;
    if ((iVar4 == iVar5) && (*(char *)(param_1 + 0x2382) == '\0')) {
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x4200;
      *(undefined4 *)(iVar3 + 0x44d0) = 6;
      cVar1 = FUN_0040b410(&DAT_0067e5f4 + g_clientContext,&DAT_0067e3d0 + g_clientContext);
      iVar3 = DAT_007934e8;
      if (cVar1 == '\0') {
        *(undefined1 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = 0;
      }
      else {
        *(undefined1 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = 1;
      }
      *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 1;
      FUN_004d25e0();
      FUN_004d2680();
      *(undefined1 *)(param_1 + 0x2382) = 1;
      goto LAB_004cbd7a;
    }
  }
  else {
    local_714 = 0;
    local_70c = 0;
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      (*pcVar14)(&DAT_005a9068);
      if (1 < iVar3) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0);
        puVar18 = &DAT_005a9068;
        (*pcVar14)(&DAT_005a9068);
        iVar3 = GetPlayerRecordBySlot(g_clientContext);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(iVar4 + 4);
        puVar17 = &DAT_005a9068;
        (*pcVar14)(&DAT_005a9068);
        uStack_460 = 0;
        uStack_66c = 0;
        EncodeOutgoingPacketField(0);
        local_c = 0;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(500);
        (*pcVar14)(&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState();
        (*pcVar14)(&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        (*pcVar14)(&DAT_005a9068);
        uVar6 = FUN_0040a7d0(auStack_68c,auStack_244,puVar18 + iVar4);
        uStack_18 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        puVar18 = &DAT_005a9068;
        (*pcVar14)(&DAT_005a9068);
        FUN_0040a8c0(uVar6,auStack_46c,puVar17);
        uStack_1c = 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar6 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar6);
        (*pcVar14)(&DAT_005a9068);
        uStack_20 = 1;
        if (iStack_45c != 0) {
          FUN_0040a240();
          FUN_0040b540(&stack0xfffff8e4);
          iVar3 = unaff_EBP;
        }
        uStack_20 = 0;
        if (iStack_238 != 0) {
          FUN_0040a240();
          FUN_0040b540(&stack0xfffff8e4);
          iVar3 = unaff_EBP;
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState();
        iVar5 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(iVar5 + iVar4);
        (*pcVar14)(&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar6 = PeekPacketChecksumState();
        (*pcVar14)(&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        (*pcVar14)(&DAT_005a9068);
        FUN_004368f0(puVar18,uVar6,4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar6 = PeekPacketChecksumState();
        (*pcVar14)(&DAT_005a9068);
        iVar3 = iVar3 + 0xae15;
        iVar4 = iVar3;
        pcVar7 = (char *)GetLocalizedString(&DAT_00796eec,0x274);
        _sprintf(&stack0xfffff8dc,pcVar7,iVar4,uVar6);
        (**(code **)(*piStack_28 + 0x28))(&stack0xfffff8dc,4,3);
        FUN_00438360();
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (local_714 == iVar4) {
          iVar4 = *(int *)(g_clientContext + 0x44e60) + 1;
          pcVar7 = (char *)GetLocalizedString(&DAT_00796eec,5000);
          _sprintf(local_6f8,pcVar7,iVar3,iVar4);
          iVar4 = DAT_007934e8;
          *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
          *(undefined2 *)(iVar4 + 0x4d4) = 0x5010;
          *(undefined1 *)(iVar4 + 0x4d6) = 0xff;
          iVar3 = *(int *)(iVar4 + 0x44d0);
          *(int *)(iVar4 + 0x44d0) = iVar3 + 1;
          pcVar7 = local_6f8;
          do {
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          *(char *)(iVar3 + 0x4d1 + iVar4) = (char)pcVar7 - ((char)local_6f8 + '\x01');
          iVar3 = *(int *)(iVar4 + 0x44d0);
          *(int *)(iVar4 + 0x44d0) = iVar3 + 1;
          pcVar7 = local_6f8;
          do {
            cVar1 = *pcVar7;
            pcVar7 = pcVar7 + 1;
          } while (cVar1 != '\0');
          uVar8 = (int)pcVar7 - (int)(local_6f8 + 1);
          uVar9 = ((int)uVar8 < 0) - 1 & uVar8;
          pcVar7 = local_6f8;
          pcVar15 = (char *)(iVar3 + 0x4d1 + iVar4);
          for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(undefined4 *)pcVar15 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar15 = pcVar15 + 4;
          }
          for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
            *pcVar15 = *pcVar7;
            pcVar7 = pcVar7 + 1;
            pcVar15 = pcVar15 + 1;
          }
          *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + uVar8;
          FUN_004d25e0();
          FUN_004d2680();
        }
        local_4 = 0xffffffff;
        pcVar14 = (code *)LeaveCriticalSection;
        if (local_664 != 0) {
          FUN_0040a240();
          FUN_0040b540(local_700);
          pcVar14 = (code *)LeaveCriticalSection;
        }
      }
      local_714 = local_714 + 1;
      local_70c = local_70c + 0x1120;
    } while (local_70c < 0x8900);
  }
LAB_004cb8d4:
  FUN_004d09c0();
  local_708 = 0xf0000000;
  local_70c = -1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_718 = PeekPacketChecksumState();
  uVar8 = PeekPacketChecksumState();
  (*pcVar14)(&DAT_005a9068);
  if (local_718 != uVar8) goto LAB_004cbd7a;
  cVar1 = FUN_004065a0();
  if (cVar1 == '\x01') {
LAB_004cbb03:
    Replay_AppendEvent(0xc40b);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)(param_1 + 0x22fc) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)(param_1 + 0x22fd) = (byte)iVar3;
    bVar11 = '\x01' << (*(byte *)(param_1 + 0x22fc) & 7);
    bVar11 = ~bVar11 & (byte)iVar3 | bVar11;
    *(byte *)(param_1 + 0x22fd) = bVar11;
    *(byte *)(param_1 + 0x22fe) = *(byte *)(param_1 + 0x22fc) + bVar11 + -0x34;
    (*pcVar14)(&DAT_005a9068);
    local_714 = 0;
    local_710 = 0;
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState();
      (*pcVar14)(&DAT_005a9068);
      if ((uVar8 < local_708) && (iVar3 = GetPlayerRecordBySlot(g_clientContext), iVar3 != 0)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState();
        (*pcVar14)(&DAT_005a9068);
        if (0 < iVar4) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar4 = PeekPacketChecksumState();
          (*pcVar14)(&DAT_005a9068);
          if (iVar4 < 9000) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_708 = PeekPacketChecksumState();
            (*pcVar14)(&DAT_005a9068);
            local_70c = local_714;
            goto LAB_004cbad9;
          }
        }
        if ((*(int *)(iVar3 + 0x24) != 0xe) || (cVar1 = FUN_004065a0(), cVar1 == '\0')) {
          Replay_AppendEvent(0xc801);
          (&g_replayEventBuffer)[g_replayEventCursor] = (undefined1)local_714;
          g_replayEventCursor = g_replayEventCursor + 1;
          Replay_FlushEvent();
          pcVar14 = (code *)LeaveCriticalSection;
        }
      }
LAB_004cbad9:
      iVar3 = g_clientContext;
      local_710 = local_710 + 0x224;
      local_714 = local_714 + 1;
    } while (local_710 < 0x1120);
    if (local_70c == -1) goto LAB_004cbb03;
    *(char *)(param_1 + 0x23d0) = (char)local_70c;
    pbVar12 = &DAT_006aa62b + iVar3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *pbVar12 = (byte)iVar4;
    iVar4 = _rand();
    (&DAT_006aa62c)[iVar3] = (byte)iVar4;
    bVar11 = '\x01' << (*pbVar12 & 7);
    bVar11 = ~bVar11 & (byte)iVar4 | bVar11;
    (&DAT_006aa62c)[iVar3] = bVar11;
    (&DAT_006aa62d)[iVar3] = bVar11 + *pbVar12 + -0x34;
    (*pcVar14)(&DAT_005a9068);
    iVar3 = g_clientContext;
    *(undefined4 *)(param_1 + 0x23cc) = 400;
    if (*(int *)(iVar3 + 0x621e0) == 0) goto LAB_004cbd7a;
    pbVar12 = (byte *)(param_1 + 0x23d4);
    cVar1 = FUN_004065a0();
    if (cVar1 == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = _rand();
      *pbVar12 = (byte)iVar3;
      iVar3 = _rand();
      *(byte *)(param_1 + 0x23d5) = (byte)iVar3;
      local_718 = *pbVar12 & 7;
      bVar11 = ~('\x01' << (sbyte)local_718) & (byte)iVar3 | '\0' << (sbyte)local_718;
      *(byte *)(param_1 + 0x23d5) = bVar11;
      *(byte *)(param_1 + 0x23d6) = bVar11 + *pbVar12 + -0x34;
      (*pcVar14)(&DAT_005a9068);
      Replay_AppendEvent(0xc308);
      FUN_0041f200(1);
      puVar13 = (undefined4 *)(g_clientContext + 0xeba78);
      puVar16 = (undefined4 *)(param_1 + 0x2302);
      for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar16 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar16 = puVar16 + 1;
      }
      Replay_FlushEvent();
      pcVar14 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar14)(&DAT_005a9068);
    if ((((int)local_718 <= iVar3) && (cVar1 = FUN_004065a0(), cVar1 == '\0')) &&
       (*(char *)(g_clientContext + 0x45127) != '\0')) {
      Replay_AppendEvent(0xc305);
      Replay_FlushEvent();
    }
    Replay_AppendEvent(0xc300);
    (&g_replayEventBuffer)[g_replayEventCursor] = (char)local_70c;
    g_replayEventCursor = g_replayEventCursor + 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar2;
    puVar13 = (undefined4 *)(param_1 + 0x2302);
    puVar16 = (undefined4 *)(&DAT_00e9aace + g_replayEventCursor);
    g_replayEventCursor = g_replayEventCursor + 2;
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar16 = *puVar13;
      puVar13 = puVar13 + 1;
      puVar16 = puVar16 + 1;
    }
    g_replayEventCursor = g_replayEventCursor + 0x20;
  }
  Replay_FlushEvent();
LAB_004cbd7a:
  *unaff_FS_OFFSET = local_c;
  return;
}

