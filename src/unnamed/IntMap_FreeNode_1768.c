/* IntMap_FreeNode_1768 - 0x005011c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): the same free-list push as
 * StringMap_FreeNode_CString, for a map whose node link sits at
 * +0x1760. EAX is the node being retired and ESI the map that owns it;
 * both are read before
 * written. The node's +0x1760 link takes the map's current free head from
 * +0x2c, the node becomes the new head, the live count at +4 drops, and
 * the map is shrunk when that count falls below the threshold at +0x1c
 * with the lock byte at +0x20 clear.
 *
 * Its bucket-sweep caller IntMap_RemoveAll_1768 carried the same defect the
 * StringMap_FreeNode_CString sweep did: the original captures the node
 * in EAX and only then advances the cursor, while the port advanced
 * first and called
 * with nothing, so writing the call in terms of the advanced value would
 * have retired the wrong node. The captured value gets a local there.
 * FUN_00500710's two sites are straightforward - `mov eax,ecx` for
 * the node the lookup found, with the map already in ESI.
 *
 * NAMED (2026-08-28): ATL7's CAtlMap<K,V>::FreeNode out of VC7.1's
 * atlcoll.h - the same member as StringMap_FreeNode_CString, for a
 * third instantiation. See that file for the field-by-field
 * correspondence and for how HashMap_Construct and FUN_00500e30 settle
 * the class from outside. This copy has no node destructor call at all,
 * which is what a POD key and value give.
 *
 * WHICH INSTANTIATION, from a caller rather than from the body:
 * FUN_00500710 runs IntMap_Find_1768 over its map and then hands the
 * node that find returned straight to this function with the same map
 * still in EBX. So the node is the 0x1768 one - payload below +0x1760,
 * m_pNext at +0x1760 (the link this writes), m_nHash at +0x1764 (the
 * field IntMap_Find_1768 compares), 0x1768 total - and the suffix is
 * that node stride, matching IntMap_Find_1768, IntMap_Insert_1768 and
 * IntMap_CopyValue_1768.
 */
#include "ghidra_types.h"


void IntMap_FreeNode_1768(int regEax,int regEsi)

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

