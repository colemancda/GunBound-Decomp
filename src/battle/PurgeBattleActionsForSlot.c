/* PurgeBattleActionsForSlot - 0x004e83b0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), LIKELY on the name, CONFIRMED on the promoted
 * parameter. Scans both of g_replayContext's 0x206-stride battle-action
 * arrays (PopDirectBattleAction's at +0x454a4/+0x454a8 and
 * PopBroadcastBattleAction's at +0x454b4/+0x454b8, both named earlier in
 * this batch) and removes every record whose byte at +4 - confirmed
 * elsewhere in this batch to be a 0-7 per-slot id, the same field
 * PopDirectBattleAction/PopBroadcastBattleAction index their "seen"
 * bitmap by - equals the slot this function was called with.
 *
 * DROPPED-REGISTER FIX (2026-10-26): Ghidra rendered the incoming slot
 * id as `unaff_BL`, a local read but never assigned in this function's
 * own body. Its sole caller, State11_InBattle_OnTick.c (orig 0x4bd8b0),
 * disassembles at the real call site (0x4bda60-0x4bda69) as:
 *     mov bl, byte ptr [esp+0x34]   ; the 0-7 loop counter
 *     mov esi, 0xe55ce0             ; &g_replayContext
 *     call 0x4e83b0
 * - `[esp+0x34]` is exactly the C source's `local_3d4c` loop variable
 * (the same one gating the per-slot bitset DAT_00e55e20 and the
 * per-mobile-per-slot byte array DAT_006a7670 two lines above the call
 * in the ported source), confirming the dropped register is the slot
 * id, not an uninitialised read. Promoted to an explicit trailing
 * `int slot` parameter; the one call site was updated to pass
 * `local_3d4c`.
 */
#include "ghidra_types.h"


void PurgeBattleActionsForSlot(int regEsi,int slot)

{
  LPCRITICAL_SECTION lpCriticalSection;
  uint uVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  char bSlot = (char)slot;
  uint uVar5;

  lpCriticalSection = (LPCRITICAL_SECTION)(regEsi + 0x45264);
  EnterCriticalSection(lpCriticalSection);
  uVar5 = *(uint *)(regEsi + 0x454a8);
  uVar1 = 0;
  if (uVar5 != 0) {
    iVar4 = 0;
    do {
      if (uVar5 <= uVar1) goto LAB_004e8470;
      if (*(char *)(*(int *)(regEsi + 0x454a4) + 4 + iVar4) == bSlot) {
        if (uVar1 + 1 <= *(uint *)(regEsi + 0x454a8)) {
          iVar4 = (*(uint *)(regEsi + 0x454a8) - uVar1) + -1;
          if (iVar4 != 0) {
            pvVar3 = (void *)(uVar1 * 0x206 + *(int *)(regEsi + 0x454a4));
            _memmove(pvVar3,(void *)((int)pvVar3 + 0x206),iVar4 * 0x206);
          }
          *(int *)(regEsi + 0x454a8) = *(int *)(regEsi + 0x454a8) + -1;
          LeaveCriticalSection(lpCriticalSection);
          return;
        }
        goto LAB_004e8470;
      }
      uVar1 = uVar1 + 1;
      iVar4 = iVar4 + 0x206;
    } while (uVar1 < uVar5);
  }
  uVar5 = 0;
  if (*(int *)(regEsi + 0x454b8) != 0) {
    iVar4 = 0;
    if (*(int *)(regEsi + 0x454b8) == 0) {
LAB_004e8470:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      if (*(char *)(*(int *)(regEsi + 0x454b4) + 4 + iVar4) == bSlot) {
        if (*(uint *)(regEsi + 0x454b8) < uVar5 + 1) goto LAB_004e8470;
        iVar2 = (*(uint *)(regEsi + 0x454b8) - uVar5) + -1;
        if (iVar2 != 0) {
          pvVar3 = (void *)(*(int *)(regEsi + 0x454b4) + iVar4);
          _memmove(pvVar3,(void *)((int)pvVar3 + 0x206),iVar2 * 0x206);
        }
        *(int *)(regEsi + 0x454b8) = *(int *)(regEsi + 0x454b8) + -1;
      }
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 0x206;
    } while (uVar5 < *(uint *)(regEsi + 0x454b8));
  }
  LeaveCriticalSection(lpCriticalSection);
  return;
}
