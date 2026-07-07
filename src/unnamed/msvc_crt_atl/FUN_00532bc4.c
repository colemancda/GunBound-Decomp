/* FUN_00532bc4 - 0x00532bc4 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __set_osfhnd
   
   Library: Visual Studio 2003 Release */

int __cdecl __set_osfhnd(int param_1,intptr_t param_2)

{
  undefined4 *puVar1;
  int iVar2;
  DWORD nStdHandle;
  
  if ((uint)param_1 < DAT_00f28314) {
    iVar2 = (param_1 & 0x1fU) * 0x24;
    if (*(int *)(iVar2 + (&DAT_00f28320)[param_1 >> 5]) == -1) {
      if (DAT_0056bf74 == 1) {
        if (param_1 == 0) {
          nStdHandle = 0xfffffff6;
        }
        else if (param_1 == 1) {
          nStdHandle = 0xfffffff5;
        }
        else {
          if (param_1 != 2) goto LAB_00532c1d;
          nStdHandle = 0xfffffff4;
        }
        SetStdHandle(nStdHandle,(HANDLE)param_2);
      }
LAB_00532c1d:
      *(intptr_t *)(iVar2 + (&DAT_00f28320)[param_1 >> 5]) = param_2;
      return 0;
    }
  }
  puVar1 = (undefined4 *)FUN_0052b6d4();
  *puVar1 = 9;
  puVar1 = (undefined4 *)FUN_0052b6dd();
  *puVar1 = 0;
  return -1;
}

