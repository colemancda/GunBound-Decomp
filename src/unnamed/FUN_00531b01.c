/* FUN_00531b01 - 0x00531b01 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___crtInitCritSecAndSpinCount
   
   Library: Visual Studio 2003 Release */

void ___crtInitCritSecAndSpinCount(undefined4 param_1,undefined4 param_2)

{
  HMODULE hModule;
  
  if (DAT_005b1b80 == (code *)0x0) {
    if (DAT_005b18c8 != 1) {
      hModule = GetModuleHandleA(s_kernel32_dll_00544f3c);
      if (hModule != (HMODULE)0x0) {
        DAT_005b1b80 = GetProcAddress(hModule,s_InitializeCriticalSectionAndSpin_00549504);
        if (DAT_005b1b80 != (FARPROC)0x0) goto LAB_00531b4d;
      }
    }
    DAT_005b1b80 = ___crtInitCritSecNoSpinCount_8;
  }
LAB_00531b4d:
  (*DAT_005b1b80)(param_1,param_2);
  return;
}

