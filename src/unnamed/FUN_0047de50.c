/* FUN_0047de50 - 0x0047de50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0047def3) */

void __fastcall FUN_0047de50(int *param_1)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff524;
  int *piVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  byte bVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  char extraout_var;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  code *pcVar17;
  undefined4 unaff_EBP;
  uint unaff_ESI;
  code *pcVar18;
  byte *pbVar19;
  undefined4 *unaff_FS_OFFSET;
  char cVar20;
  /* New local (2026-07-15): captures the previously-discarded return of
   * the `PeekPacketChecksumState();` call below (line ~301) so it can be
   * forwarded as EncodeOutgoingPacketField's dropped `self` arg further
   * down - see the FIXED comment at that call. */
  uint uVar19;
  int *local_ad0;
  undefined4 uStack_acc;
  int local_ac8;
  undefined1 auStack_ac4 [4];
  undefined1 local_ac0 [548];
  int iStack_ab8;
  int iStack_ab4;
  undefined1 auStack_8a8 [12];
  undefined1 local_89c [548];
  undefined1 auStack_684 [548];
  undefined1 auStack_460 [548];
  undefined1 auStack_23c [532];
  undefined4 uStack_28;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539bef;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  pcVar18 = (code *)EnterCriticalSection;
  local_ad0 = (int *)0x0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47dea0
   * (`lea edi,[ebp+0x40]` at 0x47de84, ebp = this file's own param_1,
   * per `mov ebp,ecx` in the prologue) the cell is param_1+0x10 (scaled
   * int* units, byte offset 0x40) - the same cell
   * EncodeChecksumDeltaShr(param_1 + 0x10, ...) below already addresses.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  iVar9 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_1 + 0x10, iVar9 + iVar8);
  pcVar17 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47dedc
   * (`lea edi,[ebp+0x264]` at 0x47deb7) the cell is param_1+0x99
   * (scaled), the same cell EncodeChecksumDeltaShr(param_1 + 0x99, ...)
   * below already addresses. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ac8 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_1 + 0x99, iVar8 + local_ac8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar12 = *(uint *)(iVar8 + 4);
  while (uVar12 < 0x186a6) {
    if (uVar12 == 0x186a5) {
      iVar8 = *(int *)(iVar8 + 0x10);
      uVar12 = *(uint *)(iVar8 + 8);
      goto joined_r0x0047df31;
    }
    iVar8 = *(int *)(iVar8 + 0x1c);
    uVar12 = *(uint *)(iVar8 + 4);
  }
  iVar8 = 0;
LAB_0047e058:
  cVar7 = '\0';
  (**(code **)(*param_1 + 0x14))();
  cVar5 = PeekPacketChecksumBool();
  if (cVar5 == '\0') {
    EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x2;
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x47e380 (`lea edi,[ebp+0xf54]` at 0x47e37a): cell = param_1+0x3d5
     * (scaled). Note: per JSON this is listed as "site3" in address
     * order (call_addr 0x47e163, edi = dword ptr [esp+0x14]) but that
     * particular entry actually corresponds textually to the LAST
     * EncodeOutgoingPacketField call further below, near
     * CheckGuardedBoolAnd(unaff_EBP) - see that call's own comment (same
     * structure as FUN_0044f050.c, confirmed via objdump at this
     * function's own addresses). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(param_1 + 0x3d5, uVar10);
    (*pcVar17)(&DAT_005a9068);
    uStack_c = 0xffffffff;
    if (iStack_ab4 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_ad0);
      pcVar17 = (code *)LeaveCriticalSection;
    }
    EncodeChecksumDeltaShr(param_1 + 0x99,&local_ac8,8);
    local_ad0 = param_1 + 0x45e;
    uStack_c = 3;
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x47e405 (`mov edi,dword ptr [esp+0x20]`, that stack slot was
     * spilled from `lea ecx,[ebp+0x1178]` = param_1+0x1178 a few
     * instructions earlier) the cell is param_1+0x45e (scaled), same as
     * local_ad0 = param_1 + 0x45e immediately above. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(param_1 + 0x45e, uVar10);
    cVar5 = '\0';
    (*pcVar17)();
    uStack_10 = 0xffffffff;
    if (iStack_ab8 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&stack0xfffff524);
      pcVar17 = (code *)LeaveCriticalSection;
    }
    cVar7 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
    if (cVar7 == '\0') {
      EmitChecksumSum(param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar12 = PeekPacketChecksumState();
      (*pcVar17)(&DAT_005a9068);
      if ((int)((uVar12 ^ (int)uVar12 >> 0x1f) - ((int)uVar12 >> 0x1f)) < 200) {
        cVar7 = PacketChecksumLessThan(param_1 + 0x122,0);
        if (cVar7 == '\0') {
          uVar10 = 200;
        }
        else {
          uVar10 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar10);
      }
      uVar10 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_684,4);
      uStack_10 = 4;
      uVar10 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_460,uVar10);
      uStack_10 = 5;
      bVar4 = false;
      bVar3 = false;
      cVar7 = CompareChecksumPair(param_1 + 0x3d5,uVar10);
      if (cVar7 == '\0') {
        uVar10 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_8a8,4);
        uStack_10 = 6;
        uVar10 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,&uStack_acc,uVar10);
        uStack_10 = 7;
        bVar4 = true;
        bVar3 = true;
        cVar7 = CompareChecksumPair(uVar10,param_1 + 0x3d5);
        unaff_ESI = unaff_ESI & 0xffffff;
        if (cVar7 != '\0') goto LAB_0047e58b;
      }
      else {
LAB_0047e58b:
        unaff_ESI = CONCAT13(1,(int3)unaff_ESI);
      }
      uStack_10 = 6;
      if (bVar3) {
        ScrubChecksumGuard();
      }
      uStack_10 = 5;
      if (bVar4) {
        ScrubChecksumGuard();
      }
      uStack_10 = 4;
      ScrubChecksumGuard();
      uStack_10 = 0xffffffff;
      ScrubChecksumGuard();
      if ((char)(unaff_ESI >> 0x18) != '\0') {
        iVar8 = param_1[0x3d4];
        param_1[0x3d4] = iVar8 + 1;
        if (iVar8 + 1 < 3) {
          uVar10 = EncodeChecksumNegate(param_1 + 0x122,auStack_23c);
          uStack_10 = 8;
          EncodeChecksumState(uVar10);
          uStack_10 = 0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = PeekPacketChecksumState();
    uVar10 = CONCAT13(iVar8 < 0,(int3)unaff_ESI);
    (*pcVar17)(&DAT_005a9068);
    if (cVar5 == '\0') {
      iVar8 = *(int *)(&g_nCameraBoundX + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState();
      cVar5 = iVar8 <= iVar9;
      (*pcVar17)(&DAT_005a9068);
      if (((cVar5 != '\0') ||
          (cVar5 = PacketChecksumGreaterEqual(uVar10,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)), cVar5 != '\0'
          )) || (cVar5 = PacketChecksumLessThan(uVar10,0xfffffc18), cVar5 != '\0')) goto LAB_0047e746;
    }
    else {
LAB_0047e746:
      *(undefined1 *)(param_1 + 5) = 1;
      cVar5 = PeekPacketChecksumBool();
      if ((cVar5 != '\0') && (cVar5 = InitChecksumSeed(), cVar5 == '\0')) {
        iVar8 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar8 == 5) || (uVar10 = 2, iVar8 == 6)) {
          uVar10 = 0x19;
        }
        QueueOutgoingPacketField(uVar10);
        iVar8 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar8) = 0;
      }
    }
    cVar5 = CheckBothGuardedBools();
    if (cVar5 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState();
      (*pcVar17)(&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = PeekPacketChecksumState();
      (*pcVar17)(&DAT_005a9068);
      iVar8 = g_clientContext;
      piVar1 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar5 = PeekPacketChecksumBool();
      if ((cVar5 == '\0') && ((&DAT_006a7758)[iVar8] != '\0')) {
        if (((&DAT_006a7736)[iVar8] == '\x01') &&
           ((uVar12 = iVar9 - *(int *)(&g_nCameraY + iVar8) >> 0x1f,
            200 < (int)((iVar9 - *(int *)(&g_nCameraY + iVar8) ^ uVar12) - uVar12) ||
            (uVar12 = iVar13 - *(int *)(&g_nCameraX + iVar8) >> 0x1f,
            300 < (int)((iVar13 - *(int *)(&g_nCameraX + iVar8) ^ uVar12) - uVar12))))) {
          (&DAT_006a7736)[iVar8] = 0;
        }
        iVar15 = 400;
        if (399 < iVar13) {
          iVar15 = iVar13;
        }
        iVar14 = *(int *)(&g_nCameraBoundX + iVar8) + -400;
        if ((iVar15 <= iVar14) && (iVar14 = iVar13, iVar13 < 400)) {
          iVar14 = 400;
        }
        iVar13 = -0x14;
        if (-0x15 < iVar9) {
          iVar13 = iVar9;
        }
        iVar15 = *(int *)(&g_nCameraBoundY + iVar8) + -0x104;
        if ((iVar13 <= iVar15) && (iVar15 = -0x14, -0x15 < iVar9)) {
          iVar15 = iVar9;
        }
        iVar9 = *piVar1 - iVar14;
        *(int *)(&g_nCameraScrollY + iVar8) = iVar15;
        if (((*(int *)(&DAT_006a770c + iVar8) - iVar15) * (*(int *)(&DAT_006a770c + iVar8) - iVar15)
             + iVar9 * iVar9 < 40000) &&
           (((&DAT_006a7734)[iVar8] == '\x01' || ((&DAT_006a7f6c)[iVar8] == '\0')))) {
          *(int *)(&g_nCameraX + iVar8) = iVar14;
          *piVar1 = iVar14;
          *(int *)(&g_nCameraY + iVar8) = iVar15;
          *(int *)(&DAT_006a770c + iVar8) = iVar15;
        }
        if ((((&DAT_006a7734)[iVar8] == '\0') && ((&DAT_006a7f6c)[iVar8] == '\x01')) &&
           ((&DAT_006a7736)[iVar8] == '\0')) {
          iVar9 = *(int *)(&DAT_006a7730 + iVar8);
          iVar13 = iVar9;
          if (iVar14 <= iVar9) {
            iVar13 = iVar14;
          }
          iVar16 = *(int *)(&DAT_006a772c + iVar8);
          if ((iVar16 <= iVar13) && (iVar16 = iVar9, iVar14 <= iVar9)) {
            iVar16 = iVar14;
          }
          *(int *)(&g_nCameraScrollX + iVar8) = iVar16;
        }
        if ((&DAT_006a7734)[iVar8] == '\x01') {
          *(int *)(&g_nCameraScrollX + iVar8) = iVar14;
          *(int *)(&g_nCameraScrollY + iVar8) = iVar15;
        }
      }
    }
    goto LAB_0047e91d;
  }
  *(undefined1 *)(param_1 + 5) = 1;
  if (iVar8 != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    pcVar17 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_acc = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0047c3f0(uVar11,uVar10);
    pcVar18 = (code *)EnterCriticalSection;
  }
  (*pcVar18)(&DAT_005a9068);
  /* This PeekPacketChecksumState()'s return (self-cell =
   * g_clientContext + 0x5b85c, per `mov edi,[g_clientContext];
   * add edi,0x5b85c` a few instructions before this point) was
   * previously discarded by the decompile; it survives in a stack spill
   * ([esp+0x14]) that is later reloaded as EncodeOutgoingPacketField's
   * dropped `self` arg below - captured here as uVar19 so that value
   * isn't lost. */
  uVar19 = PeekPacketChecksumState();
  PeekPacketChecksumState();
  cVar20 = '\0';
  (*pcVar17)();
  cVar5 = CheckGuardedBoolAnd(unaff_EBP);
  if (cVar5 != '\0') {
    (*pcVar18)(&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x47e163 (`mov edi,dword ptr [esp+0x14]`) that stack slot holds
     * the value peeked above into uVar19 (self-cell g_clientContext +
     * 0x5b85c), NOT a fixed param_1 offset like the other sites in this
     * function - angr's backward scan resolved it to this spilled stack
     * value. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(uVar19, uVar10);
    (*pcVar17)(&DAT_005a9068);
  }
  (*pcVar18)();
  PeekPacketChecksumState();
  (*pcVar17)(&DAT_005a9068);
  if (cVar7 == '\0') {
LAB_0047e1c1:
    cVar5 = '\0';
    (*pcVar18)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar17)(&DAT_005a9068);
    if (cVar5 != '\0') {
      (*pcVar18)(&DAT_005a9068);
      PeekPacketChecksumState();
      (*pcVar17)(&DAT_005a9068);
      if (cVar5 != '\0') goto LAB_0047e20d;
    }
  }
  else {
    (*pcVar18)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar17)(&DAT_005a9068);
    if (cVar7 == '\0') goto LAB_0047e1c1;
LAB_0047e20d:
    cVar5 = PeekPacketChecksumBool();
    if (cVar5 == '\0') {
      SetGuardedBool(1);
    }
  }
  (*pcVar18)(&DAT_005a9068);
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  (*pcVar17)(&DAT_005a9068);
  if ((cVar20 == '\0') || (cVar5 = CompareChecksumPair(param_1 + 0xed2,param_1 + 0xf5b), cVar5 == '\0')) {
    (*pcVar18)(&DAT_005a9068);
    PeekPacketChecksumState();
    cVar5 = extraout_var;
    PeekPacketChecksumState();
    (*pcVar17)(&DAT_005a9068);
    if ((cVar5 == '\0') ||
       ((cVar5 = CompareChecksumExceeds(param_1 + 0xed2,param_1 + 0xf5b), cVar5 == '\0' ||
        (param_1[0xed1] < 6)))) goto LAB_0047e91d;
  }
  iVar8 = g_clientContext;
  pbVar19 = (byte *)(g_clientContext + 0x62143);
  (*pcVar18)(&DAT_005a9068);
  iVar9 = _rand();
  *pbVar19 = (byte)iVar9;
  iVar9 = _rand();
  bVar2 = *pbVar19;
  *(byte *)(iVar8 + 0x62144) = (byte)iVar9;
  bVar6 = '\x01' << (bVar2 & 7);
  bVar6 = ~bVar6 & (byte)iVar9 | bVar6;
  *(byte *)(iVar8 + 0x62144) = bVar6;
  *(byte *)(iVar8 + 0x62145) = bVar2 + bVar6 + -0x34;
  (*pcVar17)(&DAT_005a9068);
LAB_0047e91d:
  *unaff_FS_OFFSET = uStack_28;
  return;
joined_r0x0047df31:
  if ((*(byte *)(param_1 + 0xf) & 0x80000007) < uVar12) goto LAB_0047df3f;
  if (uVar12 == (*(byte *)(param_1 + 0xf) & 0x80000007)) {
    local_ac8 = iVar8;
    local_ad0 = (int *)EncodeChecksumDeltaShr(param_1 + 0x99,local_ac0,8);
    local_4 = 0;
    EncodeChecksumDeltaShr(param_1 + 0x10,local_89c,8);
    SUBFIELD(local_4,0,undefined1) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad0 = (int *)PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar10 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(iVar8 + 0x24) == 0) {
      *(undefined4 *)(iVar8 + 0x3fa8) = uVar10;
      *(int **)(iVar8 + 0x3fac) = local_ad0;
    }
    local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
    if ((*(int *)(local_89c + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_ad0);
      pcVar17 = (code *)LeaveCriticalSection;
    }
    local_4 = 0xffffffff;
    iVar8 = local_ac8;
    if ((*(int *)(local_ac0 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(&local_ad0);
      pcVar17 = (code *)LeaveCriticalSection;
      iVar8 = local_ac8;
    }
    goto LAB_0047e058;
  }
  iVar8 = *(int *)(iVar8 + 0x10);
  uVar12 = *(uint *)(iVar8 + 8);
  goto joined_r0x0047df31;
LAB_0047df3f:
  iVar8 = 0;
  goto LAB_0047e058;
}

