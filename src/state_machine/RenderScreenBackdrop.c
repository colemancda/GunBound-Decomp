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
 *
 * FIXED (2026-07-14): the internal FindSpriteFrame() call was also a
 * zero-arg dropped-register stub. Confirmed via objdump at this
 * function's real entry (0x443570): `mov edx,0x2710` (outerKey=10000,
 * the same sprite-set State06_Logo2_Render uses) / `mov eax,0xea0e18`
 * (container=&DAT_00ea0e18) / `xor esi,esi` (innerKey=0, a fixed frame
 * index - this backdrop is static, not animated) immediately before
 * `call 0x4f30c0`. Recovered while wiring up State01_Title/State05_Logo1's
 * real vtable render slot (both point here, slot 15 = 0x443570 in each's
 * own real vtable in .data).
 *
 * FIXED (2026-07-14): the BlitSprite16bpp() call above was missing its
 * 3rd (y) argument, despite this file's own header already documenting
 * the real value as 0 (`push eax` twice, EAX held 0 the whole time) -
 * the call site was just never updated to actually pass it. Under
 * BlitSprite16bpp's real (frame,x,y) signature this left `y` reading
 * uninitialized stack garbage, live-reproduced as a black ServerSelect
 * screen (this function's vtable slot is shared by Title/Logo1/
 * ServerSelect - unlike Logo2, which uses its own State06_Logo2_Render
 * and was never exercised by this bug). Compare State06_Logo2_Render.c's
 * own (already-correct) `BlitSprite16bpp(frameIndex,0,0)` call.
 */
#include "ghidra_types.h"


void RenderScreenBackdrop(void)

{
  int iVar1;

  if (DAT_0079352c != 0) {
    iVar1 = FindSpriteFrame((int)&DAT_00ea0e18,10000,0);
    if (iVar1 != 0) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(0, 0, 0, 10000);
        return;
      }
      BlitSpriteClipped(0, 0, 0, 10000);
    }
  }
  return;
}

