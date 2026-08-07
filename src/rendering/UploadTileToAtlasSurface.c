/* UploadTileToAtlasSurface - 0x004f41d0 in the original binary.
 *
 * Uploads one tile's pixels into its atlas page's DirectDraw surface:
 * Lock (vtbl+0x64, retried until it stops failing, e.g. on
 * DDERR_WASSTILLDRAWING), row-by-row copy into the computed tile rect,
 * Unlock (vtbl+0x80), then sets the tile's used flag (page byte
 * 0xc+tileIndex). NAMED (2026-07-18); called by PreloadTexture.
 *
 * RECONSTRUCTED (2026-08-06) from the 0x4f41d0-0x4f42ab disassembly,
 * fixing the same three bug classes as CreateTextureAtlasSurface.c:
 *
 *   1. Dropped EBX `this`: the atlas page arrives in EBX at the sole
 *      call site (PreloadTexture, orig 0x4f44c8 `mov ebx,[esp+0x1c]` -
 *      that stack slot is its `local_90` page variable). The raw port
 *      read an uninitialised `unaff_EBX` - live crash the moment this
 *      became reachable. Also, Ghidra emitted `unaff_retaddr` for the
 *      tile-flag write: with `ret 8` (two callee-cleaned stack args) it
 *      mis-mapped the final `mov edx,[esp+0x90]` re-read of the SECOND
 *      arg onto the return-address slot - the real store is
 *      `mov byte [edx+ebx+0xc],1` = page->usedTiles[tileIndex] = 1.
 *
 *   2. Split-struct DDSURFACEDESC2 (Lock's out-descriptor): local_7c[4]
 *      + iStack_6c + iStack_58 only form the real struct by placement
 *      luck, while the zero-loop wrote 0x7c bytes through the first.
 *      The Ghidra offsets map exactly: iStack_6c = +0x10 lPitch,
 *      iStack_58 = +0x24 lpSurface. Rebuilt as one real struct.
 *
 *   3. Generic `code()` COM dispatch for Lock/Unlock - the cdecl
 *      double-cleanup class. Now explicit __stdcall typedefs through
 *      VTBL slots 25 (Lock, +0x64) and 32 (Unlock, +0x80).
 *
 * Tile addressing (byte-recovered): dst = lpSurface + tileSize *
 * ((tileIndex / tilesPerRow) * lPitch + (tileIndex % tilesPerRow) * 2),
 * then tileSize rows of tileSize*2 bytes, stepping dst by lPitch -
 * 16-bit texels, tiles packed left-to-right then top-to-bottom.
 * page layout: +4 tileSize, +8 tilesPerRow, +0xc used-tile bytes,
 * +0x110 the IDirectDrawSurface7. The original re-reads the surface
 * pointer from page+0x110 on every Lock retry; kept. */
#include "ghidra_types.h"
#include <windows.h>

typedef HRESULT (WINAPI *SurfLockFn)(void *, void *, DDSURFACEDESC2 *, DWORD, HANDLE);
typedef HRESULT (WINAPI *SurfUnlockFn)(void *, void *);
/* Nth pointer-sized vtable slot (N = byte offset / 4). */
#define VTBL(iface, n) (*(void ***)(iface))[n]

void UploadTileToAtlasSurface(undefined4 *param_1,int param_2,undefined1 *page)

{
  HRESULT hr;
  void *surf;
  int tileSize;
  int tilesPerRow;
  uint rowBytes;
  uint row;
  char *dst;
  char *srcPix;
  DDSURFACEDESC2 ddsd;

  if (*(int *)(page + 0x110) != 0) {
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);           /* 0x7c */
    do {
      surf = *(void **)(page + 0x110);
      hr = ((SurfLockFn)VTBL(surf, 25))(surf, 0, &ddsd, 0, 0);
    } while (hr != 0);
    tileSize = *(int *)(page + 4);
    tilesPerRow = *(int *)(page + 8);
    dst = (char *)ddsd.lpSurface +
          ((param_2 / tilesPerRow) * ddsd.lPitch +
           (param_2 % tilesPerRow) * 2) * tileSize;
    rowBytes = (uint)tileSize * 2;
    srcPix = (char *)param_1;
    for (row = 0; row < (uint)tileSize; row = row + 1) {
      memcpy(dst, srcPix, rowBytes);
      dst = dst + ddsd.lPitch;
      srcPix = srcPix + rowBytes;
    }
    surf = *(void **)(page + 0x110);
    ((SurfUnlockFn)VTBL(surf, 32))(surf, 0);
    *(undefined1 *)(page + 0xc + param_2) = 1;   /* used-tile flag */
  }
  return;
}
