/* FUN_00523210 - 0x00523210 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 FUN_00523210(void)

{
  code *pcVar1;
  LPCSTR pCVar2;
  HMODULE pHVar3;
  HMODULE pHVar4;
  undefined4 uVar5;
  int local_8;
  
  local_8 = 0;
  pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056abe0);
  pHVar3 = GetModuleHandleA(pCVar2);
  pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056abcc);
  pHVar4 = GetModuleHandleA(pCVar2);
  if (pHVar4 == (HMODULE)0x0) {
    return 2;
  }
  pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056abb0);
  DAT_005b15bc = (HMODULE)GetProcAddress(pHVar4,pCVar2);
  if (DAT_005b15bc != (HMODULE)0x0) {
    DAT_005b15c8 = QueryPerformanceCounter_exref;
    if (DAT_005b15ac != 0) {
      uVar5 = FUN_005218c0(&DAT_0056ab9c,DAT_005b15bc,QueryPerformanceCounter_exref);
      FUN_00521a90(DAT_005b15ac + 0x24,uVar5);
    }
    if ((DAT_005b15bc < pHVar4) && ((pHVar3 == (HMODULE)0x0 || (DAT_005b15bc < pHVar3)))) {
      if (DAT_005b15ac != 0) {
        uVar5 = FUN_005218c0(&DAT_0056ab84,pHVar4);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar5);
      }
      local_8 = 1;
    }
  }
  pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056ab70);
  DAT_005b15b8 = (HMODULE)GetProcAddress(pHVar4,pCVar2);
  if (DAT_005b15b8 != (HMODULE)0x0) {
    DAT_005b15c4 = GetTickCount_exref;
    if (DAT_005b15ac != 0) {
      uVar5 = FUN_005218c0(&DAT_0056ab5c,DAT_005b15b8,GetTickCount_exref);
      FUN_00521a90(DAT_005b15ac + 0x24,uVar5);
    }
    if ((DAT_005b15b8 < pHVar4) && ((pHVar3 == (HMODULE)0x0 || (DAT_005b15bc < pHVar3)))) {
      if (DAT_005b15ac != 0) {
        uVar5 = FUN_005218c0(&DAT_0056ab44,pHVar4);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar5);
      }
      local_8 = local_8 + 1;
    }
  }
  pcVar1 = timeGetTime_exref;
  timeGetTime();
  pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056ab34);
  pHVar4 = GetModuleHandleA(pCVar2);
  if (pHVar4 != (HMODULE)0x0) {
    pCVar2 = (LPCSTR)FUN_005218c0(&DAT_0056ab24);
    DAT_005b15c0 = (HMODULE)GetProcAddress(pHVar4,pCVar2);
    if (DAT_005b15c0 != (HMODULE)0x0) {
      DAT_005b15cc = pcVar1;
      if (DAT_005b15ac != 0) {
        uVar5 = FUN_005218c0(&DAT_0056ab10,DAT_005b15c0,pcVar1);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar5);
      }
      if ((DAT_005b15c0 < pHVar4) && ((pHVar3 == (HMODULE)0x0 || (DAT_005b15bc < pHVar3)))) {
        if (DAT_005b15ac != 0) {
          uVar5 = FUN_005218c0(&DAT_0056aaf8,pHVar4);
          FUN_00521a90(DAT_005b15ac + 0x24,uVar5);
        }
        local_8 = local_8 + 1;
      }
    }
  }
  DAT_005b15d0 = 1;
  return local_8 == 0;
}

