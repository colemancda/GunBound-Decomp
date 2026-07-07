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
  
  uVar2 = 0;
  hdc = GetDC((HWND)0x0);
  if (hdc != (HDC)0x0) {
    iVar1 = GetDeviceCaps(hdc,0xc);
    GetDeviceCaps(hdc,10);
    GetDeviceCaps(hdc,8);
    uVar2 = ReadRegistryDword(iVar1);
    ReleaseDC((HWND)0x0,hdc);
  }
  return uVar2;
}

