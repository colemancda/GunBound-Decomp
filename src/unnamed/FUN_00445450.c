/* FUN_00445450 - 0x00445450 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * PARTIALLY FIXED (2026-07-13): InvokeWidget's own dropped widgetId
 * fixed at its 2 call sites here (ids 52, 53 per an angr CFG backward-
 * scan). This file's own `extraout_AH` (same declared-but-never-
 * assigned pattern already fixed in State02_ServerSelect_
 * ProcessPacket.c) is a separate, still-unfixed issue - not attempted
 * here to keep this pass scoped to InvokeWidget.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall FUN_00445450(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined1 uVar2;
  char extraout_AH;
  int iVar3;
  char extraout_AH_00;
  uint uVar4;
  void *pvVar5;
  uint uVar6;
  undefined4 uVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 uVar12;
  char *pcVar13;
  byte bVar14;
  undefined2 *puVar15;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_451c; /* Ghidra register slot; was undefined1 [4] */
  undefined4 local_4518;
  char local_4418 [256];
  undefined1 local_4318 [548];
  char local_40f4 [24];
  undefined1 local_40dc [548];
  undefined1 local_3eb8 [4996];
  undefined1 local_2b34 [548];
  undefined1 local_2910 [548];
  undefined1 local_26ec [548];
  undefined1 local_24c8 [548];
  undefined1 local_22a4 [548];
  undefined1 local_2080 [548];
  undefined1 local_1e5c [548];
  undefined1 local_1c38 [548];
  undefined1 local_1a14 [1120];
  undefined1 local_15b4 [548];
  undefined1 local_1390 [4992];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  /* BuildSystemInfoBlob's 2nd output (orig ESI, dropped) - NOT verified
   * against this call site's original disassembly; added only to satisfy
   * the now-2-parameter signature (see BuildSystemInfoBlob.c). Revisit if
   * this code path is ever exercised. */
  undefined4 systemInfoBlob2 [6];

  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053d96a;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x44546f;
  FUN_00425350();
  local_4 = 0;
  if (param_2 != 0) {
    if ((param_2 != 0xb) || (cVar1 = PeekPacketChecksumBool(), cVar1 != '\0')) goto switchD_00445591_caseD_2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)(param_1 + 0x32c54) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)(param_1 + 0x32c55) = (byte)iVar3;
    bVar14 = *(byte *)(param_1 + 0x32c54) & 7;
    bVar14 = ~('\x01' << bVar14) & (byte)iVar3 | '\0' << bVar14;
    *(byte *)(param_1 + 0x32c55) = bVar14;
    *(byte *)(param_1 + 0x32c56) = *(byte *)(param_1 + 0x32c54) + bVar14 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RemoveWidget();
LAB_00445543:
    RemoveWidget();
    FUN_0040cdf0();
    FUN_0040cdf0();
    FUN_0044b720(param_1);
    goto switchD_00445591_caseD_2;
  }
  switch(param_4) {
  case 0:
    *(undefined1 *)(param_1 + 0x30bb9) = 1;
    FUN_0044bf00(param_1);
    break;
  case 1:
    BuildBuddyPanel();
    break;
  case 10:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if (((cVar1 != '\0') || (cVar1 = PeekPacketChecksumBool(), cVar1 == '\x01')) ||
       ((cVar1 = PeekPacketChecksumBool(), cVar1 == '\x01' || (g_stateChangeInProgress != 0)))) break;
    FUN_00449540(param_1,1);
    FUN_00449250(param_1,1,0);
    SetWidgetReadyState(1);
    uVar12 = 0;
    goto LAB_00445629;
  case 0xb:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if (((cVar1 != '\0') || (cVar1 = PeekPacketChecksumBool(), cVar1 == '\x01')) ||
       ((cVar1 = PeekPacketChecksumBool(), cVar1 == '\x01' || (g_stateChangeInProgress != 0)))) break;
    FUN_00449540(param_1,0);
    FUN_00449250(param_1,1,0);
    SetWidgetReadyState(0);
    uVar12 = 1;
LAB_00445629:
    SetWidgetReadyState(uVar12);
    uVar12 = 0;
LAB_0044563c:
    SetWidgetReadyState(uVar12);
    uVar12 = 0;
LAB_004457e7:
    SetWidgetReadyState(uVar12);
    break;
  case 0xc:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if ((((cVar1 != '\0') || (cVar1 = PeekPacketChecksumBool(), cVar1 == '\x01')) ||
        (cVar1 = PeekPacketChecksumBool(), cVar1 == '\x01')) || (g_stateChangeInProgress != 0)) break;
    FUN_00449540(param_1,2);
    FUN_00449250(param_1,1,0);
    SetWidgetReadyState(0);
    SetWidgetReadyState(0);
    uVar12 = 1;
    goto LAB_0044563c;
  case 0xd:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if (((cVar1 != '\0') || (cVar1 = PeekPacketChecksumBool(), cVar1 == '\x01')) ||
       ((cVar1 = PeekPacketChecksumBool(), cVar1 == '\x01' || (g_stateChangeInProgress != 0)))) break;
    FUN_00449540(param_1,3);
    FUN_00449250(param_1,1,0);
    SetWidgetReadyState(0);
    SetWidgetReadyState(0);
    SetWidgetReadyState(0);
    uVar12 = 1;
    goto LAB_004457e7;
  case 0xe:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if ((cVar1 == '\0') && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) {
      PeekPacketChecksumBool();
    }
    break;
  case 0xf:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if ((((cVar1 == '\0') && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
        (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) && (g_stateChangeInProgress == 0)) {
      PreviewAvatarPart();
    }
    break;
  case 0x10:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if (((cVar1 == '\0') && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
       ((cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01' && (g_stateChangeInProgress == 0)))) {
      if (*(uint *)(g_clientContext + 0x44e24) < 100) {
        FUN_00425350();
        iVar3 = param_1 + 4;
        local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
        iVar9 = PeekChecksumStateUnderLock(iVar3);
        uVar4 = (uint)*(ushort *)(param_1 + 0x2e54c + (iVar9 + *(int *)(param_1 + 0x450) * 9) * 2);
        uVar6 = (uint)*(byte *)(param_1 + 0x44c);
        iVar9 = PeekChecksumStateUnderLock(iVar3);
        FUN_004240c0(g_clientContext,
                     *(char *)(*(int *)(param_1 + 0x450) * 9 + 0x2d54c + iVar9 + param_1) == '\x01',
                     uVar6,uVar4);
        QueueOutgoingPacketField(1);
        iVar9 = PeekChecksumStateUnderLock(iVar3);
        local_451c = (undefined4)
                     ((*(char *)(*(int *)(param_1 + 0x450) * 9 + 0x2d54c + iVar9 + param_1) !=
                      '\x01') - 1 & 0x8000);
        uVar4 = PeekChecksumStateUnderLock(local_4318);
        QueueOutgoingPacketField
                  ((uint)local_451c | uVar4 | (*(uint *)(param_1 + 0x44c) & 0xf) << 0x10);
        pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,700);
        pcVar13 = (char *)(param_1 + 0x327d4);
        do {
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
          *pcVar13 = cVar1;
          pcVar13 = pcVar13 + 1;
        } while (cVar1 != '\0');
        pcVar13 = local_40f4;
        pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,60000);
        _sprintf((char *)(param_1 + 0x32854),pcVar8,pcVar13);
        pcVar13 = local_40f4;
        iVar9 = param_1 - (int)pcVar13;
        do {
          cVar1 = *pcVar13;
          pcVar13[iVar9 + 0x34794] = cVar1;
          pcVar13 = pcVar13 + 1;
        } while (cVar1 != '\0');
        iVar9 = PeekChecksumStateUnderLock(local_40dc);
        if (iVar9 == 0) {
          pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0xea62);
          _sprintf((char *)(param_1 + 0x32954),pcVar13);
        }
        else {
          uVar12 = PeekChecksumStateUnderLock(local_40dc);
          pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0xea61);
          _sprintf((char *)(param_1 + 0x32954),pcVar13,uVar12);
        }
        iVar9 = PeekChecksumStateUnderLock(local_3eb8);
        if (iVar9 == 0) {
          pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0xea64);
          _sprintf((char *)(param_1 + 0x329d4),pcVar13);
        }
        else {
          uVar12 = PeekChecksumStateUnderLock(local_3eb8);
          pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0xea63);
          _sprintf((char *)(param_1 + 0x329d4),pcVar13,uVar12);
        }
        iVar9 = PeekChecksumStateUnderLock(local_40dc);
        iVar9 = (iVar9 * 6) / 10;
        pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0xea65);
        _sprintf((char *)(param_1 + 0x32a54),pcVar13,iVar9);
        if (*(int *)(param_1 + 0x44c) == 3) {
          *(undefined1 *)(param_1 + 0x32bd4) = 0;
          *(undefined1 *)(param_1 + 0x32b54) = 0;
        }
        else {
          iVar9 = PeekChecksumStateUnderLock(iVar3);
          if (*(char *)(*(int *)(param_1 + 0x450) * 9 + 0x2d54c + iVar9 + param_1) == '\0') {
            pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0xea67);
          }
          else {
            pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0xea66);
          }
          _sprintf((char *)(param_1 + 0x32b54),pcVar13);
          pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0xea68);
          _sprintf((char *)(param_1 + 0x32bd4),pcVar13);
        }
        iVar9 = g_clientContext + 0x398c4;
        *(undefined1 *)(param_1 + 0x32ad4) = 0;
        *(undefined1 *)(param_1 + 0x328d4) = 0;
        uVar12 = PeekChecksumStateUnderLock(iVar9);
        cVar1 = PacketChecksumGreaterThan(local_3eb8,uVar12);
        if (cVar1 != '\0') {
          CreateButtonWidget(&DAT_00e9be90,0,0x3c,0x518,s_b_storewindow_cashcharge_00555a70,0xd0,
                             0x146,0x88,0x28,1,0);
        }
        uVar12 = PeekChecksumStateUnderLock(g_clientContext + 0x396a0);
        cVar1 = PacketChecksumLessEqual(local_40dc,uVar12);
        if ((cVar1 == '\0') || (cVar1 = PacketChecksumNotEquals(local_40dc,0), cVar1 == '\0')) {
          uVar12 = 0;
        }
        else {
          uVar12 = 1;
        }
        CreateButtonWidget(&DAT_00e9be90,0,0x32,0x519,s_b_storewindow_gold_00555a5c,0xea,0x178,0x55,
                           0x24,uVar12,0);
        uVar12 = PeekChecksumStateUnderLock(g_clientContext + 0x398c4);
        cVar1 = PacketChecksumLessEqual(local_3eb8,uVar12);
        if ((cVar1 == '\0') || (cVar1 = PacketChecksumNotEquals(local_3eb8,0), cVar1 == '\0')) {
          uVar12 = 0;
        }
        else {
          uVar12 = 1;
        }
        CreateButtonWidget(&DAT_00e9be90,0,0x37,0x51a,s_b_storewindow_cash_00555a48,0x95,0x178,0x55,
                           0x24,uVar12,0);
        CreateButtonWidget(&DAT_00e9be90,0,0x33,0x517,s_b_storewindow_cancel_00555a30,0x13f,0x178,
                           0x4a,0x1a,1,0);
        uVar12 = PeekChecksumStateUnderLock(iVar3);
        *(undefined4 *)(param_1 + 0x34788) = uVar12;
        local_4 = local_4 & 0xffffff00;
        FUN_004254a0();
      }
      else {
        ShowErrorDialog(0);
      }
    }
    break;
  case 0x11:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if ((((cVar1 == '\0') && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
        (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) && (g_stateChangeInProgress == 0)) {
      FUN_00449b60(param_1);
    }
    break;
  case 0x12:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if (((cVar1 == '\0') && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
       ((cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01' && (g_stateChangeInProgress == 0)))) {
      FUN_00449db0(param_1);
    }
    break;
  case 0x14:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if ((((cVar1 == '\0') && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
        (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) && (g_stateChangeInProgress == 0)) {
      iVar3 = param_1 + 0x3054c;
      iVar9 = PeekChecksumStateUnderLock(param_1 + 0x228);
      QueueOutgoingPacketField(iVar9 + *(int *)(param_1 + 0x454));
      cVar1 = PacketChecksumEquals(param_1 + 0x228,0xffffffff);
      if ((cVar1 == '\0') &&
         (uVar4 = *(uint *)(g_clientContext + 0x44e24), uVar6 = PeekChecksumStateUnderLock(iVar3), uVar6 < uVar4)) {
        PeekChecksumStateUnderLock(iVar3);
        iVar9 = FUN_00426570();
        iVar9 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
        uVar4 = iVar9 >> 0x1c;
        if ((uVar4 & 8) == 0) {
          if ((uVar4 & 4) == 0) {
            if ((uVar4 & 2) == 0) {
              FUN_00425350();
              SUBFIELD(local_4,0,undefined1) = 2;
              PeekChecksumStateUnderLock(iVar3);
              iVar9 = FUN_00426570();
              PeekChecksumStateUnderLock(iVar9 + 0x22c);
              PeekChecksumStateUnderLock(iVar3);
              iVar3 = FUN_00426570();
              iVar3 = PeekChecksumStateUnderLock(iVar3 + 0x22c);
              FUN_00423e20(g_clientContext,iVar3 >> 0x10 & 0xffffff0f);
              QueueOutgoingPacketField(2);
              pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x2c3);
              pcVar13 = (char *)(param_1 + 0x327d4);
              do {
                cVar1 = *pcVar8;
                pcVar8 = pcVar8 + 1;
                *pcVar13 = cVar1;
                pcVar13 = pcVar13 + 1;
              } while (cVar1 != '\0');
              pcVar13 = local_40f4;
              pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x2c4);
              _sprintf((char *)(param_1 + 0x32854),pcVar8,pcVar13);
              iVar3 = PeekChecksumStateUnderLock(local_40dc);
              iVar9 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
              iVar9 = (iVar3 * 6) / iVar9;
              pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0x2c5);
              _sprintf((char *)(param_1 + 0x328d4),pcVar13,iVar9);
              iVar3 = PeekChecksumStateUnderLock(local_40dc);
              iVar9 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
              iVar10 = PeekChecksumStateUnderLock(g_clientContext + 0x396a0);
              iVar10 = (iVar3 * 6) / iVar9 + iVar10;
              pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0x2c6);
              _sprintf((char *)(param_1 + 0x32954),pcVar13,iVar10);
              *(undefined1 *)(param_1 + 0x329d4) = 0;
              pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x2c7);
              pcVar13 = (char *)(param_1 + 0x32a54);
              do {
                cVar1 = *pcVar8;
                pcVar8 = pcVar8 + 1;
                *pcVar13 = cVar1;
                pcVar13 = pcVar13 + 1;
              } while (cVar1 != '\0');
              *(undefined1 *)(param_1 + 0x32ad4) = 0;
              CreateButtonWidget(&DAT_00e9be90,0,0x32,0x516,s_b_storewindow_yes_00555a1c,0xf2,0x154,
                                 0x4a,0x1a,1,0);
              CreateButtonWidget(&DAT_00e9be90,0,0x33,0x517,s_b_storewindow_cancel_00555a30,0x14d,
                                 0x154,0x4a,0x1a,1,0);
              local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
              FUN_004254a0();
            }
            else {
              ShowErrorDialog(0);
            }
          }
          else {
            ShowErrorDialog(0);
          }
        }
        else {
          ShowErrorDialog(0);
        }
      }
    }
    break;
  case 0x16:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if (((cVar1 == '\0') && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
       ((cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01' && (g_stateChangeInProgress == 0)))) {
      iVar3 = param_1 + 0x3054c;
      iVar9 = PeekChecksumStateUnderLock(param_1 + 0x228);
      QueueOutgoingPacketField(iVar9 + *(int *)(param_1 + 0x454));
      cVar1 = PacketChecksumEquals(param_1 + 0x228,0xffffffff);
      if ((cVar1 == '\0') &&
         (uVar4 = *(uint *)(g_clientContext + 0x44e24), uVar6 = PeekChecksumStateUnderLock(iVar3), uVar6 < uVar4)) {
        PeekChecksumStateUnderLock(iVar3);
        iVar9 = FUN_00426570();
        iVar9 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
        if ((iVar9 >> 0x1c & 2U) == 0) {
          FUN_00425350();
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          PeekChecksumStateUnderLock(iVar9 + 0x22c);
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          iVar9 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
          FUN_00423e20(g_clientContext,iVar9 >> 0x10 & 0xffffff0f);
          SetGuardedBool(1);
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          iVar9 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
          *(uint *)(param_1 + 0x32c58) = (iVar9 >> 0x10 & 0xfU) << 1;
          pcVar13 = local_40f4;
          iVar9 = param_1 - (int)pcVar13;
          do {
            cVar1 = *pcVar13;
            pcVar13[iVar9 + 0x32c5c] = cVar1;
            pcVar13 = pcVar13 + 1;
          } while (cVar1 != '\0');
          if (*(int *)(param_1 + 0x32c58) == 6) {
            iVar9 = -1;
          }
          else {
            PeekChecksumStateUnderLock(iVar3);
            iVar9 = FUN_00426570();
            uVar4 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
            iVar9 = 6 - (uint)((uVar4 & 0x8000) != 0);
          }
          *(int *)(param_1 + 0x32cdc) = iVar9;
          if (*(int *)(param_1 + 0x32c58) != 6) {
            PeekChecksumStateUnderLock(iVar3);
            iVar9 = FUN_00426570();
            PeekChecksumStateUnderLock(iVar9 + 0x22c);
            if (-1 < extraout_AH) {
              *(int *)(param_1 + 0x32c58) = *(int *)(param_1 + 0x32c58) + 1;
            }
          }
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          PeekChecksumStateUnderLock(iVar9 + 0x22c);
          if (extraout_AH_00 < '\0') {
            SUBFIELD(local_4518,0,undefined3) = CONCAT12(DAT_00555a16,DAT_00555a14);
          }
          else {
            SUBFIELD(local_4518,0,undefined3) = CONCAT12(DAT_00555a1a,DAT_00555a18);
          }
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          iVar9 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
          switch(iVar9 >> 0x10 & 0xf) {
          case 0:
            puVar15 = (undefined2 *)(local_451c + 3);
            do {
              pcVar13 = (char *)((int)puVar15 + 1);
              puVar15 = (undefined2 *)((int)puVar15 + 1);
            } while (*pcVar13 != '\0');
            *puVar15 = DAT_00552c80;
            break;
          case 1:
            puVar15 = (undefined2 *)(local_451c + 3);
            do {
              pcVar13 = (char *)((int)puVar15 + 1);
              puVar15 = (undefined2 *)((int)puVar15 + 1);
            } while (*pcVar13 != '\0');
            *puVar15 = DAT_005535f0;
            break;
          case 2:
            puVar15 = (undefined2 *)(local_451c + 3);
            do {
              pcVar13 = (char *)((int)puVar15 + 1);
              puVar15 = (undefined2 *)((int)puVar15 + 1);
            } while (*pcVar13 != '\0');
            *puVar15 = DAT_00552c7c;
            break;
          case 3:
            local_4518 = &DAT_00666d73;
          }
          FUN_004f1c00();
          PeekChecksumStateUnderLock(iVar3);
          iVar3 = FUN_00426570();
          uVar4 = PeekChecksumStateUnderLock(iVar3 + 0x22c);
          _sprintf((char *)((int)&local_4518 + 3),s__05d_img_00555a08,uVar4 & 0x7fff);
          LoadSpriteSet(&DAT_00ea0e18,30000);
          CreateButtonWidget(&DAT_00e9be90,0,0x34,0x517,s_b_storewindow_cancel_00555a30,0x14d,0x154,
                             0x4a,0x1a,1,0);
          CreateButtonWidget(&DAT_00e9be90,0,0x35,0x516,s_b_storewindow_confirm_00555a8c,0xf2,0x154,
                             0x4a,0x1a,1,0);
          pvVar5 = operator_new(0x458);
          if (pvVar5 == (void *)0x0) {
            iVar3 = 0;
          }
          else {
            iVar3 = FUN_0040c980(0xf2,0x112,0x49,0xc,0xc,0);
          }
          *(undefined4 *)(iVar3 + 0x448) = 0;
          RegisterActiveObject(0, 0, (undefined4 *)0);
          pvVar5 = operator_new(0x458);
          if (pvVar5 == (void *)0x0) {
            iVar3 = 0;
          }
          else {
            iVar3 = FUN_0040c980(0xf2,0x139,0xa5,0xc,0x32,0);
          }
          *(undefined4 *)(iVar3 + 0x448) = 0;
          RegisterActiveObject(0, 0, (undefined4 *)0);
          FUN_0040cf80(&DAT_00e9c0fc);
          local_4 = local_4 & 0xffffff00;
          FUN_004254a0();
        }
        else {
          ShowErrorDialog(0);
        }
      }
    }
    break;
  case 0x1a:
    cVar1 = PacketChecksumNotEquals(param_1 + 0x325b0,0);
    if ((((cVar1 == '\0') && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
        (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) && (g_stateChangeInProgress == 0)) {
      FUN_00425350();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
      iVar3 = param_1 + 0x3054c;
      iVar9 = PeekChecksumStateUnderLock(param_1 + 0x228);
      QueueOutgoingPacketField(iVar9 + *(int *)(param_1 + 0x454));
      cVar1 = PacketChecksumEquals(param_1 + 0x228,0xffffffff);
      if ((cVar1 == '\0') &&
         (uVar4 = *(uint *)(g_clientContext + 0x44e24), uVar6 = PeekChecksumStateUnderLock(iVar3), uVar6 < uVar4)) {
        PeekChecksumStateUnderLock(iVar3);
        iVar9 = FUN_00426570();
        PeekChecksumStateUnderLock(iVar9 + 0x22c);
        PeekChecksumStateUnderLock(iVar3);
        iVar3 = FUN_00426570();
        iVar3 = PeekChecksumStateUnderLock(iVar3 + 0x22c);
        FUN_00423e20(g_clientContext,iVar3 >> 0x10 & 0xffffff0f);
        QueueOutgoingPacketField(3);
        pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x2c8);
        pcVar13 = (char *)(param_1 + 0x327d4);
        do {
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
          *pcVar13 = cVar1;
          pcVar13 = pcVar13 + 1;
        } while (cVar1 != '\0');
        pcVar13 = local_40f4;
        pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x2c9);
        _sprintf((char *)(param_1 + 0x32854),pcVar8,pcVar13);
        *(undefined1 *)(param_1 + 0x328d4) = 0;
        pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x2ca);
        pcVar13 = (char *)(param_1 + 0x32954);
        do {
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
          *pcVar13 = cVar1;
          pcVar13 = pcVar13 + 1;
        } while (cVar1 != '\0');
        *(undefined1 *)(param_1 + 0x329d4) = 0;
        pcVar8 = (char *)GetLocalizedString(&g_localizedStringTable,0x2cb);
        pcVar13 = (char *)(param_1 + 0x32a54);
        do {
          cVar1 = *pcVar8;
          pcVar8 = pcVar8 + 1;
          *pcVar13 = cVar1;
          pcVar13 = pcVar13 + 1;
        } while (cVar1 != '\0');
        *(undefined1 *)(param_1 + 0x32ad4) = 0;
        CreateButtonWidget(&DAT_00e9be90,0,0x32,0x516,s_b_storewindow_yes_00555a1c,0xf2,0x154,0x4a,
                           0x1a,1,0);
        CreateButtonWidget(&DAT_00e9be90,0,0x33,0x517,s_b_storewindow_cancel_00555a30,0x14d,0x154,
                           0x4a,0x1a,1,0);
      }
      local_4 = local_4 & 0xffffff00;
      FUN_004254a0();
    }
    break;
  case 0x32:
    iVar3 = PeekChecksumStateUnderLock(param_1 + 0x325b0);
    if (iVar3 == 1) {
      iVar3 = PeekChecksumStateUnderLock(param_1 + 4);
      uVar4 = (uint)*(ushort *)(param_1 + 0x2e54c + (iVar3 + *(int *)(param_1 + 0x450) * 9) * 2);
      uVar6 = (uint)*(byte *)(param_1 + 0x44c);
      iVar3 = PeekChecksumStateUnderLock(param_1 + 4);
      FUN_004240c0(g_clientContext,
                   *(char *)(*(int *)(param_1 + 0x450) * 9 + 0x2d54c + iVar3 + param_1) == '\x01',
                   uVar6,uVar4);
      iVar3 = DAT_007934e8;
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x6010;
      *(undefined4 *)(iVar3 + 0x44d0) = 6;
      uVar12 = EncodeChecksumNegate(local_15b4,local_2910);
      SUBFIELD(local_4,0,undefined1) = 5;
      EncodeChecksumState(uVar12);
      SUBFIELD(local_4,0,undefined1) = 0;
      ScrubChecksumGuard();
      QueueOutgoingPacketField(0);
      uVar12 = PeekChecksumStateUnderLock(param_1 + 0x3054c);
      iVar3 = DAT_007934e8;
      *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
      *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
      uVar12 = EncodeChecksumNegate(local_15b4,local_24c8);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),6);
      uVar12 = PeekChecksumStateUnderLock(uVar12);
      iVar3 = DAT_007934e8;
      *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
      *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
LAB_00446d18:
      local_4 = local_4 & 0xffffff00;
      ScrubChecksumGuard();
LAB_00446d2b:
      EncodePacketBody(0,iVar3);
      SendOutgoingPacket(iVar3);
      *(undefined1 *)(param_1 + 0x32f90) = 0;
    }
    else {
      if (iVar3 == 2) {
        iVar3 = param_1 + 0x3054c;
        PeekChecksumStateUnderLock(iVar3);
        iVar9 = FUN_00426570();
        PeekChecksumStateUnderLock(iVar9 + 0x22c);
        PeekChecksumStateUnderLock(iVar3);
        iVar9 = FUN_00426570();
        iVar9 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
        FUN_00423e20(g_clientContext,iVar9 >> 0x10 & 0xffffff0f);
        uVar12 = EncodeChecksumDeltaMul(local_15b4,local_1c38,6);
        SUBFIELD(local_4,0,undefined1) = 7;
        uVar7 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
        uVar12 = EncodeChecksumDeltaDiv(uVar12,local_1e5c,uVar7);
        SUBFIELD(local_4,0,undefined1) = 8;
        EncodeChecksumState(uVar12);
        SUBFIELD(local_4,0,undefined1) = 7;
        ScrubChecksumGuard();
        SUBFIELD(local_4,0,undefined1) = 0;
        ScrubChecksumGuard();
        PeekChecksumStateUnderLock(iVar3);
        FUN_00426570();
        cVar1 = PeekPacketChecksumBool();
        iVar9 = DAT_007934e8;
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        if (cVar1 == '\0') {
          *(undefined2 *)(iVar9 + 0x4d4) = 0x6020;
          uVar2 = PeekChecksumStateUnderLock(iVar3);
          iVar9 = DAT_007934e8;
          *(undefined1 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar2;
          *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 1;
          PeekChecksumStateUnderLock(iVar3);
          iVar3 = FUN_00426570();
          uVar12 = PeekChecksumStateUnderLock(iVar3 + 0x22c);
          iVar3 = DAT_007934e8;
          *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
          *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
          uVar12 = EncodeChecksumDeltaMul(local_15b4,local_2b34,6);
          SUBFIELD(local_4,0,undefined1) = 9;
          uVar7 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
          uVar12 = EncodeChecksumDeltaDiv(uVar12,local_26ec,uVar7);
          SUBFIELD(local_4,0,undefined1) = 10;
          uVar12 = PeekChecksumStateUnderLock(uVar12);
          iVar3 = DAT_007934e8;
          *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
          *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),9);
          ScrubChecksumGuard();
        }
        else {
          *(undefined2 *)(iVar9 + 0x4d4) = 0x6021;
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          uVar12 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
          iVar9 = DAT_007934e8;
          *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
          *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 4;
          PeekChecksumStateUnderLock(iVar3);
          iVar3 = FUN_00426570();
          uVar12 = PeekChecksumStateUnderLock(iVar3 + 8);
          iVar3 = DAT_007934e8;
          *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
          *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
          uVar12 = EncodeChecksumDeltaMul(local_15b4,local_1a14,6);
          SUBFIELD(local_4,0,undefined1) = 0xb;
          uVar7 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
          uVar12 = EncodeChecksumDeltaDiv(uVar12,local_22a4,uVar7);
          SUBFIELD(local_4,0,undefined1) = 0xc;
          uVar12 = PeekChecksumStateUnderLock(uVar12);
          iVar3 = DAT_007934e8;
          *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
          *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
          ScrubChecksumGuard();
        }
        goto LAB_00446d18;
      }
      if (iVar3 == 3) {
        QueueOutgoingPacketField(0);
        iVar3 = param_1 + 0x3054c;
        PeekChecksumStateUnderLock(iVar3);
        FUN_00426570();
        cVar1 = PeekPacketChecksumBool();
        iVar9 = DAT_007934e8;
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        if (cVar1 == '\0') {
          *(undefined2 *)(iVar9 + 0x4d4) = 0x6020;
          uVar2 = PeekChecksumStateUnderLock(iVar3);
          iVar9 = DAT_007934e8;
          *(undefined1 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar2;
          *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 1;
          PeekChecksumStateUnderLock(iVar3);
          iVar3 = FUN_00426570();
          uVar12 = PeekChecksumStateUnderLock(iVar3 + 0x22c);
        }
        else {
          *(undefined2 *)(iVar9 + 0x4d4) = 0x6021;
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          uVar12 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
          iVar9 = DAT_007934e8;
          *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
          *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 4;
          PeekChecksumStateUnderLock(iVar3);
          iVar3 = FUN_00426570();
          uVar12 = PeekChecksumStateUnderLock(iVar3 + 8);
        }
        iVar9 = DAT_007934e8;
        *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
        iVar3 = *(int *)(iVar9 + 0x44d0);
        *(int *)(iVar9 + 0x44d0) = iVar3 + 4;
        *(undefined4 *)(iVar3 + 0x4d4 + iVar9) = 0;
        *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 4;
        goto LAB_00446d2b;
      }
    }
    QueueOutgoingPacketField(0);
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    FUN_0044b720(param_1);
    FUN_00449250(param_1,1,0);
    break;
  case 0x33:
    QueueOutgoingPacketField(0);
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    FUN_0044b720(param_1);
    break;
  case 0x34:
    SetGuardedBool(0);
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    goto LAB_00445543;
  case 0x35:
    pcVar8 = (char *)FUN_0040cfe0();
    pcVar13 = (char *)(param_1 + 0x32ce3);
    do {
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      *pcVar13 = cVar1;
      pcVar13 = pcVar13 + 1;
    } while (cVar1 != '\0');
    pcVar8 = (char *)FUN_0040cfe0();
    pcVar13 = (char *)(param_1 + 0x32d63);
    do {
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      *pcVar13 = cVar1;
      pcVar13 = pcVar13 + 1;
    } while (cVar1 != '\0');
    pcVar13 = (char *)(param_1 + 0x32ce3);
    do {
      cVar1 = *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (cVar1 != '\0');
    iVar3 = (int)pcVar13 - (param_1 + 0x32ce4);
    while ((-1 < iVar3 + -1 && (*(char *)(iVar3 + 0x32ce2 + param_1) == ' '))) {
      *(undefined1 *)(iVar3 + 0x32ce2 + param_1) = 0;
      iVar3 = iVar3 + -1;
    }
    pcVar13 = (char *)(param_1 + 0x32ce3);
    do {
      cVar1 = *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (cVar1 != '\0');
    local_451c = (undefined4)((int)pcVar13 - (param_1 + 0x32ce4));
    if (local_451c != (undefined4)0x0) {
      pcVar13 = (char *)(param_1 + 0x32ce3);
      iVar3 = __stricmp(pcVar13,(char *)(g_clientContext + 0x23330));
      if (iVar3 != 0) {
        SetGuardedBool(1);
        iVar3 = param_1 + 0x3054c;
        iVar9 = PeekChecksumStateUnderLock(&DAT_005f4ab8 + g_clientContext);
        iVar10 = PeekChecksumStateUnderLock(iVar3);
        if (iVar9 == iVar10) {
LAB_00446f6d:
          *(undefined1 *)(param_1 + 0x30bb8) = 0;
          *(undefined1 *)(param_1 + 0x30bb9) = 0;
        }
        else {
          iVar9 = PeekChecksumStateUnderLock(&DAT_005f4cdc + g_clientContext);
          iVar10 = PeekChecksumStateUnderLock(iVar3);
          if (iVar9 == iVar10) goto LAB_00446f6d;
          iVar9 = PeekChecksumStateUnderLock(&DAT_005f4f00 + g_clientContext);
          iVar10 = PeekChecksumStateUnderLock(iVar3);
          if (iVar9 == iVar10) goto LAB_00446f6d;
          iVar9 = PeekChecksumStateUnderLock(&DAT_005f5124 + g_clientContext);
          iVar10 = PeekChecksumStateUnderLock(iVar3);
          if (iVar9 == iVar10) goto LAB_00446f6d;
        }
        *(undefined1 *)(param_1 + 0x30bb8) = 0;
        *(undefined1 *)(param_1 + 0x30bb9) = 0;
        PeekChecksumStateUnderLock(iVar3);
        FUN_00426570();
        cVar1 = PeekPacketChecksumBool();
        iVar9 = DAT_007934e8;
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        if (cVar1 == '\0') {
          *(undefined2 *)(iVar9 + 0x4d4) = 0x6030;
          *(undefined4 *)(iVar9 + 0x4d6) = *(undefined4 *)pcVar13;
          *(undefined4 *)(iVar9 + 0x4da) = *(undefined4 *)(param_1 + 0x32ce7);
          *(undefined4 *)(iVar9 + 0x4de) = *(undefined4 *)(param_1 + 0x32ceb);
          *(undefined4 *)(iVar9 + 0x4e2) = *(undefined4 *)(param_1 + 0x32cef);
          *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 0x10;
          PeekChecksumStateUnderLock(iVar3);
          iVar10 = FUN_00426570();
          iVar9 = DAT_007934e8;
          *(undefined1 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) =
               *(undefined1 *)(iVar10 + 4);
          *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 1;
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          uVar12 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
        }
        else {
          *(undefined2 *)(iVar9 + 0x4d4) = 0x6031;
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          uVar12 = PeekChecksumStateUnderLock(iVar9 + 0x22c);
          iVar10 = DAT_007934e8;
          *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
          iVar9 = *(int *)(iVar10 + 0x44d0);
          *(int *)(iVar10 + 0x44d0) = iVar9 + 4;
          puVar11 = (undefined4 *)(iVar9 + 0x4d4 + iVar10);
          *puVar11 = *(undefined4 *)pcVar13;
          puVar11[1] = *(undefined4 *)(param_1 + 0x32ce7);
          puVar11[2] = *(undefined4 *)(param_1 + 0x32ceb);
          puVar11[3] = *(undefined4 *)(param_1 + 0x32cef);
          *(int *)(iVar10 + 0x44d0) = *(int *)(iVar10 + 0x44d0) + 0x10;
          PeekChecksumStateUnderLock(iVar3);
          iVar9 = FUN_00426570();
          uVar12 = PeekChecksumStateUnderLock(iVar9 + 8);
        }
        iVar9 = DAT_007934e8;
        *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
        pcVar13 = (char *)(param_1 + 0x32d63);
        *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 4;
        do {
          cVar1 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar1 != '\0');
        *(char *)(*(int *)(iVar9 + 0x44d0) + 0x4d0 + iVar9) = (char)pcVar13 - ((char)param_1 + 'd');
        pcVar13 = (char *)(param_1 + 0x32d63);
        *(int *)(iVar9 + 0x44d0) = *(int *)(iVar9 + 0x44d0) + 1;
        do {
          cVar1 = *pcVar13;
          pcVar13 = pcVar13 + 1;
        } while (cVar1 != '\0');
        AppendPacketBytes(param_1 + 0x32d63);
        PeekChecksumStateUnderLock(iVar3);
        FUN_00426570();
        cVar1 = PeekPacketChecksumBool();
        iVar3 = DAT_007934e8;
        if (cVar1 == '\0') {
          uVar12 = 0;
        }
        else {
          uVar12 = 4;
        }
        FUN_004d34a0(uVar12,0);
        iVar9 = g_clientContext;
        puVar11 = (undefined4 *)(&DAT_006aa408 + g_clientContext);
        pcVar13 = (char *)(param_1 + 0x32ce3);
        iVar10 = (int)puVar11 - (int)pcVar13;
        do {
          cVar1 = *pcVar13;
          pcVar13[iVar10] = cVar1;
          pcVar13 = pcVar13 + 1;
        } while (cVar1 != '\0');
        *(undefined4 *)(iVar3 + 0x44d0) = 6;
        *(undefined2 *)(iVar3 + 0x4d4) = 0x1020;
        *(undefined4 *)(iVar3 + 0x4d6) = *puVar11;
        *(undefined4 *)(iVar3 + 0x4da) = *(undefined4 *)(&DAT_006aa40c + iVar9);
        *(undefined4 *)(iVar3 + 0x4de) = *(undefined4 *)(&DAT_006aa410 + iVar9);
        iVar9 = *(int *)(iVar3 + 0x44d0);
        *(int *)(iVar3 + 0x44d0) = iVar9 + 0xc;
        *(undefined1 *)(iVar9 + 0x4dc + iVar3) = 1;
        *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 1;
        EncodePacketBody(0,iVar3);
        SendOutgoingPacket(iVar3);
        *(undefined1 *)(param_1 + 0x32f90) = 0;
        InvokeWidget(52,0);
        InvokeWidget(53,0);
        FUN_0040cf30(0);
        FUN_0040cf30(0);
        break;
      }
    }
    FUN_0040cf80(&DAT_00e9c0fc);
    break;
  case 0x36:
    RenderInventoryItemDetail(param_1);
    break;
  case 0x37:
    iVar3 = PeekChecksumStateUnderLock(param_1 + 4);
    uVar4 = (uint)*(ushort *)(param_1 + 0x2e54c + (iVar3 + *(int *)(param_1 + 0x450) * 9) * 2);
    uVar6 = (uint)*(byte *)(param_1 + 0x44c);
    iVar3 = PeekChecksumStateUnderLock(param_1 + 4);
    FUN_004240c0(g_clientContext,
                 *(char *)(*(int *)(param_1 + 0x450) * 9 + 0x2d54c + iVar3 + param_1) == '\x01',
                 uVar6,uVar4);
    iVar3 = DAT_007934e8;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x6011;
    *(undefined4 *)(iVar3 + 0x44d0) = 6;
    QueueOutgoingPacketField(0);
    uVar12 = PeekChecksumStateUnderLock(param_1 + 0x3054c);
    iVar3 = DAT_007934e8;
    *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
    *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
    uVar12 = EncodeChecksumNegate(local_1390,local_2080);
    SUBFIELD(local_4,0,undefined1) = 0xd;
    uVar12 = PeekChecksumStateUnderLock(uVar12);
    iVar3 = DAT_007934e8;
    *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar12;
    *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 4;
    local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
    ScrubChecksumGuard();
    EncodePacketBody(0,iVar3);
    SendOutgoingPacket(iVar3);
    *(undefined1 *)(param_1 + 0x32f90) = 0;
    QueueOutgoingPacketField(0);
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    FUN_0044b720(param_1);
    FUN_00449250(param_1,0,0);
    break;
  case 0x3b:
    *(undefined1 *)(param_1 + 0x32f90) = 1;
    QueueOutgoingPacketField(0);
    RemoveWidget();
    FUN_0044b720(param_1);
    FUN_00449250(param_1,1,0);
    break;
  case 0x3c:
    QueueOutgoingPacketField(0);
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    RemoveWidget();
    FUN_0044b720(param_1);
    FUN_00449250(param_1,1,0);
  case 0x3d:
    BuildSystemInfoBlob(&local_4518, systemInfoBlob2);
    puVar11 = &local_4518;
    pcVar13 = (char *)GetLocalizedString(&g_localizedStringTable,0xea69);
    _sprintf(local_4418,pcVar13,puVar11);
    ShellExecuteA((HWND)0x0,&DAT_00552728,local_4418,(LPCSTR)0x0,(LPCSTR)0x0,1);
    *(undefined1 *)(param_1 + 0x34814) = 1;
  }
switchD_00445591_caseD_2:
  local_4 = 0xffffffff;
  FUN_004254a0();
  *unaff_FS_OFFSET = local_c;
  return;
}

