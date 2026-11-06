/* AtlGetThreadACPThunk - 0x00401070 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Identity. This is ATL7's _AtlGetThreadACPThunk, the lazily-bound code
 * page getter used by the CString conversion helpers. It calls GetVersionExA
 * and selects an implementation: on a VER_PLATFORM_WIN32_NT host of major
 * version 5 or later it stores 0x00401060 (a stub that returns 3, i.e.
 * CP_THREAD_ACP) into the function-pointer cell PTR_FUN_0056d0f0 with
 * InterlockedExchange, otherwise it stores 0x00401000 (the fallback that
 * reads the default ANSI code page via GetLocaleInfoA and parses it). It
 * then calls through the cell. The cell's initial value in the .data
 * section is 0x00401070, this function, and both code-page lookups in
 * CString_LoadStringFromInstance call it as a bare function pointer, so
 * the first such call lands here and rebinds the cell. Only this function is named;
 * the two implementation stubs are left as they are.
 */
#include "ghidra_types.h"


void AtlGetThreadACPThunk(void)

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

