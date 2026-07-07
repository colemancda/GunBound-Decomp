/* FUN_0052cb3c - 0x0052cb3c in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Multiple Matches With Different Base Names
    __lock_file2
    __unlock_file2
   
   Library: Visual Studio 2003 Release */

void __cdecl FID_conflict___lock_file2(int _Index,void *_File)

{
  if (_Index < 0x14) {
    FUN_00529015(_Index + 0x10);
    return;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)((int)_File + 0x20));
  return;
}

