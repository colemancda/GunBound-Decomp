/* RemoveCrystalFragment - 0x00437ae0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence: twin of RemoveIonAura (0x43c4f0) - the same body over a
 * different layer of the battle entity registry DAT_006a7f8c. This one
 * walks class id 0x186a4 (100004), the layer SpawnCrystalShot and
 * SpawnSuperCrystalShot stamp via InitProjectile(obj, 0x186a4) (texture
 * "crystal", the fragments bullet 9's detonation throws out). Both
 * spawners call it as their first act, before allocating the new
 * fragment. It scans the layer's intrusive list for the node whose key at
 * obj + 8 equals EDX, unlinks it (prev +0xc, next +0x10) and runs its
 * virtual slot 0 with 1 (the scalar deleting destructor). The layer holds
 * crystal fragments, so the noun is Fragment rather than Shot; the key's
 * meaning is not shown by anything outside the body.
 *
 * Calling convention and the two call sites (checked against the binary):
 * the body reads only EDX (the key compared with obj + 8) and ends in a
 * plain ret; ECX is unused. SpawnCrystalShot (0x437b5e `mov edx,ebx`,
 * ebx = [esp+0x24] loaded at 0x437b57, which after its five pushes is the
 * fourth stack argument) and SpawnSuperCrystalShot (0x437dc1
 * `mov edx,edi`, edi = [esp+0x2c] after its seven pushes, again the
 * fourth stack argument) both pass param_4, read before the function
 * masks it with 7. Callers now pass (0, param_4).
 */
#include "ghidra_types.h"


void __fastcall RemoveCrystalFragment(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 < 0x186a5) {
    while (uVar1 != 0x186a4) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (0x186a4 < uVar1) {
        return;
      }
    }
    puVar3 = *(undefined4 **)(iVar2 + 0x10);
    uVar1 = puVar3[2];
    if (uVar1 <= param_2) {
      while (uVar1 != param_2) {
        puVar3 = (undefined4 *)puVar3[4];
        uVar1 = puVar3[2];
        if (param_2 < uVar1) {
          return;
        }
      }
      *(undefined4 *)(puVar3[3] + 0x10) = puVar3[4];
      *(undefined4 *)(puVar3[4] + 0xc) = puVar3[3];
      (**(code **)*puVar3)(1);
    }
  }
  return;
}

