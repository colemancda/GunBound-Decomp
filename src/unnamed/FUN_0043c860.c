/* FUN_0043c860 - 0x0043c860 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0043c860(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  byte bVar7;
  uint uVar8;
  byte bVar9;
  char cVar10;
  undefined4 *puVar11;
  byte *pbVar12;
  undefined4 *puVar13;
  uint local_8;
  
  iVar6 = param_2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)(param_1 + 4) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)(param_1 + 5) = (byte)iVar2;
  bVar9 = '\x01' << (*(byte *)(param_1 + 4) & 7);
  bVar9 = ~bVar9 & (byte)iVar2 | bVar9;
  *(byte *)(param_1 + 5) = bVar9;
  *(byte *)(param_1 + 6) = *(byte *)(param_1 + 4) + bVar9 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (*(void **)(param_1 + 8) != (void *)0x0) {
    _free(*(void **)(param_1 + 8));
    *(undefined4 *)(param_1 + 8) = 0;
  }
  iVar3 = DAT_005b3484;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  iVar2 = *(int *)(&DAT_006a7724 + iVar3);
  iVar4 = *(int *)(&DAT_006a7720 + iVar3);
  puVar11 = *(undefined4 **)(&DAT_006a773c + iVar3);
  puVar13 = *(undefined4 **)(&DAT_006a7740 + iVar3);
  for (uVar8 = (uint)(iVar2 * iVar4) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *puVar13 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar13 = puVar13 + 1;
  }
  for (uVar8 = iVar2 * iVar4 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined1 *)puVar13 = *(undefined1 *)puVar11;
    puVar11 = (undefined4 *)((int)puVar11 + 1);
    puVar13 = (undefined4 *)((int)puVar13 + 1);
  }
  local_8 = 0;
  do {
    iVar2 = GetPlayerRecordBySlot(iVar3);
    if (iVar2 != 0) {
      FUN_00463c80();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      *(char *)(iVar2 + 0x8bb1) = (char)iVar4;
      iVar4 = _rand();
      *(byte *)(iVar2 + 0x8bb2) = (byte)iVar4;
      bVar9 = *(byte *)(iVar2 + 0x8bb1) & 7;
      bVar9 = ~('\x01' << bVar9) & (byte)iVar4 | '\0' << bVar9;
      *(byte *)(iVar2 + 0x8bb2) = bVar9;
      *(byte *)(iVar2 + 0x8bb3) = *(byte *)(iVar2 + 0x8bb1) + bVar9 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    local_8 = local_8 + 1;
    iVar3 = DAT_005b3484;
  } while ((int)local_8 < 8);
  local_8 = 0;
LAB_0043c9d0:
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar8 = *(uint *)(iVar2 + 4);
  while (uVar8 < 0x186a7) {
    if (uVar8 == 0x186a6) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar8 = *(uint *)(iVar2 + 8);
      if (uVar8 <= local_8) goto LAB_0043ca06;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar8 = *(uint *)(iVar2 + 4);
  }
  goto LAB_0043ca62;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (local_8 < uVar8) break;
LAB_0043ca06:
    if (uVar8 == local_8) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      break;
    }
  }
LAB_0043ca62:
  local_8 = local_8 + 1;
  if (7 < (int)local_8) goto code_r0x0043ca70;
  goto LAB_0043c9d0;
code_r0x0043ca70:
  local_8 = 0;
LAB_0043ca80:
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar8 = *(uint *)(iVar2 + 4);
  while (uVar8 < 0x186a4) {
    if (uVar8 == 0x186a3) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar8 = *(uint *)(iVar2 + 8);
      if (uVar8 <= local_8) goto LAB_0043caba;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar8 = *(uint *)(iVar2 + 4);
  }
  goto LAB_0043cb0f;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (local_8 < uVar8) break;
LAB_0043caba:
    if (uVar8 == local_8) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      break;
    }
  }
LAB_0043cb0f:
  local_8 = local_8 + 1;
  if (0x3f < (int)local_8) goto code_r0x0043cb21;
  goto LAB_0043ca80;
code_r0x0043cb21:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = FUN_0053753c();
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = FUN_0053753c();
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = FUN_0053753c();
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = FUN_0053753c();
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = FUN_0053753c();
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = FUN_0053753c();
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = DAT_005b3484;
  pbVar12 = (byte *)(DAT_005b3484 + 0x5b818);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = _rand();
  *pbVar12 = (byte)iVar4;
  iVar4 = _rand();
  bVar9 = *pbVar12;
  *(byte *)(iVar2 + 0x5b819) = (byte)iVar4;
  bVar7 = bVar9 & 7;
  bVar7 = ~('\x01' << bVar7) & (byte)iVar4 | '\0' << bVar7;
  *(byte *)(iVar2 + 0x5b819) = bVar7;
  *(byte *)(iVar2 + 0x5b81a) = bVar9 + bVar7 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)(*(byte *)(param_2 + 0x8bba) + *(byte *)(param_2 + 0x8bbb) + -0x34) ==
      *(char *)(param_2 + 0x8bbc)) {
    param_2._0_1_ =
         '\x01' - ((*(byte *)(param_2 + 0x8bbb) >> (*(byte *)(param_2 + 0x8bba) & 7) & 1) != 1);
  }
  else {
    DAT_00793514 = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_2._0_1_ = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((char)param_2 == '\0') {
    cVar10 = FUN_0041eaa0(DAT_005b3484,*(undefined2 *)(iVar6 + 0xbfbc));
    if (cVar10 == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((byte)(*(byte *)(iVar6 + 0x8bb7) + *(byte *)(iVar6 + 0x8bb8) + -0x34) ==
          *(char *)(iVar6 + 0x8bb9)) {
        param_2._0_1_ =
             '\x01' - ((*(byte *)(iVar6 + 0x8bb8) >> (*(byte *)(iVar6 + 0x8bb7) & 7) & 1) != 1);
      }
      else {
        DAT_00793514 = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        param_2._0_1_ = '\0';
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((char)param_2 == '\0') {
        *(undefined4 *)(iVar6 + 0xbffa) = DAT_00553b68;
        *(undefined2 *)(iVar6 + 0xbffe) = DAT_00553b6c;
      }
      else {
        *(undefined4 *)(iVar6 + 0xbffa) = DAT_00553b70;
        *(undefined2 *)(iVar6 + 0xbffe) = DAT_00553b74;
      }
    }
    else {
      *(undefined4 *)(iVar6 + 0xbffa) = s_ifire_00553b60._0_4_;
      *(undefined2 *)(iVar6 + 0xbffe) = s_ifire_00553b60._4_2_;
    }
  }
  else {
    *(undefined4 *)(iVar6 + 0xbffa) = s_sfire_00553b78._0_4_;
    *(undefined2 *)(iVar6 + 0xbffe) = s_sfire_00553b78._4_2_;
  }
  do {
    do {
      do {
        iVar6 = DAT_005b3484;
        pbVar12 = &DAT_006aa628 + DAT_005b3484;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = _rand();
        *pbVar12 = (byte)iVar2;
        iVar2 = _rand();
        bVar9 = *pbVar12;
        (&DAT_006aa629)[iVar6] = (byte)iVar2;
        bVar7 = bVar9 & 7;
        bVar7 = ~('\x01' << bVar7) & (byte)iVar2 | '\0' << bVar7;
        (&DAT_006aa629)[iVar6] = bVar7;
        (&DAT_006aa62a)[iVar6] = bVar9 + bVar7 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00450810();
        FUN_004f3100();
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = DAT_005b3484;
      } while (iVar2 < 0);
      pbVar12 = &DAT_006aa625 + DAT_005b3484;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((byte)(*pbVar12 + (&DAT_006aa626)[iVar6] + -0x34) == (&DAT_006aa627)[iVar6]) {
        cVar10 = '\x01' - (((byte)(&DAT_006aa626)[iVar6] >> (*pbVar12 & 7) & 1) != 1);
      }
      else {
        DAT_00793514 = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        cVar10 = '\0';
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = DAT_005b3484;
    } while (cVar10 != '\x01');
    pbVar12 = &DAT_006aa628 + DAT_005b3484;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((byte)(*pbVar12 + (&DAT_006aa629)[iVar6] + -0x34) == (&DAT_006aa62a)[iVar6]) {
      cVar10 = '\x01' - (((byte)(&DAT_006aa629)[iVar6] >> (*pbVar12 & 7) & 1) != 1);
    }
    else {
      DAT_00793514 = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar10 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  } while (cVar10 != '\0');
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = DAT_005b3484;
  pbVar12 = &DAT_006aa625 + DAT_005b3484;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *pbVar12 = (byte)iVar2;
  iVar2 = _rand();
  bVar9 = *pbVar12;
  (&DAT_006aa626)[iVar6] = (byte)iVar2;
  bVar7 = bVar9 & 7;
  bVar7 = ~('\x01' << bVar7) & (byte)iVar2 | '\0' << bVar7;
  (&DAT_006aa626)[iVar6] = bVar7;
  (&DAT_006aa627)[iVar6] = bVar9 + bVar7 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = DAT_005b3484;
  pbVar12 = &DAT_006aa628 + DAT_005b3484;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *pbVar12 = (byte)iVar2;
  iVar2 = _rand();
  bVar9 = *pbVar12;
  (&DAT_006aa629)[iVar6] = (byte)iVar2;
  bVar7 = bVar9 & 7;
  bVar7 = ~('\x01' << bVar7) & (byte)iVar2 | '\0' << bVar7;
  (&DAT_006aa629)[iVar6] = bVar7;
  (&DAT_006aa62a)[iVar6] = bVar9 + bVar7 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *(char *)(param_1 + 4) = (char)iVar6;
  iVar6 = _rand();
  *(byte *)(param_1 + 5) = (byte)iVar6;
  bVar9 = *(byte *)(param_1 + 4) & 7;
  bVar9 = ~('\x01' << bVar9) & (byte)iVar6 | '\0' << bVar9;
  *(byte *)(param_1 + 5) = bVar9;
  *(byte *)(param_1 + 6) = *(byte *)(param_1 + 4) + bVar9 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = DAT_005b3484;
  iVar6 = *(int *)(&DAT_006a7724 + DAT_005b3484);
  iVar2 = *(int *)(&DAT_006a7720 + DAT_005b3484);
  puVar11 = *(undefined4 **)(&DAT_006a7740 + DAT_005b3484);
  puVar13 = *(undefined4 **)(&DAT_006a773c + DAT_005b3484);
  for (uVar8 = (uint)(iVar6 * iVar2) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *puVar13 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar13 = puVar13 + 1;
  }
  for (uVar8 = iVar6 * iVar2 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined1 *)puVar13 = *(undefined1 *)puVar11;
    puVar11 = (undefined4 *)((int)puVar11 + 1);
    puVar13 = (undefined4 *)((int)puVar13 + 1);
  }
  iVar6 = 0;
  do {
    iVar2 = GetPlayerRecordBySlot(iVar4);
    if (iVar2 != 0) {
      FUN_00463e50();
    }
    iVar6 = iVar6 + 1;
    iVar4 = DAT_005b3484;
  } while (iVar6 < 8);
  uVar8 = 0;
LAB_0043d480:
  iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar1 = *(uint *)(iVar6 + 4);
  while (uVar1 < 0x186a7) {
    if (uVar1 == 0x186a6) {
      iVar6 = *(int *)(iVar6 + 0x10);
      uVar1 = *(uint *)(iVar6 + 8);
      if (uVar1 <= uVar8) goto LAB_0043d4b5;
      break;
    }
    iVar6 = *(int *)(iVar6 + 0x1c);
    uVar1 = *(uint *)(iVar6 + 4);
  }
  goto LAB_0043d515;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar1 = *(uint *)(iVar6 + 8);
    if (uVar8 < uVar1) break;
LAB_0043d4b5:
    if (uVar1 == uVar8) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      break;
    }
  }
LAB_0043d515:
  uVar8 = uVar8 + 1;
  if (7 < (int)uVar8) goto code_r0x0043d51f;
  goto LAB_0043d480;
code_r0x0043d51f:
  uVar8 = 0;
LAB_0043d521:
  iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar1 = *(uint *)(iVar6 + 4);
  while (uVar1 < 0x186a4) {
    if (uVar1 == 0x186a3) {
      iVar6 = *(int *)(iVar6 + 0x10);
      uVar1 = *(uint *)(iVar6 + 8);
      if (uVar1 <= uVar8) goto LAB_0043d557;
      break;
    }
    iVar6 = *(int *)(iVar6 + 0x1c);
    uVar1 = *(uint *)(iVar6 + 4);
  }
  goto LAB_0043d5b4;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar1 = *(uint *)(iVar6 + 8);
    if (uVar8 < uVar1) break;
LAB_0043d557:
    if (uVar1 == uVar8) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      break;
    }
  }
LAB_0043d5b4:
  uVar8 = uVar8 + 1;
  if (0x3f < (int)uVar8) {
    DAT_00793517 = 1;
    return;
  }
  goto LAB_0043d521;
}

