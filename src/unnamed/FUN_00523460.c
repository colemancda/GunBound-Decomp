/* FUN_00523460 - 0x00523460 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 FUN_00523460(void)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_005b15d0 == '\0') {
    return 2;
  }
  iVar2 = 0;
  if (DAT_005b15c8 != QueryPerformanceCounter_exref) {
    if (DAT_005b15ac != 0) {
      uVar1 = FUN_005218c0(&DAT_0056ac1c,QueryPerformanceCounter_exref);
      FUN_00521a90(DAT_005b15ac + 0x24,uVar1);
    }
    iVar2 = 1;
  }
  if (DAT_005b15c4 != GetTickCount_exref) {
    if (DAT_005b15ac != 0) {
      uVar1 = FUN_005218c0(&DAT_0056ac08,GetTickCount_exref);
      FUN_00521a90(DAT_005b15ac + 0x24,uVar1);
    }
    iVar2 = iVar2 + 1;
  }
  if (DAT_005b15cc != timeGetTime_exref) {
    if (DAT_005b15ac != 0) {
      uVar1 = FUN_005218c0(&DAT_0056abf4,timeGetTime_exref);
      FUN_00521a90(DAT_005b15ac + 0x24,uVar1);
    }
    iVar2 = iVar2 + 1;
  }
  return iVar2 == 0;
}

