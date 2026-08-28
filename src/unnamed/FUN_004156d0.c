/* FUN_004156d0 - 0x004156d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): both inputs are registers and both are
 * read before written. EAX is the node being retired - `mov esi,eax` at
 * 0x4156d1 is the first instruction after the prologue push - and EDI is
 * the map that owns it, first touched at 0x4156d8 by
 * `mov eax,[edi+0x2c]`.
 *
 * The body is a free-list push: the node's +8 link is set to the map's
 * current free head at +0x2c, the node becomes the new head, the live
 * count at +4 is decremented, and when that count falls below the
 * threshold at +0x1c (with the lock byte at +0x20 clear) the map is
 * shrunk. When the count reaches zero the whole block chain at +0x28 is
 * freed.
 *
 * Its one ported call site, in FUN_00415560's bucket sweep, also needed
 * a correction beyond the arguments: the original captures the node in
 * EAX and only then advances the cursor (`mov eax,esi / mov esi,[esi+8]`
 * at 0x415590), whereas the port advanced first and called with nothing,
 * so writing the argument as the already-advanced value would have
 * retired the wrong node. See that file.
 */
#include "ghidra_types.h"


void FUN_004156d0(int regEax,int regEdi)

{
  int *piVar1;
  int in_EAX = regEax;
  undefined4 uVar2;
  int *_Memory;
  uint uVar3;
  int unaff_EDI = regEdi;
  
  thunk_FUN_00415890();
  *(undefined4 *)(in_EAX + 8) = *(undefined4 *)(unaff_EDI + 0x2c);
  uVar3 = *(int *)(unaff_EDI + 4) - 1;
  *(int *)(unaff_EDI + 0x2c) = in_EAX;
  *(uint *)(unaff_EDI + 4) = uVar3;
  if ((uVar3 < *(uint *)(unaff_EDI + 0x1c)) && (*(int *)(unaff_EDI + 0x20) == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00409e20(unaff_EDI,uVar2);
  }
  if (*(int *)(unaff_EDI + 4) == 0) {
    _Memory = *(int **)(unaff_EDI + 0x28);
    *(undefined4 *)(unaff_EDI + 0x2c) = 0;
    if (_Memory != (int *)0x0) {
      do {
        piVar1 = (int *)*_Memory;
        _free(_Memory);
        _Memory = piVar1;
      } while (piVar1 != (int *)0x0);
      *(undefined4 *)(unaff_EDI + 0x28) = 0;
    }
  }
  return;
}

