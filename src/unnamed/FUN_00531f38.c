/* FUN_00531f38 - 0x00531f38 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    ___convertcp
   
   Library: Visual Studio 2003 Release */

LPSTR ___convertcp(UINT param_1,UINT param_2,char *param_3,size_t *param_4,LPSTR param_5,int param_6
                  )

{
  size_t cbMultiByte;
  bool bVar1;
  bool bVar2;
  BOOL BVar3;
  int iVar4;
  size_t sVar5;
  LPCWSTR local_4c;
  size_t local_3c;
  LPSTR lpMultiByteStr;
  _cpinfo local_34;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00549a58;
  uStack_c = 0x531f44;
  local_20 = DAT_0056bfd4;
  lpMultiByteStr = (LPSTR)0x0;
  bVar2 = false;
  cbMultiByte = *param_4;
  bVar1 = false;
  if (param_1 != param_2) {
    BVar3 = GetCPInfo(param_1,&local_34);
    if ((((BVar3 != 0) && (local_34.MaxCharSize == 1)) &&
        (BVar3 = GetCPInfo(param_2,&local_34), BVar3 != 0)) && (local_34.MaxCharSize == 1)) {
      bVar1 = true;
    }
    if ((bVar1) && (local_3c = cbMultiByte, cbMultiByte == 0xffffffff)) {
      sVar5 = _strlen(param_3);
      local_3c = sVar5 + 1;
    }
    if ((!bVar1) &&
       (local_3c = MultiByteToWideChar(param_1,1,param_3,cbMultiByte,(LPWSTR)0x0,0), local_3c == 0))
    {
      return (LPSTR)0x0;
    }
    local_8 = (undefined *)0x0;
    local_1c = &stack0xffffffa8;
    local_4c = (LPCWSTR)&stack0xffffffa8;
    _memset(&stack0xffffffa8,0,local_3c * 2);
    local_8 = (undefined *)0xffffffff;
    if (&stack0x00000000 == (undefined1 *)0x58) {
      local_4c = _calloc(2,local_3c);
      if (local_4c == (LPCWSTR)0x0) {
        return (LPSTR)0x0;
      }
      bVar2 = true;
    }
    iVar4 = MultiByteToWideChar(param_1,1,param_3,cbMultiByte,local_4c,local_3c);
    if (iVar4 != 0) {
      if (param_5 == (LPSTR)0x0) {
        if (((bVar1) ||
            (local_3c = WideCharToMultiByte(param_2,0,local_4c,local_3c,(LPSTR)0x0,0,(LPCSTR)0x0,
                                            (LPBOOL)0x0), local_3c != 0)) &&
           (lpMultiByteStr = _calloc(1,local_3c), lpMultiByteStr != (LPSTR)0x0)) {
          sVar5 = WideCharToMultiByte(param_2,0,local_4c,local_3c,lpMultiByteStr,local_3c,
                                      (LPCSTR)0x0,(LPBOOL)0x0);
          if (sVar5 == 0) {
            _free(lpMultiByteStr);
            lpMultiByteStr = (LPSTR)0x0;
          }
          else if (cbMultiByte != 0xffffffff) {
            *param_4 = sVar5;
          }
        }
      }
      else {
        iVar4 = WideCharToMultiByte(param_2,0,local_4c,local_3c,param_5,param_6,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        if (iVar4 != 0) {
          lpMultiByteStr = param_5;
        }
      }
    }
  }
  if (bVar2) {
    _free(local_4c);
  }
  return lpMultiByteStr;
}

