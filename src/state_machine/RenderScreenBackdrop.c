/* RenderScreenBackdrop - 0x00443570 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER ARGUMENTS (pattern #1) - fixed here at this
 * function's own two BlitSprite16bpp()/BlitSpriteClipped() call sites
 * (the separate, already-documented FindSpriteFrame() zero-arg call
 * above is a distinct, project-wide, explicitly out-of-scope stub -
 * see FindSpriteFrame.c's header comment).
 *
 * Confirmed via objdump at this function's own entry (0x443570):
 *   xor    eax,eax        ; eax = 0
 *   cmp    cl,0x1
 *   push   eax            ; stack arg #1 = 0 (shared by both branches)
 *   jne    0x4435a5
 *   push   eax            ; stack arg #2 = 0
 *   call   0x4ed6a0       ; BlitSprite16bpp(0, 0)   - 2 cdecl stack args,
 *                         ;   `add esp,0x8` after confirms both were pushed
 *   ...
 *   xor    ecx,ecx        ; x = 0 (ECX register arg)
 *   call   0x4eb9c0       ; BlitSpriteClipped(0, 0, 0) - frame=0 (the stack
 *                         ;   push from above), x=0 (ECX), y=0 (EAX, still
 *                         ;   zero from the earlier `xor eax,eax`)
 * Both callees already carry their real recovered signatures
 * (BlitSprite16bpp.c: 2 params; BlitSpriteClipped.c: 3 params - frame,x,y)
 * but this call site was only passing the first argument to each,
 * silently dropping the rest. All missing args happen to be 0 here.
 */
#include "ghidra_types.h"


void RenderScreenBackdrop(void)

{
  int iVar1;

  if (DAT_0079352c != 0) {
    iVar1 = FindSpriteFrame();
    if (iVar1 != 0) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(0, 0);
        return;
      }
      BlitSpriteClipped(0, 0, 0);
    }
  }
  return;
}

