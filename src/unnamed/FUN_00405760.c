/* FUN_00405760 - 0x00405760 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00405760(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *unaff_ESI;
  
  iVar4 = *unaff_ESI;
  puVar1 = (undefined4 *)(iVar4 + -0x10);
  piVar3 = (int *)*puVar1;
  if (*(int *)(iVar4 + -0xc) != 0) {
    piVar2 = (int *)(iVar4 + -4);
    if (*(int *)(iVar4 + -4) < 0) {
      if (*(int *)(iVar4 + -8) < 0) {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      *(undefined4 *)(iVar4 + -0xc) = 0;
      *(undefined1 *)*unaff_ESI = 0;
      return;
    }
    LOCK();
    iVar4 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar4 == 1 || iVar4 + -1 < 0) {
      (**(code **)(*(int *)*puVar1 + 4))(puVar1);
    }
    (**(code **)(*piVar3 + 0xc))();
    *unaff_ESI = iVar4 + 0x10;
  }
  return;
}

