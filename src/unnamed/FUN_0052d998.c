/* FUN_0052d998 - 0x0052d998 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __tzset_lk
   
   Library: Visual Studio 2003 Release */

void __tzset_lk(void)

{
  char cVar1;
  char cVar2;
  UINT CodePage;
  char *_Str1;
  int iVar3;
  size_t sVar4;
  long lVar5;
  DWORD DVar6;
  char *_Str;
  int local_20 [3];
  undefined1 local_14 [8];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00545248;
  uStack_c = 0x52d9a4;
  __lock(7);
  CodePage = DAT_005b1b9c;
  local_8 = (undefined *)0x0;
  DAT_005b19ec = 0;
  DAT_0056c91c = 0xffffffff;
  DAT_0056c910 = 0xffffffff;
  _Str1 = (char *)__getenv_lk(&DAT_00545244);
  if ((_Str1 == (char *)0x0) || (*_Str1 == '\0')) {
    if (DAT_005b19f0 != (char *)0x0) {
      _free(DAT_005b19f0);
      DAT_005b19f0 = (char *)0x0;
    }
    DVar6 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&DAT_005b1940);
    if (DVar6 != 0xffffffff) {
      DAT_005b19ec = 1;
      _DAT_0056c878 = DAT_005b1940 * 0x3c;
      if (DAT_005b1986 != 0) {
        _DAT_0056c878 = _DAT_0056c878 + DAT_005b1994 * 0x3c;
      }
      if ((DAT_005b19da == 0) || (DAT_005b19e8 == 0)) {
        DAT_0056c87c = 0;
        DAT_0056c880 = 0;
      }
      else {
        DAT_0056c87c = 1;
        DAT_0056c880 = (DAT_005b19e8 - DAT_005b1994) * 0x3c;
      }
      iVar3 = WideCharToMultiByte(CodePage,0,(LPCWSTR)&DAT_005b1944,-1,PTR_DAT_0056c908,0x3f,
                                  (LPCSTR)0x0,local_20);
      if ((iVar3 == 0) || (local_20[0] != 0)) {
        *PTR_DAT_0056c908 = 0;
      }
      else {
        PTR_DAT_0056c908[0x3f] = 0;
      }
      iVar3 = WideCharToMultiByte(CodePage,0,(LPCWSTR)&DAT_005b1998,-1,PTR_DAT_0056c90c,0x3f,
                                  (LPCSTR)0x0,local_20);
      if ((iVar3 == 0) || (local_20[0] != 0)) {
        *PTR_DAT_0056c90c = 0;
      }
      else {
        PTR_DAT_0056c90c[0x3f] = 0;
      }
    }
  }
  else {
    if (DAT_005b19f0 != (char *)0x0) {
      iVar3 = _strcmp(_Str1,DAT_005b19f0);
      if (iVar3 == 0) goto LAB_0052db9c;
      if (DAT_005b19f0 != (char *)0x0) {
        _free(DAT_005b19f0);
      }
    }
    sVar4 = _strlen(_Str1);
    DAT_005b19f0 = _malloc(sVar4 + 1);
    if (DAT_005b19f0 != (char *)0x0) {
      FUN_0052baa0(DAT_005b19f0,_Str1);
      local_8 = (undefined *)0xffffffff;
      FUN_0052dbb3();
      _strncpy(PTR_DAT_0056c908,_Str1,3);
      PTR_DAT_0056c908[3] = 0;
      _Str = _Str1 + 3;
      cVar1 = *_Str;
      if (cVar1 == '-') {
        _Str = _Str1 + 4;
      }
      lVar5 = _atol(_Str);
      _DAT_0056c878 = lVar5 * 0xe10;
      for (; (cVar2 = *_Str, cVar2 == '+' || (('/' < cVar2 && (cVar2 < ':')))); _Str = _Str + 1) {
      }
      if (*_Str == ':') {
        _Str = _Str + 1;
        lVar5 = _atol(_Str);
        _DAT_0056c878 = _DAT_0056c878 + lVar5 * 0x3c;
        for (; ('/' < *_Str && (*_Str < ':')); _Str = _Str + 1) {
        }
        if (*_Str == ':') {
          _Str = _Str + 1;
          lVar5 = _atol(_Str);
          _DAT_0056c878 = _DAT_0056c878 + lVar5;
          for (; ('/' < *_Str && (*_Str < ':')); _Str = _Str + 1) {
          }
        }
      }
      if (cVar1 == '-') {
        _DAT_0056c878 = -_DAT_0056c878;
      }
      DAT_0056c87c = (int)*_Str;
      if (DAT_0056c87c != 0) {
        _strncpy(PTR_DAT_0056c90c,_Str,3);
        PTR_DAT_0056c90c[3] = 0;
        return;
      }
      *PTR_DAT_0056c90c = 0;
      return;
    }
  }
LAB_0052db9c:
  __local_unwind2(local_14,0xffffffff);
  return;
}

