/* FUN_004d0e90 - 0x004d0e90 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004d0e90(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int *local_c;
  int local_8;
  
  local_c = (int *)(param_1 + 0x2388);
  local_8 = 0;
  do {
    iVar1 = GetPlayerRecordBySlot(DAT_005b3484);
    if (iVar1 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar1 == local_c[-1]) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar1 == *local_c) goto LAB_004d0f92;
      }
      if (*local_c != -1) {
        iVar1 = local_c[-1];
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(iVar1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar2 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(uVar2);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = *local_c;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(iVar1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
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

