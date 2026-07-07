/* FUN_004f76c0 - 0x004f76c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f76c0(void)

{
  undefined4 *in_EAX;
  
  *in_EAX = 0x67452301;
  in_EAX[1] = 0xefcdab89;
  in_EAX[2] = 0x98badcfe;
  in_EAX[3] = 0x10325476;
  in_EAX[4] = 0xc3d2e1f0;
  in_EAX[5] = 0;
  in_EAX[6] = 0;
  in_EAX[0x17] = 0;
  return;
}

