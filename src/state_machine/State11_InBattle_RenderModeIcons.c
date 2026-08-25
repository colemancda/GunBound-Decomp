/* State11_InBattle_RenderModeIcons - 0x004caed0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified. *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 4 argless PeekPacketChecksumState() calls (4 C : 4 orig,
 * goto-free zip) - the per-turn shot parameter at +0x5b1ac, the
 * battle-mode cell at +0x45354, and two reads of the current-slot
 * index at +0x3b49c.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall State11_InBattle_RenderModeIcons(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FindTextureCacheEntryByName(&DAT_00554060);
  if (DAT_00793611 != '\x01') {
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x1b,1);
  }
  DAT_00793611 = 1;
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
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar1 + 0x94) + 0x110));
    if (*(char *)(param_1 + 0x11d0) == '\0') {
      *(undefined4 *)(iVar1 + 0x88) = 0x3e75c28f;
      *(undefined4 *)(iVar1 + 0x80) = 0x3f4147ae;
      *(undefined4 *)(iVar1 + 0x84) = 0x3ba3d70a;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(g_clientContext + 0x5b1ac));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      BuildSizedSpriteQuad(400,0x47,0,0x40,0x40,0xffffffff);
      FlushSpriteBatch();
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 == 2) {
    iVar1 = FindTextureCacheEntryByName(s_TagTexture_005568b8);
    if (iVar1 != 0) {
      (**(code **)(*g_pD3DDevice7 + 0x8c))
                (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar1 + 0x94) + 0x110));
      *(undefined4 *)(iVar1 + 0x88) = 0x3f000000;
      *(undefined4 *)(iVar1 + 0x80) = 0;
      *(undefined4 *)(iVar1 + 0x84) = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      BuildScaledSpriteQuad(0x2f4,0x246,*(int *)(g_clientContext + 0x1ff18 + iVar2 * 0x18) == 1,0xff,0xffffff);
      FlushSpriteBatch();
      if (g_currentBlendMode != 2) {
        g_currentBlendMode = 2;
        _DAT_00792194 = 2;
        (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
        (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
      }
      *(undefined4 *)(iVar1 + 0x80) = 0x3f000000;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      BuildScaledSpriteQuad(0x2f4,0x246,*(int *)(g_clientContext + 0x1ff18 + iVar1 * 0x18) == 1,0xff,0xffffff);
      FlushSpriteBatch();
    }
  }
  if (g_currentBlendMode != 1) {
    g_currentBlendMode = 1;
    _DAT_00792194 = 1;
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
  }
  iVar1 = FindTextureCacheEntryByName(s_YesooriTexture_005567d0);
  if (iVar1 == 0) {
    (**(code **)(*g_pD3DDevice7 + 0x8c))(g_pD3DDevice7,0,0);
  }
  else {
    if (*(char *)(g_clientContext + 0x2325c) != '\0') {
      FUN_004ec120(*(int *)(g_clientContext + 0x23268),400,0x12a,*(undefined4 *)(g_clientContext + 0x23264),*(int *)(g_clientContext + 0x23260));
    }
    (**(code **)(*g_pD3DDevice7 + 0x8c))
              (g_pD3DDevice7,0,*(undefined4 *)(*(int *)(iVar1 + 0x94) + 0x110));
  }
  if (g_spriteVertexCount != 0) {
    g_frameTriangleCounter = g_frameTriangleCounter + g_spriteVertexCount;
    (**(code **)(*g_pD3DDevice7 + 100))
              (g_pD3DDevice7,4,0x244,&g_spriteVertexBuffer,g_spriteVertexCount * 3,1);
    g_spriteVertexCount = 0;
    *(undefined1 *)(g_clientContext + 0x2325c) = 0;
    return;
  }
  *(undefined1 *)(g_clientContext + 0x2325c) = 0;
  return;
}

