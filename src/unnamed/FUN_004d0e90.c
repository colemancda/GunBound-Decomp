/* FUN_004d0e90 - 0x004d0e90 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 6 argless sites.  Every one of them is an offset off ESI,
 * which 0x4d0ec4 sets from the return value of the GetPlayerRecordBySlot
 * call at 0x4d0ebf and which stays live across the whole guarded region.
 * Ghidra reused `iVar1` for that pointer and then immediately overwrote it
 * with the first peek result, so the pointer is captured into a new local
 * `iRecord` first.  Offsets, in address order: +0x90c (C26), +0xb30 (C30),
 * +0x15e4 (C37 encode, C40 peek), +0x90c (C41), +0xb30 (C45).
 *
 * (Unrelated and NOT fixed here: 0x4d0eb8 also loads EDI from the loop
 * counter slot before that call, i.e. GetPlayerRecordBySlot takes the slot
 * index in EDI -- another dropped argument, tracked separately.)
 */
#include "ghidra_types.h"


void FUN_004d0e90(int param_1)

{
  int iVar1;
  int iRecord;
  undefined4 uVar2;
  undefined4 *puVar3;
  int *local_c;
  int local_8;
  
  local_c = (int *)(param_1 + 0x2388);
  local_8 = 0;
  do {
    iVar1 = GetPlayerRecordBySlot(g_clientContext);
    iRecord = iVar1;
    if (iVar1 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(iRecord + 0x90c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (iVar1 == local_c[-1]) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar1 = PeekPacketChecksumState((void *)(iRecord + 0xb30));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (iVar1 == *local_c) goto LAB_004d0f92;
      }
      if (*local_c != -1) {
        iVar1 = local_c[-1];
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(iRecord + 0x15e4), iVar1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        uVar2 = PeekPacketChecksumState((void *)(iRecord + 0x15e4));
        EncodeOutgoingPacketField((void *)(iRecord + 0x90c), uVar2);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar1 = *local_c;
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(iRecord + 0xb30), iVar1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      }
    }
LAB_004d0f92:
    local_8 = local_8 + 1;
    local_c = local_c + 2;
    if (7 < local_8) {
      puVar3 = (undefined4 *)(param_1 + 0x2384);
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = 0xffffffff;
        puVar3 = puVar3 + 1;
      }
      return;
    }
  } while( true );
}

