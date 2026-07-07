/* FUN_004eeb70 - 0x004eeb70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004eeb70(void)

{
  char in_AL;
  uint uVar1;
  
  if ((((DAT_00793549 == '\0') || (DAT_0079354b = 1, in_AL == '\0')) &&
      (DAT_0079354b = 0, in_AL == '\0')) && (uVar1 = 1, 1 < DAT_00793560)) {
    do {
      if (DAT_00793549 != '\0') {
        if (uVar1 != 0xffffffff) {
          (**(code **)(**(int **)(DAT_00793554 + uVar1 * 4) + 0xc))();
        }
        if (uVar1 == 0) {
          DAT_00793568 = 0;
        }
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < DAT_00793560);
  }
  return;
}

