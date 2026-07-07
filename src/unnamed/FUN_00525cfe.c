/* FUN_00525cfe - 0x00525cfe in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __mbscmp
   
   Library: Visual Studio 2003 Release */

int __cdecl __mbscmp(uchar *_Str1,uchar *_Str2)

{
  uchar *puVar1;
  byte bVar2;
  byte bVar3;
  ushort uVar4;
  _ptiddata p_Var5;
  pthreadmbcinfo ptVar6;
  int iVar7;
  ushort uVar8;
  byte *pbVar9;
  
  p_Var5 = __getptd();
  ptVar6 = p_Var5->_tpxcptinfoptrs;
  if (ptVar6 != DAT_00f29448) {
    ptVar6 = ___updatetmbcinfo();
  }
  if (ptVar6->ismbcodepage != 0) {
    while( true ) {
      uVar4 = (ushort)*_Str1;
      puVar1 = _Str1 + 1;
      if ((ptVar6->mbctype[uVar4 + 5] & 4) != 0) {
        if (*puVar1 == '\0') {
          uVar4 = 0;
        }
        else {
          uVar4 = CONCAT11(*_Str1,*puVar1);
          puVar1 = _Str1 + 2;
        }
      }
      _Str1 = puVar1;
      bVar2 = *_Str2;
      uVar8 = (ushort)bVar2;
      pbVar9 = _Str2 + 1;
      if ((ptVar6->mbctype[bVar2 + 5] & 4) != 0) {
        bVar3 = *pbVar9;
        if (bVar3 == 0) {
          uVar8 = 0;
        }
        else {
          pbVar9 = _Str2 + 2;
          uVar8 = CONCAT11(bVar2,bVar3);
        }
      }
      if (uVar8 != uVar4) break;
      _Str2 = pbVar9;
      if (uVar4 == 0) {
        return 0;
      }
    }
    return (-(uint)(uVar8 < uVar4) & 2) - 1;
  }
  iVar7 = _strcmp((char *)_Str1,(char *)_Str2);
  return iVar7;
}

