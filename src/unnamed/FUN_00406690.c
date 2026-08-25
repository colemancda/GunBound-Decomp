/* FUN_00406690 - 0x00406690 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00406690(int param_1,byte *regEax)

{
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((byte)((*regEax + regEax[1]) - 0x34) == regEax[2]) {
    if ((regEax[1] >> (*regEax & 7) & 1) == 1) goto LAB_004066f7;
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  if (param_1 == '\0') {
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    return 0;
  }
LAB_004066f7:
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return 1;
}

