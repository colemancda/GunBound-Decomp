/* State09_ReadyRoom_RenderCharacterPreview - 0x004d90c0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall State09_ReadyRoom_RenderCharacterPreview(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int unaff_EBP;
  undefined4 *puVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  if (DAT_00793611 != '\x01') {
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,1);
  }
  DAT_00793611 = 1;
  iVar4 = FindTextureCacheEntryByName(s_AvataTexture1_0055565c);
  if (g_currentBlendMode != 1) {
    g_currentBlendMode = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
  }
  if (iVar4 == 0) {
    iVar8 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    uVar6 = 0;
    puVar5 = (undefined4 *)(param_1 + 0x6c0);
    iVar8 = g_clientContext;
    do {
      iVar7 = g_clientContext;
      if (*(char *)(iVar8 + 0x45914 + uVar6) != '\0') {
        uVar1 = *puVar5;
        uVar2 = puVar5[-1];
        *(undefined4 *)(iVar4 + 0x88) = 0x3f000000;
        *(float *)(iVar4 + 0x80) = (float)(uVar6 % 2) * _DAT_00557fb8;
        *(float *)(iVar4 + 0x84) = (float)(int)((ulonglong)uVar6 / 2) * _DAT_00557fb8;
        BuildScaledSpriteQuad(uVar2,uVar1,
                     CONCAT31((int3)((ulonglong)uVar6 / 2 >> 8),
                              *(char *)(iVar7 + 0x4590c + uVar6) == '\0'),0xff,0xffffff);
        iVar8 = iVar7;
      }
      uVar6 = uVar6 + 1;
      puVar5 = puVar5 + 2;
    } while ((int)uVar6 < 4);
    iVar8 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  iVar4 = FindTextureCacheEntryByName(s_AvataTexture2_00556914);
  if (iVar4 == 0) {
    iVar7 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    uVar6 = 0;
    puVar5 = (undefined4 *)(unaff_EBP + 0x6e0);
    iVar7 = g_clientContext;
    do {
      iVar3 = g_clientContext;
      if (*(char *)(iVar7 + 0x45918 + uVar6) != '\0') {
        uVar1 = *puVar5;
        uVar2 = puVar5[-1];
        *(undefined4 *)(iVar4 + 0x88) = 0x3f000000;
        *(float *)(iVar4 + 0x80) = (float)(uVar6 % 2) * _DAT_00557fb8;
        *(float *)(iVar4 + 0x84) = (float)(int)((ulonglong)uVar6 / 2) * _DAT_00557fb8;
        BuildScaledSpriteQuad(uVar2,uVar1,
                     CONCAT31((int3)((ulonglong)uVar6 / 2 >> 8),
                              *(char *)(iVar3 + 0x45910 + uVar6) == '\0'),0xff,0xffffff);
        iVar7 = iVar3;
      }
      uVar6 = uVar6 + 1;
      puVar5 = puVar5 + 2;
    } while ((int)uVar6 < 4);
    iVar7 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  iVar4 = FindTextureCacheEntryByName(s_CharacterTexture1_005568d8);
  if (iVar4 == 0) {
    iVar8 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    uVar6 = 0;
    puVar5 = (undefined4 *)(iVar8 + 0x6c0);
    iVar8 = g_clientContext;
    do {
      iVar3 = g_clientContext;
      if (*(char *)(iVar8 + 0x45914 + uVar6) != '\0') {
        uVar1 = *puVar5;
        uVar2 = puVar5[-1];
        *(undefined4 *)(iVar4 + 0x88) = 0x3f000000;
        *(float *)(iVar4 + 0x80) = (float)(uVar6 % 2) * _DAT_00557fb8;
        *(float *)(iVar4 + 0x84) = (float)(int)((ulonglong)uVar6 / 2) * _DAT_00557fb8;
        BuildScaledSpriteQuad(uVar2,uVar1,
                     CONCAT31((int3)((ulonglong)uVar6 / 2 >> 8),
                              *(char *)(iVar3 + 0x4590c + uVar6) == '\0'),0xff,0xffffff);
        iVar8 = iVar3;
      }
      uVar6 = uVar6 + 1;
      puVar5 = puVar5 + 2;
    } while ((int)uVar6 < 4);
    iVar8 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  iVar4 = FindTextureCacheEntryByName(s_CharacterTexture2_005568c4);
  if (iVar4 == 0) {
    iVar7 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    uVar6 = 0;
    puVar5 = (undefined4 *)(iVar7 + 0x6e0);
    iVar7 = g_clientContext;
    do {
      iVar3 = g_clientContext;
      if (*(char *)(iVar7 + 0x45918 + uVar6) != '\0') {
        uVar1 = *puVar5;
        uVar2 = puVar5[-1];
        *(undefined4 *)(iVar4 + 0x88) = 0x3f000000;
        *(float *)(iVar4 + 0x80) = (float)(uVar6 % 2) * _DAT_00557fb8;
        *(float *)(iVar4 + 0x84) = (float)(int)((ulonglong)uVar6 / 2) * _DAT_00557fb8;
        BuildScaledSpriteQuad(uVar2,uVar1,
                     CONCAT31((int3)((ulonglong)uVar6 / 2 >> 8),
                              *(char *)(iVar3 + 0x45910 + uVar6) == '\0'),0xff,0xffffff);
        iVar7 = iVar3;
      }
      uVar6 = uVar6 + 1;
      puVar5 = puVar5 + 2;
    } while ((int)uVar6 < 4);
    iVar7 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  iVar4 = FindTextureCacheEntryByName(s_AvataEffectTexture1_00556900);
  if (g_currentBlendMode != 2) {
    g_currentBlendMode = 2;
    _DAT_00792194 = 2;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
  }
  if (iVar4 == 0) {
    iVar8 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    uVar6 = 0;
    puVar5 = (undefined4 *)(iVar8 + 0x6c0);
    iVar8 = g_clientContext;
    do {
      iVar3 = g_clientContext;
      if (*(char *)(iVar8 + 0x45914 + uVar6) != '\0') {
        uVar1 = *puVar5;
        uVar2 = puVar5[-1];
        *(undefined4 *)(iVar4 + 0x88) = 0x3f000000;
        *(float *)(iVar4 + 0x80) = (float)(uVar6 % 2) * _DAT_00557fb8;
        *(float *)(iVar4 + 0x84) = (float)(uVar6 / 2) * _DAT_00557fb8;
        BuildScaledSpriteQuad(uVar2,uVar1,*(char *)(iVar3 + 0x4590c + uVar6) == '\0',0xff,0xffffff);
        iVar8 = iVar3;
      }
      uVar6 = uVar6 + 1;
      puVar5 = puVar5 + 2;
    } while ((int)uVar6 < 4);
    iVar8 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  iVar4 = FindTextureCacheEntryByName(s_AvataEffectTexture2_005568ec);
  if (iVar4 == 0) {
    iVar7 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    uVar6 = 0;
    puVar5 = (undefined4 *)(iVar7 + 0x6e0);
    iVar7 = g_clientContext;
    do {
      iVar3 = g_clientContext;
      if (*(char *)(iVar7 + 0x45918 + uVar6) != '\0') {
        uVar1 = *puVar5;
        uVar2 = puVar5[-1];
        *(undefined4 *)(iVar4 + 0x88) = 0x3f000000;
        *(float *)(iVar4 + 0x80) = (float)(uVar6 % 2) * _DAT_00557fb8;
        *(float *)(iVar4 + 0x84) = (float)(int)((ulonglong)uVar6 / 2) * _DAT_00557fb8;
        BuildScaledSpriteQuad(uVar2,uVar1,
                     CONCAT31((int3)((ulonglong)uVar6 / 2 >> 8),
                              *(char *)(iVar3 + 0x45910 + uVar6) == '\0'),0xff,0xffffff);
        iVar7 = iVar3;
      }
      uVar6 = uVar6 + 1;
      puVar5 = puVar5 + 2;
    } while ((int)uVar6 < 4);
    iVar7 = 0;
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  iVar4 = FindTextureCacheEntryByName(s_CharEffectTexture1_005568a4);
  if (iVar4 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    uVar6 = 0;
    puVar5 = (undefined4 *)(iVar8 + 0x6c0);
    iVar8 = g_clientContext;
    do {
      iVar3 = g_clientContext;
      if (*(char *)(uVar6 + 0x45914 + iVar8) != '\0') {
        uVar1 = *puVar5;
        uVar2 = puVar5[-1];
        *(undefined4 *)(iVar4 + 0x88) = 0x3f000000;
        *(float *)(iVar4 + 0x80) = (float)(uVar6 % 2) * _DAT_00557fb8;
        *(float *)(iVar4 + 0x84) = (float)(int)((ulonglong)uVar6 / 2) * _DAT_00557fb8;
        BuildScaledSpriteQuad(uVar2,uVar1,
                     CONCAT31((int3)((ulonglong)uVar6 / 2 >> 8),
                              *(char *)(iVar3 + 0x4590c + uVar6) == '\0'),0xff,0xffffff);
        iVar8 = iVar3;
      }
      uVar6 = uVar6 + 1;
      puVar5 = puVar5 + 2;
    } while ((int)uVar6 < 4);
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  iVar4 = FindTextureCacheEntryByName(s_CharEffectTexture2_00556890);
  if (iVar4 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    uVar6 = 0;
    puVar5 = (undefined4 *)(iVar7 + 0x6e0);
    iVar8 = g_clientContext;
    do {
      iVar7 = g_clientContext;
      if (*(char *)(iVar8 + 0x45918 + uVar6) != '\0') {
        uVar1 = *puVar5;
        uVar2 = puVar5[-1];
        *(undefined4 *)(iVar4 + 0x88) = 0x3f000000;
        *(float *)(iVar4 + 0x80) = (float)(uVar6 % 2) * _DAT_00557fb8;
        *(float *)(iVar4 + 0x84) = (float)(int)((ulonglong)uVar6 / 2) * _DAT_00557fb8;
        BuildScaledSpriteQuad(uVar2,uVar1,
                     CONCAT31((int3)((ulonglong)uVar6 / 2 >> 8),
                              *(char *)(iVar7 + 0x45910 + uVar6) == '\0'),0xff,0xffffff);
        iVar8 = iVar7;
      }
      uVar6 = uVar6 + 1;
      puVar5 = puVar5 + 2;
    } while ((int)uVar6 < 4);
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar4 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
  }
  return;
}

