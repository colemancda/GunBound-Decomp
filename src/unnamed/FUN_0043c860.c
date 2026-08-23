/* FUN_0043c860 - 0x0043c860 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 30 argless PeekPacketChecksumState() calls and the 15 1-arg
 * EncodeOutgoingPacketField() calls (worklist 30/15).  Three cell owners:
 * (1) the map node found by the DAT_006a7f8c+ctx lookups (EBX/ESI = the C's
 * iVar2 / iVar6, the `*(iVar+0x10)` walker) - the head saves its +0x25c/
 * +0x480/+0x40/+0x264 cells into +0x1e50/+0x2074/+0x3fd4/+0x41f8 and the
 * tail restores them (0x43ca21..0x43cb03 / 0x43d4d4..0x43d5a8);
 * (2) param_2 (frame[0x20], `mov ebx,[esp+0x20]` at 0x43cb28, EBX kept
 * for all three middle blocks) at +0x1c54/+0x51d8 and the per-block
 * pairs 0x9cf0-0x9f14 -> Encode 0x53fc/0x5620, 0xa138-0xa35c -> 0x5844/
 * 0x5a68, 0xa9c8-0xabec -> 0x5c8c/0x5eb0 (both arms of each `iVar2 == 0`
 * test peek the same two cells, so branch order is immaterial); (3)
 * g_clientContext+0x621e8 (0x43d1e8 / 0x43d2d5).
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
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = _rand();
  *(char *)(param_1 + 4) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)(param_1 + 5) = (byte)iVar2;
  bVar9 = '\x01' << (*(byte *)(param_1 + 4) & 7);
  bVar9 = ~bVar9 & (byte)iVar2 | bVar9;
  *(byte *)(param_1 + 5) = bVar9;
  *(byte *)(param_1 + 6) = *(byte *)(param_1 + 4) + bVar9 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (*(void **)(param_1 + 8) != (void *)0x0) {
    _free(*(void **)(param_1 + 8));
    *(undefined4 *)(param_1 + 8) = 0;
  }
  iVar3 = g_clientContext;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  iVar2 = *(int *)(&g_nCameraBoundY + iVar3);
  iVar4 = *(int *)(&g_nCameraBoundX + iVar3);
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
      SavePlayerStateSnapshot();
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = _rand();
      *(char *)(iVar2 + 0x8bb1) = (char)iVar4;
      iVar4 = _rand();
      *(byte *)(iVar2 + 0x8bb2) = (byte)iVar4;
      bVar9 = *(byte *)(iVar2 + 0x8bb1) & 7;
      bVar9 = ~('\x01' << bVar9) & (byte)iVar4 | '\0' << bVar9;
      *(byte *)(iVar2 + 0x8bb2) = bVar9;
      *(byte *)(iVar2 + 0x8bb3) = *(byte *)(iVar2 + 0x8bb1) + bVar9 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    local_8 = local_8 + 1;
    iVar3 = g_clientContext;
  } while ((int)local_8 < 8);
  local_8 = 0;
LAB_0043c9d0:
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
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
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = PeekPacketChecksumState((void *)(iVar2 + 0x25c));
      EncodeOutgoingPacketField((void *)(iVar2 + 0x1e50), uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = PeekPacketChecksumState((void *)(iVar2 + 0x480));
      EncodeOutgoingPacketField((void *)(iVar2 + 0x2074), uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
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
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = PeekPacketChecksumState((void *)(iVar2 + 0x40));
      EncodeOutgoingPacketField((void *)(iVar2 + 0x3fd4), uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = PeekPacketChecksumState((void *)(iVar2 + 0x264));
      EncodeOutgoingPacketField((void *)(iVar2 + 0x41f8), uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      break;
    }
  }
LAB_0043cb0f:
  local_8 = local_8 + 1;
  if (0x3f < (int)local_8) goto code_r0x0043cb21;
  goto LAB_0043ca80;
code_r0x0043cb21:
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_2 + 0x1c54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0x51d8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0x9cf0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0x51d8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0x9cf0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_2 + 0x9f14));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar5 = FloatToInt64();
  EncodeOutgoingPacketField((void *)(param_2 + 0x53fc), uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_2 + 0x9f14));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar5 = FloatToInt64();
  EncodeOutgoingPacketField((void *)(param_2 + 0x5620), uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_2 + 0x1c54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0x51d8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0xa138));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0x51d8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0xa138));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_2 + 0xa35c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar5 = FloatToInt64();
  EncodeOutgoingPacketField((void *)(param_2 + 0x5844), uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_2 + 0xa35c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar5 = FloatToInt64();
  EncodeOutgoingPacketField((void *)(param_2 + 0x5a68), uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_2 + 0x1c54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0x51d8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0xa9c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0x51d8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(param_2 + 0xa9c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_2 + 0xabec));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar5 = FloatToInt64();
  EncodeOutgoingPacketField((void *)(param_2 + 0x5c8c), uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_2 + 0xabec));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar5 = FloatToInt64();
  EncodeOutgoingPacketField((void *)(param_2 + 0x5eb0), uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = g_clientContext;
  pbVar12 = (byte *)(g_clientContext + 0x5b818);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = _rand();
  *pbVar12 = (byte)iVar4;
  iVar4 = _rand();
  bVar9 = *pbVar12;
  *(byte *)(iVar2 + 0x5b819) = (byte)iVar4;
  bVar7 = bVar9 & 7;
  bVar7 = ~('\x01' << bVar7) & (byte)iVar4 | '\0' << bVar7;
  *(byte *)(iVar2 + 0x5b819) = bVar7;
  *(byte *)(iVar2 + 0x5b81a) = bVar9 + bVar7 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((byte)(*(byte *)(param_2 + 0x8bba) + *(byte *)(param_2 + 0x8bbb) + -0x34) ==
      *(char *)(param_2 + 0x8bbc)) {
    SUBFIELD(param_2,0,undefined1) =
         '\x01' - ((*(byte *)(param_2 + 0x8bbb) >> (*(byte *)(param_2 + 0x8bba) & 7) & 1) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    SUBFIELD(param_2,0,undefined1) = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((char)param_2 == '\0') {
    cVar10 = FUN_0041eaa0(g_clientContext,*(undefined2 *)(iVar6 + 0xbfbc));
    if (cVar10 == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if ((byte)(*(byte *)(iVar6 + 0x8bb7) + *(byte *)(iVar6 + 0x8bb8) + -0x34) ==
          *(char *)(iVar6 + 0x8bb9)) {
        SUBFIELD(param_2,0,undefined1) =
             '\x01' - ((*(byte *)(iVar6 + 0x8bb8) >> (*(byte *)(iVar6 + 0x8bb7) & 7) & 1) != 1);
      }
      else {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        SUBFIELD(param_2,0,undefined1) = '\0';
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
      *(undefined4 *)(iVar6 + 0xbffa) = SUBFIELD(s_ifire_00553b60,0,undefined4);
      *(undefined2 *)(iVar6 + 0xbffe) = SUBFIELD(s_ifire_00553b60,4,undefined2);
    }
  }
  else {
    *(undefined4 *)(iVar6 + 0xbffa) = SUBFIELD(s_sfire_00553b78,0,undefined4);
    *(undefined2 *)(iVar6 + 0xbffe) = SUBFIELD(s_sfire_00553b78,4,undefined2);
  }
  do {
    do {
      do {
        iVar6 = g_clientContext;
        pbVar12 = &DAT_006aa628 + g_clientContext;
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar2 = _rand();
        *pbVar12 = (byte)iVar2;
        iVar2 = _rand();
        bVar9 = *pbVar12;
        (&DAT_006aa629)[iVar6] = (byte)iVar2;
        bVar7 = bVar9 & 7;
        bVar7 = ~('\x01' << bVar7) & (byte)iVar2 | '\0' << bVar7;
        (&DAT_006aa629)[iVar6] = bVar7;
        (&DAT_006aa62a)[iVar6] = bVar9 + bVar7 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        FUN_00450810((int)(&DAT_006a7f88 + g_clientContext));
        FUN_004f3100((int)(&DAT_006a7f88 + g_clientContext));
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x621e8));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar6 = g_clientContext;
      } while (iVar2 < 0);
      pbVar12 = &DAT_006aa625 + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if ((byte)(*pbVar12 + (&DAT_006aa626)[iVar6] + -0x34) == (&DAT_006aa627)[iVar6]) {
        cVar10 = '\x01' - (((byte)(&DAT_006aa626)[iVar6] >> (*pbVar12 & 7) & 1) != 1);
      }
      else {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        cVar10 = '\0';
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar6 = g_clientContext;
    } while (cVar10 != '\x01');
    pbVar12 = &DAT_006aa628 + g_clientContext;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((byte)(*pbVar12 + (&DAT_006aa629)[iVar6] + -0x34) == (&DAT_006aa62a)[iVar6]) {
      cVar10 = '\x01' - (((byte)(&DAT_006aa629)[iVar6] >> (*pbVar12 & 7) & 1) != 1);
    }
    else {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      cVar10 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  } while (cVar10 != '\0');
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((void *)(g_clientContext + 0x621e8), 0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar6 = g_clientContext;
  pbVar12 = &DAT_006aa625 + g_clientContext;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = _rand();
  *pbVar12 = (byte)iVar2;
  iVar2 = _rand();
  bVar9 = *pbVar12;
  (&DAT_006aa626)[iVar6] = (byte)iVar2;
  bVar7 = bVar9 & 7;
  bVar7 = ~('\x01' << bVar7) & (byte)iVar2 | '\0' << bVar7;
  (&DAT_006aa626)[iVar6] = bVar7;
  (&DAT_006aa627)[iVar6] = bVar9 + bVar7 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar6 = g_clientContext;
  pbVar12 = &DAT_006aa628 + g_clientContext;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = _rand();
  *pbVar12 = (byte)iVar2;
  iVar2 = _rand();
  bVar9 = *pbVar12;
  (&DAT_006aa629)[iVar6] = (byte)iVar2;
  bVar7 = bVar9 & 7;
  bVar7 = ~('\x01' << bVar7) & (byte)iVar2 | '\0' << bVar7;
  (&DAT_006aa629)[iVar6] = bVar7;
  (&DAT_006aa62a)[iVar6] = bVar9 + bVar7 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar6 = _rand();
  *(char *)(param_1 + 4) = (char)iVar6;
  iVar6 = _rand();
  *(byte *)(param_1 + 5) = (byte)iVar6;
  bVar9 = *(byte *)(param_1 + 4) & 7;
  bVar9 = ~('\x01' << bVar9) & (byte)iVar6 | '\0' << bVar9;
  *(byte *)(param_1 + 5) = bVar9;
  *(byte *)(param_1 + 6) = *(byte *)(param_1 + 4) + bVar9 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = g_clientContext;
  iVar6 = *(int *)(&g_nCameraBoundY + g_clientContext);
  iVar2 = *(int *)(&g_nCameraBoundX + g_clientContext);
  puVar11 = *(undefined4 **)(&DAT_006a7740 + g_clientContext);
  puVar13 = *(undefined4 **)(&DAT_006a773c + g_clientContext);
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
      RestorePlayerStateSnapshot();
    }
    iVar6 = iVar6 + 1;
    iVar4 = g_clientContext;
  } while (iVar6 < 8);
  uVar8 = 0;
LAB_0043d480:
  iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
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
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = PeekPacketChecksumState((void *)(iVar6 + 0x1e50));
      EncodeOutgoingPacketField((void *)(iVar6 + 0x25c), uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = PeekPacketChecksumState((void *)(iVar6 + 0x2074));
      EncodeOutgoingPacketField((void *)(iVar6 + 0x480), uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
  iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
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
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = PeekPacketChecksumState((void *)(iVar6 + 0x3fd4));
      EncodeOutgoingPacketField((void *)(iVar6 + 0x40), uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = PeekPacketChecksumState((void *)(iVar6 + 0x41f8));
      EncodeOutgoingPacketField((void *)(iVar6 + 0x264), uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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

