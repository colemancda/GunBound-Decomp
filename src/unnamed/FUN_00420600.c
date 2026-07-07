/* FUN_00420600 - 0x00420600 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00420600(void)

{
  int iVar1;
  int iVar2;
  int unaff_ESI;
  
  if (unaff_ESI == 0) {
    return 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = unaff_ESI + -1;
  if (iVar1 != 0xff) {
    iVar2 = unaff_ESI;
  }
  return iVar2;
}

