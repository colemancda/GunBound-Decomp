/* FUN_00401650 - 0x00401650 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00401650(void)

{
  int *unaff_ESI;
  int iVar1;
  
  if (unaff_ESI[1] != 0) {
    iVar1 = 0;
    if (0 < *unaff_ESI) {
      do {
        _free(*(void **)(unaff_ESI[1] + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *unaff_ESI);
    }
    _free((void *)unaff_ESI[1]);
    unaff_ESI[1] = 0;
  }
  if ((void *)unaff_ESI[2] != (void *)0x0) {
    _free((void *)unaff_ESI[2]);
  }
  unaff_ESI[2] = 0;
  if ((void *)unaff_ESI[3] != (void *)0x0) {
    _free((void *)unaff_ESI[3]);
  }
  unaff_ESI[3] = 0;
  if (unaff_ESI[4] != 0) {
    iVar1 = 0;
    if (0 < *unaff_ESI) {
      do {
        _free(*(void **)(unaff_ESI[4] + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *unaff_ESI);
    }
    _free((void *)unaff_ESI[4]);
    unaff_ESI[4] = 0;
  }
  if (unaff_ESI[5] != 0) {
    iVar1 = 0;
    if (0 < *unaff_ESI) {
      do {
        _free(*(void **)(unaff_ESI[5] + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *unaff_ESI);
    }
    _free((void *)unaff_ESI[5]);
    unaff_ESI[5] = 0;
  }
  return;
}

