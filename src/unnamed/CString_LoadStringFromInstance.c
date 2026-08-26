/* CString_LoadStringFromInstance - 0x004055f0 in the original binary.
 *
 * CString::LoadString(hInst, nID): FindResourceA(param_1, (regEax >> 4) + 1,
 * RT_STRING), then walks the string-table block to entry nID & 0xf and copies
 * it into the CString at *param_2.  ConstructStringFromText passes the
 * HMODULE that FUN_00401880 (AtlFindStringResourceInstance) resolved for the
 * same nID one line earlier.
 *
 * RE-SLOTTED AND EAX RECOVERED (2026-08-24).  CString::LoadString(hInst, nID):
 * FindResourceA(param_1, (regEax >> 4) + 1, RT_STRING).  Sole call site
 * 0x0040556b in ConstructStringFromText: ECX = iVar2, the HMODULE
 * FUN_00401880 (AtlFindStringResourceInstance) just returned; push = param_2,
 * the CString; EAX = (uint)param_1 & 0xffff, the string id.  The port had
 * passed the CString as the HMODULE.
 */
#include "ghidra_types.h"


undefined4 __thiscall CString_LoadStringFromInstance(HMODULE param_1,int *param_2,uint regEax)

{
  HRSRC pHVar1;
  ushort *puVar2;
  uint uVar3;
  UINT UVar4;
  DWORD DVar5;
  LPCWSTR lpWideCharStr;
  LPCWSTR lpWideCharStr_00;
  LPSTR pCVar6;
  int iVar7;
  int cbMultiByte;
  LPCSTR pCVar8;
  LPBOOL pBVar9;
  
  pHVar1 = FindResourceA(param_1,(LPCSTR)((regEax >> 4) + 1 & 0xffff),&DAT_00000006);
  if (pHVar1 != (HRSRC)0x0) {
    puVar2 = (ushort *)LoadStringTableEntry(param_1,regEax,pHVar1);
    if (puVar2 != (ushort *)0x0) {
      uVar3 = (uint)*puVar2;
      pBVar9 = (LPBOOL)0x0;
      pCVar8 = (LPCSTR)0x0;
      iVar7 = 0;
      pCVar6 = (LPSTR)0x0;
      lpWideCharStr_00 = (LPCWSTR)(puVar2 + 1);
      DVar5 = 0;
      lpWideCharStr = lpWideCharStr_00;
      UVar4 = (*(code *)PTR_FUN_0056d0f0)();
      iVar7 = WideCharToMultiByte(UVar4,DVar5,lpWideCharStr,uVar3,pCVar6,iVar7,pCVar8,pBVar9);
      if ((int)(1U - *(int *)(*param_2 + -4) | *(int *)(*param_2 + -8) - iVar7) < 0) {
        FUN_004057c0();
      }
      pCVar6 = (LPSTR)*param_2;
      uVar3 = (uint)*puVar2;
      pBVar9 = (LPBOOL)0x0;
      pCVar8 = (LPCSTR)0x0;
      DVar5 = 0;
      cbMultiByte = iVar7;
      UVar4 = (*(code *)PTR_FUN_0056d0f0)();
      WideCharToMultiByte(UVar4,DVar5,lpWideCharStr_00,uVar3,pCVar6,cbMultiByte,pCVar8,pBVar9);
      if ((-1 < iVar7) && (iVar7 <= *(int *)(*param_2 + -8))) {
        *(int *)(*param_2 + -0xc) = iVar7;
        *(undefined1 *)(iVar7 + *param_2) = 0;
        return 1;
      }
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
  }
  return 0;
}

