/* FindTextureCacheEntryByName - 0x004f4650 in the original binary.
 *
 * Walks the texture cache's name-record list (+0x1b4, next at +0x98)
 * doing an inline strcmp of param_1 against each record's name at +0,
 * returning the matching record or NULL.
 *
 * DROPPED-`this` FIX (2026-07-16): the cache pointer arrives in EAX (a
 * custom register convention Ghidra dropped as an uninitialised
 * `int in_EAX`). Every original call site loads `mov eax, 0xeb1bd8` (or
 * forwards a param that is itself the same singleton - PreloadTexture's
 * `mov eax, ebp`) immediately before the call, so the value is always
 * &g_textureCache - the process-wide singleton constructed by the CRT
 * static-initializer 0x5429b0. Bound directly to the singleton rather
 * than adding a parameter, so the ~25 existing 1-arg callers stay
 * correct as-is. See FlushTextureCache.c for the family evidence.
 */
#include "ghidra_types.h"
#include <windows.h>


byte * FindTextureCacheEntryByName(byte *param_1)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;

  pbVar2 = *(byte **)(&g_textureCache[0] + 0x1b4);
  do {
    pbVar3 = param_1;
    pbVar5 = pbVar2;
    if (pbVar2 == (byte *)0x0) {
      return (byte *)0x0;
    }
    do {
      bVar1 = *pbVar3;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_004f468e:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_004f4693;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_004f468e;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_004f4693:
    if (iVar4 == 0) {
      return pbVar2;
    }
    pbVar2 = *(byte **)(pbVar2 + 0x98);
  } while( true );
}

