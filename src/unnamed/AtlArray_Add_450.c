/* AtlArray_Add_450 - 0x0042ae30 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlArray<E>::Add(const E& element) for the
 * 0x450-byte avatar-item record held by the arrays at g_clientContext +
 * 0x44e20 / 0x44e30 / 0x44e40.  The body is atlcoll.h's Add statement
 * for statement - iElement = m_nSize; if (iElement >= m_nMaxSize) and
 * !GrowBuffer(iElement + 1) (AtlArray_GrowBuffer_450, 0x42ae56) then
 * AtlThrow(E_OUTOFMEMORY) (ThrowCxxException(0x8007000e)); placement-new
 * copy-construct m_pData[iElement] from the element
 * (AtlArray_CopyConstructElement_450, 0x42ae85, behind the placement-new
 * null test); m_nSize++; return iElement (`mov eax,edi`).
 *
 * What fixes it from outside: the callee is the 0x450 instantiation's
 * own GrowBuffer, the element stride is `imul eax,eax,0x450`, and all
 * eight binary call sites load ECX with one of those arrays and push the
 * address of a stack record that AtlArray_ConstructElement_450 built and
 * AtlArray_DestroyElement_450 destroys afterwards.
 *
 * ARRAY RECOVERED (2026-10-29).  The convention is __thiscall (array in
 * ECX, element pushed, `ret 4`), which ghidra_types.h erases to cdecl,
 * so the port takes the array as its first argument - and every C site
 * passed only the element, landing it in the array slot.  Each site's
 * array, read off the disassembly (`mov ecx,[0x5b3484]` = g_clientContext
 * then `add ecx,0x44eN0`, or `lea ecx,[eax+0x44e20]` with EAX reloaded
 * from 0x5b3484 at 0x4445bd):
 *
 *   0x428449 +0x44e20, 0x428462 +0x44e30   State03 (back-to-back pair)
 *   0x44426d +0x44e20, 0x444286 +0x44e30   State07 (back-to-back pair)
 *   0x4450bf +0x44e20, 0x4450d8 +0x44e30   State07 (back-to-back pair)
 *   0x4445e9 +0x44e20   State07, after the duplicate scan over the
 *                       +0x44e20 records' +8 id
 *   0x44464e +0x44e40   State07, after the 0x9c-byte rep movsd into
 *                       the +0x44be8 array
 *
 * Both back-to-back State07 pairs take +0x44e20 then +0x44e30, so they
 * need no ordering assumption; the two singles carry their own witness.
 *
 * Still open: the GrowBuffer call passes only the size, while the
 * original also hands it the array in ESI (`mov esi,ecx` at 0x42ae46);
 * see AtlArray_GrowBuffer_450's header.  The unaff_FS_OFFSET lines are
 * Ghidra's SEH-frame artifact and are left as they are.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


uint __thiscall AtlArray_Add_450(int *param_1,undefined4 param_2)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a95;
  *unaff_FS_OFFSET = &local_c;
  uVar1 = param_1[1];
  if ((uint)param_1[2] <= uVar1) {
    cVar2 = AtlArray_GrowBuffer_450(uVar1 + 1);
    if (cVar2 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  iVar3 = uVar1 * 0x450 + *param_1;
  local_4 = 0;
  if (iVar3 != 0) {
    AtlArray_CopyConstructElement_450(iVar3,param_2);
  }
  param_1[1] = param_1[1] + 1;
  *unaff_FS_OFFSET = local_c;
  return uVar1;
}

