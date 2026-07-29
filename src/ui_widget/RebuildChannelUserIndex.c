/* RebuildChannelUserIndex - 0x0041b6b0 in the original binary.
 *
 * Rebuilds the channel user-list panel's compact index table
 * (g_clientContext+0x44248, walked by RenderChannelUserRow.c): fills all
 * 0x100 slots with -1 (the row loop's stop sentinel), then scans a 0x100-
 * entry byte flag array (g_clientContext+0x41345, one "is this roster slot
 * occupied" flag per possible user) and appends the index of every SET
 * flag, compacting the sparse roster into a dense list. Sole caller is
 * RenderChannelUserRow.c, once per Update.
 *
 * FIXED (2026-07-29): `unaff_ESI` was an uninitialised dropped-register
 * argument - the whole function operated on garbage stack memory instead
 * of g_clientContext, so BOTH the -1 sentinel fill and the flag scan hit
 * random addresses. Confirmed via objdump: the original has no prologue
 * computation for ESI at all (`lea edx,[esi+0x44248]` is literally its
 * first instruction), and its sole caller does
 * `mov esi,dword ptr [0x5b3484]` (= g_clientContext) immediately before
 * `call 0x41b6b0`. Promoted to an explicit parameter; the call site in
 * RenderChannelUserRow.c now passes g_clientContext.
 *
 * Symptom this fixes: with the index table built from garbage, the
 * channel roster panel showed every one of its (up to 7) row slots
 * resolving to whatever user index the garbage happened to decode to -
 * observed live as the single connected user's name repeated 7 times.
 */
#include "ghidra_types.h"


void RebuildChannelUserIndex(int clientContext)

{
  int iVar1;
  int *piVar2;
  int *piVar3;

  piVar2 = (int *)(clientContext + 0x44248);
  piVar3 = piVar2;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar3 = -1;
    piVar3 = piVar3 + 1;
  }
  iVar1 = 0;
  do {
    if (*(char *)(clientContext + 0x41345 + iVar1) != '\0') {
      *piVar2 = iVar1;
      piVar2 = piVar2 + 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  return;
}
