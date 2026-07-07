/* FUN_00401880 - 0x00401880 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


HMODULE FUN_00401880(uint param_1,WORD param_2)

{
  HMODULE hModule;
  HRSRC pHVar1;
  int iVar2;
  int local_4;
  
  hModule = ATL::CAtlBaseModule::GetHInstanceAt((CAtlBaseModule *)&DAT_005b13fc,0);
  local_4 = 1;
  while( true ) {
    if (hModule == (HMODULE)0x0) {
      return (HMODULE)0x0;
    }
    pHVar1 = FindResourceExA(hModule,&DAT_00000006,(LPCSTR)((param_1 >> 4) + 1 & 0xffff),param_2);
    if ((pHVar1 != (HRSRC)0x0) && (iVar2 = FUN_00401820(hModule), iVar2 != 0)) break;
    hModule = ATL::CAtlBaseModule::GetHInstanceAt((CAtlBaseModule *)&DAT_005b13fc,local_4);
    local_4 = local_4 + 1;
  }
  return hModule;
}

