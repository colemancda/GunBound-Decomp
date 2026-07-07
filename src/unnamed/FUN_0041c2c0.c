/* FUN_0041c2c0 - 0x0041c2c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_0041c2c0(int param_1,int param_2)

{
  int iVar1;
  int local_4;
  
  local_4 = 0;
  do {
    if (*(char *)(param_1 + 0x45914 + local_4) != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar1 == param_2) {
        return 1;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar1 == param_2) {
        return 1;
      }
    }
    local_4 = local_4 + 1;
    if (7 < local_4) {
      return 0;
    }
  } while( true );
}

