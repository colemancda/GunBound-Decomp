/* FUN_00529da5 - 0x00529da5 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    _exit
   
   Library: Visual Studio 2003 Release */

void __cdecl _exit(int _Code)

{
  doexit(_Code,0,0);
  return;
}

