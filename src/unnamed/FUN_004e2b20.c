/* FUN_004e2b20 - 0x004e2b20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e2b20(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *unaff_FS_OFFSET;
  int local_8b4 [2];
  char local_8a9;
  int local_8a8 [2];
  int local_8a0;
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
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539066;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (-iVar1 < *(int *)(param_1 + 0xefc)) {
    iVar1 = *(int *)(param_1 + 0xf04);
    if (((DAT_0079352c != 0) && (-1 < iVar1)) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(0x106,0x1df);
      }
      else {
        BlitSpriteClipped(iVar1);
      }
    }
    uVar3 = FUN_0040a7d0(param_1 + 0x224,local_89c,2);
    local_4 = 0;
    uVar3 = FUN_0040a5f0(uVar3,local_678,*(undefined4 *)(param_1 + 0xefc));
    SUBFIELD(local_4,0,undefined1) = 1;
    FUN_0040a9c0(uVar3,local_454,0x14);
    SUBFIELD(local_4,0,undefined1) = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SUBFIELD(local_4,0,undefined1) = 1;
    local_8a0 = iVar1 + 0x11;
    local_8a8[0] = local_440;
    if (local_440 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8b4);
    }
    local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
    local_8a8[0] = local_664;
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8b4);
    }
    local_4 = 0xffffffff;
    local_8a8[0] = local_888;
    if (local_888 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8b4);
    }
    FUN_0040a7d0(param_1 + 0x224,local_678,2);
    local_4 = 3;
    local_8a8[0] = FUN_0040a7d0(param_1 + 0x890,local_89c,2);
    SUBFIELD(local_4,0,undefined1) = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8b4[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
    local_8a9 = (iVar1 - local_8b4[0]) + 0x8c <= *(int *)(param_1 + 0xefc);
    local_8b4[0] = local_888;
    if (local_888 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    local_4 = 0xffffffff;
    local_8b4[0] = local_664;
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    if (local_8a9 != '\0') {
      FUN_0040a7d0(param_1 + 0x890,local_89c,2);
      local_4 = 5;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = local_888;
      local_8a0 = iVar2 + 0x11;
      local_4 = 0xffffffff;
      if (local_888 != 0) {
        FUN_0040a240();
        local_8b4[0] = iVar1;
        FUN_0040b540(local_8a8);
      }
    }
    if (((DAT_0079352c != 0) && (-1 < local_8a0)) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(0x10d,500);
      }
      else {
        BlitSpriteClipped(local_8a0);
      }
    }
    uVar3 = FUN_0040a7d0(param_1 + 0x448,local_454,2);
    local_4 = 6;
    uVar3 = FUN_0040a5f0(uVar3,local_678,*(undefined4 *)(param_1 + 0xefc));
    SUBFIELD(local_4,0,undefined1) = 7;
    FUN_0040a9c0(uVar3,local_89c,0x14);
    SUBFIELD(local_4,0,undefined1) = 8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SUBFIELD(local_4,0,undefined1) = 7;
    local_8a0 = iVar1 + 0x11;
    local_8b4[0] = local_888;
    if (local_888 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),6);
    local_8b4[0] = local_664;
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    local_4 = 0xffffffff;
    local_8b4[0] = local_440;
    if (local_440 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    FUN_0040a7d0(param_1 + 0x448,local_678,2);
    local_4 = 9;
    local_8b4[0] = FUN_0040a7d0(param_1 + 0xab4,local_89c,2);
    SUBFIELD(local_4,0,undefined1) = 10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8a8[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),9);
    local_8a9 = (iVar1 - local_8a8[0]) + 0xb4 <= *(int *)(param_1 + 0xefc);
    local_8b4[0] = local_888;
    if (local_888 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    local_4 = 0xffffffff;
    local_8b4[0] = local_664;
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    if (local_8a9 != '\0') {
      FUN_0040a7d0(param_1 + 0xab4,local_89c,2);
      local_4 = 0xb;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = local_888;
      local_8a0 = iVar2 + 0x11;
      local_4 = 0xffffffff;
      if (local_888 != 0) {
        FUN_0040a240();
        local_8b4[0] = iVar1;
        FUN_0040b540(local_8a8);
      }
    }
    if (((DAT_0079352c != 0) && (-1 < local_8a0)) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(0x129,500);
      }
      else {
        BlitSpriteClipped(local_8a0);
      }
    }
    uVar3 = FUN_0040a7d0(param_1 + 0x66c,local_454,2);
    local_4 = 0xc;
    uVar3 = FUN_0040a5f0(uVar3,local_678,*(undefined4 *)(param_1 + 0xefc));
    SUBFIELD(local_4,0,undefined1) = 0xd;
    FUN_0040a9c0(uVar3,local_89c,0x14);
    SUBFIELD(local_4,0,undefined1) = 0xe;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SUBFIELD(local_4,0,undefined1) = 0xd;
    local_8a0 = iVar1 + 0x11;
    local_8b4[0] = local_888;
    if (local_888 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xc);
    local_8b4[0] = local_664;
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    local_4 = 0xffffffff;
    local_8b4[0] = local_440;
    if (local_440 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_8a8);
    }
    FUN_0040a7d0(param_1 + 0x66c,local_678,2);
    local_4 = 0xf;
    local_8b4[0] = FUN_0040a7d0(param_1 + 0xcd8,local_89c,2);
    SUBFIELD(local_4,0,undefined1) = 0x10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8a8[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xf);
    local_8a9 = (iVar1 - local_8a8[0]) + 0xdc <= *(int *)(param_1 + 0xefc);
    if (local_888 != 0) {
      FUN_0040a240();
      local_8b4[0] = local_888;
      FUN_0040b540(local_8a8);
    }
    local_4 = 0xffffffff;
    if (local_664 != 0) {
      FUN_0040a240();
      local_8b4[0] = local_664;
      FUN_0040b540(local_8a8);
    }
    iVar1 = local_8a0;
    if (local_8a9 != '\0') {
      FUN_0040a7d0(param_1 + 0xcd8,local_230,2);
      local_4 = 0x11;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      iVar1 = iVar1 + 0x11;
      if (local_21c != 0) {
        FUN_0040a240();
        local_8b4[0] = local_21c;
        FUN_0040b540(local_8a8);
      }
    }
    if (((DAT_0079352c != 0) && (-1 < iVar1)) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(0x145,500);
        *unaff_FS_OFFSET = local_c;
        return;
      }
      BlitSpriteClipped(iVar1);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

