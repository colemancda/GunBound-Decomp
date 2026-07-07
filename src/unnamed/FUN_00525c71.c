/* FUN_00525c71 - 0x00525c71 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    _atol
   
   Library: Visual Studio 2003 Release */

long __cdecl _atol(char *_Str)

{
  _ptiddata p_Var1;
  pthreadlocinfo ptVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  byte *pbVar7;
  
  p_Var1 = __getptd();
  ptVar2 = (pthreadlocinfo)p_Var1->_tfpecode;
  if (ptVar2 != (pthreadlocinfo)PTR_DAT_0056c48c) {
    ptVar2 = ___updatetlocinfo();
  }
  while( true ) {
    if ((int)ptVar2->lc_category[1].refcount < 2) {
      uVar3 = *(byte *)((int)ptVar2->lc_category[3].refcount + (uint)(byte)*_Str * 2) & 8;
    }
    else {
      uVar3 = ___isctype_mt(ptVar2,(uint)(byte)*_Str,8);
    }
    if (uVar3 == 0) break;
    _Str = _Str + 1;
  }
  uVar3 = (uint)(byte)*_Str;
  pbVar7 = (byte *)(_Str + 1);
  if ((uVar3 == 0x2d) || (uVar5 = uVar3, uVar3 == 0x2b)) {
    uVar5 = (uint)*pbVar7;
    pbVar7 = (byte *)(_Str + 2);
  }
  iVar4 = 0;
  while( true ) {
    if ((uVar5 < 0x30) || (0x39 < uVar5)) {
      iVar6 = -1;
    }
    else {
      iVar6 = uVar5 - 0x30;
    }
    if (iVar6 == -1) break;
    iVar4 = iVar6 + iVar4 * 10;
    uVar5 = (uint)*pbVar7;
    pbVar7 = pbVar7 + 1;
  }
  if (uVar3 == 0x2d) {
    iVar4 = -iVar4;
  }
  return iVar4;
}

