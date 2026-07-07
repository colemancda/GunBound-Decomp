/* FUN_00520251 - 0x00520251 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00520251(void)

{
  int unaff_EBP;
  
  FUN_00528bc0();
  FUN_0040b9b0(s_invalid_string_position_00544b7c);
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FUN_00409fd0(unaff_EBP + -0x28);
  *(undefined ***)(unaff_EBP + -0x50) = &PTR_FUN_00544b74;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x50,&DAT_00558458);
}

