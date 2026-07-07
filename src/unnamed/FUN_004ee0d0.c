/* FUN_004ee0d0 - 0x004ee0d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ee0d0(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + 0x25c);
  iVar2 = 0x40;
  do {
    if (piVar1[-1] != 0) {
      piVar1[-1] = piVar1[-1] + -1;
    }
    if (*piVar1 != 0) {
      *piVar1 = *piVar1 + -1;
    }
    if (piVar1[1] != 0) {
      piVar1[1] = piVar1[1] + -1;
    }
    if (piVar1[2] != 0) {
      piVar1[2] = piVar1[2] + -1;
    }
    piVar1 = piVar1 + 4;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

