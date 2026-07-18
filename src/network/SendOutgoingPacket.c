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
  undefined1 local_45c [8];
  /* UNDER-SIZED STACK BUFFER FIX (2026-07-16): these two are CValueGuard
   * cells (0x224 bytes each, = GB_VG_OBJ_SIZE in winmain_bringup.h), NOT
   * the 20-byte arrays Ghidra emitted. Ghidra split each cell into a small
   * array plus a separate int for the field at its +0x14, which the real
   * callees then overran: EncodeChecksumDeltaAdd (0x410010+0x4a/+0x51) and
   * EncodeChecksumDeltaMul (0x410210+0x5a) both do
   * `movb $0,0x220(%esi); movl $0,0x14(%esi)` on the cell handed to them -
   * i.e. they write 0x220 bytes past a 20-byte local, smashing this
   * function's own return address to 0. That made GameTick's OnTick call
   * chain `ret` to 0 (EIP=0) as soon as State02_ServerSelect_OnTick sent
   * the server-directory request, which is why the broker's reply was
   * never read. The original frame proves the real size: Ghidra's own
   * offsets put local_454 at -0x454 and local_230 at -0x230 (0x224 apart),
   * local_230 to local_c is another 0x224, and local_440/local_21c sit
   * exactly at cell+0x14 (-0x454+0x14 = -0x440). Both former ints are now
   * read through their cell, so the zero-writes above are observed. */
  undefined1 local_454 [0x224];
  undefined1 local_230 [0x224];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;

  /* DROPPED-SEH-FRAME FIX (2026-07-17): Ghidra decompiled the original's
   * Windows SEH (__except) frame push (FS:[0] chain, handler LAB_00540806)
   * as reads/writes through an UNINITIALISED `unaff_FS_OFFSET` pointer -
   * the recompiled code wrote through garbage and faulted at +0x1a
   * (`mov [ebx],ecx` with wild EBX) as soon as ServerSelect's OnTick sent
   * the first broker request under the virtual desktop. Stripped entirely,
   * same as ProcessIncomingPackets'/WriteReplayEventRecord's identical fix.
   * local_4/local_c/puStack_8 kept only where reused as real locals. */
  local_4 = 0xffffffff;
  (void)local_c; (void)puStack_8;
  iVar1 = *(int *)(param_1 + 0x44d0);
  *(undefined2 *)(param_1 + 0x4d0) = *(undefined2 *)(param_1 + 0x44d0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4d26bd
   * (`lea edi,[esi+0x84]`, esi = this file's own param_1) the cell is
   * param_1+0x84, the SAME cell already passed explicitly to
   * EncodeChecksumDeltaMul 2 lines below - see
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x84, iVar3 + iVar1);
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
  if (*(int *)(local_454 + 0x14) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_45c);
  }
  local_4 = 0xffffffff;
  if (*(int *)(local_230 + 0x14) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_45c);
  }
  SendSocketData((char *)(param_1 + 0x4d0),*(undefined4 *)(param_1 + 0x84e0),
                 *(undefined4 *)(param_1 + 0x44d0));
  *(undefined4 *)(param_1 + 0x84ec) = 0;
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

