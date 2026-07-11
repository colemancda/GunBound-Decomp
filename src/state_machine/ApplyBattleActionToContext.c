/* ApplyBattleActionToContext - 0x00423130 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void ApplyBattleActionToContext(int param_1,int param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  undefined *puVar4;
  char cVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int *piVar11;
  ushort *puVar12;
  int *piVar13;
  int *piVar14;
  uint uVar15;
  undefined4 *puVar16;
  ushort *puVar17;
  undefined4 *puVar18;
  byte *pbVar19;
  int local_438;
  undefined4 local_430;
  undefined4 local_42c;
  undefined4 local_428;
  undefined4 local_424;
  undefined1 local_420;
  undefined4 local_41c;
  undefined4 local_418;
  undefined4 local_414;
  undefined1 local_410;
  byte local_408;
  byte local_407 [2];
  byte abStack_405 [1025];
  
  puVar4 = g_gameStateVTableArray[0xb];
  uVar3 = *(ushort *)(param_2 + 2);
  bVar1 = *(byte *)(param_2 + 5);
  puVar12 = (ushort *)(param_2 + 0x21);
  if (uVar3 < 0x8102) {
    if (uVar3 == 0x8101) {
      if (7 < bVar1) {
        return;
      }
      *(byte *)(bVar1 + 0x4590c + param_1) = *(byte *)puVar12;
      return;
    }
    if (0x8001 < uVar3) {
      if (uVar3 == 0x8002) {
        *(byte *)(param_1 + 0x45124) = *(byte *)puVar12;
        return;
      }
      if (uVar3 == 0x8004) {
        *(undefined4 *)(param_1 + 0x457a1) = *(undefined4 *)puVar12;
        *(undefined4 *)(param_1 + 0x457a5) = *(undefined4 *)(param_2 + 0x25);
        return;
      }
      if (uVar3 != 0x8100) {
        return;
      }
      if (7 < bVar1) {
        return;
      }
      *(byte *)(param_1 + 0x458fc + (uint)bVar1 * 2) = *(byte *)puVar12;
      *(undefined1 *)(param_1 + 0x458fd + (uint)bVar1 * 2) = *(undefined1 *)(param_2 + 0x22);
      return;
    }
    if (uVar3 == 0x8001) {
      QueueOutgoingPacketField(*(undefined4 *)puVar12);
      return;
    }
    if (uVar3 == 1) {
      if ((g_currentGameState != 3) && (g_currentGameState != 4)) {
        iVar8 = (uint)bVar1 * 0xd + 0x457f1 + param_1;
        iVar7 = FUN_004259d0(iVar8);
        if (iVar7 != -1) {
          return;
        }
        local_408 = 0;
        pbVar19 = local_407;
        for (iVar7 = 0xff; iVar7 != 0; iVar7 = iVar7 + -1) {
          pbVar19[0] = 0;
          pbVar19[1] = 0;
          pbVar19[2] = 0;
          pbVar19[3] = 0;
          pbVar19 = pbVar19 + 4;
        }
        pbVar19[0] = 0;
        pbVar19[1] = 0;
        pbVar19[2] = 0;
        puVar17 = puVar12;
        pbVar19 = &local_408;
        for (uVar10 = param_3 - 0x21U >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined4 *)pbVar19 = *(undefined4 *)puVar17;
          puVar17 = puVar17 + 2;
          pbVar19 = pbVar19 + 4;
        }
        uVar6 = 0;
        for (uVar10 = param_3 - 0x21U & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
          *pbVar19 = (byte)*puVar17;
          puVar17 = (ushort *)((int)puVar17 + 1);
          pbVar19 = pbVar19 + 1;
        }
        FUN_004e3740(&DAT_00794e14);
        AcquireSoundChannel(uVar6);
        FUN_0041b8c0(param_1,0,(uint)bVar1 * 9 + 0x457a9 + param_1,iVar8,puVar12,0,1);
        return;
      }
      iVar8 = (uint)bVar1 * 0xd + 0x41445 + param_1;
      iVar7 = FUN_004259d0(iVar8);
      if (iVar7 != -1) {
        return;
      }
      FUN_0041b8c0(param_1,0,(uint)bVar1 * 9 + 0x43548 + param_1,iVar8,puVar12,0,0);
      return;
    }
    if (uVar3 != 0x307) {
      if (uVar3 != 0x8000) {
        return;
      }
      *(byte *)(param_1 + 0x44ef8) = *(byte *)puVar12;
      QueueOutgoingPacketField(*(undefined4 *)(param_2 + 0x22));
      *(undefined1 *)(param_1 + 0x45124) = *(undefined1 *)(param_2 + 0x26);
      *(undefined4 *)(param_1 + 0x457a1) = *(undefined4 *)(param_2 + 0x27);
      iVar8 = g_clientContext;
      *(undefined4 *)(param_1 + 0x457a5) = *(undefined4 *)(param_2 + 0x2b);
      uVar15 = param_3 - 0x2f;
      uVar9 = ((int)uVar15 < 0) - 1 & uVar15;
      puVar16 = (undefined4 *)(param_2 + 0x2f);
      puVar18 = (undefined4 *)(iVar8 + 0x44e64);
      for (uVar10 = uVar9 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar18 = *puVar16;
        puVar16 = puVar16 + 1;
        puVar18 = puVar18 + 1;
      }
      for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined1 *)puVar18 = *(undefined1 *)puVar16;
        puVar16 = (undefined4 *)((int)puVar16 + 1);
        puVar18 = (undefined4 *)((int)puVar18 + 1);
      }
      *(undefined1 *)(iVar8 + 0x44e64 + uVar15) = 0;
      return;
    }
    bVar2 = *(byte *)puVar12;
    if (bVar2 != 2) {
      if (bVar2 == 0xe) {
        cVar5 = PacketChecksumEquals(param_1 + 0x621e8,0xffffffff);
        if (cVar5 == '\0') {
          return;
        }
        goto LAB_0042326c;
      }
      if (bVar2 != 0xf) {
        return;
      }
    }
    if (((*(int *)(g_gameStateVTableArray[0xb] + 0x10b4) == -1) &&
        (cVar5 = PacketChecksumEquals(g_clientContext + 0x6240c,0xffffffff), cVar5 != '\0')) &&
       (puVar4[0x10bd] == '\0')) {
LAB_0042326c:
      FUN_004e7d60(0xffff);
      Replay_AppendEvent(0xc302);
      iVar8 = g_clientContext;
      (&g_replayEventBuffer)[g_replayEventCursor] = *(byte *)puVar12;
      g_replayEventCursor = g_replayEventCursor + 1;
      uVar6 = PeekChecksumStateUnderLock(iVar8 + 0xeba98);
      *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar6;
      g_replayEventCursor = g_replayEventCursor + 4;
      if (*(byte *)puVar12 == 0xe) {
        uVar6 = FUN_0045d360(0);
        *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar6;
        g_replayEventCursor = g_replayEventCursor + 4;
      }
      FUN_004e7140(bVar1);
      return;
    }
  }
  else if (uVar3 < 0x8401) {
    if (uVar3 == 0x8400) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar8 < (int)(uint)*puVar12) {
        ShowErrorDialog(1);
      }
      local_430 = *(undefined4 *)(param_2 + 0x23);
      local_42c = *(undefined4 *)(param_2 + 0x27);
      local_428 = *(undefined4 *)(param_2 + 0x2b);
      local_424 = *(undefined4 *)(param_2 + 0x2f);
      local_41c = *(undefined4 *)(param_2 + 0x33);
      local_418 = *(undefined4 *)(param_2 + 0x37);
      local_414 = *(undefined4 *)(param_2 + 0x3b);
      local_420 = 0;
      local_410 = 0;
      FUN_00426620(&DAT_006aa41c + param_1,&local_430);
      FUN_00426620(&DAT_006aa44c + param_1,&local_41c);
      iVar8 = g_clientContext;
      uVar10 = (uint)bVar1;
      *(uint *)(g_clientContext + 0x4599c + uVar10 * 4) = (uint)*(ushort *)(param_2 + 0x3f);
      *(undefined4 *)(iVar8 + 0x4593c + uVar10 * 4) = *(undefined4 *)(param_2 + 0x41);
      *(undefined4 *)(iVar8 + 0x4595c + uVar10 * 4) = *(undefined4 *)(param_2 + 0x45);
      *(undefined4 *)(iVar8 + 0x4597c + uVar10 * 4) = *(undefined4 *)(param_2 + 0x49);
      *(undefined4 *)(iVar8 + 0x4663c + uVar10 * 4) = 0;
      *(undefined4 *)(iVar8 + 0x4665c + uVar10 * 4) = 0;
      iVar7 = uVar10 * 0x50 + iVar8;
      piVar13 = (int *)(param_2 + 0x4d);
      piVar11 = (int *)(iVar7 + 0x459bc);
      local_438 = 4;
      do {
        *piVar11 = *piVar13;
        piVar11[0xa0] = piVar13[1];
        piVar11[0x280] = piVar11[0xa0] + *piVar11;
        piVar14 = (int *)(iVar8 + 0x4663c + uVar10 * 4);
        *piVar14 = *piVar14 + *piVar11;
        *(int *)(iVar8 + 0x4665c + uVar10 * 4) =
             *(int *)(iVar8 + 0x4665c + uVar10 * 4) + piVar11[0xa0];
        piVar11[1] = piVar13[2];
        piVar11[0xa1] = piVar13[3];
        piVar11[0x281] = piVar11[0xa1] + piVar11[1];
        piVar14 = (int *)(iVar8 + 0x4663c + uVar10 * 4);
        *piVar14 = *piVar14 + piVar11[1];
        *(int *)(iVar8 + 0x4665c + uVar10 * 4) =
             *(int *)(iVar8 + 0x4665c + uVar10 * 4) + piVar11[0xa1];
        piVar11[2] = piVar13[4];
        piVar11[0xa2] = piVar13[5];
        piVar11[0x282] = piVar11[0xa2] + piVar11[2];
        piVar14 = (int *)(iVar8 + 0x4663c + uVar10 * 4);
        *piVar14 = *piVar14 + piVar11[2];
        *(int *)(iVar8 + 0x4665c + uVar10 * 4) =
             *(int *)(iVar8 + 0x4665c + uVar10 * 4) + piVar11[0xa2];
        piVar11[3] = piVar13[6];
        piVar11[0xa3] = piVar13[7];
        piVar11[0x283] = piVar11[0xa3] + piVar11[3];
        piVar14 = (int *)(iVar8 + 0x4663c + uVar10 * 4);
        *piVar14 = *piVar14 + piVar11[3];
        *(int *)(iVar8 + 0x4665c + uVar10 * 4) =
             *(int *)(iVar8 + 0x4665c + uVar10 * 4) + piVar11[0xa3];
        piVar11[4] = piVar13[8];
        piVar11[0xa4] = piVar13[9];
        piVar11[0x284] = piVar11[0xa4] + piVar11[4];
        piVar13 = piVar13 + 10;
        *(int *)(iVar8 + 0x4663c + uVar10 * 4) = *(int *)(iVar8 + 0x4663c + uVar10 * 4) + piVar11[4]
        ;
        piVar14 = piVar11 + 0xa4;
        piVar11 = piVar11 + 5;
        local_438 = local_438 + -1;
        *(int *)(iVar8 + 0x4665c + uVar10 * 4) = *(int *)(iVar8 + 0x4665c + uVar10 * 4) + *piVar14;
      } while (local_438 != 0);
      *(undefined4 *)(iVar8 + 0x472fc + uVar10 * 4) = 0;
      *(undefined4 *)(iVar8 + 0x4731c + uVar10 * 4) = 0;
      piVar11 = (int *)(iVar7 + 0x4667c);
      local_438 = 4;
      do {
        piVar14 = piVar13;
        *piVar11 = *piVar14;
        piVar11[0xa0] = piVar14[1];
        piVar11[0x280] = piVar11[0xa0] + *piVar11;
        piVar13 = (int *)(iVar8 + 0x472fc + uVar10 * 4);
        *piVar13 = *piVar13 + *piVar11;
        *(int *)(iVar8 + 0x4731c + uVar10 * 4) =
             *(int *)(iVar8 + 0x4731c + uVar10 * 4) + piVar11[0xa0];
        piVar11[1] = piVar14[2];
        piVar11[0xa1] = piVar14[3];
        piVar11[0x281] = piVar11[0xa1] + piVar11[1];
        piVar13 = (int *)(iVar8 + 0x472fc + uVar10 * 4);
        *piVar13 = *piVar13 + piVar11[1];
        *(int *)(iVar8 + 0x4731c + uVar10 * 4) =
             *(int *)(iVar8 + 0x4731c + uVar10 * 4) + piVar11[0xa1];
        piVar11[2] = piVar14[4];
        piVar11[0xa2] = piVar14[5];
        piVar11[0x282] = piVar11[0xa2] + piVar11[2];
        piVar13 = (int *)(iVar8 + 0x472fc + uVar10 * 4);
        *piVar13 = *piVar13 + piVar11[2];
        *(int *)(iVar8 + 0x4731c + uVar10 * 4) =
             *(int *)(iVar8 + 0x4731c + uVar10 * 4) + piVar11[0xa2];
        piVar11[3] = piVar14[6];
        piVar11[0xa3] = piVar14[7];
        piVar11[0x283] = piVar11[0xa3] + piVar11[3];
        piVar13 = (int *)(iVar8 + 0x472fc + uVar10 * 4);
        *piVar13 = *piVar13 + piVar11[3];
        *(int *)(iVar8 + 0x4731c + uVar10 * 4) =
             *(int *)(iVar8 + 0x4731c + uVar10 * 4) + piVar11[0xa3];
        piVar11[4] = piVar14[8];
        piVar11[0xa4] = piVar14[9];
        piVar11[0x284] = piVar11[0xa4] + piVar11[4];
        *(int *)(iVar8 + 0x472fc + uVar10 * 4) = *(int *)(iVar8 + 0x472fc + uVar10 * 4) + piVar11[4]
        ;
        piVar13 = piVar11 + 0xa4;
        piVar11 = piVar11 + 5;
        local_438 = local_438 + -1;
        *(int *)(iVar8 + 0x4731c + uVar10 * 4) = *(int *)(iVar8 + 0x4731c + uVar10 * 4) + *piVar13;
        piVar13 = piVar14 + 10;
      } while (local_438 != 0);
      *(int *)(iVar8 + 0x4735c + uVar10 * 4) = piVar14[10];
      *(int *)(iVar8 + 0x4733c + uVar10 * 4) = piVar14[0xb];
      return;
    }
    if (uVar3 == 0x8102) {
      if (bVar1 < 8) {
        *(byte *)(bVar1 + 0x45914 + param_1) = *(byte *)puVar12;
        return;
      }
    }
    else if (uVar3 == 0x8103) {
      if (bVar1 < 8) {
        *(undefined1 *)(bVar1 + 0x45914 + param_1) = 1;
        return;
      }
    }
    else if (uVar3 == 0x82ff) {
      *(undefined1 *)(bVar1 + 0x449ba + param_1) = 1;
      return;
    }
  }
  else if (uVar3 != 0x8600) {
    if (uVar3 == 0xc302) {
      if ((bVar1 < 8) &&
         (iVar8 = *(int *)(param_2 + 0x22), iVar7 = PeekChecksumStateUnderLock(g_clientContext + 0xeba98),
         iVar8 == iVar7)) {
        (&DAT_006a7670)[param_1 + (uint)*(byte *)puVar12 * 8 + (uint)bVar1] = 1;
        if ((*(byte *)puVar12 == 0xe) &&
           ((uint)bVar1 == *(uint *)(g_gameStateVTableArray[0xb] + 0x10a0))) {
          *(undefined4 *)(&DAT_006aab04 + param_1) = *(undefined4 *)(param_2 + 0x26);
        }
        FUN_00423a20();
      }
    }
    else if (uVar3 == 0xf00e) {
      DAT_0079352a = 1;
      return;
    }
  }
  return;
}

