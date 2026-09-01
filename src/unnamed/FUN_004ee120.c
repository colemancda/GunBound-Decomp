/* FUN_004ee120 - 0x004ee120 in the original binary.
 *
 * TRIAGE RECHECK (2026-09-01, after the 86e96f30 matrix sizing): the
 * blocker HOLDS - the prerequisite is the split-struct coalesce of the
 * 0xe53698 input/cursor object (0x5a8 bytes; highest ctor write +0x5a4),
 * not the 0x5a9xxx sizing, which is only the pattern to copy. Plan:
 * exact-fit object in globals_sized.c, SUBFIELD macros for the split
 * neighbours (+0x04, cursor deltas, +0x4c/+0x54, the FUN_004ee540 timer
 * fields +0x68..+0x84, +0x58c..+0x5a4; verify g_cursorFreeMode==0xe53c3c
 * against Ghidra before folding and retire its hand-set =1), then
 * promote this ctor's regEax.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RESOLVED BUT DELIBERATELY NOT APPLIED (2026-08-27).
 * in_EAX is 0xe53698 -- uniform, and there is only one call site: the static
 * initialiser thunk FUN_00540e00 (`mov eax,0xe53698; call; atexit`).  That
 * address is g_mouseDeviceTimerBlock, so the argument itself is settled.
 *
 * Passing it would be a regression, not a fix.  This is the constructor for
 * the DirectInput mouse singleton, and globals.c models that object as a
 * SPLIT STRUCT: g_mouseDeviceTimerBlock is only 0x88 bytes -- sized to cover
 * the highest field its *consumers* read -- while the object's other fields
 * live in the scattered separate globals beside it (DAT_00e5369c,
 * g_cursorDeltaX/Y, DAT_00e536e4, ...), flagged there as a KNOWN DIVERGENCE.
 * This body writes out to +0x5a4, so wiring the pointer would run 0x51c bytes
 * off the end of that array AND still miss every field the split-out globals
 * actually hold.  Today the call is a harmless no-op, which globals.c relies
 * on ("the constructors are bring-up-stubbed ... so the singletons never
 * exist").
 *
 * What this body DOES settle is the extent globals_sized.c says is unknown:
 * its highest write is the byte at +0x5a4, and that file records the next
 * object base as 0x5a8 higher -- the same exact-fit argument it used to size
 * DAT_00eb1a78 and DAT_00eb1698.  So the blocker is no longer the size; it is
 * coalescing the split-out neighbours into the one object.  That is the
 * split-struct job (the g_inputEventRing / g_replayContext class), and it has
 * to land before this argument can be passed.
 */
#include "ghidra_types.h"


void FUN_004ee120(void)

{
  undefined4 *in_EAX;
  
  in_EAX[2] = DAT_00557328;
  in_EAX[3] = DAT_0055732c;
  in_EAX[4] = DAT_00557330;
  in_EAX[5] = DAT_00557334;
  in_EAX[1] = 0;
  *(undefined1 *)((int)in_EAX + 0x4b) = 0;
  *(undefined1 *)((int)in_EAX + 0x4a) = 0;
  *(undefined1 *)((int)in_EAX + 0x49) = 0;
  *(undefined1 *)(in_EAX + 0x12) = 0;
  in_EAX[0x13] = 0;
  in_EAX[0x14] = 10;
  *(undefined1 *)(in_EAX + 0x15) = 0;
  *in_EAX = &PTR_FUN_00557484;
  in_EAX[0x165] = 0;
  in_EAX[0x163] = 0;
  in_EAX[0x164] = 799;
  in_EAX[0x166] = 599;
  in_EAX[0x167] = 400;
  in_EAX[0x168] = 300;
  *(undefined1 *)(in_EAX + 0x169) = 1;
  in_EAX[0x1a] = 0;
  in_EAX[0x1b] = 0;
  in_EAX[0x1c] = 0;
  in_EAX[0x1d] = 0;
  in_EAX[0x1e] = 0;
  in_EAX[0x1f] = 0;
  in_EAX[0x20] = 0;
  in_EAX[0x21] = 0;
  return;
}

