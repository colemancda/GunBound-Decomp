/* FUN_0040afb0 - 0x0040afb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040afb0(void)

{
  int iVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  iVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar2 + iVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

