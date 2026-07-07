/* FUN_004eb940 - 0x004eb940 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004eb940(int param_1,undefined4 *param_2,int param_3)

{
  int in_EAX;
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  if ((((DAT_00793534 <= param_3) && (param_3 <= DAT_0056df34)) &&
      (DAT_00793530 <= in_EAX + param_1)) && (in_EAX <= DAT_0056df30)) {
    if (in_EAX < DAT_00793530) {
      param_2 = (undefined4 *)((int)param_2 + (DAT_00793530 - in_EAX) * 2);
      param_1 = param_1 + (in_EAX - DAT_00793530);
      in_EAX = DAT_00793530;
    }
    if (DAT_0056df30 < in_EAX + param_1) {
      param_1 = (DAT_0056df30 - in_EAX) + 1;
    }
    uVar1 = param_1 * 2 & (param_1 * 2 < 0) - 1;
    puVar3 = (undefined4 *)(DAT_0079352c + (DAT_005b3620 * param_3 + in_EAX) * 2);
    for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar3 = *param_2;
      param_2 = param_2 + 1;
      puVar3 = puVar3 + 1;
    }
    for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined1 *)puVar3 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    }
  }
  return;
}

