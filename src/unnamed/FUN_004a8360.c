/* FUN_004a8360 - 0x004a8360 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004a8360(int *param_1)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  byte *pbVar9;
  int iVar10;
  byte *pbVar11;
  char *pcVar12;
  int *piVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  undefined4 *unaff_FS_OFFSET;
  bool bVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  char cStack_b15;
  int iStack_b14;
  byte *local_b10;
  int local_b0c;
  byte *pbStack_b08;
  byte *apbStack_b04 [2];
  byte *pbStack_afc;
  byte *pbStack_af8;
  int *piStack_af4;
  int *local_af0;
  int *piStack_aec;
  int *piStack_ae8;
  int *apiStack_ae4 [2];
  undefined1 auStack_adc [20];
  byte *pbStack_ac8;
  undefined1 uStack_8bc;
  undefined1 auStack_8b4 [20];
  byte *pbStack_8a0;
  undefined1 uStack_694;
  undefined1 auStack_688 [20];
  byte *pbStack_674;
  undefined1 auStack_464 [548];
  undefined1 auStack_240 [552];
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  undefined4 uStack_c;
  
  uStack_c = 0xffffffff;
  puStack_10 = &LAB_0053e757;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  local_b10 = (byte *)0x0;
  local_af0 = param_1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  iVar7 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar7 + iVar6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_b0c = PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar6 + local_b0c);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 == '\0') {
    FUN_0040b180(param_1 + 0x10,auStack_688,8);
    puStack_10 = (undefined1 *)0x11;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pbVar9 = pbStack_674;
    puStack_10 = (undefined1 *)0xffffffff;
    if (pbStack_674 != (byte *)0x0) {
      ScrambleChecksumGuardBytes();
      apbStack_b04[0] = pbVar9;
      FUN_0040b540(&local_b10);
      param_1 = piStack_af4;
    }
    FUN_0040b180(param_1 + 0x99,auStack_688,8);
    piStack_aec = param_1 + 0x45e;
    puStack_10 = (undefined1 *)0x12;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_10 = (undefined1 *)0xffffffff;
    if (pbStack_674 != (byte *)0x0) {
      ScrambleChecksumGuardBytes();
      apbStack_b04[0] = pbStack_674;
      FUN_0040b540(&local_b10);
      param_1 = piStack_af4;
    }
    cVar4 = FUN_00406610(param_1[0x3d2] != 0);
    if (cVar4 == '\0') {
      FUN_0040afb0(param_1 + 0x2bd);
      FUN_0040afb0(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      apbStack_b04[0] = (byte *)PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((int)(((uint)apbStack_b04[0] ^ (int)apbStack_b04[0] >> 0x1f) -
               ((int)apbStack_b04[0] >> 0x1f)) < 200) {
        cVar4 = FUN_0040b330(param_1 + 0x122,0);
        if (cVar4 == '\0') {
          uVar8 = 200;
        }
        else {
          uVar8 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar8);
      }
      uVar8 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_464,4);
      puStack_10 = (undefined1 *)0x13;
      uVar8 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_8b4,uVar8);
      puStack_10 = (undefined1 *)0x14;
      bVar3 = false;
      bVar18 = false;
      cVar4 = FUN_0040b490(param_1 + 0x3d5,uVar8);
      if (cVar4 == '\0') {
        uVar8 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_adc,4);
        puStack_10 = (undefined1 *)0x15;
        uVar8 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,auStack_688,uVar8);
        puStack_10 = (undefined1 *)0x16;
        bVar3 = true;
        bVar18 = true;
        cVar4 = FUN_0040b490(uVar8,param_1 + 0x3d5);
        bVar2 = false;
        if (cVar4 != '\0') goto LAB_004aa132;
      }
      else {
LAB_004aa132:
        bVar2 = true;
      }
      puStack_10 = (undefined1 *)0x15;
      if (bVar18) {
        ScrubChecksumGuard();
      }
      puStack_10 = (undefined1 *)0x14;
      if (bVar3) {
        ScrubChecksumGuard();
      }
      puStack_10 = (undefined1 *)0x13;
      ScrubChecksumGuard();
      puStack_10 = (undefined1 *)0xffffffff;
      ScrubChecksumGuard();
      if (bVar2) {
        iVar6 = param_1[0x3d4];
        param_1[0x3d4] = iVar6 + 1;
        if (iVar6 + 1 < 3) {
          uVar8 = FUN_0040a500(param_1 + 0x122,auStack_240);
          puStack_10 = (undefined1 *)0x17;
          EncodeChecksumState(uVar8);
          puStack_10 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          FUN_00406500(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_b10 = (byte *)(param_1 + 0x3d5);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 < 0) {
LAB_004aa2ed:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar4 = PeekPacketChecksumBool();
      if ((cVar4 != '\0') && (cVar4 = FUN_0043a530(), cVar4 == '\0')) {
        iVar6 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar6 == 5) || (uVar8 = 2, iVar6 == 6)) {
          uVar8 = 0x19;
        }
        QueueOutgoingPacketField(uVar8);
      }
    }
    else {
      apbStack_b04[0] = *(byte **)(&DAT_006a7720 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      bVar18 = (int)apbStack_b04[0] <= iVar6;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      piVar13 = piStack_aec;
      if (((bVar18) ||
          (cVar4 = FUN_0040b300(piStack_aec,*(undefined4 *)(&DAT_006a7724 + g_clientContext)),
          cVar4 != '\0')) || (cVar4 = FUN_0040b330(piVar13,0xfffffc18), cVar4 != '\0'))
      goto LAB_004aa2ed;
    }
    cVar4 = FUN_00406710();
    if (cVar4 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar10 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = g_clientContext;
      piVar13 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar4 = PeekPacketChecksumBool();
      if ((cVar4 == '\0') && ((&DAT_006a7758)[iVar6] != '\0')) {
        if (((&DAT_006a7736)[iVar6] == '\x01') &&
           ((uVar15 = iVar7 - *(int *)(&DAT_006a7714 + iVar6) >> 0x1f,
            200 < (int)((iVar7 - *(int *)(&DAT_006a7714 + iVar6) ^ uVar15) - uVar15) ||
            (uVar15 = iVar10 - *(int *)(&DAT_006a7710 + iVar6) >> 0x1f,
            300 < (int)((iVar10 - *(int *)(&DAT_006a7710 + iVar6) ^ uVar15) - uVar15))))) {
          (&DAT_006a7736)[iVar6] = 0;
        }
        iVar14 = 400;
        if (399 < iVar10) {
          iVar14 = iVar10;
        }
        iVar16 = *(int *)(&DAT_006a7720 + iVar6) + -400;
        if ((iVar14 <= iVar16) && (iVar16 = iVar10, iVar10 < 400)) {
          iVar16 = 400;
        }
        iVar10 = -0x14;
        if (-0x15 < iVar7) {
          iVar10 = iVar7;
        }
        iVar14 = *(int *)(&DAT_006a7724 + iVar6) + -0x104;
        if ((iVar10 <= iVar14) && (iVar14 = -0x14, -0x15 < iVar7)) {
          iVar14 = iVar7;
        }
        iVar7 = *piVar13 - iVar16;
        *(int *)(&DAT_006a771c + iVar6) = iVar14;
        if (((*(int *)(&DAT_006a770c + iVar6) - iVar14) * (*(int *)(&DAT_006a770c + iVar6) - iVar14)
             + iVar7 * iVar7 < 40000) &&
           (((&DAT_006a7734)[iVar6] == '\x01' || ((&DAT_006a7f6c)[iVar6] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar6) = iVar16;
          *piVar13 = iVar16;
          *(int *)(&DAT_006a7714 + iVar6) = iVar14;
          *(int *)(&DAT_006a770c + iVar6) = iVar14;
        }
        if ((((&DAT_006a7734)[iVar6] == '\0') && ((&DAT_006a7f6c)[iVar6] == '\x01')) &&
           ((&DAT_006a7736)[iVar6] == '\0')) {
          iVar7 = *(int *)(&DAT_006a7730 + iVar6);
          iVar10 = iVar7;
          if (iVar16 <= iVar7) {
            iVar10 = iVar16;
          }
          iVar17 = *(int *)(&DAT_006a772c + iVar6);
          if ((iVar17 <= iVar10) && (iVar17 = iVar7, iVar16 <= iVar7)) {
            iVar17 = iVar16;
          }
          *(int *)(&DAT_006a7718 + iVar6) = iVar17;
        }
        if ((&DAT_006a7734)[iVar6] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar6) = iVar16;
          *(int *)(&DAT_006a771c + iVar6) = iVar14;
        }
      }
    }
    goto LAB_004aa4ab;
  }
  piStack_aec = param_1 + 0x45e;
  FUN_004262d0(param_1[2],piStack_aec);
  *(undefined1 *)(param_1 + 5) = 1;
  EncodeChecksumPairDiff(param_1 + 0x3d5,auStack_adc,piStack_aec);
  puStack_10 = (undefined1 *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_10 = (undefined1 *)0xffffffff;
  local_b10 = pbStack_ac8;
  if (pbStack_ac8 != (byte *)0x0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(apbStack_b04);
    param_1 = piStack_af4;
  }
  iVar7 = 0;
  iStack_b14 = 0;
  if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
    do {
      if (((-1 < iVar6) && (iVar6 < *(int *)(&DAT_006a7720 + g_clientContext))) &&
         ((-1 < iVar7 &&
          ((iVar7 < *(int *)(&DAT_006a7724 + g_clientContext) &&
           (*(char *)(*(int *)(&DAT_006a7720 + g_clientContext) * iVar7 +
                      *(int *)(&DAT_006a773c + g_clientContext) + iVar6) != '\0')))))) {
        FUN_00436150(&DAT_006a7f70 + g_clientContext,iVar6,iVar7,0);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_b10 = (byte *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar15 = (uint)*(byte *)(param_1 + 0xfe4);
        uVar20 = 0;
        uVar19 = 1;
        uVar8 = 0;
        pbVar9 = local_b10;
        PeekPacketChecksumBool(0,local_b10,uVar15,1,0);
        FUN_00431d90((char)param_1[0xf],7,1,uVar8,pbVar9,uVar15,uVar19,uVar20);
        pbStack_afc = (byte *)(param_1 + 0xc66);
        uVar8 = FUN_0040a500(pbStack_afc,auStack_688);
        puStack_10 = (undefined1 *)0x1;
        pbStack_af8 = (byte *)FUN_0040a7d0(uVar8,auStack_8b4,7);
        SUBFIELD(puStack_10,0,undefined1) = 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_b10 = (byte *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_b10 = (byte *)EncodeChecksumDeltaDiv(pbStack_af8,auStack_adc,local_b10);
        SUBFIELD(puStack_10,0,undefined1) = 3;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        piStack_ae8 = param_1 + 0xd7b;
        pbStack_af8 = (byte *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        apiStack_ae4[0] = param_1 + 0xcf2;
        local_af0 = (int *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        pbStack_b08 = (byte *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_b10 = (byte *)PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_0043af40(iVar6,iVar7,local_b10,pbStack_b08,local_af0,pbStack_af8,(char)param_1[0xf]);
        SUBFIELD(puStack_10,0,undefined1) = 2;
        local_b10 = pbStack_ac8;
        if (pbStack_ac8 != (byte *)0x0) {
          ScrambleChecksumGuardBytes();
          FUN_0040b540(apbStack_b04);
          param_1 = piStack_af4;
        }
        puStack_10 = (undefined1 *)CONCAT31(SUBFIELD(puStack_10,1,undefined3),1);
        local_b10 = pbStack_8a0;
        if (pbStack_8a0 != (byte *)0x0) {
          ScrambleChecksumGuardBytes();
          FUN_0040b540(apbStack_b04);
          param_1 = piStack_af4;
        }
        puStack_10 = (undefined1 *)0xffffffff;
        local_b10 = pbStack_674;
        if (pbStack_674 != (byte *)0x0) {
          ScrambleChecksumGuardBytes();
          FUN_0040b540(apbStack_b04);
          param_1 = piStack_af4;
        }
        cVar4 = PeekPacketChecksumBool();
        pbVar9 = local_b10;
        if (cVar4 != '\0') {
          local_b10 = &DAT_006a7708 + g_clientContext;
          cVar4 = PeekPacketChecksumBool();
          pbVar9 = local_b10;
          if ((cVar4 == '\0') && (local_b10[0x50] != 0)) {
            if ((local_b10[0x2e] == 1) &&
               ((uVar15 = iVar7 - *(int *)(local_b10 + 0xc) >> 0x1f,
                200 < (int)((iVar7 - *(int *)(local_b10 + 0xc) ^ uVar15) - uVar15) ||
                (uVar15 = iVar6 - *(int *)(local_b10 + 8) >> 0x1f,
                300 < (int)((iVar6 - *(int *)(local_b10 + 8) ^ uVar15) - uVar15))))) {
              local_b10[0x2e] = 0;
            }
            iVar10 = 400;
            if (399 < iVar6) {
              iVar10 = iVar6;
            }
            iVar14 = *(int *)(local_b10 + 0x18) + -400;
            if ((iVar10 <= iVar14) && (iVar14 = iVar6, iVar6 < 400)) {
              iVar14 = 400;
            }
            iVar6 = iVar7;
            if (iVar7 < -0x14) {
              iVar6 = -0x14;
            }
            iVar10 = *(int *)(local_b10 + 0x1c) + -0x104;
            if ((iVar6 <= *(int *)(local_b10 + 0x1c) + -0x104) && (iVar10 = iVar7, iVar7 < -0x14)) {
              iVar10 = -0x14;
            }
            *(int *)(local_b10 + 0x14) = iVar10;
            pbVar9 = (byte *)(*(int *)local_b10 - iVar14);
            if (((*(int *)(local_b10 + 4) - iVar10) * (*(int *)(local_b10 + 4) - iVar10) +
                 (int)pbVar9 * (int)pbVar9 < 40000) &&
               ((local_b10[0x2c] == 1 || (local_b10[0x864] == 0)))) {
              *(int *)(local_b10 + 8) = iVar14;
              *(int *)local_b10 = iVar14;
              *(int *)(local_b10 + 0xc) = iVar10;
              *(int *)(local_b10 + 4) = iVar10;
            }
            if (((local_b10[0x2c] == 0) && (local_b10[0x864] == 1)) && (local_b10[0x2e] == 0)) {
              iVar6 = *(int *)(local_b10 + 0x28);
              if (iVar14 <= *(int *)(local_b10 + 0x28)) {
                iVar6 = iVar14;
              }
              iVar7 = *(int *)(local_b10 + 0x24);
              if ((*(int *)(local_b10 + 0x24) <= iVar6) &&
                 (iVar7 = *(int *)(local_b10 + 0x28), iVar14 <= *(int *)(local_b10 + 0x28))) {
                iVar7 = iVar14;
              }
              *(int *)(local_b10 + 0x10) = iVar7;
            }
            if (local_b10[0x2c] == 1) {
              *(int *)(local_b10 + 0x10) = iVar14;
              *(int *)(local_b10 + 0x14) = iVar10;
            }
          }
        }
        goto LAB_004a86e6;
      }
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 1;
      iStack_b14 = iVar7;
    } while (iVar7 < *(int *)(&DAT_006a7724 + g_clientContext));
  }
  FUN_00436150(&DAT_006a7f70 + g_clientContext,iVar6,iStack_b14,0);
  pbStack_afc = (byte *)(param_1 + 0xc66);
  uVar8 = FUN_0040a500(pbStack_afc,auStack_8b4);
  puStack_10 = (undefined1 *)0x4;
  pbStack_af8 = (byte *)FUN_0040a7d0(uVar8,auStack_adc,7);
  SUBFIELD(puStack_10,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_b10 = (byte *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_b10 = (byte *)EncodeChecksumDeltaDiv(pbStack_af8,auStack_688,local_b10);
  SUBFIELD(puStack_10,0,undefined1) = 6;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piStack_ae8 = param_1 + 0xd7b;
  pbStack_af8 = (byte *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apiStack_ae4[0] = param_1 + 0xcf2;
  local_af0 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pbStack_b08 = (byte *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_b10 = (byte *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0043af40(iVar6,iStack_b14,local_b10,pbStack_b08,local_af0,pbStack_af8,(char)param_1[0xf]);
  pbVar9 = pbStack_674;
  SUBFIELD(puStack_10,0,undefined1) = 5;
  if (pbStack_674 != (byte *)0x0) {
    ScrambleChecksumGuardBytes();
    local_b10 = pbVar9;
    FUN_0040b540(apbStack_b04);
    param_1 = piStack_af4;
  }
  pbVar9 = pbStack_ac8;
  puStack_10 = (undefined1 *)CONCAT31(SUBFIELD(puStack_10,1,undefined3),4);
  if (pbStack_ac8 != (byte *)0x0) {
    ScrambleChecksumGuardBytes();
    local_b10 = pbVar9;
    FUN_0040b540(apbStack_b04);
    param_1 = piStack_af4;
  }
  pbVar11 = pbStack_8a0;
  puStack_10 = (undefined1 *)0xffffffff;
  pbVar9 = local_b10;
  if (pbStack_8a0 != (byte *)0x0) {
    ScrambleChecksumGuardBytes();
    local_b10 = pbVar11;
    FUN_0040b540(apbStack_b04);
    param_1 = piStack_af4;
    pbVar9 = local_b10;
  }
LAB_004a86e6:
  local_b10 = pbVar9;
  EncodeChecksumPairSum(param_1 + 0x3d5,auStack_688,piStack_aec);
  puStack_10 = (undefined1 *)0x7;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pbVar9 = (byte *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puStack_10 = (undefined1 *)0xffffffff;
  local_b10 = pbStack_674;
  if (pbStack_674 != (byte *)0x0) {
    iVar6 = (int)pbStack_674 << 4;
    pbStack_b08 = (byte *)0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar7;
      iVar6 = iVar6 + 1;
      pbStack_b08 = (byte *)((int)pbStack_b08 + -1);
    } while (pbStack_b08 != (byte *)0x0);
    FUN_0040b540(apbStack_b04);
    param_1 = piStack_af4;
  }
  local_b10 = *(byte **)(&DAT_006a7724 + g_clientContext);
  iVar6 = 0;
  iStack_b14 = 0;
  if (0 < (int)local_b10) {
LAB_004a87b1:
    if ((((int)pbVar9 < 0) || (*(int *)(&DAT_006a7720 + g_clientContext) <= (int)pbVar9)) ||
       ((iVar6 < 0 ||
        ((*(int *)(&DAT_006a7724 + g_clientContext) <= iVar6 ||
         (pbVar9[*(int *)(&DAT_006a7720 + g_clientContext) * iVar6 +
                 *(int *)(&DAT_006a773c + g_clientContext)] == 0)))))) goto LAB_004a87de;
    FUN_00436150(&DAT_006a7f70 + g_clientContext,pbVar9,iVar6,1);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_b10 = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((char)((char)param_1[0x3cf] + *(char *)((int)param_1 + 0xf3d) + -0x34) !=
        *(char *)((int)param_1 + 0xf3e)) {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00431d90((char)param_1[0xf],7,1,0,local_b10,(char)param_1[0xfe4],1,0);
    pbStack_af8 = (byte *)FUN_0040a7d0(pbStack_afc,auStack_adc,7);
    puStack_10 = (undefined1 *)0x8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_b10 = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_b10 = (byte *)EncodeChecksumDeltaDiv(pbStack_af8,auStack_688,local_b10);
    SUBFIELD(puStack_10,0,undefined1) = 9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pbStack_af8 = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_af0 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pbStack_b08 = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_b10 = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(pbVar9,iVar6,local_b10,pbStack_b08,local_af0,pbStack_af8,(char)param_1[0xf]);
    puStack_10 = (undefined1 *)CONCAT31(SUBFIELD(puStack_10,1,undefined3),8);
    local_b10 = pbStack_674;
    if (pbStack_674 != (byte *)0x0) {
      iVar7 = (int)pbStack_674 << 4;
      pbStack_b08 = (byte *)0x10;
      do {
        iVar10 = _rand();
        *(char *)(iVar7 + DAT_0079376c) = (char)iVar10;
        iVar7 = iVar7 + 1;
        pbStack_b08 = pbStack_b08 + -1;
      } while (pbStack_b08 != (byte *)0x0);
      FUN_0040b540(apbStack_b04);
      param_1 = piStack_af4;
    }
    puStack_10 = (undefined1 *)0xffffffff;
    local_b10 = pbStack_ac8;
    if (pbStack_ac8 != (byte *)0x0) {
      iVar7 = (int)pbStack_ac8 << 4;
      pbStack_b08 = (byte *)0x10;
      do {
        iVar10 = _rand();
        *(char *)(iVar7 + DAT_0079376c) = (char)iVar10;
        iVar7 = iVar7 + 1;
        pbStack_b08 = pbStack_b08 + -1;
      } while (pbStack_b08 != (byte *)0x0);
      FUN_0040b540(apbStack_b04);
      param_1 = piStack_af4;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    bVar1 = *(byte *)((int)param_1 + 0xf3f);
    bVar5 = *(byte *)(param_1 + 0x3d0);
    bVar18 = (byte)(bVar1 + bVar5 + -0x34) == *(char *)((int)param_1 + 0xf41);
    if (!bVar18) {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (bVar18 && (bVar5 >> (bVar1 & 7) & 1) == 1) {
      piStack_ae8 = (int *)(&DAT_006a7708 + g_clientContext);
      local_b10 = &DAT_006a7f74 + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      bVar1 = *local_b10;
      bVar5 = local_b10[1];
      bVar18 = (byte)((bVar1 + bVar5) - 0x34) != local_b10[2];
      if (bVar18) {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((bVar18 || (bVar5 >> (bVar1 & 7) & 1) != 1) && ((char)piStack_ae8[0x14] != '\0')) {
        if ((*(char *)((int)piStack_ae8 + 0x2e) == '\x01') &&
           ((uVar15 = iVar6 - piStack_ae8[3] >> 0x1f,
            200 < (int)((iVar6 - piStack_ae8[3] ^ uVar15) - uVar15) ||
            (uVar15 = (int)pbVar9 - piStack_ae8[2] >> 0x1f,
            300 < (int)(((int)pbVar9 - piStack_ae8[2] ^ uVar15) - uVar15))))) {
          *(undefined1 *)((int)piStack_ae8 + 0x2e) = 0;
        }
        pbVar11 = (byte *)0x190;
        if (399 < (int)pbVar9) {
          pbVar11 = pbVar9;
        }
        pbStack_afc = (byte *)(piStack_ae8[6] + -400);
        if (((int)pbVar11 <= (int)pbStack_afc) && (pbStack_afc = (byte *)0x190, 399 < (int)pbVar9))
        {
          pbStack_afc = pbVar9;
        }
        iVar7 = -0x14;
        if (-0x15 < iVar6) {
          iVar7 = iVar6;
        }
        iVar10 = piStack_ae8[7] + -0x104;
        if ((iVar7 <= iVar10) && (iVar10 = -0x14, -0x15 < iVar6)) {
          iVar10 = iVar6;
        }
        piStack_ae8[5] = iVar10;
        if (((piStack_ae8[1] - iVar10) * (piStack_ae8[1] - iVar10) +
             (*piStack_ae8 - (int)pbStack_afc) * (*piStack_ae8 - (int)pbStack_afc) < 40000) &&
           (((char)piStack_ae8[0xb] == '\x01' || ((char)piStack_ae8[0x219] == '\0')))) {
          piStack_ae8[2] = (int)pbStack_afc;
          *piStack_ae8 = (int)pbStack_afc;
          piStack_ae8[3] = iVar10;
          piStack_ae8[1] = iVar10;
        }
        if ((((char)piStack_ae8[0xb] == '\0') && ((char)piStack_ae8[0x219] == '\x01')) &&
           (*(char *)((int)piStack_ae8 + 0x2e) == '\0')) {
          pbVar9 = (byte *)piStack_ae8[10];
          if ((int)pbStack_afc <= piStack_ae8[10]) {
            pbVar9 = pbStack_afc;
          }
          pbVar11 = (byte *)piStack_ae8[9];
          if ((piStack_ae8[9] <= (int)pbVar9) &&
             (pbVar11 = (byte *)piStack_ae8[10], (int)pbStack_afc <= piStack_ae8[10])) {
            pbVar11 = pbStack_afc;
          }
          piStack_ae8[4] = (int)pbVar11;
        }
        if ((char)piStack_ae8[0xb] == '\x01') {
          piStack_ae8[4] = (int)pbStack_afc;
          piStack_ae8[5] = iVar10;
        }
      }
    }
    goto LAB_004a89b5;
  }
LAB_004a87ec:
  FUN_00436150(&DAT_006a7f70 + g_clientContext,pbVar9,iStack_b14,0);
  pbStack_af8 = (byte *)FUN_0040a7d0(pbStack_afc,auStack_adc,7);
  puStack_10 = (undefined1 *)0xa;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_b10 = (byte *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_b10 = (byte *)EncodeChecksumDeltaDiv(pbStack_af8,auStack_688,local_b10);
  SUBFIELD(puStack_10,0,undefined1) = 0xb;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pbStack_af8 = (byte *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_af0 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pbStack_b08 = (byte *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_b10 = (byte *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0043af40(pbVar9,iStack_b14,local_b10,pbStack_b08,local_af0,pbStack_af8,(char)param_1[0xf]);
  puStack_10 = (undefined1 *)CONCAT31(SUBFIELD(puStack_10,1,undefined3),10);
  if (pbStack_674 != (byte *)0x0) {
    iVar6 = (int)pbStack_674 << 4;
    pbStack_b08 = (byte *)0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar7;
      iVar6 = iVar6 + 1;
      pbStack_b08 = pbStack_b08 + -1;
    } while (pbStack_b08 != (byte *)0x0);
    local_b10 = pbStack_674;
    FUN_0040b540(apbStack_b04);
    param_1 = piStack_af4;
  }
  puStack_10 = (undefined1 *)0xffffffff;
  local_b10 = pbStack_ac8;
  if (pbStack_ac8 != (byte *)0x0) {
    iVar6 = (int)pbStack_ac8 << 4;
    iVar7 = 0x10;
    do {
      iVar10 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar10;
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    FUN_0040b540(apbStack_b04);
    param_1 = piStack_af4;
  }
LAB_004a89b5:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = *(byte *)(param_1 + 0xe46);
  bVar5 = *(byte *)((int)param_1 + 0x3919);
  bVar18 = (byte)(bVar1 + bVar5 + -0x34) == *(char *)((int)param_1 + 0x391a);
  if (!bVar18) {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar18 && (bVar5 >> (bVar1 & 7) & 1) == 1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar6) &&
       (local_b10 = *(byte **)(&DAT_006a7720 + g_clientContext), iVar6 < (int)local_b10)) {
      pcVar12 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar6);
      pbStack_afc = (byte *)0x0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar12 != '\0') goto LAB_004a9290;
          pcVar12 = pcVar12 + (int)local_b10;
          pbStack_afc = pbStack_afc + 1;
        } while ((int)pbStack_afc < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    pbStack_afc = (byte *)0x2710;
LAB_004a9290:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_b10 = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,local_b10,pbStack_afc);
    pbStack_b08 = (byte *)0x1;
    if (0 < param_1[0xfe5]) {
      pbStack_b08 = (byte *)param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_b10 = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pbStack_af8 = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_af0 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apiStack_ae4[0] = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(apiStack_ae4[0],pbStack_afc,0,local_af0,(int)pbStack_af8 / (int)pbStack_b08,
                 local_b10,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_b10 = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((char)((char)param_1[0x3cf] + *(char *)((int)param_1 + 0xf3d) + -0x34) !=
        *(char *)((int)param_1 + 0xf3e)) {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00431d90((char)param_1[0xf],7,0,0,local_b10,0xff,2,0);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pbVar9 = (byte *)PeekPacketChecksumState();
  pbStack_af8 = pbVar9;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar13 = (int *)PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apiStack_ae4[0] = (int *)param_1[2];
  local_b10 = &DAT_006a7f70 + g_clientContext;
  pbStack_afc = pbVar9;
  piStack_ae8 = piVar13;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == 4) {
    pbVar9 = operator_new(0x3fbc);
    puStack_10 = (undefined1 *)0xc;
    apbStack_b04[0] = pbVar9;
    if (pbVar9 == (byte *)0x0) {
      pbStack_b08 = (byte *)0x0;
    }
    else {
      FUN_00454dc0(pbVar9,0x186a9);
      *(undefined ***)pbVar9 = &PTR_FUN_0055658c;
      pbVar9[0x3f9c] = 0xff;
      pbVar9[0x3f9d] = 0xff;
      pbVar9[0x3f9e] = 0xff;
      pbVar9[0x3f9f] = 0xff;
      pbStack_b08 = pbVar9;
    }
    puStack_10 = (undefined1 *)0xffffffff;
    iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar15 = *(uint *)(iVar6 + 4);
    while (uVar15 < 0x186ab) {
      if (uVar15 == 0x186aa) {
        piVar13 = *(int **)(iVar6 + 0x10);
        bVar18 = true;
        piStack_aec = piVar13;
        if (piVar13[2] == 0) goto LAB_004a9552;
        break;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar15 = *(uint *)(iVar6 + 4);
    }
  }
LAB_004a9af3:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)(*(byte *)((int)param_1 + 0xf3f) + *(byte *)(param_1 + 0x3d0) + -0x34) ==
      *(char *)((int)param_1 + 0xf41)) {
    cStack_b15 = '\x01' - ((*(byte *)(param_1 + 0x3d0) >> (*(byte *)((int)param_1 + 0xf3f) & 7) & 1)
                          != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cStack_b15 = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((cStack_b15 != '\0') && (cVar4 = FUN_0043a530(), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apbStack_b04[0] = (byte *)(g_clientContext + 0x621e8);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apbStack_b04[0] = (byte *)PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  apbStack_b04[0] = (byte *)CONCAT31(SUBFIELD(apbStack_b04[0],1,undefined3),(int)apbStack_b04[0] < iVar6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar4 = FUN_00406610(apbStack_b04[0]);
  if (cVar4 != '\0') {
    apbStack_b04[0] = (byte *)(g_clientContext + 0x5b85c);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar6 < 1) goto LAB_004a9c65;
LAB_004a9cb9:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((byte)(*(byte *)(param_1 + 0x3d3) + *(byte *)((int)param_1 + 0xf4d) + -0x34) ==
        *(char *)((int)param_1 + 0xf4e)) {
      cStack_b15 = '\x01' - ((*(byte *)((int)param_1 + 0xf4d) >> (*(byte *)(param_1 + 0x3d3) & 7) &
                             1) != 1);
    }
    else {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cStack_b15 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = g_clientContext;
    if (cStack_b15 == '\0') {
      pbVar9 = (byte *)(g_clientContext + 0x62146);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = _rand();
      *pbVar9 = (byte)iVar7;
      uVar15 = _rand();
      apbStack_b04[0] = (byte *)(uVar15 & 0x800000ff);
      if ((int)apbStack_b04[0] < 0) {
        apbStack_b04[0] = (byte *)(((uint)(apbStack_b04[0] + -1) | 0xffffff00) + 1);
      }
      bVar1 = *pbVar9;
      *(byte *)(iVar6 + 0x62147) = (byte)apbStack_b04[0];
      bVar5 = '\x01' << (bVar1 & 7);
      bVar5 = ~bVar5 & (byte)apbStack_b04[0] | bVar5;
      *(byte *)(iVar6 + 0x62147) = bVar5;
      *(byte *)(iVar6 + 0x62148) = bVar1 + bVar5 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
  }
  else {
LAB_004a9c65:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar6) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar6 < 0) goto LAB_004a9cb9;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apbStack_b04[0] = (byte *)PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  bVar18 = (int)apbStack_b04[0] < iVar6;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar18) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apbStack_b04[0] = (byte *)PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    bVar18 = (int)apbStack_b04[0] < iVar6;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (bVar18) goto LAB_004a9e72;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apbStack_b04[0] = (byte *)PeekPacketChecksumState();
  iVar6 = PeekPacketChecksumState();
  bVar18 = iVar6 < (int)apbStack_b04[0];
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar18) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar7 < iVar6) && (5 < param_1[0xed1])) {
LAB_004a9e72:
      iVar6 = g_clientContext;
      pbVar9 = (byte *)(g_clientContext + 0x62143);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = _rand();
      *pbVar9 = (byte)iVar7;
      iVar7 = _rand();
      bVar1 = *pbVar9;
      *(byte *)(iVar6 + 0x62144) = (byte)iVar7;
      bVar5 = '\x01' << (bVar1 & 7);
      bVar5 = ~bVar5 & (byte)iVar7 | bVar5;
      *(byte *)(iVar6 + 0x62144) = bVar5;
      *(byte *)(iVar6 + 0x62145) = bVar1 + bVar5 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *unaff_FS_OFFSET = uStack_18;
      return;
    }
  }
LAB_004aa4ab:
  *unaff_FS_OFFSET = uStack_18;
  return;
LAB_004a87de:
  iVar6 = iVar6 + 1;
  pbVar9 = pbVar9 + -1;
  iStack_b14 = iVar6;
  if ((int)local_b10 <= iVar6) goto LAB_004a87ec;
  goto LAB_004a87b1;
LAB_004a9552:
  if (!bVar18) goto code_r0x004a9554;
  apbStack_b04[0] = (byte *)piVar13[0xf];
  local_af0 = (int *)piVar13[0xe];
  piStack_aec = piVar13;
  iVar6 = FUN_004f1f10();
  iVar7 = FloatToInt64();
  local_af0 = (int *)((int)local_af0 - iVar7);
  iVar7 = FloatToInt64();
  pbStack_af8 = apbStack_b04[0] + -iVar7;
  (**(code **)(*piVar13 + 4))(&DAT_00553b90);
  piVar13[0x11] = iVar6;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = local_b10[4];
  bVar5 = local_b10[5];
  bVar18 = (byte)((bVar1 + bVar5) - 0x34) != local_b10[6];
  if (bVar18) {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (bVar18 || (bVar5 >> (bVar1 & 7) & 1) != 1) {
    uStack_8bc = 0;
    pbStack_ac8 = (byte *)0x0;
    EncodeOutgoingPacketField(0);
    puStack_10 = (undefined1 *)0xf;
    uStack_694 = 0;
    pbStack_8a0 = (byte *)0x0;
    EncodeOutgoingPacketField(0);
    puStack_10 = (undefined1 *)CONCAT31(SUBFIELD(puStack_10,1,undefined3),0x10);
    FUN_004262d0(apiStack_ae4[0] + 4,auStack_8b4);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    apbStack_b04[0] = (byte *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((char)((char)param_1[0x3cf] + *(char *)((int)param_1 + 0xf3d) + -0x34) !=
        *(char *)((int)param_1 + 0xf3e)) {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00432320((char)param_1[0xf],1,1,apbStack_b04[0],0,100,0xff,param_1[0xfe5],0);
    pbVar9 = pbStack_8a0;
    puStack_10 = (undefined1 *)CONCAT31(SUBFIELD(puStack_10,1,undefined3),0xf);
    if (pbStack_8a0 != (byte *)0x0) {
      iVar7 = (int)pbStack_8a0 << 4;
      apiStack_ae4[0] = (int *)0x10;
      do {
        iVar10 = _rand();
        *(char *)(iVar7 + DAT_0079376c) = (char)iVar10;
        iVar7 = iVar7 + 1;
        apiStack_ae4[0] = (int *)((int)apiStack_ae4[0] + -1);
      } while (apiStack_ae4[0] != (int *)0x0);
      apbStack_b04[0] = pbVar9;
      FUN_0040b540(apiStack_ae4);
      param_1 = piStack_af4;
    }
    puStack_10 = (undefined1 *)0xffffffff;
    if (pbStack_ac8 != (byte *)0x0) {
      iVar7 = (int)pbStack_ac8 << 4;
      iVar10 = 0x10;
      do {
        iVar14 = _rand();
        *(char *)(iVar7 + DAT_0079376c) = (char)iVar14;
        iVar7 = iVar7 + 1;
        iVar10 = iVar10 + -1;
        pbVar9 = pbStack_ac8;
      } while (iVar10 != 0);
      goto LAB_004a9a04;
    }
  }
  else {
    cVar4 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&piStack_ae8,&pbStack_afc,2,1,1);
    if (cVar4 != '\0') {
      uStack_694 = 0;
      pbStack_8a0 = (byte *)0x0;
      EncodeOutgoingPacketField(0);
      puStack_10 = (undefined1 *)0xd;
      uStack_8bc = 0;
      pbStack_ac8 = (byte *)0x0;
      EncodeOutgoingPacketField(0);
      SUBFIELD(puStack_10,0,undefined1) = 0xe;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(piStack_ae8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(pbStack_afc);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_004262d0(apiStack_ae4[0] + 4,auStack_adc);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      apbStack_b04[0] = (byte *)PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar7 = param_1[0xfe5];
      uVar21 = 0;
      uVar20 = 0xff;
      uVar19 = 100;
      uVar8 = 0;
      pbVar9 = apbStack_b04[0];
      PeekPacketChecksumBool(apbStack_b04[0],0,100,0xff,iVar7,0);
      FUN_00432320((char)param_1[0xf],1,1,pbVar9,uVar8,uVar19,uVar20,iVar7,uVar21);
      pbVar9 = pbStack_ac8;
      puStack_10 = (undefined1 *)CONCAT31(SUBFIELD(puStack_10,1,undefined3),0xd);
      if (pbStack_ac8 != (byte *)0x0) {
        iVar7 = (int)pbStack_ac8 << 4;
        apiStack_ae4[0] = (int *)0x10;
        do {
          iVar10 = _rand();
          *(char *)(iVar7 + DAT_0079376c) = (char)iVar10;
          iVar7 = iVar7 + 1;
          apiStack_ae4[0] = (int *)((int)apiStack_ae4[0] + -1);
        } while (apiStack_ae4[0] != (int *)0x0);
        apbStack_b04[0] = pbVar9;
        FUN_0040b540(apiStack_ae4);
        param_1 = piStack_af4;
      }
      puStack_10 = (undefined1 *)0xffffffff;
      if (pbStack_8a0 != (byte *)0x0) {
        iVar7 = (int)pbStack_8a0 << 4;
        iVar10 = 0x10;
        do {
          iVar14 = _rand();
          *(char *)(iVar7 + DAT_0079376c) = (char)iVar14;
          iVar7 = iVar7 + 1;
          iVar10 = iVar10 + -1;
          pbVar9 = pbStack_8a0;
        } while (iVar10 != 0);
LAB_004a9a04:
        apbStack_b04[0] = pbVar9;
        FUN_0040b540(apiStack_ae4);
        param_1 = piStack_af4;
      }
    }
  }
  pbVar9 = pbStack_b08;
  *(int **)(pbStack_b08 + 0x3fa8) = local_af0;
  *(byte **)(pbStack_b08 + 0x3fac) = pbStack_af8;
  *(byte **)(pbStack_b08 + 0x3fb4) = pbStack_afc;
  *(int **)(pbStack_b08 + 0x3fb0) = piStack_ae8;
  *(int *)(pbStack_b08 + 0x3fb8) = iVar6;
  uVar8 = FUN_004ac4d0();
  *(undefined4 *)(pbVar9 + 0x3fa4) = uVar8;
  iVar6 = FUN_004ac400();
  *(int *)(pbVar9 + 0x3fa0) = iVar6 * param_1[0xfe5];
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)((local_b10[4] + local_b10[5]) - 0x34) == local_b10[6]) {
    cStack_b15 = '\x01' - ((local_b10[5] >> (local_b10[4] & 7) & 1) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cStack_b15 = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (cStack_b15 == '\0') {
    RegisterActiveObject();
  }
  else {
    (*(code *)**(undefined4 **)pbVar9)(1);
  }
  goto LAB_004a9af3;
code_r0x004a9554:
  piVar13 = (int *)piVar13[4];
  bVar18 = piVar13[2] == 0;
  piStack_aec = piVar13;
  if (!bVar18) goto LAB_004a9af3;
  goto LAB_004a9552;
}

