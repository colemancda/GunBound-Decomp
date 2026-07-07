/* FUN_00536072 - 0x00536072 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __strdup
   
   Library: Visual Studio 2003 Release */

char * __cdecl __strdup(char *_Src)

{
  size_t sVar1;
  void *pvVar2;
  char *pcVar3;
  
  if (_Src != (char *)0x0) {
    sVar1 = _strlen(_Src);
    pvVar2 = _malloc(sVar1 + 1);
    if (pvVar2 != (void *)0x0) {
      pcVar3 = (char *)FUN_0052baa0(pvVar2,_Src);
      return pcVar3;
    }
  }
  return (char *)0x0;
}

