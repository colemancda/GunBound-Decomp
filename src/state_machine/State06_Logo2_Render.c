/* State06_Logo2_Render - 0x00443360 in the original binary.
 *
 * CGameState vtable slot 15 (+0x3c) - the per-state main render pass,
 * called every tick from GameTick's `(*(GameStateVirtualFn *)(vtable +
 * 0x3c))(this)` inside the LockBackBuffer-guarded block. This slot was
 * simply MISSING from src/globals.c's reconstructed vtable (which only
 * populated slots 0-9), so nothing ever drew - the black screen.
 *
 * Recovered from the original binary's real vtable_State06_Logo2 in
 * .data at 0x555528 (slot 15 = 0x00443360), then disassembled:
 *   mov edx,[ecx+0x4]   ; this->frameCounter (the same field OnTick
 *                       ;   increments and checks against 0x28)
 *   xor eax,eax
 *   cmp edx,0x28
 *   setge al            ; frame index = (frameCounter >= 40) ? 1 : 0
 *   mov esi,eax
 *   mov eax,ds:0x79352c ; DAT_0079352c - backbuffer-locked flag
 *   test eax,eax
 *   je ret              ; not locked -> nothing to draw
 *   test esi,esi
 *   jl ret
 *   mov edx,0x2710      ; sprite-set id 10000 (the set OnEnter loads
 *                       ;   logomode2.img into)
 *   mov eax,0xea0e18    ; &DAT_00ea0e18 - the sprite registry
 *   call 0x4f30c0       ; FindSpriteFrame(container=EAX, outer=EDX, inner=ESI)
 *   test eax,eax
 *   je ret              ; frame not found
 *   cmp byte [eax+0x18],1
 *   jne clipped
 *   BlitSprite16bpp(frame=ESI, 0, 0)   ; 2 cdecl stack args + EAX
 *   ret
 * clipped:
 *   BlitSpriteClipped(ESI, x=ECX=0, y=EAX=0)
 *
 * i.e. it blits sprite-set 10000's frame 0 (or frame 1 once the logo has
 * been on screen 40 ticks), picking the full or clipped blit path from the
 * frame record's +0x18 flag - exactly the same shape as
 * RenderScreenBackdrop (0x443570), which is Title/Logo1's equivalent.
 *
 * __thiscall (this in ECX, no other args) per the original's `ret` with no
 * stack cleanup; declared __fastcall with a dummy EDX slot since MSVC 7.1
 * forbids explicit __thiscall on a C function (same idiom as
 * ChangeGameState.c's GameStateVirtualFn).
 */
#include "ghidra_types.h"


void __fastcall State06_Logo2_Render(int param_1,int dummyEDX)

{
  int frameIndex;
  int frameRecord;

  (void)dummyEDX;
  frameIndex = (0x28 <= *(int *)(param_1 + 4));
  if (DAT_0079352c == 0) {
    return;
  }
  frameRecord = FindSpriteFrame((int)&DAT_00ea0e18,10000,frameIndex);
  if (frameRecord == 0) {
    return;
  }
  if (*(char *)(frameRecord + 0x18) == '\x01') {
    BlitSprite16bpp(frameIndex,0,0);
  }
  else {
    BlitSpriteClipped(frameIndex,0,0);
  }
  return;
}
