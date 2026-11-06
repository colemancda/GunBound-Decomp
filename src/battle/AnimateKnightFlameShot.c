/* AnimateKnightFlameShot - 0x0047ab00 in the original binary.
 *
 * RENAMED (from FUN_0047ab00): slot 2 (+0x8) of vtable 0x556008, whose
 * slot 0 is KnightFlameShot_ScalarDtor (0x47aad0).  Slot 2 is the
 * projectile Animate virtual; this override counts +0x3fa0 up to the limit
 * at +0x3f9c, advancing the sprite meanwhile, plays a sound
 * (AcquireSoundChannel) when it reaches it, and then falls through to the
 * base AnimateProjectileTick (0x48f1c0), which is what the sibling vtables
 * install in this slot.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void __fastcall AnimateKnightFlameShot(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x3fa0) + 1;
  *(int *)(param_1 + 0x3fa0) = iVar2;
  if (iVar2 < *(int *)(param_1 + 0x3f9c)) {
    AdvanceSpriteAnimation(param_1);
    return;
  }
  if (iVar2 == *(int *)(param_1 + 0x3f9c)) {
    cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
    if (cVar1 == '\0') {
      AcquireSoundChannel(0);
    }
  }
  AnimateProjectileTick();
  return;
}

