/* FUN_0045ba50 - 0x0045ba50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0045ba50(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 *unaff_FS_OFFSET;
  int local_ad4;
  int local_ad0 [2];
  undefined1 local_ac8 [8];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053a482;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uVar2 = EncodeChecksumDeltaDiv(param_1 + 0x119c,local_678,2);
  local_4 = 0;
  EncodeChecksumPairDiff(param_1 + 0xb30,local_454,uVar2);
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed at
   * 0x45bb08. y=EAX came from the PeekPacketChecksumState() return just
   * above (dropped by Ghidra, captured here as iVar6); x=EDI came from
   * the second Peek's return just above that (captured as iVar7). */
  FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar7,iVar6);
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ad0);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ad0);
  }
  uVar2 = EncodeChecksumDeltaDiv(param_1 + 0x119c,local_ac0,2);
  local_4 = 2;
  EncodeChecksumPairDiff(param_1 + 0xb30,local_89c,uVar2);
  SUBFIELD(local_4,0,undefined1) = 3;
  uVar2 = EncodeChecksumDeltaDiv(param_1 + 0xd54,local_454,2);
  SUBFIELD(local_4,0,undefined1) = 4;
  EncodeChecksumPairDiff(param_1 + 0x90c,local_678,uVar2);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed at
   * 0x45bc4e. y=EAX came from the PeekPacketChecksumState() return just
   * above (dropped by Ghidra, captured here as iVar8); x=EDI came from
   * the second Peek's return just above that (captured as iVar9). */
  FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),iVar9,iVar8);
  iVar3 = (*(int *)(local_678 + 0x14));
  SUBFIELD(local_4,0,undefined1) = 4;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    local_ad0[0] = iVar3;
    TreeLowerBound(local_ac8);
  }
  iVar3 = (*(int *)(local_454 + 0x14));
  SUBFIELD(local_4,0,undefined1) = 3;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    local_ad0[0] = iVar3;
    TreeLowerBound(local_ac8);
  }
  iVar3 = (*(int *)(local_89c + 0x14));
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    local_ad0[0] = iVar3;
    TreeLowerBound(local_ac8);
  }
  iVar3 = (*(int *)(local_ac0 + 0x14));
  local_4 = 0xffffffff;
  if ((*(int *)(local_ac0 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    local_ad0[0] = iVar3;
    TreeLowerBound(local_ac8);
  }
  uVar2 = EncodeChecksumDeltaDiv(param_1 + 0x119c,local_454,2);
  local_4 = 6;
  EncodeChecksumPairDiff(param_1 + 0xb30,local_678,uVar2);
  SUBFIELD(local_4,0,undefined1) = 7;
  uVar2 = EncodeChecksumDeltaDiv(param_1 + 0xd54,local_89c,2);
  SUBFIELD(local_4,0,undefined1) = 8;
  local_ad0[0] = EncodeChecksumPairSum(param_1 + 0x90c,local_ac0,uVar2);
  SUBFIELD(local_4,0,undefined1) = 9;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ad0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed at
   * 0x45be0b. y=EAX came from the PeekPacketChecksumState() return just
   * above (dropped by Ghidra, captured here as iVar10); x=EDI came from
   * local_ad0[0], which Ghidra already captured a couple lines up. */
  FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),local_ad0[0],iVar10);
  SUBFIELD(local_4,0,undefined1) = 8;
  local_ad0[0] = (*(int *)(local_ac0 + 0x14));
  if ((*(int *)(local_ac0 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  SUBFIELD(local_4,0,undefined1) = 7;
  local_ad0[0] = (*(int *)(local_89c + 0x14));
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),6);
  local_ad0[0] = (*(int *)(local_678 + 0x14));
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  local_4 = 0xffffffff;
  local_ad0[0] = (*(int *)(local_454 + 0x14));
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  iVar3 = CalculateAngleFromDelta();
  if (0x10e < iVar3) {
    iVar3 = iVar3 + -0x168;
  }
  iVar3 = iVar3 / *(int *)(param_1 + 0xbff0);
  local_ad4 = -iVar3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45bf9a
   * (`lea edi,[ebx+0x1e78]`, ebx = this file's own param_1) the cell is
   * param_1+0x1e78. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x1e78, local_ad4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45bfbf
   * (`lea edi,[ebx+0x62f8]`) the cell is param_1+0x62f8 - a fresh cell,
   * distinct from the param_1+0x1e78 one just peeked above. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x62f8, uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumPairDiff(param_1 + 0x209c,local_ac0,param_1 + 0x1e78);
  local_4 = 10;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_ac0 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  if (3 < (int)((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f))) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45c07c
     * (`lea eax,[ebx+0x1e78]` feeding the Peek just above, edi left
     * unchanged since) the cell is param_1+0x1e78 - re-peeked/re-encoded
     * (round-trips the value written at the first call above). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(param_1 + 0x1e78, uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 == 1) {
    local_ad4 = iVar3;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45c0cd
   * (`lea edi,[ebx+0x51d8]`) the cell is param_1+0x51d8. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x51d8, local_ad4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaAdd(param_1 + 0x4948,local_ac0,local_ad4);
  local_4 = 0xb;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45c115
   * (`lea edi,[ebx+0x4fb4]`) the cell is param_1+0x4fb4. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x4fb4, uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_ac0 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 == 0) {
    uVar2 = EncodeChecksumNegate(param_1 + 0x4fb4,local_89c);
    local_4 = 0xc;
    EncodeChecksumDeltaAdd(uVar2,local_ac0,0xb4);
    SUBFIELD(local_4,0,undefined1) = 0xd;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45c1d6
     * (edi left unchanged since `lea edi,[ebx+0x4fb4]` above) the cell is
     * param_1+0x4fb4 - the same cell as the previous Peek/Encode pair
     * (EncodeChecksumNegate's cell arg just above). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(param_1 + 0x4fb4, uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xc);
    if ((*(int *)(local_ac0 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_ac8);
    }
    local_4 = 0xffffffff;
    if ((*(int *)(local_89c + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_ac8);
    }
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    EncodeChecksumDeltaAdd(param_1 + 0x4948,local_ac0,local_ad4);
    local_4 = 0xe;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45c2a7
     * (`lea edi,[ebx+0x60d4]`) the cell is param_1+0x60d4. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(param_1 + 0x60d4, uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if ((*(int *)(local_ac0 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_ac8);
    }
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\x01') {
      EncodeChecksumDeltaAdd(param_1 + 0x4948,local_ac0,local_ad4);
      local_4 = 0xf;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x45c33f (`lea edi,[ebx+0x4d90]`) the cell is param_1+0x4d90.
       * See tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField(param_1 + 0x4d90, uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if ((*(int *)(local_ac0 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_ac8);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 == 0) {
        uVar2 = EncodeChecksumNegate(param_1 + 0x4d90,local_89c);
        local_4 = 0x10;
        uVar2 = EncodeChecksumDeltaAdd(uVar2,local_ac0,0xb4);
        SUBFIELD(local_4,0,undefined1) = 0x11;
        EncodeChecksumState(uVar2);
        local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x10);
        ScrubChecksumGuard();
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0xb4 < iVar3) {
      uVar2 = EncodeChecksumNegate(param_1 + 0x60d4,local_89c);
      local_4 = 0x12;
      EncodeChecksumDeltaAdd(uVar2,local_ac0,0xb4);
      SUBFIELD(local_4,0,undefined1) = 0x13;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x45c48e (edi left unchanged since `lea edi,[ebx+0x60d4]` at
       * 0x45c41e) the cell is param_1+0x60d4 - reused from the
       * PeekPacketChecksumState()/EncodeChecksumNegate pair above. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField(param_1 + 0x60d4, uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x12);
      if ((*(int *)(local_ac0 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_ac8);
      }
      local_4 = 0xffffffff;
      if ((*(int *)(local_89c + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_ac8);
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0x5a < iVar3) {
      EncodeChecksumDeltaSub(param_1 + 0x60d4,local_ac0,0x5a);
      local_4 = 0x14;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x45c58d (edi left unchanged since `lea edi,[ebx+0x60d4]` at
       * 0x45c51b) the cell is param_1+0x60d4 - reused from the
       * PeekPacketChecksumState()/EncodeChecksumDeltaSub pair above.
       * See tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField(param_1 + 0x60d4, 0x5a - iVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if ((*(int *)(local_ac0 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_ac8);
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 < -0x5a) {
      EncodeChecksumDeltaAdd(param_1 + 0x60d4,local_230,0x5a);
      local_4 = 0x15;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x45c652 (edi left unchanged since `lea edi,[ebx+0x60d4]` at
       * 0x45c5dd) the cell is param_1+0x60d4 - reused from the
       * PeekPacketChecksumState()/EncodeChecksumDeltaAdd pair above.
       * See tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField(param_1 + 0x60d4, -0x5a - iVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if ((*(int *)(local_230 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_ac8);
      }
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45c6b0
   * (`lea edi,[ebx+0x4b6c]`) the cell is param_1+0x4b6c. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x4b6c, local_ad4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return;
}

