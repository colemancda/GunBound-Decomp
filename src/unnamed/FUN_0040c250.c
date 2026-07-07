/* FUN_0040c250 - 0x0040c250 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0040c250(char *param_1,PHKEY param_2,int param_3,HKEY param_4)

{
  bool bVar1;
  LSTATUS LVar2;
  int iVar3;
  DWORD dwIndex;
  int iVar4;
  DWORD local_2d8;
  DWORD local_2d4;
  DWORD local_2d0;
  HKEY local_2cc;
  _FILETIME local_2c8;
  BYTE local_2c0 [64];
  BYTE local_280 [128];
  CHAR local_200 [256];
  char local_100 [256];
  
  iVar4 = 0;
  dwIndex = 0;
  if (param_4 == (HKEY)0x0) {
    bVar1 = true;
    LVar2 = RegOpenKeyExA(HKEY_CURRENT_USER,&DAT_0055207c,0,0x20019,&param_4);
    if (LVar2 != 0) goto LAB_0040c440;
  }
  else {
    bVar1 = false;
  }
  local_2d8 = 0x40;
  LVar2 = RegQueryValueExA(param_4,s_class_00552074,(LPDWORD)0x0,&local_2d4,local_2c0,&local_2d8);
  if (((LVar2 == 0) && (local_2d4 == 1)) &&
     (iVar3 = __stricmp(param_1,(char *)local_2c0), iVar3 == 0)) {
    local_2d8 = 0x80;
    LVar2 = RegQueryValueExA(param_4,s_driver_0055206c,(LPDWORD)0x0,&local_2d4,local_280,&local_2d8)
    ;
    if ((LVar2 == 0) && (local_2d4 == 1)) {
      _sprintf(local_100,s_System_CurrentControlSet_Service_00552040,local_280);
      LVar2 = RegOpenKeyExA(HKEY_CURRENT_USER,local_100,0,0xf003f,param_2);
      if (LVar2 == 0) {
        iVar4 = 1;
      }
    }
  }
  if (iVar4 < param_3) {
    local_2d0 = 0x100;
    iVar3 = RegEnumKeyExA(param_4,0,local_200,&local_2d0,(LPDWORD)0x0,(LPSTR)0x0,(LPDWORD)0x0,
                          &local_2c8);
    while (iVar3 == 0) {
      dwIndex = dwIndex + 1;
      LVar2 = RegOpenKeyExA(param_4,local_200,0,0x20019,&local_2cc);
      if (LVar2 == 0) {
        iVar3 = FUN_0040c250(param_1,param_2 + iVar4,param_3 - iVar4,local_2cc);
        iVar4 = iVar4 + iVar3;
        RegCloseKey(local_2cc);
      }
      local_2d0 = 0x100;
      iVar3 = RegEnumKeyExA(param_4,dwIndex,local_200,&local_2d0,(LPDWORD)0x0,(LPSTR)0x0,
                            (LPDWORD)0x0,&local_2c8);
    }
  }
LAB_0040c440:
  if ((param_4 != (HKEY)0x0) && (bVar1)) {
    RegCloseKey(param_4);
  }
  return iVar4;
}

