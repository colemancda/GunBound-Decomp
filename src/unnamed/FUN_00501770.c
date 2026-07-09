/* FUN_00501770 - 0x00501770 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall FUN_00501770(int param_1,int param_2,int param_3)

{
  ushort *puVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  byte bVar5;
  ushort uVar6;
  SOCKET s;
  int iVar7;
  HWND hWnd;
  UINT_PTR UVar8;
  undefined4 uVar9;
  uint uVar10;
  __time32_t _Var11;
  char *pcVar12;
  byte *pbVar13;
  byte *pbVar14;
  undefined4 *puVar15;
  byte *pbVar16;
  undefined4 *unaff_FS_OFFSET;
  char *pcVar17;
  sockaddr *name;
  uint uVar18;
  uint *namelen;
  uint local_4984;
  char *local_4980;
  int local_497c;
  uint local_4978;
  int iStack_4974;
  undefined4 *local_4970;
  sockaddr local_496c;
  undefined1 local_495c;
  undefined1 local_4958 [4];
  undefined4 local_4954;
  undefined4 local_4950;
  undefined4 local_494c;
  undefined4 local_4944;
  undefined4 uStack_4940;
  undefined4 uStack_493c;
  undefined4 uStack_4938;
  undefined4 uStack_4934;
  undefined1 uStack_4930;
  undefined2 local_4928;
  undefined4 local_4924;
  undefined4 local_4920;
  undefined1 local_491c;
  undefined1 local_4917;
  char local_4914 [17];
  undefined1 local_4903;
  undefined1 local_4902;
  undefined1 local_48f0 [18];
  undefined1 local_48de;
  undefined1 local_48c9;
  undefined2 local_48be;
  char local_48ba [82];
  undefined4 auStack_4868 [64];
  byte abStack_4768 [256];
  undefined4 local_4668;
  undefined4 local_4664;
  undefined4 local_4660;
  undefined4 local_465c;
  undefined4 local_4658;
  undefined4 local_4654;
  uint local_4650;
  undefined4 local_464c [1493];
  ushort local_2ef8;
  undefined4 local_2ef6 [7];
  undefined1 local_2ed8 [5968];
  ushort local_1788;
  undefined4 local_1786 [1498];
  undefined4 uStack_1c;
  int iStack_18;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_00538f8c;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  uStack_1c = 0x501796;
  uVar6 = *(ushort *)(param_2 + 2);
  puVar1 = (ushort *)(param_2 + 4);
  param_3 = param_3 + -4;
  local_497c = param_1;
  iStack_18 = param_1;
  if (uVar6 < 0x2011) {
    if (uVar6 == 0x2010) {
      if ((0xf < param_3) &&
         (cVar4 = FUN_004f72b0(*(undefined4 *)(param_1 + 0x1784),puVar1,6000), cVar4 != '\0')) {
        local_4970 = local_2ef6;
        puVar15 = local_1786;
        local_2ef8 = local_1788;
        if (local_1788 != 0) {
          local_4980 = (char *)(param_1 + 0x17cc);
          local_4984 = (uint)local_1788;
          local_4978 = param_1 - 0x2f4;
          do {
            *local_4970 = *puVar15;
            local_4970 = local_4970 + 1;
            SUBFIELD(local_496c,0,undefined4) = puVar15[1];
            SUBFIELD(local_496c.sa_data,2,undefined4) = puVar15[2];
            SUBFIELD(local_496c.sa_data,6,undefined4) = puVar15[3];
            SUBFIELD(local_496c.sa_data,10,undefined4) = puVar15[4];
            local_495c = 0;
            uVar10 = 0;
            do {
              cVar4 = *(char *)((int)puVar15 + uVar10 + 0x14);
              uVar18 = uVar10;
              if (cVar4 == '\0') break;
              bVar5 = (char)uVar10 + 1;
              uVar18 = (uint)bVar5;
              *(char *)((int)&local_4924 + uVar10) = cVar4;
              uVar10 = uVar18;
            } while (bVar5 < 0xc);
            local_4917 = (char)uVar18;
            *(undefined1 *)((int)&local_4924 + uVar18) = 0;
            uVar10 = 0;
            do {
              bVar5 = (byte)uVar10;
              if (local_496c.sa_data[uVar10 - 2] == '\0') break;
              bVar5 = bVar5 + 1;
              local_48ba[uVar10] = local_496c.sa_data[uVar10 - 2];
              uVar10 = (uint)bVar5;
            } while (bVar5 < 0x10);
            local_48ba[0x11] = bVar5;
            local_48ba[bVar5] = '\0';
            FUN_00503e30(local_48ba);
            uVar6 = *(ushort *)((int)puVar15 + 0x26);
            FUN_00504970(local_4978,&local_496c,puVar15[8],*(undefined2 *)(puVar15 + 9));
            puVar15 = (undefined4 *)((int)puVar15 + uVar6 + 0x28);
            local_4984 = local_4984 - 1;
          } while (local_4984 != 0);
          local_4984 = 0;
        }
        FUN_00502500(0x2011);
      }
      goto LAB_00502483;
    }
    if (0x101f < uVar6) {
      if (uVar6 == 0x1ffe) {
        if (3 < param_3) {
          local_4954 = 0;
          local_4950 = 0;
          local_494c = 0;
          local_c = 1;
          iVar7 = (**(code **)(DAT_005b1444 + 0xc))();
          local_4978 = iVar7 + 0x10;
          iVar7 = (**(code **)(DAT_005b1444 + 0xc))();
          iVar7 = iVar7 + 0x10;
          local_c = 2;
          uVar6 = *puVar1;
          pbVar13 = (byte *)(param_2 + 6);
          iStack_4974 = iVar7;
          if (uVar6 < 0xb) {
            if (uVar6 != 0) {
              local_4984 = (uint)uVar6;
              do {
                uVar10 = (uint)*pbVar13;
                pbVar14 = pbVar13 + 1;
                uVar18 = (uint)(*pbVar13 >> 2);
                pbVar13 = pbVar14;
                pbVar16 = (byte *)auStack_4868;
                for (; uVar18 != 0; uVar18 = uVar18 - 1) {
                  *(undefined4 *)pbVar16 = *(undefined4 *)pbVar13;
                  pbVar13 = pbVar13 + 4;
                  pbVar16 = pbVar16 + 4;
                }
                for (uVar18 = uVar10 & 3; uVar18 != 0; uVar18 = uVar18 - 1) {
                  *pbVar16 = *pbVar13;
                  pbVar13 = pbVar13 + 1;
                  pbVar16 = pbVar16 + 1;
                }
                pbVar14 = pbVar14 + uVar10;
                *(undefined1 *)((int)auStack_4868 + uVar10) = 0;
                uVar10 = (uint)*pbVar14;
                pbVar13 = pbVar14 + 1;
                pbVar16 = abStack_4768;
                for (uVar18 = (uint)(*pbVar14 >> 2); uVar18 != 0; uVar18 = uVar18 - 1) {
                  *(undefined4 *)pbVar16 = *(undefined4 *)pbVar13;
                  pbVar13 = pbVar13 + 4;
                  pbVar16 = pbVar16 + 4;
                }
                for (uVar18 = uVar10 & 3; uVar18 != 0; uVar18 = uVar18 - 1) {
                  *pbVar16 = *pbVar13;
                  pbVar13 = pbVar13 + 1;
                  pbVar16 = pbVar16 + 1;
                }
                abStack_4768[uVar10] = 0;
                pbVar13 = pbVar14 + 1 + uVar10;
                FUN_004055b0();
                FUN_004055b0();
                FUN_00502890();
                local_4984 = local_4984 - 1;
              } while (local_4984 != 0);
              local_4984 = 0;
              param_1 = local_497c;
            }
            iVar7 = iStack_4974;
            (**(code **)(**(int **)(param_1 + 0x17bc) + 0x10))(local_4958);
          }
          local_c = 1;
          piVar2 = (int *)(iVar7 + -4);
          LOCK();
          iVar3 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar3 + -1 < 1) {
            (**(code **)(**(int **)(iVar7 + -0x10) + 4))((undefined4 *)(iVar7 + -0x10));
          }
          piVar2 = (int *)(local_4978 - 4);
          LOCK();
          iVar7 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar7 == 1 || iVar7 + -1 < 0) {
            (**(code **)(**(int **)(local_4978 - 0x10) + 4))((undefined4 *)(local_4978 - 0x10));
          }
          FUN_00502a90();
        }
      }
      else if ((uVar6 == 0x1fff) && (param_3 == 2)) {
        FUN_004fdda0(param_1 + -0x2f0);
        (**(code **)(**(int **)(param_1 + 0x17bc) + 8))(*puVar1);
      }
      goto LAB_00502483;
    }
    if (uVar6 == 0x101f) {
      if (param_3 == 6) {
        *(undefined1 *)(param_1 + 0x1788) = 1;
        *(undefined2 *)(param_1 + 0x178c) = 2;
        *(undefined4 *)(param_1 + 0x1790) = *(undefined4 *)puVar1;
        *(undefined2 *)(param_1 + 0x178e) = *(undefined2 *)(param_2 + 8);
        *(undefined4 *)(param_1 + 0x1794) = 0;
        *(undefined4 *)(param_1 + 0x1798) = 0;
      }
      goto LAB_00502483;
    }
    if (uVar6 == 0x1001) {
      if (param_3 == 4) {
        if (*(void **)(param_1 + 0x1784) != (void *)0x0) {
          _free(*(void **)(param_1 + 0x1784));
        }
        uVar9 = FUN_004f6f10();
        *(undefined4 *)(param_1 + 0x1784) = uVar9;
        cVar4 = FUN_004fcd80(local_4914,0x11);
        if (((cVar4 != '\0') && (cVar4 = FUN_004fcd80(&local_4944,0x15), cVar4 != '\0')) &&
           (cVar4 = FUN_004f6f40(*(undefined4 *)(param_1 + 0x1784),&DAT_00551b7c,
                                 *(undefined4 *)puVar1,&local_2ef8), cVar4 != '\0')) {
          local_4978 = 0x10;
          cVar4 = FUN_00503930(&local_4984,&local_497c);
          if ((cVar4 != '\0') &&
             (iVar7 = getsockname(*(SOCKET *)(param_1 + -0x40),&local_496c,(int *)&local_4978),
             iVar7 == 0)) {
            local_4660 = uStack_4940;
            local_465c = uStack_493c;
            local_4654 = uStack_4934;
            local_4664 = local_4944;
            local_4650 = local_4984;
            local_4658 = uStack_4938;
            local_4668 = 0x13;
            local_464c[0] = CONCAT22(SUBFIELD(local_464c[0],2,undefined2),SUBFIELD(local_496c.sa_data,0,undefined2));
            cVar4 = FUN_004f7210(*(undefined4 *)(param_1 + 0x1784),local_2ed8,0x1750);
            if (cVar4 != '\0') {
              FUN_00502500(0x1010);
            }
          }
        }
      }
      goto LAB_00502483;
    }
    if ((uVar6 != 0x1011) || (param_3 < 2)) goto LAB_00502483;
    local_4954 = 0;
    local_4950 = 0;
    local_494c = 0;
    local_c = 0;
    uStack_4940 = 0;
    uStack_493c = 0;
    uStack_4938 = 0;
    uStack_4934 = 0;
    uStack_4930 = 0;
    local_4978 = (uint)*puVar1;
    local_4980 = (char *)(param_2 + 6);
    local_4984 = 0x10;
    local_4944 = 0;
    if (*puVar1 == 0) {
      if (0x1d < param_3) {
        local_4970 = (undefined4 *)(param_1 + -0x2c8);
        FUN_00503bb0();
        FUN_004fefe0();
        namelen = &local_4984;
        name = &local_496c;
        s = FUN_00503910();
        iVar7 = getpeername(s,name,(int *)namelen);
        pcVar12 = local_4980;
        if (iVar7 == 0) {
          sendto(*(SOCKET *)(param_1 + -0x40),local_4980,4,0,&local_496c,local_4984);
        }
        local_4980 = (char *)(param_1 + 0x179c);
        FUN_00503e10();
        FUN_004fcd80(local_4914,0x11);
        FUN_004fdc50();
        FUN_00503e30(local_48ba + 0x40);
        FUN_005037f0();
        local_4978 = CONCAT22(SUBFIELD(local_4978,2,undefined2),*(undefined2 *)(pcVar12 + 0x18));
        uVar6 = *(ushort *)(pcVar12 + 0x1a);
        pcVar12 = pcVar12 + 0x1c;
        if (100 < uVar6) {
          uVar6 = 100;
        }
        if (uVar6 != 0) {
          local_4980 = (char *)(uint)uVar6;
          do {
            FUN_004fe5d0();
            FUN_00503e10();
            FUN_00503e30(local_48f0);
            if (pcVar12[0x1c] == '\0') {
              pcVar12 = pcVar12 + 0x1d;
            }
            else {
              local_4944 = *(undefined4 *)(pcVar12 + 0x1c);
              uStack_4940 = *(undefined4 *)(pcVar12 + 0x20);
              uStack_493c = *(undefined4 *)(pcVar12 + 0x24);
              uStack_4938 = *(undefined4 *)(pcVar12 + 0x28);
              uStack_4934 = *(undefined4 *)(pcVar12 + 0x2c);
              uStack_4930 = 0;
              pcVar12 = pcVar12 + 0x30;
            }
            FUN_005037d0();
            FUN_005037f0();
            local_48be = *(undefined2 *)(pcVar12 + 8);
            pcVar12 = pcVar12 + 10;
            FUN_00502800();
            FUN_00502750();
            FUN_00503a10();
            local_4980 = local_4980 + -1;
          } while (local_4980 != (char *)0x0);
        }
        param_1 = local_497c;
        if (*(int *)(local_497c + 0x17c0) == 0) {
          hWnd = CreateWindowExA(0,s_STATIC_00557b50,s_CBuddy2_Timer_Receiving_Window_00557b74,
                                 0x80000000,0,0,0,0,(HWND)0x0,(HMENU)0x0,(HINSTANCE)0x0,(LPVOID)0x0)
          ;
          *(HWND *)(param_1 + 0x17c0) = hWnd;
          if (hWnd != (HWND)0x0) {
            SetWindowLongA(hWnd,-0x15,param_1 + -0x2f4);
            SetWindowLongA(*(HWND *)(param_1 + 0x17c0),-4,0x4fdaa0);
          }
        }
        if ((*(HWND *)(param_1 + 0x17c0) != (HWND)0x0) && (*(int *)(param_1 + 0x17c4) == 0)) {
          UVar8 = SetTimer(*(HWND *)(param_1 + 0x17c0),0x14d,60000,(TIMERPROC)0x0);
          *(UINT_PTR *)(param_1 + 0x17c4) = UVar8;
        }
        *(undefined1 *)(param_1 + 0x177d) = 1;
        *(undefined1 *)(param_1 + 0x1788) = 0;
        FUN_00501600();
        pcVar12 = (char *)&local_4924;
        pcVar17 = local_4914;
        uVar10 = 0;
        uVar18 = local_4978;
        goto LAB_00501b17;
      }
    }
    else {
      FUN_00501600();
      FUN_00503810();
      uVar18 = 0;
      pcVar12 = local_48ba + 0x12;
      pcVar17 = &DAT_00551cb1;
      uVar10 = local_4978;
LAB_00501b17:
      (**(code **)(**(int **)(param_1 + 0x17bc) + 0xc))(uVar10,pcVar17,pcVar12,uVar18,local_4958);
    }
    FUN_005028f0();
    goto LAB_00502483;
  }
  if (uVar6 < 0x3004) {
    if (uVar6 == 0x3003) {
      if ((1 < param_3) && (*puVar1 == 0)) {
        SUBFIELD(local_496c.sa_data,2,undefined4) = *(undefined4 *)(param_2 + 10);
        SUBFIELD(local_496c,0,undefined4) = *(undefined4 *)(param_2 + 6);
        pcVar12 = *(char **)(param_1 + 0x17b0);
        SUBFIELD(local_496c.sa_data,6,undefined4) = *(undefined4 *)(param_2 + 0xe);
        SUBFIELD(local_496c.sa_data,10,undefined4) = *(undefined4 *)(param_2 + 0x12);
        local_495c = 0;
        if (pcVar12 != *(char **)(param_1 + 0x17b4)) {
          do {
            iVar7 = __strnicmp(pcVar12,(char *)&local_496c,0x10);
            if (iVar7 == 0) {
              FUN_005027d0(pcVar12);
              break;
            }
            pcVar12 = pcVar12 + 0x12;
          } while (pcVar12 != *(char **)(param_1 + 0x17b4));
        }
      }
    }
    else if (uVar6 == 0x2021) {
      if ((0x2f < param_3) &&
         (cVar4 = FUN_004f72b0(*(undefined4 *)(param_1 + 0x1784),puVar1,6000), cVar4 != '\0')) {
        FUN_004fe5d0();
        FUN_00503e10();
        iVar7 = local_497c;
        FUN_00503e30(local_4958);
        _Var11 = FID_conflict___time32((__time32_t *)0x0);
        FUN_00504970(iVar7 + -0x2f4,local_4958,_Var11,local_464c[0]);
      }
    }
    else if (((uVar6 == 0x3001) && (1 < param_3)) && (*puVar1 == 0)) {
      SUBFIELD(local_496c,0,undefined4) = *(undefined4 *)(param_2 + 6);
      SUBFIELD(local_496c.sa_data,2,undefined4) = *(undefined4 *)(param_2 + 10);
      SUBFIELD(local_496c.sa_data,6,undefined4) = *(undefined4 *)(param_2 + 0xe);
      SUBFIELD(local_496c.sa_data,10,undefined4) = *(undefined4 *)(param_2 + 0x12);
      local_495c = 0;
      FUN_00503e10();
      FUN_004fdc50();
      FUN_00503e30(local_48ba + 0x2e);
      local_4924 = *(undefined4 *)(param_2 + 0x22);
      local_4920 = *(undefined4 *)(param_2 + 0x26);
      local_4978 = CONCAT22(SUBFIELD(local_4978,2,undefined2),*(undefined2 *)(param_2 + 0x2a));
      local_491c = 0;
      FUN_004fdc50();
      iVar7 = local_497c;
      FUN_00502750();
      FUN_00503a10();
      FUN_004fe5d0();
      FUN_005037f0();
      local_48be = (undefined2)local_4978;
      local_48c9 = 0;
      local_48de = 0;
      (**(code **)(**(int **)(iVar7 + 0x17bc) + 0x2c))(local_48f0);
    }
    goto LAB_00502483;
  }
  if (uVar6 == 0x3fff) {
    if (1 < param_3) {
      if (*puVar1 != 0) {
        local_4984 = (uint)*puVar1;
        local_4970 = (undefined4 *)(param_1 + -0x2c8);
        puVar15 = (undefined4 *)(param_2 + 6);
        do {
          SUBFIELD(local_496c,0,undefined4) = *puVar15;
          SUBFIELD(local_496c.sa_data,2,undefined4) = puVar15[1];
          SUBFIELD(local_496c.sa_data,6,undefined4) = puVar15[2];
          SUBFIELD(local_496c.sa_data,10,undefined4) = puVar15[3];
          local_4902 = *(char *)(puVar15 + 4) != '\0';
          pcVar12 = (char *)((int)puVar15 + 0x11);
          local_495c = 0;
          if ((bool)local_4902) {
            local_4980 = (char *)((int)puVar15 + 0x1d);
            FUN_005039a0(*(undefined4 *)pcVar12,*(undefined2 *)((int)puVar15 + 0x15),
                         *(undefined4 *)((int)puVar15 + 0x17));
            pcVar12 = local_4980;
            param_1 = local_497c;
          }
          else {
            FUN_00503a50(local_4970,&local_496c);
            FUN_004fdc50();
            FUN_004fe500();
          }
          uVar10 = 0;
          do {
            uVar18 = uVar10;
            if (local_496c.sa_data[uVar10 - 2] == '\0') break;
            bVar5 = (char)uVar10 + 1;
            uVar18 = (uint)bVar5;
            local_4914[uVar10] = local_496c.sa_data[uVar10 - 2];
            uVar10 = uVar18;
          } while (bVar5 < 0x10);
          piVar2 = *(int **)(param_1 + 0x17bc);
          local_4903 = (undefined1)uVar18;
          local_4914[uVar18] = '\0';
          (**(code **)(*piVar2 + 0x14))(local_4914);
          local_4984 = local_4984 - 1;
          puVar15 = (undefined4 *)pcVar12;
        } while (local_4984 != 0);
      }
    }
    goto LAB_00502483;
  }
  if ((uVar6 != 0x4001) || (param_3 < 2)) goto LAB_00502483;
  local_4954 = 0;
  local_4950 = 0;
  local_494c = 0;
  local_c = 3;
  if (*puVar1 == 0) {
    if (3 < param_3) {
      iVar7 = param_2 + 8;
      if (*(ushort *)(param_2 + 6) != 0) {
        local_4984 = (uint)*(ushort *)(param_2 + 6);
        local_4980 = (char *)(param_1 + 0x17cc);
        do {
          FUN_004fe5d0();
          FUN_00503e10();
          FUN_00503e30(&local_4944);
          FUN_005037f0();
          local_4928 = *(undefined2 *)(iVar7 + 0x24);
          iVar7 = iVar7 + 0x26;
          FUN_00502920(&local_4944);
          local_4984 = local_4984 - 1;
        } while (local_4984 != 0);
        local_4984 = 0;
      }
      goto LAB_00502356;
    }
  }
  else {
LAB_00502356:
    (**(code **)(**(int **)(local_497c + 0x17bc) + 0x34))(local_4958);
  }
  FUN_005028f0();
LAB_00502483:
  *unaff_FS_OFFSET = local_14;
  return 1;
}

