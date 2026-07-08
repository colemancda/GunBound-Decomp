/* FUN_0043c440 - 0x0043c440 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043c440(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int in_EAX;
  int *piVar4;
  uint uVar5;
  
  uVar5 = in_EAX * 8;
  iVar1 = uVar5 + 8;
joined_r0x0043c44c:
  if (iVar1 <= (int)uVar5) {
    return;
  }
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar3 = *(uint *)(iVar2 + 4);
  while (uVar3 < 0x186a4) {
    if (uVar3 == 0x186a3) {
      piVar4 = *(int **)(iVar2 + 0x10);
      uVar3 = piVar4[2];
      if (uVar3 <= uVar5) goto LAB_0043c485;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar3 = *(uint *)(iVar2 + 4);
  }
  goto LAB_0043c498;
  while( true ) {
    piVar4 = (int *)piVar4[4];
    uVar3 = piVar4[2];
    if (uVar5 < uVar3) break;
LAB_0043c485:
    if (uVar3 == uVar5) {
      (**(code **)(*piVar4 + 0x20))();
      break;
    }
  }
LAB_0043c498:
  uVar5 = uVar5 + 1;
  goto joined_r0x0043c44c;
}

