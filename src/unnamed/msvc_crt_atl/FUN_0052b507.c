/* FUN_0052b507 - 0x0052b507 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __stricmp
   
   Library: Visual Studio 2003 Release */

int __cdecl __stricmp(char *_Str1,char *_Str2)

{
  _ptiddata p_Var1;
  pthreadlocinfo ptVar2;
  int iVar3;
  int iVar4;
  
  p_Var1 = __getptd();
  ptVar2 = (pthreadlocinfo)p_Var1->_tfpecode;
  if (ptVar2 != (pthreadlocinfo)PTR_DAT_0056c48c) {
    ptVar2 = ___updatetlocinfo();
  }
  if (ptVar2->lc_category[0].wlocale == (wchar_t *)0x0) {
    iVar3 = ___ascii_stricmp(_Str1,_Str2);
  }
  else {
    do {
      iVar3 = ___tolower_mt(ptVar2,*_Str1);
      _Str1 = _Str1 + 1;
      iVar4 = ___tolower_mt(ptVar2,*_Str2);
      _Str2 = _Str2 + 1;
      if (iVar3 == 0) break;
    } while (iVar3 == iVar4);
    iVar3 = iVar3 - iVar4;
  }
  return iVar3;
}

