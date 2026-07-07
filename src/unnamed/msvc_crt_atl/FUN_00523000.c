/* FUN_00523000 - 0x00523000 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00523000(void)

{
  char cVar1;
  HANDLE hObject;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 *puStack_234;
  DWORD DStack_230;
  undefined4 local_220 [3];
  undefined1 auStack_214 [256];
  undefined1 auStack_114 [276];
  
  cVar1 = FUN_00522e40();
  if (cVar1 != '\0') {
    puVar4 = local_220;
    for (iVar3 = 0x88; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    DStack_230 = 0x523030;
    DStack_230 = GetCurrentProcessId();
    puStack_234 = (undefined1 *)0x8;
    hObject = (HANDLE)(*DAT_005b1580)();
    if (hObject != (HANDLE)0xffffffff) {
      puStack_234 = &stack0xfffffdd4;
      iVar3 = (*DAT_005b1584)(hObject);
      if (iVar3 != 0) {
        if (DAT_005b15ac == 0) goto LAB_005230c5;
        uVar2 = FUN_005218c0(&DAT_0056aa68);
        FUN_00521a90(DAT_005b15ac + 0x24,uVar2);
        do {
          if (DAT_005b15ac != 0) {
            uVar2 = FUN_005218c0(&DAT_0056aa48,auStack_214,local_220[0],local_220[1],auStack_114);
            FUN_00521a90(DAT_005b15ac + 0x24,uVar2);
          }
LAB_005230c5:
          iVar3 = (*DAT_005b1474)(hObject,&puStack_234);
        } while (iVar3 != 0);
      }
      CloseHandle(hObject);
    }
  }
  return;
}

