/* FUN_004d27e0 - 0x004d27e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Type propagation algorithm not settling */

void FUN_004d27e0(int param_1,HWND param_2)

{
  short *psVar1;
  ushort uVar2;
  ushort uVar3;
  undefined1 uVar4;
  short sVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  ushort *lParam;
  char *pcVar9;
  uint uVar10;
  undefined3 uVar12;
  LPCSTR pCVar11;
  LPCSTR lpText;
  uint uVar13;
  int iVar14;
  undefined4 *puVar15;
  ushort *puVar16;
  undefined4 *unaff_FS_OFFSET;
  bool bVar17;
  UINT UVar18;
  int local_24e4;
  undefined1 local_24dc [8];
  char local_24d4 [128];
  undefined1 local_2454 [20];
  int local_2440;
  undefined1 local_2230 [20];
  int local_221c;
  undefined4 local_200c [2047];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053df96;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4d27ff;
  if ((*(char *)(param_1 + 0x84e4) != '\0') && (*(int *)(*(int *)(param_1 + 0x84e0) + 0x22c) != 3))
  {
    *(undefined1 *)(param_1 + 0x84e4) = 0;
    *(bool *)(param_1 + 0x84e5) = *(int *)(*(int *)(param_1 + 0x84e0) + 0x22c) == 2;
  }
LAB_004d2840:
  do {
    iVar6 = *(int *)(param_1 + 0x84e0);
    iVar14 = *(int *)(iVar6 + 0x24238);
    if (iVar14 == *(int *)(iVar6 + 0x24234)) {
LAB_004d33f1:
      *unaff_FS_OFFSET = local_c;
      return;
    }
    local_24e4 = *(int *)(iVar6 + 0x24640 + iVar14 * 4);
    uVar13 = iVar14 + 1U & 0x800000ff;
    psVar1 = (short *)(*(int *)(iVar6 + 0x24240 + iVar14 * 4) + 0x4234 + iVar6);
    if ((int)uVar13 < 0) {
      uVar13 = (uVar13 - 1 | 0xffffff00) + 1;
    }
    *(uint *)(iVar6 + 0x24238) = uVar13;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar6 + 2 + local_24e4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = FUN_0040a7d0(param_1 + 0x2a8,local_2230,0x343fd);
    local_4 = 0;
    FUN_0040a5f0(uVar7,local_2454,0x29ac03);
    local_4._0_1_ = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    sVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = (uint)local_4._1_3_ << 8;
    if (local_2440 != 0) {
      iVar14 = 0;
      iVar6 = local_2440 * 0x10;
      do {
        iVar8 = _rand();
        *(char *)(iVar6 + DAT_0079376c + iVar14) = (char)iVar8;
        iVar14 = iVar14 + 1;
      } while (iVar14 < 0x10);
      FUN_0040b540(local_24dc);
    }
    local_4 = 0xffffffff;
    if (local_221c != 0) {
      iVar14 = 0;
      iVar6 = local_221c * 0x10;
      do {
        iVar8 = _rand();
        *(char *)(iVar6 + DAT_0079376c + iVar14) = (char)iVar8;
        iVar14 = iVar14 + 1;
      } while (iVar14 < 0x10);
      FUN_0040b540(local_24dc);
    }
  } while (*psVar1 != sVar5);
  uVar2 = psVar1[1];
  lParam = (ushort *)(psVar1 + 2);
  if (uVar2 < 0x4103) {
    if (uVar2 != 0x4102) {
      if (uVar2 < 0x2020) {
        if (uVar2 != 0x201f) {
          if (uVar2 == 0x1021) goto LAB_004d2a44;
          if ((uVar2 < 0x1032) || (0x1033 < uVar2)) goto LAB_004d2adb;
        }
      }
      else if (uVar2 != 0x3432) goto LAB_004d2adb;
    }
LAB_004d2a70:
    uVar7 = *(undefined4 *)(param_1 + 0x84e8);
    iVar6 = local_24e4 + -4;
    puVar16 = lParam;
LAB_004d2a90:
    FUN_004f7150(uVar7,uVar2,puVar16,0x2000);
    iVar6 = (int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4;
    uVar13 = iVar6 * 0xc;
    puVar15 = local_200c;
    for (uVar13 = (uVar13 & ((int)uVar13 < 0) - 1) >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
      *(undefined4 *)puVar16 = *puVar15;
      puVar15 = puVar15 + 1;
      puVar16 = puVar16 + 2;
    }
    local_24e4 = local_24e4 + iVar6 * -4;
    for (iVar6 = 0; iVar6 != 0; iVar6 = iVar6 + -1) {
      *(undefined1 *)puVar16 = *(undefined1 *)puVar15;
      puVar15 = (undefined4 *)((int)puVar15 + 1);
      puVar16 = (ushort *)((int)puVar16 + 1);
    }
  }
  else if (uVar2 < 0x6002) {
    if (uVar2 == 0x6001) {
LAB_004d2a44:
      uVar7 = *(undefined4 *)(param_1 + 0x84e8);
      puVar16 = (ushort *)(psVar1 + 3);
      iVar6 = local_24e4 + -6;
      goto LAB_004d2a90;
    }
    if ((uVar2 == 0x4106) || (uVar2 == 0x4410)) goto LAB_004d2a70;
  }
  else if (uVar2 == 0x6002) goto LAB_004d2a70;
LAB_004d2adb:
  uVar13 = (uint)uVar2;
  if (0x2001 < uVar13) {
    if (uVar13 < 0x4010) {
      if (uVar13 != 0x400f) {
        if ((uVar13 != 0x2103) && (uVar13 != 0x2111)) {
          bVar17 = uVar13 == 0x2121;
          goto LAB_004d2b17;
        }
        goto LAB_004d2d5c;
      }
      *(undefined4 *)(param_1 + 0x44d0) = 6;
      *(undefined2 *)(param_1 + 0x4d4) = 0x2000;
      *(undefined2 *)(param_1 + 0x4d6) = 0xffff;
      *(int *)(param_1 + 0x44d0) = *(int *)(param_1 + 0x44d0) + 2;
      FUN_004d2680();
    }
    else if ((uVar13 == 0x6017) || (uVar13 == 0x6037)) goto LAB_004d2d5c;
    goto switchD_004d2d94_caseD_5;
  }
  if (uVar13 == 0x2001) {
LAB_004d2d5c:
    uVar10 = (uint)*lParam;
    uVar4 = (undefined1)(*lParam >> 8);
    if (0x2008 < uVar10) {
      if (uVar10 < 0x7005) {
        if (uVar10 != 0x7004) {
          if (uVar10 < 0x6002) {
            if (uVar10 == 0x6001) {
              if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
              uVar13 = (uint)CONCAT11(uVar4,uVar2 == 0x1031);
            }
            else if (uVar10 < 0x5012) {
              if (uVar10 == 0x5011) {
                if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
                uVar13 = (uint)CONCAT11(uVar4,uVar2 == 0x1031);
              }
              else if (uVar10 == 0x3001) {
                if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
                uVar13 = (uint)CONCAT11(uVar4,uVar2 == 0x1031);
              }
              else {
                if (uVar10 != 0x5001) goto switchD_004d2d94_caseD_5;
                if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
                uVar13 = (uint)CONCAT11(uVar4,uVar2 == 0x1031);
              }
            }
            else if (uVar10 == 0x5012) {
              if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
              uVar13 = (uint)(uVar2 == 0x1031);
            }
            else {
              if (uVar10 != 0x5013) goto switchD_004d2d94_caseD_5;
              if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
              uVar13 = (uint)(uVar2 == 0x1031);
            }
            goto LAB_004d337b;
          }
          switch(uVar10) {
          case 0x7000:
            break;
          case 0x7001:
            break;
          case 0x7002:
            break;
          case 0x7003:
            break;
          default:
            goto switchD_004d2d94_caseD_5;
          }
        }
      }
      else {
        if (0x8001 < uVar10) {
          if (uVar10 < 0xf001) {
            if (((uVar10 == 0xf000) || (uVar10 == 0x8002)) || (uVar10 == 0x8003))
            goto joined_r0x004d3289;
          }
          else if (uVar10 == 0xf001) goto switchD_004d2d94_caseD_13;
          goto switchD_004d2d94_caseD_5;
        }
        if (uVar10 != 0x8001) {
          if (uVar10 < 0x7008) {
            if (((uVar10 == 0x7007) || (uVar10 == 0x7005)) || (uVar10 == 0x7006))
            goto joined_r0x004d3289;
          }
          else if ((uVar10 == 0x7008) || (uVar10 == 0x8000)) goto joined_r0x004d3289;
switchD_004d2d94_caseD_5:
          goto LAB_004d2b24;
        }
      }
joined_r0x004d3289:
      if (param_2 == (HWND)0x0) goto LAB_004d3379;
LAB_004d2b2c:
      SendMessageA(param_2,0x464,uVar13,(LPARAM)lParam);
      goto LAB_004d2840;
    }
    if (uVar10 != 0x2008) {
      if (0x20 < uVar10) {
        if (uVar10 < 0x2002) {
          if (uVar10 == 0x2001) {
            if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
            uVar13 = (uint)CONCAT11(uVar4,uVar2 == 0x1031);
          }
          else if (uVar10 < 0x1002) {
            if (uVar10 != 0x1001) {
              if (uVar10 == 0x30) {
                if (param_2 == (HWND)0x0) goto LAB_004d3379;
                UVar18 = 0;
                pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19d);
                uVar7 = 0x197;
              }
              else {
                if (uVar10 != 0x60) goto switchD_004d2d94_caseD_5;
                if (param_2 == (HWND)0x0) goto LAB_004d3379;
                UVar18 = 0;
                pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19d);
                uVar7 = 0x198;
              }
              goto LAB_004d33cb;
            }
            if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
            uVar13 = (uint)CONCAT11(uVar4,uVar2 == 0x1031);
          }
          else if (uVar10 == 0x1002) {
            if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
            uVar13 = (uint)(uVar2 == 0x1031);
          }
          else {
            if (uVar10 != 0x1003) goto switchD_004d2d94_caseD_5;
            if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
            uVar13 = (uint)(uVar2 == 0x1031);
          }
        }
        else {
          uVar12 = (undefined3)(uVar10 - 0x2002 >> 8);
          switch(uVar10 - 0x2002) {
          case 0:
            if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
            uVar13 = CONCAT31(uVar12,uVar2 == 0x1031);
            break;
          case 1:
            if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
            uVar13 = CONCAT31(uVar12,uVar2 == 0x1031);
            break;
          case 2:
            if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
            uVar13 = CONCAT31(uVar12,uVar2 == 0x1031);
            break;
          case 3:
          case 4:
          case 5:
            goto switchD_004d2d94_caseD_13;
          default:
            goto switchD_004d2d94_caseD_5;
          }
        }
        goto LAB_004d337b;
      }
      if (uVar10 != 0x20) {
        uVar12 = (undefined3)(uVar10 - 1 >> 8);
        switch(uVar10) {
        case 1:
          if (param_2 == (HWND)0x0) {
            uVar13 = CONCAT31(uVar12,uVar2 == 0x1031);
            goto LAB_004d337b;
          }
          UVar18 = 0;
          pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19c);
          uVar7 = 400;
          break;
        case 2:
        case 3:
        case 4:
        case 7:
        case 8:
          if (param_2 == (HWND)0x0) goto LAB_004d3379;
          UVar18 = 0;
          pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19c);
          uVar7 = 0x191;
          break;
        default:
          goto switchD_004d2d94_caseD_5;
        case 0x10:
          if (param_2 == (HWND)0x0) {
            uVar13 = CONCAT31(uVar12,uVar2 == 0x1031);
            goto LAB_004d337b;
          }
          UVar18 = 0;
          pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19d);
          uVar7 = 0x193;
          break;
        case 0x11:
          if (param_2 == (HWND)0x0) {
            uVar13 = CONCAT31(uVar12,uVar2 == 0x1031);
            goto LAB_004d337b;
          }
          UVar18 = 0;
          pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19d);
          uVar7 = 0x194;
          break;
        case 0x12:
          if (param_2 == (HWND)0x0) {
            uVar13 = CONCAT31(uVar12,uVar2 == 0x1031);
            goto LAB_004d337b;
          }
          UVar18 = 0;
          pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19d);
          uVar7 = 0x195;
          break;
        case 0x13:
        case 0x18:
        case 0x1a:
        case 0x1b:
        case 0x1c:
        case 0x1e:
switchD_004d2d94_caseD_13:
          if (param_2 == (HWND)0x0) goto LAB_004d3379;
          UVar18 = 0;
          pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19d);
          uVar7 = 0x196;
          break;
        case 0x19:
          if (param_2 == (HWND)0x0) {
            uVar13 = CONCAT31(uVar12,uVar2 == 0x1031);
            goto LAB_004d337b;
          }
          UVar18 = 0;
          pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19d);
          uVar7 = 0x192;
        }
LAB_004d33cb:
        lpText = (LPCSTR)FUN_0043dc70(&DAT_00796eec,uVar7);
        MessageBoxA(param_2,lpText,pCVar11,UVar18);
LAB_004d2b24:
        if (param_2 == (HWND)0x0) goto LAB_004d3383;
        goto LAB_004d2b2c;
      }
      ShowErrorDialog(1);
      goto LAB_004d33f1;
    }
    if (param_2 != (HWND)0x0) goto LAB_004d2b2c;
    uVar13 = (uint)CONCAT11(uVar4,uVar2 == 0x1031);
LAB_004d337b:
    ShowErrorDialog(uVar13);
  }
  else {
    if (uVar13 < 0x1103) {
      if (((uVar13 != 0x1102) && (uVar13 != 0x1012)) && (uVar13 != 0x1031)) {
        bVar17 = uVar13 == 0x1079;
LAB_004d2b17:
        if (!bVar17) goto switchD_004d2d94_caseD_5;
      }
      goto LAB_004d2d5c;
    }
    if (uVar13 == 0x1312) goto LAB_004d2d5c;
    if (uVar13 != 0x1fff) goto switchD_004d2d94_caseD_5;
    FUN_004d24f0();
    if (param_2 != (HWND)0x0) {
      uVar3 = *lParam;
      if (uVar3 == 0) {
        UVar18 = 0;
        pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19d);
        uVar7 = 0x199;
        goto LAB_004d33cb;
      }
      if (uVar3 == 1) {
        iVar6 = g_clientContext + 0x23330;
        pcVar9 = (char *)FUN_0043dc70(&DAT_00796eec,0x19a);
        _sprintf(local_24d4,pcVar9,iVar6);
        UVar18 = 0;
        pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19e);
        MessageBoxA(param_2,local_24d4,pCVar11,UVar18);
      }
      else if (uVar3 == 2) {
        iVar6 = g_clientContext + 0x23313;
        pcVar9 = (char *)FUN_0043dc70(&DAT_00796eec,0x19b);
        _sprintf(local_24d4,pcVar9,iVar6);
        UVar18 = 0;
        pCVar11 = (LPCSTR)FUN_0043dc70(&DAT_00796eec,0x19e);
        MessageBoxA(param_2,local_24d4,pCVar11,UVar18);
      }
      goto LAB_004d2b24;
    }
    uVar3 = *lParam;
    if (0x1000 < uVar3) {
      if (((uVar3 != 0x1001) && (uVar3 != 0x1002)) && (uVar3 != 0x100f)) {
switchD_004d2b8e_caseD_3:
      }
      goto LAB_004d3379;
    }
    if (uVar3 == 0x1000) goto LAB_004d3379;
    switch(uVar3) {
    case 0:
      goto LAB_004d3379;
    case 1:
      ShowErrorDialogFmt(1,g_clientContext + 0x2331c);
      break;
    case 2:
      ShowErrorDialogFmt(1,g_clientContext + 0x23313);
      break;
    default:
      goto switchD_004d2b8e_caseD_3;
    case 0x10:
LAB_004d3379:
      uVar13 = 1;
      goto LAB_004d337b;
    }
  }
LAB_004d3383:
  WriteReplayEventRecord(local_24e4 + -4,uVar2,lParam);
  goto LAB_004d2840;
}

