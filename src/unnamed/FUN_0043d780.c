/* FUN_0043d780 - 0x0043d780 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0043d780(byte *param_1,int regEax)

{
  byte *pbVar1;
  undefined4 *puVar2;
  byte bVar3;
  undefined2 uVar4;
  uint uVar5;
  char cVar6;
  byte *pbVar7;
  int local_10;
  undefined4 local_8;
  
  bVar3 = *param_1;
  pbVar7 = param_1 + 1;
  if (*(void **)(regEax + 8) != (void *)0x0) {
    _free(*(void **)(regEax + 8));
    *(int *)(regEax + 8) = 0;
  }
  *(undefined4 *)(regEax + 0xc) = 0;
  *(undefined4 *)(regEax + 0x10) = 0;
  local_10 = 0;
  if (bVar3 != 0) {
    do {
      pbVar1 = pbVar7 + 1;
      uVar5 = *(uint *)(regEax + 0xc);
      uVar4 = *(undefined2 *)(pbVar7 + 3);
      local_8 = *pbVar7;
      pbVar7 = pbVar7 + 5;
      local_8 = CONCAT22(*(undefined2 *)pbVar1,(undefined2)local_8);
      if ((*(uint *)(regEax + 0x10) <= uVar5) && (cVar6 = GrowChecksumStateArray(uVar5 + 1,(int *)(regEax + 8)), cVar6 == '\0')) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
      puVar2 = (undefined4 *)(*(int *)(regEax + 8) + uVar5 * 6);
      if (puVar2 != (undefined4 *)0x0) {
        *puVar2 = local_8;
        *(undefined2 *)(puVar2 + 1) = uVar4;
      }
      local_10 = local_10 + 1;
      *(int *)(regEax + 0xc) = *(int *)(regEax + 0xc) + 1;
    } while (local_10 < (int)(uint)bVar3);
  }
  return (int)pbVar7 - (int)param_1;
}

