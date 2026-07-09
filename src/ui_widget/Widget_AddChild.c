/* Widget_AddChild - 0x0050e670 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void Widget_AddChild(int param_1)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  int unaff_EBX;
  
  uVar2 = *(uint *)(unaff_EBX + 0x10);
  if (*(uint *)(unaff_EBX + 0x14) <= uVar2) {
    cVar3 = FUN_0050ed30();
    if (cVar3 == '\0') {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x8007000e);
    }
  }
  piVar1 = (int *)(*(int *)(unaff_EBX + 0xc) + uVar2 * 4);
  if (piVar1 != (int *)0x0) {
    *piVar1 = param_1;
  }
  *(int *)(unaff_EBX + 0x10) = *(int *)(unaff_EBX + 0x10) + 1;
  Widget_MoveBy(*(undefined4 *)(unaff_EBX + 0x28),*(undefined4 *)(unaff_EBX + 0x2c));
  *(int *)(param_1 + 8) = unaff_EBX;
  return;
}

