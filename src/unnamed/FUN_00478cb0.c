/* FUN_00478cb0 - 0x00478cb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00478cb0(int *param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  int local_2d20 [2];
  double local_2d18;
  int local_2d10;
  int local_2d0c;
  undefined1 local_2d08 [8];
  undefined1 local_2d00 [20];
  int local_2cec;
  undefined1 local_2adc [548];
  undefined1 local_28b8 [20];
  int local_28a4;
  undefined1 local_2694 [548];
  undefined1 local_2470 [20];
  int local_245c;
  undefined1 local_224c [548];
  undefined1 local_2028 [20];
  int local_2014;
  undefined1 local_1e04 [548];
  undefined1 local_1be0 [20];
  int local_1bcc;
  undefined1 local_19bc [548];
  undefined1 local_1798 [548];
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
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539d55;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x478ccf;
  cVar1 = PeekPacketChecksumBool();
  if ((cVar1 != '\0') || ((char)param_1[5] == '\x01')) goto LAB_004798f4;
  local_2d0c = 0;
  EncodeChecksumDeltaSub(param_1 + 0x97,local_2028,param_2);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_2 = PeekPacketChecksumState();
  local_2d10 = param_2;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  SUBFIELD(local_2d18,0,undefined4) = local_2014;
  SUBFIELD(local_2d18,0,undefined4) = local_2014;
  if (local_2014 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_2d20);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 == 0) {
    uVar3 = EncodeChecksumDeltaDiv(unaff_EDI + 0x24c0,local_2470,2);
    local_4 = 1;
    uVar4 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
    uVar3 = EncodeChecksumDeltaAdd(uVar3,local_28b8,uVar4);
    SUBFIELD(local_4,0,undefined1) = 2;
    iVar2 = PeekChecksumStateUnderLock(uVar3);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    iVar5 = PeekChecksumStateUnderLock(unaff_EDI + 0x2b2c);
    if (iVar5 < 1) {
      SUBFIELD(local_2d18,0,undefined4) = 1;
    }
    else {
      SUBFIELD(local_2d18,0,undefined4) = PeekChecksumStateUnderLock(unaff_EDI + 0x2b2c);
    }
    iVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
    param_2 = (iVar5 * local_2d10) / SUBFIELD(local_2d18,0,undefined4);
    local_2d10 = iVar2;
  }
  else if (iVar2 == 1) {
    uVar3 = EncodeChecksumDeltaDiv(unaff_EDI + 0x26e4,local_224c,2);
    local_4 = 3;
    uVar4 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
    uVar3 = EncodeChecksumDeltaAdd(uVar3,local_1e04,uVar4);
    SUBFIELD(local_4,0,undefined1) = 4;
    iVar2 = PeekChecksumStateUnderLock(uVar3);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    iVar5 = PeekChecksumStateUnderLock(unaff_EDI + 0x2d50);
    if (iVar5 < 1) {
      SUBFIELD(local_2d18,0,undefined4) = 1;
    }
    else {
      SUBFIELD(local_2d18,0,undefined4) = PeekChecksumStateUnderLock(unaff_EDI + 0x2d50);
    }
    iVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
    param_2 = (iVar5 * local_2d10) / SUBFIELD(local_2d18,0,undefined4);
    local_2d10 = iVar2;
  }
  else if (iVar2 == 2) {
    uVar3 = EncodeChecksumDeltaDiv(unaff_EDI + 0x2908,local_2694,2);
    local_4 = 5;
    uVar4 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
    uVar3 = EncodeChecksumDeltaAdd(uVar3,local_2adc,uVar4);
    SUBFIELD(local_4,0,undefined1) = 6;
    iVar2 = PeekChecksumStateUnderLock(uVar3);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),5);
    ScrubChecksumGuard();
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    iVar5 = PeekChecksumStateUnderLock(unaff_EDI + 0x2f74);
    if (iVar5 < 1) {
      SUBFIELD(local_2d18,0,undefined4) = 1;
    }
    else {
      SUBFIELD(local_2d18,0,undefined4) = PeekChecksumStateUnderLock(unaff_EDI + 0x2f74);
    }
    iVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
    param_2 = (iVar5 * local_2d10) / SUBFIELD(local_2d18,0,undefined4);
    local_2d10 = iVar2;
  }
  iVar2 = local_2d10 * local_2d10;
  local_2d10 = iVar2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  SUBFIELD(local_2d18,0,undefined4) = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = EncodeChecksumDeltaSub(param_1 + 0x120,local_28b8,SUBFIELD(local_2d18,0,undefined4));
  local_4 = 7;
  SUBFIELD(local_2d18,0,undefined4) = EncodeChecksumDeltaSub(uVar3,local_2470,param_3);
  SUBFIELD(local_4,0,undefined1) = 8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_2d20[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
  if (local_245c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_2d08);
    iVar2 = local_2d10;
  }
  local_4 = 0xffffffff;
  local_2d18 = (double)CONCAT44(SUBFIELD(local_2d18,4,undefined4),local_28a4);
  if (local_28a4 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_2d08);
    iVar2 = local_2d10;
  }
  iVar5 = param_2 * param_2 + local_2d20[0] * local_2d20[0];
  if (iVar5 < iVar2) {
    iVar2 = PeekChecksumStateUnderLock(g_clientContext + 0x475c8);
    iVar2 = PeekChecksumStateUnderLock((iVar2 * 0xb + (uint)*(byte *)(g_clientContext + 0x475c4)) * 0x7d28 + 0x1a1f48
                         + g_clientContext);
    if (iVar2 == 0) {
      local_2d20[0] = EncodeChecksumDeltaDiv(unaff_EDI + 0x24c0,local_f08,2);
      local_4 = 9;
      uVar3 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      local_2d20[0] = EncodeChecksumDeltaAdd(local_2d20[0],local_1350,uVar3);
      SUBFIELD(local_4,0,undefined1) = 10;
      uVar3 = EncodeChecksumDeltaDiv(unaff_EDI + 0x24c0,local_1798,2);
      SUBFIELD(local_4,0,undefined1) = 0xb;
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      uVar3 = EncodeChecksumDeltaAdd(uVar3,local_ce4,uVar4);
      SUBFIELD(local_4,0,undefined1) = 0xc;
      local_2d20[0] = PeekChecksumStateUnderLock(local_2d20[0]);
      local_2d18 = ((double)local_2d20[0] - SQRT((double)iVar5)) * _DAT_00558078;
      local_2d20[0] = PeekChecksumStateUnderLock(uVar3);
      uVar3 = FloatToInt64();
      SUBFIELD(local_4,0,undefined1) = 0xb;
      ScrubChecksumGuard();
      SUBFIELD(local_4,0,undefined1) = 10;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),9);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar3 = EncodeChecksumDeltaMul(unaff_EDI + 0x1e54,local_2d00,uVar3);
      local_4 = 0xd;
      uVar3 = EncodeChecksumDeltaDiv(uVar3,local_1be0,1000);
      SUBFIELD(local_4,0,undefined1) = 0xe;
      local_2d0c = PeekChecksumStateUnderLock(uVar3);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xd);
      ScrubChecksumGuard();
    }
    else if (iVar2 == 1) {
      local_2d20[0] = EncodeChecksumDeltaDiv(unaff_EDI + 0x26e4,local_454,2);
      local_4 = 0xf;
      uVar3 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      local_2d20[0] = EncodeChecksumDeltaAdd(local_2d20[0],local_1574,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x10;
      uVar3 = EncodeChecksumDeltaDiv(unaff_EDI + 0x26e4,local_678,2);
      SUBFIELD(local_4,0,undefined1) = 0x11;
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      uVar3 = EncodeChecksumDeltaAdd(uVar3,local_ac0,uVar4);
      SUBFIELD(local_4,0,undefined1) = 0x12;
      local_2d20[0] = PeekChecksumStateUnderLock(local_2d20[0]);
      local_2d18 = ((double)local_2d20[0] - SQRT((double)iVar5)) * _DAT_00558078;
      local_2d20[0] = PeekChecksumStateUnderLock(uVar3);
      uVar3 = FloatToInt64();
      SUBFIELD(local_4,0,undefined1) = 0x11;
      ScrubChecksumGuard();
      SUBFIELD(local_4,0,undefined1) = 0x10;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xf);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar3 = EncodeChecksumDeltaMul(unaff_EDI + 0x2078,local_89c,uVar3);
      local_4 = 0x13;
      uVar3 = EncodeChecksumDeltaDiv(uVar3,local_112c,1000);
      SUBFIELD(local_4,0,undefined1) = 0x14;
      local_2d0c = PeekChecksumStateUnderLock(uVar3);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x13);
      ScrubChecksumGuard();
    }
    else {
      if (iVar2 != 2) goto LAB_00479655;
      local_2d20[0] = EncodeChecksumDeltaDiv(unaff_EDI + 0x2908,local_2adc,2);
      local_4 = 0x15;
      uVar3 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      local_2d20[0] = EncodeChecksumDeltaAdd(local_2d20[0],local_2694,uVar3);
      SUBFIELD(local_4,0,undefined1) = 0x16;
      uVar3 = EncodeChecksumDeltaDiv(unaff_EDI + 0x2908,local_1e04,2);
      SUBFIELD(local_4,0,undefined1) = 0x17;
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
      uVar3 = EncodeChecksumDeltaAdd(uVar3,local_224c,uVar4);
      SUBFIELD(local_4,0,undefined1) = 0x18;
      local_2d20[0] = PeekChecksumStateUnderLock(local_2d20[0]);
      local_2d18 = ((double)local_2d20[0] - SQRT((double)iVar5)) * _DAT_00558078;
      local_2d20[0] = PeekChecksumStateUnderLock(uVar3);
      uVar3 = FloatToInt64();
      SUBFIELD(local_4,0,undefined1) = 0x17;
      ScrubChecksumGuard();
      SUBFIELD(local_4,0,undefined1) = 0x16;
      ScrubChecksumGuard();
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x15);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar3 = EncodeChecksumDeltaMul(unaff_EDI + 0x229c,local_19bc,uVar3);
      local_4 = 0x19;
      uVar3 = EncodeChecksumDeltaDiv(uVar3,local_2028,1000);
      SUBFIELD(local_4,0,undefined1) = 0x1a;
      local_2d0c = PeekChecksumStateUnderLock(uVar3);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x19);
      ScrubChecksumGuard();
    }
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
  }
LAB_00479655:
  uVar3 = EncodeChecksumDeltaMul(unaff_EDI + 0x17e4,local_1be0,local_2d0c);
  local_4 = 0x1b;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_2d20[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaDiv(uVar3,local_2d00,local_2d20[0]);
  SUBFIELD(local_4,0,undefined1) = 0x1c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_2d10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x1b);
  local_2d20[0] = local_2cec;
  if (local_2cec != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_2d08);
  }
  local_4 = 0xffffffff;
  local_2d20[0] = local_1bcc;
  if (local_1bcc != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_2d08);
  }
  EncodeChecksumDeltaDiv(unaff_EDI + 0x15c0,local_2d00,2);
  local_4 = 0x1d;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  local_2d18 = (double)CONCAT44(SUBFIELD(local_2d18,4,undefined4),uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_2d20[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = ((iVar2 + local_2d20[0] + SUBFIELD(local_2d18,0,undefined4)) * local_2d10) / iVar5;
  local_4 = 0xffffffff;
  local_2d0c = iVar5;
  if (local_2cec != 0) {
    ScrambleChecksumGuardBytes();
    local_2d20[0] = local_2cec;
    TreeLowerBound(local_2d08);
  }
  if (0 < iVar5) {
    AddToPacketChecksum(iVar5);
    uVar3 = EncodeChecksumDeltaSub(param_1 + 0x120,local_230,0xf);
    local_4 = 0x1e;
    uVar3 = PeekChecksumStateUnderLock(uVar3);
    uVar4 = PeekChecksumStateUnderLock(param_1 + 0x97);
    FUN_00436860(uVar4,uVar3);
    local_4 = 0xffffffff;
    ScrubChecksumGuard();
    (**(code **)(*param_1 + 4))(s_damage_00555cc0);
    cVar1 = PeekPacketChecksumBool();
    if ((cVar1 == '\x01') && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
      AddToPacketChecksum(local_2d0c);
    }
    QueueOutgoingPacketField(*(undefined1 *)(unaff_EDI + 0x3c));
  }
LAB_004798f4:
  *unaff_FS_OFFSET = local_c;
  return;
}

