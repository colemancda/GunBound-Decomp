/* ScrambleChecksumGuardBytes - 0x0040a240 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void ScrambleChecksumGuardBytes(void)

{
  int in_EAX;
  int iVar1;
  int *unaff_EBX;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = _rand();
    *(char *)(*unaff_EBX + in_EAX * 0x10 + iVar2) = (char)iVar1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  return;
}

