/* FUN_00520120 - 0x00520120 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00520120(undefined4 param_1,undefined4 param_2)

{
  undefined **local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_10 = &PTR__scalar_deleting_destructor__00544b54;
  local_c = param_1;
  local_8 = param_2;
  local_4 = 0;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(&local_10,&DAT_005582ec);
}

