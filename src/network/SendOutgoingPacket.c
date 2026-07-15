/* SendOutgoingPacket - 0x004d2680 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Dropped-argument fix: Ghidra emitted the client-context/channel `this`
 * pointer (the same base used throughout src/ for +0x44d0 length-cursor,
 * +0x4d0 packet buffer, +0x84e0 socket handle, etc. - see globals.h's
 * DAT_007934e8/DAT_007934ec comment) as a bare `unaff_ESI` read instead of
 * a real parameter. Confirmed via objdump of orig/GunBound.gme: every
 * sampled call site (e.g. 0x401238, 0x4028c9, 0x402a93, 0x402fb2, 0x403a37)
 * loads/keeps that same context pointer in ESI immediately before `call
 * 0x4d2680` with no intervening write to ESI, and the function itself reads
 * [esi+0x44d0] as its very first instruction with no preceding `mov esi,...`
 * - i.e. ESI is live-in, not a dropped global. Promoted to an explicit
 * parameter; functions.h's prototype is left K&R-empty so any not-yet-
 * updated call sites still compile. Every real call site under src/ has
 * been updated to pass the context pointer that was live at that point
 * (almost always DAT_007934e8 or a local copy of it taken shortly before).
 *
 * FIXED (2026-07-14): the trailing SendSocketData call only passed 2 of
 * its 3 real args and dropped the buffer ("this") entirely. Confirmed via
 * angr disassembly at 0x4d27a3-0x4d27b7: `lea ecx,[esi+0x4d0]` (buffer,
 * this) / `push eax` where eax=[esi+0x84e0] (connection object, param_2) /
 * `push edx` where edx=[esi+0x44d0] (length, param_3) - the outgoing
 * packet buffer lives at context+0x4d0 (the length-cursor at +0x44d0 is a
 * separate field, matching this file's own header comment above).
 */
#include "ghidra_types.h"


undefined4 SendOutgoingPacket(int param_1)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_45c [8];
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;

  local_4 = 0xffffffff;
  puStack_8 = &LAB_00540806;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  iVar1 = *(int *)(param_1 + 0x44d0);
  *(undefined2 *)(param_1 + 0x4d0) = *(undefined2 *)(param_1 + 0x44d0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar3 + iVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = EncodeChecksumDeltaMul(param_1 + 0x84,local_230,0x343fd);
  local_4 = 0;
  EncodeChecksumDeltaAdd(uVar4,local_454,0x269ec3);
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  *(undefined2 *)(param_1 + 0x4d2) = uVar2;
  if (local_440 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_45c);
  }
  local_4 = 0xffffffff;
  if (local_21c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_45c);
  }
  SendSocketData((char *)(param_1 + 0x4d0),*(undefined4 *)(param_1 + 0x84e0),
                 *(undefined4 *)(param_1 + 0x44d0));
  *(undefined4 *)(param_1 + 0x84ec) = 0;
  *unaff_FS_OFFSET = local_c;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

