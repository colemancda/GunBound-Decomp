/* FUN_0044c740 - 0x0044c740 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0044c740(void)

{
  undefined4 uVar1;
  int unaff_EBX;
  int unaff_ESI;
  
  RescrambleGuardedBool();
  *(undefined4 *)(unaff_ESI + 4) = *(undefined4 *)(unaff_EBX + 4);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x44c76a
   * (`lea edi,[esi + 8]`, esi = this file's own `unaff_ESI`, already
   * used as a base pointer above for the `unaff_ESI + 4` write): cell is
   * unaff_ESI+8, matching the same 8/0x22c cell-offset pair confirmed
   * (via tableHandle zero-writes) in the sibling constructors
   * FUN_00428550.c/FUN_0042aeb0.c. `unaff_ESI` is plain `int`, so byte
   * offsets add directly. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(unaff_ESI + 8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x44c793
   * (`lea edi,[esi + 0x22c]`, esi = unaff_ESI): cell is unaff_ESI+0x22c,
   * the paired second cell offset for this same class. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(unaff_ESI + 0x22c, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

