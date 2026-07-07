/* FUN_004055f0 - 0x004055f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004055f0(HMODULE param_1,int *param_2)

{
  uint in_EAX;
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
  
  pHVar1 = FindResourceA(param_1,(LPCSTR)((in_EAX >> 4) + 1 & 0xffff),&DAT_00000006);
  if (pHVar1 != (HRSRC)0x0) {
    puVar2 = (ushort *)FUN_00401820(param_1);
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
      FUN_004010c0(0x80070057);
    }
  }
  return 0;
}

