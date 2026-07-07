/* FUN_00531da2 - 0x00531da2 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __isatty
   
   Library: Visual Studio 2003 Release */

int __cdecl __isatty(int _FileHandle)

{
  if (DAT_00f28314 <= (uint)_FileHandle) {
    return 0;
  }
  return (int)*(char *)((&DAT_00f28320)[_FileHandle >> 5] + 4 + (_FileHandle & 0x1fU) * 0x24) & 0x40
  ;
}

