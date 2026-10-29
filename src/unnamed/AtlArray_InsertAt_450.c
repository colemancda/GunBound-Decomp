/* AtlArray_InsertAt_450 - 0x0050cff0 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlArray<E>::InsertAt(iElement, element,
 * nElements) for the 0x450-byte avatar-item record, as
 * AtlArray_CopyElement_450's header already maps it.  The body is
 * atlcoll.h's VC7.1 InsertAt: if iElement >= m_nSize, SetCount(iElement
 * + nElements, -1) (AtlArray_SetCount_450, 0x50d02c); otherwise
 * SetCount(m_nSize + nElements, -1) (0x50d044), destroy the nElements
 * slots past the old size (AtlArray_DestroyElement_450, 0x50d066),
 * _memmove the upper elements up (0x50d0af) and re-construct the hole
 * (AtlArray_CallConstructors_450, 0x50d0c4); then both arms assign
 * `m_pData[i] = element` over the inserted range
 * (AtlArray_CopyElement_450, 0x50d0f0).  Every callee is already named
 * as a member of this one instantiation.  Four stack arguments (`ret
 * 0x10`): the array, then iElement, element, nElements.
 *
 * The one caller, FUN_0050a320 (the Avatar-Store reorder, 0x50a44b),
 * pushes (g_clientContext + 0x44e20, an index, the scratch record it
 * just copied out with AtlArray_CopyElement_450, 1) right after calling
 * 0x44c6a0 - the RemoveAt that AtlArray_RemoveAll_450's header
 * identifies - on the same array (0x50a42e): a move expressed as
 * RemoveAt + InsertAt.  That file is C++ and carries its own extern
 * declaration, renamed with this one.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void AtlArray_InsertAt_450(int *param_1,uint param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  int local_1c;
  int local_18;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053be70) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (param_2 < (uint)param_1[1]) {
    iVar1 = param_1[1];
    /* 0x50d036-0x50d044: `mov esi,[edi+4]` = iVar1, `mov ecx,[ebp+0x14];
       add ecx,esi` = param_4 + iVar1, edx = edi = param_1, eax = -1.  This
       is the `jb` target, i.e. the param_2 < param_1[1] arm. */
    AtlArray_SetCount_450(param_4 + iVar1,param_1,-1);
    local_18 = iVar1 * 0x450 + *param_1;
    if (param_4 != 0) {
      local_1c = param_4;
      do {
        AtlArray_DestroyElement_450(local_18);
        local_18 = local_18 + 0x450;
        local_1c = local_1c + -1;
      } while (local_1c != 0);
    }
    _memmove((void *)((param_4 + param_2) * 0x450 + *param_1),(void *)(param_2 * 0x450 + *param_1),
             (iVar1 - param_2) * 0x450);
    local_8 = 0;
    AtlArray_CallConstructors_450(*param_1 + param_2 * 0x450,param_4);
  }
  else {
    /* 0x50d01e-0x50d02c (the fall-through arm): `mov eax,[ebp+0x14];
       lea esi,[ebx+eax]` = param_2 + param_4, edx = edi = param_1,
       eax = -1. */
    AtlArray_SetCount_450(param_2 + param_4,param_1,-1);
  }
  uVar2 = param_2 + param_4;
  local_8 = 0xffffffff;
  /* DROPPED BASES RECOVERED (2026-08-27): 0x50d0e0-0x50d0f0 is
     `mov esi,[ebp+0x14]; imul esi,esi,0x450; add esi,[edi]` with edi =
     param_1, then `mov ebx,[ebp+0x10]` = param_3.  [ebp+0x14] is the dead
     param_4 slot reused as this loop's counter (`mov [ebp+0x14],ebx` at
     0x50d0db seeds it from param_2), which is the counter the C already
     spells param_2. */
  for (; param_2 < uVar2; param_2 = param_2 + 1) {
    AtlArray_CopyElement_450(param_2 * 0x450 + *param_1,(int)param_3);
  }
  return;
}

