/* FUN_00424400 - 0x00424400 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 8 argless PeekPacketChecksumState() calls and all 13 1-arg
 * EncodeOutgoingPacketField() calls.  regEsi is g_clientContext for the
 * whole function (the C's own `*(int *)(regEsi + 0x44e24)` catalog-count
 * reads are the give-away, and every cell is `lea ...,[esi + 0x...]`).
 *
 * The head loop clears FOUR consecutive equipped-slot cells: EDI starts at
 * esi+0x5f4ab8 and advances 0x224 per pass while local_8 counts 4->1, so
 * the cell is + (4 - local_8) * 0x224 (0x424412/0x424439).
 *
 * The body is then the same block four times, once per equipped-part
 * category, each pairing one part cell with one slot cell:
 *   +0x3ac08 / +0x5f4ab8, +0x3ae2c / +0x5f4cdc,
 *   +0x3b050 / +0x5f4f00, +0x3b274 / +0x5f5124
 * (0x2c and 0x224 apart respectively - the four category strides).  Each
 * block also peeks the store-catalog record's part-code cell
 * *(ctx+0x44e20) + local_10*0x450 + 0x22c, guarded by the C's own
 * ctx+0x44e24 bounds check on the line above (0x424490/0x424670/
 * 0x424850/0x4249c0, all identical).
 *
 * ESI RECOVERED (2026-08-25) by uniformity: every call site in the original
 * loads the same value into it (`mov esi,[0x5b3484]`), so no site pairing is
 * needed -- there is nothing to match up, and the answer cannot be corrupted
 * by Ghidra's block reordering.  All 3 sites, and the source has 3.
 */
#include "ghidra_types.h"


void FUN_00424400(int regEsi)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char local_11;
  uint local_10;
  int local_8;
  
  local_8 = 4;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(regEsi + (4 - local_8) * 0x224 + 0x5f4ab8), 0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  cVar1 = PeekPacketChecksumBool((byte *)(regEsi + 0x3b498));
  local_10 = 0;
  if (*(int *)(regEsi + 0x44e24) != 0) {
    do {
      if (*(uint *)(regEsi + 0x44e24) <= local_10) goto LAB_00424a44;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar2 = PeekPacketChecksumState((void *)(*(int *)(regEsi + 0x44e20) + local_10 * 0x450 + 0x22c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(regEsi + 0x3ac08));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if ((uVar2 & 0x3ffff) == (uVar3 & 0x7fff | -(uint)(cVar1 != '\0') & 0x8000)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(regEsi + 0x5f4ab8), local_10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        break;
      }
      local_10 = local_10 + 1;
    } while (local_10 < *(uint *)(regEsi + 0x44e24));
  }
  if (local_10 == *(uint *)(regEsi + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((byte)(*(byte *)(regEsi + 0x3b498) + *(byte *)(regEsi + 0x3b499) + -0x34) ==
        *(char *)(regEsi + 0x3b49a)) {
      local_11 = '\x01' - ((*(byte *)(regEsi + 0x3b499) >> (*(byte *)(regEsi + 0x3b498) & 7) &
                           1) != 1);
    }
    else {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_11 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(regEsi + 0x3ac08), -(uint)(local_11 != '\0') & 0x8000);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(regEsi + 0x5f4ab8), 0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((byte)(*(byte *)(regEsi + 0x3b498) + *(byte *)(regEsi + 0x3b499) + -0x34) ==
      *(char *)(regEsi + 0x3b49a)) {
    local_11 = '\x01' - ((*(byte *)(regEsi + 0x3b499) >> (*(byte *)(regEsi + 0x3b498) & 7) & 1
                         ) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    local_11 = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_10 = 0;
  if (*(int *)(regEsi + 0x44e24) != 0) {
    do {
      if (*(uint *)(regEsi + 0x44e24) <= local_10) goto LAB_00424a44;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar2 = PeekPacketChecksumState((void *)(*(int *)(regEsi + 0x44e20) + local_10 * 0x450 + 0x22c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(regEsi + 0x3ae2c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if ((uVar2 & 0x3ffff) == (uVar3 & 0x7fff | (-(uint)(local_11 != '\0') & 0x8000) + 0x10000)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(regEsi + 0x5f4cdc), local_10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        break;
      }
      local_10 = local_10 + 1;
    } while (local_10 < *(uint *)(regEsi + 0x44e24));
  }
  if (local_10 == *(uint *)(regEsi + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((byte)(*(byte *)(regEsi + 0x3b498) + *(byte *)(regEsi + 0x3b499) + -0x34) ==
        *(char *)(regEsi + 0x3b49a)) {
      local_11 = '\x01' - ((*(byte *)(regEsi + 0x3b499) >> (*(byte *)(regEsi + 0x3b498) & 7) &
                           1) != 1);
    }
    else {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_11 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(regEsi + 0x3ae2c), -(uint)(local_11 != '\0') & 0x8000);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(regEsi + 0x5f4cdc), 0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((byte)(*(byte *)(regEsi + 0x3b498) + *(byte *)(regEsi + 0x3b499) + -0x34) ==
      *(char *)(regEsi + 0x3b49a)) {
    local_11 = '\x01' - ((*(byte *)(regEsi + 0x3b499) >> (*(byte *)(regEsi + 0x3b498) & 7) & 1
                         ) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    local_11 = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_10 = 0;
  if (*(int *)(regEsi + 0x44e24) != 0) {
    do {
      if (*(uint *)(regEsi + 0x44e24) <= local_10) goto LAB_00424a44;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar2 = PeekPacketChecksumState((void *)(*(int *)(regEsi + 0x44e20) + local_10 * 0x450 + 0x22c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(regEsi + 0x3b050));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if ((uVar2 & 0x3ffff) == (uVar3 & 0x7fff | (-(uint)(local_11 != '\0') & 0x8000) + 0x20000)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(regEsi + 0x5f4f00), local_10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        break;
      }
      local_10 = local_10 + 1;
    } while (local_10 < *(uint *)(regEsi + 0x44e24));
  }
  if (local_10 == *(uint *)(regEsi + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((byte)(*(byte *)(regEsi + 0x3b498) + *(byte *)(regEsi + 0x3b499) + -0x34) ==
        *(char *)(regEsi + 0x3b49a)) {
      local_11 = '\x01' - ((*(byte *)(regEsi + 0x3b499) >> (*(byte *)(regEsi + 0x3b498) & 7) &
                           1) != 1);
    }
    else {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_11 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(regEsi + 0x3b050), -(uint)(local_11 != '\0') & 0x8000);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(regEsi + 0x5f4f00), 0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  local_10 = 0;
  if (*(int *)(regEsi + 0x44e24) != 0) {
    do {
      if (*(uint *)(regEsi + 0x44e24) <= local_10) {
LAB_00424a44:
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar2 = PeekPacketChecksumState((void *)(*(int *)(regEsi + 0x44e20) + local_10 * 0x450 + 0x22c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(regEsi + 0x3b274));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if ((uVar2 & 0x3ffff) == (uVar3 & 0x7fff | 0x38000)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(regEsi + 0x5f5124), local_10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        break;
      }
      local_10 = local_10 + 1;
    } while (local_10 < *(uint *)(regEsi + 0x44e24));
  }
  if (local_10 == *(uint *)(regEsi + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(regEsi + 0x3b274), 0x8000);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(regEsi + 0x5f5124), 0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  return;
}

