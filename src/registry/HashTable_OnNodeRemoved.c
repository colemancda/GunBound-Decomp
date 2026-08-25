/* HashTable_OnNodeRemoved - 0x00409f60 in the original binary.
 *
 * Bookkeeping after a node is unlinked from the hash table regEsi (bucket
 * count at +8, live count at +4, shrink threshold at +0x1c, lock count at
 * +0x20, chunk list at +0x28, free head at +0x2c): pushes the node regEax
 * onto the free list, shrinks the bucket array when the live count drops
 * below the threshold and nothing holds the table locked, and frees every
 * chunk once the table is empty.  FUN_00415600 drives it once per node while
 * emptying the table -- which is why that caller captures the node before
 * advancing: this function overwrites node+8.
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


void HashTable_OnNodeRemoved(int regEax,int regEsi)

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

