/* FUN_0053609d - 0x0053609d in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __mbschr
   
   Library: Visual Studio 2003 Release */

uchar * __cdecl __mbschr(uchar *_Str,uint _Ch)

{
  byte bVar1;
  byte bVar2;
  _ptiddata p_Var3;
  pthreadmbcinfo ptVar4;
  uchar *puVar5;
  byte *pbVar6;
  uint uVar7;
  
  p_Var3 = __getptd();
  ptVar4 = p_Var3->_tpxcptinfoptrs;
  if (ptVar4 != DAT_00f29448) {
    ptVar4 = ___updatetmbcinfo();
  }
  if (ptVar4->ismbcodepage == 0) {
    puVar5 = (uchar *)FUN_0052c940();
    return puVar5;
  }
  while( true ) {
    bVar2 = *_Str;
    uVar7 = (uint)bVar2;
    if (bVar2 == 0) break;
    if ((ptVar4->mbctype[uVar7 + 5] & 4) == 0) {
      pbVar6 = _Str;
      if (_Ch == uVar7) break;
    }
    else {
      bVar1 = _Str[1];
      if (bVar1 == 0) {
        return (uchar *)0x0;
      }
      pbVar6 = _Str + 1;
      if (_Ch == CONCAT11(bVar2,bVar1)) {
        return _Str;
      }
    }
    _Str = pbVar6 + 1;
  }
  return (uchar *)(~-(uint)(_Ch != uVar7) & (uint)_Str);
}

