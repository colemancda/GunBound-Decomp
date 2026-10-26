/* HasPendingTurnPhaseBarrierForSlot - 0x004e82c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), MODERATE-HIGH. Sole real caller is
 * State11_InBattle_OnTick.c:251 (orig 0x4bda41-0x4bda57), inside the
 * per-slot (0-7) loop that, every 60th tick for a given active mobile,
 * guards the call to PurgeBattleActionsForSlot(slot) right after it with
 * this function's return value - i.e. "is there still a reason to keep
 * this slot's queued actions" gates "go ahead and drop them".
 *
 * Scans both of g_replayContext's 0x206-stride battle-action arrays
 * (PopDirectBattleAction's at +0x454a4/+0x454a8, PopBroadcastBattleAction's
 * at +0x454b4/+0x454b8 - both named earlier in this batch) for a record
 * whose +4 byte - the same 0-7 per-slot id field PopDirectBattleAction/
 * PopBroadcastBattleAction/PurgeBattleActionsForSlot all index by -
 * equals `slot`, whose +0 ushort equals 0xc302 (TurnEventSet_Find.c's
 * header already documents 0xc302 as a turn-phase "ordering barrier"
 * opcode posted at battle entry and erased by OnTick/ProcessPacket), and
 * whose +0x26 byte equals `mobileId`.
 *
 * REGISTERS CONFIRMED BY DISASSEMBLY (2026-10-26). `ret 0`, nothing on
 * the stack: ECX is the context (the call site's `mov ecx, 0xe55ce0` =
 * &g_replayContext). The call site disassembles (0x4bda13-0x4bda57) as a
 * loop over `eax` counting 0-7 (the slot, matching the bitset test
 * `test dword ptr [eax>>5*4 + 0xe55e20], ...` against the same
 * DAT_00e55e20 bitset State11_InBattle_OnTick.c already reads as a
 * per-slot flag array), with `ebx` reloaded from `[esp+0x30]` right
 * before the call and never written afterward - `[esp+0x30]` is the
 * source's `local_3d50`, loaded earlier from `DAT_006a76f4[local_3d54]`,
 * i.e. a per-active-mobile value already used two lines above the call
 * to index DAT_006a7670's per-mobile-per-slot byte array. So `slot`
 * arrives in AL and `mobileId` arrives in BL, confirmed by disassembly,
 * not inferred from the body.
 *
 * HEDGE: what the queued record's +0x26 byte itself represents is NOT
 * independently confirmed. Tracing both producers (ProcessUdpProbeDatagram
 * for the direct array, ProcessEventBroadcast for the broadcast array)
 * shows +0x26 lands one byte past the 0x21-byte payload a normal record
 * carries - i.e. inside the opaque per-action payload the reference
 * server's Tunnel/TunnelForward struct forwards unmodified and never
 * itself defines. The caller-side identity of `mobileId` (a per-active-
 * mobile value from DAT_006a76f4) is solid; that the record's +0x26 byte
 * is "the same mobile id" is this function's own internal comparison,
 * not something confirmed from outside it - treat that one equality as
 * likely but unverified.
 */
#include "ghidra_types.h"


bool __fastcall HasPendingTurnPhaseBarrierForSlot(int param_1,int slot,int mobileId)

{
  bool bVar1;
  char bSlot = (char)slot;
  char bMobileId = (char)mobileId;
  uint uVar2;
  int iVar3;

  uVar2 = 0;
  bVar1 = false;
  if (*(uint *)(param_1 + 0x454a8) != 0) {
    iVar3 = 0;
    do {
      if (*(uint *)(param_1 + 0x454a8) <= uVar2) goto LAB_004e8398;
      if (*(char *)(iVar3 + 4 + *(int *)(param_1 + 0x454a4)) == bSlot) {
        if (*(uint *)(param_1 + 0x454a8) <= uVar2) goto LAB_004e8398;
        if (*(short *)(iVar3 + *(int *)(param_1 + 0x454a4)) == -0x3cfe) {
          if (*(uint *)(param_1 + 0x454a8) <= uVar2) goto LAB_004e8398;
          if (*(char *)(iVar3 + 0x26 + *(int *)(param_1 + 0x454a4)) == bMobileId) {
            bVar1 = true;
            break;
          }
        }
      }
      uVar2 = uVar2 + 1;
      iVar3 = iVar3 + 0x206;
    } while (uVar2 < *(uint *)(param_1 + 0x454a8));
  }
  uVar2 = 0;
  if (*(uint *)(param_1 + 0x454b8) == 0) {
    return bVar1;
  }
  iVar3 = 0;
  while (uVar2 < *(uint *)(param_1 + 0x454b8)) {
    if (*(char *)(iVar3 + 4 + *(int *)(param_1 + 0x454b4)) == bSlot) {
      if (*(uint *)(param_1 + 0x454b8) <= uVar2) break;
      if (*(short *)(iVar3 + *(int *)(param_1 + 0x454b4)) == -0x3cfe) {
        if (*(uint *)(param_1 + 0x454b8) <= uVar2) break;
        if (*(char *)(iVar3 + 0x26 + *(int *)(param_1 + 0x454b4)) == bMobileId) {
          return true;
        }
      }
    }
    uVar2 = uVar2 + 1;
    iVar3 = iVar3 + 0x206;
    if (*(uint *)(param_1 + 0x454b8) <= uVar2) {
      return bVar1;
    }
  }
LAB_004e8398:
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}
