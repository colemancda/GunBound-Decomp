/* FUN_00507310 - 0x00507310 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_00507310(int param_1,int param_2,int param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *(int *)(param_1 + 0x2c) + 0x25;
  if ((*(int *)(param_1 + 0x28) + 9 < param_2) && (param_2 < *(int *)(param_1 + 0x28) + 0xa5)) {
    iVar5 = 0;
    do {
      if ((iVar4 < param_3) && (param_3 < iVar4 + 0x19)) {
        iVar4 = *(int *)(DAT_005b3484 + 0x44248 +
                        (*(int *)(&DAT_005f2f3c + DAT_005b3484) + iVar5) * 4);
        puVar2 = DAT_00e53c44;
        if (iVar4 != -1) goto joined_r0x00507384;
        break;
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x1e;
    } while (iVar5 < 7);
  }
  goto LAB_00507427;
  while( true ) {
    piVar1 = puVar2 + 2;
    puVar2 = (undefined4 *)*puVar2;
    if ((*(int *)(*piVar1 + 0x20) == 0) && (*(int *)(*piVar1 + 0x24) == 10000)) break;
joined_r0x00507384:
    if (puVar2 == (undefined4 *)0x0) {
      iVar4 = __stricmp((char *)(iVar4 * 0xd + 0x41445 + DAT_005b3484),
                        (char *)(DAT_005b3484 + 0x23330));
      if (iVar4 != 0) {
        FUN_004025e0(&DAT_00e53e88,
                     *(int *)(DAT_005b3484 + 0x44248 +
                             (*(int *)(&DAT_005f2f3c + DAT_005b3484) + iVar5) * 4) * 0xd + 0x41445 +
                     DAT_005b3484);
      }
      goto LAB_00507427;
    }
  }
  iVar4 = FUN_0050e620();
  if (iVar4 != -1) {
    FUN_005056c0(*(int *)(DAT_005b3484 + 0x44248 +
                         (*(int *)(&DAT_005f2f3c + DAT_005b3484) + iVar5) * 4) * 0xd + 0x41445 +
                 DAT_005b3484);
  }
LAB_00507427:
  uVar3 = 0;
  if ((((*(char *)(param_1 + 0x1e) == '\0') && (*(int *)(param_1 + 0x28) < param_2)) &&
      (param_2 < *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28))) &&
     ((*(int *)(param_1 + 0x2c) < param_3 &&
      (param_3 < *(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c))))) {
    uVar3 = 1;
  }
  return uVar3;
}

