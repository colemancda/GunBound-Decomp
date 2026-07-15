/* FindGroundHeightAtColumn - 0x004e4340 in the original binary.
 *
 * Scans terrain object `param_2` (width +0x18, height +0x1c, pixel
 * buffer +0x34) down column `x` starting at row `y` (clamped to >=0),
 * looking for the first non-zero (solid) terrain pixel; returns that
 * row, or the sentinel 10000 if `x` is out of bounds or no solid pixel
 * is found before the bottom. `x`/`y` were dropped as unaff_EDI/in_EAX
 * (confirmed via direct disassembly of this function's own body at
 * 0x4e4340: EDX=param_2/terrain obj, EDI=x, EAX=y - the real fastcall
 * convention plus 2 extra non-standard registers, same bug class as
 * DrawHLine/ClampCursorToRect). Every caller's `x`/`y` value recovered
 * via an angr CFG backward-taint scan (tools/scan_findgroundheightat
 * column.py, cached in tools/findgroundheightatcolumn_sites.json).
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 */
#include "ghidra_types.h"


int __fastcall FindGroundHeightAtColumn(undefined4 param_1,int param_2,int x,int y)

{
  int iVar1;
  char *pcVar2;

  if ((-1 < x) && (iVar1 = *(int *)(param_2 + 0x18), x < iVar1)) {
    if (y < 0) {
      y = 0;
    }
    pcVar2 = (char *)(iVar1 * y + *(int *)(param_2 + 0x34) + x);
    while( true ) {
      if (*(int *)(param_2 + 0x1c) <= y) {
        return 10000;
      }
      if (*pcVar2 != '\0') break;
      pcVar2 = pcVar2 + iVar1;
      y = y + 1;
    }
    return y;
  }
  return 10000;
}

