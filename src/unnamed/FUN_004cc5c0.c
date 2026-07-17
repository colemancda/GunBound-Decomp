/* FUN_004cc5c0 - 0x004cc5c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_004cc5c0(undefined4 param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar8;
  char *pcVar9;
  int local_1358;
  undefined1 local_1350 [548];
  undefined1 local_112c [548];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053bf43;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4cc5df;
  iVar2 = GetPlayerRecordBySlot(g_clientContext);
  if (iVar2 != 0) {
    if (param_2 == '\0') {
      switch(param_3) {
      case 1:
        SetGuardedBool(1);
        break;
      case 2:
        SetGuardedBool(1);
        break;
      case 3:
        uVar6 = EncodeChecksumDeltaMul(iVar2 + 0x6744,local_112c,8);
        local_4 = 3;
        uVar4 = PeekChecksumStateUnderLock(&DAT_00796aa0);
        uVar6 = EncodeChecksumDeltaDiv(uVar6,local_1350,uVar4);
        local_4 = 4;
        EmitChecksumDiff(uVar6);
        local_4 = 3;
        ScrubChecksumGuard();
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        cVar1 = PacketChecksumLessThan(iVar2 + 0x6968,1);
        if (cVar1 != '\0') {
          QueueOutgoingPacketField(1);
        }
        SetGuardedBool(1);
        break;
      case 7:
        cVar1 = PeekPacketChecksumBool();
        iVar7 = iVar2 + 0x6744;
        if (cVar1 == '\0') {
          uVar6 = PeekChecksumStateUnderLock(&DAT_00794bf0);
          uVar6 = EncodeChecksumDeltaMul(iVar7,local_230,uVar6);
          local_4 = 7;
          uVar4 = PeekChecksumStateUnderLock(&DAT_00796aa0);
          uVar6 = EncodeChecksumDeltaDiv(uVar6,local_678,uVar4);
          local_4 = 8;
          EmitChecksumSum(uVar6);
          local_4 = 7;
          ScrubChecksumGuard();
        }
        else {
          uVar6 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
          uVar6 = EncodeChecksumDeltaMul(iVar7,local_ac0,uVar6);
          local_4 = 5;
          uVar4 = PeekChecksumStateUnderLock(&DAT_00796aa0);
          uVar6 = EncodeChecksumDeltaDiv(uVar6,local_f08,uVar4);
          local_4 = 6;
          EmitChecksumSum(uVar6);
          local_4 = 5;
          ScrubChecksumGuard();
        }
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        cVar1 = CompareChecksumExceeds(iVar2 + 0x6968,iVar7);
        if (cVar1 != '\0') {
          EncodeChecksumState(iVar7);
        }
        break;
      case 0xf:
        AddToPacketChecksum(0xb4);
        uVar6 = PeekChecksumStateUnderLock(&DAT_00e9bed8);
        cVar1 = PacketChecksumGreaterThan(g_clientContext + 0x5b1ac,uVar6);
        if (cVar1 != '\0') {
          uVar6 = PeekChecksumStateUnderLock(&DAT_00e9bed8);
          SubFromPacketChecksum(uVar6);
        }
      }
    }
    else {
      switch(param_3) {
      case 1:
        SetGuardedBool(1);
        SetGuardedBool(0);
        break;
      case 2:
        SetGuardedBool(1);
        SetGuardedBool(0);
        break;
      case 6:
        SetGuardedBool(1);
        break;
      case 7:
        cVar1 = PeekPacketChecksumBool();
        iVar7 = iVar2 + 0x6744;
        if (cVar1 == '\0') {
          uVar6 = EncodeChecksumDeltaDiv(iVar7,local_ce4,4);
          local_4 = 2;
          EmitChecksumSum(uVar6);
        }
        else {
          uVar6 = EncodeChecksumDeltaMul(iVar7,local_89c,3);
          local_4 = 0;
          uVar4 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
          uVar6 = EncodeChecksumDeltaDiv(uVar6,local_454,uVar4);
          local_4 = 1;
          EmitChecksumSum(uVar6);
          local_4 = 0;
          ScrubChecksumGuard();
        }
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        cVar1 = CompareChecksumExceeds(iVar2 + 0x6968,iVar7);
        if (cVar1 != '\0') {
          EncodeChecksumState(iVar7);
        }
        break;
      case 10:
        SetGuardedBool(1);
        break;
      case 0xb:
        uVar6 = 10000;
        local_1358 = -1;
        iVar7 = 0;
        do {
          iVar3 = GetPlayerRecordBySlot(g_clientContext);
          if ((((iVar3 != 0) && (*(int *)(iVar3 + 0x24) != 0xe)) &&
              (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
             ((*(char *)(g_clientContext + 0x45122) == '\0' ||
              (*(int *)(iVar3 + 0xae2c) == *(int *)(iVar2 + 0xae2c))))) {
            cVar1 = PacketChecksumLessThan(iVar3 + 0x6968,uVar6);
            if (cVar1 != '\0') {
              uVar6 = PeekChecksumStateUnderLock(iVar3 + 0x6968);
              local_1358 = iVar7;
            }
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 < 8);
        if ((local_1358 != -1) && (iVar7 = GetPlayerRecordBySlot(g_clientContext), iVar2 != iVar7)) {
          iVar3 = iVar2 + 0x90c;
          uVar6 = PeekChecksumStateUnderLock(iVar3);
          iVar5 = iVar7 + 0x90c;
          EncodeChecksumState(iVar5);
          QueueOutgoingPacketField(uVar6);
          iVar2 = iVar2 + 0xb30;
          uVar6 = PeekChecksumStateUnderLock(iVar2);
          EncodeChecksumState(iVar7 + 0xb30);
          QueueOutgoingPacketField(uVar6);
          EncodeChecksumState(iVar3);
          EncodeChecksumState(iVar2);
          EncodeChecksumState(iVar5);
          EncodeChecksumState(iVar7 + 0xb30);
          pcVar9 = s_teleport1_005535f8;
          uVar8 = 0x14b5;
          uVar6 = PeekChecksumStateUnderLock(iVar7 + 0xb30);
          uVar4 = PeekChecksumStateUnderLock(iVar5);
          FUN_004372f0(0,uVar4,uVar6,uVar8,pcVar9);
          pcVar9 = s_teleport1_005535f8;
          uVar8 = 0x14b5;
          uVar6 = PeekChecksumStateUnderLock(iVar2);
          uVar4 = PeekChecksumStateUnderLock(iVar3);
          FUN_004372f0(1,uVar4,uVar6,uVar8,pcVar9);
        }
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

