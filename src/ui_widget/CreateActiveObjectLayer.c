/* CreateActiveObjectLayer - 0x004f2f00 in the original binary.
 *
 * PROMOTED (2026-07-14): allocates a new "layer" (outer-list bucket) node
 * for an active-object registry and links it into the registry's sorted
 * outer list at the correct sorted position for `layerKey` - the helper
 * RegisterActiveObject calls when no existing layer matches the node
 * being registered's own key (`node[1]`).
 *
 * DROPPED-ARGUMENT FIX: Ghidra read the layer key as `unaff_ESI`, an
 * uninitialized local, instead of a real parameter - silently reading
 * garbage. Confirmed via the original disassembly at RegisterActiveObject's
 * own call site (orig 0x4f2fba: `mov esi,[edi+4]` - i.e. `node[1]` - then
 * `push edx` [param_1, the registry] / `call 0x4f2f00`, ESI never pushed:
 * a mixed convention, key-in-ESI/registry-on-stack, matching the
 * ReadXFSEntryByte count-in-EAX idiom already documented elsewhere).
 * Promoted `layerKey` to a real second parameter.
 *
 * NOT FIXED HERE: this function has 4 other call sites (orig 0x414965,
 * 0x4150c5, 0x4d19c7, 0x4d1fc5) besides RegisterActiveObject's, each in
 * its own not-yet-verified caller with its own distinct ESI source -
 * those still use the old 1-arg form and need the same per-site
 * disassembly treatment (same partial-fix precedent as
 * RegisterActiveObject.c's own header, which fixed only its
 * LoadSpriteSet.c call site first).
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 *CreateActiveObjectLayer(int param_1, uint layerKey)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;

  puVar3 = operator_new(0x20);
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    puVar3[1] = layerKey;
    puVar3[2] = 0xffffffff;
    puVar3[3] = 0;
    puVar3[4] = 0;
    *(undefined1 *)(puVar3 + 5) = 0;
    *puVar3 = &PTR_FUN_00557530;
    *(undefined1 *)((int)puVar3 + 0x15) = 1;
    puVar3[6] = 0;
    puVar3[7] = 0;
  }
  iVar1 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while( true ) {
    if (layerKey < uVar2) {
      puVar3[7] = iVar1;
      puVar3[6] = *(undefined4 *)(iVar1 + 0x18);
      *(undefined4 **)(*(int *)(iVar1 + 0x18) + 0x1c) = puVar3;
      *(undefined4 **)(iVar1 + 0x18) = puVar3;
      puVar3[4] = puVar3;
      puVar3[3] = puVar3;
      return puVar3;
    }
    if (uVar2 == layerKey) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  if (puVar3 != (undefined4 *)0x0) {
    (**(code **)*puVar3)(1);
  }
  return (undefined4 *)0x0;
}
