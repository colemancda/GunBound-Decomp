/* FUN_0052cb5f - 0x0052cb5f in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __openfile
   
   Library: Visual Studio 2003 Release */

FILE * __cdecl __openfile(char *_Filename,char *_Mode,int _ShFlag,FILE *_File)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint _OpenFlag;
  uint uVar6;
  
  cVar1 = *_Mode;
  bVar4 = false;
  bVar3 = false;
  if (cVar1 == 'a') {
    _OpenFlag = 0x109;
  }
  else {
    if (cVar1 == 'r') {
      _OpenFlag = 0;
      uVar6 = DAT_005b1bfc | 1;
      goto LAB_0052cba0;
    }
    if (cVar1 != 'w') {
      return (FILE *)0x0;
    }
    _OpenFlag = 0x301;
  }
  uVar6 = DAT_005b1bfc | 2;
LAB_0052cba0:
  bVar2 = true;
LAB_0052cc7f:
  _Mode = _Mode + 1;
  cVar1 = *_Mode;
  if ((cVar1 == '\0') || (!bVar2)) {
    iVar5 = __sopen(_Filename,_OpenFlag,_ShFlag,0x1a4);
    if (iVar5 < 0) {
      return (FILE *)0x0;
    }
    _DAT_005b1930 = _DAT_005b1930 + 1;
    _File->_flag = uVar6;
    _File->_cnt = 0;
    _File->_ptr = (char *)0x0;
    _File->_base = (char *)0x0;
    _File->_tmpfname = (char *)0x0;
    _File->_file = iVar5;
    return _File;
  }
  if (cVar1 < 'U') {
    if (cVar1 == 'T') {
      if ((_OpenFlag & 0x1000) == 0) {
        _OpenFlag = _OpenFlag | 0x1000;
        goto LAB_0052cc7f;
      }
    }
    else if (cVar1 == '+') {
      if ((_OpenFlag & 2) == 0) {
        _OpenFlag = _OpenFlag & 0xfffffffe | 2;
        uVar6 = uVar6 & 0xfffffffc | 0x80;
        goto LAB_0052cc7f;
      }
    }
    else if (cVar1 == 'D') {
      if ((_OpenFlag & 0x40) == 0) {
        _OpenFlag = _OpenFlag | 0x40;
        goto LAB_0052cc7f;
      }
    }
    else if (cVar1 == 'R') {
      if (!bVar3) {
        bVar3 = true;
        _OpenFlag = _OpenFlag | 0x10;
        goto LAB_0052cc7f;
      }
    }
    else if ((cVar1 == 'S') && (!bVar3)) {
      bVar3 = true;
      _OpenFlag = _OpenFlag | 0x20;
      goto LAB_0052cc7f;
    }
  }
  else {
    if (cVar1 == 'b') {
      if ((_OpenFlag & 0xc000) != 0) goto LAB_0052cc61;
      _OpenFlag = _OpenFlag | 0x8000;
      goto LAB_0052cc7f;
    }
    if (cVar1 == 'c') {
      if (!bVar4) {
        bVar4 = true;
        uVar6 = uVar6 | 0x4000;
        goto LAB_0052cc7f;
      }
    }
    else {
      if (cVar1 != 'n') {
        if ((cVar1 != 't') || ((_OpenFlag & 0xc000) != 0)) goto LAB_0052cc61;
        _OpenFlag = _OpenFlag | 0x4000;
        goto LAB_0052cc7f;
      }
      if (!bVar4) {
        bVar4 = true;
        uVar6 = uVar6 & 0xffffbfff;
        goto LAB_0052cc7f;
      }
    }
  }
LAB_0052cc61:
  bVar2 = false;
  goto LAB_0052cc7f;
}

