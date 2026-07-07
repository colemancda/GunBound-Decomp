/* FUN_0040d170 - 0x0040d170 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void thunk_FUN_004154e0(void)

{
  int in_EAX;
  
  FUN_00415740();
  if (*(void **)(in_EAX + 0x14) != (void *)0x0) {
    _free(*(void **)(in_EAX + 0x14));
  }
  return;
}

