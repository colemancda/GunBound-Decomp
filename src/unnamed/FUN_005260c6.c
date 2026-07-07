/* FUN_005260c6 - 0x005260c6 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _fwrite
   
   Library: Visual Studio 2003 Release */

size_t __cdecl _fwrite(void *_Str,size_t _Size,size_t _Count,FILE *_File)

{
  size_t sVar1;
  
  __lock_file(_File);
  sVar1 = __fwrite_lk(_Str,_Size,_Count,_File);
  FUN_00526108();
  return sVar1;
}

