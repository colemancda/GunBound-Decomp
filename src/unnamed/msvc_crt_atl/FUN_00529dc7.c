/* FUN_00529dc7 - 0x00529dc7 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __cexit
   
   Library: Visual Studio 2003 Release */

void __cdecl __cexit(void)

{
  doexit(0,0,1);
  return;
}

