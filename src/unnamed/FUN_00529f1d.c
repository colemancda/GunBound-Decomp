/* FUN_00529f1d - 0x00529f1d in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* Library Function - Single Match
    void __cdecl _inconsistency(void)
   
   Library: Visual Studio 2003 Release */

void __cdecl _inconsistency(void)

{
  if (PTR_terminate_0056c130 != (undefined *)0x0) {
    (*(code *)PTR_terminate_0056c130)();
    return;
  }
                    /* WARNING: Subroutine does not return */
  terminate();
}

