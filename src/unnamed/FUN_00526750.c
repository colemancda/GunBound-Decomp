/* FUN_00526750 - 0x00526750 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    _qsort
   
   Library: Visual Studio 2003 Release */

void __cdecl
_qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,_PtFuncCompare *_PtFuncCompare)

{
  undefined1 uVar1;
  uint uVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  size_t sVar7;
  undefined1 *puVar8;
  undefined1 *local_100;
  undefined1 *local_fc;
  int local_f8;
  size_t sStack_f4;
  undefined4 auStack_f0 [30];
  undefined4 auStack_78 [30];
  
  if ((_NumOfElements < 2) || (_SizeOfElements == 0)) {
    return;
  }
  local_f8 = 0;
  local_100 = _Base;
  local_fc = (undefined1 *)((_NumOfElements - 1) * _SizeOfElements + (int)_Base);
LAB_00526795:
  while (uVar2 = (uint)((int)local_fc - (int)local_100) / _SizeOfElements + 1, 8 < uVar2) {
    puVar3 = local_100 + (uVar2 >> 1) * _SizeOfElements;
    iVar4 = (*_PtFuncCompare)(local_100,puVar3);
    if ((0 < iVar4) && (local_100 != puVar3)) {
      puVar5 = puVar3;
      sVar7 = _SizeOfElements;
      do {
        uVar1 = puVar5[(int)local_100 - (int)puVar3];
        puVar5[(int)local_100 - (int)puVar3] = *puVar5;
        *puVar5 = uVar1;
        puVar5 = puVar5 + 1;
        sVar7 = sVar7 - 1;
      } while (sVar7 != 0);
    }
    iVar4 = (*_PtFuncCompare)(local_100,local_fc);
    if ((0 < iVar4) && (local_100 != local_fc)) {
      puVar5 = local_fc;
      sVar7 = _SizeOfElements;
      do {
        uVar1 = puVar5[(int)local_100 - (int)local_fc];
        puVar5[(int)local_100 - (int)local_fc] = *puVar5;
        *puVar5 = uVar1;
        puVar5 = puVar5 + 1;
        sVar7 = sVar7 - 1;
      } while (sVar7 != 0);
    }
    iVar4 = (*_PtFuncCompare)(puVar3,local_fc);
    puVar5 = local_100;
    puVar8 = local_fc;
    if ((0 < iVar4) && (puVar3 != local_fc)) {
      puVar6 = local_fc;
      sVar7 = _SizeOfElements;
      do {
        uVar1 = puVar6[(int)puVar3 - (int)local_fc];
        puVar6[(int)puVar3 - (int)local_fc] = *puVar6;
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
        sVar7 = sVar7 - 1;
      } while (sVar7 != 0);
    }
LAB_00526880:
    if (puVar5 < puVar3) {
      do {
        puVar5 = puVar5 + _SizeOfElements;
        if (puVar3 <= puVar5) goto LAB_005268a0;
        iVar4 = (*_PtFuncCompare)(puVar5,puVar3);
      } while (iVar4 < 1);
      if (puVar3 <= puVar5) goto LAB_005268a0;
    }
    else {
LAB_005268a0:
      do {
        puVar5 = puVar5 + _SizeOfElements;
        if (local_fc < puVar5) break;
        iVar4 = (*_PtFuncCompare)(puVar5,puVar3);
      } while (iVar4 < 1);
    }
    do {
      puVar8 = puVar8 + -_SizeOfElements;
      if (puVar8 <= puVar3) break;
      iVar4 = (*_PtFuncCompare)(puVar8,puVar3);
    } while (0 < iVar4);
    if (puVar5 <= puVar8) {
      if (puVar5 != puVar8) {
        sStack_f4 = _SizeOfElements;
        puVar6 = puVar8;
        do {
          uVar1 = puVar6[(int)puVar5 - (int)puVar8];
          puVar6[(int)puVar5 - (int)puVar8] = *puVar6;
          *puVar6 = uVar1;
          puVar6 = puVar6 + 1;
          sStack_f4 = sStack_f4 - 1;
        } while (sStack_f4 != 0);
      }
      if (puVar3 == puVar8) {
        puVar3 = puVar5;
      }
      goto LAB_00526880;
    }
    puVar8 = puVar8 + _SizeOfElements;
    if (puVar3 < puVar8) {
      do {
        puVar8 = puVar8 + -_SizeOfElements;
        if (puVar8 <= puVar3) goto LAB_00526940;
        iVar4 = (*_PtFuncCompare)(puVar8,puVar3);
      } while (iVar4 == 0);
      if (puVar8 <= puVar3) goto LAB_00526940;
    }
    else {
LAB_00526940:
      do {
        puVar8 = puVar8 + -_SizeOfElements;
        if (puVar8 <= local_100) break;
        iVar4 = (*_PtFuncCompare)(puVar8,puVar3);
      } while (iVar4 == 0);
    }
    if ((int)puVar8 - (int)local_100 < (int)local_fc - (int)puVar5) goto LAB_0052699b;
    if (local_100 < puVar8) {
      auStack_f0[local_f8] = local_100;
      auStack_78[local_f8] = puVar8;
      local_f8 = local_f8 + 1;
    }
    local_100 = puVar5;
    if (local_fc <= puVar5) goto LAB_005267b7;
  }
  shortsort(local_100,_SizeOfElements,_PtFuncCompare);
  goto LAB_005267b7;
LAB_0052699b:
  if (puVar5 < local_fc) {
    auStack_f0[local_f8] = puVar5;
    auStack_78[local_f8] = local_fc;
    local_f8 = local_f8 + 1;
  }
  local_fc = puVar8;
  if (puVar8 <= local_100) {
LAB_005267b7:
    local_f8 = local_f8 + -1;
    if (local_f8 < 0) {
      return;
    }
    local_100 = (undefined1 *)auStack_f0[local_f8];
    local_fc = (undefined1 *)auStack_78[local_f8];
  }
  goto LAB_00526795;
}

