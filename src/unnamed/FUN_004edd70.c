/* FUN_004edd70 - 0x004edd70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004edd70(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uStack_38;
  int *piStack_34;
  undefined *puStack_30;
  int *piStack_2c;
  int iStack_28;
  int *piStack_24;
  undefined4 uStack_20;
  undefined4 uStack_14;
  
  uStack_20 = 0;
  piVar1 = (int *)(param_1 + 4);
  iStack_28 = param_1 + 8;
  piStack_2c = DAT_00674f68;
  puStack_30 = (undefined *)0x4edd8c;
  piStack_24 = piVar1;
  iVar2 = (**(int (**)())(*DAT_00674f68 + 0xc))();
  if (-1 < iVar2) {
    piStack_34 = (int *)*piVar1;
    puStack_30 = &DAT_0054b420;
    uStack_38 = 0x4edd9d;
    iVar2 = (**(int (**)())(*piStack_34 + 0x2c))();
    if (-1 < iVar2) {
      uStack_38 = 6;
      iVar2 = (**(int (**)())(*(int *)*piVar1 + 0x34))((int *)*piVar1,uStack_14);
      if (-1 < iVar2) {
        uStack_38 = 0x14;
        piStack_34 = (int *)0x10;
        puStack_30 = (undefined *)0x0;
        piStack_2c = (int *)0x0;
        iStack_28 = 0x40;
        iVar2 = (**(int (**)())(*(int *)*piVar1 + 0x18))((int *)*piVar1,1,&uStack_38);
        if (-1 < iVar2) {
          piVar1 = (int *)*piVar1;
          if (piVar1 != (int *)0x0) {
            (**(int (**)())(*piVar1 + 0x1c))(piVar1);
          }
          *(undefined1 *)(param_1 + 0x54) = 1;
          return 1;
        }
      }
    }
  }
  return 0;
}

