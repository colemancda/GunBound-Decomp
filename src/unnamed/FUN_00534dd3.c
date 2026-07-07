/* FUN_00534dd3 - 0x00534dd3 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __mbsnbicoll
   
   Library: Visual Studio 2003 Release */

int __cdecl __mbsnbicoll(uchar *_Str1,uchar *_Str2,size_t _MaxCount)

{
  _ptiddata p_Var1;
  pthreadmbcinfo ptVar2;
  int iVar3;
  int unaff_EBP;
  
  p_Var1 = __getptd();
  ptVar2 = p_Var1->_tpxcptinfoptrs;
  if (ptVar2 != DAT_00f29448) {
    ptVar2 = ___updatetmbcinfo();
  }
  if (_MaxCount == 0) {
    return 0;
  }
  iVar3 = ___crtCompareStringA
                    (*(_locale_t *)ptVar2->mbulinfo,(LPCWSTR)0x1,(DWORD)_Str1,(LPCSTR)_MaxCount,
                     (int)_Str2,(LPCSTR)_MaxCount,ptVar2->mbcodepage,unaff_EBP);
  if (iVar3 == 0) {
    return 0x7fffffff;
  }
  return iVar3 + -2;
}

