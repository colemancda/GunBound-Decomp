/* FUN_00543970 - 0x00543970 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00543970(void)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*(void **)((int)&DAT_00f22650 + iVar1) != (void *)0x0) {
      _free(*(void **)((int)&DAT_00f22650 + iVar1));
      *(undefined4 *)((int)&DAT_00f22650 + iVar1) = 0;
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x1000);
  return;
}

