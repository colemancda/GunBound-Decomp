/* FUN_004e9490 - 0x004e9490 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004e9490(float param_1)

{
  if (ABS(param_1) < _DAT_0054c870) {
    return 1;
  }
  return 0;
}

