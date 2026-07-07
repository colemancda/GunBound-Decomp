/* FUN_00529de5 - 0x00529de5 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __msize
   
   Library: Visual Studio 2003 Release */

size_t __cdecl __msize(void *_Memory)

{
  int iVar1;
  SIZE_T SVar2;
  size_t local_20;
  
  if (DAT_00f296b0 == 3) {
    __lock(4);
    iVar1 = ___sbh_find_block(_Memory);
    if (iVar1 != 0) {
      local_20 = *(int *)((int)_Memory + -4) - 9;
    }
    FUN_00529e52();
    if (iVar1 != 0) {
      return local_20;
    }
  }
  SVar2 = HeapSize(DAT_00f296ac,0,_Memory);
  return SVar2;
}

