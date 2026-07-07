/* SetupZBuffer - 0x004ef9a0 in the original binary.
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


bool SetupZBuffer(void)

{
  int iVar1;
  int *piStack_188;
  undefined *puStack_184;
  code *pcStack_180;
  undefined4 *puStack_17c;
  int *piStack_178;
  undefined1 *puStack_174;
  int *piStack_170;
  undefined1 *puStack_16c;
  int aiStack_140 [3];
  undefined4 uStack_134;
  undefined4 auStack_130 [8];
  undefined4 uStack_110;
  undefined1 local_ec [61];
  char cStack_af;
  
  puStack_16c = local_ec;
  piStack_170 = g_pD3DDevice7;
  puStack_174 = (undefined1 *)0x4ef9b6;
  (**(code **)(*g_pD3DDevice7 + 0xc))();
  if (cStack_af < '\0') {
    return true;
  }
  piStack_170 = (int *)0x7c;
  piStack_178 = g_pBackBufferSurface;
  puStack_17c = (undefined4 *)0x4ef9e1;
  puStack_174 = (undefined1 *)&piStack_170;
  (**(code **)(*g_pBackBufferSurface + 0x58))();
  puStack_17c = auStack_130;
  pcStack_180 = FUN_004ef970;
  puStack_184 = &DAT_00f22504;
  puStack_174 = (undefined1 *)0x1007;
  uStack_110 = 0x24000;
  auStack_130[0] = 0;
  piStack_188 = g_pDirect3D7;
  (**(code **)(*g_pDirect3D7 + 0x18))();
  if (aiStack_140[0] == 0) {
    uStack_134 = 0x10;
    (**(code **)(*g_pDirect3D7 + 0x18))(g_pDirect3D7,&DAT_00f22504,FUN_004ef970,aiStack_140);
    if (aiStack_140[0] == 0) {
      return false;
    }
  }
  iVar1 = (**(code **)(*g_pDirectDraw7 + 0x18))(g_pDirectDraw7,&piStack_188,&g_pZBufferSurface,0);
  if ((-1 < iVar1) &&
     (iVar1 = (**(code **)(*g_pBackBufferSurface + 0xc))(g_pBackBufferSurface,g_pZBufferSurface),
     -1 < iVar1)) {
    iVar1 = (**(code **)(*g_pD3DDevice7 + 0x20))(g_pD3DDevice7,g_pBackBufferSurface,0);
    return -1 < iVar1;
  }
  return false;
}

