/* FUN_005286d2 - 0x005286d2 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    int __cdecl IsExceptionObjectToBeDestroyed(void *)
   
   Library: Visual Studio 2003 Release */

int __cdecl IsExceptionObjectToBeDestroyed(void *param_1)

{
  _ptiddata p_Var1;
  int *piVar2;
  
  p_Var1 = __getptd();
  piVar2 = p_Var1->_curexception;
  while( true ) {
    if (piVar2 == (int *)0x0) {
      return 1;
    }
    if ((void *)*piVar2 == param_1) break;
    piVar2 = (int *)piVar2[1];
  }
  return 0;
}

