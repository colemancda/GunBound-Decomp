/* FUN_0040b540 - 0x0040b540 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


undefined4 * FUN_0040b540(undefined4 *param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  int in_EAX;
  undefined4 *puVar3;
  int *unaff_EBX;
  
  puVar2 = param_1;
  param_1 = *(undefined4 **)(in_EAX + 4);
  bVar1 = true;
  if (*(char *)((int)param_1[1] + 0x11) == '\0') {
    puVar3 = (undefined4 *)param_1[1];
    do {
      param_1 = puVar3;
      bVar1 = *unaff_EBX < (int)param_1[3];
      if (bVar1) {
        puVar3 = (undefined4 *)*param_1;
      }
      else {
        puVar3 = (undefined4 *)param_1[2];
      }
    } while (*(char *)((int)puVar3 + 0x11) == '\0');
  }
  if (bVar1) {
    if (param_1 == (undefined4 *)**(int **)(in_EAX + 4)) {
      puVar3 = (undefined4 *)FUN_0040bae0(&param_1,1,unaff_EBX);
      *puVar2 = *puVar3;
      *(undefined1 *)(puVar2 + 1) = 1;
      return puVar2;
    }
    FUN_0040c150();
  }
  if ((int)param_1[3] < *unaff_EBX) {
    puVar3 = (undefined4 *)FUN_0040bae0(&param_1,bVar1,unaff_EBX);
    *puVar2 = *puVar3;
    *(undefined1 *)(puVar2 + 1) = 1;
    return puVar2;
  }
  *puVar2 = param_1;
  *(undefined1 *)(puVar2 + 1) = 0;
  return puVar2;
}

