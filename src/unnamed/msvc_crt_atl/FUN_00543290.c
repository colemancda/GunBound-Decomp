/* FUN_00543290 - 0x00543290 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00543290(void)

{
  /* 0x543290 `mov ecx,0xe9b1e0 / jmp 0x4e9ba0`: ECX is the static scene-node
   * object constructed at 0x540e44. The stub is EXCLUDED from the build and
   * the object has no port symbol, so the original address stands in. */
  FUN_004e9ba0((undefined4 *)0xe9b1e0);
  return;
}

