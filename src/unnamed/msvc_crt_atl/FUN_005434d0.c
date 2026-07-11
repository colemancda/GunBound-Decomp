/* FUN_005434d0 - 0x005434d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005434d0(void)

{
  undefined1 local_8 [8];
  
  if (DAT_00e55acc != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_8);
  }
  return;
}

