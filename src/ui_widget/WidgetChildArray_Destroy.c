/* WidgetChildArray_Destroy - 0x0050e560 in the original binary.
 *
 * The recursive widget-tree teardown: re-vtables `this` to the destructor
 * vtable (0x557f58), then for each child in the +0xc/+0x10 child array
 * destroys the child's own subtree, frees the child, and compacts the array;
 * finally frees the array backing store. Called directly (not via vtable) by
 * CPanelManager::PruneByKey (FUN_005098e0) to tear down a pruned panel.
 *
 * FIXED (2026-07-20): two bugs that never fired while this was dead code
 * (its only caller, the panel prune, was a no-op stub until now):
 *  1. SEH-PROLOGUE ARTIFACT -> CRASH. Ghidra's `unaff_FS_OFFSET` was an
 *     UNINITIALISED pointer that the body read and wrote (`*unaff_FS_OFFSET`),
 *     faulting on the first write (observed: write to IID_IDirectDraw7+0x20
 *     at WidgetChildArray_Destroy+0x13). The original's `push -1 / push
 *     0x5378ab / mov fs:[0],esp` is a standard MSVC exception frame; stripped
 *     per the entry/InitGame.c idiom (we don't reproduce __try frames), same
 *     as InitConnectionObject and others.
 *  2. DROPPED RECURSION ARGUMENT. Orig 0x50e5a6 `mov ecx,ebx; call 0x50e560`
 *     recurses on the CHILD (ebx = the child-array element), but Ghidra lost
 *     the ECX arg and it had been made to compile by passing `param_1`
 *     (self) - infinite/self recursion over the same array. Recurse on the
 *     child `pvVar1`.
 */
#include "ghidra_types.h"


void __fastcall WidgetChildArray_Destroy(undefined4 *param_1)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;

  *param_1 = &PTR_LAB_00557f58;
  uVar4 = param_1[4];
  uVar2 = uVar4;
  while( true ) {
    uVar2 = uVar2 - 1;
    if ((int)uVar2 < 0) {
      if ((void *)param_1[3] != (void *)0x0) {
        _free((void *)param_1[3]);
      }
      return;
    }
    if ((uint)param_1[4] <= uVar2) break;
    pvVar1 = *(void **)(param_1[3] + uVar2 * 4);
    if (pvVar1 != (void *)0x0) {
      /* orig 0x50e5a6 `mov ecx,ebx; call 0x50e560`: recurse on the CHILD
       * (pvVar1), not on self - see the header note. */
      WidgetChildArray_Destroy((undefined4 *)pvVar1);
      _free(pvVar1);
    }
    if ((uint)param_1[4] < uVar4) break;
    iVar3 = (param_1[4] - uVar2) + -1;
    if (iVar3 != 0) {
      pvVar1 = (void *)(param_1[3] + uVar2 * 4);
      _memmove(pvVar1,(void *)((int)pvVar1 + 4),iVar3 * 4);
    }
    uVar4 = uVar4 - 1;
    param_1[4] = param_1[4] + -1;
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

