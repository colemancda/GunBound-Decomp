/* FUN_00532da0 - 0x00532da0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __unlock_fhandle
   
   Library: Visual Studio 2003 Release */

void __cdecl __unlock_fhandle(int _Filehandle)

{
  LeaveCriticalSection
            ((LPCRITICAL_SECTION)
             ((&DAT_00f28320)[_Filehandle >> 5] + 0xc + (_Filehandle & 0x1fU) * 0x24));
  return;
}

