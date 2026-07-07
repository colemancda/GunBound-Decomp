/* FUN_00401070 - 0x00401070 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00401070(void)

{
  undefined1 *Value;
  _OSVERSIONINFOA local_94;
  
  local_94.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_94);
  if ((local_94.dwPlatformId != 2) || (Value = &LAB_00401060, local_94.dwMajorVersion < 5)) {
    Value = &LAB_00401000;
  }
  InterlockedExchange((LONG *)&PTR_FUN_0056d0f0,(LONG)Value);
  (*(code *)PTR_FUN_0056d0f0)();
  return;
}

