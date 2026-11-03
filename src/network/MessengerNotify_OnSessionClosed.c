/* MessengerNotify_OnSessionClosed - 0x00403890 in the original binary.
 *
 * NAMING (batch 22, was FUN_00403890): Slot 1 of the notify interface
 * 0x551cb8; CommP2POwner_OnConnectionClosed calls it on the session
 * handler ([owner+0x1aac], vtable +4) and it sets the closed flag at
 * +0x1bc4.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x551cbc, SLOT 1 of the messenger's notify interface
 * 0x551cb8. Extent 0x403890-0x4038ac (29 bytes, plain `ret`).
 *
 * __thiscall, ECX = this (the interface at ctx+8), no stack arguments:
 *   cmp dword ptr [ecx+0x1bc8],0x2710   ; 0x403890
 *   mov byte ptr [ecx+0x1bc4],1         ; 0x40389a (mov leaves the flags)
 *   je  0x4038ad                         ; was 0x2710 -> keep it
 *   mov dword ptr [ecx+0x1bc8],0         ; else clear it
 * This is the call CommP2POwner_OnConnectionClosed makes on the session
 * handler (ECX = [this+0x1aac], `call [vtbl+4]`) - its header already
 * records the bytes. Erased __thiscall: this first.
 */
#include "ghidra_types.h"


void MessengerNotify_OnSessionClosed(int param_1)

{
  int iVar1;

  iVar1 = *(int *)(param_1 + 0x1bc8);
  *(undefined1 *)(param_1 + 0x1bc4) = 1;
  if (iVar1 != 0x2710) {
    *(undefined4 *)(param_1 + 0x1bc8) = 0;
  }
  return;
}
