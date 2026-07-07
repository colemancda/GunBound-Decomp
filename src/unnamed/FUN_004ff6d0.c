/* FUN_004ff6d0 - 0x004ff6d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ff6d0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *unaff_ESI;
  
  iVar1 = unaff_ESI[2];
  while (iVar1 != 0) {
    puVar2 = (undefined4 *)*unaff_ESI;
    *unaff_ESI = *puVar2;
    FUN_005006c0(puVar2);
    iVar1 = unaff_ESI[2];
  }
  *unaff_ESI = 0;
  unaff_ESI[1] = 0;
  unaff_ESI[4] = 0;
  puVar2 = (undefined4 *)unaff_ESI[3];
  while (puVar2 != (undefined4 *)0x0) {
    puVar3 = (undefined4 *)*puVar2;
    _free(puVar2);
    puVar2 = puVar3;
  }
  unaff_ESI[3] = 0;
  return;
}

