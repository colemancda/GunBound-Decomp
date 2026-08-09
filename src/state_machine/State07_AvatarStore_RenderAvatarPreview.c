/* State07_AvatarStore_RenderAvatarPreview - 0x00449050 in the original binary.
 *
 * PORTED + RENAMED (2026-08-09): CState07AvatarStore's vtable slot 14
 * (+0x38). The avatar-preview compositing pass: takes the AvataTexture1
 * off-screen texture the store built and draws it twice into the sprite
 * batch (a left-half then right-half quad, via BuildSizedSpriteQuad at
 * screen 599,0x53 size 0x80x0x80) with two different Direct3D texture-
 * stage blend setups, flushing the batch through IDirect3DDevice7::
 * DrawPrimitiveVB after each. Was an unported bring-up auto-stub, so the
 * store's avatar preview never drew - one of the two render slots (13/14)
 * that left the AVATAR store's main area blank. Slot 13
 * (State07_AvatarStore_RenderStoreContent) draws the background+items;
 * this slot composites the avatar on top.
 *
 * CALLING-CONVENTION FIX (2026-08-09, live-crash): the g_pD3DDevice7
 * vtable dispatches (SetRenderState +0x50, SetTexture +0x8c,
 * DrawPrimitive +0x64) are __stdcall COM methods, but the raw port
 * dispatched them through ghidra_types.h's generic `code()` cast -
 * `typedef int code()`, K&R cdecl, CALLER-clean - so every call double-
 * cleaned its stack args (callee `ret N` + caller `add esp,N`) and ESP
 * drifted upward. Files like FlushSpriteBatch.c survive the same latent
 * bug only because their EBP-framed epilogue (`mov esp,ebp`) silently
 * repairs the drift; this function is small enough that MSVC gave it an
 * ESP-relative frame, so its final `ret` popped drifted garbage and
 * jumped wild (live crash EIP=0xf75fcff4 entering the store, isolated to
 * this slot by NoOp-ing it). Fixed with explicit WINAPI (__stdcall)
 * typedefs - the established idiom (LockBackBuffer.c/PresentFrame.c/
 * CreateTextureAtlasSurface.c). The State09 sibling
 * (RenderCharacterPreview.c) and RenderWeatherHazards.c/FlushSpriteBatch.c
 * still carry the cdecl-cast form and are latent candidates for the same
 * fix when their paths go live. See src/README.md's "Raw/verbatim ports".
 */
#include "ghidra_types.h"
#include <windows.h>

/* IDirect3DDevice7 __stdcall vtable methods (this, ...):
 * +0x50 SetRenderState(state, value); +0x8c SetTexture(stage, texture);
 * +0x64 DrawPrimitive(type, fvf, vertices, vertexCount, flags). */
typedef long (WINAPI *D3DDevSetRenderStateFn)(void *, int, int);
typedef long (WINAPI *D3DDevSetTextureFn)(void *, int, void *);
typedef long (WINAPI *D3DDevDrawPrimitiveFn)(void *, int, int, void *, int, int);


void __fastcall State07_AvatarStore_RenderAvatarPreview(int param_1)

{
  int iVar1;

  (void)param_1; /* slot-14 dispatch passes `this` in ECX; original ignores it */
  if (DAT_00793611 != '\x01') {
    (*(D3DDevSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,1);
  }
  DAT_00793611 = 1;
  iVar1 = FindTextureCacheEntryByName(s_AvataTexture1_0055565c);
  if (g_currentBlendMode != 1) {
    g_currentBlendMode = 1;
    _DAT_00792194 = 1;
    (*(D3DDevSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (*(D3DDevSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
  }
  if (iVar1 == 0) {
    (*(D3DDevSetTextureFn *)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,(void *)0);
  }
  else {
    *(undefined4 *)(iVar1 + 0x80) = 0;
    *(undefined4 *)(iVar1 + 0x84) = 0;
    *(undefined4 *)(iVar1 + 0x88) = 0x3f000000;
    BuildSizedSpriteQuad(599,0x53,0,0x80,0x80,0xffffffff);
    (*(D3DDevSetTextureFn *)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(void **)(*(int *)(iVar1 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (*(D3DDevDrawPrimitiveFn *)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  if (g_currentBlendMode != 2) {
    g_currentBlendMode = 2;
    _DAT_00792194 = 2;
    (*(D3DDevSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (*(D3DDevSetRenderStateFn *)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
  }
  if (iVar1 == 0) {
    (*(D3DDevSetTextureFn *)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,(void *)0);
  }
  else {
    *(undefined4 *)(iVar1 + 0x80) = 0x3f000000;
    *(undefined4 *)(iVar1 + 0x84) = 0;
    *(undefined4 *)(iVar1 + 0x88) = 0x3f000000;
    BuildSizedSpriteQuad(599,0x53,0,0x80,0x80,0xffffffff);
    (*(D3DDevSetTextureFn *)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(void **)(*(int *)(iVar1 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (*(D3DDevDrawPrimitiveFn *)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  return;
}
