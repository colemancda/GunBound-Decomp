/* FUN_0043de10 - 0x0043de10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * The ATL CStringData clone: given a string header (pStringMgr +0,
 * nDataLength +4, nAllocLength +8, nRefs +0xc, characters at +0x10), it
 * either shares the header (AddRef) when the header's manager's Clone()
 * (vtable +0x10) returns the same manager and the header is not locked
 * (nRefs >= 0), or allocates a new header through that manager's
 * Allocate (vtable +0) and copies nDataLength+1 characters. It returns
 * the header the caller should use. All 11 callers add 0x10 to it to
 * get the new CString handle.
 *
 * FIXED (2026-10-30): the header arrives in EAX (`mov esi,eax` at
 * 0x43de11, no earlier write), now the parameter regEax. Every one of
 * the 11 call sites loads it as `<handle> - 0x10` just before the call.
 * The port also returned 0 on both success paths. The shared path
 * returns the same header (`mov eax,esi` at 0x43de28 before the ret),
 * and the copy path returns the newly allocated one (EAX, still the
 * Allocate result, at 0x43de6b). Both are restored, because every
 * caller stores return + 0x10 as the cloned handle. The
 * allocation-failure path tail-jumps to 0x4058b0 (`jmp` at 0x43de45),
 * which does not return.
 *
 * Not changed: the two manager vtable calls keep Ghidra's argument
 * lists (no `this`), matching the self-sufficient CAtlStringMgr
 * reconstruction in crt_shims_msvc.c, whose slots take no `this`.
 */
#include "ghidra_types.h"


undefined4 FUN_0043de10(int *regEax)

{
  int iVar1;
  int *in_EAX = regEax;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int *piVar6;
  
  puVar2 = (undefined4 *)(**(code **)(*(int *)*in_EAX + 0x10))();
  if ((-1 < in_EAX[3]) && (puVar2 == (undefined4 *)*in_EAX)) {
    LOCK();
    in_EAX[3] = in_EAX[3] + 1;
    UNLOCK();
    /* 0x43de28: mov eax,esi - the shared header itself. */
    return (undefined4)in_EAX;
  }
  iVar3 = (**(code **)*puVar2)(in_EAX[1],1);
  if (iVar3 == 0) {
    /* 0x43de45: jmp 0x4058b0, which does not return. */
    FUN_004058b0();
    return 0;
  }
  *(int *)(iVar3 + 4) = in_EAX[1];
  iVar1 = in_EAX[1];
  piVar5 = in_EAX + 4;
  piVar6 = (int *)(iVar3 + 0x10);
  for (uVar4 = iVar1 + 1U >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *piVar6 = *piVar5;
    piVar5 = piVar5 + 1;
    piVar6 = piVar6 + 1;
  }
  for (uVar4 = iVar1 + 1U & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)piVar6 = (char)*piVar5;
    piVar5 = (int *)((int)piVar5 + 1);
    piVar6 = (int *)((int)piVar6 + 1);
  }
  /* 0x43de6b: EAX is still the Allocate result - the new header. */
  return (undefined4)iVar3;
}

