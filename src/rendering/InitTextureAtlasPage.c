/* InitTextureAtlasPage - 0x004f4170 in the original binary.
 *
 * Initializes an atlas page: tile bpp (+4), tiles-per-row (+8 =
 * 0x100/tileSize), total tile count (+0x10c), zeroes the 0x40-dword
 * used-tile bitmap, then CreateTextureAtlasSurface (Release on
 * failure). NAMED (2026-07-18); called by PreloadTexture.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REGISTER FIX (2026-08-06): the page (ESI) and the format id
 * (BL) were both read as uninitialised register artifacts - only the
 * tile size was a real argument. Recovered from orig 0x4f4170-0x4f41cb:
 * the prologue is `push ebp; mov ebp,[esp+8]` (the single stack arg =
 * tile size, `ret 4`), while ESI is the page throughout (`mov [esi+4],
 * ebp`, `mov [esi],bl`, `lea edi,[esi+0xc]`) and BL is stored to the
 * page's byte 0. At the call site (0x4f4481-0x4f4497) ESI is the page
 * AllocTextureAtlasPage just returned and BL is PreloadTexture's format
 * id, both still live in those registers.
 *
 * The nested CreateTextureAtlasSurface call was argless too, which was
 * worse than a wrong value: it is __fastcall with one STACK parameter,
 * so the callee pops 4 bytes the caller never pushed and unbalances this
 * function's stack. The original passes EDX = page+0x110 (the surface
 * slot this function reads back on failure) and pushes the format id.
 */
#include "ghidra_types.h"


uint InitTextureAtlasPage(int param_1,undefined1 *page,undefined1 formatId)

{
  int *piVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined1 unaff_BL = formatId;
  undefined1 *unaff_ESI = page;
  undefined4 *puVar5;

  cVar2 = CreateTextureAtlasSurface(0,(undefined4)(unaff_ESI + 0x110),formatId);
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

