/* FUN_00520291 - 0x00520291 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00520291(void)

{
  int unaff_EBP;
  
  FUN_00528bc0();
  FUN_0040b9b0(s_string_too_long_00544b94);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_00409fd0(unaff_EBP + -0x28);
  *(undefined ***)(unaff_EBP + -0x50) = &PTR_FUN_00544b68;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x50,&DAT_0055841c);
}

