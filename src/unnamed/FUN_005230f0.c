/* FUN_005230f0 - 0x005230f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_005230f0(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  DWORD DVar3;
  undefined4 uVar4;
  char *_Format;
  int iVar5;
  int iVar6;
  int iVar7;
  char local_80 [128];
  
  if (DAT_005b15b5 != '\0') {
    return 1;
  }
  DAT_005b15b5 = '\x01';
  puVar1 = (undefined4 *)*param_1;
  if (DAT_005b15ac != (char *)0x0) {
    uVar4 = DAT_005b1590;
    DVar3 = GetCurrentThreadId();
    uVar4 = FUN_005218c0(&DAT_0056aac0,*puVar1,puVar1[3],DVar3,uVar4);
    FUN_00521a90(DAT_005b15ac + 0x24,uVar4);
  }
  iVar2 = puVar1[3];
  iVar7 = 0;
  iVar6 = 0;
  do {
    _Format = (char *)FUN_005218c0(&DAT_0056aab4,*(undefined1 *)(iVar6 + iVar2));
    iVar5 = _sprintf(local_80 + iVar7,_Format);
    iVar7 = iVar7 + iVar5;
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x20);
  local_80[iVar7] = '\0';
  if (DAT_005b15ac != (char *)0x0) {
    uVar4 = FUN_005218c0(&DAT_0056aaa0,local_80);
    FUN_00521a90(DAT_005b15ac + 0x24,uVar4);
  }
  FUN_00522f20();
  FUN_00523000();
  if ((DAT_005b15ac != (char *)0x0) && (*DAT_005b15ac == '\0')) {
    *(int *)(DAT_005b15ac + 0x10) = *(int *)(DAT_005b15ac + 0x10) + 10000;
    DAT_005b158c = 1;
    FUN_00522880();
                    /* WARNING: Subroutine does not return */
    ExitProcess(100);
  }
  return 0;
}

