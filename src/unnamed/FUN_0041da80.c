/* FUN_0041da80 - 0x0041da80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-GUARD-CELL FIX (2026-08-11): all 59 argless
 * PeekPacketChecksumState() calls and all 41 cell-less
 * EncodeOutgoingPacketField() calls had lost their CValueGuard cell
 * pointer (EAX resp. EDI at the original call sites). Recovered every
 * cell from tools/guard_worklist.json plus capstone disasm of
 * 0x41da80-0x41e98a. NOTE the decompile's branch order is INVERTED
 * vs the binary (C's param_4=='\0' branch is the binary's THIRD block
 * at 0x41e159, cells +0xf61b4..; the param_4!=0 branch is the second
 * block at 0x41de26, +0xf7d88..; the C else/param_6!=0 branch is the
 * FIRST block at 0x41dacc, +0xf995c..), so sites were matched by
 * landmark offsets, not line order (spot-verified at 0x41dadd/
 * 0x41dbb6-0x41dbc7/0x41dc96/0x41de37/0x41e15b-0x41e16a/0x41e323/
 * 0x41e4d2/0x41e51e/0x41e8dc-0x41e912). Peek cells are base-relative
 * (base = param_1*0xb1ac + param_2 = local_460, asm [esp+0x1c];
 * stride 0x224), encode cells are param_3-relative (+0x1e54..+0x35ec).
 * The branch-shared peek at 0x41e485 is reached with a branch-
 * dependent cell (+0xf7b64 vs +0xf9738) - expressed as a param_4
 * conditional. Six tail peeks (after each EncodeChecksumDeltaAdd)
 * take that helper's just-returned cell pointer, which the decompile
 * discarded - now captured in iVar1/iVar3/iVar4. Three tail peeks use
 * *(byte *)(param_3+0x3c)*0x1120 + param_2 + 0x50688, three more
 * + 0x50464; the original re-reads param_3's untouched arg slot
 * [esp+0x484] there while the decompile artifact-clobbers param_3
 * (lines "param_3 = ...retaddr/puStack_8/iStack_10/iStack_18") -
 * preserved via new local iVar8. The four EncodeGuardedBool sites
 * (cells param_3+0x33bc/+0x33bf/+0x33c2/+0x33c5 per disasm) stay
 * marked GB_GUARD_UNRECOVERED - out of this sweep's Peek/Encode
 * scope. The EncodeChecksumDeltaAdd calls' own dropped/artifact args
 * were NOT touched (not in scope; defs are promoted centrally).
 */
#include "ghidra_types.h"


void __thiscall
FUN_0041da80(int param_1,int param_2,undefined1 *param_3,char param_4,undefined *param_5,
            char param_6)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffffb70;
  undefined stack0xfffffb74;
  undefined stack0xfffffb78;
  undefined stack0xfffffb80;
  undefined stack0xfffffb88;
  undefined stack0xfffffb90;
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar8;
  code *pcVar5;
  int unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  int unaff_retaddr;
  undefined *puVar6;
  undefined *puVar7;
  int local_468 [2];
  undefined *local_460;
  int local_45c;
  undefined *puStack_458;
  int iStack_450;
  int iStack_448;
  undefined1 auStack_25c [16];
  int iStack_24c;
  undefined4 uStack_3c;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  int iStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053af72;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_468[0] = (int)param_3 + 0x1e54;
  iVar8 = (int)param_3; /* the untouched arg slot [esp+0x484] the original re-reads in
                         * the tail; the decompile artifact-clobbers param_3 there */
  if (param_6 == '\0') {
    if (param_4 == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_460 = (undefined *)(param_1 * 0xb1ac + param_2);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf61b4));
      EncodeOutgoingPacketField((void *)(param_3 + 0x1e54),uVar2);
      pcVar5 = (code *)LeaveCriticalSection;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf63d8));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2078),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf65fc));
      EncodeOutgoingPacketField((void *)(param_3 + 0x229c),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf6820));
      EncodeOutgoingPacketField((void *)(param_3 + 0x24c0),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf6a44));
      EncodeOutgoingPacketField((void *)(param_3 + 0x26e4),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_45c = (int)param_3 + 0x2908;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf6c68));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2908),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf6e8c));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2b2c),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf70b0));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2d50),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf72d4));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2f74),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf74f8));
      EncodeOutgoingPacketField((void *)(param_3 + 0x3198),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState((void *)((int)local_460 + 0xf771c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState((void *)((int)local_460 + 0xf771c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState((void *)((int)local_460 + 0xf771c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState((void *)((int)local_460 + 0xf771c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf7940));
      EncodeOutgoingPacketField((void *)(param_3 + 0x33c8),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_460 = (undefined *)(param_1 * 0xb1ac + param_2);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf7d88));
      EncodeOutgoingPacketField((void *)(param_3 + 0x1e54),uVar2);
      pcVar5 = (code *)LeaveCriticalSection;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf7fac));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2078),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf81d0));
      EncodeOutgoingPacketField((void *)(param_3 + 0x229c),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf83f4));
      EncodeOutgoingPacketField((void *)(param_3 + 0x24c0),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf8618));
      EncodeOutgoingPacketField((void *)(param_3 + 0x26e4),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_45c = (int)param_3 + 0x2908;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf883c));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2908),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf8a60));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2b2c),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf8c84));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2d50),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf8ea8));
      EncodeOutgoingPacketField((void *)(param_3 + 0x2f74),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf90cc));
      EncodeOutgoingPacketField((void *)(param_3 + 0x3198),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState((void *)((int)local_460 + 0xf92f0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState((void *)((int)local_460 + 0xf92f0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState((void *)((int)local_460 + 0xf92f0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState((void *)((int)local_460 + 0xf92f0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf9514));
      EncodeOutgoingPacketField((void *)(param_3 + 0x33c8),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + ((param_4 == '\0') ? 0xf7b64 : 0xf9738)));
    EncodeOutgoingPacketField((void *)(param_3 + 0x35ec),uVar2);
    (*pcVar5)();
    pcVar5 = (code *)LeaveCriticalSection;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_460 = (undefined *)(param_1 * 0xb1ac + param_2);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf995c));
    EncodeOutgoingPacketField((void *)(param_3 + 0x1e54),uVar2);
    pcVar5 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf9b80));
    EncodeOutgoingPacketField((void *)(param_3 + 0x2078),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf9da4));
    EncodeOutgoingPacketField((void *)(param_3 + 0x229c),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xf9fc8));
    EncodeOutgoingPacketField((void *)(param_3 + 0x24c0),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xfa1ec));
    EncodeOutgoingPacketField((void *)(param_3 + 0x26e4),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_45c = (int)param_3 + 0x2908;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xfa410));
    EncodeOutgoingPacketField((void *)(param_3 + 0x2908),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xfa634));
    EncodeOutgoingPacketField((void *)(param_3 + 0x2b2c),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xfa858));
    EncodeOutgoingPacketField((void *)(param_3 + 0x2d50),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xfaa7c));
    EncodeOutgoingPacketField((void *)(param_3 + 0x2f74),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xfaca0));
    EncodeOutgoingPacketField((void *)(param_3 + 0x3198),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)((int)local_460 + 0xfaec4));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)((int)local_460 + 0xfaec4));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)((int)local_460 + 0xfaec4));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)((int)local_460 + 0xfaec4));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xfb0e8));
    EncodeOutgoingPacketField((void *)(param_3 + 0x33c8),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)((int)local_460 + 0xfb30c));
    EncodeOutgoingPacketField((void *)(param_3 + 0x35ec),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  local_460 = (undefined *)0x1;
  if (0 < (int)param_5) {
    local_460 = param_5;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)((uint)*(byte *)(iVar8 + 0x3c) * 0x1120 + param_2 + 0x50688));
  (*pcVar5)();
  iVar1 = EncodeChecksumDeltaAdd();
  puStack_8 = (undefined1 *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)iVar1);
  EncodeOutgoingPacketField((void *)local_468[0],uVar2);
  puVar7 = &DAT_005a9068;
  (*pcVar5)();
  local_c = 0xffffffff;
  if (iStack_448 != 0) {
    ScrambleChecksumGuardBytes(iStack_448,&DAT_0079376c);
    TreeLowerBound();
    pcVar5 = (code *)LeaveCriticalSection;
    param_3 = (undefined1 *)unaff_retaddr;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)((uint)*(byte *)(iVar8 + 0x3c) * 0x1120 + param_2 + 0x50688));
  (*pcVar5)();
  iVar1 = EncodeChecksumDeltaAdd((int)param_3 + 0x2078);
  iStack_10 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)iVar1);
  EncodeOutgoingPacketField((void *)(iVar8 + 0x2078),uVar2);
  puVar6 = &DAT_005a9068;
  (*pcVar5)();
  uStack_14 = 0xffffffff;
  if (iStack_450 != 0) {
    ScrambleChecksumGuardBytes(iStack_450,&DAT_0079376c);
    TreeLowerBound();
    pcVar5 = (code *)LeaveCriticalSection;
    param_3 = puStack_8;
    unaff_EDI = iStack_450;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)((uint)*(byte *)(iVar8 + 0x3c) * 0x1120 + param_2 + 0x50688));
  (*pcVar5)();
  iVar1 = EncodeChecksumDeltaAdd((int)param_3 + 0x229c,local_468,(iVar1 * 3) / unaff_EDI);
  iStack_18 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)iVar1);
  EncodeOutgoingPacketField((void *)(iVar8 + 0x229c),uVar2);
  (*pcVar5)(&DAT_005a9068);
  uStack_1c = 0xffffffff;
  if (puStack_458 != (undefined *)0x0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffffb80);
    pcVar5 = (code *)LeaveCriticalSection;
    param_3 = (undefined1 *)iStack_10;
    puVar7 = puStack_458;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)((uint)*(byte *)(iVar8 + 0x3c) * 0x1120 + param_2 + 0x50464));
  (*pcVar5)(&DAT_005a9068);
  iVar1 = EncodeChecksumDeltaAdd((int)param_3 + 0x24c0,&stack0xfffffb90,(iVar1 / 2) / (int)puVar7);
  uStack_20 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)iVar1);
  EncodeOutgoingPacketField((void *)(iVar8 + 0x24c0),uVar2);
  (*pcVar5)(&DAT_005a9068);
  puVar7 = local_460;
  uStack_24 = 0xffffffff;
  if (local_460 != (undefined *)0x0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffffb78);
    pcVar5 = (code *)LeaveCriticalSection;
    param_3 = (undefined1 *)iStack_18;
    puVar6 = puVar7;
  }
  iVar1 = 1;
  if (0 < iStack_10) {
    iVar1 = iStack_10;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)((uint)*(byte *)(iVar8 + 0x3c) * 0x1120 + param_2 + 0x50464));
  (*pcVar5)(&DAT_005a9068);
  iVar3 = EncodeChecksumDeltaAdd((int)param_3 + 0x26e4,&stack0xfffffb88,(iVar3 / 2) / (int)puVar6);
  uStack_28 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)iVar3);
  EncodeOutgoingPacketField((void *)(iVar8 + 0x26e4),uVar2);
  (*pcVar5)(&DAT_005a9068);
  uStack_2c = 0xffffffff;
  if (local_468[0] != 0) {
    ScrambleChecksumGuardBytes(local_468[0],&DAT_0079376c);
    TreeLowerBound(&stack0xfffffb70);
    pcVar5 = (code *)LeaveCriticalSection;
  }
  iVar3 = iStack_18;
  if (iStack_18 < 1) {
    iVar3 = 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)((uint)*(byte *)(iVar8 + 0x3c) * 0x1120 + param_2 + 0x50464));
  (*pcVar5)(&DAT_005a9068);
  iVar4 = EncodeChecksumDeltaAdd(iVar1,auStack_25c,(iVar4 / 2) / iVar3);
  uStack_30 = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)iVar4);
  EncodeOutgoingPacketField((void *)local_45c,uVar2);
  (*pcVar5)(&DAT_005a9068);
  uStack_34 = 0xffffffff;
  if (iStack_24c != 0) {
    ScrambleChecksumGuardBytes(iStack_24c,&DAT_0079376c);
    TreeLowerBound(&stack0xfffffb74);
  }
  *unaff_FS_OFFSET = uStack_3c;
  return;
}

