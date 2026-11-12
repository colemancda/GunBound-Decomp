/* ReplayContext_ClearSlot - 0x004e7560 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e7560 mean this function.)
 *
 * NAMED (batch 48), LIKELY. Empties one of the g_replayContext object's 8
 * per-player slots. Its sole caller, WriteReplayEventRecord, calls it with
 * EDX = &g_replayContext and ESI = the slot byte in the 0x3020
 * (GB_OP_USER_QUIT_NOTIFICATION) branch, right after the room's per-slot
 * active byte at client context +0x45914 + slot is zeroed for the
 * departing user. It clears bit slot in both bitsets at +0x138/+0x140 (the
 * two bitsets SetSlot sets/clears) and zeroes the slot's two 0x200-byte
 * areas at +0x40bd8/+0x42de0 and its three per-slot bytes at
 * +0x3c0/+0x3c8/+0x454e4, exactly the bytes ReplayContext_SetSlot
 * initialises. LIKELY: the slot meaning rests on the room-slot usage at
 * the call site and the SetSlot pairing, not on a named field.
 *
 * ARGUMENTS FILLED.  `ret 0` puts nothing on the stack, so param_1 (ECX) and
 * param_2 (EDX) are both registers and the sole call site passed neither.
 * ECX is a PHANTOM -- the entry writes it (`mov ecx,esi`) before any read --
 * so it takes 0; EDX is &g_replayContext.
 *
 * EBX, ESI and EDI are read before being written here too, so they are
 * further register arguments Ghidra did not declare.  They stay open.
 */
#include "ghidra_types.h"


void __fastcall ReplayContext_ClearSlot(undefined4 param_1,int param_2,uint regEsi)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  if ((int)regEsi < 8) {
    if (7 < regEsi) {
                    /* WARNING: Subroutine does not return */
      Bitset_ThrowInvalidPosition();
    }
    iVar2 = (regEsi >> 5) * 4;
    uVar4 = ~(1 << ((byte)regEsi & 0x1f));
    *(uint *)(iVar2 + 0x140 + param_2) = *(uint *)(iVar2 + 0x140 + param_2) & uVar4;
    puVar1 = (uint *)(iVar2 + 0x138 + param_2);
    *puVar1 = *puVar1 & uVar4;
    iVar2 = regEsi * 0x200 + param_2;
    puVar5 = (undefined4 *)(iVar2 + 0x42de0);
    for (iVar3 = 0x80; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    puVar5 = (undefined4 *)(iVar2 + 0x40bd8);
    for (iVar3 = 0x80; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    *(undefined1 *)(regEsi + 0x3c0 + param_2) = 0;
    *(undefined1 *)(regEsi + 0x3c8 + param_2) = 0;
    *(undefined1 *)(regEsi + 0x454e4 + param_2) = 0;
  }
  return;
}

