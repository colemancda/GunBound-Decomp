/* FUN_0052cabb - 0x0052cabb in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __lock_file
   
   Library: Visual Studio 2003 Release */

void __cdecl __lock_file(FILE *_File)

{
  if (((FILE *)0x56c5cf < _File) && (_File < (FILE *)0x56c831)) {
    __lock(((int)&_File[-0x2b62f]._file >> 5) + 0x10);
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)(_File + 1));
  return;
}

