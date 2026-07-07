/* FUN_00528d9d - 0x00528d9d in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __mbsnbicmp
   
   Library: Visual Studio 2003 Release */

int __cdecl __mbsnbicmp(uchar *_Str1,uchar *_Str2,size_t _MaxCount)

{
  size_t sVar1;
  byte bVar2;
  byte bVar3;
  _ptiddata p_Var4;
  pthreadmbcinfo ptVar5;
  int iVar6;
  uchar *puVar7;
  uint uVar8;
  byte *pbVar9;
  ushort local_c;
  ushort local_8;
  
  p_Var4 = __getptd();
  ptVar5 = p_Var4->_tpxcptinfoptrs;
  if (ptVar5 != DAT_00f29448) {
    ptVar5 = ___updatetmbcinfo();
  }
  if (_MaxCount == 0) {
    return 0;
  }
  if (ptVar5->ismbcodepage == 0) {
    iVar6 = __strnicmp((char *)_Str1,(char *)_Str2,_MaxCount);
    return iVar6;
  }
  do {
    bVar2 = *_Str1;
    local_c = (ushort)bVar2;
    sVar1 = _MaxCount - 1;
    puVar7 = _Str1 + 1;
    if ((ptVar5->mbctype[bVar2 + 5] & 4) == 0) {
      _Str1 = puVar7;
      if ((ptVar5->mbctype[bVar2 + 5] & 0x10) != 0) {
        local_c = (ushort)(char)ptVar5->mbcasemap[bVar2 + 4];
      }
LAB_00528e74:
      bVar2 = *_Str2;
      pbVar9 = _Str2 + 1;
      if ((ptVar5->mbctype[(ushort)bVar2 + 5] & 4) == 0) {
        uVar8 = (uint)(ushort)bVar2;
        if ((ptVar5->mbctype[uVar8 + 5] & 0x10) != 0) {
          uVar8 = (uint)(ushort)(short)(char)ptVar5->mbcasemap[uVar8 + 4];
        }
        goto LAB_00528ee2;
      }
      if (sVar1 == 0) {
LAB_00528e96:
        _MaxCount = sVar1;
        local_8 = 0;
      }
      else {
        bVar3 = *pbVar9;
        sVar1 = _MaxCount - 2;
        if (bVar3 == 0) goto LAB_00528e96;
        pbVar9 = _Str2 + 2;
        local_8 = CONCAT11(bVar2,bVar3);
        _MaxCount = sVar1;
        if ((local_8 < ptVar5->mbulinfo[2]) || (ptVar5->mbulinfo[3] < local_8)) {
          if ((ptVar5->mbulinfo[5] <= local_8) && (local_8 <= *(ushort *)ptVar5->mbctype)) {
            local_8 = local_8 + *(short *)(ptVar5->mbctype + 2);
          }
        }
        else {
          local_8 = local_8 + ptVar5->mbulinfo[4];
        }
      }
    }
    else {
      if (sVar1 != 0) {
        if (*puVar7 == '\0') {
          local_c = 0;
          _Str1 = puVar7;
        }
        else {
          _Str1 = _Str1 + 2;
          local_c = CONCAT11(bVar2,*puVar7);
          if ((local_c < ptVar5->mbulinfo[2]) || (ptVar5->mbulinfo[3] < local_c)) {
            if ((ptVar5->mbulinfo[5] <= local_c) && (local_c <= *(ushort *)ptVar5->mbctype)) {
              local_c = local_c + *(short *)(ptVar5->mbctype + 2);
            }
          }
          else {
            local_c = local_c + ptVar5->mbulinfo[4];
          }
        }
        goto LAB_00528e74;
      }
      uVar8 = (uint)*_Str2;
      if ((ptVar5->mbctype[uVar8 + 5] & 4) != 0) {
        return 0;
      }
      local_c = 0;
      pbVar9 = _Str2;
      _Str1 = puVar7;
LAB_00528ee2:
      local_8 = (ushort)uVar8;
      _MaxCount = sVar1;
    }
    if (local_8 != local_c) {
      return (-(uint)(local_8 < local_c) & 2) - 1;
    }
    if (local_c == 0) {
      return 0;
    }
    _Str2 = pbVar9;
    if (_MaxCount == 0) {
      return 0;
    }
  } while( true );
}

