/* CommP2POwner_AddRef - 0x004fd3b0 in the original binary.
 *
 * NAMING (batch 22, was FUN_004fd3b0): Slot 0 of the CommP2P owner vtable
 * 0x5575c8; increments the refcount at owner+0x1a6c that
 * ConstructCommP2POwner seeds with 1 and slot 1 (CommP2POwner_Release)
 * decrements.
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
 * this is the AddRef half of the pair. Erased __thiscall:
 * `this` is the first cdecl argument.
 */
#include "ghidra_types.h"


void CommP2POwner_AddRef(int param_1)

{
  *(int *)(param_1 + 0x1a6c) = *(int *)(param_1 + 0x1a6c) + 1;
  return;
}
