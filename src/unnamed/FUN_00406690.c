/* FUN_00406690 - 0x00406690 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00406690(int param_1)

{
  byte *in_EAX;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((byte)((*in_EAX + in_EAX[1]) - 0x34) == in_EAX[2]) {
    if ((in_EAX[1] >> (*in_EAX & 7) & 1) == 1) goto LAB_004066f7;
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  if (param_1 == '\0') {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    return 0;
  }
LAB_004066f7:
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return 1;
}

