/* FUN_005287d2 - 0x005287d2 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __callnewh
   
   Library: Visual Studio 2003 Release */

int __cdecl __callnewh(size_t _Size)

{
  int iVar1;
  
  if (DAT_005b176c != (code *)0x0) {
    iVar1 = (*DAT_005b176c)(_Size);
    if (iVar1 != 0) {
      return 1;
    }
  }
  return 0;
}

