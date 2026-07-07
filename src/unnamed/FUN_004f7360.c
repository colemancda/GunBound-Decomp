/* FUN_004f7360 - 0x004f7360 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


byte __fastcall FUN_004f7360(int param_1)

{
  byte bVar1;
  
  bVar1 = 0;
  do {
    if (*(char *)((uint)bVar1 + param_1) == '\0') {
      return bVar1;
    }
    bVar1 = bVar1 + 1;
  } while (bVar1 < 0x10);
  return 0x10;
}

