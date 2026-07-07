/* FUN_004f0a20 - 0x004f0a20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f0a20(void)

{
  int in_EAX;
  
  if (*(int *)(in_EAX + 0x1040) != -1) {
    FUN_004f0d70();
  }
  *(undefined ***)(in_EAX + 0x10714) = &PTR_FUN_005572dc;
  DeleteCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x10718));
  return;
}

