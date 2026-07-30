/* PanelManager_Unregister - 0x0050ef10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CI COMPILE-ERR FIX (2026-07-30): PanelManager_ReleasePool/
 * WidgetChildArray_Destroy were given real 1-param prototypes in an
 * earlier pass (see FUN_0050f290.c's header) but this file's own two
 * call sites were never updated, breaking the build once MSVC started
 * enforcing the real prototypes (C2198 "too few arguments for call
 * through pointer-to-function" - __fastcall arg-count mismatches route
 * through that error even for direct calls). Confirmed via objdump
 * (orig 0x50ef76 and 0x50ef85): `this`=`piVar1` (ecx stays `ebp+4`,
 * unmodified since function entry) for PanelManager_ReleasePool, and
 * `this`=`_Memory` (esi, set from `piVar4[2]` earlier in this same
 * function) for WidgetChildArray_Destroy - same shape as FUN_0050f290's
 * own already-fixed calls to these two functions.
 */
#include "ghidra_types.h"


undefined4 PanelManager_Unregister(int *param_1)

{
  int *piVar1;
  void *_Memory;
  int *piVar2;
  int iVar3;
  int in_EAX;
  int *piVar4;
  int unaff_EBX;
  
  piVar1 = param_1 + 1;
  piVar4 = (int *)*piVar1;
  if (piVar4 != (int *)0x0) {
    while( true ) {
      _Memory = (void *)piVar4[2];
      piVar2 = (int *)*piVar4;
      if ((*(int *)((int)_Memory + 0x20) == in_EAX) && (*(int *)((int)_Memory + 0x24) == unaff_EBX))
      break;
      piVar4 = piVar2;
      if (piVar2 == (int *)0x0) {
        /* Ghidra emitted a bare `return;` in a value-returning function;
         * MSVC falls through with whatever's in EAX, gcc 14 rejects it
         * (-Wreturn-mismatch). This path's result is unused by callers -
         * return 0 to satisfy both toolchains without inventing a value. */
        return 0;
      }
    }
    if (piVar4 == (int *)*piVar1) {
      *piVar1 = *piVar4;
    }
    else {
      *(int *)piVar4[1] = *piVar4;
    }
    if (piVar4 == (int *)param_1[2]) {
      param_1[2] = piVar4[1];
    }
    else {
      *(int *)(*piVar4 + 4) = piVar4[1];
    }
    *piVar4 = param_1[5];
    iVar3 = param_1[3];
    param_1[5] = (int)piVar4;
    param_1[3] = iVar3 + -1;
    if (iVar3 + -1 == 0) {
      PanelManager_ReleasePool((undefined4 *)piVar1);
    }
    (**(code **)(*param_1 + 0x18))();
    WidgetChildArray_Destroy((undefined4 *)_Memory);
    _free(_Memory);
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

