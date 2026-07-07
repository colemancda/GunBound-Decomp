/* FUN_00501600 - 0x00501600 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00501600(void)

{
  int unaff_ESI;
  
  if (*(void **)(unaff_ESI + 0x1d9c) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x1d9c));
    *(undefined4 *)(unaff_ESI + 0x1d9c) = 0;
  }
  if (*(void **)(unaff_ESI + 0x2020) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x2020));
    *(undefined4 *)(unaff_ESI + 0x2020) = 0;
  }
  return;
}

