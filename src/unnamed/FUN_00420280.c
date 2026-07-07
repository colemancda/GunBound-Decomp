/* FUN_00420280 - 0x00420280 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00420280(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *local_4;
  
  local_4 = (undefined4 *)0x8;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = (undefined4 *)((int)local_4 + -1);
  } while (local_4 != (undefined4 *)0x0);
  local_4 = (undefined4 *)(param_1 + 0x58b40);
  iVar2 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((*(char *)(param_1 + 0x5010d + iVar2) == '\x01') &&
       (*(char *)(iVar2 + 0x50126 + param_1) != -1)) {
      uVar1 = *local_4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(uVar1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar1 = *local_4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(uVar1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar2 = iVar2 + 1;
    local_4 = local_4 + 1;
  } while (iVar2 < 8);
  return;
}

