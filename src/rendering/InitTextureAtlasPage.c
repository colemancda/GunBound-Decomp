/* InitTextureAtlasPage - 0x004f4170 in the original binary.
 *
 * Initializes an atlas page: tile bpp (+4), tiles-per-row (+8 =
 * 0x100/tileSize), total tile count (+0x10c), zeroes the 0x40-dword
 * used-tile bitmap, then CreateTextureAtlasSurface (Release on
 * failure). NAMED (2026-07-18); called by PreloadTexture.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint InitTextureAtlasPage(int param_1)

{
  int *piVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined1 unaff_BL;
  undefined1 *unaff_ESI;
  undefined4 *puVar5;
  
  cVar2 = CreateTextureAtlasSurface();
  if (cVar2 == '\0') {
    piVar1 = *(int **)(unaff_ESI + 0x110);
    uVar3 = (**(code **)(*piVar1 + 8))(piVar1);
    *(undefined4 *)(unaff_ESI + 0x110) = 0;
    return uVar3 & 0xffffff00;
  }
  iVar4 = (int)(0x100 / (longlong)param_1);
  *(int *)(unaff_ESI + 4) = param_1;
  *unaff_ESI = unaff_BL;
  *(int *)(unaff_ESI + 8) = iVar4;
  *(int *)(unaff_ESI + 0x10c) = iVar4 * iVar4;
  puVar5 = (undefined4 *)(unaff_ESI + 0xc);
  for (iVar4 = 0x40; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  return 1;
}

