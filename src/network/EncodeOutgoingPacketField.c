/* EncodeOutgoingPacketField - 0x0040a380 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* `self` is the object pointer Ghidra dropped as `unaff_EDI`: the original
 * passes `this` in EDI (a custom register convention, callee cleans the one
 * stack arg via `ret 4` at 0x40a43a). Recovered from the real binary - every
 * caller is `mov edi,<obj>; call 0x40a380`. Made an explicit leading parameter
 * so callers can pass it; other (not-yet-swept) 1-arg call sites still compile
 * against the K&R decl in functions.h.
 *
 * 2026-07-13 scope correction (round 2 - the round-1 note below undersold
 * it): `grep -rn "EncodeOutgoingPacketField("` across the whole tree finds
 * **2070 call sites in ~230 files**, not 171 in 13 - the zero-arg grep
 * pattern only caught calls missing BOTH arguments; there are also 1877
 * one-arg call sites (e.g. `EncodeOutgoingPacketField(uVar2);`) missing
 * only `self`, which is functionally the identical bug (uninitialized EDI
 * read) but invisible to a `EncodeOutgoingPacketField()`-shaped grep. Only
 * 21 call sites in the whole tree are already correct.
 *
 * Ran an angr CFG backward-scan + whole-function backward register taint
 * over all 2102 predecessors of 0x40a380 (tools/scan_encodeoutgoingpacket
 * field.py, cached in tools/encodeoutgoingpacketfield_sites.json) to
 * recover the dropped EDI value at each site: 2055/2102 resolved (either a
 * literal `lea edi,[base+offset]`/`mov edi,[stack]`, or a `<clobbered:add
 * edi,N>` one-step-further trace), only 47 fully unresolved. The
 * per-caller pattern is highly mechanical - nearly every site is `lea
 * edi,[<existing this-like base register>+<fixed offset>]` where the base
 * is almost always a parameter or local the caller's own decompiled C
 * already names.
 *
 * BUT: spot-checking the 13 files from the original (undersold) scope
 * note found several - e.g. FUN_0041da80.c (406 lines) - where Ghidra's
 * decompile is severely corrupted well beyond just this one dropped
 * argument (dozens of zero-arg calls to unrelated functions like
 * EncodeGuardedBool()/TreeLowerBound()/ScrambleChecksumGuardBytes(),
 * inconsistent indirect `(*pcVar5)()` calls, raw `stack0xfffffbNN`
 * artifacts). Mechanically inserting the angr-resolved `self` value into
 * those calls without also reconstructing the surrounding control flow
 * would leave the function just as wrong, in a different way - the same
 * "confirm via disassembly, don't patch on suspicion" standard used
 * throughout this project applies here. Several of the 13 files are 800-
 * 2000+ lines each (FUN_004513b0.c 977, FUN_004a2ce0.c 822, FUN_004af7a0.c
 * 807, FUN_004a4950.c 806, FUN_00495e80.c 806, State11_InBattle_OnTick.c
 * 2039) - fixing all of them properly is multiple sessions' worth of
 * FUN_00405ba0.c-style full reconstruction, not a single mechanical pass.
 * Not attempted here; the cached JSON should let a dedicated follow-up
 * skip the expensive CFG/taint step and go straight to per-file
 * reconstruction, file by file, verifying each via disassembly before
 * editing.
 *
 * FIXED (2026-07-15): the `if ((int *)*puVar3 != DAT_00793774)` guard
 * after FUN_0040b8c0() dereferenced `puVar3`, a local NEVER assigned
 * anywhere in this function - a genuine uninitialized-pointer read that
 * could crash unpredictably any time DAT_00793778 != 0 took this branch
 * (live-reproduced: a jump-to-NULL crash once SendOutgoingPacket's first
 * real call started exercising this path). Per this file's own prior
 * note, FUN_0040b8c0 is void-returning and this comparison was always a
 * Ghidra decompilation artifact, not real original behavior - removed
 * the same way entry/WinMain.c's FUN_004058c0 call site was fixed
 * (call kept for its side effects, the bogus post-call check dropped). */
void EncodeOutgoingPacketField(void *self, uint param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar4;
  uint *puVar5;
  int unaff_EDI = (int)self;
  undefined1 local_8 [8];

  uVar2 = param_1;
  uVar1 = *(uint *)(unaff_EDI + 0x14);
  if (uVar1 != 0) {
    ScrambleChecksumGuardBytes();
    param_1 = uVar1;
    TreeLowerBound(local_8);
  }
  if (DAT_00793778 == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = *(int *)(*DAT_00793774 + 0xc);
    FUN_0040b600(&DAT_00793770,&param_1,*DAT_00793774);
  }
  *(int *)(unaff_EDI + 0x14) = iVar4;
  if (iVar4 != 0) {
    param_1 = iVar4;
    FUN_0040b8c0();
  }
  puVar5 = (uint *)(iVar4 * 0x10 + DAT_0079376c);
  *(uint *)(unaff_EDI + 4) = *puVar5 ^ uVar2;
  *(uint *)(unaff_EDI + 8) = puVar5[1] ^ uVar2;
  *(uint *)(unaff_EDI + 0xc) = puVar5[2] ^ uVar2;
  *(uint *)(unaff_EDI + 0x10) = puVar5[3] ^ uVar2;
  return;
}

