/* FUN_0040aea0 - 0x0040aea0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-16): all 3 EncodeOutgoingPacketField calls dropped
 * self - same idiom/derivation as EncodeChecksumDeltaAdd.c (angr
 * func_addr 0x40aea0; the first call's cell shows as esp+0x20 vs the
 * second's esp+0x1c there due to the intervening `if (iVar2==0)`
 * branch shifting the stack at that instruction, still the same
 * local_21c cell - same pattern as EncodeChecksumDeltaDiv.c): first
 * two calls' self is local_21c's address minus 0x14, third call's
 * self is param_2. Division-style sibling of EncodeChecksumDeltaDiv.c
 * (dividend/divisor operand order differs slightly - not touched here).
 */
#include "ghidra_types.h"


int FUN_0040aea0(undefined4 param_1,int param_2)

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
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_10 = 0;
  local_21c = 0;
  EncodeOutgoingPacketField((char *)&local_21c - 0x14, 0);
  local_4 = 1;
  iVar1 = PeekPacketChecksumState();
  iVar2 = PeekPacketChecksumState();
  if (iVar2 == 0) {
    iVar2 = 1;
  }
  EncodeOutgoingPacketField((char *)&local_21c - 0x14, iVar1 / iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(param_2 + 0x220) = 0;
  *(undefined4 *)(param_2 + 0x14) = 0;
  uVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)param_2, uVar3);
  local_4 = local_4 & 0xffffff00;
  if (local_21c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_238);
  }
  *unaff_FS_OFFSET = local_c;
  return param_2;
}

