/* DestroyActiveObjectLayerObjects - 0x004f1c00 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence. It walks the same key-ascending layer ring as
 * FindActiveObjectLayer (registry in EAX, ring head at +4, layer links at
 * +0x1c, key at +4, key in ECX), bails when the ring passes the key, and for
 * the matching layer calls every object's vtable slot 0 with 1 (the deleting
 * destructor, as PruneDeadActiveObjects does) before pointing the layer's
 * list sentinel at itself. src/cxx/ActiveObjects.h documents the identical
 * walk as ActiveObjects_DestroyBucket and records that the Title, Logo1,
 * Logo2 and Loading states carry inlined copies of it. The layer node itself
 * survives, so the verb is about the objects, not the layer. Callers pass the
 * outerKey values that State07_AvatarStore_RenderStoreContent blits with:
 * 0x9c40 from RenderInventoryItemDetail and 0x7530 from
 * State07_AvatarStore_OnCommand, i.e. they flush those preview layers before
 * repopulating them. "Clear" was rejected because it would hide that the
 * objects are freed.
 */
#include "ghidra_types.h"


void __fastcall DestroyActiveObjectLayerObjects(uint param_1,int regEax)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar4 = *(undefined4 **)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = puVar4[1];
  if (uVar1 <= param_1) {
    while (uVar1 != param_1) {
      puVar4 = (undefined4 *)puVar4[7];
      uVar1 = puVar4[1];
      if (param_1 < uVar1) {
        return;
      }
    }
    puVar2 = (undefined4 *)puVar4[4];
    while (puVar2 != puVar4) {
      puVar3 = (undefined4 *)*puVar2;
      puVar2 = (undefined4 *)puVar2[4];
      (*(code *)*puVar3)(1);
    }
    puVar4[3] = puVar4;
    puVar4[4] = puVar4;
  }
  return;
}

