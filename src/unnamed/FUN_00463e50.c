/* FUN_00463e50 - 0x00463e50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00463e50(void)

{
  undefined4 uVar1;
  int unaff_ESI;
  
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x463e72/
   * 0x463e99/0x463ebe/0x463edf/0x463f04/0x463fd5/0x464000/0x464025/
   * 0x46404a (edi loaded from esi+0x90c/esi+0x15e4/esi+0xb30/esi+0x1808/
   * esi+0x1c54/esi+0x6fd4/esi+0x4d90/esi+0x51d8/esi+0x4948 respectively).
   * esi is this file's own `unaff_ESI` (the base already used for the
   * byte copies below, e.g. `unaff_ESI + 0x24`); `unaff_ESI` is plain
   * `int`, so `unaff_ESI + N` is already byte-precise. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(unaff_ESI + 0x90c, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(unaff_ESI + 0x15e4, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(unaff_ESI + 0xb30, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(unaff_ESI + 0x1808, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(unaff_ESI + 0x1c54, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(unaff_ESI + 0x24) = *(undefined4 *)(unaff_ESI + 0xc91c);
  *(undefined4 *)(unaff_ESI + 0x28) = *(undefined4 *)(unaff_ESI + 0xc920);
  *(undefined4 *)(unaff_ESI + 0x30) = *(undefined4 *)(unaff_ESI + 0xc928);
  *(undefined4 *)(unaff_ESI + 0x2c) = *(undefined4 *)(unaff_ESI + 0xc924);
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  RescrambleGuardedBool();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(unaff_ESI + 0x6fd4, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_0045ba50(unaff_ESI);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(unaff_ESI + 0x4d90, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(unaff_ESI + 0x51d8, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(unaff_ESI + 0x4948, uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

