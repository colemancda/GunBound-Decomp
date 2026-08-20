/* QueueBroadcastEvent - 0x004e6c90 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * DROPPED REGISTER ARGUMENT RECOVERED (2026-08-20).  Everything this function
 * touches hangs off a base that arrived in ESI and that Ghidra modelled as an
 * uninitialised local - the critical section at +0x198, the 0x200-byte event
 * buffer at +0x44dec, the sequence counter at +0x45204.  With nothing
 * supplying it, the port was entering a CRITICAL SECTION at a garbage address
 * and then zeroing 0x200 bytes there.
 *
 * All 110 direct call sites were scanned: 105 do `mov esi, 0xe55ce0`, which
 * this tree already knows as g_replayContext, the battle/replay turn-event
 * buffer sized in globals_sized.c - and whose header already records that
 * FUN_004e84c0/4e7b60/4e80d0/4e77e0/4e7de0/4e6050 all take &g_replayContext
 * as their context argument.  This is the same subsystem and the same base.
 *
 * The 5 sites that do not load the literal take it from a register instead
 * (ebx, ecx, ebp) and live in just three callers - FUN_004e6160, FUN_004e6770
 * and FUN_004e7de0.  Those three files are excluded from the sweep rather
 * than assumed: FUN_004e7de0 is on the list above as a function that RECEIVES
 * the context, so its ESI is its own parameter being forwarded, which may or
 * may not be this global at run time.
 *
 * functions.h deliberately keeps the K&R-empty declaration rather than a full
 * prototype: 9 call sites still pass no arguments at all, and a real prototype
 * would turn those into build errors before there is anything to fix them
 * with.  Same partial-promotion arrangement as FindSpriteFrame.
 */
#include "ghidra_types.h"
#include <windows.h>


void QueueBroadcastEvent(int param_1,int replayCtx)

{
  int iVar1;
  undefined4 *puVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(replayCtx + 0x198));
  puVar2 = (undefined4 *)(replayCtx + 0x44dec);
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(char *)(replayCtx + 0x44df4) = *(char *)(replayCtx + 0x45204);
  *(char *)(replayCtx + 0x45204) = *(char *)(replayCtx + 0x45204) + '\x01';
  *(undefined2 *)(replayCtx + 0x44dee) = param_1;
  *(undefined1 *)(replayCtx + 0x44df1) = *(undefined1 *)(replayCtx + 0x14c);
  *(undefined4 *)(replayCtx + 0x44df5) = *(undefined4 *)(replayCtx + 0x15d);
  *(undefined4 *)(replayCtx + 0x44df9) = *(undefined4 *)(replayCtx + 0x161);
  *(undefined4 *)(replayCtx + 0x44dfd) = *(undefined4 *)(replayCtx + 0x165);
  *(undefined4 *)(replayCtx + 0x44fec) = 0x21;
  *(undefined1 *)(replayCtx + 0x44ff4) = 0;
  return;
}

