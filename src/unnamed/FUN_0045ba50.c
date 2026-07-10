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
  undefined4 *unaff_FS_OFFSET;
  int local_ad4;
  int local_ad0 [2];
  undefined1 local_ac8 [8];
  undefined1 local_ac0 [20];
  int local_aac;
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053a482;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uVar2 = FUN_0040a8c0(param_1 + 0x119c,local_678,2);
  local_4 = 0;
  FUN_0040aca0(param_1 + 0xb30,local_454,uVar2);
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004e4340();
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if (local_440 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ad0);
  }
  local_4 = 0xffffffff;
  if (local_664 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ad0);
  }
  uVar2 = FUN_0040a8c0(param_1 + 0x119c,local_ac0,2);
  local_4 = 2;
  FUN_0040aca0(param_1 + 0xb30,local_89c,uVar2);
  SUBFIELD(local_4,0,undefined1) = 3;
  uVar2 = FUN_0040a8c0(param_1 + 0xd54,local_454,2);
  SUBFIELD(local_4,0,undefined1) = 4;
  FUN_0040aca0(param_1 + 0x90c,local_678,uVar2);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004e4340();
  iVar3 = local_664;
  SUBFIELD(local_4,0,undefined1) = 4;
  if (local_664 != 0) {
    FUN_0040a240();
    local_ad0[0] = iVar3;
    FUN_0040b540(local_ac8);
  }
  iVar3 = local_440;
  SUBFIELD(local_4,0,undefined1) = 3;
  if (local_440 != 0) {
    FUN_0040a240();
    local_ad0[0] = iVar3;
    FUN_0040b540(local_ac8);
  }
  iVar3 = local_888;
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if (local_888 != 0) {
    FUN_0040a240();
    local_ad0[0] = iVar3;
    FUN_0040b540(local_ac8);
  }
  iVar3 = local_aac;
  local_4 = 0xffffffff;
  if (local_aac != 0) {
    FUN_0040a240();
    local_ad0[0] = iVar3;
    FUN_0040b540(local_ac8);
  }
  uVar2 = FUN_0040a8c0(param_1 + 0x119c,local_454,2);
  local_4 = 6;
  FUN_0040aca0(param_1 + 0xb30,local_678,uVar2);
  SUBFIELD(local_4,0,undefined1) = 7;
  uVar2 = FUN_0040a8c0(param_1 + 0xd54,local_89c,2);
  SUBFIELD(local_4,0,undefined1) = 8;
  local_ad0[0] = FUN_0040aba0(param_1 + 0x90c,local_ac0,uVar2);
  SUBFIELD(local_4,0,undefined1) = 9;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ad0[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004e4340();
  SUBFIELD(local_4,0,undefined1) = 8;
  local_ad0[0] = local_aac;
  if (local_aac != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  SUBFIELD(local_4,0,undefined1) = 7;
  local_ad0[0] = local_888;
  if (local_888 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),6);
  local_ad0[0] = local_664;
  if (local_664 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  local_4 = 0xffffffff;
  local_ad0[0] = local_440;
  if (local_440 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  PeekPacketChecksumState();
  PeekPacketChecksumState();
  iVar3 = FUN_004f1f10();
  if (0x10e < iVar3) {
    iVar3 = iVar3 + -0x168;
  }
  iVar3 = iVar3 / *(int *)(param_1 + 0xbff0);
  local_ad4 = -iVar3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(local_ad4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040aca0(param_1 + 0x209c,local_ac0,param_1 + 0x1e78);
  local_4 = 10;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_aac != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  if (3 < (int)((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f))) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 == 1) {
    local_ad4 = iVar3;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(local_ad4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0040a5f0(param_1 + 0x4948,local_ac0,local_ad4);
  local_4 = 0xb;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_aac != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 == 0) {
    uVar2 = FUN_0040a500(param_1 + 0x4fb4,local_89c);
    local_4 = 0xc;
    FUN_0040a5f0(uVar2,local_ac0,0xb4);
    SUBFIELD(local_4,0,undefined1) = 0xd;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xc);
    if (local_aac != 0) {
      FUN_0040a240();
      FUN_0040b540(local_ac8);
    }
    local_4 = 0xffffffff;
    if (local_888 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_ac8);
    }
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    FUN_0040a5f0(param_1 + 0x4948,local_ac0,local_ad4);
    local_4 = 0xe;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (local_aac != 0) {
      FUN_0040a240();
      FUN_0040b540(local_ac8);
    }
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\x01') {
      FUN_0040a5f0(param_1 + 0x4948,local_ac0,local_ad4);
      local_4 = 0xf;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_aac != 0) {
        FUN_0040a240();
        FUN_0040b540(local_ac8);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 == 0) {
        uVar2 = FUN_0040a500(param_1 + 0x4d90,local_89c);
        local_4 = 0x10;
        uVar2 = FUN_0040a5f0(uVar2,local_ac0,0xb4);
        SUBFIELD(local_4,0,undefined1) = 0x11;
        EncodeChecksumState(uVar2);
        local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x10);
        FUN_0040a2a0();
        local_4 = 0xffffffff;
        FUN_0040a2a0();
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0xb4 < iVar3) {
      uVar2 = FUN_0040a500(param_1 + 0x60d4,local_89c);
      local_4 = 0x12;
      FUN_0040a5f0(uVar2,local_ac0,0xb4);
      SUBFIELD(local_4,0,undefined1) = 0x13;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0x12);
      if (local_aac != 0) {
        FUN_0040a240();
        FUN_0040b540(local_ac8);
      }
      local_4 = 0xffffffff;
      if (local_888 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_ac8);
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0x5a < iVar3) {
      FUN_0040a6e0(param_1 + 0x60d4,local_ac0,0x5a);
      local_4 = 0x14;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(0x5a - iVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_aac != 0) {
        FUN_0040a240();
        FUN_0040b540(local_ac8);
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar3 < -0x5a) {
      FUN_0040a5f0(param_1 + 0x60d4,local_230,0x5a);
      local_4 = 0x15;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(-0x5a - iVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_21c != 0) {
        FUN_0040a240();
        FUN_0040b540(local_ac8);
      }
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(local_ad4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return;
}

