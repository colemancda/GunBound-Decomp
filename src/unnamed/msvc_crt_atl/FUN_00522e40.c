/* FUN_00522e40 - 0x00522e40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00522e40(void)

{
  LPCSTR pCVar1;
  HMODULE hModule;
  
  if (DAT_005b15b4 != '\0') {
    return 1;
  }
  pCVar1 = (LPCSTR)FUN_005218c0(&DAT_0056a9dc);
  hModule = GetModuleHandleA(pCVar1);
  if (hModule == (HMODULE)0x0) {
    return 0;
  }
  pCVar1 = (LPCSTR)FUN_005218c0(&DAT_0056a9bc);
  DAT_005b1580 = GetProcAddress(hModule,pCVar1);
  if (DAT_005b1580 == (FARPROC)0x0) {
    return 0;
  }
  pCVar1 = (LPCSTR)FUN_005218c0(&DAT_0056a9a8);
  DAT_005b1470 = GetProcAddress(hModule,pCVar1);
  if (DAT_005b1470 == (FARPROC)0x0) {
    return 0;
  }
  pCVar1 = (LPCSTR)FUN_005218c0(&DAT_0056a994);
  DAT_005b1588 = GetProcAddress(hModule,pCVar1);
  if (DAT_005b1588 == (FARPROC)0x0) {
    return 0;
  }
  pCVar1 = (LPCSTR)FUN_005218c0(&DAT_0056a980);
  DAT_005b1584 = GetProcAddress(hModule,pCVar1);
  if (DAT_005b1584 == (FARPROC)0x0) {
    return 0;
  }
  pCVar1 = (LPCSTR)FUN_005218c0(&DAT_0056a96c);
  DAT_005b1474 = GetProcAddress(hModule,pCVar1);
  if (DAT_005b1474 == (FARPROC)0x0) {
    return 0;
  }
  DAT_005b15b4 = 1;
  return 1;
}

