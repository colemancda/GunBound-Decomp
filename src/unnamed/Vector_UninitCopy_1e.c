/* Vector_UninitCopy_1e - 0x005046b0 in the original binary.
 *
 * Named above (2026-08-28, from its Vector_*_34 twin), but still a
 * raw/near-verbatim port of Ghidra's decompiler output, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 *
 * DROPPED-REG FIX (2026-08-28): the 0x1e twin of Vector_UninitCopy_34 -
 * VC7.1's _Uninit_copy, constructing [param_2, param_3) into raw
 * storage at regEax and returning the destination end.
 *
 * ECX -> param_1  PHANTOM: first touch is the write `mov cl,[edx+0x11]`
 *                 at 0x5046c4.
 * EDX -> param_2  the source cursor, compared against param_3 at entry
 *                 (`cmp edx,[esp+4]` at 0x5046b0, depth 0) and at the
 *                 loop tail (`mov ecx,[esp+0x14]` at 0x504711, four
 *                 pushes deep) - the same slot at two depths, the
 *                 two-way pin of the frame model.
 * [esp+4]
 *     -> param_3  the source END.
 * [esp+8]
 *     -> param_4  the never-read allocator word; pushed and cleaned by
 *                 every caller, read by nothing.
 * EAX -> regEax   the destination cursor and the RETURN VALUE - every
 *                 caller consumes the advanced EAX (Vector_InsertN_1e
 *                 stores it as the new end or feeds it to the fill).
 */
#include "ghidra_types.h"


undefined4 __fastcall Vector_UninitCopy_1e(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,
                                   undefined4 param_4,undefined4 *regEax)

{
  byte bVar1;
  undefined4 *in_EAX = regEax;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  for (; param_2 != param_3; param_2 = (undefined4 *)((int)param_2 + 0x1e)) {
    if (in_EAX != (undefined4 *)0x0) {
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
      *(undefined1 *)((int)in_EAX + (uint)bVar1) = 0;
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
      *(undefined1 *)(bVar1 + 0x12 + (int)in_EAX) = 0;
      *(undefined2 *)(in_EAX + 7) = *(undefined2 *)(param_2 + 7);
    }
    in_EAX = (undefined4 *)((int)in_EAX + 0x1e);
  }
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

