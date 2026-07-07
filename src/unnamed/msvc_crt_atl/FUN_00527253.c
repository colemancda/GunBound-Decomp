/* FUN_00527253 - 0x00527253 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    _strftime
   
   Library: Visual Studio 2003 Release */

size_t __cdecl _strftime(char *_Buf,size_t _SizeInBytes,char *_Format,tm *_Tm)

{
  size_t sVar1;
  
  sVar1 = __Strftime(_Buf,_SizeInBytes,_Format,_Tm,(void *)0x0);
  return sVar1;
}

