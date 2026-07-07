/* FUN_005011c0 - 0x005011c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_005011c0(void)

{
  int *piVar1;
  int in_EAX;
  undefined4 uVar2;
  int *_Memory;
  uint uVar3;
  int unaff_ESI;
  
  *(undefined4 *)(in_EAX + 0x1760) = *(undefined4 *)(unaff_ESI + 0x2c);
  uVar3 = *(int *)(unaff_ESI + 4) - 1;
  *(int *)(unaff_ESI + 0x2c) = in_EAX;
  *(uint *)(unaff_ESI + 4) = uVar3;
  if ((uVar3 < *(uint *)(unaff_ESI + 0x1c)) && (*(int *)(unaff_ESI + 0x20) == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00501070(unaff_ESI,uVar2);
  }
  if (*(int *)(unaff_ESI + 4) == 0) {
    _Memory = *(int **)(unaff_ESI + 0x28);
    *(undefined4 *)(unaff_ESI + 0x2c) = 0;
    if (_Memory != (int *)0x0) {
      do {
        piVar1 = (int *)*_Memory;
        _free(_Memory);
        _Memory = piVar1;
      } while (piVar1 != (int *)0x0);
      *(undefined4 *)(unaff_ESI + 0x28) = 0;
    }
  }
  return;
}

