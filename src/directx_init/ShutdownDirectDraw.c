/* ShutdownDirectDraw - 0x004eff90 in the original binary.
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
#include "xfs.h"
#include <windows.h>


void ShutdownDirectDraw(void)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*(void **)((int)&DAT_00f22650 + iVar1) != (void *)0x0) {
      _free(*(void **)((int)&DAT_00f22650 + iVar1));
      *(undefined4 *)((int)&DAT_00f22650 + iVar1) = 0;
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x1000);
  /* Original set ESI=&g_graphicsArchive before this call (dropped by Ghidra);
   * FUN_004f0d70 (CloseXFSArchive) flushes and closes the graphics archive. */
  FUN_004f0d70(&g_graphicsArchive);
  FUN_004f3e70();
  FUN_004f3a30();
  /* Container passed in EBX by the original (`mov ebx,0xeb1bd8` immediately
   * before the call) - see src/unnamed/FUN_004f46b0.c's header. */
  FUN_004f46b0((int)&DAT_00eb1bd8);
  if (g_pD3DDevice7 != (int *)0x0) {
    (**(code **)(*g_pD3DDevice7 + 8))(g_pD3DDevice7);
    g_pD3DDevice7 = (int *)0x0;
  }
  if (g_pBackBufferSurface != (int *)0x0) {
    (**(code **)(*g_pBackBufferSurface + 8))(g_pBackBufferSurface);
    g_pBackBufferSurface = (int *)0x0;
  }
  if (g_pZBufferSurface != (int *)0x0) {
    (**(code **)(*g_pZBufferSurface + 8))(g_pZBufferSurface);
    g_pZBufferSurface = (int *)0x0;
  }
  if (g_pPrimarySurface != (int *)0x0) {
    (**(code **)(*g_pPrimarySurface + 8))(g_pPrimarySurface);
    g_pPrimarySurface = (int *)0x0;
  }
  if (g_pDirect3D7 != (int *)0x0) {
    (**(code **)(*g_pDirect3D7 + 8))(g_pDirect3D7);
    g_pDirect3D7 = (int *)0x0;
  }
  if (g_pDirectDraw7 != (int *)0x0) {
    (**(code **)(*g_pDirectDraw7 + 8))(g_pDirectDraw7);
    g_pDirectDraw7 = (int *)0x0;
  }
  FreeLibrary(g_hDDrawDll);
  return;
}

