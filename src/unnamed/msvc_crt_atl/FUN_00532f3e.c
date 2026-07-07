/* FUN_00532f3e - 0x00532f3e in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __commit
   
   Library: Visual Studio 2003 Release */

int __cdecl __commit(int _FileHandle)

{
  HANDLE hFile;
  BOOL BVar1;
  DWORD *pDVar2;
  undefined4 *puVar3;
  int iVar4;
  DWORD local_20;
  
  if (DAT_00f28314 <= (uint)_FileHandle) {
LAB_00532fe6:
    puVar3 = (undefined4 *)FUN_0052b6d4();
    *puVar3 = 9;
    return -1;
  }
  iVar4 = (_FileHandle & 0x1fU) * 0x24;
  if ((*(byte *)((&DAT_00f28320)[_FileHandle >> 5] + 4 + iVar4) & 1) == 0) goto LAB_00532fe6;
  __lock_fhandle(_FileHandle);
  if ((*(byte *)((&DAT_00f28320)[_FileHandle >> 5] + 4 + iVar4) & 1) != 0) {
    hFile = (HANDLE)__get_osfhandle(_FileHandle);
    BVar1 = FlushFileBuffers(hFile);
    if (BVar1 == 0) {
      local_20 = GetLastError();
    }
    else {
      local_20 = 0;
    }
    if (local_20 == 0) goto LAB_00532fcd;
    pDVar2 = (DWORD *)FUN_0052b6dd();
    *pDVar2 = local_20;
  }
  puVar3 = (undefined4 *)FUN_0052b6d4();
  *puVar3 = 9;
  local_20 = 0xffffffff;
LAB_00532fcd:
  FUN_00532fde();
  return local_20;
}

