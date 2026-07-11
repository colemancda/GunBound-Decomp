/* FUN_004a2ce0 - 0x004a2ce0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004a2ce0(int *param_1)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff2c0;
  undefined stack0xfffff2d0;
  undefined stack0xfffff2d4;
  undefined stack0xfffff2d8;
  undefined stack0xfffff2dc;
  undefined stack0xfffff2e0;
  undefined stack0xfffff2e4;
  byte bVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  char *pcVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  byte bVar18;
  int iVar19;
  code *pcVar20;
  byte *pbVar21;
  int unaff_EDI;
  int *piVar22;
  undefined4 *unaff_FS_OFFSET;
  bool bVar23;
  undefined4 uVar24;
  undefined4 uVar25;
  undefined *puVar26;
  undefined4 uVar27;
  char cVar28;
  undefined *puVar29;
  undefined *puVar30;
  undefined *puVar31;
  undefined *puVar32;
  undefined *puVar33;
  undefined *puVar34;
  undefined *puVar35;
  undefined1 auStack_d18 [3];
  char local_d15;
  int local_d14;
  int *local_d10;
  int local_d0c;
  undefined *puStack_d08;
  undefined4 local_d04;
  float local_d00;
  int local_cfc;
  int *local_cf8 [4];
  undefined *puStack_ce8;
  int local_ce4;
  int local_cd0;
  undefined1 uStack_b04;
  undefined1 auStack_b00 [4];
  undefined1 auStack_afc [16];
  undefined4 uStack_aec;
  int local_aac;
  undefined1 uStack_8e0;
  undefined1 auStack_8d8 [532];
  undefined1 auStack_6c4 [20];
  int iStack_6b0;
  undefined1 auStack_490 [532];
  undefined1 auStack_27c [20];
  int iStack_268;
  undefined4 uStack_58;
  undefined4 uStack_50;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053eb25;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_d04 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d10 = param_1 + 0xfea;
  iVar4 = PeekPacketChecksumState();
  pcVar20 = (code *)LeaveCriticalSection;
  local_d15 = iVar4 == -1000000;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (local_d15 == '\0') {
LAB_004a2df0:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_cf8[0] = param_1 + 0x1073;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_cf8[0] = param_1 + 0x1073;
    iVar4 = PeekPacketChecksumState();
    local_d15 = iVar4 == -1000000;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (local_d15 == '\0') goto LAB_004a2df0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004585e0();
  EncodeChecksumDeltaAdd();
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d14 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaMod();
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if (local_cd0 != 0) {
    ScrambleChecksumGuardBytes();
    local_d14 = local_cd0;
    TreeLowerBound();
    pcVar20 = (code *)LeaveCriticalSection;
  }
  local_4 = 0xffffffff;
  if (local_aac != 0) {
    ScrambleChecksumGuardBytes();
    local_d14 = local_aac;
    TreeLowerBound();
    pcVar20 = (code *)LeaveCriticalSection;
  }
  local_cfc = (param_1[0xfe7] + 0x5a) % 0x168;
  local_d14 = param_1[0xfe9] << 8;
  local_d00 = (float)local_d14;
  local_d14 = FloatToInt64();
  local_cfc = FloatToInt64();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  puVar35 = &DAT_005a9068;
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  puVar34 = &DAT_005a9068;
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d04 = PeekPacketChecksumState();
  puVar33 = &DAT_005a9068;
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d0c = PeekPacketChecksumState();
  puVar32 = &DAT_005a9068;
  (*pcVar20)();
  EncodeChecksumPairDiff(param_1 + 0x10);
  uStack_14 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  puVar31 = &DAT_005a9068;
  (*pcVar20)();
  uStack_18 = 0xffffffff;
  if (local_ce4 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound();
    pcVar20 = (code *)LeaveCriticalSection;
    unaff_EDI = local_ce4;
  }
  EncodeChecksumPairDiff(param_1 + 0x99,local_cf8);
  uStack_18 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  (*pcVar20)();
  uStack_1c = 0xffffffff;
  if (puStack_ce8 != (undefined *)0x0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffff2dc);
    pcVar20 = (code *)LeaveCriticalSection;
    puVar35 = puStack_ce8;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar5);
  puVar30 = &DAT_005a9068;
  (*pcVar20)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar5);
  (*pcVar20)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  (*pcVar20)(&DAT_005a9068);
  iVar4 = param_1[0xfe7];
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((iVar4 + 0x5a) % iVar6);
  puVar29 = &DAT_005a9068;
  (*pcVar20)(&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(unaff_EDI);
  cVar3 = '\0';
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(puVar34);
  puVar34 = &DAT_005a9068;
  (*pcVar20)(&DAT_005a9068);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    EncodeChecksumDeltaShr(param_1 + 0x10,auStack_d18,8);
    uStack_38 = 9;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    (*pcVar20)(&DAT_005a9068);
    uStack_3c = 0xffffffff;
    if (puStack_d08 != (undefined *)0x0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff2d4);
      pcVar20 = (code *)LeaveCriticalSection;
      puVar30 = puStack_d08;
    }
    EncodeChecksumDeltaShr(param_1 + 0x99,&stack0xfffff2e4,8);
    uStack_3c = 10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    cVar2 = '\0';
    (*pcVar20)();
    uStack_40 = 0xffffffff;
    if (local_d0c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff2d0);
      pcVar20 = (code *)LeaveCriticalSection;
    }
    cVar3 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
    if (cVar3 == '\0') {
      EmitChecksumSum(param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar15 = PeekPacketChecksumState();
      (*pcVar20)(&DAT_005a9068);
      if ((int)((uVar15 ^ (int)uVar15 >> 0x1f) - ((int)uVar15 >> 0x1f)) < 200) {
        cVar3 = PacketChecksumLessThan(param_1 + 0x122,0);
        if (cVar3 == '\0') {
          uVar5 = 200;
        }
        else {
          uVar5 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar5);
      }
      uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8d8,4);
      uStack_40 = 0xb;
      uVar5 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_490,uVar5);
      uStack_40 = 0xc;
      uVar15 = 3;
      cVar3 = CompareChecksumPair(param_1 + 0x3d5,uVar5);
      if (cVar3 == '\0') {
        uVar5 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_afc,4);
        uStack_40 = 0xd;
        uVar5 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&stack0xfffff2e0,uVar5);
        uStack_40 = 0xe;
        uVar15 = 0xf;
        cVar3 = CompareChecksumPair(uVar5,param_1 + 0x3d5);
        if (cVar3 != '\0') goto LAB_004a41c8;
        cVar3 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18);
        bVar23 = false;
        if (cVar3 != '\0') goto LAB_004a41c8;
      }
      else {
LAB_004a41c8:
        bVar23 = true;
      }
      uStack_40 = 0xd;
      if ((uVar15 & 8) != 0) {
        uVar15 = uVar15 & 0xfffffff7;
        ScrubChecksumGuard();
      }
      uStack_40 = 0xc;
      if ((uVar15 & 4) != 0) {
        uVar15 = uVar15 & 0xfffffffb;
        ScrubChecksumGuard();
      }
      uStack_40 = 0xb;
      if ((uVar15 & 2) != 0) {
        uVar15 = uVar15 & 0xfffffffd;
        ScrubChecksumGuard();
      }
      uStack_40 = 0xffffffff;
      if ((uVar15 & 1) != 0) {
        ScrubChecksumGuard();
      }
      if (bVar23) {
        iVar4 = param_1[0x3d4];
        param_1[0x3d4] = iVar4 + 1;
        if (iVar4 + 1 < 3) {
          uVar5 = EncodeChecksumNegate(param_1 + 0x122,auStack_8d8);
          uStack_40 = 0xf;
          EncodeChecksumState(uVar5);
          uStack_40 = 0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    if (cVar2 == '\0') {
      iVar4 = *(int *)(&DAT_006a7720 + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      cVar2 = iVar4 <= iVar6;
      (*pcVar20)(&DAT_005a9068);
      if (cVar2 != '\0') goto LAB_004a4381;
      cVar2 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&DAT_006a7724 + g_clientContext));
      if ((cVar2 != '\0') || (cVar2 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar2 != '\0'))
      goto LAB_004a4381;
    }
    else {
LAB_004a4381:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar2 = PeekPacketChecksumBool();
      if ((cVar2 != '\0') && (cVar2 = FUN_0043a530(), cVar2 == '\0')) {
        iVar4 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar4 == 5) || (uVar5 = 2, iVar4 == 6)) {
          uVar5 = 0x19;
        }
        QueueOutgoingPacketField(uVar5);
      }
    }
    cVar2 = CheckBothGuardedBools();
    if (cVar2 != '\0') {
      EncodeChecksumDeltaShr(puVar30,auStack_27c,8);
      uStack_50 = 0x10;
      EncodeChecksumDeltaShr(puVar34,auStack_6c4,8);
      SUBFIELD(uStack_50,0,undefined1) = 0x11;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      (*pcVar20)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar14 = PeekPacketChecksumState();
      (*pcVar20)(&DAT_005a9068);
      iVar4 = g_clientContext;
      piVar22 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar2 = PeekPacketChecksumBool();
      if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar4] != '\0')) {
        if (((&DAT_006a7736)[iVar4] == '\x01') &&
           ((uVar15 = iVar6 - *(int *)(&DAT_006a7714 + iVar4) >> 0x1f,
            200 < (int)((iVar6 - *(int *)(&DAT_006a7714 + iVar4) ^ uVar15) - uVar15) ||
            (uVar15 = iVar14 - *(int *)(&DAT_006a7710 + iVar4) >> 0x1f,
            300 < (int)((iVar14 - *(int *)(&DAT_006a7710 + iVar4) ^ uVar15) - uVar15))))) {
          (&DAT_006a7736)[iVar4] = 0;
        }
        iVar19 = 400;
        if (399 < iVar14) {
          iVar19 = iVar14;
        }
        iVar16 = *(int *)(&DAT_006a7720 + iVar4) + -400;
        if ((iVar19 <= iVar16) && (iVar16 = iVar14, iVar14 < 400)) {
          iVar16 = 400;
        }
        iVar14 = -0x14;
        if (-0x15 < iVar6) {
          iVar14 = iVar6;
        }
        iVar19 = *(int *)(&DAT_006a7724 + iVar4) + -0x104;
        if ((iVar14 <= *(int *)(&DAT_006a7724 + iVar4) + -0x104) && (iVar19 = -0x14, -0x15 < iVar6))
        {
          iVar19 = iVar6;
        }
        iVar6 = *piVar22 - iVar16;
        *(int *)(&DAT_006a771c + iVar4) = iVar19;
        if (((*(int *)(&DAT_006a770c + iVar4) - iVar19) * (*(int *)(&DAT_006a770c + iVar4) - iVar19)
             + iVar6 * iVar6 < 40000) &&
           (((&DAT_006a7734)[iVar4] == '\x01' || ((&DAT_006a7f6c)[iVar4] == '\0')))) {
          *(int *)(&DAT_006a7710 + iVar4) = iVar16;
          *piVar22 = iVar16;
          *(int *)(&DAT_006a7714 + iVar4) = iVar19;
          *(int *)(&DAT_006a770c + iVar4) = iVar19;
        }
        if ((((&DAT_006a7734)[iVar4] == '\0') && ((&DAT_006a7f6c)[iVar4] == '\x01')) &&
           ((&DAT_006a7736)[iVar4] == '\0')) {
          iVar6 = *(int *)(&DAT_006a7730 + iVar4);
          iVar14 = iVar6;
          if (iVar16 <= iVar6) {
            iVar14 = iVar16;
          }
          iVar17 = *(int *)(&DAT_006a772c + iVar4);
          if ((iVar17 <= iVar14) && (iVar17 = iVar6, iVar16 <= iVar6)) {
            iVar17 = iVar16;
          }
          *(int *)(&DAT_006a7718 + iVar4) = iVar17;
        }
        if ((&DAT_006a7734)[iVar4] == '\x01') {
          *(int *)(&DAT_006a7718 + iVar4) = iVar16;
          *(int *)(&DAT_006a771c + iVar4) = iVar19;
        }
      }
      uStack_50 = CONCAT31(SUBFIELD(uStack_50,1,undefined3),0x10);
      if (iStack_6b0 != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(&stack0xfffff2c0);
      }
      uStack_50 = 0xffffffff;
      if (iStack_268 != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(&stack0xfffff2c0);
      }
    }
    goto LAB_004a45e9;
  }
  FUN_004262d0(param_1[2],param_1 + 0x45e);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    puVar26 = &DAT_005a9068;
    (*pcVar20)(&DAT_005a9068);
    if ((-1 < iVar4) && (iVar4 < *(int *)(&DAT_006a7720 + g_clientContext))) {
      pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar4);
      iVar4 = 0;
      if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        do {
          if (*pcVar7 != '\0') goto LAB_004a337e;
          pcVar7 = pcVar7 + *(int *)(&DAT_006a7720 + g_clientContext);
          iVar4 = iVar4 + 1;
        } while (iVar4 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
    iVar4 = 10000;
LAB_004a337e:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,puVar29,iVar6);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puVar31 = (undefined *)PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    FUN_0043af40(puVar33,puVar34,0,puVar32,iVar4 / iVar6,puVar26,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar20)(&DAT_005a9068);
    uVar27 = 0;
    uVar25 = 2;
    uVar24 = 0xff;
    uVar5 = 0;
    PeekPacketChecksumBool(0,iVar4,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar5,iVar4,uVar24,uVar25,uVar27);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  cVar28 = '\0';
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  cVar2 = '\0';
  (*pcVar20)();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar20)(&DAT_005a9068);
  if (cVar3 == '\0') {
    puVar8 = operator_new(0x3fbc);
    uStack_44 = 4;
    if (puVar8 == (undefined4 *)0x0) {
      puVar8 = (undefined4 *)0x0;
    }
    else {
      InitProjectile(puVar8,0x186a9);
      *puVar8 = &PTR_FUN_0055658c;
      puVar8[0xfe7] = 0xffffffff;
    }
    uStack_44 = 0xffffffff;
    iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar15 = *(uint *)(iVar4 + 4);
    while (uVar15 < 0x186ab) {
      if (uVar15 == 0x186aa) {
        piVar22 = *(int **)(iVar4 + 0x10);
        bVar23 = true;
        if (piVar22[2] == 0) goto LAB_004a3601;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar15 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_004a3955;
  while( true ) {
    piVar22 = (int *)piVar22[4];
    bVar23 = piVar22[2] == 0;
    if (!bVar23) break;
LAB_004a3601:
    if (bVar23) {
      iVar4 = piVar22[0xf];
      iVar6 = piVar22[0xe];
      iVar14 = FUN_004f1f10();
      iVar19 = FloatToInt64();
      iVar6 = iVar6 - iVar19;
      iVar19 = FloatToInt64();
      (**(code **)(*piVar22 + 4))(&DAT_00553b90);
      piVar22[0x11] = iVar14;
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
        uStack_8e0 = 0;
        uStack_aec = 0;
        EncodeOutgoingPacketField(0);
        uStack_44 = 7;
        uStack_b04 = 0;
        local_d10 = (int *)0x0;
        EncodeOutgoingPacketField(0);
        SUBFIELD(uStack_44,0,undefined1) = 8;
        FUN_004262d0(puVar30 + 0x10,&stack0xfffff2dc);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        (*pcVar20)(&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        puVar8 = (undefined4 *)PeekPacketChecksumState();
        (*pcVar20)(&DAT_005a9068);
        iVar16 = param_1[0xfe5];
        uVar9 = 0;
        uVar27 = 0xff;
        uVar25 = 100;
        uVar24 = 0;
        PeekPacketChecksumBool(uVar5,0,100,0xff,iVar16,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar5,uVar24,uVar25,uVar27,iVar16,uVar9);
        uStack_44 = CONCAT31(SUBFIELD(uStack_44,1,undefined3),7);
        ScrubChecksumGuard();
LAB_004a38be:
        uStack_44 = 0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar3 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&stack0xfffff2d8,&stack0xfffff2d4,2,1,1);
        if (cVar3 != '\0') {
          uStack_b04 = 0;
          local_d10 = (int *)0x0;
          EncodeOutgoingPacketField(0);
          uStack_44 = 5;
          uStack_8e0 = 0;
          uStack_aec = 0;
          EncodeOutgoingPacketField(0);
          SUBFIELD(uStack_44,0,undefined1) = 6;
          QueueOutgoingPacketField(puVar31);
          QueueOutgoingPacketField(puVar35);
          FUN_004262d0(puVar30 + 0x10,auStack_b00);
          iVar16 = param_1[0xfe5];
          uVar9 = 0;
          uVar27 = 0xff;
          uVar25 = 100;
          uVar24 = 0;
          PeekChecksumStateUnderLock(auStack_b00);
          uVar5 = PeekChecksumStateUnderLock(&stack0xfffff2dc);
          PeekPacketChecksumBool(uVar5,uVar24,uVar25,uVar27,iVar16,uVar9);
          FUN_00432320((char)param_1[0xf],1,1,uVar5,uVar24,uVar25,uVar27,iVar16,uVar9);
          uStack_44 = CONCAT31(SUBFIELD(uStack_44,1,undefined3),5);
          ScrubChecksumGuard();
          goto LAB_004a38be;
        }
      }
      puVar8[0xfea] = iVar6;
      puVar8[0xfeb] = iVar4 - iVar19;
      puVar8[0xfec] = puVar31;
      puVar8[0xfed] = puVar35;
      puVar8[0xfee] = iVar14;
      uVar5 = FUN_004ac4d0();
      puVar8[0xfe9] = uVar5;
      iVar4 = FUN_004ac400();
      puVar8[0xfe8] = iVar4 * param_1[0xfe5];
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
        RegisterActiveObject();
      }
      else {
        (**(code **)*puVar8)(1);
      }
      break;
    }
  }
LAB_004a3955:
  *(undefined1 *)(param_1 + 5) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar24 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar25 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar27 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar12 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar13 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004e4970(uVar12,uVar11,uVar10,uVar9,uVar27,uVar25,uVar24,uVar5);
  FUN_004e4d00(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar24 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(uVar24,uVar5,param_1,1,0,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar24 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar24,uVar5);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar24 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(param_1[2],uVar24,uVar5,param_1[0xe25],param_1 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar24 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar25 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar25,uVar24,0x3c,uVar5);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = g_clientContext;
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 != '\x01') {
    iVar14 = *(int *)(&DAT_006a7750 + iVar4);
    if (iVar14 < 0xb) {
      iVar14 = 10;
    }
    *(int *)(&DAT_006a7750 + iVar4) = iVar14;
    iVar14 = 10;
    if (iVar6 < 0xb) {
      iVar14 = iVar6;
    }
    iVar19 = *(int *)(&DAT_006a7754 + iVar4);
    if ((iVar19 <= iVar14) && (iVar19 = iVar6, 10 < iVar6)) {
      iVar19 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar4) = iVar19;
  }
  cVar3 = PeekPacketChecksumBool();
  if (cVar3 == '\0') {
    AcquireSoundChannel(0);
  }
  cVar3 = PeekPacketChecksumBool();
  pcVar20 = (code *)LeaveCriticalSection;
  if ((cVar3 != '\0') &&
     (cVar3 = FUN_0043a530(), pcVar20 = (code *)LeaveCriticalSection, cVar3 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    pcVar20 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    QueueOutgoingPacketField(uVar5);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar20)(&DAT_005a9068);
  cVar3 = CheckGuardedBoolAnd(uVar13);
  if (cVar3 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    (*pcVar20)(&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar20)(&DAT_005a9068);
  if (cVar28 == '\0') {
LAB_004a3e01:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    cVar3 = 0 < iVar4;
    (*pcVar20)(&DAT_005a9068);
    if (cVar3 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      cVar3 = iVar4 < 0;
      (*pcVar20)(&DAT_005a9068);
      if (cVar3 != '\0') goto LAB_004a3e4d;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    cVar3 = 0 < iVar4;
    (*pcVar20)(&DAT_005a9068);
    if (cVar3 == '\0') goto LAB_004a3e01;
LAB_004a3e4d:
    cVar3 = PeekPacketChecksumBool();
    if (cVar3 == '\0') {
      SetGuardedBool(1);
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar20)(&DAT_005a9068);
  if ((cVar2 == '\0') || (cVar2 = CompareChecksumPair(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    cVar2 = iVar6 < iVar4;
    (*pcVar20)(&DAT_005a9068);
    if ((cVar2 == '\0') ||
       ((cVar2 = FUN_0040b410(param_1 + 0xed2,param_1 + 0xf5b), cVar2 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_004a45e9;
  }
  iVar4 = g_clientContext;
  pbVar21 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar21 = (byte)iVar6;
  iVar6 = _rand();
  bVar1 = *pbVar21;
  *(byte *)(iVar4 + 0x62144) = (byte)iVar6;
  bVar18 = '\x01' << (bVar1 & 7);
  bVar1 = *pbVar21;
  bVar18 = ~bVar18 & (byte)iVar6 | bVar18;
  *(byte *)(iVar4 + 0x62144) = bVar18;
  *(byte *)(iVar4 + 0x62145) = bVar18 + bVar1 + -0x34;
  (*pcVar20)(&DAT_005a9068);
LAB_004a45e9:
  *unaff_FS_OFFSET = uStack_58;
  return;
}

