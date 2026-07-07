/* FUN_0052df7f - 0x0052df7f in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___tzset
   
   Library: Visual Studio 2003 Release */

void __cdecl ___tzset(void)

{
  if (DAT_005b19f4 == 0) {
    __lock(6);
    if (DAT_005b19f4 == 0) {
      __tzset_lk();
      DAT_005b19f4 = DAT_005b19f4 + 1;
    }
    FUN_0052dfc2();
  }
  return;
}

