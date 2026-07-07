/* FUN_004e9070 - 0x004e9070 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004e9070(void)

{
  void *pvVar1;
  uint uVar2;
  undefined2 *puVar3;
  int iVar4;
  int unaff_ESI;
  int *piVar5;
  int local_4;
  
  *(undefined4 *)(unaff_ESI + 0x1000) = 0;
  local_4 = 0;
  if (0 < *(int *)(unaff_ESI + 0x1008)) {
    piVar5 = (int *)(unaff_ESI + 0x100c);
    do {
      uVar2 = *(uint *)(unaff_ESI + 0x1000);
      iVar4 = (int)(uVar2 + ((int)uVar2 >> 0x1f & 0x3ffU)) >> 10;
      uVar2 = uVar2 & 0x800003ff;
      if ((int)uVar2 < 0) {
        uVar2 = (uVar2 - 1 | 0xfffffc00) + 1;
      }
      if (*(int *)(unaff_ESI + iVar4 * 4) == 0) {
        pvVar1 = operator_new(0x4000);
        *(void **)(unaff_ESI + iVar4 * 4) = pvVar1;
      }
      *(int *)(unaff_ESI + 0x1000) = *(int *)(unaff_ESI + 0x1000) + 1;
      puVar3 = (undefined2 *)(uVar2 * 0x10 + *(int *)(unaff_ESI + iVar4 * 4));
      *piVar5 = (int)puVar3;
      *puVar3 = 0;
      *(undefined2 *)(*piVar5 + 2) = *(undefined2 *)(unaff_ESI + 0x1004);
      *(undefined1 *)(*piVar5 + 4) = 0;
      *(undefined4 *)(*piVar5 + 8) = 0;
      *(undefined4 *)(*piVar5 + 0xc) = 0;
      local_4 = local_4 + 1;
      piVar5 = piVar5 + 1;
    } while (local_4 < *(int *)(unaff_ESI + 0x1008));
  }
  return;
}

