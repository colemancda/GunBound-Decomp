/* FUN_0052a4a4 - 0x0052a4a4 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __mtterm
   
   Library: Visual Studio 2003 Release */

void __cdecl __mtterm(void)

{
  if (DAT_0056c230 != -1) {
    (*DAT_005b191c)(DAT_0056c230);
    DAT_0056c230 = -1;
  }
  __mtdeletelocks();
  return;
}

