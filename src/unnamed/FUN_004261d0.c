/* FUN_004261d0 - 0x004261d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004261d0(void)

{
  int iVar1;
  byte unaff_BL;
  int unaff_ESI;
  
  (&DAT_006aa624)[unaff_ESI] = unaff_BL;
  if (unaff_BL != 0xff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    (&DAT_006a7670)[unaff_ESI + (uint)unaff_BL * 8 + iVar1] = 1;
  }
  return;
}

