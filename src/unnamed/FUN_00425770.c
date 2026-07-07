/* FUN_00425770 - 0x00425770 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00425770(void)

{
  int iVar1;
  DWORD DVar2;
  uint *puVar3;
  int iVar4;
  int unaff_ESI;
  
  puVar3 = (uint *)(&DAT_0067e348 + unaff_ESI);
  DVar2 = GetTickCount();
  if ((*puVar3 <= DVar2) && (iVar1 = *(int *)(&DAT_0067e3c8 + unaff_ESI), iVar1 != 0)) {
    iVar4 = 0;
    if (iVar1 != 1 && -1 < iVar1 + -1) {
      do {
        *puVar3 = puVar3[1];
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 1;
      } while (iVar4 < *(int *)(&DAT_0067e3c8 + unaff_ESI) + -1);
    }
    *(int *)(&DAT_0067e3c8 + unaff_ESI) = *(int *)(&DAT_0067e3c8 + unaff_ESI) + -1;
  }
  return;
}

