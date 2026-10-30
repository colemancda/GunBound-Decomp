/* StaticText_Update - 0x0050dfd0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-30), CERTAIN: CStaticText's slot-9 Update override.
 * The original's vtable 0x557f30 holds this at slot 9 (+0x24), the
 * slot src/cxx/Widget.h declares as CWidget::Update; the vtable is
 * stored only by CreateStaticTextWidget (0x508024), and Widget.h
 * records it as CStaticText's. Slots 0-8 are all inherited base bodies
 * (Widget_DrawChildren at slot 8), so this is the class's one override.
 * Its draw reads exactly the two fields Widget.h gives the class: the
 * RGB565 color m_color (+0x38) and the 0x80-byte lines of m_wrapped
 * (+0x3a). It then forwards Update to each child, as the base slot-9
 * broadcast Widget_DrawChildrenDeep (0x50ecf0) does.
 *
 * FIXED (2026-10-30): the child Update calls passed no `this`. At
 * 0x50e025-0x50e02d the original loads the child into ECX (`mov
 * ecx,[eax+edi*4] / mov edx,[ecx] / call [edx+0x24]`) and pushes
 * nothing - a 0-argument __thiscall. Now dispatched through a
 * __fastcall(this) pointer, ABI-identical for a 0-argument method (the
 * TickActiveObjectRegistry.c idiom; __thiscall itself is erased by
 * ghidra_types.h).
 *
 * Noted, not fixed: Widget_DrawChildrenDeep (0x50ecf0) has the same
 * argless child call. Panel.cpp/Widget.h declare no
 * CStaticText::Update, so the C++ build never reaches this body.
 *
 * BlitRLESprite's dropped 4th arg (rleData) and its ECX/`this` arg were
 * recovered from objdump at this file's single call site (0x50dff8):
 *   lea  ebx,[esi + 0x3a]      ; ebx = param_1 + 0x3a  (rleData, before loop)
 *   ...
 *   mov  eax,ebx               ; EAX = rleData for this iteration <-- dropped
 *   mov  ecx,[esi + 0x28]      ; ECX = *(int *)(param_1 + 0x28)    <-- dropped
 *   call BlitRLESprite
 *   ...
 *   add  ebx,0x80              ; rleData advances by 0x80 bytes/iteration,
 *                               ; in lockstep with iVar1's +0xe/iteration.
 * Neither *(param_1+0x28) nor the param_1+0x3a-based array is referenced
 * anywhere else in this function, so both are new to this fix.
 */
#include "ghidra_types.h"

/* Slot 9 of a child CWidget: a 0-argument __thiscall, dispatched as
 * __fastcall(this) - see the header. */
typedef void (__fastcall *ChildUpdateFn)(void *thisPtr);

void __fastcall StaticText_Update(int param_1)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;

  if (*(char *)(param_1 + 0x1e) == '\0') {
    iVar1 = 0;
    pbVar3 = (byte *)(param_1 + 0x3a);
    do {
      if (*(int *)(param_1 + 0x2c) < iVar1) break;
      BlitRLESprite(*(int *)(param_1 + 0x28),iVar1 + *(int *)(param_1 + 0x2c),
                    *(undefined2 *)(param_1 + 0x38),pbVar3);
      iVar1 = iVar1 + 0xe;
      pbVar3 = pbVar3 + 0x80;
    } while (iVar1 < 0x8c);
    if (*(char *)(param_1 + 0x1e) == '\0') {
      uVar2 = 0;
      if (*(int *)(param_1 + 0x10) != 0) {
        if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        do {
          /* 0x50e025-0x50e02d: ECX = the child, nothing pushed. */
          {
            void *child = *(void **)(*(int *)(param_1 + 0xc) + uVar2 * 4);
            ((ChildUpdateFn)(*(void ***)child)[9])(child);
          }
          uVar2 = uVar2 + 1;
        } while (uVar2 < *(uint *)(param_1 + 0x10));
      }
    }
  }
  return;
}

