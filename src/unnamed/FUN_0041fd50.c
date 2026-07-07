/* FUN_0041fd50 - 0x0041fd50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_0041fd50(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int local_14;
  int local_c;
  int local_8;
  
  param_1 = 0;
  local_8 = 0xc;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8 = local_8 + -1;
  } while (local_8 != 0);
  local_c = 0;
  local_8 = 0;
  do {
    local_14 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar1) {
      do {
        if (7 < param_1) goto LAB_0041ff38;
        uVar5 = 0x2000 << ((byte)local_c & 0x1f);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        param_1 = param_1 + 1;
        if ((uVar2 & uVar5) == uVar5) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar1 = local_c;
        }
        else {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar1 = -1;
        }
        EncodeOutgoingPacketField(iVar1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_14 = local_14 + 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      } while (local_14 < iVar1);
    }
    if (7 < param_1) break;
    local_8 = local_8 + 0x224;
    local_c = local_c + 1;
  } while (local_8 < 0xefc);
LAB_0041ff38:
  DAT_005b3488 = param_2;
  param_1 = 0x1f;
  do {
    uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
    iVar1 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
    uVar5 = iVar1 * 0x343fd + 0x5809315;
    DAT_005b3488 = iVar1 + (uVar5 * 0x61 + 0x61) % 0xf4241;
    if ((uVar2 & 7) != (uVar5 & 7)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar2 & 0x10000) == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = 0;
  }
  else {
    uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
    DAT_005b3488 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar2 % 0x1a);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
    DAT_005b3488 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = uVar2 % uVar5;
  }
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
  DAT_005b3488 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((uVar2 & 0xf) - 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = DAT_005b3488 * 0x343fd + 0x5809315;
  DAT_005b3488 = DAT_005b3488 + (uVar2 * 0x61 + 0x61) % 0xf4241;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar2 % 0x50 - 0x28);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_2 = 0x400;
  do {
    iVar1 = DAT_005b3488 * 0x343fd + 0x5809315;
    DAT_005b3488 = DAT_005b3488 + (iVar1 * 0x61 + 0x61U) % 0xf4241;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

