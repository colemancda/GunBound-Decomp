/* FUN_00409f60 - 0x00409f60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * BOTH REGISTERS RECOVERED (2026-08-24, workflow-analysed, hand-checked).
 * regEsi is the hash table (the caller's own in_EAX: +0x20 lock count, +8
 * bucket count, +0x28 chunk list, +0x2c free head -- the same fields this
 * function touches); regEax is the chain NODE being released onto the free
 * list (*(regEsi+0x2c) = regEax; *(regEax+8) = old head).  At the sole call
 * site the caller advances iVar1 = *(iVar1+8) BEFORE calling with the
 * previous node in EAX (`mov eax,edi / mov edi,[edi+8] / call`), so the
 * source hoists the node into `node` before the advance -- the order
 * matters, because this function overwrites node+8.
 */
#include "ghidra_types.h"


void FUN_00409f60(int regEax,int regEsi)

{
  int *piVar1;
  undefined4 uVar2;
  int *_Memory;
  uint uVar3;
  thunk_FUN_00405320();
  *(undefined4 *)(regEax + 8) = *(undefined4 *)(regEsi + 0x2c);
  uVar3 = *(int *)(regEsi + 4) - 1;
  *(int *)(regEsi + 0x2c) = regEax;
  *(uint *)(regEsi + 4) = uVar3;
  if ((uVar3 < *(uint *)(regEsi + 0x1c)) && (*(int *)(regEsi + 0x20) == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00409e20(regEsi,uVar2);
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

