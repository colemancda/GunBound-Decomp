/* PresentFrame - 0x004f0070 in the original binary.
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


bool PresentFrame(void)

{
  int iVar1;
  
  (**(code **)(*g_pPrimarySurface + 0x70))(g_pPrimarySurface,g_pClipper);
  iVar1 = (**(code **)(*g_pPrimarySurface + 0x14))
                    (g_pPrimarySurface,&DAT_006773b4,g_pBackBufferSurface,0,0x1000000,0);
  if (iVar1 == -0x7789fe3e) {
    (**(code **)(*g_pPrimarySurface + 0x6c))(g_pPrimarySurface);
    (**(code **)(*g_pBackBufferSurface + 0x6c))(g_pBackBufferSurface);
    (**(code **)(*g_pZBufferSurface + 0x6c))(g_pZBufferSurface);
    iVar1 = (**(code **)(*g_pD3DDevice7 + 0x20))(g_pD3DDevice7,g_pBackBufferSurface,0);
    if (iVar1 < 0) {
      return false;
    }
  }
  return iVar1 == 0;
}

