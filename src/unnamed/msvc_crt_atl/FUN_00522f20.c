/* FUN_00522f20 - 0x00522f20 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00522f20(void)

{
  char cVar1;
  HANDLE hObject;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 *puStack_138;
  undefined4 uStack_134;
  undefined4 local_124 [4];
  undefined1 auStack_114 [276];
  
  cVar1 = FUN_00522e40();
  if (cVar1 != '\0') {
    uStack_134 = 0;
    puVar4 = local_124;
    for (iVar3 = 0x49; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    puStack_138 = (undefined1 *)0x2;
    hObject = (HANDLE)(*DAT_005b1580)();
    if (hObject != (HANDLE)0xffffffff) {
      puStack_138 = &stack0xfffffed0;
      iVar3 = (*DAT_005b1470)(hObject);
      if (iVar3 != 0) {
        if (DAT_005b15ac == 0) goto LAB_00522fdc;
        uVar2 = FUN_005218c0(&DAT_0056aa14);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar2);
        do {
          if (DAT_005b15ac != 0) {
            uVar2 = FUN_005218c0(&DAT_0056a9f0,auStack_114,0x128,local_124[0],local_124[2]);
            FUN_00521a90(DAT_005b15ac + 0x24,uVar2);
          }
LAB_00522fdc:
          iVar3 = (*DAT_005b1588)(hObject,&puStack_138);
        } while (iVar3 != 0);
      }
      CloseHandle(hObject);
    }
  }
  return;
}

