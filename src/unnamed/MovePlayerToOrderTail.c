/* MovePlayerToOrderTail - 0x00415ce0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): it works on the 8-slot table that
 * ResetPlayerOrderList initialises to the identity (ctx+0x4737c, count at
 * +0x20 = ctx+0x4739c), and all five callers pass the player slot and
 * ctx+0x4737c.  The caller pattern fixes what "target position" means:
 * - packet 0x3010 in WriteReplayEventRecord and the two join arms in
 *   State03_GameRoomList_ProcessPacket do `ctx[0x4739c] += 1` first, then
 *   call it - the new player is put at index count-1, the last active slot;
 * - packet 0x3020 in WriteReplayEventRecord calls it first and then does
 *   `ctx[0x4739c] -= 1` - the leaving player is put at the last active slot
 *   and the count shrinks past it;
 * - State09_ReadyRoom_ProcessBattleAction (map-selection-sync arm) calls it
 *   with no count change, re-seating that player at index count-1.
 * So the target is always index count-1, the tail of the active region
 * (the body's iVar2 = count - 1).  The requested name was
 * MovePlayerToOrderBoundary; "Tail" says which end of the active region
 * the player is moved to, which is what the callers show.  If the player is
 * not in the table or is already at the tail nothing happens; otherwise the
 * entries between are shifted by one.
 *
 * Second parameter is the table base in EBX (witnessed per site in the
 * DROPPED REGISTER note below); tools/count_call_args.py reports 2
 * arguments at all 5 sites.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_EBX is the 8-slot table this
 * searches and compacts, and it is `<context> + 0x4737c` at all five sites --
 * every one of them is a `lea ebx,[<base> + 0x4737c]` immediately before the
 * call, never a load.
 *
 * The base is witnessed locally at each site rather than assumed, because
 * this function's callers reuse their registers heavily:
 *   - Three sites sit directly under `*(int *)(<base> + 0x4739c) += 1`, and
 *     0x4737c + 0x20 = 0x4739c is the count field this body reads as
 *     `unaff_EBX + 0x20` -- so the C line above each call is literally
 *     writing base+0x20 through the same register.
 *   - State09_ReadyRoom_ProcessBattleAction's is pinned by the
 *     `cmp byte ptr [eax + 0x3b6c0],0xff` two instructions earlier, which is
 *     that file's own `if (*(char *)(g_clientContext + 0x3b6c0) == -1)`.
 *   - WriteReplayEventRecord's 0x3020 site takes iVar19 rather than
 *     g_clientContext because that is what the `+ 0x4739c` line beside it
 *     uses; EDI is written half a dozen times in that 5587-byte function, so
 *     the neighbouring expression is the reliable witness, not the register.
 */
#include "ghidra_types.h"


void MovePlayerToOrderTail(int param_1,int regEbx)

{
  int iVar1;
  int iVar2;
  int unaff_EBX = regEbx;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar2 = *(int *)(unaff_EBX + 0x20) + -1;
  iVar1 = 0;
  do {
    if (*(int *)(unaff_EBX + iVar1 * 4) == param_1) goto LAB_00415cfe;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  iVar1 = -1;
LAB_00415cfe:
  if ((iVar1 != iVar2) && (iVar1 != -1)) {
    if (iVar1 < iVar2) {
      puVar3 = (undefined4 *)(unaff_EBX + iVar1 * 4);
      puVar4 = puVar3;
      for (iVar1 = iVar2 - iVar1; puVar3 = puVar3 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar4 = puVar4 + 1;
      }
      *(int *)(unaff_EBX + iVar2 * 4) = param_1;
      return;
    }
    for (; iVar2 < iVar1; iVar1 = iVar1 + -1) {
      *(undefined4 *)(unaff_EBX + iVar1 * 4) = *(undefined4 *)(unaff_EBX + -4 + iVar1 * 4);
    }
    *(int *)(unaff_EBX + iVar2 * 4) = param_1;
  }
  return;
}

