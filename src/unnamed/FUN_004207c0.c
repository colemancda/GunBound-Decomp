/* FUN_004207c0 - 0x004207c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004207c0(int param_1,uint param_2)

{
  int iVar1;
  int *piVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *unaff_FS_OFFSET;
  int *local_8b8;
  int *local_8ac;
  int *piStack_8a8;
  undefined1 auStack_8a4 [8];
  undefined1 auStack_89c [20];
  int iStack_888;
  undefined1 auStack_678 [20];
  int iStack_664;
  undefined1 auStack_458 [20];
  int *piStack_444;
  undefined1 auStack_234 [20];
  int *piStack_220;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  local_c = *unaff_FS_OFFSET;
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053ce62;
  *unaff_FS_OFFSET = &local_c;
  iVar5 = *(int *)(*(int *)(&DAT_006a7f8c + param_1) + 0x1c);
  uVar8 = *(uint *)(iVar5 + 4);
  iVar1 = iVar5;
  while (uVar8 < 0x186a2) {
    if (uVar8 == 0x186a1) {
      local_8ac = *(int **)(iVar1 + 0x10);
      uVar8 = local_8ac[2];
      goto joined_r0x00420826;
    }
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar8 = *(uint *)(iVar1 + 4);
  }
  local_8ac = (int *)0x0;
LAB_00420846:
  uVar8 = *(uint *)(iVar5 + 4);
  while (uVar8 < 0x186a2) {
    if (uVar8 == 0x186a1) {
      local_8b8 = *(int **)(iVar5 + 0x10);
      uVar8 = local_8b8[2];
      goto joined_r0x00420876;
    }
    iVar5 = *(int *)(iVar5 + 0x1c);
    uVar8 = *(uint *)(iVar5 + 4);
  }
  local_8b8 = (int *)0x0;
LAB_00420896:
  if ((local_8ac != (int *)0x0) && (local_8b8 != (int *)0x0)) {
    cVar3 = PeekPacketChecksumBool();
    piVar2 = local_8b8;
    if (cVar3 == '\0') {
      piVar2 = local_8ac;
      local_8ac = local_8b8;
    }
    local_8b8 = piVar2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)(local_8b8 + 0x242) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8b8 + 0x909) = (byte)iVar5;
    bVar4 = '\x01' << (*(byte *)(local_8b8 + 0x242) & 7);
    bVar4 = ~bVar4 & (byte)iVar5 | bVar4;
    *(byte *)((int)local_8b8 + 0x909) = bVar4;
    *(byte *)((int)local_8b8 + 0x90a) = *(byte *)(local_8b8 + 0x242) + bVar4 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)(local_8ac + 0x242) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0x909) = (byte)iVar5;
    bVar4 = *(byte *)(local_8ac + 0x242) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)((int)local_8ac + 0x909) = bVar4;
    *(byte *)((int)local_8ac + 0x90a) = *(byte *)(local_8ac + 0x242) + bVar4 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = local_8ac[0x2c29];
    if (DAT_00793549 != '\0') {
      if (iVar5 != -1) {
        (**(code **)(**(int **)(DAT_00793554 + iVar5 * 4) + 0xc))();
      }
      if (iVar5 == 0) {
        DAT_00793568 = 0;
      }
    }
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    FUN_00406530();
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0040b490(local_8b8 + 0x20c6,local_8ac + 0x214f);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00406530();
    *(short *)(local_8b8 + 0x2fef) = (short)local_8ac[0x2fef];
    *(char *)(local_8b8 + 0x2b9a) = (char)local_8ac[0x2b9a];
    local_8b8[0x2c25] = local_8ac[0x2c25];
    local_8b8[0x2c26] = local_8ac[0x2c26];
    local_8b8[0x2c27] = local_8ac[0x2c27];
    local_8b8[0x2c28] = local_8ac[0x2c28];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piVar2 = local_8b8 + 0x243;
    local_8b8[0x2c2c] = local_8ac[0x2c2c];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piStack_8a8 = local_8b8 + 0x2cc;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar6);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8b8[0x2ff9] = 200;
    local_8b8[0x2ff8] = 200;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 == 9) {
      uVar6 = EncodeChecksumDeltaSub(piStack_8a8,auStack_89c,200);
      uStack_4 = 0;
      PeekChecksumStateUnderLock(local_8b8 + 0x715);
      uVar8 = (uint)(local_8b8[0x2b8b] != 0);
      uVar9 = local_8b8[2] & 7;
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(piVar2);
      FUN_00437f70(&DAT_006a7f70 + param_1,uVar7,uVar6,uVar9,uVar8);
      uStack_4 = 0xffffffff;
      ScrubChecksumGuard();
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 == 0xe) {
      uVar6 = EncodeChecksumDeltaSub(piStack_8a8,auStack_89c,200);
      uStack_4 = 1;
      PeekChecksumStateUnderLock(local_8b8 + 0x715);
      uVar9 = (uint)(local_8b8[0x2b8b] != 0);
      uVar8 = local_8b8[2] & 7;
      uVar6 = PeekChecksumStateUnderLock(uVar6);
      uVar7 = PeekChecksumStateUnderLock(piVar2);
      FUN_00438100(&DAT_006a7f70 + param_1,uVar7,uVar6,uVar8,uVar9);
      uStack_4 = 0xffffffff;
      ScrubChecksumGuard();
    }
    uVar6 = EncodeChecksumPairSum(local_8b8 + 0x19d1,auStack_678,local_8b8 + 0x1b6c);
    uStack_4 = 2;
    uVar6 = EncodeChecksumDeltaDiv(uVar6,auStack_89c,3);
    uStack_4 = 3;
    cVar3 = FUN_0040b490(local_8b8 + 0x1a5a,uVar6);
    uStack_4 = 2;
    if (iStack_888 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(auStack_8a4);
    }
    uStack_4 = 0xffffffff;
    if (iStack_664 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(auStack_8a4);
    }
    if (cVar3 == '\0') {
      (**(code **)(*local_8b8 + 4))(s_normal_00552230);
    }
    else {
      (**(code **)(*local_8b8 + 4))(s_wnormal_00553618);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)((int)local_8ac + 0xbfbe) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0xbfbf) = (byte)iVar5;
    bVar4 = *(byte *)((int)local_8ac + 0xbfbe) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)((int)local_8ac + 0xbfbf) = bVar4;
    *(byte *)(local_8ac + 0x2ff0) = *(byte *)((int)local_8ac + 0xbfbe) + bVar4 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)((int)local_8ac + 0xbfc1) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0xbfc2) = (byte)iVar5;
    bVar4 = *(byte *)((int)local_8ac + 0xbfc1) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)((int)local_8ac + 0xbfc2) = bVar4;
    *(byte *)((int)local_8ac + 0xbfc3) = *(byte *)((int)local_8ac + 0xbfc1) + bVar4 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)(local_8ac + 0x2ff1) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0xbfc5) = (byte)iVar5;
    bVar4 = *(byte *)(local_8ac + 0x2ff1) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)((int)local_8ac + 0xbfc5) = bVar4;
    *(byte *)((int)local_8ac + 0xbfc6) = *(byte *)(local_8ac + 0x2ff1) + bVar4 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)((int)local_8ac + 0xbfc7) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)(local_8ac + 0x2ff2) = (byte)iVar5;
    bVar4 = *(byte *)((int)local_8ac + 0xbfc7) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)(local_8ac + 0x2ff2) = bVar4;
    *(byte *)((int)local_8ac + 0xbfc9) = *(byte *)((int)local_8ac + 0xbfc7) + bVar4 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)((int)local_8ac + 0xbfca) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0xbfcb) = (byte)iVar5;
    bVar4 = *(byte *)((int)local_8ac + 0xbfca) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)((int)local_8ac + 0xbfcb) = bVar4;
    *(byte *)(local_8ac + 0x2ff3) = *(byte *)((int)local_8ac + 0xbfca) + bVar4 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)((int)local_8ac + 0xbfcd) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0xbfce) = (byte)iVar5;
    bVar4 = *(byte *)((int)local_8ac + 0xbfcd) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)((int)local_8ac + 0xbfce) = bVar4;
    *(byte *)((int)local_8ac + 0xbfcf) = *(byte *)((int)local_8ac + 0xbfcd) + bVar4 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)(local_8ac + 0x2ff4) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0xbfd1) = (byte)iVar5;
    bVar4 = *(byte *)(local_8ac + 0x2ff4) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)((int)local_8ac + 0xbfd1) = bVar4;
    *(byte *)((int)local_8ac + 0xbfd2) = *(byte *)(local_8ac + 0x2ff4) + bVar4 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)(local_8ac + 0x22ea) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0x8ba9) = (byte)iVar5;
    bVar4 = ~('\x01' << (*(byte *)(local_8ac + 0x22ea) & 7)) & (byte)iVar5 |
            '\0' << (*(byte *)(local_8ac + 0x22ea) & 7);
    *(byte *)((int)local_8ac + 0x8ba9) = bVar4;
    *(byte *)((int)local_8ac + 0x8baa) = bVar4 + (char)local_8ac[0x22ea] + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)((int)local_8ac + 0x8bab) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)(local_8ac + 0x22eb) = (byte)iVar5;
    bVar4 = *(byte *)((int)local_8ac + 0x8bab) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)(local_8ac + 0x22eb) = bVar4;
    *(byte *)((int)local_8ac + 0x8bad) = bVar4 + *(char *)((int)local_8ac + 0x8bab) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)((int)local_8ac + 0x8bae) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0x8baf) = (byte)iVar5;
    bVar4 = *(byte *)((int)local_8ac + 0x8bae) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)((int)local_8ac + 0x8baf) = bVar4;
    *(byte *)(local_8ac + 0x22ec) = bVar4 + *(char *)((int)local_8ac + 0x8bae) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)((int)local_8ac + 0x8bb1) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0x8bb2) = (byte)iVar5;
    bVar4 = *(byte *)((int)local_8ac + 0x8bb1) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)((int)local_8ac + 0x8bb2) = bVar4;
    *(byte *)((int)local_8ac + 0x8bb3) = bVar4 + *(char *)((int)local_8ac + 0x8bb1) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)(local_8ac + 0x22ed) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0x8bb5) = (byte)iVar5;
    bVar4 = ~('\x01' << (*(byte *)(local_8ac + 0x22ed) & 7)) & (byte)iVar5 |
            '\0' << (*(byte *)(local_8ac + 0x22ed) & 7);
    *(byte *)((int)local_8ac + 0x8bb5) = bVar4;
    *(byte *)((int)local_8ac + 0x8bb6) = bVar4 + (char)local_8ac[0x22ed] + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)((int)local_8ac + 0x8bb7) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)(local_8ac + 0x22ee) = (byte)iVar5;
    bVar4 = *(byte *)((int)local_8ac + 0x8bb7) & 7;
    bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
    *(byte *)(local_8ac + 0x22ee) = bVar4;
    *(byte *)((int)local_8ac + 0x8bb9) = bVar4 + *(char *)((int)local_8ac + 0x8bb7) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00406530();
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)(local_8ac + 0x22f0) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0x8bc1) = (byte)iVar5;
    bVar4 = ~('\x01' << (*(byte *)(local_8ac + 0x22f0) & 7)) & (byte)iVar5 |
            '\0' << (*(byte *)(local_8ac + 0x22f0) & 7);
    *(byte *)((int)local_8ac + 0x8bc1) = bVar4;
    *(byte *)((int)local_8ac + 0x8bc2) = bVar4 + (char)local_8ac[0x22f0] + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = _rand();
    *(char *)(local_8ac + 0x714) = (char)iVar5;
    iVar5 = _rand();
    *(byte *)((int)local_8ac + 0x1c51) = (byte)iVar5;
    bVar4 = ~('\x01' << (*(byte *)(local_8ac + 0x714) & 7)) & (byte)iVar5 |
            '\0' << (*(byte *)(local_8ac + 0x714) & 7);
    *(byte *)((int)local_8ac + 0x1c51) = bVar4;
    *(byte *)((int)local_8ac + 0x1c52) = bVar4 + (char)local_8ac[0x714] + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined2 *)(local_8ac + 0x2fef) = 0;
    uVar6 = EncodeChecksumPairSum(local_8ac + 0x19d1,auStack_234,local_8ac + 0x1b6c);
    puStack_8 = (undefined1 *)0x4;
    uVar6 = EncodeChecksumDeltaDiv(uVar6,auStack_458,3);
    puStack_8 = 5;
    cVar3 = FUN_0040b490(local_8ac + 0x1a5a,uVar6);
    puStack_8 = (undefined1 *)4;
    if (piStack_444 != (int *)0x0) {
      ScrambleChecksumGuardBytes();
      local_8b8 = piStack_444;
      FUN_0040b540(&piStack_8a8);
      local_8ac = piVar2;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (piStack_220 != (int *)0x0) {
      ScrambleChecksumGuardBytes();
      local_8b8 = piStack_220;
      FUN_0040b540(&piStack_8a8);
      local_8ac = piVar2;
    }
    if (cVar3 == '\0') {
      (**(code **)(*local_8ac + 4))(s_tnormal_00553604);
    }
    else {
      (**(code **)(*local_8ac + 4))(s_twnormal_0055360c);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (param_2 == uVar8) {
      *(int **)(param_1 + 0x621e0) = local_8b8;
    }
    *(int **)(param_1 + 0x621e4) = local_8b8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_004372f0(0,uVar7,uVar6,0x14b5,s_teleport1_005535f8);
  }
  *unaff_FS_OFFSET = local_c;
  return;
joined_r0x00420826:
  if (param_2 < uVar8) goto LAB_00420834;
  if (uVar8 == param_2) goto LAB_00420846;
  local_8ac = (int *)local_8ac[4];
  uVar8 = local_8ac[2];
  goto joined_r0x00420826;
LAB_00420834:
  local_8ac = (int *)0x0;
  goto LAB_00420846;
joined_r0x00420876:
  if (param_2 + 8 < uVar8) goto LAB_00420884;
  if (uVar8 == param_2 + 8) goto LAB_00420896;
  local_8b8 = (int *)local_8b8[4];
  uVar8 = local_8b8[2];
  goto joined_r0x00420876;
LAB_00420884:
  local_8b8 = (int *)0x0;
  goto LAB_00420896;
}

