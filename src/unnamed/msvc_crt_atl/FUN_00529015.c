/* FUN_00529015 - 0x00529015 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00529015(int param_1)

{
  LeaveCriticalSection((LPCRITICAL_SECTION)(&DAT_0056c008)[param_1 * 2]);
  return;
}

