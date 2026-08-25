/* FUN_005028f0 - 0x005028f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005028f0(int regEsi)

{
  
  if (*(void **)(regEsi + 4) != (void *)0x0) {
    _free(*(void **)(regEsi + 4));
  }
  *(undefined4 *)(regEsi + 4) = 0;
  *(undefined4 *)(regEsi + 8) = 0;
  *(undefined4 *)(regEsi + 0xc) = 0;
  return;
}

