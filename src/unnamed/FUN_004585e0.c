/* FUN_004585e0 - 0x004585e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: the +0x6ac/+0x488 pair (0x4585f7/0x458618) off the live-in ESI the file already declares as unaff_ESI (int *, so /4), feeding CalculateAngleFromDelta.  The worklist's 10 sites overrun into the neighbouring function; this one owns two.
 */
#include "ghidra_types.h"


void FUN_004585e0(void)

{
  int iVar1;
  /* FIXED (2026-07-15): this file's decompile never surfaced unaff_ESI
   * as a variable because EVERY use of it in this function is as a
   * dropped-self-arg to a K&R-declared callee (PeekPacketChecksumState
   * at 0x40a2e0 also drops its self arg the same way, out of scope
   * here); objdump of orig/GunBound.gme confirms esi is never assigned
   * anywhere in this function, i.e. it's the incoming register value at
   * entry, same convention as unaff_ESI in sibling files (e.g.
   * FUN_0047fee0.c, FUN_0047c040.c). Declared here to name the
   * EncodeOutgoingPacketField cell below. */
  int *unaff_ESI;

  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(unaff_ESI + 0x1ab));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(unaff_ESI + 0x122));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = CalculateAngleFromDelta();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x458675
   * (`lea edi,[esi+0x1c2c]`, esi = unaff_ESI per the note above).
   * unaff_ESI is `int *` (scales by 4), so the byte offset is taken via
   * `(int)unaff_ESI + 0x1c2c`. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)unaff_ESI + 0x1c2c, ((iVar1 + 1) / 3) * 3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return;
}

