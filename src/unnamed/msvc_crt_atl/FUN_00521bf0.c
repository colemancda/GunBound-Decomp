/* FUN_00521bf0 - 0x00521bf0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00521bf0(int param_1)

{
  LPCSTR pCVar1;
  HMODULE hModule;
  FARPROC pFVar2;
  _OSVERSIONINFOA local_94;
  
  local_94.dwOSVersionInfoSize = 0x94;
  GetVersionExA(&local_94);
  if (local_94.dwPlatformId == 2) {
    return 1;
  }
  pCVar1 = (LPCSTR)FUN_005218c0(&DAT_0056a428);
  hModule = GetModuleHandleA(pCVar1);
  pCVar1 = (LPCSTR)FUN_005218c0(&DAT_0056a414);
  pFVar2 = GetProcAddress(hModule,pCVar1);
  if (pFVar2 == (FARPROC)0x0) {
    pCVar1 = (LPCSTR)FUN_005218c0(&DAT_0056a3fc);
    pFVar2 = GetProcAddress(hModule,pCVar1);
    if (pFVar2 == (FARPROC)0x0) {
      return 0;
    }
  }
  *(undefined1 *)(param_1 + 0x1140) = 1;
  return 1;
}

