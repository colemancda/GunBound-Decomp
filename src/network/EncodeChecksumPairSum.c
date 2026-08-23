/* EncodeChecksumPairSum - 0x0040aba0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-16): all 3 EncodeOutgoingPacketField calls dropped
 * self - same idiom/derivation as EncodeChecksumDeltaAdd.c (angr
 * func_addr 0x40aba0): first two calls' self is local_21c's address
 * minus 0x14, third call's self is param_2.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): this helper really
 * takes THREE cells - Ghidra kept only two.  The original reads its first
 * stack argument at `[esp+0x250]` and its THIRD at `[esp+0x258]` (8 bytes
 * apart = two argument slots), so the recovered signature is
 * (param_1, param_2, param_3) and the 150+ call sites that already pass three
 * arguments were right all along.  The three internal peeks are, in order,
 * param_1, param_3, and the stack scratch the result is staged in
 * (`(char *)&local_21c - 0x14`, the same cell the encodes above already use).
 * Net effect: `param_2 = param_1.Peek() OP param_3.Peek()`, returning param_2 -
 * which is exactly why these helpers return their SECOND argument.
 */
#include "ghidra_types.h"


int EncodeChecksumPairSum(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_238 [28];
  int local_21c;
  undefined1 local_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00538e6a;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_10 = 0;
  local_21c = 0;
  EncodeOutgoingPacketField((char *)&local_21c - 0x14, 0);
  local_4 = 1;
  iVar1 = PeekPacketChecksumState((void *)(param_1));
  iVar2 = PeekPacketChecksumState((void *)(param_3));
  EncodeOutgoingPacketField((char *)&local_21c - 0x14, iVar2 + iVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined1 *)(param_2 + 0x220) = 0;
  *(undefined4 *)(param_2 + 0x14) = 0;
  uVar3 = PeekPacketChecksumState((void *)((char *)&local_21c - 0x14));
  EncodeOutgoingPacketField((void *)param_2, uVar3);
  local_4 = local_4 & 0xffffff00;
  if (local_21c != 0) {
    ScrambleChecksumGuardBytes(local_21c,&g_valueGuardKeyTable);
    TreeLowerBound(local_238,&g_valueGuardMap);
  }
  *unaff_FS_OFFSET = local_c;
  return param_2;
}

