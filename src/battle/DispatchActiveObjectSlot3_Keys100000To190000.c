/* DispatchActiveObjectSlot3_Keys100000To190000 - 0x00450bd0 in the original binary.
 *
 * NAMED (batch 41), name is deliberately neutral. A key-filtered pass
 * over the same layer collection DrawActiveObjectLayers (0x450860) and
 * TickActiveObjectLayers (0x4507d0) walk: layer nodes chained through
 * +0x1c from the head at ring+4, each with its key at +4 and an inner
 * object chain through +0x10 ended by the flag at +0x15. For every layer
 * whose key is greater than 100000 and below 190000 (cmp 0x186a0 and
 * 0x2e630)
 * it calls vtable slot 3 (+0xc) on each object in the inner chain. The
 * ring (ctx+0x6a7f88, passed in EBX) appears to be ordered by key, since
 * the walk returns at the first key past the range.
 *
 * Caller: State11_InBattle_ClearEffectTextures (0x4c2d2f), immediately after
 * FlushCompositorLayer(2, ...).
 *
 * Why not "Draw" or "Render": slot 3 is the draw step for most classes
 * (docs/vtable_census.txt: RenderMobile and the hazard renderers sit
 * there) but a different operation for others; the projectile classes
 * carry PublishProjectileTrackingState in slot 3. The key ranges are
 * read off the compares in the body and are not matched to named layer
 * ids, so no stronger verb is claimed.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void DispatchActiveObjectSlot3_Keys100000To190000(int regEbx)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(int *)(*(int *)(regEbx + 4) + 0x1c);
  if (iVar3 != *(int *)(regEbx + 4)) {
    do {
      if (100000 < *(uint *)(iVar3 + 4)) {
        if (189999 < *(uint *)(iVar3 + 4)) {
          return;
        }
        piVar2 = *(int **)(iVar3 + 0x10);
        cVar1 = *(char *)((int)piVar2 + 0x15);
        while (cVar1 == '\0') {
          (**(code **)(*piVar2 + 0xc))();
          piVar2 = (int *)piVar2[4];
          cVar1 = *(char *)((int)piVar2 + 0x15);
        }
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
    } while (iVar3 != *(int *)(regEbx + 4));
  }
  return;
}

