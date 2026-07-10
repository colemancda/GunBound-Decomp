/* FUN_004b97d0 - 0x004b97d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004b97d0(int *param_1,uint param_2,int param_3,uint param_4)

{
  short *psVar1;
  undefined2 *puVar2;
  undefined1 *puVar3;
  char cVar4;
  undefined1 uVar5;
  short sVar6;
  undefined2 uVar7;
  undefined2 uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  undefined *puVar16;
  undefined4 extraout_EDX;
  uint uVar17;
  uint uVar18;
  bool bVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  char *pcVar22;
  undefined4 uVar23;
  char acStack_80 [128];
  
  iVar13 = g_clientContext;
  if (0x202 < param_2) {
    if (param_2 == 0x204) {
      *(undefined1 *)((int)param_1 + 0x91) = 1;
      if (DAT_00e53c3c != '\0') {
        DAT_00e53c3c = '\0';
      }
      (&DAT_006a7758)[g_clientContext] = 0;
      FUN_00461c60(&DAT_00553f90);
      return;
    }
    if (param_2 != 0x205) {
      if (param_2 != 0x206) {
        return;
      }
      iVar10 = FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xb30);
      iVar11 = FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x90c);
      iVar13 = g_clientContext;
      cVar4 = FUN_004065a0();
      if ((cVar4 == '\0') && ((&DAT_006a7758)[iVar13] != '\0')) {
        iVar15 = 400;
        if (399 < iVar11) {
          iVar15 = iVar11;
        }
        iVar12 = *(int *)(&DAT_006a7720 + iVar13) + -400;
        if ((iVar15 <= iVar12) && (iVar12 = iVar11, iVar11 < 400)) {
          iVar12 = 400;
        }
        iVar11 = -0x14;
        if (-0x15 < iVar10) {
          iVar11 = iVar10;
        }
        iVar15 = *(int *)(&DAT_006a7724 + iVar13) + -0x104;
        if ((iVar11 <= *(int *)(&DAT_006a7724 + iVar13) + -0x104) &&
           (iVar15 = -0x14, -0x15 < iVar10)) {
          iVar15 = iVar10;
        }
        *(int *)(&DAT_006a7718 + iVar13) = iVar12;
        *(int *)(&DAT_006a771c + iVar13) = iVar15;
      }
      *(undefined1 *)((int)param_1 + 0x91) = 1;
      if (DAT_00e53c3c != '\0') {
        DAT_00e53c3c = '\0';
      }
      (&DAT_006a7758)[g_clientContext] = 0;
      return;
    }
    uVar5 = 0;
    *(undefined1 *)((int)param_1 + 0x91) = 0;
    if (DAT_00e53c3c != '\x01') {
      DAT_00e53c3c = '\x01';
    }
    if ((*(char *)((int)param_1 + 0x92) == '\0') && (*(char *)((int)param_1 + 0x93) == '\0')) {
      uVar5 = 1;
    }
    (&DAT_006a7758)[g_clientContext] = uVar5;
    FUN_00461c60(s_normal_00552230);
    return;
  }
  if (param_2 != 0x202) {
    if (0x112 < param_2) {
      if (param_2 != 0x201) {
        return;
      }
      uVar17 = param_4 & 0xffff;
      uVar9 = param_4 >> 0x10;
      if ((char)param_1[0x46b] != '\0') {
        if ((0x72 < uVar9) && (uVar9 < 0x7f)) {
          if ((0x1d < uVar17) && (uVar17 < 0x5e)) {
            (&DAT_005f2f40)[g_clientContext] = 2;
          }
          if ((0x71 < uVar17) && (uVar17 < 0xb2)) {
            (&DAT_005f2f40)[iVar13] = 0;
          }
          if ((0xc6 < uVar17) && (uVar17 < 0x106)) {
            (&DAT_005f2f40)[iVar13] = 1;
          }
          QueueOutgoingPacketField(0xffffffff);
          QueueOutgoingPacketField(0xffffffff);
        }
        iVar13 = g_clientContext;
        if ((0xa8 < uVar9) && (uVar9 < 0xb4)) {
          if ((0x27 < uVar17) && (uVar17 < 0x41)) {
            *(undefined4 *)(&DAT_005f2f44 + g_clientContext) = 0x14;
          }
          if ((0x41 < uVar17) && (uVar17 < 0x69)) {
            *(undefined4 *)(&DAT_005f2f44 + iVar13) = 0x1e;
          }
          if ((0x69 < uVar17) && (uVar17 < 0x91)) {
            *(undefined4 *)(&DAT_005f2f44 + iVar13) = 0x28;
          }
          if ((0x91 < uVar17) && (uVar17 < 0xb9)) {
            *(undefined4 *)(&DAT_005f2f44 + iVar13) = 0x32;
          }
          if ((0xb9 < uVar17) && (uVar17 < 0xe1)) {
            *(undefined4 *)(&DAT_005f2f44 + iVar13) = 0x3c;
          }
          if ((0xe1 < uVar17) && (uVar17 < 0x109)) {
            *(undefined4 *)(&DAT_005f2f44 + iVar13) = 0x46;
          }
        }
        if ((0xda < uVar9) && (uVar9 < 0xe6)) {
          if ((0x23 < uVar17) && (uVar17 < 0x50)) {
            (&DAT_005f2f48)[iVar13] = 0;
          }
          if ((0xd6 < uVar17) && (uVar17 < 0x101)) {
            (&DAT_005f2f48)[iVar13] = 1;
          }
        }
        if ((0xf8 < uVar9) && (uVar9 < 0x104)) {
          if ((0x59 < uVar17) && (uVar17 < 0x6e)) {
            bVar19 = DAT_00793549 != '\0';
            *(undefined4 *)(&DAT_005f2f4c + iVar13) = 0;
            DAT_0079354a = '\0';
            if (bVar19) {
              (**(code **)(*(int *)*DAT_00793554 + 0xc))();
              DAT_00793568 = 0;
              iVar13 = g_clientContext;
            }
          }
          if ((0x6e < uVar17) && (uVar17 < 0x8c)) {
            if (DAT_0079354a == '\0') {
              DAT_0079354a = DAT_00793549 != '\0';
              _sprintf(acStack_80,s_stage_d_mp3_005569c0,(uint)*(byte *)(iVar13 + 0x475c4));
              cVar4 = PlayMusicTrack(1);
              iVar13 = g_clientContext;
              if (cVar4 == '\0') {
                iVar13 = _rand();
                _sprintf(acStack_80,s_stage_d_mp3_005569c0,iVar13 % 6 + 1);
                PlayMusicTrack(1);
                iVar13 = g_clientContext;
              }
            }
            *(undefined4 *)(&DAT_005f2f4c + iVar13) = 0x50;
            FUN_004eeb10();
            iVar13 = g_clientContext;
          }
          if ((0x8c < uVar17) && (uVar17 < 0xaa)) {
            if (DAT_0079354a == '\0') {
              DAT_0079354a = DAT_00793549 != '\0';
              _sprintf(acStack_80,s_stage_d_mp3_005569c0,(uint)*(byte *)(iVar13 + 0x475c4));
              cVar4 = PlayMusicTrack(1);
              iVar13 = g_clientContext;
              if (cVar4 == '\0') {
                iVar13 = _rand();
                _sprintf(acStack_80,s_stage_d_mp3_005569c0,iVar13 % 6 + 1);
                PlayMusicTrack(1);
                iVar13 = g_clientContext;
              }
            }
            *(undefined4 *)(&DAT_005f2f4c + iVar13) = 0x5a;
            FUN_004eeb10();
            iVar13 = g_clientContext;
          }
          if ((0xaa < uVar17) && (uVar17 < 200)) {
            if (DAT_0079354a == '\0') {
              DAT_0079354a = DAT_00793549 != '\0';
              _sprintf(acStack_80,s_stage_d_mp3_005569c0,(uint)*(byte *)(iVar13 + 0x475c4));
              cVar4 = PlayMusicTrack(1);
              iVar13 = g_clientContext;
              if (cVar4 == '\0') {
                iVar13 = _rand();
                _sprintf(acStack_80,s_stage_d_mp3_005569c0,iVar13 % 6 + 1);
                PlayMusicTrack(1);
                iVar13 = g_clientContext;
              }
            }
            *(undefined4 *)(&DAT_005f2f4c + iVar13) = 0x5f;
            FUN_004eeb10();
            iVar13 = g_clientContext;
          }
          if ((200 < uVar17) && (uVar17 < 0xe6)) {
            if (DAT_0079354a == '\0') {
              DAT_0079354a = DAT_00793549 != '\0';
              _sprintf(acStack_80,s_stage_d_mp3_005569c0,(uint)*(byte *)(iVar13 + 0x475c4));
              cVar4 = PlayMusicTrack(1);
              iVar13 = g_clientContext;
              if (cVar4 == '\0') {
                iVar13 = _rand();
                _sprintf(acStack_80,s_stage_d_mp3_005569c0,iVar13 % 6 + 1);
                PlayMusicTrack(1);
                iVar13 = g_clientContext;
              }
            }
            *(undefined4 *)(&DAT_005f2f4c + iVar13) = 0x62;
            FUN_004eeb10();
            iVar13 = g_clientContext;
          }
          if ((0xe6 < uVar17) && (uVar17 < 0xfb)) {
            if (DAT_0079354a == '\0') {
              DAT_0079354a = DAT_00793549 != '\0';
              _sprintf(acStack_80,s_stage_d_mp3_005569c0,(uint)*(byte *)(iVar13 + 0x475c4));
              cVar4 = PlayMusicTrack(1);
              iVar13 = g_clientContext;
              if (cVar4 == '\0') {
                iVar13 = _rand();
                _sprintf(acStack_80,s_stage_d_mp3_005569c0,iVar13 % 6 + 1);
                PlayMusicTrack(1);
                iVar13 = g_clientContext;
              }
            }
            *(undefined4 *)(&DAT_005f2f4c + iVar13) = 100;
            FUN_004eeb10();
            iVar13 = g_clientContext;
          }
        }
        uVar14 = DAT_00793560;
        if ((0x112 < uVar9) && (uVar9 < 0x11e)) {
          if ((0x59 < uVar17) && (uVar17 < 0x6e)) {
            uVar18 = 1;
            *(undefined4 *)(&DAT_005f2f50 + iVar13) = 0;
            DAT_0079354b = 0;
            if (1 < uVar14) {
              do {
                if (DAT_00793549 != '\0') {
                  if (uVar18 != 0xffffffff) {
                    (**(code **)(*(int *)DAT_00793554[uVar18] + 0xc))();
                    iVar13 = g_clientContext;
                  }
                  if (uVar18 == 0) {
                    DAT_00793568 = 0;
                  }
                }
                uVar18 = uVar18 + 1;
              } while (uVar18 < DAT_00793560);
            }
          }
          if ((0x6e < uVar17) && (uVar17 < 0x8c)) {
            DAT_0079354b = DAT_00793549 != '\0';
            *(undefined4 *)(&DAT_005f2f50 + iVar13) = 0x50;
            FUN_004eeb30();
            iVar13 = g_clientContext;
          }
          if ((0x8c < uVar17) && (uVar17 < 0xaa)) {
            DAT_0079354b = DAT_00793549 != '\0';
            *(undefined4 *)(&DAT_005f2f50 + iVar13) = 0x5a;
            FUN_004eeb30();
            iVar13 = g_clientContext;
          }
          if ((0xaa < uVar17) && (uVar17 < 200)) {
            DAT_0079354b = DAT_00793549 != '\0';
            *(undefined4 *)(&DAT_005f2f50 + iVar13) = 0x5f;
            FUN_004eeb30();
            iVar13 = g_clientContext;
          }
          if ((200 < uVar17) && (uVar17 < 0xe6)) {
            DAT_0079354b = DAT_00793549 != '\0';
            *(undefined4 *)(&DAT_005f2f50 + iVar13) = 0x62;
            FUN_004eeb30();
            iVar13 = g_clientContext;
          }
          if ((0xe6 < uVar17) && (uVar17 < 0xfb)) {
            DAT_0079354b = DAT_00793549 != '\0';
            *(undefined4 *)(&DAT_005f2f50 + iVar13) = 100;
            FUN_004eeb30();
            iVar13 = g_clientContext;
          }
        }
        if ((0x143 < uVar9) && (uVar9 < 0x151)) {
          if ((0x1d < uVar17) && (uVar17 < 0x5d)) {
            (&DAT_005f2f54)[iVar13] = 3;
          }
          if ((0x71 < uVar17) && (uVar17 < 0xb2)) {
            (&DAT_005f2f54)[iVar13] = 2;
          }
          if ((0xc6 < uVar17) && (uVar17 < 0x107)) {
            (&DAT_005f2f54)[iVar13] = 1;
          }
        }
        if (uVar9 < 0x177) {
          return;
        }
        if (0x182 < uVar9) {
          return;
        }
        if ((0x23 < uVar17) && (uVar17 < 0x4a)) {
          (&DAT_005f2f55)[iVar13] = 1;
        }
        if (uVar17 < 0xdc) {
          return;
        }
        if (0x101 < uVar17) {
          return;
        }
        (&DAT_005f2f55)[iVar13] = 0;
        return;
      }
      if ((((0x226 < uVar9) && (uVar9 < 599)) && (0xf4 < uVar17)) && (uVar17 < 0x284)) {
        *(uint *)(g_clientContext + 0xebee8) = uVar17;
        *(undefined1 *)(param_1 + 4) = 1;
      }
      if ((((3 < uVar9) && (uVar9 < 0x22)) &&
          ((cVar4 = FUN_004065a0(), iVar13 = g_clientContext, cVar4 == '\0' &&
           ((cVar4 = FUN_004065a0(), iVar13 = g_clientContext, cVar4 == '\x01' &&
            ((char)param_1[0x42f] == '\x01')))))) &&
         (cVar4 = PacketChecksumNotEquals(g_clientContext + 0xebcbc,6), iVar13 = g_clientContext,
         cVar4 != '\0')) {
        iVar10 = 0;
        iVar11 = 0x218;
        do {
          cVar4 = PacketChecksumNotEquals(iVar10 + 0x39f30 + g_clientContext,0);
          if (((cVar4 != '\0') && (iVar11 + -0x23 < (int)uVar17)) && ((int)uVar17 < iVar11)) {
            cVar4 = FUN_004065a0();
            if (cVar4 == '\0') {
              iVar10 = FUN_00420600(g_clientContext);
              iVar13 = g_clientContext;
              if (*(int *)(g_clientContext + 0xf0374) == iVar10) {
                *(undefined4 *)(g_clientContext + 0xf0374) = 0xffffffff;
              }
              else {
                *(int *)(g_clientContext + 0xf0374) = iVar10;
              }
            }
            else {
              uVar20 = FUN_00420600(g_clientContext);
              FUN_004cbda0(param_1,uVar20);
              iVar13 = g_clientContext;
            }
            break;
          }
          iVar11 = iVar11 + 0x24;
          iVar10 = iVar10 + 0x224;
          iVar13 = g_clientContext;
        } while (iVar11 < 0x2f0);
      }
      if (uVar9 < 0x27) {
        return;
      }
      if (499 < uVar9) {
        return;
      }
      if (*(char *)((int)param_1 + 0x92) != '\0') {
        Replay_AppendEvent(0x8404);
        sVar6 = FUN_0040a4d0(g_clientContext + 0xeba98);
        *(short *)(&g_replayEventBuffer + g_replayEventCursor) = sVar6 + 4;
        puVar16 = &DAT_006a64c4 + g_clientContext;
        psVar1 = (short *)(&DAT_00e9aace + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 2;
        *psVar1 = *(short *)(&DAT_006a7710 + g_clientContext) + (short)param_4 + -400;
        g_replayEventCursor = g_replayEventCursor + 2;
        iVar13 = FUN_0040a4d0(puVar16);
        if (iVar13 == 1) {
          iVar13 = _rand();
          (&g_replayEventBuffer)[g_replayEventCursor] = (char)(iVar13 % 6) + '\x02';
        }
        else {
          uVar5 = FUN_0040a4d0(&DAT_006a64c4 + g_clientContext);
          (&g_replayEventBuffer)[g_replayEventCursor] = uVar5;
        }
        g_replayEventCursor = g_replayEventCursor + 1;
        uVar5 = FUN_0040a4d0(g_clientContext + 0x3b49c);
        (&g_replayEventBuffer)[g_replayEventCursor] = uVar5;
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
        *(undefined1 *)((int)param_1 + 0x92) = 0;
        FUN_004e1f70();
        FUN_00405fb0();
        iVar13 = g_clientContext;
        (&DAT_006a7758)[g_clientContext] = 1;
        *(undefined4 *)(&DAT_006a73c8 + iVar13) = 1;
      }
      if (*(char *)((int)param_1 + 0x93) != '\0') {
        Replay_AppendEvent(0x8408);
        cVar4 = PacketChecksumEquals(g_clientContext + 0x45354,3);
        if (cVar4 == '\0') {
          sVar6 = FUN_0040a4d0(g_clientContext + 0xeba98);
          *(short *)(&g_replayEventBuffer + g_replayEventCursor) = sVar6 + 4;
        }
        else {
          sVar6 = FUN_0040a4d0(g_clientContext + 0xeba98);
          *(short *)(&g_replayEventBuffer + g_replayEventCursor) = sVar6 + 2;
        }
        iVar13 = g_replayEventCursor;
        g_replayEventCursor = g_replayEventCursor + 2;
        iVar10 = g_clientContext + 0x3b49c;
        *(short *)(&DAT_00e9aace + iVar13) =
             *(short *)(&DAT_006a7710 + g_clientContext) + (short)param_4 + -400;
        g_replayEventCursor = g_replayEventCursor + 2;
        iVar13 = FUN_0040a4d0(iVar10);
        uVar14 = FUN_0040a4d0(iVar13 * 0x224 + 0xebef4 + g_clientContext);
        if (uVar14 < 10) {
          *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = 10;
        }
        else {
          iVar13 = FUN_0045d360(0);
          *(int *)(&g_replayEventBuffer + g_replayEventCursor) = iVar13 / 2;
        }
        g_replayEventCursor = g_replayEventCursor + 4;
        Replay_FlushEvent();
        iVar13 = g_clientContext;
        *(undefined1 *)((int)param_1 + 0x93) = 0;
        (&DAT_006a7758)[iVar13] = 1;
      }
      iVar10 = FUN_0043c550(*(int *)(&DAT_006a7710 + iVar13) + -400 + uVar17,
                            *(int *)(&DAT_006a7714 + iVar13) + -0x12a + uVar9);
      iVar13 = g_clientContext;
      if (iVar10 != -1) {
        _DAT_00e9b4e8 = *(undefined2 *)(g_clientContext + 0x4591c + iVar10 * 2);
        pcVar22 = (char *)(iVar10 * 0xd + 0x457f1 + g_clientContext);
        iVar11 = (int)&DAT_00e9b4fd - (int)pcVar22;
        do {
          cVar4 = *pcVar22;
          pcVar22[iVar11] = cVar4;
          pcVar22 = pcVar22 + 1;
        } while (cVar4 != '\0');
        pcVar22 = (char *)(iVar10 * 9 + 0x457a9 + iVar13);
        iVar11 = (int)&DAT_00e9b4ea - (int)pcVar22;
        do {
          cVar4 = *pcVar22;
          pcVar22[iVar11] = cVar4;
          pcVar22 = pcVar22 + 1;
        } while (cVar4 != '\0');
        uVar20 = *(undefined4 *)(iVar13 + 0x4593c + iVar10 * 4);
        pcVar22 = (char *)GetLocalizedString(&g_localizedStringTable,3000);
        _sprintf(&DAT_00e9b50a,pcVar22,uVar20);
        uVar9 = *(uint *)(g_clientContext + 0x4597c + iVar10 * 4);
        if (999 < uVar9) {
          uVar9 = 999;
        }
        uVar20 = *(undefined4 *)(g_clientContext + 0x4599c + iVar10 * 4);
        pcVar22 = (char *)GetLocalizedString(&g_localizedStringTable,0xbb9);
        _sprintf(&DAT_00e9b58a,pcVar22,uVar9,uVar20);
        iVar13 = *(int *)(g_clientContext + 0x472fc + iVar10 * 4);
        uVar9 = *(int *)(g_clientContext + 0x4731c + iVar10 * 4) + iVar13;
        if (uVar9 == 0) {
          uVar9 = 1;
        }
        uVar9 = (uint)(iVar13 * 100) / uVar9;
        pcVar22 = (char *)GetLocalizedString(&g_localizedStringTable,0xbba);
        _sprintf(&DAT_00e9b60a,pcVar22,uVar9);
        uVar9 = *(uint *)(g_clientContext + 0x4735c + iVar10 * 4);
        if (uVar9 == 0) {
          uVar9 = 1;
        }
        uVar9 = *(uint *)(g_clientContext + 0x4733c + iVar10 * 4) / uVar9;
        pcVar22 = (char *)GetLocalizedString(&g_localizedStringTable,0xbbb);
        _sprintf(&DAT_00e9b68a,pcVar22,uVar9);
        iVar15 = FUN_0040a4d0(iVar10 * 0x448 + 0x477ec + g_clientContext);
        iVar12 = FUN_00420650(g_clientContext,iVar10,iVar15);
        iVar13 = iVar10 * 0x14 + iVar15;
        iVar11 = *(int *)(g_clientContext + 0x459bc + iVar13 * 4);
        uVar9 = *(int *)(g_clientContext + 0x45c3c + iVar13 * 4) + iVar11;
        if (uVar9 == 0) {
          uVar9 = 1;
        }
        uVar9 = (uint)(iVar11 * 100) / uVar9;
        uVar20 = GetLocalizedString(&g_localizedStringTable,iVar15 + 1000);
        pcVar22 = (char *)GetLocalizedString(&g_localizedStringTable,0xbbc);
        _sprintf(&DAT_00e9b70a,pcVar22,uVar20,uVar9);
        iVar13 = iVar10 * 0x14 + iVar12;
        iVar10 = *(int *)(g_clientContext + 0x459bc + iVar13 * 4);
        uVar9 = *(int *)(g_clientContext + 0x45c3c + iVar13 * 4) + iVar10;
        if (uVar9 == 0) {
          uVar9 = 1;
        }
        uVar9 = (uint)(iVar10 * 100) / uVar9;
        uVar20 = GetLocalizedString(&g_localizedStringTable,iVar12 + 1000);
        pcVar22 = (char *)GetLocalizedString(&g_localizedStringTable,0xbbd);
        _sprintf(&DAT_00e9b78a,pcVar22,uVar20,uVar9);
        _DAT_00e9b810 = 800;
        _DAT_00e9b80c = 0xfffffff6;
        DAT_00e9b80a = 1;
        (&DAT_006a7758)[g_clientContext] = 0;
        return;
      }
      cVar4 = FUN_00406710();
      if (cVar4 == '\0') {
        return;
      }
      cVar4 = FUN_004065a0();
      if (cVar4 == '\0') {
        return;
      }
      cVar4 = FUN_004065a0();
      if (cVar4 == '\0') {
        return;
      }
      if (*(int *)(*(int *)(g_clientContext + 0x621e0) + 0x24) == 0xd) {
        return;
      }
      if ((char)param_1[0x468] != '\0') {
        return;
      }
      if ((&DAT_005f2f40)[g_clientContext] != '\x02') {
        return;
      }
      if (*(int *)(&DAT_005f3768 + g_clientContext) == 1) {
        return;
      }
      if (*(int *)(&DAT_005f3768 + g_clientContext) == 2) {
        return;
      }
      *(undefined1 *)(param_1 + 0x468) = 1;
      param_1[0x469] = 0;
      param_1[0x46a] = 0;
      if (DAT_00e53c3c != '\0') {
        DAT_00e53c3c = '\0';
      }
      FUN_00461c60(&DAT_00556980);
      FUN_00406300(0);
      Replay_AppendEvent(0x8006);
      uVar7 = FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x90c);
      iVar13 = g_clientContext;
      *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
      g_replayEventCursor = g_replayEventCursor + 2;
      uVar7 = FUN_0040a4d0(*(int *)(iVar13 + 0x621e0) + 0xb30);
      *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
      g_replayEventCursor = g_replayEventCursor + 2;
      cVar4 = FUN_004065a0();
      if (cVar4 == '\0') {
        cVar4 = FUN_004065a0();
        uVar5 = cVar4 != '\0';
      }
      else {
        uVar5 = 2;
      }
      iVar13 = g_clientContext;
      (&g_replayEventBuffer)[g_replayEventCursor] = uVar5;
      g_replayEventCursor = g_replayEventCursor + 1;
      uVar5 = PacketChecksumEquals(*(int *)(iVar13 + 0x621e0) + 0x1c54,1);
      (&g_replayEventBuffer)[g_replayEventCursor] = uVar5;
LAB_004b9bb0:
      g_replayEventCursor = g_replayEventCursor + 1;
      Replay_FlushEvent();
      return;
    }
    if (param_2 == 0x112) {
      if (param_3 != 0xf060) {
        return;
      }
      if ((param_1[1] < 0xe11) && (cVar4 = FUN_004065a0(), cVar4 != '\0')) {
        return;
      }
      g_pendingGameState = 0xf;
      g_stateChangeRequested = 1;
      ChangeGameState(0xf);
      return;
    }
    if (param_2 != 0x100) {
      if (param_2 != 0x101) {
        return;
      }
      if (param_3 != 9) {
        if (param_3 != 0x78) {
          return;
        }
        if (*(char *)(g_clientContext + 0xebee5) == '\x01') {
          FUN_00405fb0();
          CreateButtonWidget(&DAT_00e9be90,0,4,0x3ec,s_b_play_all_0055412c,0xa8,0x219,0x1d,0x10,1,0)
          ;
          *(undefined1 *)(g_clientContext + 0xebee5) = 0;
          return;
        }
        FUN_00405fb0();
        CreateButtonWidget(&DAT_00e9be90,0,5,0x3ed,s_b_play_team_00554114,0xa8,0x219,0x1d,0x10,1,0);
        *(undefined1 *)(g_clientContext + 0xebee5) = 1;
        return;
      }
      cVar4 = FUN_004065a0();
      if (cVar4 == '\0') {
        return;
      }
      cVar4 = FUN_004065a0();
      if (cVar4 == '\x01') {
        *(undefined4 *)(g_clientContext + 0xebef0) = 0xfffffffd;
        FUN_00406500(0);
        FUN_00406500(0);
        FUN_00405fb0();
        CreateButtonWidget(&DAT_00e9be90,0,2,0x3ea,s_b_play_weapon2_00554154,0x2f,0x232,0x23,0x22,1,
                           0);
        uVar9 = FUN_0040b2d0(*(int *)(g_clientContext + 0x621e0) + 0xc080,4);
        if (((char)uVar9 == '\0') ||
           (uVar9 = *(uint *)(g_clientContext + 0x621e0), *(short *)(uVar9 + 0xbfbc) != 0)) {
          uVar9 = uVar9 & 0xffffff00;
        }
        else {
          uVar9 = CONCAT31((int3)(uVar9 >> 8),1);
        }
        CreateButtonWidget(&DAT_00e9be90,0,0x12,0x3fa,s_b_play_weapon3_00554144,0x58,0x232,0x23,0x22
                           ,uVar9,0);
        return;
      }
      cVar4 = FUN_004065a0();
      if (cVar4 == '\0') {
        *(undefined4 *)(g_clientContext + 0xebef0) = 0xffffffe8;
        FUN_00406500(1);
        FUN_00405fb0();
        uVar23 = 6;
        pcVar22 = s_b_play_weapon1_00554164;
        uVar21 = 0x3e9;
        uVar20 = 1;
      }
      else {
        cVar4 = FUN_0040b2d0(*(int *)(g_clientContext + 0x621e0) + 0xc080,4);
        if (((cVar4 == '\0') &&
            ((cVar4 = FUN_004065a0(), cVar4 != '\x01' ||
             (*(char *)(g_clientContext + 0x45127) != '\x03')))) ||
           (*(short *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc) != 0)) {
          *(undefined4 *)(g_clientContext + 0xebef0) = 0xfffffffd;
          FUN_00406500(0);
          FUN_00405fb0();
        }
        else {
          FUN_00406500(1);
          FUN_00405fb0();
          CreateButtonWidget(&DAT_00e9be90,0,1,0x3e9,s_b_play_weapon1_00554164,6,0x232,0x23,0x22,1,0
                            );
        }
        uVar23 = 0x2f;
        pcVar22 = s_b_play_weapon2_00554154;
        uVar21 = 0x3ea;
        uVar20 = 2;
      }
      CreateButtonWidget(&DAT_00e9be90,0,uVar20,uVar21,pcVar22,uVar23,0x232,0x23,0x22,1,0);
      Replay_AppendEvent(0x4005);
      cVar4 = FUN_004065a0();
      (&g_replayEventBuffer)[g_replayEventCursor] = cVar4 != '\0';
      g_replayEventCursor = g_replayEventCursor + 1;
      uVar5 = PacketChecksumEquals(*(int *)(g_clientContext + 0x621e0) + 0x1c54,1);
      (&g_replayEventBuffer)[g_replayEventCursor] = uVar5;
      goto LAB_004b9bb0;
    }
    if (param_3 != 0xd) {
      if (param_3 == 0x1b) {
        if ((char)param_1[0x474] != '\0') {
          return;
        }
        if ((&DAT_006a6481)[g_clientContext] != '\0') {
          FUN_00409990(&DAT_006a647c + g_clientContext,0);
          return;
        }
        FUN_004f2da0(0,0,0);
        return;
      }
      if (param_3 != 0x24) {
        return;
      }
      iVar10 = FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xb30);
      iVar11 = FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x90c);
      iVar13 = g_clientContext;
      cVar4 = FUN_004065a0();
      if (cVar4 != '\0') {
        return;
      }
      if ((&DAT_006a7758)[iVar13] == '\0') {
        return;
      }
      iVar15 = 400;
      if (399 < iVar11) {
        iVar15 = iVar11;
      }
      iVar12 = *(int *)(&DAT_006a7720 + iVar13) + -400;
      if ((iVar15 <= iVar12) && (iVar12 = iVar11, iVar11 < 400)) {
        iVar12 = 400;
      }
      iVar11 = -0x14;
      if (-0x15 < iVar10) {
        iVar11 = iVar10;
      }
      iVar15 = *(int *)(&DAT_006a7724 + iVar13) + -0x104;
      if ((iVar11 <= *(int *)(&DAT_006a7724 + iVar13) + -0x104) && (iVar15 = -0x14, -0x15 < iVar10))
      {
        iVar15 = iVar10;
      }
      *(int *)(&DAT_006a7718 + iVar13) = iVar12;
      *(int *)(&DAT_006a771c + iVar13) = iVar15;
      return;
    }
    if (((char)param_1[0x474] != '\0') && (cVar4 = FUN_00406400(), cVar4 == '\x01')) {
      FUN_00406300(extraout_EDX);
      iVar13 = DAT_007934e8;
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3232;
      *(undefined4 *)(iVar13 + 0x44d0) = 6;
      FUN_004d2680();
      return;
    }
    if (DAT_007933b8 != '\x01') goto LAB_004b9e53;
    cVar4 = FUN_004065a0();
    if (cVar4 == '\0') {
      FUN_0040c880();
      if ((acStack_80[0] != '\0') && (cVar4 = FUN_004218c0(g_clientContext,acStack_80), cVar4 == '\0'))
      {
        cVar4 = FUN_00415b00(acStack_80);
        if (cVar4 == '\x01') {
          uVar20 = 0x202;
        }
        else {
          cVar4 = FUN_00415230();
          if (cVar4 == '\0') {
            Replay_AppendEvent((*(char *)(g_clientContext + 0xebee5) != '\0') + 0x4002);
            pcVar22 = acStack_80;
            do {
              cVar4 = *pcVar22;
              pcVar22 = pcVar22 + 1;
            } while (cVar4 != '\0');
            Replay_AppendString(acStack_80);
            Replay_FlushEvent();
            goto LAB_004b9e3e;
          }
          uVar20 = 0x205;
        }
        uVar23 = 6;
        uVar21 = 2;
        iVar13 = *param_1;
        uVar20 = GetLocalizedString(&g_localizedStringTable,uVar20);
        (**(code **)(iVar13 + 0x28))(uVar20,uVar21,uVar23);
      }
    }
    else {
      FUN_00426230();
    }
LAB_004b9e3e:
    SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
LAB_004b9e53:
    FUN_00409990(&DAT_006a647c + g_clientContext,1);
    return;
  }
  uVar9 = param_4 & 0xffff;
  if ((char)param_1[4] != '\0') {
    if ((((0x233 < param_4 >> 0x10) && (param_4 >> 0x10 < 0x247)) && (0xf5 < uVar9)) &&
       (uVar9 < 0x285)) {
      *(uint *)(g_clientContext + 0xebee8) = uVar9;
    }
    *(undefined1 *)(param_1 + 4) = 0;
  }
  if ((((char)param_1[0x468] != '\x01') ||
      (cVar4 = FUN_004065a0(), iVar13 = g_clientContext, cVar4 == '\0')) ||
     ((cVar4 = FUN_004065a0(), iVar13 = g_clientContext, cVar4 == '\0' ||
      ((&DAT_005f2f40)[g_clientContext] != '\x02')))) goto LAB_004bb56e;
  *(undefined1 *)(param_1 + 0x468) = 0;
  iVar13 = FUN_0040a4d0(*(int *)(iVar13 + 0x621e0) + 0x7640);
  iVar10 = FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x7864);
  if (iVar10 < iVar13 * 10) {
    iVar13 = FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x7864);
  }
  else {
    iVar13 = FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x7640);
    iVar13 = iVar13 * 10;
  }
  QueueOutgoingPacketField(iVar13);
  FUN_0043c860(&DAT_006a7f70 + g_clientContext,*(undefined4 *)(g_clientContext + 0x621e0));
  cVar4 = FUN_004065a0();
  if (cVar4 == '\x01') {
    cVar4 = FUN_004065a0();
    if (cVar4 == '\0') {
      uVar20 = 0xc409;
    }
    else {
LAB_004bafd2:
      uVar20 = 0xc400;
    }
  }
  else {
    cVar4 = FUN_0041eaa0(g_clientContext,*(undefined2 *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc));
    if (cVar4 == '\0') goto LAB_004bafd2;
    uVar20 = 0x8403;
  }
  Replay_AppendEvent(uVar20);
  uVar7 = FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x90c);
  iVar13 = g_clientContext;
  *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  g_replayEventCursor = g_replayEventCursor + 2;
  uVar7 = FUN_0040a4d0(*(int *)(iVar13 + 0x621e0) + 0xb30);
  iVar13 = g_clientContext;
  *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  g_replayEventCursor = g_replayEventCursor + 2;
  uVar5 = PacketChecksumEquals(*(int *)(iVar13 + 0x621e0) + 0x1c54,1);
  (&g_replayEventBuffer)[g_replayEventCursor] = uVar5;
  g_replayEventCursor = g_replayEventCursor + 1;
  uVar5 = FUN_004065a0();
  iVar13 = g_clientContext;
  (&g_replayEventBuffer)[g_replayEventCursor] = uVar5;
  g_replayEventCursor = g_replayEventCursor + 1;
  uVar7 = FUN_0040a4d0(*(int *)(iVar13 + 0x621e0) + 0x4d90);
  iVar13 = g_clientContext;
  *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  g_replayEventCursor = g_replayEventCursor + 2;
  uVar7 = FUN_0040a4d0(*(int *)(iVar13 + 0x621e0) + 0x7864);
  *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  g_replayEventCursor = g_replayEventCursor + 2;
  cVar4 = FUN_0045ec30();
  iVar13 = g_clientContext;
  (&g_replayEventBuffer)[g_replayEventCursor] = cVar4 != '\0';
  g_replayEventCursor = g_replayEventCursor + 1;
  cVar4 = PacketChecksumEquals(*(int *)(iVar13 + 0x621e0) + 0x1c54,0);
  if (cVar4 == '\0') {
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x9cf0);
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x51d8);
  }
  else {
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x51d8);
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x9cf0);
  }
  FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x9f14);
  FUN_004ead90();
  uVar7 = FUN_0053753c();
  FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x9f14);
  FUN_004ead70();
  uVar8 = FUN_0053753c();
  iVar13 = g_clientContext;
  *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  puVar2 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
  g_replayEventCursor = g_replayEventCursor + 2;
  *puVar2 = uVar8;
  g_replayEventCursor = g_replayEventCursor + 2;
  cVar4 = PacketChecksumEquals(*(int *)(iVar13 + 0x621e0) + 0x1c54,0);
  if (cVar4 == '\0') {
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xa138);
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x51d8);
  }
  else {
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x51d8);
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xa138);
  }
  FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xa35c);
  FUN_004ead90();
  uVar7 = FUN_0053753c();
  FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xa35c);
  FUN_004ead70();
  uVar8 = FUN_0053753c();
  iVar13 = g_clientContext;
  *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  puVar2 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
  g_replayEventCursor = g_replayEventCursor + 2;
  *puVar2 = uVar8;
  g_replayEventCursor = g_replayEventCursor + 2;
  cVar4 = PacketChecksumEquals(*(int *)(iVar13 + 0x621e0) + 0x1c54,0);
  if (cVar4 == '\0') {
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xa9c8);
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x51d8);
  }
  else {
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x51d8);
    FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xa9c8);
  }
  FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xabec);
  FUN_004ead90();
  uVar7 = FUN_0053753c();
  FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0xabec);
  FUN_004ead70();
  uVar8 = FUN_0053753c();
  iVar13 = g_clientContext;
  *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  puVar2 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
  g_replayEventCursor = g_replayEventCursor + 2;
  *puVar2 = uVar8;
  g_replayEventCursor = g_replayEventCursor + 2;
  uVar7 = FUN_0040a4d0(iVar13 + 0x5af88);
  iVar13 = g_clientContext;
  *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  g_replayEventCursor = g_replayEventCursor + 2;
  uVar7 = FUN_0040a4d0(iVar13 + 0x5b1ac);
  *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar7;
  puVar3 = &DAT_00e9aace + g_replayEventCursor;
  g_replayEventCursor = g_replayEventCursor + 2;
  *puVar3 = 0;
  g_replayEventCursor = g_replayEventCursor + 1;
  FUN_0043d6d0();
  Replay_FlushEvent();
  FUN_0040a4d0(*(int *)(g_clientContext + 0x621e0) + 0x7864);
  ClampCursorToRect();
  FUN_00406500(0);
  FUN_00406500(0);
  QueueOutgoingPacketField(0xffffffff);
  QueueOutgoingPacketField(0xffffffff);
  *(undefined1 *)(*(int *)(g_clientContext + 0x621e0) + 0xbfe8) = 0;
  FUN_00461c60(s_normal_00552230);
  iVar13 = g_clientContext;
LAB_004bb56e:
  _DAT_00e9b80c = 10;
  (&DAT_006a7758)[iVar13] = 1;
  if (DAT_00e53c3c == '\x01') {
    return;
  }
  DAT_00e53c3c = 1;
  return;
}

