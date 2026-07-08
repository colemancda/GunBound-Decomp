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
  cVar1 = FUN_004065a0();
  if ((cVar1 != '\0') || ((char)param_1[5] == '\x01')) goto LAB_004798f4;
  local_2d0c = 0;
  FUN_0040a6e0(param_1 + 0x97,local_2028,param_2);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_2 = PeekPacketChecksumState();
  local_2d10 = param_2;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_2d18._0_4_ = local_2014;
  local_2d18._0_4_ = local_2014;
  if (local_2014 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_2d20);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 == 0) {
    uVar3 = FUN_0040a8c0(unaff_EDI + 0x24c0,local_2470,2);
    local_4 = 1;
    uVar4 = FUN_0040a4d0(&DAT_00e9ba40);
    uVar3 = FUN_0040a5f0(uVar3,local_28b8,uVar4);
    local_4._0_1_ = 2;
    iVar2 = FUN_0040a4d0(uVar3);
    local_4 = CONCAT31(local_4._1_3_,1);
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    iVar5 = FUN_0040a4d0(unaff_EDI + 0x2b2c);
    if (iVar5 < 1) {
      local_2d18._0_4_ = 1;
    }
    else {
      local_2d18._0_4_ = FUN_0040a4d0(unaff_EDI + 0x2b2c);
    }
    iVar5 = FUN_0040a4d0(&DAT_00796aa0);
    param_2 = (iVar5 * local_2d10) / local_2d18._0_4_;
    local_2d10 = iVar2;
  }
  else if (iVar2 == 1) {
    uVar3 = FUN_0040a8c0(unaff_EDI + 0x26e4,local_224c,2);
    local_4 = 3;
    uVar4 = FUN_0040a4d0(&DAT_00e9ba40);
    uVar3 = FUN_0040a5f0(uVar3,local_1e04,uVar4);
    local_4._0_1_ = 4;
    iVar2 = FUN_0040a4d0(uVar3);
    local_4 = CONCAT31(local_4._1_3_,3);
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    iVar5 = FUN_0040a4d0(unaff_EDI + 0x2d50);
    if (iVar5 < 1) {
      local_2d18._0_4_ = 1;
    }
    else {
      local_2d18._0_4_ = FUN_0040a4d0(unaff_EDI + 0x2d50);
    }
    iVar5 = FUN_0040a4d0(&DAT_00796aa0);
    param_2 = (iVar5 * local_2d10) / local_2d18._0_4_;
    local_2d10 = iVar2;
  }
  else if (iVar2 == 2) {
    uVar3 = FUN_0040a8c0(unaff_EDI + 0x2908,local_2694,2);
    local_4 = 5;
    uVar4 = FUN_0040a4d0(&DAT_00e9ba40);
    uVar3 = FUN_0040a5f0(uVar3,local_2adc,uVar4);
    local_4._0_1_ = 6;
    iVar2 = FUN_0040a4d0(uVar3);
    local_4 = CONCAT31(local_4._1_3_,5);
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    iVar5 = FUN_0040a4d0(unaff_EDI + 0x2f74);
    if (iVar5 < 1) {
      local_2d18._0_4_ = 1;
    }
    else {
      local_2d18._0_4_ = FUN_0040a4d0(unaff_EDI + 0x2f74);
    }
    iVar5 = FUN_0040a4d0(&DAT_00796aa0);
    param_2 = (iVar5 * local_2d10) / local_2d18._0_4_;
    local_2d10 = iVar2;
  }
  iVar2 = local_2d10 * local_2d10;
  local_2d10 = iVar2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_2d18._0_4_ = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = FUN_0040a6e0(param_1 + 0x120,local_28b8,local_2d18._0_4_);
  local_4 = 7;
  local_2d18._0_4_ = FUN_0040a6e0(uVar3,local_2470,param_3);
  local_4._0_1_ = 8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_2d20[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(local_4._1_3_,7);
  if (local_245c != 0) {
    FUN_0040a240();
    FUN_0040b540(local_2d08);
    iVar2 = local_2d10;
  }
  local_4 = 0xffffffff;
  local_2d18 = (double)CONCAT44(local_2d18._4_4_,local_28a4);
  if (local_28a4 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_2d08);
    iVar2 = local_2d10;
  }
  iVar5 = param_2 * param_2 + local_2d20[0] * local_2d20[0];
  if (iVar5 < iVar2) {
    iVar2 = FUN_0040a4d0(g_clientContext + 0x475c8);
    iVar2 = FUN_0040a4d0((iVar2 * 0xb + (uint)*(byte *)(g_clientContext + 0x475c4)) * 0x7d28 + 0x1a1f48
                         + g_clientContext);
    if (iVar2 == 0) {
      local_2d20[0] = FUN_0040a8c0(unaff_EDI + 0x24c0,local_f08,2);
      local_4 = 9;
      uVar3 = FUN_0040a4d0(&DAT_00e9ba40);
      local_2d20[0] = FUN_0040a5f0(local_2d20[0],local_1350,uVar3);
      local_4._0_1_ = 10;
      uVar3 = FUN_0040a8c0(unaff_EDI + 0x24c0,local_1798,2);
      local_4._0_1_ = 0xb;
      uVar4 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar3 = FUN_0040a5f0(uVar3,local_ce4,uVar4);
      local_4._0_1_ = 0xc;
      local_2d20[0] = FUN_0040a4d0(local_2d20[0]);
      local_2d18 = ((double)local_2d20[0] - SQRT((double)iVar5)) * _DAT_00558078;
      local_2d20[0] = FUN_0040a4d0(uVar3);
      uVar3 = FUN_0053753c();
      local_4._0_1_ = 0xb;
      FUN_0040a2a0();
      local_4._0_1_ = 10;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,9);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      uVar3 = FUN_0040a7d0(unaff_EDI + 0x1e54,local_2d00,uVar3);
      local_4 = 0xd;
      uVar3 = FUN_0040a8c0(uVar3,local_1be0,1000);
      local_4._0_1_ = 0xe;
      local_2d0c = FUN_0040a4d0(uVar3);
      local_4 = CONCAT31(local_4._1_3_,0xd);
      FUN_0040a2a0();
    }
    else if (iVar2 == 1) {
      local_2d20[0] = FUN_0040a8c0(unaff_EDI + 0x26e4,local_454,2);
      local_4 = 0xf;
      uVar3 = FUN_0040a4d0(&DAT_00e9ba40);
      local_2d20[0] = FUN_0040a5f0(local_2d20[0],local_1574,uVar3);
      local_4._0_1_ = 0x10;
      uVar3 = FUN_0040a8c0(unaff_EDI + 0x26e4,local_678,2);
      local_4._0_1_ = 0x11;
      uVar4 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar3 = FUN_0040a5f0(uVar3,local_ac0,uVar4);
      local_4._0_1_ = 0x12;
      local_2d20[0] = FUN_0040a4d0(local_2d20[0]);
      local_2d18 = ((double)local_2d20[0] - SQRT((double)iVar5)) * _DAT_00558078;
      local_2d20[0] = FUN_0040a4d0(uVar3);
      uVar3 = FUN_0053753c();
      local_4._0_1_ = 0x11;
      FUN_0040a2a0();
      local_4._0_1_ = 0x10;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0xf);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      uVar3 = FUN_0040a7d0(unaff_EDI + 0x2078,local_89c,uVar3);
      local_4 = 0x13;
      uVar3 = FUN_0040a8c0(uVar3,local_112c,1000);
      local_4._0_1_ = 0x14;
      local_2d0c = FUN_0040a4d0(uVar3);
      local_4 = CONCAT31(local_4._1_3_,0x13);
      FUN_0040a2a0();
    }
    else {
      if (iVar2 != 2) goto LAB_00479655;
      local_2d20[0] = FUN_0040a8c0(unaff_EDI + 0x2908,local_2adc,2);
      local_4 = 0x15;
      uVar3 = FUN_0040a4d0(&DAT_00e9ba40);
      local_2d20[0] = FUN_0040a5f0(local_2d20[0],local_2694,uVar3);
      local_4._0_1_ = 0x16;
      uVar3 = FUN_0040a8c0(unaff_EDI + 0x2908,local_1e04,2);
      local_4._0_1_ = 0x17;
      uVar4 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar3 = FUN_0040a5f0(uVar3,local_224c,uVar4);
      local_4._0_1_ = 0x18;
      local_2d20[0] = FUN_0040a4d0(local_2d20[0]);
      local_2d18 = ((double)local_2d20[0] - SQRT((double)iVar5)) * _DAT_00558078;
      local_2d20[0] = FUN_0040a4d0(uVar3);
      uVar3 = FUN_0053753c();
      local_4._0_1_ = 0x17;
      FUN_0040a2a0();
      local_4._0_1_ = 0x16;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x15);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      uVar3 = FUN_0040a7d0(unaff_EDI + 0x229c,local_19bc,uVar3);
      local_4 = 0x19;
      uVar3 = FUN_0040a8c0(uVar3,local_2028,1000);
      local_4._0_1_ = 0x1a;
      local_2d0c = FUN_0040a4d0(uVar3);
      local_4 = CONCAT31(local_4._1_3_,0x19);
      FUN_0040a2a0();
    }
    local_4 = 0xffffffff;
    FUN_0040a2a0();
  }
LAB_00479655:
  uVar3 = FUN_0040a7d0(unaff_EDI + 0x17e4,local_1be0,local_2d0c);
  local_4 = 0x1b;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_2d20[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a8c0(uVar3,local_2d00,local_2d20[0]);
  local_4._0_1_ = 0x1c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_2d10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(local_4._1_3_,0x1b);
  local_2d20[0] = local_2cec;
  if (local_2cec != 0) {
    FUN_0040a240();
    FUN_0040b540(local_2d08);
  }
  local_4 = 0xffffffff;
  local_2d20[0] = local_1bcc;
  if (local_1bcc != 0) {
    FUN_0040a240();
    FUN_0040b540(local_2d08);
  }
  FUN_0040a8c0(unaff_EDI + 0x15c0,local_2d00,2);
  local_4 = 0x1d;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  local_2d18 = (double)CONCAT44(local_2d18._4_4_,uVar3);
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
  iVar5 = ((iVar2 + local_2d20[0] + local_2d18._0_4_) * local_2d10) / iVar5;
  local_4 = 0xffffffff;
  local_2d0c = iVar5;
  if (local_2cec != 0) {
    FUN_0040a240();
    local_2d20[0] = local_2cec;
    FUN_0040b540(local_2d08);
  }
  if (0 < iVar5) {
    AddToPacketChecksum(iVar5);
    uVar3 = FUN_0040a6e0(param_1 + 0x120,local_230,0xf);
    local_4 = 0x1e;
    uVar3 = FUN_0040a4d0(uVar3);
    uVar4 = FUN_0040a4d0(param_1 + 0x97);
    FUN_00436860(uVar4,uVar3);
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    (**(code **)(*param_1 + 4))(s_damage_00555cc0);
    cVar1 = FUN_004065a0();
    if ((cVar1 == '\x01') && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
      AddToPacketChecksum(local_2d0c);
    }
    QueueOutgoingPacketField(*(undefined1 *)(unaff_EDI + 0x3c));
  }
LAB_004798f4:
  *unaff_FS_OFFSET = local_c;
  return;
}

