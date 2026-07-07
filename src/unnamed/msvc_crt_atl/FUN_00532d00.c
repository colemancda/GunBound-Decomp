/* FUN_00532d00 - 0x00532d00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __lock_fhandle
   
   Library: Visual Studio 2003 Release */

int __cdecl __lock_fhandle(int _Filehandle)

{
  int iVar1;
  int iVar2;
  undefined1 local_14 [8];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00549a88;
  uStack_c = 0x532d0c;
  iVar1 = (&DAT_00f28320)[_Filehandle >> 5] + (_Filehandle & 0x1fU) * 0x24;
  if (*(int *)(iVar1 + 8) == 0) {
    __lock(10);
    local_8 = (undefined *)0x0;
    if (*(int *)(iVar1 + 8) == 0) {
      iVar2 = ___crtInitCritSecAndSpinCount(iVar1 + 0xc,4000);
      if (iVar2 == 0) {
        __local_unwind2(local_14,0xffffffff);
        return 0;
      }
      *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + 1;
    }
    local_8 = (undefined *)0xffffffff;
    FUN_00532d97();
  }
  EnterCriticalSection
            ((LPCRITICAL_SECTION)
             ((&DAT_00f28320)[_Filehandle >> 5] + 0xc + (_Filehandle & 0x1fU) * 0x24));
  return 1;
}

