/* FUN_004435e0 - 0x004435e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004435e0(void)

{
  int in_EAX;
  undefined1 local_4 [4];
  
  FUN_00443700(local_4,**(undefined4 **)(in_EAX + 4),*(undefined4 **)(in_EAX + 4));
  _free(*(void **)(in_EAX + 4));
  *(undefined4 *)(in_EAX + 4) = 0;
  *(undefined4 *)(in_EAX + 8) = 0;
  return;
}

