/* AtlFindStringResourceInstance - 0x00401880 in the original binary.
 *
 * NAMED (2026-10-29): ATL7's AtlFindStringResourceInstance(nID,
 * wLanguage) from atlcore.h, matched exactly:
 *
 *   hInst = _AtlBaseModule.GetHInstanceAt(0)      ECX = 0x5b13fc, push 0
 *   while (hInst != NULL && pImage == NULL) {     test esi / test edi
 *     pImage = AtlGetStringResourceImage(hInst, nID, wLanguage)
 *       - FindResourceExA(hInst, RT_STRING,       push 6 at 0x4018b7
 *           MAKEINTRESOURCE((nID >> 4) + 1),      shr 4; inc; movzx
 *           wLanguage)
 *       - then the block walk, 0x401820           LoadStringTableEntry
 *     if (pImage == NULL)
 *       hInst = GetHInstanceAt(++iIndex)          local counter from 1
 *   }
 *   return hInst                                  0 when the walk ends
 *
 * Library identity, plus the caller: ConstructStringFromText (0x405510)
 * is CStringT's from-text constructor, and its resource-ID arm (the
 * `IS_INTRESOURCE` test on the source pointer's high word) calls this
 * with (id, 0) and passes the returned HINSTANCE straight to
 * CString_LoadStringFromInstance - CStringT::LoadString(nID)'s
 * `FindStringResourceInstance(nID)` then `LoadString(hInst, nID)`.
 * `_AtlBaseModule` is the CAtlBaseModule at 0x5b13fc.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


HMODULE AtlFindStringResourceInstance(uint param_1,WORD param_2)

{
  HMODULE hModule;
  HRSRC pHVar1;
  int iVar2;
  int local_4;
  
  hModule = ATL_CAtlBaseModule_GetHInstanceAt((CAtlBaseModule *)&DAT_005b13fc,0);
  local_4 = 1;
  while( true ) {
    if (hModule == (HMODULE)0x0) {
      return (HMODULE)0x0;
    }
    pHVar1 = FindResourceExA(hModule,&DAT_00000006,(LPCSTR)((param_1 >> 4) + 1 & 0xffff),param_2);
    if ((pHVar1 != (HRSRC)0x0) && (iVar2 = LoadStringTableEntry(hModule,param_1,pHVar1), iVar2 != 0)) break;
    hModule = ATL_CAtlBaseModule_GetHInstanceAt((CAtlBaseModule *)&DAT_005b13fc,local_4);
    local_4 = local_4 + 1;
  }
  return hModule;
}

