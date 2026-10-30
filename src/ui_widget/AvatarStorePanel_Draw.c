/* AvatarStorePanel_Draw - 0x0050a8f0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: CAvatarStorePanel's slot-8 Draw
 * override. The original's vtable 0x557eb8 holds this at slot 8
 * (+0x20), the slot src/cxx/Widget.h declares as CWidget::Draw ("self
 * + child broadcast", base body Widget_DrawChildren 0x50e520); the
 * vtable is installed only by BuildAvatarStorePanel (0x509ea5), and
 * Widget.h records it as CAvatarStorePanel's. The tail is that base
 * broadcast - each child's own slot 8 - and the override adds a drag
 * auto-scroll in front: while +0x90 is set and +0x94 is not -1 (the
 * dragged row's catalog index, per RenderAvatarListDragRow.c), a
 * cursor (g_cursorAnchorY) above y+0x68 or below y+0x156 nudges the
 * id-0 scrollbar child by -1/+1 through FUN_0050f840, which clamps the
 * scrollbar's position and reports evt 0x2000 to its parent (here
 * AvatarStorePanel_OnCommand, which re-pages the store).
 *
 * Slot numbering caution: the `_Draw` suffix here is slot 8, as for
 * ScrollListWidget_Draw (0x50f660). WorldListPanel_Draw (0x50dc40) is
 * the exception - it is slot 9 of 0x557f08, Widget.h's Update.
 *
 * FIXED (2026-10-30), from the disassembly of 0x50a8f0-0x50a97f:
 *  1. FUN_0050f840 was called with no arguments. At 0x50a94f-0x50a957
 *     ECX = EBP (the scroll direction) and EDX = the child found by
 *     index (`mov edx,[ebx+0xc] / mov edx,[edx+eax*4]`). The direction
 *     computation itself (0x50a908-0x50a926) had been dropped
 *     entirely; it is restored, and FUN_0050f840's prototype gains its
 *     two __fastcall parameters (this is its only call site).
 *  2. The child Draw broadcast passed no `this`. At 0x50a969-0x50a971
 *     ECX = the child and nothing is pushed - a 0-argument __thiscall,
 *     now dispatched as __fastcall(this) (the
 *     TickActiveObjectRegistry.c idiom).
 *
 * FIXED (2026-10-30): Widget_FindChildIndex now gets its register
 * arguments - ECX = this (0x50a933), ESI = 0, EDI = 4 (the scrollbar
 * type).
 * Panel.cpp declares no CAvatarStorePanel::Draw.
 */
#include "ghidra_types.h"

/* Slot 8 of a child CWidget: a 0-argument __thiscall, dispatched as
 * __fastcall(this) - see the header. */
typedef void (__fastcall *ChildDrawFn)(void *thisPtr);

void __fastcall AvatarStorePanel_Draw(int param_1)

{
  uint uVar1;
  int dir;
  
  if ((*(char *)(param_1 + 0x90) != '\0') && (*(int *)(param_1 + 0x94) != -1)) {
    /* RECOVERED (2026-10-30), 0x50a908-0x50a926: EBP = the auto-scroll
     * direction from the cursor's y against the item rows' band. */
    dir = 0;
    if ((int)g_cursorAnchorY < *(int *)(param_1 + 0x2c) + 0x68) {
      dir = -1;
    }
    if (*(int *)(param_1 + 0x2c) + 0x156 < (int)g_cursorAnchorY) {
      dir = 1;
    }
    uVar1 = Widget_FindChildIndex(param_1,0,4);
    if (uVar1 != 0xffffffff) {
      if (*(uint *)(param_1 + 0x10) <= uVar1) goto LAB_0050a945;
      /* 0x50a94f-0x50a957: ECX = dir (EBP), EDX = the found child */
      FUN_0050f840(dir,*(int *)(*(int *)(param_1 + 0xc) + uVar1 * 4));
    }
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0x10) != 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
LAB_0050a945:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      /* 0x50a969-0x50a971: ECX = the child, nothing pushed. */
      {
        void *child = *(void **)(*(int *)(param_1 + 0xc) + uVar1 * 4);
        ((ChildDrawFn)(*(void ***)child)[8])(child);
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < *(uint *)(param_1 + 0x10));
  }
  return;
}
