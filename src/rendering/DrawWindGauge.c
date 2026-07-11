/* DrawWindGauge - 0x00406990 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void DrawWindGauge(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  uint uVar11;
  code *pcVar12;
  bool bVar13;
  int local_fa0;
  int local_f9c [2];
  uint local_f94;
  undefined1 local_f90 [8];
  char local_f88 [128];
  undefined1 local_f08 [20];
  int local_ef4;
  undefined1 local_ce4 [20];
  int local_cd0;
  undefined1 local_ac0 [20];
  int local_aac;
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [548];
  undefined1 local_230 [20];
  int local_21c;
  int local_4;
  
  iVar2 = DAT_00ea0e1c;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00538f51) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. local_4
   * is a real, separate local (an exception-cleanup index) reused
   * throughout this function; its `._0_1_`/`._1_3_` partial-field
   * accesses are rewritten as plain int operations, same reasoning as
   * FUN_004174c0.c's fix. */
  g_nCompositorLayer = 3;
  iVar2 = *(int *)(iVar2 + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      bVar13 = true;
      if (*(int *)(iVar2 + 8) == 0) goto LAB_004069e1;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
  goto LAB_00406a12;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    bVar13 = *(int *)(iVar2 + 8) == 0;
    if (!bVar13) break;
LAB_004069e1:
    if (bVar13) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
        QueueTextureRegionSpans(0);
      }
      break;
    }
  }
LAB_00406a12:
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 < 2) goto LAB_00406a43;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00406a78:
  if (*(char *)(g_clientContext + 0x3b6c0) == -1) {
LAB_00408159:
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 == 1) {
    QueueSpriteSpansByContentId(7000);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 == 3) {
    QueueSpriteSpansByContentId(7000);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 < 1) {
    uVar9 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar3 = EncodeChecksumDeltaMul(*(int *)(g_clientContext + 0x621e0) + 0x7864,local_89c,0x28);
  local_4 = 0;
  uVar9 = EncodeChecksumDeltaDiv(uVar3,local_678,uVar9);
  local_4 = 1;
  EncodeChecksumDeltaAdd(uVar9,local_ce4,0xf4);
  local_4 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  SetClipRect();
  local_4 = 1;
  if (local_cd0 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_f9c);
  }
  local_4 = 0;
  if (local_664 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_f9c);
  }
  local_4 = 0xffffffff;
  if (local_888 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_f9c);
  }
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 < 3) goto LAB_00406d0a;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00406d42:
  SetClipRect();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 < 1) {
    uVar9 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar3 = EncodeChecksumDeltaMul(*(int *)(g_clientContext + 0x621e0) + 0x7a88,local_ce4,0x28);
  local_4 = 3;
  uVar9 = EncodeChecksumDeltaDiv(uVar3,local_678,uVar9);
  local_4 = 4;
  EncodeChecksumDeltaAdd(uVar9,local_89c,0xf5);
  local_4 = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 < 5) goto LAB_00406e61;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00406e95:
  local_4 = 4;
  if (local_888 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_f9c);
  }
  local_4 = 3;
  if (local_664 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_f9c);
  }
  local_4 = 0xffffffff;
  if (local_cd0 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_f9c);
  }
  if (*param_1 == -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar2 == 6) goto LAB_00406f80;
    iVar2 = 0;
    iVar10 = 0;
    iVar5 = 0x1f5;
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar6 == 0xff) {
          uVar9 = EncodeChecksumDeltaSub(iVar10 + 0x3a154 + g_clientContext,local_ce4,1);
          local_4 = 6;
          uVar9 = EncodeChecksumDeltaMul(uVar9,local_678,2);
          local_4 = 7;
          EncodeChecksumDeltaAdd(uVar9,local_89c,iVar2 == *(int *)(g_clientContext + 0xf0374));
          local_4 = 8;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          QueueSpriteSpansByContentId(0x1b5a);
          local_4 = 7;
          ScrubChecksumGuard();
          local_4 = 6;
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          iVar2 = iVar2 + 1;
          iVar10 = iVar10 + 0x224;
          iVar5 = iVar5 + 0x24;
        }
        else {
          uVar9 = EncodeChecksumDeltaSub(iVar10 + 0x39f30 + g_clientContext,local_f08,1);
          local_4 = 9;
          uVar9 = EncodeChecksumDeltaMul(uVar9,local_ac0,2);
          local_4 = 10;
          EncodeChecksumDeltaAdd(uVar9,local_454,iVar2 == *(int *)(g_clientContext + 0xf0374));
          local_4 = 0xb;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          QueueSpriteSpansByContentId(0x1b59);
          local_4 = 10;
          ScrubChecksumGuard();
          local_4 = 9;
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
        }
      }
      iVar5 = iVar5 + 0x24;
      iVar2 = iVar2 + 1;
      iVar10 = iVar10 + 0x224;
    } while (iVar5 < 0x2cd);
  }
  else {
LAB_00406f80:
    QueueSpriteSpansByContentId(7000);
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    EncodeChecksumDeltaDiv(*(int *)(g_clientContext + 0x621e0) + 0x8bc4,local_f08,200);
    local_4 = 0xc;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueSpriteSpansByContentId(500);
    local_4 = 0xffffffff;
    if (local_ef4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_f9c);
    }
    uVar9 = EncodeChecksumDeltaDiv(*(int *)(g_clientContext + 0x621e0) + 0x8bc4,local_ac0,0x14);
    local_4 = 0xd;
    EncodeChecksumDeltaMod(uVar9,local_f08,10);
    local_4 = 0xe;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueSpriteSpansByContentId(500);
    local_4 = 0xd;
    if (local_ef4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_f9c);
    }
    local_4 = 0xffffffff;
    if (local_aac != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_f9c);
    }
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1f5) {
      if (uVar11 == 500) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0x9d) goto LAB_004073ee;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
LAB_00407429:
    uVar9 = EncodeChecksumDeltaDiv(*(int *)(g_clientContext + 0x621e0) + 0x8bc4,local_ac0,2);
    local_4 = 0xf;
    EncodeChecksumDeltaMod(uVar9,local_f08,10);
    local_4 = 0x10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueSpriteSpansByContentId(500);
    local_4 = 0xf;
    if (local_ef4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_f9c);
    }
    local_4 = 0xffffffff;
    if (local_aac != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_f9c);
    }
  }
  pcVar12 = (code *)EnterCriticalSection;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  _sprintf(local_f88,&DAT_00551ed4,uVar9);
  pcVar4 = local_f88;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if ((int)pcVar4 - (int)(local_f88 + 1) == 2) {
    iVar10 = 0;
    iVar2 = 0x186;
    do {
      if (local_f88[iVar10] != ' ') {
        QueueSpriteSpansByContentId(500);
      }
      iVar2 = iVar2 + 0xb;
      iVar10 = iVar10 + 1;
    } while (iVar2 < 0x19c);
  }
  else {
    QueueSpriteSpansByContentId(500);
  }
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1f5) {
    if (uVar11 == 500) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 < 0xb2) goto LAB_004075f6;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00407631:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 < 0) {
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1f5) {
      if (uVar11 == 500) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb3) goto LAB_00407694;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
  }
LAB_004076cf:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  uVar11 = iVar2 / 10 + 0xb3;
  iVar10 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = *(uint *)(iVar10 + 4);
  while (uVar8 < 0x1f5) {
    if (uVar8 == 500) {
      iVar10 = *(int *)(iVar10 + 0x10);
      uVar8 = *(uint *)(iVar10 + 8);
      if (uVar8 <= uVar11) goto LAB_00407742;
      break;
    }
    iVar10 = *(int *)(iVar10 + 0x1c);
    uVar8 = *(uint *)(iVar10 + 4);
  }
LAB_00407778:
  iVar10 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = iVar2 % 10 + 0xb3;
  uVar8 = *(uint *)(iVar10 + 4);
  while (uVar8 < 0x1f5) {
    if (uVar8 == 500) {
      iVar2 = *(int *)(iVar10 + 0x10);
      uVar8 = *(uint *)(iVar2 + 8);
      if (uVar8 <= uVar11) goto LAB_004077ad;
      break;
    }
    iVar10 = *(int *)(iVar10 + 0x1c);
    uVar8 = *(uint *)(iVar10 + 4);
  }
LAB_004077e3:
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = (byte)(&DAT_005f2f40)[g_clientContext] + 9;
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 <= uVar8) goto LAB_00407823;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00407859:
  if ((char)param_1[10] != '\0') {
    QueueSpriteSpansByContentId(7000);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar2) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SetClipRect();
    QueueSpriteSpansByContentId(7000);
    SetClipRect();
    pcVar12 = (code *)EnterCriticalSection;
  }
  (*pcVar12)(&DAT_005a9068);
  uVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  switch(uVar9) {
  case 0:
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb0) goto LAB_004079ff;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
    break;
  case 1:
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb2) goto LAB_00407a7a;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
    break;
  case 2:
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb1) goto LAB_00407af4;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
    break;
  case 3:
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb3) goto LAB_00407b5d;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
  }
  goto switchD_004079b9_default;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (1 < uVar11) break;
LAB_00406a43:
    if (uVar11 == 1) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
        QueueTextureRegionSpans(0);
      }
      break;
    }
  }
  goto LAB_00406a78;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (2 < uVar11) break;
LAB_00406d0a:
    if (uVar11 == 2) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
        QueueTextureRegionSpans(0xf4);
      }
      break;
    }
  }
  goto LAB_00406d42;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (4 < uVar11) break;
LAB_00406e61:
    if (uVar11 == 4) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
        QueueTextureRegionSpans(uVar9);
      }
      break;
    }
  }
  goto LAB_00406e95;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0x9c < uVar11) break;
LAB_004073ee:
    if (uVar11 == 0x9c) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
        QueueTextureRegionSpans(0x2f7);
      }
      break;
    }
  }
  goto LAB_00407429;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb1 < uVar11) break;
LAB_004075f6:
    if (uVar11 == 0xb1) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
        QueueTextureRegionSpans(0x187);
      }
      break;
    }
  }
  goto LAB_00407631;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb2 < uVar11) break;
LAB_00407694:
    if (uVar11 == 0xb2) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
        QueueTextureRegionSpans(0x8a);
      }
      break;
    }
  }
  goto LAB_004076cf;
  while( true ) {
    iVar10 = *(int *)(iVar10 + 0x10);
    uVar8 = *(uint *)(iVar10 + 8);
    if (uVar11 < uVar8) break;
LAB_00407742:
    if (uVar8 == uVar11) {
      if (-1 < (int)uVar11) {
        if (*(char *)(iVar10 + 0x18) == '\x01') {
          QueueSpriteFrameSpans();
        }
        else {
          QueueTextureRegionSpans(0x91);
        }
      }
      break;
    }
  }
  goto LAB_00407778;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (uVar11 < uVar8) break;
LAB_004077ad:
    if (uVar8 == uVar11) {
      if (-1 < (int)uVar11) {
        if (*(char *)(iVar2 + 0x18) == '\x01') {
          QueueSpriteFrameSpans();
        }
        else {
          QueueTextureRegionSpans(0x99);
        }
      }
      break;
    }
  }
  goto LAB_004077e3;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (uVar8 < uVar11) break;
LAB_00407823:
    if (uVar11 == uVar8) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
        QueueTextureRegionSpans(0xab);
      }
      break;
    }
  }
  goto LAB_00407859;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb2 < uVar11) break;
LAB_00407b5d:
    if (uVar11 == 0xb2) {
      if (*(char *)(iVar2 + 0x18) != '\x01') goto LAB_00407b8f;
      QueueSpriteFrameSpans(0x141);
      break;
    }
  }
  goto switchD_004079b9_default;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb0 < uVar11) break;
LAB_00407af4:
    if (uVar11 == 0xb0) {
      if (*(char *)(iVar2 + 0x18) != '\x01') goto LAB_00407b8f;
      QueueSpriteFrameSpans(0x141);
      break;
    }
  }
  goto switchD_004079b9_default;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb1 < uVar11) break;
LAB_00407a7a:
    if (uVar11 == 0xb1) {
      if (*(char *)(iVar2 + 0x18) != '\x01') goto LAB_00407b8f;
      QueueSpriteFrameSpans(0x141);
      break;
    }
  }
  goto switchD_004079b9_default;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xaf < uVar11) break;
LAB_004079ff:
    if (uVar11 == 0xaf) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
LAB_00407b8f:
        QueueTextureRegionSpans(0x141);
      }
      break;
    }
  }
switchD_004079b9_default:
  _sprintf(local_f88,(char *)&PTR_DAT_00551ed0,param_1[0xd]);
  iVar10 = 0;
  iVar2 = 0x15e;
LAB_00407bb4:
  cVar1 = local_f88[iVar10];
  if (cVar1 != ' ') {
    if (cVar1 == '-') {
      iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar11 = *(uint *)(iVar5 + 4);
      while (uVar11 < 0x1f5) {
        if (uVar11 == 500) {
          iVar5 = *(int *)(iVar5 + 0x10);
          uVar11 = *(uint *)(iVar5 + 8);
          if (uVar11 < 0x92) goto LAB_00407c03;
          break;
        }
        iVar5 = *(int *)(iVar5 + 0x1c);
        uVar11 = *(uint *)(iVar5 + 4);
      }
    }
    else {
      iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar8 = (int)cVar1 + 0x57;
      uVar11 = *(uint *)(iVar5 + 4);
      while (uVar11 < 0x1f5) {
        if (uVar11 == 500) {
          iVar5 = *(int *)(iVar5 + 0x10);
          uVar11 = *(uint *)(iVar5 + 8);
          if (uVar11 <= uVar8) goto LAB_00407c6b;
          break;
        }
        iVar5 = *(int *)(iVar5 + 0x1c);
        uVar11 = *(uint *)(iVar5 + 4);
      }
    }
  }
  goto LAB_00407c9d;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar11 = *(uint *)(iVar5 + 8);
    if (uVar8 < uVar11) break;
LAB_00407c6b:
    if (uVar11 == uVar8) {
      if (-1 < (int)uVar8) {
        if (*(char *)(iVar5 + 0x18) != '\x01') goto LAB_00407c95;
        QueueSpriteFrameSpans(iVar2);
      }
      break;
    }
  }
  goto LAB_00407c9d;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar11 = *(uint *)(iVar5 + 8);
    if (0x91 < uVar11) break;
LAB_00407c03:
    if (uVar11 == 0x91) {
      if (*(char *)(iVar5 + 0x18) == '\x01') {
        QueueSpriteFrameSpans();
      }
      else {
LAB_00407c95:
        QueueTextureRegionSpans(iVar2);
      }
      break;
    }
  }
LAB_00407c9d:
  iVar2 = iVar2 + 0x14;
  iVar10 = iVar10 + 1;
  if (0x1c1 < iVar2) goto code_r0x00407cad;
  goto LAB_00407bb4;
code_r0x00407cad:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 == -1) goto LAB_00407df7;
  EncodeChecksumDeltaMul(g_clientContext + 0xebcbc,local_f08,0x14);
  local_4 = 0x11;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = param_1[0xf] % 0x14 + 0x19 + iVar2;
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = *(uint *)(iVar2 + 4);
  while (uVar8 < 0x1b59) {
    if (uVar8 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar8 = *(uint *)(iVar2 + 8);
      if (uVar8 <= uVar11) goto LAB_00407d6b;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar8 = *(uint *)(iVar2 + 4);
  }
  goto LAB_00407d9e;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (uVar11 < uVar8) break;
LAB_00407d6b:
    if (uVar8 == uVar11) {
      if (-1 < (int)uVar11) {
        if (*(char *)(iVar2 + 0x18) == '\x01') {
          QueueSpriteFrameSpans();
        }
        else {
          QueueTextureRegionSpans(0x53);
        }
      }
      break;
    }
  }
LAB_00407d9e:
  local_4 = 0xffffffff;
  if (local_ef4 != 0) {
    iVar2 = local_ef4 << 4;
    iVar10 = 0x10;
    do {
      iVar5 = _rand();
      *(char *)(iVar2 + DAT_0079376c) = (char)iVar5;
      iVar2 = iVar2 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    TreeLowerBound(local_f9c);
  }
LAB_00407df7:
  SetClipRect();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 + -1 < 0) {
    iVar2 = 0;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = iVar2 + -1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar10 < 1) {
    iVar10 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 + -1 < 0) {
    iVar6 = 0;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = iVar6 + -1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar7 < 1) {
    iVar7 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  local_fa0 = 6;
  local_f94 = iVar6 / iVar7 + 1;
  iVar2 = 0x80 - ((iVar2 % iVar5) * 0x23) / iVar10;
LAB_00407fd0:
  uVar11 = local_f94 & 0x80000007;
  if ((int)uVar11 < 0) {
    uVar11 = (uVar11 - 1 | 0xfffffff8) + 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar10 != -1) {
    EncodeChecksumDeltaAdd(uVar11 * 0x224 + 0x595d8 + g_clientContext,local_230,0xa5);
    local_4 = 0x12;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar10 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar10 = *(int *)(iVar10 + 0x10);
        uVar11 = *(uint *)(iVar10 + 8);
        if (uVar11 <= uVar8) goto LAB_0040809a;
        break;
      }
      iVar10 = *(int *)(iVar10 + 0x1c);
      uVar11 = *(uint *)(iVar10 + 4);
    }
    goto LAB_004080ce;
  }
  goto LAB_00408127;
  while( true ) {
    iVar10 = *(int *)(iVar10 + 0x10);
    uVar11 = *(uint *)(iVar10 + 8);
    if (uVar8 < uVar11) break;
LAB_0040809a:
    if (uVar11 == uVar8) {
      if (-1 < (int)uVar8) {
        if (*(char *)(iVar10 + 0x18) == '\x01') {
          QueueSpriteFrameSpans();
        }
        else {
          QueueTextureRegionSpans(iVar2);
        }
      }
      break;
    }
  }
LAB_004080ce:
  iVar10 = local_21c;
  local_4 = 0xffffffff;
  if (local_21c != 0) {
    iVar5 = local_21c << 4;
    iVar6 = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar5 + DAT_0079376c) = (char)iVar7;
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    local_f9c[0] = iVar10;
    TreeLowerBound(local_f90);
  }
LAB_00408127:
  local_f94 = local_f94 + 1;
  iVar2 = iVar2 + 0x23;
  local_fa0 = local_fa0 + -1;
  if (local_fa0 == 0) goto code_r0x00408142;
  goto LAB_00407fd0;
code_r0x00408142:
  SetClipRect();
  goto LAB_00408159;
}

