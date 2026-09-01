/* FUN_00405290 - 0x00405290 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00405290(int regEax,int regEsi)

{
  int *piVar1;
  undefined4 uVar2;
  int *_Memory;
  uint uVar3;
  
  thunk_FUN_00405320();
  *(undefined4 *)(regEax + 0x24) = *(undefined4 *)(regEsi + 0x2c);
  uVar3 = *(int *)(regEsi + 4) - 1;
  *(int *)(regEsi + 0x2c) = regEax;
  *(uint *)(regEsi + 4) = uVar3;
  if ((uVar3 < *(uint *)(regEsi + 0x1c)) && (*(int *)(regEsi + 0x20) == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00405150(regEsi,uVar2);
  }
  if (*(int *)(regEsi + 4) == 0) {
    _Memory = *(int **)(regEsi + 0x28);
    *(undefined4 *)(regEsi + 0x2c) = 0;
    if (_Memory != (int *)0x0) {
      do {
        piVar1 = (int *)*_Memory;
        _free(_Memory);
        _Memory = piVar1;
      } while (piVar1 != (int *)0x0);
      *(undefined4 *)(regEsi + 0x28) = 0;
    }
  }
  return;
}

