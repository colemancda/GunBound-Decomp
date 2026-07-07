/* FUN_00529ce2 - 0x00529ce2 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _doexit
   
   Library: Visual Studio 2003 Release */

void __cdecl doexit(UINT param_1,int param_2,int param_3)

{
  HANDLE hProcess;
  UINT uExitCode;
  
  __lock(8);
  if (DAT_005b1908 == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_005b1904 = 1;
  DAT_005b1900 = (undefined1)param_3;
  if (param_2 == 0) {
    if (DAT_00f29688 != (undefined4 *)0x0) {
      while( true ) {
        DAT_00f29684 = DAT_00f29684 + -1;
        if (DAT_00f29684 < DAT_00f29688) break;
        if ((code *)*DAT_00f29684 != (code *)0x0) {
          (*(code *)*DAT_00f29684)();
        }
      }
    }
    __initterm(&DAT_00563720);
  }
  __initterm(&DAT_0056372c);
  FUN_00529d91();
  if (param_3 == 0) {
    DAT_005b1908 = 1;
                    /* WARNING: Subroutine does not return */
    ___crtExitProcess(param_1);
  }
  return;
}

