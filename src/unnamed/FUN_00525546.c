/* FUN_00525546 - 0x00525546 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */

void __cdecl _free(void *_Memory)

{
  int iVar1;
  
  if (_Memory != (void *)0x0) {
    if (DAT_00f296b0 == 3) {
      __lock(4);
      iVar1 = ___sbh_find_block(_Memory);
      if (iVar1 != 0) {
        ___sbh_free_block(iVar1,_Memory);
      }
      FUN_00525113();
      if (iVar1 != 0) {
        return;
      }
    }
    HeapFree(DAT_00f296ac,0,_Memory);
  }
  return;
}

