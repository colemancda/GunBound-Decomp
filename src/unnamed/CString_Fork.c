/* CString_Fork - 0x00405810 in the original binary.
 * (Historical notes below: FUN_004057c0 is now CString_PrepareWrite2.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): sole caller is the shared (refcount above
 * 1) arm of CString_PrepareWrite2 (0x4057d8). It allocates a new header of
 * the requested capacity through the manager, copies min(length,
 * capacity)+1 characters, keeps the old length, releases one reference on
 * the old header (Free when last) and stores the new data pointer into the
 * CString, which is ATL7 CSimpleStringT::Fork(nLength).
 *
 * FIX (2026-11-03): rebuilt from the disassembly (the raw port read an
 * uninitialised puVar3/iVar4 and lost the EAX argument).  Caller: the one
 * site, 0x4057d8 in FUN_004057c0 (`push esi` = the CString*, EAX = the new
 * capacity; `ret 4`, 0x405887).  The string is unshared (nRefs > 1):
 * Clone the string manager (`call [edx+0x10]`, 0x405827), Allocate
 * (`push 1 / push esi / call [edx]`, 0x40582c-0x405831) a header of the
 * new capacity, throw (0x4058b0) if that fails, copy min(oldLen, capacity)
 * + 1 bytes of text (0x405840-0x40585c), set the new length to the OLD
 * length (`mov [eax+4],ebp`, 0x40585e), drop one reference from the old
 * buffer and Free it through its manager when that was the last
 * (`lock xadd` / `call [edx+4]`, 0x405867-0x405876), and store the new
 * text pointer (new header + 0x10) back into the CString (0x405883).
 * The manager vtable calls use the shims' ABI (no `this`, see
 * crt_shims_msvc.c).  Declared cdecl: string first, EAX as a trailing
 * parameter.
 */
#include "ghidra_types.h"


void CString_Fork(int *param_1,int regEax)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;

  piVar6 = (int *)(*param_1 + -0x10);
  iVar2 = *(int *)(*param_1 + -0xc);
  piVar4 = (int *)(**(code **)(*(int *)*piVar6 + 0x10))();
  piVar5 = (int *)(**(code **)*(int *)piVar4)(regEax,1);
  if (piVar5 == (int *)0x0) {
    FUN_004058b0();
  }
  iVar9 = regEax;
  if (iVar2 < iVar9) {
    iVar9 = iVar2;
  }
  piVar7 = piVar5 + 4;
  piVar1 = piVar6 + 4;
  for (uVar8 = (uint)(iVar9 + 1) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *piVar7 = *piVar1;
    piVar7 = piVar7 + 1;
    piVar1 = piVar1 + 1;
  }
  for (uVar8 = (uint)(iVar9 + 1) & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(char *)piVar7 = *(char *)piVar1;
    piVar7 = (int *)((int)piVar7 + 1);
    piVar1 = (int *)((int)piVar1 + 1);
  }
  piVar5[1] = iVar2;
  piVar1 = piVar6 + 3;
  LOCK();
  iVar3 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar3 + -1 < 1) {
    (**(code **)(*(int *)*piVar6 + 4))(piVar6);
  }
  *param_1 = (int)(piVar5 + 4);
  return;
}
