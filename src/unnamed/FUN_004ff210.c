/* FUN_004ff210 - 0x004ff210 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ff210(void)

{
  int in_EAX;
  
  if (*(void **)(in_EAX + 0x80) != (void *)0x0) {
    _free(*(void **)(in_EAX + 0x80));
  }
  FUN_00500790();
  FUN_00500a20();
  return;
}

