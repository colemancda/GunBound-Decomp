/* FUN_00520700 - 0x00520700 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_00520700(char *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*param_1 == '\0') {
    uVar2 = FUN_005218c0(&DAT_00569e68,*(undefined4 *)(param_1 + 0x10));
    FUN_00521a90(param_1 + 0x24,uVar2);
    return *(undefined4 *)(param_1 + 0x10);
  }
  FUN_00522f20();
  FUN_00523000();
  *(undefined4 *)(param_1 + 4) = param_2;
  if (*(int *)(param_1 + 8) != 0) {
    uVar2 = FUN_005218c0(&DAT_00569e48,*(int *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
    FUN_00521a90(param_1 + 0x24,uVar2);
    cVar1 = FUN_004152d0(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
    if (cVar1 == '\0') {
      uVar2 = FUN_005218c0(&DAT_00569e2c);
      FUN_00521a90(param_1 + 0x24,uVar2);
      return 200;
    }
  }
  FUN_005240c0(0x8b1,0x612,*(undefined4 *)(param_1 + 4));
  uVar2 = FUN_005218c0(&DAT_00569e10);
  FUN_00521a90(param_1 + 0x24,uVar2);
  return *(undefined4 *)(param_1 + 0x10);
}

