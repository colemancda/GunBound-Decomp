/* FUN_00535be5 - 0x00535be5 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___crtsetenv
   
   Library: Visual Studio 2003 Release */

int __cdecl ___crtsetenv(char **_POption,int _Primary)

{
  uchar *_Str;
  uchar *puVar1;
  int iVar2;
  int *piVar3;
  size_t sVar4;
  LPCSTR lpName;
  BOOL BVar5;
  bool bVar6;
  int local_14;
  
  local_14 = 0;
  if (_POption == (char **)0x0) {
    return -1;
  }
  _Str = (uchar *)*_POption;
  if (_Str == (uchar *)0x0) {
    return -1;
  }
  puVar1 = __mbschr(_Str,0x3d);
  if (puVar1 == (uchar *)0x0) {
    return -1;
  }
  if (_Str == puVar1) {
    return -1;
  }
  bVar6 = puVar1[1] == '\0';
  if (DAT_005b18e8 == DAT_005b18ec) {
    DAT_005b18e8 = (int *)copy_environ();
  }
  if (DAT_005b18e8 == (int *)0x0) {
    if ((_Primary != 0) && (DAT_005b18f0 != (undefined4 *)0x0)) {
      iVar2 = ___wtomb_environ();
      if (iVar2 != 0) {
        return -1;
      }
      goto LAB_00535c9a;
    }
    if (!bVar6) {
      DAT_005b18e8 = _malloc(4);
      if (DAT_005b18e8 == (int *)0x0) {
        return -1;
      }
      *DAT_005b18e8 = 0;
      if (DAT_005b18f0 == (undefined4 *)0x0) {
        DAT_005b18f0 = _malloc(4);
        if (DAT_005b18f0 == (undefined4 *)0x0) {
          return -1;
        }
        *DAT_005b18f0 = 0;
      }
      goto LAB_00535c9a;
    }
LAB_00535c68:
    local_14 = 0;
  }
  else {
LAB_00535c9a:
    piVar3 = DAT_005b18e8;
    iVar2 = findenv(_Str);
    if ((iVar2 < 0) || (*piVar3 == 0)) {
      if (bVar6) {
        _free(_Str);
        *_POption = (char *)0x0;
        goto LAB_00535c68;
      }
      if (iVar2 < 0) {
        iVar2 = -iVar2;
      }
      piVar3 = _realloc(DAT_005b18e8,iVar2 * 4 + 8);
      if (piVar3 == (int *)0x0) {
        return -1;
      }
      piVar3[iVar2] = (int)_Str;
      (piVar3 + iVar2)[1] = 0;
      *_POption = (char *)0x0;
LAB_00535d37:
      DAT_005b18e8 = piVar3;
    }
    else {
      piVar3 = piVar3 + iVar2;
      _free((void *)*piVar3);
      if (bVar6) {
        for (; *piVar3 != 0; piVar3 = piVar3 + 1) {
          *piVar3 = piVar3[1];
          iVar2 = iVar2 + 1;
        }
        piVar3 = _realloc(DAT_005b18e8,iVar2 << 2);
        if (piVar3 != (int *)0x0) goto LAB_00535d37;
      }
      else {
        *piVar3 = (int)_Str;
        *_POption = (char *)0x0;
      }
    }
    if (_Primary != 0) {
      sVar4 = _strlen((char *)_Str);
      lpName = _malloc(sVar4 + 2);
      if (lpName != (LPCSTR)0x0) {
        FUN_0052baa0(lpName,_Str);
        puVar1[(int)lpName - (int)_Str] = '\0';
        BVar5 = SetEnvironmentVariableA
                          (lpName,(LPCSTR)(~-(uint)bVar6 &
                                          (uint)(puVar1 + ((int)lpName - (int)_Str) + 1)));
        if (BVar5 == 0) {
          local_14 = -1;
        }
        _free(lpName);
      }
    }
    if (bVar6) {
      _free(_Str);
    }
  }
  return local_14;
}

