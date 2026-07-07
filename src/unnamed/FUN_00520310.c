/* FUN_00520310 - 0x00520310 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00520310(void)

{
  undefined **local_14 [3];
  char *local_8;
  
  if ((_DAT_005b146c & 1) == 0) {
    _DAT_005b146c = _DAT_005b146c | 1;
    local_8 = s_bad_allocation_00544bb0;
    exception::exception((exception *)&DAT_005b1460,&local_8);
    _DAT_005b1460 = &PTR_FUN_00544ba8;
    _atexit(FUN_005439d6);
  }
  exception::exception((exception *)local_14,(exception *)&DAT_005b1460);
  local_14[0] = &PTR_FUN_00544ba8;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_14,&DAT_0055836c);
}

