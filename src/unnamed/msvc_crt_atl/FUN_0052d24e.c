/* FUN_0052d24e - 0x0052d24e in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __close
   
   Library: Visual Studio 2003 Release */

int __cdecl __close(int _FileHandle)

{
  undefined4 *puVar1;
  int iVar2;
  int local_20;
  
  if ((uint)_FileHandle < DAT_00f28314) {
    iVar2 = (_FileHandle & 0x1fU) * 0x24;
    if ((*(byte *)((&DAT_00f28320)[_FileHandle >> 5] + 4 + iVar2) & 1) != 0) {
      __lock_fhandle(_FileHandle);
      if ((*(byte *)((&DAT_00f28320)[_FileHandle >> 5] + 4 + iVar2) & 1) == 0) {
        puVar1 = (undefined4 *)FUN_0052b6d4();
        *puVar1 = 9;
        local_20 = -1;
      }
      else {
        local_20 = __close_lk(_FileHandle);
      }
      FUN_0052d2c5();
      return local_20;
    }
  }
  puVar1 = (undefined4 *)FUN_0052b6d4();
  *puVar1 = 9;
  puVar1 = (undefined4 *)FUN_0052b6dd();
  *puVar1 = 0;
  return -1;
}

