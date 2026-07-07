/* FUN_0052835e - 0x0052835e in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0052835e(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_0056bfe8 = *(undefined4 *)(unaff_EBP + 8);
  DAT_0056bfe4 = in_EAX;
  DAT_0056bfec = unaff_EBP;
  return;
}

