/* FUN_004fd030 - 0x004fd030 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004fd030(void)

{
  undefined2 in_AX;
  
  switch(in_AX) {
  case 0xc011:
  case 0xc018:
  case 0xc041:
  case 0xc042:
  case 0xc043:
    return 1;
  default:
    return 0;
  }
}

