/* FUN_00525f50 - 0x00525f50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __fsopen
   
   Library: Visual Studio 2003 Release */

FILE * __cdecl __fsopen(char *_Filename,char *_Mode,int _ShFlag)

{
  FILE *pFVar1;
  undefined4 *puVar2;
  
  pFVar1 = __getstream();
  if (pFVar1 == (FILE *)0x0) {
    puVar2 = (undefined4 *)FUN_0052b6d4();
    *puVar2 = 0x18;
    pFVar1 = (FILE *)0x0;
  }
  else {
    pFVar1 = __openfile(_Filename,_Mode,_ShFlag,pFVar1);
    FUN_00525fa2();
  }
  return pFVar1;
}

