/* FUN_0044c740 - 0x0044c740 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the same two-cell copy as FUN_0042aeb0 with the bases in registers - source EBX (unaff_EBX), dest ESI - at +8 and +0x22c.
 *
 * REGISTERS PROMOTED (2026-08-27).  Both bases were dropped and all three
 * call sites passed nothing.  The record is 0x450 bytes -- fixed
 * independently by FUN_0050a320.cpp's own `unsigned char local_45c[1104]`,
 * which is the destination at one of those sites -- and every caller walks
 * an array of them with an `add esi,0x450` stride.
 *
 * ESI is the destination and EBX the source, which the body already showed
 * (`*(unaff_ESI + 4) = *(unaff_EBX + 4)`) and each call site confirms
 * separately: FUN_0044c630 sets ESI to `uVar1*0x450 + *(int *)param_1` and
 * derives EBX from it by a constant delta; FUN_0050cff0 sets ESI from its
 * own loop counter over `*param_1` and takes EBX straight from param_3; and
 * FUN_0050a320 points ESI at the local_45c scratch record and EBX at
 * `this->[0x94]*0x450 + *(g_clientContext + 0x44e20)`.
 */
#include "ghidra_types.h"


void FUN_0044c740(int dstRecord,int srcRecord)

{
  undefined4 uVar1;
  int unaff_EBX = srcRecord;
  int unaff_ESI = dstRecord;
  
  CopyGuardedBool((byte *)unaff_ESI,(byte *)unaff_EBX);
  *(undefined4 *)(unaff_ESI + 4) = *(undefined4 *)(unaff_EBX + 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 8));
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x44c76a
   * (`lea edi,[esi + 8]`, esi = this file's own `unaff_ESI`, already
   * used as a base pointer above for the `unaff_ESI + 4` write): cell is
   * unaff_ESI+8, matching the same 8/0x22c cell-offset pair confirmed
   * (via tableHandle zero-writes) in the sibling constructors
   * FUN_00428550.c/FUN_0042aeb0.c. `unaff_ESI` is plain `int`, so byte
   * offsets add directly. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(unaff_ESI + 8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0x22c));
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x44c793
   * (`lea edi,[esi + 0x22c]`, esi = unaff_ESI): cell is unaff_ESI+0x22c,
   * the paired second cell offset for this same class. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(unaff_ESI + 0x22c, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return;
}

