/* GameTick - 0x00413130 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void GameTick(void)

{
  undefined4 *puVar1;
  char cVar2;
  DWORD DVar3;
  char *_Format;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  DWORD DVar7;
  uint uVar8;
  undefined *puVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  char local_400 [1024];
  
  if (g_currentGameState == 0) {
    return;
  }
  if (g_currentGameState == 0xf) {
    return;
  }
  if (g_valueGuardTamperFlag == '\x01') {
    g_valueGuardTamperFlag = '\0';
    ShowErrorDialog(1);
  }
  if ((DAT_00793640 != 0) && (DAT_00793516 == '\0')) {
    g_pendingGameState = 0xf;
    g_stateChangeRequested = '\x01';
    ChangeGameState(0xf);
    DAT_00793516 = '\x01';
  }
  DVar3 = timeGetTime();
  uVar10 = (DVar3 - DAT_007934e0) / 0x32;
  if (DAT_00793521 != '\0') {
    puVar12 = &DAT_005b22d0;
    _Format = (char *)GetLocalizedString(&g_localizedStringTable,9000);
    _sprintf(local_400,_Format,puVar12);
    DAT_00793521 = '\0';
    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_400,2,6);
  }
  if (uVar10 == 0) {
    return;
  }
  PumpBattleActions(uVar10);
  DAT_007934fc = DAT_007934fc + 1;
  if (1 < uVar10) {
    DAT_00793500 = DAT_00793500 + -1 + uVar10;
  }
  g_frameCounter = g_frameCounter + uVar10;
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\x01') {
    SubFromPacketChecksum(uVar10);
    cVar2 = PacketChecksumLessEqual(&DAT_006aa67c + g_clientContext,0);
    if (cVar2 != '\0') {
      SetGuardedBool(0);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9084);
  FUN_0050f290();
  FUN_00406280();
  FUN_0040cf00();
  FUN_0041b6f0();
  FUN_0041c0a0();
  FUN_004022b0();
  FUN_00412130();
  if ((DAT_00793522 == '\0') && (DAT_00793517 == '\0')) {
    DAT_00793517 = 0;
    for (uVar8 = uVar10; uVar8 != 0; uVar8 = uVar8 - 1) {
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x24))();
      FUN_004b3e00();
      if (DAT_0056d118 != -1) {
        DAT_0056d118 = DAT_0056d118 + 1;
      }
    }
  }
  else {
    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x24))();
  }
  DAT_00793517 = 0;
  for (; uVar10 != 0; uVar10 = uVar10 - 1) {
    FUN_004ee540();
    FUN_004ee0d0();
    AdvanceSpriteAnimation();
  }
  if (5 < *(int *)(&DAT_0067e3c8 + g_clientContext)) {
    if (DAT_00793515 == '\0') {
      iVar5 = *(int *)g_gameStateVTableArray[g_currentGameState];
      uVar13 = 6;
      uVar11 = 2;
      DAT_00793515 = '\x01';
      uVar4 = GetLocalizedString(&g_localizedStringTable,0x141);
      (**(code **)(iVar5 + 0x28))(uVar4,uVar11,uVar13);
      *(undefined4 *)(&DAT_0067e3c8 + g_clientContext) = 0;
    }
    else {
      ShowErrorDialog(1);
      *(undefined4 *)(&DAT_0067e3c8 + g_clientContext) = 0;
    }
  }
  FUN_00425770();
  FUN_00422f70(g_clientContext);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9084);
  if (DAT_007934cc == '\0') goto LAB_00413a44;
  g_frameTriangleCounter = 0;
  if (g_pD3DDevice7 != (int *)0x0) {
    (**(code **)(*g_pD3DDevice7 + 0x28))(g_pD3DDevice7,0,0,3,DAT_00793634,0x3f800000,0);
  }
  FUN_004e9070();
  _DAT_00793618 = 0;
  if (g_currentGameState == 0xb) {
    cVar2 = LockBackBuffer(&DAT_0079352c,&DAT_005b3620);
    if (cVar2 == '\0') {
      DAT_0079352c = 0;
    }
    else {
      DAT_005b3620 = DAT_005b3620 / 2;
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x2c))();
      DAT_0079352c = 0;
      (**(code **)(*g_pBackBufferSurface + 0x80))(g_pBackBufferSurface,0);
    }
    iVar5 = (**(int (**)())(*g_pD3DDevice7 + 0x14))(g_pD3DDevice7);
    if (iVar5 == 0) {
      FUN_004f3ea0();
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x30))();
      if (DAT_00793610 != '\0') {
        (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,7,0);
      }
      DAT_00793610 = '\0';
      FUN_004f3ee0();
      (**(code **)(*g_pD3DDevice7 + 0x18))(g_pD3DDevice7);
    }
LAB_00413510:
    cVar2 = LockBackBuffer(&DAT_0079352c,&DAT_005b3620);
    if (cVar2 == '\0') {
      DAT_0079352c = 0;
    }
    else {
      DAT_005b3620 = DAT_005b3620 / 2;
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x34))();
      DAT_0079352c = 0;
      (**(code **)(*g_pBackBufferSurface + 0x80))(g_pBackBufferSurface,0);
    }
    iVar5 = (**(int (**)())(*g_pD3DDevice7 + 0x14))(g_pD3DDevice7);
    if (iVar5 == 0) {
      FUN_004f3ea0();
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x38))();
      if (DAT_00793610 != '\0') {
        (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,7,0);
      }
      DAT_00793610 = '\0';
      FUN_004f3ee0();
      (**(code **)(*g_pD3DDevice7 + 0x18))(g_pD3DDevice7);
    }
  }
  else if ((g_currentGameState == 9) || (g_currentGameState == 7)) goto LAB_00413510;
  cVar2 = LockBackBuffer(&DAT_0079352c,&DAT_005b3620);
  if (cVar2 == '\0') {
    DAT_0079352c = 0;
  }
  else {
    DAT_005b3620 = DAT_005b3620 / 2;
    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x3c))();
    FUN_004b3e60(&DAT_00e9b4e8);
    FUN_004062b0(&DAT_00e9be90);
    FUN_004062b0(&DAT_00e9c0fc);
    iVar5 = DAT_00e53c48;
    while (iVar5 != 0) {
      puVar1 = (undefined4 *)(iVar5 + 8);
      iVar5 = *(int *)(iVar5 + 4);
      (**(code **)(*(int *)*puVar1 + 0x24))();
    }
    if ((g_stateChangeInProgress == 0) && (0x28 < DAT_0056d118)) {
      FUN_004eb890();
    }
    DAT_0079352c = 0;
    (**(code **)(*g_pBackBufferSurface + 0x80))(g_pBackBufferSurface,0);
  }
  iVar5 = (**(int (**)())(*g_pD3DDevice7 + 0x14))(g_pD3DDevice7);
  if (iVar5 == 0) {
    *(undefined4 *)(DAT_00792190 + 0x7c) = 0;
    DAT_00793660 = 1;
    if (DAT_00793611 != '\0') {
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,0);
    }
    DAT_00793611 = '\0';
    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x40))();
    if (DAT_0056d108 == -1) {
LAB_00413791:
      if (((g_stateChangeInProgress != 0) || (DAT_0079350c != '\0')) || (DAT_0079350d != '\0'))
      goto LAB_004137a9;
    }
    else {
      if (g_stateChangeInProgress == 0) {
        if (g_currentBlendMode != 1) {
          g_currentBlendMode = 1;
          _DAT_00792194 = 1;
          (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
          (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
        }
        (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
        FUN_004edaa0(0xffffffff,0xffffffff,800,0xffffffff,0xffffffff,
                     *(undefined4 *)(DAT_0056d108 * 4 + 0x56d11c));
        FUN_004edaa0(800,600 - *(int *)(DAT_0056d108 * 4 + 0x56d11c),800,600,0xffffffff,600);
        goto LAB_00413791;
      }
LAB_004137a9:
      if (g_currentBlendMode != 1) {
        g_currentBlendMode = 1;
        _DAT_00792194 = 1;
        (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
        (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
      }
      BuildColorQuad(0,0,799,0,799,599,0,599,0,0,0,0,0x80000000,0x80000000);
    }
    if (DAT_00793610 != '\0') {
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,7,0);
    }
    DAT_00793610 = '\0';
    FUN_004f3ee0();
    (**(code **)(*g_pD3DDevice7 + 0x18))(g_pD3DDevice7);
  }
  cVar2 = LockBackBuffer(&DAT_0079352c,&DAT_005b3620);
  if (cVar2 == '\0') {
    DAT_0079352c = 0;
  }
  else {
    DAT_005b3620 = DAT_005b3620 / 2;
    if (DAT_0079350d != '\0') {
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x44))();
    }
    if (g_stateChangeInProgress == 0) {
      if (DAT_0079350d != '\0') goto LAB_00413933;
    }
    else {
      if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
        if (*(char *)(iVar5 + 0x18) == '\x01') {
          BlitSprite16bpp(0xf9,0xc1);
        }
        else {
          BlitSpriteClipped(0);
        }
      }
      BlitRLESprite(0xcf,0xffff);
      iVar5 = 0xec;
      puVar9 = &DAT_005b1da2;
      do {
        BlitRLESprite(iVar5,0xffff);
        puVar9 = puVar9 + 0x32;
        iVar5 = iVar5 + 0xe;
      } while ((int)puVar9 < 0x5b1ece);
LAB_00413933:
      FUN_004062b0(&DAT_00e9be90);
      FUN_004062b0(&DAT_00e9c0fc);
    }
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\x01') && (g_frameCounter % 0x14 < 10)) {
      if (DAT_0079352c != 0) {
        iVar5 = FindSpriteFrame();
        if (iVar5 != 0) {
          if (*(char *)(iVar5 + 0x18) == '\x01') {
            BlitSprite16bpp(0x2fc,8);
          }
          else {
            BlitSpriteClipped(0);
          }
        }
        goto LAB_004139be;
      }
    }
    else {
LAB_004139be:
      iVar5 = g_cursorFrame;
      if (((DAT_0079352c != 0) && (-1 < g_cursorFrame)) && (iVar6 = FindSpriteFrame(), iVar6 != 0)) {
        if (*(char *)(iVar6 + 0x18) == '\x01') {
          BlitSprite16bpp(g_cursorAnchorX,g_cursorAnchorY);
        }
        else {
          BlitSpriteClipped(iVar5);
        }
      }
    }
    if (DAT_00793520 != '\0') {
      DAT_00793520 = '\0';
      FUN_00412e50();
    }
    DAT_0079352c = 0;
    (**(code **)(*g_pBackBufferSurface + 0x80))(g_pBackBufferSurface,0);
  }
  PresentFrame();
LAB_00413a44:
  DVar7 = timeGetTime();
  DAT_007934e0 = DVar3 - (DVar3 - DAT_007934e0) % 0x32;
  uVar10 = (DVar3 - DVar7) + 0x2d;
  Sleep(uVar10 & ((int)uVar10 < 1) - 1);
  timeGetTime();
  if (((DAT_0056d108 != -1) && (g_stateChangeInProgress == 0)) &&
     (DAT_0056d108 = DAT_0056d108 + _DAT_007934d8, DAT_0056d108 == 0xb)) {
    DAT_0056d108 = -1;
    ChangeGameState(g_pendingGameState);
  }
  if (g_stateChangeRequested != '\0') {
    ChangeGameState(g_pendingGameState);
  }
  DAT_00e536c4 = 0;
  DAT_00e536c0 = 0;
  return;
}

