/* BattleRandom_Next - 0x00415c60 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-11-04), LIKELY. Advances the shared battle random state at
 * DAT_005b3480 and returns a value drawn from it: x = state * 0xda003 +
 * 0x5703b11 is the return value, and the state becomes state + ((x * 0x61
 * + 0x61) mod 0xf4241). It is a deterministic generator, not the CRT rand:
 * the state is set from the wire, in State09_ReadyRoom_ProcessPacket's
 * GB_OP_START_GAME_NOTIFICATION arm (the dword right after the events
 * word, i.e. the head of the notification's trailing command data), so
 * every client starts the match from the same value, and the identical
 * update is inlined in SpawnJewel, State11_InBattle_OnEnter and
 * State11_InBattle_OnTick. The callers of this out-of-line copy -
 * TickJewelFrame and State11_InBattle_OnTick - use it for a parity test
 * and for the modulo-10 choice among the speech-balloon strings
 * (GetLocalizedString base + r % 10). LIKELY: the synchronised-seed role
 * rests on the start-notification assignment and the inlined copies; the
 * server's StartGameNotification struct does not name the field.
 */
#include "ghidra_types.h"


int BattleRandom_Next(void)

{
  int iVar1;
  
  iVar1 = DAT_005b3480 * 0xda003 + 0x5703b11;
  DAT_005b3480 = DAT_005b3480 + (iVar1 * 0x61 + 0x61U) % 0xf4241;
  return iVar1;
}

