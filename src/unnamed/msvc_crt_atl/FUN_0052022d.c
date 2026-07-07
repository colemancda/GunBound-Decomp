/* FUN_0052022d - 0x0052022d in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    void * __cdecl operator new(unsigned int)
   
   Library: Visual Studio 2003 Release */

void * __cdecl operator_new(uint param_1)

{
  int iVar1;
  void *pvVar2;
  
  while( true ) {
    pvVar2 = _malloc(param_1);
    if (pvVar2 != (void *)0x0) break;
    iVar1 = __callnewh(param_1);
    if (iVar1 == 0) {
      FUN_00520310();
    }
  }
  return pvVar2;
}

