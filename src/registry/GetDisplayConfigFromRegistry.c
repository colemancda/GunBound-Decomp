/* GetDisplayConfigFromRegistry - 0x0040c620 in the original binary.
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


undefined4 GetDisplayConfigFromRegistry(void)

{
  HDC hdc;
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = 0;
  hdc = GetDC((HWND)0x0);
  if (hdc != (HDC)0x0) {
    /* 0x40c63b..0x40c64e: stack arg = BITSPIXEL (0xc), ECX = VERTRES (10),
     * EDX = HORZRES (8). */
    iVar1 = GetDeviceCaps(hdc,0xc);
    iVar3 = GetDeviceCaps(hdc,10);
    iVar4 = GetDeviceCaps(hdc,8);
    uVar2 = ReadRegistryDword(iVar3,iVar4,iVar1);
    ReleaseDC((HWND)0x0,hdc);
  }
  return uVar2;
}

