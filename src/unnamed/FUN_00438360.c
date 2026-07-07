/* FUN_00438360 - 0x00438360 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00438360(void)

{
  uint uVar1;
  char cVar2;
  void *pvVar3;
  int iVar4;
  undefined4 *puVar5;
  int unaff_ESI;
  bool bVar6;
  
  cVar2 = FUN_004065a0();
  if (cVar2 != '\0') {
    return;
  }
  iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  while (uVar1 < 0x2e636) {
    if (uVar1 == 0x2e635) {
      puVar5 = *(undefined4 **)(iVar4 + 0x10);
      bVar6 = true;
      if (puVar5[2] == 0) goto LAB_004383a5;
      break;
    }
    iVar4 = *(int *)(iVar4 + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
  }
  goto LAB_004383df;
  while( true ) {
    puVar5 = (undefined4 *)puVar5[4];
    bVar6 = puVar5[2] == 0;
    if (!bVar6) break;
LAB_004383a5:
    if (bVar6) {
      if (((puVar5[0x11] == 0) && (unaff_ESI != 0)) && (unaff_ESI < 5)) {
        puVar5[0x11] = unaff_ESI;
        return;
      }
      *(undefined4 *)(puVar5[3] + 0x10) = puVar5[4];
      *(undefined4 *)(puVar5[4] + 0xc) = puVar5[3];
      (**(code **)*puVar5)(1);
      break;
    }
  }
LAB_004383df:
  pvVar3 = operator_new(0x58);
  if (pvVar3 == (void *)0x0) {
    iVar4 = 0;
  }
  else {
    iVar4 = FUN_004b3b10();
  }
  *(int *)(iVar4 + 0x44) = unaff_ESI;
  RegisterActiveObject();
  return;
}

