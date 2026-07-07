/* FUN_004d0dd0 - 0x004d0dd0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


undefined4 FUN_004d0dd0(void)

{
  int iVar1;
  int iVar2;
  int local_4;
  
  local_4 = 0x7fffffff;
  iVar2 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (-1 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (local_4 < iVar1) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
    }
    iVar2 = iVar2 + 0x224;
  } while (iVar2 < 0x1120);
  return 8;
}

