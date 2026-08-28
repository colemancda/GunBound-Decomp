/* CommConnectionList_Erase - 0x004ff720 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the erase member of the comm engine's intrusive
 * doubly-linked connection list (the RAW list at engine+4 = owner+8,
 * per commit 1b842e4c's three agreeing witnesses, restated below).
 * Unlink, destroy the node's payload, recycle the node onto the
 * free list at +0x10, decrement the live count, full teardown via
 * FUN_004ff6d0 when it reaches zero - erase-with-node-recycling.
 * The three callers are ConnectToHostPort's failure arm and the two
 * searching wrappers, now CommEngineCloseConnection (was FUN_004fe6a0)
 * and CommEngineConnectComplete (was FUN_004ff640).
 *
 *
 * DROPPED-REG FIX (2026-08-28): EAX is the RAW connection list - head at
 * +0, tail at +4, live count at +8, free-list head at +0x10 - and EDI
 * the node being erased. Both are read before written. The body unlinks
 * the node from the doubly-linked list (next at node+0, prev at
 * node+4), destroys its payload through FUN_00500f90 (which is just
 * `add ecx,8 / jmp 0x5006b0` - the node's guts start at +8), pushes the
 * node onto the free list, decrements the count, and tears the whole
 * thing down through FUN_004ff6d0 when it hits zero.
 *
 * The raw list lives at engine+4 inside the vtable'd engine object -
 * every caller says so the same way: ConnectToHostPort passes
 * `lea eax,[ebx+4]` off its manager, and both erase-searchers
 * FUN_004fe6a0 / FUN_004ff640 do `add esi,4` on the engine before the
 * call (0x4fe6b2 / 0x4ff654).
 */
#include "ghidra_types.h"


void CommConnectionList_Erase(int *regEax,int *regEdi)

{
  int iVar1;
  int *in_EAX = regEax;
  int *unaff_EDI = regEdi;
  
  if (unaff_EDI == (int *)*in_EAX) {
    *in_EAX = *unaff_EDI;
  }
  else {
    *(int *)unaff_EDI[1] = *unaff_EDI;
  }
  if (unaff_EDI == (int *)in_EAX[1]) {
    in_EAX[1] = unaff_EDI[1];
  }
  else {
    *(int *)(*unaff_EDI + 4) = unaff_EDI[1];
  }
  FUN_00500f90();
  *unaff_EDI = in_EAX[4];
  iVar1 = in_EAX[2];
  in_EAX[4] = (int)unaff_EDI;
  in_EAX[2] = iVar1 + -1;
  if (iVar1 + -1 == 0) {
    FUN_004ff6d0();
  }
  return;
}

