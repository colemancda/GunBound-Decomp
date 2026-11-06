/* SnapMobilesToGround - 0x0043a5f0 in the original binary.
 *
 * NAMED (batch 36), LIKELY. Walks the battle entity registry
 * (g_clientContext + 0x6a7f8c) to the class-id 100001 (0x186a1) layer,
 * the player mobiles (see InitMobile, which seeds +4 with 0x186a1), and for
 * each mobile calls vtable slot 5 (+0x14), ComputeMobileGroundY (0x45c6e0 -
 * the shared slot-5 implementation, FindGroundHeightAtColumn on the mobile's
 * column cell +0x90c), then stores the result into the guard cell at
 * +0xb30 with EncodeOutgoingPacketField under g_valueGuardLock.
 *
 * Why "ground": +0xb30 is exactly one guard cell (0x224 bytes) after
 * +0x90c, the column ComputeMobileGroundY reads, so the pair is the mobile's
 * (x, y) position and this writes y = terrain height under x. Mobile.h
 * labels the two cells fire angle/power instead; the column use in
 * ComputeMobileGroundY and the slot name contradict that, but it is the
 * soft spot of this name.
 *
 * Callers (4 sites): the battle tick (State11_InBattle_OnTick, 0x4c0a61),
 * ProcessBattleAction (0x4b6782 and 0x4b6901; the 0x4b6782 one sits behind
 * a PacketChecksumEquals gate) and FUN_0043bda0 (0x43be13), which walks
 * the same 100001 layer right after the call.
 *
 * The vtable call drops `this` (ECX = the mobile) in the port, and the stored
 * value (EAX = the slot-5 return) is the Ghidra-lost uVar3.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void SnapMobilesToGround(void)

{
  uint uVar1;
  int *piVar2;
  undefined4 uVar3;
  int *piVar4;
  
  piVar4 = *(int **)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar1 = piVar4[1];
  if (uVar1 < 0x186a2) {
    while (uVar1 != 0x186a1) {
      piVar4 = (int *)piVar4[7];
      uVar1 = piVar4[1];
      if (0x186a1 < uVar1) {
        return;
      }
    }
    for (piVar2 = (int *)piVar4[4]; piVar4 != piVar2; piVar2 = (int *)piVar2[4]) {
      (**(code **)(*piVar2 + 0x14))();
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x43a647
       * (`lea edi,[esi+0xb30]`, esi = this file's own loop variable piVar2,
       * confirmed by objdump of orig/GunBound.gme). piVar2 is `int *`
       * (scales by 4), so the byte offset is taken via `(int)piVar2 +
       * 0xb30`. See tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField((int)piVar2 + 0xb30, uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  return;
}

