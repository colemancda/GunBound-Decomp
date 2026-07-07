/* FUN_00500a20 - 0x00500a20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00500aa3) */

void FUN_00500a20(void)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  undefined4 uVar9;
  int *unaff_ESI;
  undefined4 uVar10;
  uint local_8;
  
  unaff_ESI[8] = unaff_ESI[8] + 1;
  if ((*unaff_ESI != 0) && (local_8 = 0, unaff_ESI[2] != 0)) {
    do {
      iVar6 = *(int *)(*unaff_ESI + local_8 * 4);
      while (iVar6 != 0) {
        iVar2 = *(int *)(iVar6 + 0xc);
        *(int *)(iVar6 + 0xc) = unaff_ESI[0xb];
        iVar3 = unaff_ESI[1];
        unaff_ESI[0xb] = iVar6;
        unaff_ESI[1] = iVar3 - 1U;
        if ((iVar3 - 1U < (uint)unaff_ESI[7]) && (unaff_ESI[8] == 0)) {
          uVar5 = FUN_0053753c();
          iVar6 = 0;
          if (0x11 < uVar5) {
            do {
              puVar1 = &DAT_00557664 + iVar6;
              iVar6 = iVar6 + 1;
            } while (*puVar1 < uVar5);
          }
          uVar7 = (&DAT_00557660)[iVar6];
          if ((&DAT_00557660)[iVar6] == 0xffffffff) {
            uVar7 = uVar5;
          }
          FUN_00501220(unaff_ESI,uVar7);
        }
        iVar6 = iVar2;
        if (unaff_ESI[1] == 0) {
          unaff_ESI[0xb] = 0;
          piVar8 = (int *)unaff_ESI[10];
          if ((int *)unaff_ESI[10] != (int *)0x0) {
            do {
              piVar4 = (int *)*piVar8;
              _free(piVar8);
              piVar8 = piVar4;
            } while (piVar4 != (int *)0x0);
            unaff_ESI[10] = 0;
          }
        }
      }
      local_8 = local_8 + 1;
    } while (local_8 < (uint)unaff_ESI[2]);
  }
  _free((void *)*unaff_ESI);
  *unaff_ESI = 0;
  unaff_ESI[1] = 0;
  if (unaff_ESI[8] == 0) {
    uVar10 = 0;
    uVar9 = FUN_00500e30(0);
    FUN_00500c00(unaff_ESI,uVar9,uVar10);
  }
  unaff_ESI[0xb] = 0;
  piVar8 = (int *)unaff_ESI[10];
  if ((int *)unaff_ESI[10] != (int *)0x0) {
    do {
      piVar4 = (int *)*piVar8;
      _free(piVar8);
      piVar8 = piVar4;
    } while (piVar4 != (int *)0x0);
    unaff_ESI[10] = 0;
  }
  unaff_ESI[8] = unaff_ESI[8] + -1;
  return;
}

