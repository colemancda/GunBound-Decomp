/* FUN_00543920 - 0x00543920 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * The atexit destructor thunk for the static object at 0xeb1698:
 * `mov eax,0xeb1698; jmp 0x4f2d40`.  The object arrives in EAX, which is
 * why the ported call passes it explicitly.
 */
#include "ghidra_types.h"


void FUN_00543920(void)

{
  FUN_004f2d40((int)DAT_00eb1698);
  return;
}

