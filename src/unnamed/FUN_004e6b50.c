/* FUN_004e6b50 - 0x004e6b50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e6b50(void)

{
  /* BRING-UP WORKAROUND: skip starting this worker thread.
   *
   * Same dropped-ESI situation as FUN_00415500/FUN_00415530 (orig
   * 0x40f3b4 loads ESI=&g_replayContext before calling this), but that global
   * is ALREADY a large, widely-referenced struct throughout battle/replay
   * code (PostTurnEvent, FUN_004e7b60/004e80d0/004e84c0, WriteReplayEventRecord,
   * etc. all take &g_replayContext as their own context arg) with other globals
   * declared close behind it (DAT_00e55cf4 only 0x14 bytes later) - this
   * function needs to write as far as +0x3bc, which would require resizing
   * g_replayContext far beyond what's safe without auditing every one of those
   * other call sites. Not required to reach the logo/menu render loop;
   * revisit alongside a proper pass over the whole g_replayContext struct. */
  return;
}

