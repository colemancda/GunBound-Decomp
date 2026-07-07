/* FUN_004f46b0 - 0x004f46b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f46b0(void)

{
  void *_Memory;
  void *pvVar1;
  int *piVar2;
  void *pvVar3;
  int iVar4;
  int unaff_EBX;
  undefined4 *puVar5;
  
  _Memory = *(void **)(unaff_EBX + 0x114);
  pvVar3 = *(void **)(unaff_EBX + 0x1b4);
  while (pvVar3 != (void *)0x0) {
    pvVar1 = *(void **)((int)pvVar3 + 0x98);
    _free(pvVar3);
    pvVar3 = pvVar1;
  }
  while (_Memory != (void *)0x0) {
    piVar2 = *(int **)((int)_Memory + 0x110);
    pvVar3 = *(void **)((int)_Memory + 0x114);
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 8))(piVar2);
    }
    *(undefined4 *)((int)_Memory + 0x110) = 0;
    _free(_Memory);
    _Memory = pvVar3;
  }
  *(undefined4 *)(unaff_EBX + 0x114) = 0;
  *(undefined4 *)(unaff_EBX + 0x118) = 0;
  *(undefined4 *)(unaff_EBX + 0x1b4) = 0;
  puVar5 = (undefined4 *)(unaff_EBX + 0x401bc);
  for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *(undefined4 *)(unaff_EBX + 0x401b8) = 0;
  return;
}

