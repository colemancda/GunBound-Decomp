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
 * Near-verbatim port of Ghidra's decompiler output; the g_pD3DDevice7
 * vtable dispatches (SetTextureStageState +0x50, SetTexture +0x8c,
 * DrawPrimitiveVB +0x64) use the same direct `(**(code**)(*dev+off))(dev,
 * ...)` idiom already established in RenderWeatherHazards.c/
 * FlushSpriteBatch.c (they are __stdcall COM methods; the shared cdecl
 * `code()` cast is the project's accepted form for these). Not yet
 * hand-verified beyond that. See src/README.md's "Raw/verbatim ports".
 */
#include "ghidra_types.h"


void __fastcall State07_AvatarStore_RenderAvatarPreview(int param_1)

{
  int iVar1;

  (void)param_1; /* slot-14 dispatch passes `this` in ECX; original ignores it */
  if (DAT_00793611 != '\x01') {
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,1);
  }
  DAT_00793611 = 1;
  iVar1 = FindTextureCacheEntryByName(s_AvataTexture1_0055565c);
  if (g_currentBlendMode != 1) {
    g_currentBlendMode = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
  }
  if (iVar1 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    *(undefined4 *)(iVar1 + 0x80) = 0;
    *(undefined4 *)(iVar1 + 0x84) = 0;
    *(undefined4 *)(iVar1 + 0x88) = 0x3f000000;
    BuildSizedSpriteQuad(599,0x53,0,0x80,0x80,0xffffffff);
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar1 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  if (g_currentBlendMode != 2) {
    g_currentBlendMode = 2;
    _DAT_00792194 = 2;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
  }
  if (iVar1 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    *(undefined4 *)(iVar1 + 0x80) = 0x3f000000;
    *(undefined4 *)(iVar1 + 0x84) = 0;
    *(undefined4 *)(iVar1 + 0x88) = 0x3f000000;
    BuildSizedSpriteQuad(599,0x53,0,0x80,0x80,0xffffffff);
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar1 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  return;
}
