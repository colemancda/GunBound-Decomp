/* FUN_00534a6b - 0x00534a6b in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    int __cdecl _ValidateExecute(int (__stdcall*)(void))
   
   Library: Visual Studio 2003 Release */

int __cdecl _ValidateExecute(_func_int *param_1)

{
  BOOL BVar1;
  
  BVar1 = IsBadCodePtr((FARPROC)param_1);
  return (uint)(BVar1 == 0);
}

