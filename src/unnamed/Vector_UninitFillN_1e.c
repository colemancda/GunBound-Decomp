/* Vector_UninitFillN_1e - 0x00504270 in the original binary.
 *
 * Named above (2026-08-28, from its Vector_*_34 twin), but still a
 * raw/near-verbatim port of Ghidra's decompiler output, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 *
 * DROPPED-REG FIX (2026-08-28): the 0x1e twin of Vector_UninitFillN_34 -
 * VC7.1's _Uninit_fill_n, constructing param_1 copies of one element
 * into raw storage via the element copy.
 *
 * ECX -> param_1  the COUNT: `push ecx / test ecx / jbe exit` is the
 *                 function's opening, and the loop decrements it.
 * EDX -> param_2  the source element.
 * [esp+4]
 *     -> param_3  the never-read allocator word of the STL shape: every
 *                 caller pushes it and clears it with `add esp,4`, and
 *                 no instruction in the body reads above the frame.
 * EAX -> regEax   the destination cursor, advanced 0x1e per element;
 *                 read at 0x504280 (`test eax,eax`) before any write.
 *
 * Both Vector_InsertN_1e sites and the Vector_PushBack_1e push_back fast path
 * were mis-slotted - each passed one value that landed in ECX where the
 * count belongs.
 */
#include "ghidra_types.h"


void __fastcall Vector_UninitFillN_1e(int param_1,undefined4 *param_2,undefined4 param_3,
                             undefined4 *regEax)

{
  byte bVar1;
  undefined4 *in_EAX = regEax;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  for (; param_1 != 0; param_1 = param_1 + -1) {
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
  return;
}

