/* FUN_00500790 - 0x00500790 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25): the map at +0x50 of the enclosing 0x90-byte
 * object -- `lea eax,[esi+0x50]` at 0x4ff226 and `lea eax,[esp+0x7c]`
 * (frame -0x4c = -0x9c + 0x50) at 0x4fe97f.  The two sites agree on the
 * offset from two different directions, which is what fixes the layout.
 */
#include "ghidra_types.h"


void FUN_00500790(int *regEax)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int *_Memory;
  uint uVar4;
  undefined4 uVar5;
  
  regEax[8] = regEax[8] + 1;
  if ((*regEax != 0) && (uVar4 = 0, regEax[2] != 0)) {
    do {
      iVar1 = *(int *)(*regEax + uVar4 * 4);
      while (iVar1 != 0) {
        iVar1 = *(int *)(iVar1 + 0x1760);
        FUN_005011c0();
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)regEax[2]);
  }
  _free((void *)*regEax);
  *regEax = 0;
  regEax[1] = 0;
  if (regEax[8] == 0) {
    uVar5 = 0;
    uVar3 = FUN_00500e30(0);
    HashMap_InitHashTable(regEax,uVar3,uVar5);
  }
  _Memory = (int *)regEax[10];
  regEax[0xb] = 0;
  if (_Memory != (int *)0x0) {
    do {
      piVar2 = (int *)*_Memory;
      _free(_Memory);
      _Memory = piVar2;
    } while (piVar2 != (int *)0x0);
    regEax[10] = 0;
  }
  regEax[8] = regEax[8] + -1;
  return;
}

