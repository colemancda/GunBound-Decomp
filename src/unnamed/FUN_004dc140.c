/* FUN_004dc140 - 0x004dc140 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


int FUN_004dc140(int param_1)

{
  int iVar1;
  int iVar2;
  int local_4;
  
  iVar2 = 0;
  local_4 = 0;
  do {
    if ((param_1 == 2) && (iVar2 == 0xab4)) {
      return -1;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar1 == 0) {
      if (param_1 == 1) {
        return local_4;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar1 == 0) {
        return local_4;
      }
    }
    local_4 = local_4 + 1;
    iVar2 = iVar2 + 0x224;
    if (0xcd7 < iVar2) {
      return -1;
    }
  } while( true );
}

