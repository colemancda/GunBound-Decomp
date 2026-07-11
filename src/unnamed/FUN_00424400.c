/* FUN_00424400 - 0x00424400 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00424400(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int unaff_ESI;
  char local_11;
  uint local_10;
  int local_8;
  
  local_8 = 4;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  cVar1 = PeekPacketChecksumBool();
  local_10 = 0;
  if (*(int *)(unaff_ESI + 0x44e24) != 0) {
    do {
      if (*(uint *)(unaff_ESI + 0x44e24) <= local_10) goto LAB_00424a44;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((uVar2 & 0x3ffff) == (uVar3 & 0x7fff | -(uint)(cVar1 != '\0') & 0x8000)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(local_10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        break;
      }
      local_10 = local_10 + 1;
    } while (local_10 < *(uint *)(unaff_ESI + 0x44e24));
  }
  if (local_10 == *(uint *)(unaff_ESI + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((byte)(*(byte *)(unaff_ESI + 0x3b498) + *(byte *)(unaff_ESI + 0x3b499) + -0x34) ==
        *(char *)(unaff_ESI + 0x3b49a)) {
      local_11 = '\x01' - ((*(byte *)(unaff_ESI + 0x3b499) >> (*(byte *)(unaff_ESI + 0x3b498) & 7) &
                           1) != 1);
    }
    else {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_11 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(-(uint)(local_11 != '\0') & 0x8000);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)(*(byte *)(unaff_ESI + 0x3b498) + *(byte *)(unaff_ESI + 0x3b499) + -0x34) ==
      *(char *)(unaff_ESI + 0x3b49a)) {
    local_11 = '\x01' - ((*(byte *)(unaff_ESI + 0x3b499) >> (*(byte *)(unaff_ESI + 0x3b498) & 7) & 1
                         ) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_11 = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_10 = 0;
  if (*(int *)(unaff_ESI + 0x44e24) != 0) {
    do {
      if (*(uint *)(unaff_ESI + 0x44e24) <= local_10) goto LAB_00424a44;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((uVar2 & 0x3ffff) == (uVar3 & 0x7fff | (-(uint)(local_11 != '\0') & 0x8000) + 0x10000)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(local_10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        break;
      }
      local_10 = local_10 + 1;
    } while (local_10 < *(uint *)(unaff_ESI + 0x44e24));
  }
  if (local_10 == *(uint *)(unaff_ESI + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((byte)(*(byte *)(unaff_ESI + 0x3b498) + *(byte *)(unaff_ESI + 0x3b499) + -0x34) ==
        *(char *)(unaff_ESI + 0x3b49a)) {
      local_11 = '\x01' - ((*(byte *)(unaff_ESI + 0x3b499) >> (*(byte *)(unaff_ESI + 0x3b498) & 7) &
                           1) != 1);
    }
    else {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_11 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(-(uint)(local_11 != '\0') & 0x8000);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)(*(byte *)(unaff_ESI + 0x3b498) + *(byte *)(unaff_ESI + 0x3b499) + -0x34) ==
      *(char *)(unaff_ESI + 0x3b49a)) {
    local_11 = '\x01' - ((*(byte *)(unaff_ESI + 0x3b499) >> (*(byte *)(unaff_ESI + 0x3b498) & 7) & 1
                         ) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_11 = '\0';
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_10 = 0;
  if (*(int *)(unaff_ESI + 0x44e24) != 0) {
    do {
      if (*(uint *)(unaff_ESI + 0x44e24) <= local_10) goto LAB_00424a44;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((uVar2 & 0x3ffff) == (uVar3 & 0x7fff | (-(uint)(local_11 != '\0') & 0x8000) + 0x20000)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(local_10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        break;
      }
      local_10 = local_10 + 1;
    } while (local_10 < *(uint *)(unaff_ESI + 0x44e24));
  }
  if (local_10 == *(uint *)(unaff_ESI + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((byte)(*(byte *)(unaff_ESI + 0x3b498) + *(byte *)(unaff_ESI + 0x3b499) + -0x34) ==
        *(char *)(unaff_ESI + 0x3b49a)) {
      local_11 = '\x01' - ((*(byte *)(unaff_ESI + 0x3b499) >> (*(byte *)(unaff_ESI + 0x3b498) & 7) &
                           1) != 1);
    }
    else {
      g_valueGuardTamperFlag = 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_11 = '\0';
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(-(uint)(local_11 != '\0') & 0x8000);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  local_10 = 0;
  if (*(int *)(unaff_ESI + 0x44e24) != 0) {
    do {
      if (*(uint *)(unaff_ESI + 0x44e24) <= local_10) {
LAB_00424a44:
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((uVar2 & 0x3ffff) == (uVar3 & 0x7fff | 0x38000)) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(local_10);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        break;
      }
      local_10 = local_10 + 1;
    } while (local_10 < *(uint *)(unaff_ESI + 0x44e24));
  }
  if (local_10 == *(uint *)(unaff_ESI + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x8000);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  return;
}

