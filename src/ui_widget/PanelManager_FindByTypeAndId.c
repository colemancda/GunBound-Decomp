/* PanelManager_FindByTypeAndId - 0x0050f000 in the original binary.
 *
 * NAMED (batch 35), CERTAIN (was FUN_0050f000).  Walks the panel manager's
 * node list (head at manager+4, node = {next, prev, panel}; the same list
 * PanelManager_PruneBelowId unlinks) and returns the first panel whose
 * +0x20 equals EDX and whose +0x24 equals ESI, else 0.  Widget.h names
 * those two fields m_typeId (+0x20) and m_id (+0x24); PanelManager_
 * FindByName tests the same pair with (0, 0x4e21).  Callers confirm the
 * reading: WriteReplayEventRecord passes (0, 0x232a), the
 * ChannelUserList panel id PruneBelowId's header lists, and State09_
 * ReadyRoom_OnCommand passes (0, 3).  The manager is EAX (`mov ecx,
 * [eax+4]` at 0x50f000), type EDX, id ESI; no stack arguments (plain
 * `ret`).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * ESI RECOVERED (2026-08-25): an immediate at both sites, and they differ --
 * 0x232a from WriteReplayEventRecord, 3 from State09_ReadyRoom_OnCommand --
 * so the two had to be paired rather than filled uniformly.  The pairing is
 * free here: the two binary sites are in two different named functions, one
 * source call each.
 */
#include "ghidra_types.h"


int __fastcall PanelManager_FindByTypeAndId(undefined4 param_1,int param_2,int regEax,int regEsi)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = *(undefined4 **)(regEax + 4);
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    iVar2 = puVar1[2];
    puVar1 = (undefined4 *)*puVar1;
  } while ((*(int *)(iVar2 + 0x20) != param_2) || (*(int *)(iVar2 + 0x24) != regEsi));
  return iVar2;
}

