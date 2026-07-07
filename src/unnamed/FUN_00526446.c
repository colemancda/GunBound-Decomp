/* FUN_00526446 - 0x00526446 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _ftell
   
   Library: Visual Studio 2003 Release */

long __cdecl _ftell(FILE *_File)

{
  long lVar1;
  
  __lock_file(_File);
  lVar1 = __ftell_lk(_File);
  FUN_0052647d();
  return lVar1;
}

