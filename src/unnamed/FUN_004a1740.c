/* FUN_004a1740 - 0x004a1740 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Removing unreachable block (ram,0x004a1e80) */

undefined4 FUN_004a1740(int param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_1574 [548];
  undefined1 local_1350 [548];
  undefined1 local_112c [548];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [544];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_005396ee;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x4a175f;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar13 = param_1 + 0xf54;
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar7 == 0) {
LAB_004a2741:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x5a);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    iVar7 = *(int *)(&DAT_006a7720 + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar8 == iVar7 + -1) goto LAB_004a2741;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_1 = param_1 + 0x1178;
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar7 == -0x113) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0xb4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else {
      cVar6 = PacketChecksumEquals(param_1,*(int *)(&DAT_006a7724 + g_clientContext) + -1);
      if (cVar6 == '\0') {
        uVar9 = EncodeChecksumDeltaSub(param_1,local_112c,6);
        local_4 = 0;
        PeekChecksumStateUnderLock(uVar9);
        PeekChecksumStateUnderLock(iVar13);
        iVar7 = FUN_004e4340();
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        uVar9 = EncodeChecksumDeltaSub(param_1,local_f08,6);
        local_4 = 1;
        uVar10 = EncodeChecksumDeltaSub(iVar13,local_112c,4);
        SUBFIELD(local_4,0,undefined1) = 2;
        PeekChecksumStateUnderLock(uVar9);
        PeekChecksumStateUnderLock(uVar10);
        iVar8 = FUN_004e4340();
        local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
        ScrubChecksumGuard();
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        uVar9 = EncodeChecksumDeltaSub(param_1,local_112c,6);
        local_4 = 3;
        uVar10 = EncodeChecksumDeltaAdd(iVar13,local_f08,4);
        SUBFIELD(local_4,0,undefined1) = 4;
        PeekChecksumStateUnderLock(uVar9);
        PeekChecksumStateUnderLock(uVar10);
        iVar11 = FUN_004e4340();
        local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
        ScrubChecksumGuard();
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        uVar9 = EncodeChecksumDeltaSub(param_1,local_1574,6);
        local_4 = 5;
        bVar2 = false;
        bVar5 = false;
        bVar4 = false;
        bVar3 = false;
        iVar12 = PeekChecksumStateUnderLock(uVar9);
        if (iVar7 == iVar12) {
LAB_004a1ad6:
          bVar1 = true;
        }
        else {
          uVar9 = EncodeChecksumDeltaAdd(param_1,local_1350,10);
          local_4 = 6;
          bVar2 = true;
          bVar5 = false;
          bVar4 = false;
          bVar3 = false;
          iVar7 = PeekChecksumStateUnderLock(uVar9);
          if (iVar7 < iVar8) goto LAB_004a1ad6;
          uVar9 = EncodeChecksumDeltaAdd(param_1,local_ce4,10);
          local_4 = 7;
          bVar2 = true;
          bVar5 = true;
          bVar4 = false;
          bVar3 = false;
          iVar7 = PeekChecksumStateUnderLock(uVar9);
          if (iVar7 < iVar11) goto LAB_004a1ad6;
          uVar9 = EncodeChecksumDeltaSub(param_1,local_112c,6);
          local_4 = 8;
          bVar2 = true;
          bVar5 = true;
          bVar4 = true;
          bVar3 = false;
          iVar7 = PeekChecksumStateUnderLock(uVar9);
          if (iVar8 == iVar7) goto LAB_004a1ad6;
          uVar9 = EncodeChecksumDeltaSub(param_1,local_f08,6);
          local_4 = 9;
          bVar2 = true;
          bVar5 = true;
          bVar4 = true;
          bVar3 = true;
          iVar7 = PeekChecksumStateUnderLock(uVar9);
          if (iVar11 == iVar7) goto LAB_004a1ad6;
          bVar1 = false;
        }
        local_4 = 8;
        if (bVar3) {
          ScrubChecksumGuard();
        }
        local_4 = 7;
        if (bVar4) {
          ScrubChecksumGuard();
        }
        local_4 = 6;
        if (bVar5) {
          ScrubChecksumGuard();
        }
        local_4 = 5;
        if (bVar2) {
          ScrubChecksumGuard();
        }
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        bVar3 = false;
        if (bVar1) {
          uVar9 = EncodeChecksumDeltaAdd(param_1,local_1574,6);
          local_4 = 10;
          PeekChecksumStateUnderLock(uVar9);
          PeekChecksumStateUnderLock(iVar13);
          iVar7 = FUN_004e4390();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          uVar9 = EncodeChecksumDeltaAdd(param_1,local_1350,6);
          local_4 = 0xb;
          uVar10 = EncodeChecksumDeltaSub(iVar13,local_1574,4);
          SUBFIELD(local_4,0,undefined1) = 0xc;
          PeekChecksumStateUnderLock(uVar9);
          PeekChecksumStateUnderLock(uVar10);
          iVar8 = FUN_004e4390();
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          uVar9 = EncodeChecksumDeltaAdd(param_1,local_1350,6);
          local_4 = 0xd;
          uVar10 = EncodeChecksumDeltaAdd(iVar13,local_1574,4);
          SUBFIELD(local_4,0,undefined1) = 0xe;
          PeekChecksumStateUnderLock(uVar9);
          PeekChecksumStateUnderLock(uVar10);
          iVar11 = FUN_004e4390();
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xd);
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          uVar9 = EncodeChecksumDeltaAdd(param_1,local_112c,6);
          local_4 = 0xf;
          bVar5 = false;
          bVar4 = false;
          iVar12 = PeekChecksumStateUnderLock(uVar9);
          if (iVar7 == iVar12) {
LAB_004a1e19:
            bVar2 = true;
          }
          else {
            uVar9 = EncodeChecksumDeltaSub(param_1,local_f08,10);
            local_4 = 0x10;
            bVar5 = false;
            bVar4 = false;
            bVar3 = true;
            iVar7 = PeekChecksumStateUnderLock(uVar9);
            if (iVar8 < iVar7) goto LAB_004a1e19;
            uVar9 = EncodeChecksumDeltaSub(param_1,local_ce4,10);
            local_4 = 0x11;
            bVar5 = false;
            bVar4 = false;
            bVar3 = true;
            iVar7 = PeekChecksumStateUnderLock(uVar9);
            if (iVar11 < iVar7) goto LAB_004a1e19;
            uVar9 = EncodeChecksumDeltaAdd(param_1,local_1350,6);
            local_4 = 0x12;
            bVar5 = true;
            bVar4 = false;
            bVar3 = true;
            iVar7 = PeekChecksumStateUnderLock(uVar9);
            if (iVar8 == iVar7) goto LAB_004a1e19;
            uVar9 = EncodeChecksumDeltaAdd(param_1,local_1574,6);
            local_4 = 0x13;
            bVar5 = true;
            bVar4 = true;
            bVar3 = true;
            iVar7 = PeekChecksumStateUnderLock(uVar9);
            bVar2 = false;
            if (iVar11 == iVar7) goto LAB_004a1e19;
          }
          local_4 = 0x12;
          if (bVar4) {
            ScrubChecksumGuard();
          }
          local_4 = 0x11;
          if (bVar5) {
            ScrubChecksumGuard();
          }
          local_4 = 0xf;
          if (bVar3) {
            ScrubChecksumGuard();
          }
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          if (bVar2) {
            uVar9 = EncodeChecksumDeltaSub(iVar13,local_1574,6);
            local_4 = 0x14;
            PeekChecksumStateUnderLock(param_1);
            PeekChecksumStateUnderLock(uVar9);
            iVar7 = FUN_004e4410();
            local_4 = 0xffffffff;
            ScrubChecksumGuard();
            uVar9 = EncodeChecksumDeltaSub(param_1,local_1350,4);
            local_4 = 0x15;
            uVar10 = EncodeChecksumDeltaSub(iVar13,local_1574,6);
            SUBFIELD(local_4,0,undefined1) = 0x16;
            PeekChecksumStateUnderLock(uVar9);
            PeekChecksumStateUnderLock(uVar10);
            iVar11 = FUN_004e4410();
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x15);
            ScrubChecksumGuard();
            local_4 = 0xffffffff;
            ScrubChecksumGuard();
            uVar9 = EncodeChecksumDeltaAdd(param_1,local_1350,4);
            local_4 = 0x17;
            uVar10 = EncodeChecksumDeltaSub(iVar13,local_1574,6);
            SUBFIELD(local_4,0,undefined1) = 0x18;
            PeekChecksumStateUnderLock(uVar9);
            PeekChecksumStateUnderLock(uVar10);
            iVar8 = FUN_004e4410();
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x17);
            ScrubChecksumGuard();
            local_4 = 0xffffffff;
            ScrubChecksumGuard();
            uVar9 = EncodeChecksumDeltaSub(iVar13,local_112c,6);
            local_4 = 0x19;
            bVar2 = false;
            bVar5 = false;
            bVar4 = false;
            bVar3 = false;
            iVar12 = PeekChecksumStateUnderLock(uVar9);
            if (iVar7 == iVar12) {
LAB_004a2166:
              bVar1 = true;
            }
            else {
              uVar9 = EncodeChecksumDeltaAdd(iVar13,local_f08,10);
              local_4 = 0x1a;
              bVar2 = true;
              bVar5 = false;
              bVar4 = false;
              bVar3 = false;
              iVar7 = PeekChecksumStateUnderLock(uVar9);
              if (iVar7 < iVar11) goto LAB_004a2166;
              uVar9 = EncodeChecksumDeltaAdd(iVar13,local_ce4,10);
              local_4 = 0x1b;
              bVar2 = true;
              bVar5 = true;
              bVar4 = false;
              bVar3 = false;
              iVar7 = PeekChecksumStateUnderLock(uVar9);
              if (iVar7 < iVar8) goto LAB_004a2166;
              uVar9 = EncodeChecksumDeltaSub(iVar13,local_1350,6);
              local_4 = 0x1c;
              bVar2 = true;
              bVar5 = true;
              bVar4 = true;
              bVar3 = false;
              iVar7 = PeekChecksumStateUnderLock(uVar9);
              if (iVar11 == iVar7) goto LAB_004a2166;
              uVar9 = EncodeChecksumDeltaSub(iVar13,local_1574,6);
              local_4 = 0x1d;
              bVar2 = true;
              bVar5 = true;
              bVar4 = true;
              bVar3 = true;
              iVar7 = PeekChecksumStateUnderLock(uVar9);
              if (iVar8 == iVar7) goto LAB_004a2166;
              bVar1 = false;
            }
            local_4 = 0x1c;
            if (bVar3) {
              ScrubChecksumGuard();
            }
            local_4 = 0x1b;
            if (bVar4) {
              ScrubChecksumGuard();
            }
            local_4 = 0x1a;
            if (bVar5) {
              ScrubChecksumGuard();
            }
            local_4 = 0x19;
            if (bVar2) {
              ScrubChecksumGuard();
            }
            local_4 = 0xffffffff;
            ScrubChecksumGuard();
            if (bVar1) {
              uVar9 = EncodeChecksumDeltaAdd(iVar13,local_1574,6);
              local_4 = 0x1e;
              PeekChecksumStateUnderLock(param_1);
              PeekChecksumStateUnderLock(uVar9);
              iVar7 = FUN_004e43d0();
              local_4 = 0xffffffff;
              ScrubChecksumGuard();
              uVar9 = EncodeChecksumDeltaSub(param_1,local_1350,4);
              local_4 = 0x1f;
              uVar10 = EncodeChecksumDeltaAdd(iVar13,local_1574,6);
              SUBFIELD(local_4,0,undefined1) = 0x20;
              PeekChecksumStateUnderLock(uVar9);
              PeekChecksumStateUnderLock(uVar10);
              iVar11 = FUN_004e43d0();
              local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x1f);
              ScrubChecksumGuard();
              local_4 = 0xffffffff;
              ScrubChecksumGuard();
              uVar9 = EncodeChecksumDeltaAdd(param_1,local_1350,4);
              local_4 = 0x21;
              uVar10 = EncodeChecksumDeltaAdd(iVar13,local_1574,6);
              SUBFIELD(local_4,0,undefined1) = 0x22;
              PeekChecksumStateUnderLock(uVar9);
              PeekChecksumStateUnderLock(uVar10);
              iVar8 = FUN_004e43d0();
              local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x21);
              ScrubChecksumGuard();
              local_4 = 0xffffffff;
              ScrubChecksumGuard();
              uVar9 = EncodeChecksumDeltaAdd(iVar13,local_230,6);
              local_4 = 0x23;
              bVar2 = false;
              bVar5 = false;
              bVar4 = false;
              bVar3 = false;
              iVar12 = PeekChecksumStateUnderLock(uVar9);
              if (iVar7 == iVar12) {
LAB_004a24a3:
                bVar1 = true;
              }
              else {
                uVar9 = EncodeChecksumDeltaSub(iVar13,local_678,10);
                local_4 = 0x24;
                bVar2 = true;
                bVar5 = false;
                bVar4 = false;
                bVar3 = false;
                iVar7 = PeekChecksumStateUnderLock(uVar9);
                if (iVar11 < iVar7) goto LAB_004a24a3;
                uVar9 = EncodeChecksumDeltaSub(iVar13,local_ac0,10);
                local_4 = 0x25;
                bVar2 = true;
                bVar5 = true;
                bVar4 = false;
                bVar3 = false;
                iVar7 = PeekChecksumStateUnderLock(uVar9);
                if (iVar8 < iVar7) goto LAB_004a24a3;
                uVar9 = EncodeChecksumDeltaAdd(iVar13,local_454,6);
                local_4 = 0x26;
                bVar2 = true;
                bVar5 = true;
                bVar4 = true;
                bVar3 = false;
                iVar7 = PeekChecksumStateUnderLock(uVar9);
                if (iVar11 == iVar7) goto LAB_004a24a3;
                uVar9 = EncodeChecksumDeltaAdd(iVar13,local_89c,6);
                local_4 = 0x27;
                bVar2 = true;
                bVar5 = true;
                bVar4 = true;
                bVar3 = true;
                iVar7 = PeekChecksumStateUnderLock(uVar9);
                if (iVar8 == iVar7) goto LAB_004a24a3;
                bVar1 = false;
              }
              local_4 = 0x26;
              if (bVar3) {
                ScrubChecksumGuard();
              }
              local_4 = 0x25;
              if (bVar4) {
                ScrubChecksumGuard();
              }
              local_4 = 0x24;
              if (bVar5) {
                ScrubChecksumGuard();
              }
              local_4 = 0x23;
              if (bVar2) {
                ScrubChecksumGuard();
              }
              local_4 = 0xffffffff;
              ScrubChecksumGuard();
              if (bVar1) {
                uVar9 = 0;
                goto LAB_004a2765;
              }
              if (iVar8 != iVar11) {
                iVar11 = iVar11 - iVar8;
                for (iVar7 = 8;
                    (((iVar11 < -0x7f || (0x80 < iVar11)) || (iVar7 < -0x7f)) || (0x80 < iVar7));
                    iVar7 = iVar7 / 2) {
                  iVar11 = iVar11 / 2;
                }
                QueueOutgoingPacketField
                          ((int)*(short *)(&DAT_00598e7e + (iVar7 * 0x100 + iVar11) * 2));
                goto LAB_004a2763;
              }
            }
            else if (iVar8 != iVar11) {
              iVar11 = iVar11 - iVar8;
              for (iVar7 = 8;
                  ((iVar11 < -0x7f || (0x80 < iVar11)) || ((iVar7 < -0x7f || (0x80 < iVar7))));
                  iVar7 = iVar7 / 2) {
                iVar11 = iVar11 / 2;
              }
              QueueOutgoingPacketField
                        ((int)*(short *)(&DAT_00598e7e + (iVar7 * 0x100 + iVar11) * 2));
              goto LAB_004a2763;
            }
            QueueOutgoingPacketField(0x5a);
          }
          else if (iVar8 == iVar11) {
            QueueOutgoingPacketField(0xb4);
          }
          else {
            iVar7 = 8;
            for (iVar11 = iVar11 - iVar8;
                ((iVar7 < -0x7f || (0x80 < iVar7)) || ((iVar11 < -0x7f || (0x80 < iVar11))));
                iVar11 = iVar11 / 2) {
              iVar7 = iVar7 / 2;
            }
            QueueOutgoingPacketField((int)*(short *)(&DAT_00598e7e + (iVar11 * 0x100 + iVar7) * 2));
          }
        }
        else if (iVar8 == iVar11) {
          QueueOutgoingPacketField(0);
        }
        else {
          iVar7 = 8;
          for (iVar11 = iVar11 - iVar8;
              (((iVar7 < -0x7f || (0x80 < iVar7)) || (iVar11 < -0x7f)) || (0x80 < iVar11));
              iVar11 = iVar11 / 2) {
            iVar7 = iVar7 / 2;
          }
          QueueOutgoingPacketField((int)*(short *)(&DAT_00598e7e + (iVar11 * 0x100 + iVar7) * 2));
        }
      }
      else {
        QueueOutgoingPacketField(0);
      }
    }
  }
LAB_004a2763:
  uVar9 = 1;
LAB_004a2765:
  *unaff_FS_OFFSET = local_c;
  return uVar9;
}

