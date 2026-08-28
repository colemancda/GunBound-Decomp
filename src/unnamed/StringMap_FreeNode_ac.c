/* StringMap_FreeNode_ac - 0x00500e80 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): the same free-list push as
 * StringMap_FreeNode_CString, for a map whose node link sits at +0xa4.
 * EAX is the node being retired and ESI the map that owns it; both are
 * read before
 * written. The node's +0xa4 link takes the map's current free head from
 * +0x2c, the node becomes the new head, the live count at +4 drops, and
 * the map is shrunk when that count falls below the threshold at +0x1c
 * with the lock byte at +0x20 clear.
 *
 * Its bucket-sweep caller StringMap_RemoveAll_ac carried the same defect the
 * StringMap_FreeNode_CString sweep did: the original captures the node
 * in EAX and only then advances the cursor, while the port advanced
 * first and called
 * with nothing, so writing the call in terms of the advanced value would
 * have retired the wrong node. The captured value gets a local there.
 * FUN_00504050's two sites are straightforward - `mov eax,ecx` for
 * the node the lookup found, with the map already in ESI.
 *
 * NAMED (2026-08-28): ATL7's CAtlMap<K,V>::FreeNode out of VC7.1's
 * atlcoll.h - the same member as StringMap_FreeNode_CString, for a
 * different instantiation. See that file for the field-by-field
 * correspondence and for why HashMap_Construct and FUN_00500e30 settle
 * the class from outside.
 *
 * WHICH INSTANTIATION, from a caller rather than from the body:
 * FUN_00504050 runs StringMap_Find_ac over its map and then hands the
 * node that find returned straight to this function with the same map
 * still in EAX. So the node is the 0xac one - payload below +0xa4,
 * m_pNext at +0xa4 (the link this writes), m_nHash at +0xa8 (the field
 * StringMap_Find_ac compares), 0xac total - and the suffix is that node
 * stride, matching StringMap_Find_ac and StringMap_Insert_ac.
 */
#include "ghidra_types.h"


void StringMap_FreeNode_ac(int regEax,int regEsi)

{
  int *piVar1;
  int in_EAX = regEax;
  undefined4 uVar2;
  int *_Memory;
  uint uVar3;
  int unaff_ESI = regEsi;
  
  thunk_FUN_00500f80();
  *(undefined4 *)(in_EAX + 0xa4) = *(undefined4 *)(unaff_ESI + 0x2c);
  uVar3 = *(int *)(unaff_ESI + 4) - 1;
  *(int *)(unaff_ESI + 0x2c) = in_EAX;
  *(uint *)(unaff_ESI + 4) = uVar3;
  if ((uVar3 < *(uint *)(unaff_ESI + 0x1c)) && (*(int *)(unaff_ESI + 0x20) == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00500ce0(unaff_ESI,uVar2);
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

