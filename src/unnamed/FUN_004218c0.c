/* FUN_004218c0 - 0x004218c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004218c0(int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  undefined4 *puVar7;
  DWORD DVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  char *pcVar13;
  bool bVar14;
  undefined4 uVar15;
  char local_220 [115];
  char acStack_1ad [13];
  char local_1a0 [116];
  char acStack_12c [12];
  char local_120 [32];
  char local_100;
  undefined4 local_ff [31];
  undefined1 local_80 [128];
  
  FUN_00423050(param_1,param_2);
  if (*param_2 != '/') {
    return 0;
  }
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2[(int)local_ff + (-1 - (int)param_2)] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = FUN_00525ea0(&local_100,&DAT_005535f4);
  while (iVar3 != 0) {
    pcVar2 = (char *)(iVar3 + 1);
    iVar3 = iVar3 - (int)pcVar2;
    do {
      cVar1 = *pcVar2;
      pcVar2[iVar3] = cVar1;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    iVar3 = FUN_00525ea0(&local_100,&DAT_005535f4);
  }
  iVar3 = FUN_00421820(&local_100);
  if (local_100 < '\0') {
    uVar10 = 0;
  }
  else {
    uVar10 = (uint)local_100;
  }
  pcVar2 = (char *)local_ff;
  pcVar13 = local_220;
  for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar13 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar13 = pcVar13 + 1;
  }
  local_220[local_100] = '\0';
  iVar4 = __stricmp(local_220,(char *)&DAT_005535f0);
  if (((iVar4 == 0) || (iVar4 = __stricmp(local_220,&DAT_005535e8), iVar4 == 0)) ||
     (iVar4 = __stricmp(local_220,s_guide_005535e0), iVar4 == 0)) {
    if (iVar3 != 1) {
      return 1;
    }
    uVar15 = 500;
    goto LAB_00422eef;
  }
  iVar4 = __stricmp(local_220,&DAT_005535dc);
  if (((iVar4 == 0) || (iVar4 = __stricmp(local_220,&DAT_005535d8), iVar4 == 0)) ||
     ((iVar4 = __stricmp(local_220,s_message_005535d0), iVar4 == 0 ||
      (iVar4 = __stricmp(local_220,&DAT_005535cc), iVar4 == 0)))) {
    FUN_0040d260(local_1a0);
    iVar4 = FUN_00525ea0(&local_100,local_80);
    if (iVar4 == 0) {
      if (2 < iVar3) {
        iVar3 = 0;
        iVar4 = 2;
        do {
          iVar4 = iVar4 + -1;
          iVar3 = iVar3 + 1 + (int)*(char *)((int)local_ff + iVar3 + -1);
        } while (iVar4 != 0);
        FUN_00421870();
        iVar4 = __stricmp(local_1a0,(char *)(DAT_005b3484 + 0x23330));
        if (iVar4 == 0) {
          return 1;
        }
        SetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&DAT_00551cb1);
        FUN_00402720(&DAT_00e53e88,local_1a0,param_2 + iVar3 + 1);
        return 1;
      }
      uVar15 = 0x1f5;
    }
    else {
      uVar15 = 0x205;
    }
    goto LAB_00422eef;
  }
  iVar4 = __stricmp(local_220,&DAT_005535c4);
  if (iVar4 != 0) {
    iVar4 = __stricmp(local_220,(char *)&PTR_DAT_005535c0);
    if (iVar4 == 0) {
      uVar15 = 0x1f8;
    }
    else {
      iVar4 = __stricmp(local_220,&DAT_005535b8);
      if ((iVar4 == 0) || (iVar4 = __stricmp(local_220,&DAT_005535b0), iVar4 == 0)) {
        if (iVar3 != 1) {
          return 1;
        }
        g_pendingGameState = 0xf;
        g_stateChangeRequested = 0;
        DAT_0056d108 = 0;
        _DAT_007934d8 = 1;
        return 1;
      }
      iVar4 = __stricmp(local_220,&DAT_005535ac);
      if (iVar4 == 0) {
        if (iVar3 == 2) {
          if (g_currentGameState == 3) {
            FUN_00421870();
            lVar6 = _atol(local_1a0);
            if ((lVar6 + -1 < 999) && (lVar6 = _atol(local_1a0), lVar6 + -1 < 0)) {
              iVar3 = 0;
            }
            else {
              lVar6 = _atol(local_1a0);
              if (lVar6 + -1 < 999) {
                lVar6 = _atol(local_1a0);
                iVar3 = lVar6 + -1;
              }
              else {
                iVar3 = 999;
              }
            }
            iVar5 = DAT_007934e8;
            *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
            *(undefined2 *)(iVar5 + 0x4d4) = 0x2100;
            *(undefined1 *)(iVar5 + 0x4d6) = 1;
            iVar4 = *(int *)(iVar5 + 0x44d0);
            *(int *)(iVar5 + 0x44d0) = iVar4 + 1;
            *(undefined1 *)(iVar4 + 0x4d1 + iVar5) = 0;
            iVar4 = *(int *)(iVar5 + 0x44d0);
            *(int *)(iVar5 + 0x44d0) = iVar4 + 1;
            *(short *)(iVar4 + 0x4d1 + iVar5) = (short)(iVar3 / 6);
            *(int *)(iVar5 + 0x44d0) = *(int *)(iVar5 + 0x44d0) + 2;
            g_gameStateVTableArray[3][0x115] = 1;
            g_gameStateVTableArray[3][0x116] = 0;
            *(int *)(g_gameStateVTableArray[3] + 0x11c) = iVar3 / 6;
            FUN_004d2680();
            iVar3 = iVar3 + 1;
            pcVar2 = (char *)FUN_0043dc70(&DAT_00796eec,0x27a);
            _sprintf(local_1a0,pcVar2,iVar3);
            (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_1a0,2,6);
            return 1;
          }
        }
        else if (g_currentGameState == 3) {
          uVar15 = 0x1fa;
          goto LAB_00422eef;
        }
        uVar15 = 0x1f9;
      }
      else {
        iVar4 = __stricmp(local_220,&DAT_005535a4);
        if (iVar4 == 0) {
          if (1 < iVar3) {
            iVar4 = 1;
            do {
              pcVar2 = local_1a0;
              FUN_00421870();
              do {
                cVar1 = *pcVar2;
                pcVar2 = pcVar2 + 1;
              } while (cVar1 != '\0');
              if ((uint)((int)pcVar2 - (int)(local_1a0 + 1)) < 0xd) {
                FUN_00425840();
              }
              iVar4 = iVar4 + 1;
            } while (iVar4 < iVar3);
            return 1;
          }
          uVar15 = 0x1fb;
        }
        else {
          iVar4 = __stricmp(local_220,s_mutelist_00553598);
          if (iVar4 == 0) {
            iVar3 = *(int *)(&DAT_0067ec64 + param_1);
            iVar4 = iVar3;
            pcVar2 = (char *)FUN_0043dc70(&DAT_00796eec,0x1fc);
            _sprintf(local_1a0,pcVar2,iVar4);
            (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_1a0,2,6);
            uVar10 = 0;
            acStack_1ad[1] = 0;
            if (0 < iVar3) {
              do {
                uVar11 = uVar10 & 0x80000003;
                bVar14 = uVar11 == 0;
                if ((int)uVar11 < 0) {
                  bVar14 = (uVar11 - 1 | 0xfffffffc) == 0xffffffff;
                }
                if (bVar14) {
                  (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                            (acStack_1ad + 1,2,0);
                  acStack_1ad[1] = 0;
                }
                puVar7 = (undefined4 *)FUN_00415450();
                _sprintf(acStack_12c,s___15s_00553590,*puVar7);
                pcVar2 = acStack_12c;
                do {
                  cVar1 = *pcVar2;
                  pcVar2 = pcVar2 + 1;
                } while (cVar1 != '\0');
                uVar11 = (int)pcVar2 - (int)acStack_12c;
                pcVar2 = acStack_1ad;
                do {
                  pcVar13 = pcVar2 + 1;
                  pcVar2 = pcVar2 + 1;
                } while (*pcVar13 != '\0');
                pcVar13 = acStack_12c;
                for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *(undefined4 *)pcVar2 = *(undefined4 *)pcVar13;
                  pcVar13 = pcVar13 + 4;
                  pcVar2 = pcVar2 + 4;
                }
                uVar10 = uVar10 + 1;
                for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
                  *pcVar2 = *pcVar13;
                  pcVar13 = pcVar13 + 1;
                  pcVar2 = pcVar2 + 1;
                }
              } while ((int)uVar10 < iVar3);
            }
            (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                      (acStack_1ad + 1,2,0);
            return 1;
          }
          iVar4 = __stricmp(local_220,&DAT_00553588);
          if (iVar4 != 0) {
            iVar4 = __stricmp(local_220,s_loudall_00553580);
            if (iVar4 == 0) {
              FUN_00425960();
              return 1;
            }
            iVar4 = __stricmp(local_220,s_comsik_00553578);
            if (((iVar4 == 0) || (iVar4 = __stricmp(local_220,&DAT_00553570), iVar4 == 0)) &&
               (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553554,9,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (s_Game_Programmer___comsik_00553538,9,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553508,9,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005534d4,9,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,&DAT_005534cc);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005534b4,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (s_Oh___It_s_CozY_here______00553498,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_enddream_0055348c);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553478,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553440,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553404,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005533d0,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_yesoori_005533c8);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005533b0,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553390,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_oorusa_00553388);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553370,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553354,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_jaeyong_0055334c);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553330,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553320,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_yaong2_00553318);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005532fc,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005532e4,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_jchlee75_005532d8);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005532bc,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_0055328c,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_reddragon_00553280);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553258,8,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (s_Server___Game_buddy_Programmer___0055322c,8,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_designer_00553220);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553200,2,5);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_johnny5_005531f8);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005531e0,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005531b4,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553188,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553148,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_0055310c,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_loserii_00553104);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005530ec,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005530cc,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_scjang_005530c4);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_005530ac,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553074,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_0055303c,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00553018,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_chuko_00553010);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552ffc,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552fe4,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552fc8,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552fac,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_pirania_00552fa4);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552f90,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552f64,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552f4c,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552f34,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_blash45_00552f2c);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552f1c,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552ef0,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552ed4,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_knights_00552ecc);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552ebc,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552ea4,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552e90,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552e68,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552e30,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,&DAT_00552e24);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552e14,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552de4,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552db4,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552d94,2,0);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552d60,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_ethera_00552d58);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (&DAT_00552d38,2,5);
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (s_Feel_ethereal_____00552d24,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_noack_00552d1c);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              DAT_00e9b1d8 = 1;
              (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                        (s_Acks_will_not_be_send_00552d04,2,0);
              return 1;
            }
            iVar4 = __stricmp(local_220,s_clear_00552cfc);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              Replay_AppendEvent(0x9000);
              Replay_FlushEvent();
              return 1;
            }
            iVar4 = __stricmp(local_220,s_logging_00552cf4);
            if ((iVar4 == 0) && (iVar3 == 1)) {
              Replay_AppendEvent(0xf00e);
              Replay_FlushEvent();
              return 1;
            }
            iVar5 = __stricmp(local_220,s_shrduatlwkr_00552ce8);
            iVar4 = DAT_007934e8;
            if ((iVar5 == 0) && (iVar3 == 1)) {
              *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3430;
              *(undefined4 *)(iVar4 + 0x44d0) = 6;
              DVar8 = GetTickCount();
              iVar3 = DAT_007934e8;
              *(DWORD *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = DVar8;
              iVar4 = DAT_005b3484 + 0x45354;
              *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
              cVar1 = PacketChecksumEquals(iVar4,3);
              if (cVar1 != '\0') {
                iVar3 = 6;
                do {
                  iVar5 = _rand();
                  iVar4 = DAT_007934e8;
                  *(short *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = (short)iVar5;
                  *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 2;
                  iVar5 = FUN_0040a4d0(&DAT_00796aa0);
                  iVar9 = _rand();
                  iVar4 = DAT_007934e8;
                  *(char *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) =
                       (char)(iVar9 % iVar5);
                  iVar3 = iVar3 + -1;
                  *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 1;
                } while (iVar3 != 0);
                FUN_004d2680();
                return 1;
              }
              FUN_004d2680();
              return 1;
            }
            if (((g_currentGameState == 9) && (DAT_00793522 == '\0')) && (iVar3 == 1)) {
              cVar1 = FUN_0040b390(param_1 + 0x3b6c4,param_1 + 0x3b49c);
              if ((cVar1 != '\0') && (iVar4 = FUN_00409c70(&DAT_00e9bea8), iVar4 != -1)) {
                uVar10 = FUN_0040a4d0(g_gameStateVTableArray[9] + 0x26c);
                QueueOutgoingPacketField(uVar10 & 0xfffff | iVar4 << 0x18);
                iVar3 = DAT_007934e8;
                *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3101;
                *(undefined4 *)(iVar3 + 0x44d0) = 6;
                uVar15 = FUN_0040a4d0(g_gameStateVTableArray[9] + 0xc);
                iVar3 = DAT_007934e8;
                *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar15;
                *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
                FUN_004d2680();
                return 1;
              }
              if (((g_currentGameState == 9) && (DAT_00793522 == '\0')) &&
                 ((cVar1 = FUN_0040b390(param_1 + 0x3b6c4,param_1 + 0x3b49c), cVar1 != '\0' &&
                  (iVar5 = __stricmp(local_220,s_shrduarhkswjs_00552cd8), iVar4 = DAT_007934e8,
                  iVar5 == 0)))) {
                *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
                *(undefined2 *)(iVar4 + 0x4d4) = 0x3210;
                g_gameStateVTableArray[9][0x25b] = 0xff;
                *(undefined1 *)(*(int *)(iVar4 + 0x44d0) + 0x4d0 + iVar4) = 0xff;
                goto LAB_00422d6b;
              }
            }
            iVar5 = __stricmp(local_220,s_shrduaakstpakstpaksakstp_00552cbc);
            iVar4 = DAT_007934e8;
            if ((iVar5 != 0) || (iVar3 != 2)) {
              *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x5100;
              *(undefined4 *)(iVar4 + 0x44d0) = 6;
              pcVar2 = param_2;
              do {
                cVar1 = *pcVar2;
                pcVar2 = pcVar2 + 1;
              } while (cVar1 != '\0');
              FUN_004d2530(param_2);
              FUN_004d2680();
              return 1;
            }
            if (g_currentGameState != 9) {
              return 1;
            }
            FUN_00421870();
            FUN_004da460(g_gameStateVTableArray[9],0,0);
            iVar3 = DAT_007934e8;
            iVar4 = DAT_005b3484 + 0x45354;
            *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3200;
            *(undefined4 *)(iVar3 + 0x44d0) = 6;
            cVar1 = PacketChecksumNotEquals(iVar4,2);
            if (cVar1 != '\0') {
              *(undefined4 *)(g_gameStateVTableArray[9] + 0x268) = 0;
            }
            lVar6 = _atol(local_120);
            g_gameStateVTableArray[9][*(int *)(g_gameStateVTableArray[9] + 0x268) + 0x259] =
                 (char)lVar6;
            if (*(int *)(g_gameStateVTableArray[9] + 0x268) == 0) {
              g_gameStateVTableArray[9][0x25a] = 0xff;
            }
            *(int *)(g_gameStateVTableArray[9] + 0x268) =
                 *(int *)(g_gameStateVTableArray[9] + 0x268) + 1;
            iVar4 = DAT_007934e8;
            uVar10 = *(uint *)(g_gameStateVTableArray[9] + 0x268) & 0x80000001;
            if ((int)uVar10 < 0) {
              uVar10 = (uVar10 - 1 | 0xfffffffe) + 1;
            }
            *(uint *)(g_gameStateVTableArray[9] + 0x268) = uVar10;
            *(undefined *)(*(int *)(iVar4 + 0x44d0) + 0x4d0 + iVar4) =
                 g_gameStateVTableArray[9][0x259];
            iVar3 = *(int *)(iVar4 + 0x44d0);
            *(int *)(iVar4 + 0x44d0) = iVar3 + 1;
            *(undefined *)(iVar3 + 0x4d1 + iVar4) = g_gameStateVTableArray[9][0x25a];
            goto LAB_00422d6b;
          }
          if (1 < iVar3) {
            iVar4 = 1;
            do {
              pcVar2 = local_1a0;
              FUN_00421870();
              do {
                cVar1 = *pcVar2;
                pcVar2 = pcVar2 + 1;
              } while (cVar1 != '\0');
              if ((uint)((int)pcVar2 - (int)(local_1a0 + 1)) < 0xd) {
                FUN_004258e0(local_1a0);
              }
              iVar4 = iVar4 + 1;
            } while (iVar4 < iVar3);
            return 1;
          }
          uVar15 = 0x1fd;
        }
      }
    }
    goto LAB_00422eef;
  }
  if (iVar3 == 2) {
    if (g_currentGameState == 9) {
      cVar1 = FUN_0040b390(param_1 + 0x3b6c4,param_1 + 0x3b49c);
      if (cVar1 != '\0') {
        FUN_00421870();
        iVar3 = 0;
        pcVar2 = (char *)(param_1 + 0x457f1);
        while (iVar5 = __stricmp(pcVar2,local_1a0), iVar4 = DAT_007934e8, iVar5 != 0) {
          iVar3 = iVar3 + 1;
          pcVar2 = pcVar2 + 0xd;
          if (7 < iVar3) {
            return 1;
          }
        }
        *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3150;
        *(undefined4 *)(iVar4 + 0x44d0) = 6;
        *(char *)(iVar4 + 0x4d6) = (char)iVar3;
LAB_00422d6b:
        *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 1;
        FUN_004d2680();
        return 1;
      }
      goto LAB_00421b11;
    }
  }
  else {
LAB_00421b11:
    if (g_currentGameState == 9) {
      uVar15 = 0x1f7;
      goto LAB_00422eef;
    }
  }
  uVar15 = 0x1f6;
LAB_00422eef:
  FUN_0043dc70(&DAT_00796eec,uVar15);
  FUN_00413af0();
  return 1;
}

