/* FUN_00543950 - 0x00543950 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00543950(void)

{
  DestroyTextureCache((int)&g_textureCache);
  return;
}

