/* Widget_DrawChildrenDeep - 0x0050ecf0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-10-30): the child Update calls passed no `this`. At
 * 0x50ed08-0x50ed10 the original loads the child into ECX (`mov
 * ecx,[eax+esi*4] / mov edx,[ecx] / call [edx+0x24]`) and pushes
 * nothing, which is a 0-argument __thiscall. The call now goes through a
 * __fastcall(this) pointer, which has the same ABI for a 0-argument
 * method (the StaticText_Update.c idiom; __thiscall itself is erased by
 * ghidra_types.h).
 */
#include "ghidra_types.h"

/* Slot 9 of a child CWidget: a 0-argument __thiscall, dispatched as
 * __fastcall(this) - see the header. */
typedef void (__fastcall *ChildUpdateFn)(void *thisPtr);


void __fastcall Widget_DrawChildrenDeep(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x1e) == '\0') {
    uVar1 = 0;
    if (*(int *)(param_1 + 0x10) != 0) {
      if (*(int *)(param_1 + 0x10) == 0) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      do {
        /* 0x50ed08-0x50ed10: ECX = the child, nothing pushed. */
        {
          void *child = *(void **)(*(int *)(param_1 + 0xc) + uVar1 * 4);
          ((ChildUpdateFn)(*(void ***)child)[9])(child);
        }
        uVar1 = uVar1 + 1;
      } while (uVar1 < *(uint *)(param_1 + 0x10));
    }
  }
  return;
}

