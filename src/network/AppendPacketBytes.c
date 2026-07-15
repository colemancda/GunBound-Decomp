/* AppendPacketBytes - 0x004d2530 in the original binary.
 *
 * Copies `count` bytes from `src` into the growing outgoing-packet
 * buffer on object `self` (write cursor + buffer base both live at
 * `self+0x44d0`/`self+0x4d0`), then advances the cursor by `count`.
 * `self` was dropped as `in_EAX` (confirmed via direct disassembly of
 * this function's own body at 0x4d2530: EAX=self, EDX=count/param_2,
 * stack=src/param_3 - the real fastcall convention plus one extra
 * non-standard register, same bug class as DrawHLine/ClampCursorToRect/
 * FindGroundHeightAtColumn). `param_1` is genuinely dead (overwritten
 * before any read). Raw/near-verbatim port of Ghidra's decompiler
 * output otherwise, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall AppendPacketBytes(undefined4 param_1,int self,uint param_2,undefined4 *param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;

  uVar1 = ((int)param_2 < 0) - 1 & param_2;
  puVar3 = (undefined4 *)(*(int *)(self + 0x44d0) + 0x4d0 + self);
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar3 = *param_3;
    param_3 = param_3 + 1;
    puVar3 = puVar3 + 1;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar3 = *(undefined1 *)param_3;
    param_3 = (undefined4 *)((int)param_3 + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  *(uint *)(self + 0x44d0) = *(int *)(self + 0x44d0) + param_2;
  return;
}

