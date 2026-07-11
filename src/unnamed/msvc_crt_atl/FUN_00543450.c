/* FUN_00543450 - 0x00543450 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00543450(void)

{
  undefined1 local_8 [8];
  
  if (DAT_00e9ba54 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_8);
  }
  return;
}

