/* FUN_0040b030 - 0x0040b030 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040b030(void)

{
  int iVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar1 + 1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

