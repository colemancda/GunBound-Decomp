/* FUN_0040d200 - 0x0040d200 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


int __fastcall FUN_0040d200(int param_1)

{
  uint uVar1;
  int aiStack_1c [7];
  
  aiStack_1c[1] = 0;
  aiStack_1c[2] = 0x3c;
  aiStack_1c[3] = 0x46;
  aiStack_1c[4] = 0x4b;
  aiStack_1c[5] = 0x55;
  aiStack_1c[6] = 100;
  uVar1 = 1;
  do {
    if (param_1 < aiStack_1c[uVar1 + 1]) {
      return aiStack_1c[uVar1];
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 6);
  return 100;
}

