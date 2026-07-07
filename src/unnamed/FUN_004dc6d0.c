/* FUN_004dc6d0 - 0x004dc6d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004dc6d0(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  char local_180 [127];
  undefined4 uStack_101;
  undefined1 local_fc [123];
  undefined4 uStack_81;
  
  _sprintf(local_180,s_tank_d_00553fa0,param_1 + 1);
  AppendPersistentButtonName(&DAT_0067ec70 + DAT_005b3484);
  iVar5 = FindPreloadedTextureByName(local_180);
  if (iVar5 != 0) {
    iVar6 = 0;
    do {
      cVar1 = local_180[iVar6];
      *(char *)((int)&uStack_101 + iVar6 + 1) = cVar1;
      iVar6 = iVar6 + 1;
    } while (cVar1 != '\0');
    puVar4 = &uStack_101;
    do {
      puVar7 = puVar4;
      puVar4 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined4 *)((int)puVar7 + 1) = DAT_005554f8;
    *(undefined1 *)((int)puVar7 + 5) = DAT_005554fc;
    iVar6 = 0;
    do {
      cVar1 = local_180[iVar6];
      *(char *)((int)&uStack_81 + iVar6 + 1) = cVar1;
      iVar6 = iVar6 + 1;
    } while (cVar1 != '\0');
    puVar4 = &uStack_81;
    do {
      puVar7 = puVar4;
      puVar4 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    piVar2 = *(int **)(iVar5 + 0x10);
    *(undefined4 *)((int)puVar7 + 1) = DAT_00556ae0;
    iVar3 = *piVar2;
    *(undefined2 *)((int)puVar7 + 5) = DAT_00556ae4;
    iVar6 = iVar3 + **(int **)(iVar5 + 0xc) * 4;
    FUN_004dfdb0(iVar3,iVar6,iVar6 - iVar3 >> 2);
    FUN_004f1a50(&DAT_00ea0e18,param_1 + 5000,**(undefined4 **)(iVar5 + 0x10),
                 **(undefined4 **)(iVar5 + 0xc));
    FUN_004f1a50(&DAT_00ea0e18,param_1 + 0x13ec,**(undefined4 **)(iVar5 + 0x10),
                 **(undefined4 **)(iVar5 + 0xc));
  }
  return;
}

