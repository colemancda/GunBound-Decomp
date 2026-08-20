/* PostTurnEvent - 0x004e7d30 in the original binary.
 *
 * SIGNATURE FIX (2026-08-19): this was declared `PostTurnEvent(void)` while
 * the original is `ret 8` = TWO stack arguments, and every call site passes
 * two - `PostTurnEvent(&g_replayContext, 0xc302)` and friends.  Found by
 * tools/retn_signature_audit.py.  The two parameters are now declared.
 *
 * WHAT THE BODY DOES, and what is still dropped.  The whole function is a
 * forward into FUN_004e86f0 (orig 0x4e7d30-0x4e7d4f):
 *     sub esp,8 / push ebx
 *     lea eax,[esp+4] / push eax        <- the out-slot, the ONLY argument
 *                                          the decompile kept
 *     mov eax,[esp+0x14] / add eax,0x45230   <- EAX = param_1 + 0x45230
 *     lea ebx,[esp+0x18]                     <- EBX = &param_2
 *     call 0x4e86f0 / ret 8
 * FUN_004e86f0 is a std::set<ushort>::insert: it takes the set in EAX, a
 * POINTER to the 16-bit key in EBX, and the out-slot (a pair<iterator,bool>)
 * as its one stack argument - it writes the node to *out and the inserted
 * flag to out[1].  Ghidra modelled the two register arguments as `in_EAX`
 * and `unaff_EBX`, so they arrive as garbage today.
 *
 * FIXED the same day across all 22 call sites: FUN_004e86f0 now takes the set
 * and the key pointer as real parameters.  The per-site work was recovering
 * the key local, which the decompile had dropped entirely in three of them
 * (State10_Loading_OnEnter x2, FUN_00423a20) and whose out-slot it had
 * dropped in eight more (State11_InBattle_OnTick).
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


void PostTurnEvent(int param_1,undefined4 param_2)

{
  undefined1 local_8 [8];
  
  /* orig 0x4e7d39-0x4e7d46: EAX = param_1 + 0x45230 (the event set - the same
   * 0xe9af10 every other call site passes as a literal) and EBX = &param_2
   * (the 16-bit event code).  Both were dropped by the decompile; both are
   * now passed. */
  FUN_004e86f0((undefined4 *)local_8,param_1 + 0x45230,(ushort *)&param_2);
  return;
}

