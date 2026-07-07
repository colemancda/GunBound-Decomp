/* FUN_0053307b - 0x0053307b in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___crtMessageBoxA
   
   Library: Visual Studio 2003 Release */

int __cdecl ___crtMessageBoxA(LPCSTR _LpText,LPCSTR _LpCaption,UINT _UType)

{
  HMODULE hModule;
  int iVar1;
  int iVar2;
  undefined1 local_14 [8];
  byte local_c;
  undefined1 local_8 [4];
  
  iVar2 = 0;
  if (DAT_005b1c00 == (FARPROC)0x0) {
    hModule = LoadLibraryA(s_user32_dll_00549b20);
    if ((hModule == (HMODULE)0x0) ||
       (DAT_005b1c00 = GetProcAddress(hModule,s_MessageBoxA_00549b14), DAT_005b1c00 == (FARPROC)0x0)
       ) {
      return 0;
    }
    DAT_005b1c04 = GetProcAddress(hModule,s_GetActiveWindow_00549b04);
    DAT_005b1c08 = GetProcAddress(hModule,s_GetLastActivePopup_00549af0);
    if ((DAT_005b18c8 == 2) &&
       (DAT_005b1c10 = GetProcAddress(hModule,s_GetUserObjectInformationA_00549ad4),
       DAT_005b1c10 != (FARPROC)0x0)) {
      DAT_005b1c0c = GetProcAddress(hModule,s_GetProcessWindowStation_00549abc);
    }
  }
  if ((DAT_005b1c0c == (FARPROC)0x0) ||
     (((iVar1 = (*DAT_005b1c0c)(), iVar1 != 0 &&
       (iVar1 = (*DAT_005b1c10)(iVar1,1,local_14,0xc,local_8), iVar1 != 0)) && ((local_c & 1) != 0))
     )) {
    if (((DAT_005b1c04 != (FARPROC)0x0) && (iVar2 = (*DAT_005b1c04)(), iVar2 != 0)) &&
       (DAT_005b1c08 != (FARPROC)0x0)) {
      iVar2 = (*DAT_005b1c08)(iVar2);
    }
  }
  else if (DAT_005b18d4 < 4) {
    _UType = _UType | 0x40000;
  }
  else {
    _UType = _UType | 0x200000;
  }
  iVar2 = (*DAT_005b1c00)(iVar2,_LpText,_LpCaption,_UType);
  return iVar2;
}

