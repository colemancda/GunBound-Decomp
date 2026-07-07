/* FUN_00526298 - 0x00526298 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    _fread
   
   Library: Visual Studio 2003 Release */

size_t __cdecl _fread(void *_DstBuf,size_t _ElementSize,size_t _Count,FILE *_File)

{
  size_t sVar1;
  
  __lock_file(_File);
  sVar1 = __fread_lk(_DstBuf,_ElementSize,_Count,_File);
  FUN_005262da();
  return sVar1;
}

