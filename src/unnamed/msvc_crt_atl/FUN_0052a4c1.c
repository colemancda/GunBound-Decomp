/* FUN_0052a4c1 - 0x0052a4c1 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __initptd
   
   Library: Visual Studio 2003 Release */

void __cdecl __initptd(_ptiddata _Ptd,pthreadlocinfo _Locale)

{
  _Ptd->_initaddr = &DAT_0056c240;
  _Ptd->_holdrand = 1;
  return;
}

