/* FUN_005011c0 - 0x005011c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): the same free-list push as
 * FUN_004156d0, for a map whose node link sits at +0x1760. EAX is the node
 * being retired and ESI the map that owns it; both are read before
 * written. The node's +0x1760 link takes the map's current free head from
 * +0x2c, the node becomes the new head, the live count at +4 drops, and
 * the map is shrunk when that count falls below the threshold at +0x1c
 * with the lock byte at +0x20 clear.
 *
 * Its bucket-sweep caller FUN_00500790 carried the same defect the
 * FUN_004156d0 sweep did: the original captures the node in EAX and only
 * then advances the cursor, while the port advanced first and called
 * with nothing, so writing the call in terms of the advanced value would
 * have retired the wrong node. The captured value gets a local there.
 * FUN_00500710's two sites are straightforward - `mov eax,ecx` for
 * the node the lookup found, with the map already in ESI.
 */
#include "ghidra_types.h"


void FUN_005011c0(int regEax,int regEsi)

{
  int *piVar1;
  int in_EAX = regEax;
  undefined4 uVar2;
  int *_Memory;
  uint uVar3;
  int unaff_ESI = regEsi;
  
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

