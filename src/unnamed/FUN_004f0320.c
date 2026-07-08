/* FUN_004f0320 - 0x004f0320 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f0320(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0;
  piStack_c = g_pPrimarySurface;
  (**(code **)(*g_pPrimarySurface + 0x70))();
  if (DAT_00588f4c != '\0') {
    piVar3 = g_pDirectDraw7;
    (**(code **)(*g_pDirectDraw7 + 0x10))(g_pDirectDraw7,0,&piStack_c,0);
    if (-1 < iVar1) {
      (**(code **)(*piVar3 + 0x20))(piVar3,0,DAT_007935ec);
      piVar2 = g_pPrimarySurface;
      (**(code **)(*g_pPrimarySurface + 0x70))(g_pPrimarySurface,piVar3);
      (**(code **)(*piVar2 + 8))(piVar2);
    }
  }
  return;
}

