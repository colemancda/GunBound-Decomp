/* FUN_004fd3b0 - 0x004fd3b0 in the original binary.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x5575c8, SLOT 0 of the CommP2P owner's primary vtable
 * (ConstructCommP2POwner stores 0x5575c8 at owner+0; value read from the
 * original .data). Extent 0x4fd3b0-0x4fd3b6 (7 bytes, then int3
 * padding to the next slot, CommP2POwner_Release at 0x4fd3c0).
 *
 * `inc dword ptr [ecx+0x1a6c]` / `ret`: __thiscall, ECX = the owner, no
 * stack arguments. +0x1a6c is the refcount ConstructCommP2POwner seeds
 * with 1 (param_1[0x69b]) and CommP2POwner_Release (slot 1) decrements:
 * this is the AddRef half of the pair. Left unnamed. Erased __thiscall:
 * `this` is the first cdecl argument.
 */
#include "ghidra_types.h"


void FUN_004fd3b0(int param_1)

{
  *(int *)(param_1 + 0x1a6c) = *(int *)(param_1 + 0x1a6c) + 1;
  return;
}
