/* FUN_004e1bf0 - 0x004e1bf0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004e1c9a) */
/* WARNING: Removing unreachable block (ram,0x004e1ca4) */
/* WARNING: Removing unreachable block (ram,0x004e1c82) */
/* WARNING: Removing unreachable block (ram,0x004e1c8c) */
/* WARNING: Removing unreachable block (ram,0x004e1cc3) */
/* WARNING: Removing unreachable block (ram,0x004e1ccd) */

void FUN_004e1bf0(int param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int unaff_EDI;
  char local_80 [128];
  
  if ((unaff_EDI < 0x10) && (-2 < unaff_EDI)) {
    if (*(int *)(param_1 + 0x28 + unaff_EDI * 4) != 0) {
      FUN_004124a0(0);
      return;
    }
    _sprintf(local_80,s__d__d__d__d_00557138,(uint)*(byte *)(DAT_005b3484 + 0x4104a + unaff_EDI * 4)
             ,(uint)*(byte *)(DAT_005b3484 + 0x4104b + unaff_EDI * 4),
             (uint)*(byte *)(DAT_005b3484 + 0x4104c + unaff_EDI * 4),
             (uint)*(byte *)(DAT_005b3484 + 0x4104d + unaff_EDI * 4));
    DAT_0056d118 = 0;
    if ((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
       (piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar1[2] == 0)) {
      (**(code **)(*piVar1 + 4))(s_disable_00551e68);
    }
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
      piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
      uVar2 = piVar1[2];
      while (uVar2 < 2) {
        if (uVar2 == 1) {
          (**(code **)(*piVar1 + 4))(s_disable_00551e68);
          break;
        }
        piVar1 = (int *)piVar1[4];
        uVar2 = piVar1[2];
      }
    }
    FUN_00406300(0);
    iVar4 = DAT_007934ec;
    iVar3 = DAT_005b3484;
    *(undefined1 *)(param_1 + 0x24) = 0;
    *(undefined1 *)(iVar4 + 0x84e6) = 0;
    FUN_004d2480(local_80,*(undefined2 *)(iVar3 + 0x4108a + unaff_EDI * 2));
    *(undefined1 *)(param_1 + 4) = 1;
    *(int *)(param_1 + 0x68) = unaff_EDI;
  }
  return;
}

