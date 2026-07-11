/* FUN_0048f300 - 0x0048f300 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined1 FUN_0048f300(int param_1)

{
  int *piVar1;
  undefined1 uVar2;
  uint uVar3;
  char cVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 *unaff_FS_OFFSET;
  int local_249c;
  int local_2498;
  undefined1 local_2492;
  uint local_2490;
  int local_2480 [2];
  undefined1 local_2478 [8];
  undefined1 local_2470 [20];
  int iStack_245c;
  undefined1 local_224c [20];
  int iStack_2238;
  undefined1 local_2028 [20];
  int iStack_2014;
  undefined1 local_1e04 [20];
  int iStack_1df0;
  undefined1 local_1be0 [20];
  int iStack_1bcc;
  undefined1 local_19bc [20];
  int local_19a8;
  undefined1 local_1798 [20];
  int local_1784;
  undefined1 local_1574 [548];
  undefined1 local_1350 [20];
  int local_133c;
  undefined1 local_112c [548];
  undefined1 local_f08 [20];
  int local_ef4;
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 auStack_230 [20];
  int iStack_21c;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  uStack_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_005399d3;
  *unaff_FS_OFFSET = &uStack_c;
  uStack_10 = 0x48f31f;
  local_2492 = 0;
  local_2490 = 0;
  do {
    piVar5 = (int *)GetPlayerRecordBySlot(g_clientContext);
    if ((piVar5 != (int *)0x0) && (cVar4 = PeekPacketChecksumBool(), cVar4 != '\x01')) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 != '\0') {
        iVar6 = iVar6 / 2 + iVar6;
      }
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 != '\0') {
        iVar6 = iVar6 + ((int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2);
      }
      EncodeChecksumPairDiff(param_1 + 0x40,local_1350,piVar5 + 0x243);
      local_4 = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_133c != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540(local_2480);
      }
      EncodeChecksumPairDiff(param_1 + 0x264,local_1798,piVar5 + 0x2cc);
      local_4 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_2480[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_1784 != 0) {
        ScrambleChecksumGuardBytes();
        FUN_0040b540(local_2478);
      }
      if (local_2480[0] * local_2480[0] + iVar7 * iVar7 < iVar6 * iVar6) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_2498 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar7 < iVar6) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 != 1) goto LAB_0048f583;
LAB_0048f5d0:
          local_2498 = -local_2498;
        }
        else {
LAB_0048f583:
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          iVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 < iVar7) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar6 == 0) goto LAB_0048f5d0;
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        cVar4 = PeekPacketChecksumBool();
        if (cVar4 == '\x01') {
          cVar4 = PeekPacketChecksumBool();
          if (cVar4 == '\x01') {
            iVar6 = iVar6 + -4;
          }
          cVar4 = PeekPacketChecksumBool();
          if (cVar4 == '\x01') {
            iVar6 = iVar6 + 4;
          }
        }
        cVar4 = PeekPacketChecksumBool();
        if (cVar4 == '\x01') {
          cVar4 = PeekPacketChecksumBool();
          if (cVar4 == '\x01') {
            iVar6 = iVar6 + -4;
          }
          cVar4 = PeekPacketChecksumBool();
          if (cVar4 == '\x01') {
            iVar6 = iVar6 + 4;
          }
        }
        cVar4 = PeekPacketChecksumBool();
        if (cVar4 == '\x01') {
          cVar4 = PeekPacketChecksumBool();
          if (cVar4 == '\x01') {
            iVar6 = iVar6 + 4;
          }
          cVar4 = PeekPacketChecksumBool();
          if (cVar4 == '\x01') {
            iVar6 = iVar6 + -4;
          }
        }
        uVar8 = EncodeChecksumDeltaMul(g_clientContext + 0x15406c,local_f08,iVar6);
        local_4 = 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar9 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeChecksumDeltaDiv(uVar8,local_19bc,uVar9);
        SUBFIELD(local_4,0,undefined1) = 3;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
        if (local_19a8 != 0) {
          ScrambleChecksumGuardBytes();
          FUN_0040b540(local_2478);
        }
        local_4 = 0xffffffff;
        if (local_ef4 != 0) {
          ScrambleChecksumGuardBytes();
          FUN_0040b540(local_2478);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((iVar7 != 3) && (piVar5[9] != 0xe)) {
          EncodeChecksumDeltaSub(piVar5 + 0x1bf5,local_ac0,iVar6);
          local_4 = 4;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          if (iVar7 < 1) {
            QueueOutgoingPacketField(0);
          }
          else {
            QueueOutgoingPacketField(iVar7);
            iVar7 = 0;
          }
          AddToPacketChecksum(iVar7);
          iVar7 = piVar5[0x2c2a];
          piVar5[0x2c2a] = iVar7 + 1;
          EncodeChecksumDeltaSub(piVar5 + 0x2cc,local_678,iVar7 * 0xf);
          local_4 = 5;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar9 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436860(uVar9,uVar8);
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          *(undefined1 *)(piVar5 + 0x2c2b) = *(undefined1 *)(param_1 + 0x3c);
          if (*(byte *)(param_1 + 0x3c) < 8) {
            if (*(char *)(*(byte *)(param_1 + 0x3c) + 0x4590c + g_clientContext) ==
                *(char *)((piVar5[2] & 7U) + 0x4590c + g_clientContext)) {
              *(int *)(g_clientContext + 0x5b83c + (uint)*(byte *)(param_1 + 0x3c) * 4) =
                   *(int *)(g_clientContext + 0x5b83c + (uint)*(byte *)(param_1 + 0x3c) * 4) + iVar6;
              *(undefined1 *)(piVar5 + 0x2c2d) = 1;
            }
            else {
              piVar1 = (int *)(g_clientContext + 0x5b81c + (uint)*(byte *)(param_1 + 0x3c) * 4);
              *piVar1 = *piVar1 + iVar6;
            }
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (local_2498 <= iVar6) {
          local_2492 = 1;
          piVar5[0x2ff7] = piVar5[0x2ff7] + local_2498 * -3 + 200;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 < piVar5[0x2ff7]) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = piVar5[0x2ff7] / iVar6;
            cVar4 = FUN_0040b410(param_1 + 0x40,piVar5 + 0x243);
            if (cVar4 == '\0') {
              uVar8 = EncodeChecksumDeltaSub(piVar5 + 0x2cc,local_224c,0x1e);
              local_4 = 0xb;
              uVar9 = EncodeChecksumDeltaDiv(piVar5 + 0x355,local_2028,2);
              SUBFIELD(local_4,0,undefined1) = 0xc;
              uVar9 = EncodeChecksumPairSum(piVar5 + 0x243,local_1e04,uVar9);
              SUBFIELD(local_4,0,undefined1) = 0xd;
              local_2480[0] = EncodeChecksumDeltaSub(piVar5 + 0x2cc,local_1be0,0x1e);
              SUBFIELD(local_4,0,undefined1) = 0xe;
              PeekChecksumStateUnderLock(uVar8);
              PeekChecksumStateUnderLock(uVar9);
              iVar7 = FindGroundHeightAtColumn();
              iVar10 = PeekChecksumStateUnderLock(local_2480[0]);
              SUBFIELD(local_4,0,undefined1) = 0xd;
              ScrubChecksumGuard();
              SUBFIELD(local_4,0,undefined1) = 0xc;
              ScrubChecksumGuard();
              local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
              ScrubChecksumGuard();
              local_4 = 0xffffffff;
              ScrubChecksumGuard();
              if (iVar10 < iVar7) {
                AddToPacketChecksum(iVar6);
              }
              uVar8 = EncodeChecksumDeltaAdd(piVar5 + 0x2cc,local_2470,0x14);
              local_4 = 0xf;
              iVar7 = (**(code **)(*piVar5 + 0x14))();
              iVar10 = PeekChecksumStateUnderLock(uVar8);
              local_4 = 0xffffffff;
              ScrubChecksumGuard();
              if (iVar10 < iVar7) {
                SubFromPacketChecksum(iVar6);
              }
            }
            else {
              uVar8 = EncodeChecksumDeltaSub(piVar5 + 0x2cc,local_89c,0x1e);
              local_4 = 6;
              uVar9 = EncodeChecksumDeltaDiv(piVar5 + 0x355,local_112c,2);
              SUBFIELD(local_4,0,undefined1) = 7;
              uVar9 = EncodeChecksumPairDiff(piVar5 + 0x243,local_454,uVar9);
              SUBFIELD(local_4,0,undefined1) = 8;
              local_2480[0] = EncodeChecksumDeltaSub(piVar5 + 0x2cc,local_1574,0x1e);
              SUBFIELD(local_4,0,undefined1) = 9;
              PeekChecksumStateUnderLock(uVar8);
              PeekChecksumStateUnderLock(uVar9);
              iVar7 = FindGroundHeightAtColumn();
              iVar10 = PeekChecksumStateUnderLock(local_2480[0]);
              SUBFIELD(local_4,0,undefined1) = 8;
              ScrubChecksumGuard();
              SUBFIELD(local_4,0,undefined1) = 7;
              ScrubChecksumGuard();
              local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),6);
              ScrubChecksumGuard();
              local_4 = 0xffffffff;
              ScrubChecksumGuard();
              if (iVar10 < iVar7) {
                SubFromPacketChecksum(iVar6);
                uVar8 = EncodeChecksumDeltaAdd(piVar5 + 0x2cc,local_ce4,0x14);
                local_4 = 10;
                iVar7 = (**(code **)(*piVar5 + 0x14))();
                iVar10 = PeekChecksumStateUnderLock(uVar8);
                local_4 = 0xffffffff;
                ScrubChecksumGuard();
                if (iVar10 < iVar7) {
                  AddToPacketChecksum(iVar6);
                }
              }
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            piVar5[0x2ff7] = piVar5[0x2ff7] % iVar6;
            EncodeChecksumState(piVar5 + 0x243);
            *(undefined1 *)(piVar5 + 0x2c2b) = *(undefined1 *)(param_1 + 0x3c);
          }
        }
      }
    }
    local_2490 = local_2490 + 1;
    if (7 < (int)local_2490) {
      iVar6 = param_1 + 0x33c8;
      FUN_0040ada0(iVar6,local_2470,iVar6);
      local_4 = 0x10;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (iStack_245c != 0) {
        iVar10 = iStack_245c << 4;
        local_2498 = 0x10;
        do {
          iVar11 = _rand();
          *(char *)(iVar10 + DAT_0079376c) = (char)iVar11;
          iVar10 = iVar10 + 1;
          local_2498 = local_2498 + -1;
        } while (local_2498 != 0);
        FUN_0040b540(local_2478);
      }
      local_2490 = 0;
      do {
        iVar10 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
        uVar3 = *(uint *)(iVar10 + 4);
        while (uVar3 < 0x186a4) {
          if (uVar3 == 0x186a3) {
            piVar5 = *(int **)(iVar10 + 0x10);
            uVar3 = piVar5[2];
            if (uVar3 <= local_2490) goto LAB_0048fe95;
            break;
          }
          iVar10 = *(int *)(iVar10 + 0x1c);
          uVar3 = *(uint *)(iVar10 + 4);
        }
LAB_0049008d:
        local_2490 = local_2490 + 1;
      } while ((int)local_2490 < 0x40);
      FUN_0040ada0(iVar6,local_2470,iVar6);
      local_4 = 0x13;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (iStack_245c != 0) {
        iVar7 = iStack_245c << 4;
        iVar10 = 0x10;
        do {
          iVar11 = _rand();
          *(char *)(iVar7 + DAT_0079376c) = (char)iVar11;
          iVar7 = iVar7 + 1;
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
        FUN_0040b540(local_2478);
      }
      local_2490 = 0;
      do {
        iVar7 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
        uVar3 = *(uint *)(iVar7 + 4);
        while (uVar3 < 0x186a7) {
          if (uVar3 == 0x186a6) {
            iVar7 = *(int *)(iVar7 + 0x10);
            uVar3 = *(uint *)(iVar7 + 8);
            if (uVar3 <= local_2490) goto LAB_00490184;
            break;
          }
          iVar7 = *(int *)(iVar7 + 0x1c);
          uVar3 = *(uint *)(iVar7 + 4);
        }
LAB_00490747:
        local_2490 = local_2490 + 1;
        if (7 < (int)local_2490) {
          *unaff_FS_OFFSET = uStack_c;
          return local_2492;
        }
      } while( true );
    }
  } while( true );
LAB_0048fe95:
  if (uVar3 != local_2490) goto code_r0x0048fe97;
  EncodeChecksumPairDiff(param_1 + 0x40,local_224c,piVar5 + 0x10);
  local_4 = 0x11;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (iStack_2238 != 0) {
    iVar11 = iStack_2238 << 4;
    local_2498 = 0x10;
    do {
      iVar12 = _rand();
      *(char *)(iVar11 + DAT_0079376c) = (char)iVar12;
      iVar11 = iVar11 + 1;
      local_2498 = local_2498 + -1;
    } while (local_2498 != 0);
    FUN_0040b540(local_2478);
  }
  EncodeChecksumPairDiff(param_1 + 0x264,local_2028,piVar5 + 0x99);
  local_4 = 0x12;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar11 = PeekPacketChecksumState();
  local_2480[0] = iVar11;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (iStack_2014 != 0) {
    iVar11 = iStack_2014 << 4;
    local_2498 = 0x10;
    do {
      iVar12 = _rand();
      *(char *)(iVar11 + DAT_0079376c) = (char)iVar12;
      iVar11 = iVar11 + 1;
      local_2498 = local_2498 + -1;
    } while (local_2498 != 0);
    FUN_0040b540(local_2478);
    iVar11 = local_2480[0];
  }
  if (iVar10 * iVar10 + iVar11 * iVar11 < iVar7) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState();
    iVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar10 <= iVar11) || (piVar5[0xfea] != 0)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    (**(code **)(*piVar5 + 0x20))();
  }
  goto LAB_0049008d;
code_r0x0048fe97:
  piVar5 = (int *)piVar5[4];
  uVar3 = piVar5[2];
  if (local_2490 < uVar3) goto LAB_0049008d;
  goto LAB_0048fe95;
LAB_00490184:
  if (uVar3 != local_2490) goto code_r0x00490186;
  EncodeChecksumPairDiff(param_1 + 0x40,local_224c,iVar7 + 0x25c);
  local_4 = 0x14;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_2480[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (iStack_2238 != 0) {
    iVar10 = iStack_2238 << 4;
    local_2498 = 0x10;
    do {
      iVar11 = _rand();
      *(char *)(iVar10 + DAT_0079376c) = (char)iVar11;
      iVar10 = iVar10 + 1;
      local_2498 = local_2498 + -1;
    } while (local_2498 != 0);
    FUN_0040b540(local_2478);
  }
  EncodeChecksumPairDiff(param_1 + 0x264,local_2028,iVar7 + 0x480);
  local_4 = 0x15;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (iStack_2014 != 0) {
    iVar11 = iStack_2014 << 4;
    local_2498 = 0x10;
    do {
      iVar12 = _rand();
      *(char *)(iVar11 + DAT_0079376c) = (char)iVar12;
      iVar11 = iVar11 + 1;
      local_2498 = local_2498 + -1;
    } while (local_2498 != 0);
    FUN_0040b540(local_2478);
  }
  if (local_2480[0] * local_2480[0] + iVar10 * iVar10 < iVar6) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = *(undefined1 *)(param_1 + 0x3c);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar12 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar12 + iVar10);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = *(int *)(iVar7 + 0xaec);
    *(int *)(iVar7 + 0xaec) = iVar10 + 1;
    EncodeChecksumDeltaSub(iVar7 + 0x480,local_1e04,iVar10 * 0xf);
    local_4 = 0x16;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_2480[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436860(local_2480[0],uVar8);
    local_4 = 0xffffffff;
    if (iStack_1df0 != 0) {
      iVar10 = iStack_1df0 << 4;
      local_2498 = 0x10;
      do {
        iVar12 = _rand();
        *(char *)(iVar10 + DAT_0079376c) = (char)iVar12;
        iVar10 = iVar10 + 1;
        local_2498 = local_2498 + -1;
      } while (local_2498 != 0);
      FUN_0040b540(local_2478);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar11 <= iVar10) {
      local_2492 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar10 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(iVar10 + (100 - iVar11) * 2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar10 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar11 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar10 < iVar11) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar10 = PeekPacketChecksumState();
        iVar11 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar8 = PeekPacketChecksumState();
        if (iVar10 < iVar11) {
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeChecksumDeltaDiv(iVar7 + 0x15ac,local_1be0,uVar8);
          local_4 = 0x17;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState();
          iVar10 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar10 + iVar7);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 0xffffffff;
          if (iStack_1bcc != 0) {
            iVar7 = iStack_1bcc << 4;
            local_249c = 0x10;
            do {
              iVar10 = _rand();
              *(char *)(iVar7 + DAT_0079376c) = (char)iVar10;
              iVar7 = iVar7 + 1;
              local_249c = local_249c + -1;
            } while (local_249c != 0);
LAB_004906f3:
            FUN_0040b540(local_2478);
          }
        }
        else {
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeChecksumDeltaDiv(iVar7 + 0x15ac,auStack_230,uVar8);
          local_4 = 0x18;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState();
          iVar10 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar7 - iVar10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 0xffffffff;
          if (iStack_21c != 0) {
            iVar7 = iStack_21c << 4;
            local_249c = 0x10;
            do {
              iVar10 = _rand();
              *(char *)(iVar7 + DAT_0079376c) = (char)iVar10;
              iVar7 = iVar7 + 1;
              local_249c = local_249c + -1;
            } while (local_249c != 0);
            goto LAB_004906f3;
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar10 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(iVar10 % iVar7);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
    }
  }
  goto LAB_00490747;
code_r0x00490186:
  iVar7 = *(int *)(iVar7 + 0x10);
  uVar3 = *(uint *)(iVar7 + 8);
  if (local_2490 < uVar3) goto LAB_00490747;
  goto LAB_00490184;
}

