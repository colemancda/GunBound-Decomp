/* FUN_004217b0 - 0x004217b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): takes the client
 * context in EAX (`mov esi,eax`, dropped) plus one stack argument.  It peeks
 * ctx + 0xeb854 (a selector), adds the stack argument, reduces the sum mod
 * 0x400 (signed, 0x4217ea-0x4217f9), scales by 0x224 and peeks that cell of
 * the ctx + 0x62854 array - the same selector/array pair
 * State11_InBattle_RenderHud reads.  Ghidra DISCARDED the first peek's result
 * (bare call), so it is captured into uVar1 here.  All 11 callers are in
 * FUN_0041f200 and pass 0/1/2 as the offset; they were arg-less on the ctx and
 * are fixed alongside.
 */
#include "ghidra_types.h"


undefined4 FUN_004217b0(int ctx,undefined4 param_1)

{
  undefined4 uVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState((void *)(ctx + 0xeb854));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState((void *)(ctx + ((int)uVar1 + (int)param_1) % 0x400 * 0x224 + 0x62854));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return uVar1;
}

