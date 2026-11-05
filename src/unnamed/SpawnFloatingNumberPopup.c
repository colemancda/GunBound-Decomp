/* SpawnFloatingNumberPopup - 0x004368f0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004368f0 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Builds a
 * 0x4c byte effect object stamped with class id 0x30d54 and vtable
 * 0x555f04 (5 slots in docs/vtable_census.txt: slot 2 at 0x471dc0 moves
 * the object up 3 px per tick for the first 10 ticks and marks it dead
 * after 30; slot 3 at 0x471df0 sprintfs the integer at +0x44 with format
 * 0x551ed4 and draws the digits at +0x38,+0x3c), registers it with
 * RegisterActiveObject, and does nothing when the effects guard flag is
 * set. Callers pass (x, y, value) with value in -1, 1, 2 or 4:
 * FinishTurnAndSelectNext, FUN_004ccd10, State11_InBattle_OnTick,
 * State11_InBattle_ProcessPacket and State11_InBattle_ProcessBattleAction
 * use it for the score-award floating number over the mobile
 * (SpawnBattleAnnouncement's header). The class id 0x30d54 is shared with
 * SpawnDamagePopup's DamagePopup_ctor object but that class uses vtable
 * 0x555d98 and merges hits into one popup, so the two are distinct
 * classes; LIKELY because the meaning of the value (a score delta) is read
 * from callers and not confirmed from the strings.
 */
#include "ghidra_types.h"


void SpawnFloatingNumberPopup(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    puVar2 = operator_new(0x4c);
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = (undefined4 *)0x0;
    }
    else {
      puVar2[1] = 0x30d54;
      puVar2[2] = 0xffffffff;
      puVar2[3] = 0;
      puVar2[4] = 0;
      *(undefined1 *)(puVar2 + 5) = 0;
      *(undefined1 *)((int)puVar2 + 0x15) = 0;
      puVar2[6] = 0xffffffff;
      puVar2[7] = 0;
      *(undefined1 *)(puVar2 + 8) = 0;
      puVar2[10] = 0;
      puVar2[0xb] = 0;
      puVar2[9] = 0xffffffff;
      *puVar2 = &PTR_FUN_00555f04;
      puVar2[0x10] = 0;
      puVar2[0x12] = 0;
    }
    puVar2[0xf] = param_2;
    puVar2[0xe] = param_1;
    puVar2[0x11] = param_3;
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

