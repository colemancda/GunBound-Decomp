/* FUN_00522270 - 0x00522270 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00522270(int param_1)

{
  DWORD DVar1;
  int iVar2;
  undefined4 uVar3;
  
LAB_0052227c:
  while( true ) {
    while( true ) {
      DVar1 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x14),0xde3);
      if (DVar1 != 0) break;
      if (*(char *)(param_1 + 0x18) == '\0') {
        return 0;
      }
      FUN_00522570(0x62d,0);
    }
    iVar2 = FUN_00523460();
    if (iVar2 != 0) break;
    FUN_00522570(0x62d,10);
  }
  if (*(code **)(param_1 + 0x1c) == (code *)0x0) goto LAB_005222c8;
  iVar2 = (**(code **)(param_1 + 0x1c))();
  if (iVar2 == 0) goto LAB_005222c8;
  goto LAB_005222cf;
LAB_005222c8:
  if (*(char *)(param_1 + 0x20) != '\0') {
LAB_005222cf:
    if (DAT_005b15ac != 0) {
      if (*(code **)(param_1 + 0x1c) == (code *)0x0) {
        uVar3 = 0;
      }
      else {
        uVar3 = (**(code **)(param_1 + 0x1c))();
      }
      uVar3 = FUN_005218c0(&DAT_0056a5f8,uVar3,*(undefined1 *)(param_1 + 0x20));
      FUN_00521a90(DAT_005b15ac + 0x24,uVar3);
    }
    FUN_00522570(500,0);
  }
  goto LAB_0052227c;
}

