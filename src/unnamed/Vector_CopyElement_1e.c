/* Vector_CopyElement_1e - 0x00503770 in the original binary.
 *
 * Copies one 0x11-byte name key: the length byte at +0x11 first, then that
 * many bytes of text.  The same key record HashStringNoCase hashes.
 *
 * DROPPED-REG FIX (2026-08-28), and a correction to the line above: this
 * is the whole 0x1e-byte ELEMENT copy of the 0x1e vector family - the
 * exact twin of Vector_CopyElement_34 one stride down - not just a key
 * copy. It moves two counted strings (at +0 with the length at +0x11,
 * at +0x12 with the length at +0x1b) plus the trailing word at +0x1c:
 * 0x1e bytes, the stride its own family walks. EAX is the DESTINATION,
 * read at 0x503774 before any write. ECX is a PHANTOM: `push ecx` at
 * 0x503770 is balanced by `pop ecx` at 0x5037cb and CL's first touch is
 * the write at 0x503771. Bare ret, no [esp+N] reads - EAX and EDX are
 * the whole input. Its one call site is Vector_InsertN_1e's
 * copy-construction of the by-value element into [ebp-0x34], from that
 * function's newly declared regEdx.
 */
#include "ghidra_types.h"


void __fastcall Vector_CopyElement_1e(undefined4 param_1,undefined4 *param_2,undefined4 *regEax)

{
  byte bVar1;
  undefined4 *in_EAX = regEax;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  bVar1 = *(byte *)((int)param_2 + 0x11);
  *(byte *)((int)in_EAX + 0x11) = bVar1;
  puVar3 = param_2;
  puVar4 = in_EAX;
  for (uVar2 = (uint)(bVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  for (uVar2 = bVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  *(undefined1 *)((uint)bVar1 + (int)in_EAX) = 0;
  bVar1 = *(byte *)((int)param_2 + 0x1b);
  *(byte *)((int)in_EAX + 0x1b) = bVar1;
  puVar3 = (undefined4 *)((int)param_2 + 0x12);
  puVar4 = (undefined4 *)((int)in_EAX + 0x12);
  for (uVar2 = (uint)(bVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  for (uVar2 = bVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    puVar4 = (undefined4 *)((int)puVar4 + 1);
  }
  *(undefined1 *)((uint)bVar1 + (int)in_EAX + 0x12) = 0;
  *(undefined2 *)(in_EAX + 7) = *(undefined2 *)(param_2 + 7);
  return;
}

