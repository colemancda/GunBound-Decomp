/* FUN_005357b3 - 0x005357b3 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: This function may have set the stack pointer */
/* WARNING: Type propagation algorithm not settling */
/* Library Function - Single Match
    ___crtCompareStringA
   
   Library: Visual Studio 2003 Release */

int __cdecl
___crtCompareStringA
          (_locale_t _Plocinfo,LPCWSTR _LocaleName,DWORD _DwCmpFlags,LPCSTR _LpString1,
          int _CchCount1,LPCSTR _LpString2,int _CchCount2,int _Code_page)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  DWORD DVar4;
  BOOL BVar5;
  BYTE *pBVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  int iVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  int iVar12;
  undefined1 *puVar13;
  undefined1 *puVar14;
  undefined1 *puVar15;
  size_t unaff_EDI;
  void *_Memory;
  undefined4 uStackY_7c;
  int local_44;
  void *local_3c;
  _cpinfo local_34;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_0054b3f0;
  uStack_c = 0x5357bf;
  local_20 = DAT_0056bfd4;
  _Memory = (void *)0x0;
  if (DAT_005b1c3c == 0) {
    uStackY_7c = 0x5357e5;
    iVar3 = CompareStringW(0,0,(PCNZWCH)&DAT_00544fc4,1,(PCNZWCH)&DAT_00544fc4,1);
    if (iVar3 == 0) {
      DVar4 = GetLastError();
      if (DVar4 == 0x78) {
        DAT_005b1c3c = 2;
      }
    }
    else {
      DAT_005b1c3c = 1;
    }
  }
  if (0 < (int)_LpString1) {
    _LpString1 = (LPCSTR)_strncnt(_LpString1,unaff_EDI);
  }
  if (0 < (int)_LpString2) {
    _LpString2 = (LPCSTR)_strncnt(_LpString2,unaff_EDI);
  }
  if ((DAT_005b1c3c == 2) || (DAT_005b1c3c == 0)) {
    local_3c = (void *)0x0;
    if (_Plocinfo == (_locale_t)0x0) {
      _Plocinfo = DAT_005b1b8c;
    }
    if (_CchCount2 == 0) {
      _CchCount2 = DAT_005b1b9c;
    }
    iVar3 = ___ansicp();
    if (iVar3 != -1) {
      if (iVar3 == _CchCount2) {
LAB_00535af6:
        uStackY_7c = 0x535b0e;
        iVar3 = CompareStringA((LCID)_Plocinfo,(DWORD)_LocaleName,(PCNZCH)_DwCmpFlags,
                               (int)_LpString1,(PCNZCH)_CchCount1,(int)_LpString2);
        if (_Memory != (void *)0x0) {
          _free(_Memory);
          _free(local_3c);
          return iVar3;
        }
        return iVar3;
      }
      uStackY_7c = 0x535abf;
      _Memory = (void *)___convertcp();
      if (_Memory != (void *)0x0) {
        uStackY_7c = 0x535ada;
        _CchCount1 = ___convertcp();
        _DwCmpFlags = (DWORD)_Memory;
        local_3c = (void *)_CchCount1;
        if ((void *)_CchCount1 != (void *)0x0) goto LAB_00535af6;
        _free(_Memory);
      }
    }
  }
  else if (DAT_005b1c3c == 1) {
    bVar2 = false;
    bVar1 = false;
    local_44 = 0;
    if (_CchCount2 == 0) {
      _CchCount2 = DAT_005b1b9c;
    }
    if ((_LpString1 == (LPCSTR)0x0) || (_LpString2 == (LPCSTR)0x0)) {
      if (_LpString1 == _LpString2) {
        return 2;
      }
      if (1 < (int)_LpString2) {
        return 1;
      }
      if (1 < (int)_LpString1) {
        return 3;
      }
      BVar5 = GetCPInfo(_CchCount2,&local_34);
      if (BVar5 == 0) {
        return 0;
      }
      if (0 < (int)_LpString1) {
        if (local_34.MaxCharSize < 2) {
          return 3;
        }
        pBVar6 = local_34.LeadByte;
        while( true ) {
          if (local_34.LeadByte[0] == 0) {
            return 3;
          }
          if (pBVar6[1] == 0) break;
          if ((*pBVar6 <= *(byte *)_DwCmpFlags) && (*(byte *)_DwCmpFlags <= pBVar6[1])) {
            return 2;
          }
          pBVar6 = pBVar6 + 2;
          local_34.LeadByte[0] = *pBVar6;
        }
        return 3;
      }
      if (0 < (int)_LpString2) {
        if (local_34.MaxCharSize < 2) {
          return 1;
        }
        pBVar6 = local_34.LeadByte;
        if (local_34.LeadByte[0] != 0) {
          while( true ) {
            if (pBVar6[1] == 0) {
              return 1;
            }
            if ((*pBVar6 <= *(byte *)_CchCount1) && (*(byte *)_CchCount1 <= pBVar6[1])) break;
            pBVar6 = pBVar6 + 2;
            if (*pBVar6 == 0) {
              return 1;
            }
          }
          return 2;
        }
        return 1;
      }
    }
    uStackY_7c = 0x53592f;
    iVar3 = MultiByteToWideChar(_CchCount2,9,(LPCSTR)_DwCmpFlags,(int)_LpString1,(LPWSTR)0x0,0);
    if (iVar3 != 0) {
      puVar7 = (undefined1 *)(iVar3 * 2 + 3U & 0xfffffffc);
      iVar9 = -(int)puVar7;
      puVar8 = &stack0xffffffa0 + iVar9;
      local_1c = &stack0xffffffa0 + iVar9;
      local_8 = (undefined *)0xffffffff;
      if (&stack0xffffffa0 == puVar7) {
        *(int *)(&stack0xffffff9c + iVar9) = iVar3 * 2;
        *(undefined4 *)(&stack0xffffff98 + iVar9) = 0x535987;
        puVar8 = _malloc(*(size_t *)(&stack0xffffff9c + iVar9));
        if (puVar8 == (undefined1 *)0x0) {
          return 0;
        }
        bVar2 = true;
      }
      *(int *)(&stack0xffffff9c + iVar9) = iVar3;
      *(undefined1 **)(&stack0xffffff98 + iVar9) = puVar8;
      *(LPCSTR *)(&stack0xffffff94 + iVar9) = _LpString1;
      *(DWORD *)(&stack0xffffff90 + iVar9) = _DwCmpFlags;
      *(undefined4 *)(&stack0xffffff8c + iVar9) = 1;
      *(int *)(&stack0xffffff88 + iVar9) = _CchCount2;
      puVar13 = (undefined1 *)((int)&uStackY_7c + iVar9);
      *(undefined4 *)((int)&uStackY_7c + iVar9) = 0x5359a8;
      iVar9 = MultiByteToWideChar(*(UINT *)(&stack0xffffff88 + iVar9),
                                  *(DWORD *)(&stack0xffffff8c + iVar9),
                                  *(LPCSTR *)(&stack0xffffff90 + iVar9),
                                  *(int *)(&stack0xffffff94 + iVar9),
                                  *(LPWSTR *)(&stack0xffffff98 + iVar9),
                                  *(int *)(&stack0xffffff9c + iVar9));
      puVar7 = puVar13;
      if (iVar9 != 0) {
        *(undefined4 *)(puVar13 + -4) = 0;
        *(undefined4 *)(puVar13 + -8) = 0;
        *(LPCSTR *)(puVar13 + -0xc) = _LpString2;
        *(int *)(puVar13 + -0x10) = _CchCount1;
        *(undefined4 *)(puVar13 + -0x14) = 9;
        *(int *)(puVar13 + -0x18) = _CchCount2;
        puVar14 = puVar13 + -0x1c;
        *(undefined4 *)(puVar13 + -0x1c) = 0x5359c5;
        iVar9 = MultiByteToWideChar(*(UINT *)(puVar13 + -0x18),*(DWORD *)(puVar13 + -0x14),
                                    *(LPCSTR *)(puVar13 + -0x10),*(int *)(puVar13 + -0xc),
                                    *(LPWSTR *)(puVar13 + -8),*(int *)(puVar13 + -4));
        puVar7 = puVar14;
        if (iVar9 != 0) {
          puVar10 = (undefined1 *)(iVar9 * 2 + 3U & 0xfffffffc);
          *(undefined4 *)(puVar14 + -4) = 0x5359e7;
          iVar12 = -(int)puVar10;
          puVar11 = puVar14 + iVar12;
          puVar7 = puVar14 + iVar12;
          local_1c = puVar14 + iVar12;
          local_8 = (undefined *)0xffffffff;
          if (puVar14 == puVar10) {
            sRamfffffffc = iVar9 * 2;
            uRamfffffff8 = 0x535a1a;
            puVar11 = _malloc(sRamfffffffc);
            if (puVar11 == (undefined1 *)0x0) goto LAB_00535a61;
            bVar1 = true;
          }
          *(int *)(puVar14 + iVar12 + -4) = iVar9;
          *(undefined1 **)(puVar14 + iVar12 + -8) = puVar11;
          *(LPCSTR *)(puVar14 + iVar12 + -0xc) = _LpString2;
          *(int *)(puVar14 + iVar12 + -0x10) = _CchCount1;
          *(undefined4 *)(puVar14 + iVar12 + -0x14) = 1;
          *(int *)(puVar14 + iVar12 + -0x18) = _CchCount2;
          puVar15 = puVar14 + iVar12 + -0x1c;
          *(undefined4 *)(puVar14 + iVar12 + -0x1c) = 0x535a3b;
          iVar12 = MultiByteToWideChar(*(UINT *)(puVar14 + iVar12 + -0x18),
                                       *(DWORD *)(puVar14 + iVar12 + -0x14),
                                       *(LPCSTR *)(puVar14 + iVar12 + -0x10),
                                       *(int *)(puVar14 + iVar12 + -0xc),
                                       *(LPWSTR *)(puVar14 + iVar12 + -8),
                                       *(int *)(puVar14 + iVar12 + -4));
          puVar7 = puVar15;
          if (iVar12 != 0) {
            *(int *)(puVar15 + -4) = iVar9;
            *(undefined1 **)(puVar15 + -8) = puVar11;
            *(int *)(puVar15 + -0xc) = iVar3;
            *(undefined1 **)(puVar15 + -0x10) = puVar8;
            *(LPCWSTR *)(puVar15 + -0x14) = _LocaleName;
            *(_locale_t *)(puVar15 + -0x18) = _Plocinfo;
            puVar7 = puVar15 + -0x1c;
            *(undefined4 *)(puVar15 + -0x1c) = 0x535a51;
            local_44 = CompareStringW(*(LCID *)(puVar15 + -0x18),*(DWORD *)(puVar15 + -0x14),
                                      *(PCNZWCH *)(puVar15 + -0x10),*(int *)(puVar15 + -0xc),
                                      *(PCNZWCH *)(puVar15 + -8),*(int *)(puVar15 + -4));
          }
          if (bVar1) {
            *(undefined1 **)(puVar7 + -4) = puVar11;
            *(undefined4 *)(puVar7 + -8) = 0x535a60;
            _free(*(void **)(puVar7 + -4));
          }
        }
      }
LAB_00535a61:
      if (bVar2) {
        *(undefined1 **)(puVar7 + -4) = puVar8;
        *(undefined4 *)(puVar7 + -8) = 0x535a6f;
        _free(*(void **)(puVar7 + -4));
        return local_44;
      }
      return local_44;
    }
  }
  return 0;
}

