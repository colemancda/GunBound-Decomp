/* FUN_00415ca0 - 0x00415ca0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00415ca0(void)

{
  undefined4 *in_EAX;
  
  *in_EAX = 0;
  in_EAX[1] = 1;
  in_EAX[2] = 2;
  in_EAX[3] = 3;
  in_EAX[4] = 4;
  in_EAX[5] = 5;
  in_EAX[6] = 6;
  in_EAX[7] = 7;
  in_EAX[8] = 0;
  return;
}

