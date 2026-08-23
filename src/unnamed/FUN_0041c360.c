/* FUN_0041c360 - 0x0041c360 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-GUARD-CELL FIX (2026-08-11): all 105 argless
 * PeekPacketChecksumState() calls and all 73 one-arg
 * EncodeOutgoingPacketField() calls had lost their CValueGuard cell
 * pointer (EAX resp. EDI at the original call sites). Recovered every
 * cell from tools/guard_worklist.json plus capstone disasm of
 * 0x41c360-0x41da70 (order-zip, landmark-verified at 0x41c3ae/
 * 0x41c761-0x41c7a1/0x41c97d/0x41cca4/0x41d1a1-0x41d1c3/0x41d551/
 * 0x41d7f6/0x41d90e-0x41d924 among others): peek cells are mostly
 * param_2-relative (+0xf0384..+0xf5f90, stride 0x224; param_2 is
 * pre-adjusted by +param_1*0xb1ac at entry - asm keeps it in
 * [esp+0x18]), encode cells are param_3-relative (+0xd54..+0xabec,
 * ebx in the asm). Eight peeks (after each EncodeChecksumPairSum/
 * DeltaSub/DeltaAdd) take the just-returned cell pointer of that
 * helper, whose return value the decompile discarded - now captured
 * in uVar2. Three peeks use the RAW (pre-adjust) param_2 +
 * (*(int *)(param_3+8) & 7)*0x1120 + 0x508ac/0x50ad0/0x50240
 * (original reads the untouched arg slot [esp+0x8c8]; preserved via
 * new local iVar7). Two peeks read the global cell &DAT_00e9ba40.
 */
#include "ghidra_types.h"


void __thiscall FUN_0041c360(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_8a4 [8];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053b030;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = param_2;
  param_2 = param_2 + param_1 * 0xb1ac;
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf0384));
  EncodeOutgoingPacketField((void *)(param_3 + 0xd54),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf05a8));
  EncodeOutgoingPacketField((void *)(param_3 + 0xf78),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf07cc));
  EncodeOutgoingPacketField((void *)(param_3 + 0x13c0),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_3 + 0xf78));
  EncodeOutgoingPacketField((void *)(param_3 + 0x119c),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf09f0));
  EncodeOutgoingPacketField((void *)(param_3 + 0x22c0),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf0c14));
  EncodeOutgoingPacketField((void *)(param_3 + 0x24e4),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf0e38));
  EncodeOutgoingPacketField((void *)(param_3 + 0x2708),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf105c));
  EncodeOutgoingPacketField((void *)(param_3 + 0x292c),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf1280));
  EncodeOutgoingPacketField((void *)(param_3 + 0x2b50),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf14a4));
  EncodeOutgoingPacketField((void *)(param_3 + 0x2d74),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf16c8));
  EncodeOutgoingPacketField((void *)(param_3 + 0x2f98),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf18ec));
  EncodeOutgoingPacketField((void *)(param_3 + 0x31bc),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf1b10));
  EncodeOutgoingPacketField((void *)(param_3 + 0x33e0),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf1d34));
  EncodeOutgoingPacketField((void *)(param_3 + 0x3604),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf1f58));
  EncodeOutgoingPacketField((void *)(param_3 + 0x3828),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf217c));
  EncodeOutgoingPacketField((void *)(param_3 + 0x3a4c),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf23a0));
  EncodeOutgoingPacketField((void *)(param_3 + 0x3c70),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf25c4));
  EncodeOutgoingPacketField((void *)(param_3 + 0x3e94),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf27e8));
  EncodeOutgoingPacketField((void *)(param_3 + 0x40b8),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf2a0c));
  EncodeOutgoingPacketField((void *)(param_3 + 0x42dc),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf2c30));
  EncodeOutgoingPacketField((void *)(param_3 + 0x4500),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf2e54));
  EncodeOutgoingPacketField((void *)(param_3 + 0x4724),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x22c0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x24e4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (0x5a < iVar3 - iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_3 + 0x22c0));
    iVar3 = ((iVar3 - iVar4) + -0x5a) / 2;
    EncodeOutgoingPacketField((void *)(param_3 + 0x22c0),iVar5 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x24e4));
    EncodeOutgoingPacketField((void *)(param_3 + 0x24e4),iVar4 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar2 = EncodeChecksumPairDiff(param_2 + 0xf09f0,local_89c,param_2 + 0xf0c14);
  local_4 = 0;
  uVar2 = EncodeChecksumDeltaDiv(uVar2,local_678,2);
  local_4 = 1;
  uVar2 = EncodeChecksumPairSum(uVar2,local_454,param_2 + 0xf0c14);
  local_4 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 1;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  local_4 = 0;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x22c0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_3 + 0x22c0),iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x24e4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_3 + 0x24e4),iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x2708));
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x22c0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x22c0));
    EncodeOutgoingPacketField((void *)(param_3 + 0x2708),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x292c));
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x24e4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x24e4));
    EncodeOutgoingPacketField((void *)(param_3 + 0x292c),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x2f98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x31bc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (0x5a < iVar3 - iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_3 + 0x2f98));
    iVar3 = ((iVar3 - iVar4) + -0x5a) / 2;
    EncodeOutgoingPacketField((void *)(param_3 + 0x2f98),iVar5 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x31bc));
    EncodeOutgoingPacketField((void *)(param_3 + 0x31bc),iVar4 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar2 = EncodeChecksumPairDiff(param_2 + 0xf16c8,local_454,param_2 + 0xf18ec);
  local_4 = 3;
  uVar2 = EncodeChecksumDeltaDiv(uVar2,local_678,2);
  local_4 = 4;
  uVar2 = EncodeChecksumPairSum(uVar2,local_89c,param_2 + 0xf18ec);
  local_4 = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 4;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  local_4 = 3;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x2f98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_3 + 0x2f98),iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x31bc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_3 + 0x31bc),iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x33e0));
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x2f98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x2f98));
    EncodeOutgoingPacketField((void *)(param_3 + 0x33e0),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x3604));
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x31bc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x31bc));
    EncodeOutgoingPacketField((void *)(param_3 + 0x3604),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x2f98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x31bc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (0x5a < iVar3 - iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_3 + 0x3c70));
    iVar3 = ((iVar3 - iVar4) + -0x5a) / 2;
    EncodeOutgoingPacketField((void *)(param_3 + 0x3c70),iVar5 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x3e94));
    EncodeOutgoingPacketField((void *)(param_3 + 0x3e94),iVar4 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar2 = EncodeChecksumPairDiff(param_2 + 0xf23a0,local_454,param_2 + 0xf25c4);
  local_4 = 6;
  uVar2 = EncodeChecksumDeltaDiv(uVar2,local_678,2);
  local_4 = 7;
  uVar2 = EncodeChecksumPairSum(uVar2,local_89c,param_2 + 0xf25c4);
  local_4 = 8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 7;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  local_4 = 6;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x3c70));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_3 + 0x3c70),iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x3e94));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_3 + 0x3e94),iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x40b8));
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x3c70));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x3c70));
    EncodeOutgoingPacketField((void *)(param_3 + 0x40b8),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x42dc));
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x3e94));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 < iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x3e94));
    EncodeOutgoingPacketField((void *)(param_3 + 0x42dc),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  uVar2 = EncodeChecksumPairDiff(param_3 + 0x22c0,local_454,param_3 + 0x24e4);
  local_4 = 9;
  uVar2 = EncodeChecksumDeltaDiv(uVar2,local_678,2);
  local_4 = 10;
  uVar2 = EncodeChecksumPairSum(uVar2,local_89c,param_3 + 0x24e4);
  local_4 = 0xb;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)uVar2);
  EncodeOutgoingPacketField((void *)(param_3 + 0x4948),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 10;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  local_4 = 9;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf3078));
  EncodeOutgoingPacketField((void *)(param_3 + 0x6520),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(iVar7 + (*(int *)(param_3 + 8) & 7) * 0x1120 + 0x508ac));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = EncodeChecksumDeltaSub(param_3 + 0x6520,local_89c,(iVar3 << 3) / 10);
  local_4 = 0xc;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)uVar2);
  EncodeOutgoingPacketField((void *)(param_3 + 0x6520),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf329c));
  EncodeOutgoingPacketField((void *)(param_3 + 0x6744),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf34c0));
  EncodeOutgoingPacketField((void *)(param_3 + 0x6db0),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x6db0));
  EncodeOutgoingPacketField((void *)(param_3 + 0x6fd4),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x6fd4));
  EncodeOutgoingPacketField((void *)(param_3 + 0x71f8),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(iVar7 + (*(int *)(param_3 + 8) & 7) * 0x1120 + 0x50ad0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = EncodeChecksumDeltaAdd(param_3 + 0x6744,local_89c,iVar4 * iVar3);
  local_4 = 0xd;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)uVar2);
  EncodeOutgoingPacketField((void *)(param_3 + 0x6744),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  uVar2 = EncodeChecksumPairSum(param_3 + 0x6744,local_89c,param_3 + 0x6db0);
  local_4 = 0xe;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  if (2000 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)(param_3 + 0x6db0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_3 + 0x6744),2000 - iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x6744));
  EncodeOutgoingPacketField((void *)(param_3 + 0x6968),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x6968));
  EncodeOutgoingPacketField((void *)(param_3 + 0x6b8c),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf36e4));
  EncodeOutgoingPacketField((void *)(param_3 + 0x741c),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf3908));
  EncodeOutgoingPacketField((void *)(param_3 + 0x7640),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf3b2c));
  EncodeOutgoingPacketField((void *)(param_3 + 0x853c),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(param_3 + 0x853c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 < iVar3) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(param_3 + 0x853c),uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_3 + 0x853c));
  EncodeOutgoingPacketField((void *)(param_3 + 0x8318),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf3d50));
  EncodeOutgoingPacketField((void *)(param_3 + 0x80f4),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf3f74));
  EncodeOutgoingPacketField((void *)(param_3 + 0x8de8),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)(iVar7 + (*(int *)(param_3 + 8) & 7) * 0x1120 + 0x50240));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = EncodeChecksumDeltaAdd(param_3 + 0x8de8,local_230,(iVar3 * 0x19) / 10);
  local_4 = 0xf;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)uVar2);
  EncodeOutgoingPacketField((void *)(param_3 + 0x8de8),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_230 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_8a4,&g_valueGuardMap);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf4198));
  EncodeOutgoingPacketField((void *)(param_3 + 0x900c),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf43bc));
  EncodeOutgoingPacketField((void *)(param_3 + 0x9230),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf45e0));
  EncodeOutgoingPacketField((void *)(param_3 + 0x9454),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf4804));
  EncodeOutgoingPacketField((void *)(param_3 + 0x9678),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf4a28));
  EncodeOutgoingPacketField((void *)(param_3 + 0x989c),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf4c4c));
  EncodeOutgoingPacketField((void *)(param_3 + 0x9ac0),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = PeekPacketChecksumState((void *)(param_2 + 0xf4e70));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool((bVar1 & 8) == 8,(byte *)GB_GUARD_UNRECOVERED);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = PeekPacketChecksumState((void *)(param_2 + 0xf4e70));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool((bVar1 & 4) == 4,(byte *)GB_GUARD_UNRECOVERED);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = PeekPacketChecksumState((void *)(param_2 + 0xf4e70));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool((bVar1 & 2) == 2,(byte *)GB_GUARD_UNRECOVERED);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState((void *)(param_2 + 0xf4e70));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(CONCAT31((int3)((uVar6 & 0xffffff01) >> 8),
                        '\x01' - ((char)(uVar6 & 0xffffff01) != '\x01')),
                    (byte *)GB_GUARD_UNRECOVERED);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf5094));
  EncodeOutgoingPacketField((void *)(param_3 + 0x9cf0),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf52b8));
  EncodeOutgoingPacketField((void *)(param_3 + 0x9f14),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf54dc));
  EncodeOutgoingPacketField((void *)(param_3 + 0xa138),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf5700));
  EncodeOutgoingPacketField((void *)(param_3 + 0xa35c),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf5924));
  EncodeOutgoingPacketField((void *)(param_3 + 0xa580),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf5b48));
  EncodeOutgoingPacketField((void *)(param_3 + 0xa7a4),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf5d6c));
  EncodeOutgoingPacketField((void *)(param_3 + 0xa9c8),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_2 + 0xf5f90));
  EncodeOutgoingPacketField((void *)(param_3 + 0xabec),uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return;
}

