/* FUN_004e2b20 - 0x004e2b20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 13 argless PeekPacketChecksumState() calls (peek status
 * "clean", 13 C : 13 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x4e2b20-0x4e3464.
 *
 * All but one cell is a CHAINED RETURN: this function is three near
 * identical rounds of DeltaMul -> DeltaAdd -> DeltaMod / DeltaMul ->
 * DeltaMul, and each Peek re-reads the dest cell one of those helpers
 * just returned in EAX.  Nine of the twelve helper returns are discarded
 * by the decompile and are now captured in a new uVar4; the other three
 * are already assigned (local_8a8[0] at ~line 76, local_8b4[0] at ~150
 * and ~224) and those Peeks use the existing variable, leaving the
 * statements untouched.
 *
 * Pairing each Peek with the RIGHT helper matters and is not positional:
 * within a round two DeltaMuls run back to back (0x4e2d00 then 0x4e2d20)
 * and the first Peek re-reads the FIRST one's return via EBX while the
 * second Peek re-reads the SECOND one's, spilled to a frame slot.  The
 * remaining cell is the &DAT_00796aa0 read at 0x4e2b52, before the
 * function's main branch.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e2b20(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *unaff_FS_OFFSET;
  int local_8b4 [2];
  char local_8a9;
  int local_8a8 [2];
  int local_8a0;
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539066;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)&DAT_00796aa0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (-iVar1 < *(int *)(param_1 + 0xefc)) {
    iVar1 = *(int *)(param_1 + 0xf04);
    if (((DAT_0079352c != 0) && (-1 < iVar1)) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2328,iVar1), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar1,0x106,0x1df,0x2328);
      }
      else {
        BlitSpriteClipped(iVar1,0x106,0x1df,0x2328);
      }
    }
    uVar3 = EncodeChecksumDeltaMul(param_1 + 0x224,local_89c,2);
    local_4 = 0;
    uVar3 = EncodeChecksumDeltaAdd(uVar3,local_678,*(undefined4 *)(param_1 + 0xefc));
    SUBFIELD(local_4,0,undefined1) = 1;
    uVar4 = EncodeChecksumDeltaMod(uVar3,local_454,0x14);
    SUBFIELD(local_4,0,undefined1) = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SUBFIELD(local_4,0,undefined1) = 1;
    local_8a0 = iVar1 + 0x11;
    local_8a8[0] = (*(int *)(local_454 + 0x14));
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8b4);
    }
    local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
    local_8a8[0] = (*(int *)(local_678 + 0x14));
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8b4);
    }
    local_4 = 0xffffffff;
    local_8a8[0] = (*(int *)(local_89c + 0x14));
    if ((*(int *)(local_89c + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8b4);
    }
    uVar4 = EncodeChecksumDeltaMul(param_1 + 0x224,local_678,2);
    local_4 = 3;
    local_8a8[0] = EncodeChecksumDeltaMul(param_1 + 0x890,local_89c,2);
    SUBFIELD(local_4,0,undefined1) = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8b4[0] = PeekPacketChecksumState((void *)uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)local_8a8[0]);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
    local_8a9 = (iVar1 - local_8b4[0]) + 0x8c <= *(int *)(param_1 + 0xefc);
    local_8b4[0] = (*(int *)(local_89c + 0x14));
    if ((*(int *)(local_89c + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    local_4 = 0xffffffff;
    local_8b4[0] = (*(int *)(local_678 + 0x14));
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    if (local_8a9 != '\0') {
      uVar4 = EncodeChecksumDeltaMul(param_1 + 0x890,local_89c,2);
      local_4 = 5;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState((void *)uVar4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = (*(int *)(local_89c + 0x14));
      local_8a0 = iVar2 + 0x11;
      local_4 = 0xffffffff;
      if ((*(int *)(local_89c + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        local_8b4[0] = iVar1;
        TreeLowerBound(local_8a8);
      }
    }
    if (((DAT_0079352c != 0) && (-1 < local_8a0)) && (iVar1 = FindSpriteFrame((int)&DAT_00ea0e18,0x2328,local_8a0), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(local_8a0,0x10d,500,0x2328);
      }
      else {
        BlitSpriteClipped(local_8a0,0x10d,500,0x2328);
      }
    }
    uVar3 = EncodeChecksumDeltaMul(param_1 + 0x448,local_454,2);
    local_4 = 6;
    uVar3 = EncodeChecksumDeltaAdd(uVar3,local_678,*(undefined4 *)(param_1 + 0xefc));
    SUBFIELD(local_4,0,undefined1) = 7;
    uVar4 = EncodeChecksumDeltaMod(uVar3,local_89c,0x14);
    SUBFIELD(local_4,0,undefined1) = 8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SUBFIELD(local_4,0,undefined1) = 7;
    local_8a0 = iVar1 + 0x11;
    local_8b4[0] = (*(int *)(local_89c + 0x14));
    if ((*(int *)(local_89c + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),6);
    local_8b4[0] = (*(int *)(local_678 + 0x14));
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    local_4 = 0xffffffff;
    local_8b4[0] = (*(int *)(local_454 + 0x14));
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    uVar4 = EncodeChecksumDeltaMul(param_1 + 0x448,local_678,2);
    local_4 = 9;
    local_8b4[0] = EncodeChecksumDeltaMul(param_1 + 0xab4,local_89c,2);
    SUBFIELD(local_4,0,undefined1) = 10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8a8[0] = PeekPacketChecksumState((void *)uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)local_8b4[0]);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),9);
    local_8a9 = (iVar1 - local_8a8[0]) + 0xb4 <= *(int *)(param_1 + 0xefc);
    local_8b4[0] = (*(int *)(local_89c + 0x14));
    if ((*(int *)(local_89c + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    local_4 = 0xffffffff;
    local_8b4[0] = (*(int *)(local_678 + 0x14));
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    if (local_8a9 != '\0') {
      uVar4 = EncodeChecksumDeltaMul(param_1 + 0xab4,local_89c,2);
      local_4 = 0xb;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState((void *)uVar4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = (*(int *)(local_89c + 0x14));
      local_8a0 = iVar2 + 0x11;
      local_4 = 0xffffffff;
      if ((*(int *)(local_89c + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        local_8b4[0] = iVar1;
        TreeLowerBound(local_8a8);
      }
    }
    if (((DAT_0079352c != 0) && (-1 < local_8a0)) && (iVar1 = FindSpriteFrame((int)&DAT_00ea0e18,0x2328,local_8a0), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(local_8a0,0x129,500,0x2328);
      }
      else {
        BlitSpriteClipped(local_8a0,0x129,500,0x2328);
      }
    }
    uVar3 = EncodeChecksumDeltaMul(param_1 + 0x66c,local_454,2);
    local_4 = 0xc;
    uVar3 = EncodeChecksumDeltaAdd(uVar3,local_678,*(undefined4 *)(param_1 + 0xefc));
    SUBFIELD(local_4,0,undefined1) = 0xd;
    uVar4 = EncodeChecksumDeltaMod(uVar3,local_89c,0x14);
    SUBFIELD(local_4,0,undefined1) = 0xe;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SUBFIELD(local_4,0,undefined1) = 0xd;
    local_8a0 = iVar1 + 0x11;
    local_8b4[0] = (*(int *)(local_89c + 0x14));
    if ((*(int *)(local_89c + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xc);
    local_8b4[0] = (*(int *)(local_678 + 0x14));
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    local_4 = 0xffffffff;
    local_8b4[0] = (*(int *)(local_454 + 0x14));
    if ((*(int *)(local_454 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_8a8);
    }
    uVar4 = EncodeChecksumDeltaMul(param_1 + 0x66c,local_678,2);
    local_4 = 0xf;
    local_8b4[0] = EncodeChecksumDeltaMul(param_1 + 0xcd8,local_89c,2);
    SUBFIELD(local_4,0,undefined1) = 0x10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8a8[0] = PeekPacketChecksumState((void *)uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)local_8b4[0]);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xf);
    local_8a9 = (iVar1 - local_8a8[0]) + 0xdc <= *(int *)(param_1 + 0xefc);
    if ((*(int *)(local_89c + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      local_8b4[0] = (*(int *)(local_89c + 0x14));
      TreeLowerBound(local_8a8);
    }
    local_4 = 0xffffffff;
    if ((*(int *)(local_678 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes();
      local_8b4[0] = (*(int *)(local_678 + 0x14));
      TreeLowerBound(local_8a8);
    }
    iVar1 = local_8a0;
    if (local_8a9 != '\0') {
      uVar4 = EncodeChecksumDeltaMul(param_1 + 0xcd8,local_230,2);
      local_4 = 0x11;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState((void *)uVar4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      iVar1 = iVar1 + 0x11;
      if ((*(int *)(local_230 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        local_8b4[0] = (*(int *)(local_230 + 0x14));
        TreeLowerBound(local_8a8);
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

