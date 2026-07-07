/* FUN_00525636 - 0x00525636 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __mbsicmp
   
   Library: Visual Studio 2003 Release */

int __cdecl __mbsicmp(uchar *_Str1,uchar *_Str2)

{
  ushort uVar1;
  ushort uVar2;
  _ptiddata p_Var3;
  pthreadmbcinfo ptVar4;
  int iVar5;
  uchar *puVar6;
  BOOL unaff_EDI;
  undefined4 local_8;
  
  p_Var3 = __getptd();
  ptVar4 = p_Var3->_tpxcptinfoptrs;
  if (ptVar4 != DAT_00f29448) {
    ptVar4 = ___updatetmbcinfo();
  }
  if (ptVar4->ismbcodepage == 0) {
    iVar5 = __stricmp((char *)_Str1,(char *)_Str2);
  }
  else {
    do {
      uVar1 = (ushort)*_Str1;
      puVar6 = _Str1 + 1;
      if ((ptVar4->mbctype[uVar1 + 5] & 4) == 0) {
        _Str1 = puVar6;
        if ((ptVar4->mbctype[uVar1 + 5] & 0x10) != 0) {
          uVar1 = (ushort)(char)ptVar4->mbcasemap[uVar1 + 4];
        }
      }
      else if (*puVar6 == '\0') {
        uVar1 = 0;
        _Str1 = puVar6;
      }
      else {
        iVar5 = ___crtLCMapStringA(*(_locale_t *)ptVar4->mbulinfo,(LPCWSTR)&DAT_00000200,
                                   (DWORD)_Str1,(LPCSTR)0x2,(int)&local_8,(LPSTR)0x2,
                                   ptVar4->mbcodepage,1,unaff_EDI);
        if (iVar5 == 1) {
          uVar1 = (ushort)local_8 & 0xff;
        }
        else {
          if (iVar5 != 2) {
            return 0x7fffffff;
          }
          uVar1 = (ushort)local_8 * 0x100 + ((ushort)((uint)local_8 >> 8) & 0xff);
        }
        _Str1 = _Str1 + 2;
      }
      uVar2 = (ushort)*_Str2;
      puVar6 = _Str2 + 1;
      if ((ptVar4->mbctype[uVar2 + 5] & 4) == 0) {
        _Str2 = puVar6;
        if ((ptVar4->mbctype[uVar2 + 5] & 0x10) != 0) {
          uVar2 = (ushort)(char)ptVar4->mbcasemap[uVar2 + 4];
        }
      }
      else if (*puVar6 == '\0') {
        uVar2 = 0;
        _Str2 = puVar6;
      }
      else {
        iVar5 = ___crtLCMapStringA(*(_locale_t *)ptVar4->mbulinfo,(LPCWSTR)&DAT_00000200,
                                   (DWORD)_Str2,(LPCSTR)0x2,(int)&local_8,(LPSTR)0x2,
                                   ptVar4->mbcodepage,1,unaff_EDI);
        if (iVar5 == 1) {
          uVar2 = (ushort)local_8 & 0xff;
        }
        else {
          if (iVar5 != 2) {
            return 0x7fffffff;
          }
          uVar2 = (ushort)local_8 * 0x100 + ((ushort)((uint)local_8 >> 8) & 0xff);
        }
        _Str2 = _Str2 + 2;
      }
      if (uVar2 != uVar1) {
        return (-(uint)(uVar2 < uVar1) & 2) - 1;
      }
    } while (uVar1 != 0);
    iVar5 = 0;
  }
  return iVar5;
}

