/* FUN_00403170 - 0x00403170 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00403170(int param_1,uchar *param_2)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  uint local_208 [64];
  uint local_108 [65];
  
  local_208[0] = 0xffffffff;
  puVar1 = (uint *)FUN_00404b00(param_2);
  if (puVar1 != (uint *)0x0) {
    do {
      do {
        puVar2 = (uint *)FUN_004050a0(param_1 + 0x1be4);
        if ((puVar2 == (uint *)0x0) || (iVar3 = __mbsicmp((uchar *)*puVar2,param_2), iVar3 != 0)) {
          puVar2 = (uint *)0x0;
        }
        puVar4 = local_108;
        for (iVar3 = 0x40; puVar1 = puVar1 + 1, iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = *puVar1;
          puVar4 = puVar4 + 1;
        }
        if (local_108[0] < local_208[0]) {
          puVar1 = local_108;
          puVar4 = local_208;
          for (iVar3 = 0x40; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar4 = *puVar1;
            puVar1 = puVar1 + 1;
            puVar4 = puVar4 + 1;
          }
        }
        puVar1 = puVar2;
      } while (puVar2 != (uint *)0x0);
      FUN_004032c0(param_1,param_2 + 1);
      FUN_004048e0();
      local_208[0] = 0xffffffff;
      puVar1 = (uint *)FUN_00404b00(param_2);
    } while (puVar1 != (uint *)0x0);
  }
  return;
}

