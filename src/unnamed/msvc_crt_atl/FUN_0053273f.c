/* FUN_0053273f - 0x0053273f in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    _mbtowc
   
   Library: Visual Studio 2003 Release */

int __cdecl _mbtowc(wchar_t *_DstCh,char *_SrcCh,size_t _SrcSizeInBytes)

{
  _ptiddata p_Var1;
  pthreadlocinfo ptVar2;
  int iVar3;
  
  p_Var1 = __getptd();
  ptVar2 = (pthreadlocinfo)p_Var1->_tfpecode;
  if (ptVar2 != (pthreadlocinfo)PTR_DAT_0056c48c) {
    ptVar2 = ___updatetlocinfo();
  }
  iVar3 = ___mbtowc_mt(ptVar2,_DstCh,_SrcCh,_SrcSizeInBytes);
  return iVar3;
}

