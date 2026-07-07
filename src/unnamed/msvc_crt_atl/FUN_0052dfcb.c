/* FUN_0052dfcb - 0x0052dfcb in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __isindst
   
   Library: Visual Studio 2003 Release */

int __cdecl __isindst(tm *_Time)

{
  int iVar1;
  
  __lock(6);
  iVar1 = __isindst_lk();
  FUN_0052e000();
  return iVar1;
}

