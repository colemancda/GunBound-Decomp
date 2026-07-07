/* FUN_004dc0f0 - 0x004dc0f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004dc0f0(void)

{
  int iVar1;
  int iVar2;
  int unaff_EDI;
  
  if (unaff_EDI == 0) {
    return 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = unaff_EDI + -1;
  if (iVar1 != 0xff) {
    iVar2 = unaff_EDI;
  }
  return iVar2;
}

