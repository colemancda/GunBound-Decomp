/* EncodeChecksumDeltaDiv - 0x0040a8c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-15): all 3 EncodeOutgoingPacketField calls dropped
 * `self` - same idiom/derivation as EncodeChecksumDeltaAdd.c (angr
 * func_addr 0x40a8c0; the first call's cell shows as esp+0x24 instead
 * of +0x20 there due to the intervening `if (param_3==0)` branch
 * shifting the stack at that instruction, still the same local_21c
 * cell): first two calls' self is local_21c's address minus 0x14,
 * third call's self is param_2.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): both internal
 * PeekPacketChecksumState() calls now name their cell.  The first reads the
 * SOURCE cell param_1 (orig `mov eax,[esp+0x250]` = the first stack argument);
 * the second reads back the stack scratch this function stages the result in,
 * which is the same `local_230` the two encodes above it
 * already use.  That is the shape the whole delta family shares:
 * `param_2 = param_1.Peek() OP param_3`, staged through the scratch, and the
 * function returns param_2.
 */
/* OBJECT-OVERLAP FIX (2026-11-12): the raw port declared a 28-byte local_238
 * (the TreeInsert out pair plus the first 0x14 bytes of the object) and a lone
 * int local_21c, then passed `&local_21c - 0x14` as a 0x224-byte object, so
 * the Encode/Peek calls ran off the end of a four-byte local.  The disassembly
 * keeps two separate things: the 8-byte pair at frame -0x238 (`lea eax,[esp+
 * 0x14]` before the TreeInsert call) and the 0x224-byte object at -0x230
 * (`lea edi,[esp+0x20]`), which ends exactly at the saved fs:[0] link at -0xc.
 * The guard pointer is object+0x14 (-0x21c) and the flag byte object+0x220. */
#include "ghidra_types.h"


int EncodeChecksumDeltaDiv(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_238 [2];     /* TreeInsert's out pair, frame -0x238 (8 bytes) */
  undefined1 local_230 [0x224]; /* the guard-cell object, frame -0x230..-0xc: guard pointer at +0x14, flag byte at +0x220 */
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00538e6a;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_230[0x220] = 0;
  *(int *)(local_230 + 0x14) = 0;
  EncodeOutgoingPacketField(local_230, 0);
  local_4 = 1;
  iVar1 = PeekPacketChecksumState((void *)(param_1));
  if (param_3 == 0) {
    param_3 = 1;
  }
  EncodeOutgoingPacketField(local_230, iVar1 / param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(undefined1 *)(param_2 + 0x220) = 0;
  *(undefined4 *)(param_2 + 0x14) = 0;
  uVar2 = PeekPacketChecksumState(local_230);
  EncodeOutgoingPacketField((void *)param_2, uVar2);
  local_4 = local_4 & 0xffffff00;
  if (*(int *)(local_230 + 0x14) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&g_valueGuardKeyTable);
    TreeInsert(local_238,&g_valueGuardMap);
  }
  *unaff_FS_OFFSET = local_c;
  return param_2;
}

