/* EncodeChecksumNegate - 0x0040a500 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-16): all 3 EncodeOutgoingPacketField calls dropped
 * self - same idiom/derivation as EncodeChecksumDeltaAdd.c (angr
 * func_addr 0x40a500): first two calls' self is local_21c's address
 * minus 0x14, third call's self is param_2.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): both internal
 * PeekPacketChecksumState() calls now name their cell.  The first reads the
 * SOURCE cell param_1 (orig `mov eax,[esp+0x250]` = the first stack argument);
 * the second reads back the stack scratch this function stages the result in,
 * which is the same `(char *)&local_21c - 0x14` the two encodes above it
 * already use.  That is the shape the whole delta family shares:
 * `param_2 = param_1.Peek() OP param_3`, staged through the scratch, and the
 * function returns param_2.
 */
#include "ghidra_types.h"


int EncodeChecksumNegate(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_238 [28];
  int local_21c;
  undefined1 local_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00538e6a) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_10 = 0;
  local_21c = 0;
  EncodeOutgoingPacketField((char *)&local_21c - 0x14, 0);
  local_4 = 1;
  iVar1 = PeekPacketChecksumState((void *)(param_1));
  EncodeOutgoingPacketField((char *)&local_21c - 0x14, -iVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(param_2 + 0x220) = 0;
  *(undefined4 *)(param_2 + 0x14) = 0;
  uVar2 = PeekPacketChecksumState((void *)((char *)&local_21c - 0x14));
  EncodeOutgoingPacketField((void *)param_2, uVar2);
  local_4 = local_4 & 0xffffff00;
  if (local_21c != 0) {
    ScrambleChecksumGuardBytes(local_21c,&DAT_0079376c);
    TreeLowerBound(local_238);
  }
  return param_2;
}

