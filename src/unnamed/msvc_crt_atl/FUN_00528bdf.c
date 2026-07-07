/* FUN_00528bdf - 0x00528bdf in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __mbsrchr
   
   Library: Visual Studio 2003 Release */

uchar * __cdecl __mbsrchr(uchar *_Str,uint _Ch)

{
  byte bVar1;
  ushort uVar2;
  _ptiddata p_Var3;
  pthreadmbcinfo ptVar4;
  uchar *puVar5;
  byte *pbVar6;
  byte bVar7;
  byte *pbVar8;
  bool bVar9;
  
  pbVar8 = (byte *)0x0;
  p_Var3 = __getptd();
  ptVar4 = p_Var3->_tpxcptinfoptrs;
  if (ptVar4 != DAT_00f29448) {
    ptVar4 = ___updatetmbcinfo();
  }
  if (ptVar4->ismbcodepage == 0) {
    puVar5 = (uchar *)_strrchr((char *)_Str,_Ch);
    return puVar5;
  }
  do {
    bVar7 = *_Str;
    if ((ptVar4->mbctype[bVar7 + 5] & 4) == 0) {
      bVar9 = _Ch == bVar7;
LAB_00528c3a:
      pbVar6 = _Str;
      if (bVar9) {
        pbVar8 = _Str;
      }
    }
    else {
      pbVar6 = _Str + 1;
      bVar1 = *pbVar6;
      if (bVar1 == 0) {
        bVar9 = pbVar8 == (byte *)0x0;
        _Str = pbVar6;
        bVar7 = bVar1;
        goto LAB_00528c3a;
      }
      uVar2 = CONCAT11(bVar7,bVar1);
      bVar7 = bVar1;
      if (_Ch == uVar2) {
        pbVar8 = _Str;
      }
    }
    _Str = pbVar6 + 1;
    if (bVar7 == 0) {
      return pbVar8;
    }
  } while( true );
}

