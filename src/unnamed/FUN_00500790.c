/* FUN_00500790 - 0x00500790 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00500790(void)

{
  int iVar1;
  int *piVar2;
  int *in_EAX;
  undefined4 uVar3;
  int *_Memory;
  uint uVar4;
  undefined4 uVar5;
  
  in_EAX[8] = in_EAX[8] + 1;
  if ((*in_EAX != 0) && (uVar4 = 0, in_EAX[2] != 0)) {
    do {
      iVar1 = *(int *)(*in_EAX + uVar4 * 4);
      while (iVar1 != 0) {
        iVar1 = *(int *)(iVar1 + 0x1760);
        FUN_005011c0();
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)in_EAX[2]);
  }
  _free((void *)*in_EAX);
  *in_EAX = 0;
  in_EAX[1] = 0;
  if (in_EAX[8] == 0) {
    uVar5 = 0;
    uVar3 = FUN_00500e30(0);
    FUN_00500c00(in_EAX,uVar3,uVar5);
  }
  _Memory = (int *)in_EAX[10];
  in_EAX[0xb] = 0;
  if (_Memory != (int *)0x0) {
    do {
      piVar2 = (int *)*_Memory;
      _free(_Memory);
      _Memory = piVar2;
    } while (piVar2 != (int *)0x0);
    in_EAX[10] = 0;
  }
  in_EAX[8] = in_EAX[8] + -1;
  return;
}

