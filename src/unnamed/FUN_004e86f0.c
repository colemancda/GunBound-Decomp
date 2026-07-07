/* FUN_004e86f0 - 0x004e86f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004e86f0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int in_EAX;
  undefined4 *puVar2;
  ushort *unaff_EBX;
  bool bVar3;
  
  puVar1 = param_1;
  param_1 = *(undefined4 **)(in_EAX + 4);
  bVar3 = true;
  if (*(char *)((int)param_1[1] + 0xf) == '\0') {
    puVar2 = (undefined4 *)param_1[1];
    do {
      param_1 = puVar2;
      bVar3 = *unaff_EBX < *(ushort *)(param_1 + 3);
      if (bVar3) {
        puVar2 = (undefined4 *)*param_1;
      }
      else {
        puVar2 = (undefined4 *)param_1[2];
      }
    } while (*(char *)((int)puVar2 + 0xf) == '\0');
  }
  if (bVar3) {
    if (param_1 == (undefined4 *)**(int **)(in_EAX + 4)) {
      puVar2 = (undefined4 *)FUN_004e8b10(&param_1,1,unaff_EBX);
      *puVar1 = *puVar2;
      *(undefined1 *)(puVar1 + 1) = 1;
      return puVar1;
    }
    FUN_004e8eb0();
  }
  if (*(ushort *)(param_1 + 3) < *unaff_EBX) {
    puVar2 = (undefined4 *)FUN_004e8b10(&param_1,bVar3,unaff_EBX);
    *puVar1 = *puVar2;
    *(undefined1 *)(puVar1 + 1) = 1;
    return puVar1;
  }
  *puVar1 = param_1;
  *(undefined1 *)(puVar1 + 1) = 0;
  return puVar1;
}

