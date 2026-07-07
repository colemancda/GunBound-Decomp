/* FUN_00406860 - 0x00406860 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


bool FUN_00406860(void)

{
  byte bVar1;
  byte bVar2;
  byte *in_EAX;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  bVar1 = *in_EAX;
  bVar2 = in_EAX[1];
  if ((byte)((bVar1 + bVar2) - 0x34) != in_EAX[2]) {
    DAT_00793514 = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    return true;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return (bVar2 >> (bVar1 & 7) & 1) != 1;
}

