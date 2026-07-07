/* FUN_00406380 - 0x00406380 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00406380(undefined4 param_1,uint param_2,char param_3)

{
  uint uVar1;
  int in_EAX;
  int iVar2;
  int *piVar3;
  uint unaff_EDI;
  
  iVar2 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 <= param_2) {
    while (uVar1 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar1) {
        return;
      }
    }
    piVar3 = *(int **)(iVar2 + 0x10);
    uVar1 = piVar3[2];
    if (uVar1 <= unaff_EDI) {
      while (uVar1 != unaff_EDI) {
        piVar3 = (int *)piVar3[4];
        uVar1 = piVar3[2];
        if (unaff_EDI < uVar1) {
          return;
        }
      }
      *(undefined1 *)(piVar3 + 0x13) = 0;
      if (param_3 == '\0') {
        if (piVar3[9] != 3) {
          (**(code **)(*piVar3 + 4))(s_ready_00551e80);
          return;
        }
      }
      else if (piVar3[9] != 3) {
        (**(code **)(*piVar3 + 4))(s_active_00551e58);
        *(undefined1 *)(piVar3 + 0x13) = 1;
      }
    }
  }
  return;
}

