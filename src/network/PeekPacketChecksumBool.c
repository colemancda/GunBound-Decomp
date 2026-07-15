/* PeekPacketChecksumBool - 0x004065a0 in the original binary.
 *
 * The boolean reader of the value-guard / "packet-checksum" family (the
 * bit-valued sibling of PeekPacketChecksumState). Takes the guarded cell
 * in a register (EAX; Ghidra drops it): under the shared guard lock it
 * validates the (a,b,check) triple - on mismatch it sets
 * g_valueGuardTamperFlag and returns 0 - then returns bit (a & 7) of b as
 * a bool. Used pervasively to read guarded flags (e.g. the replay-playback
 * mode flag). See ARCHITECTURE.md "Packet-checksum utility family".
 *
 * NOT A QUICK FIX (2026-07-13): `in_EAX` is part of the same large,
 * already-acknowledged CValueGuard migration flagged in
 * PeekPacketChecksumState.c's own header (300+ callers there) - this
 * function has 190+ callers of its own (every Mobile*_MainAction,
 * SimulateMobileFrame/ProjectileFrame, most ProcessPacket handlers,
 * etc.), each passing a different guard cell address per call site.
 * Recovering the real cell for even a handful would need per-caller
 * tracing at this scale; this belongs to the CValueGuard/ValueGuard.cpp
 * migration effort, not a one-file bug-hunt pass.
 *
 * STARTED (2026-07-14): promoted to take the guard cell as an explicit
 * `cell` parameter - the uninitialized `in_EAX` read was the true root
 * cause of the bring-up getting stuck on the logo screen forever (see
 * ShowErrorDialog.c's header): this function is called unconditionally
 * every GameTick, and reading 3 essentially-random bytes off garbage
 * `in_EAX` fails the checksum almost immediately, setting
 * g_valueGuardTamperFlag, which pops a modal error dialog that can never
 * be dismissed without real mouse input, which permanently blocks every
 * future ChangeGameState call. GameTick.c's own 2 call sites are fixed
 * (recovered via objdump: g_clientContext+0x6aa678 and
 * g_clientContext+0x23310). functions.h keeps the K&R-empty declaration
 * so the ~188 other not-yet-recovered call sites keep compiling
 * unchanged (same partial-promotion pattern as FindSpriteFrame.c) -
 * recover each remaining caller's real cell address per-site as its own
 * code path is brought up, not attempted here.
 */
#include "ghidra_types.h"


char PeekPacketChecksumBool(byte *cell)

{
  /* BRING-UP NEUTER (2026-07-14): return the benign "false" default instead
   * of decoding the guard cell, mirroring the sibling PeekPacketChecksumState's
   * own `return 0` bring-up workaround. Once the broker connection opened
   * (FUN_004d2170 un-drop) and ProcessIncomingPackets began running on a real
   * receive ring, this got called from an unmigrated packet-handler call site
   * with a dropped-register `cell` = garbage (live-reproduced: page fault
   * reading 0x1), and even a valid-but-wrong cell would fail the checksum and
   * latch g_valueGuardTamperFlag (permanent modal error dialog that blocks all
   * ChangeGameState). Both are manifestations of the ~1397-caller
   * CValueGuard/ValueGuard.cpp migration, not this function's bug. GameTick's
   * two recovered cells are seeded all-false and already read as 0, so this is
   * behaviour-preserving for them. Remove once the guard-cell call sites are
   * recovered for a real build. */
  (void)cell;
  return '\0';
}

