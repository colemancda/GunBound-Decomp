/* Vector_UninitFillN_12 - 0x00504110 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00504110).  VC7.1's _Uninit_fill_n
 * for the 0x12-byte element vector: copy-construct ECX copies of the
 * element at EBX into raw storage starting at EAX, stepping 0x12. Same
 * opening as Vector_UninitFillN_1e (`push ecx / test ecx / jbe exit`,
 * the count decremented in the pushed slot), same placement-new null
 * test on the destination, and the element copy is the counted 18-byte
 * name record (length byte at +0x11, NUL at +len) that
 * Vector_UninitCopy_12 copies too.
 *
 * Its three call sites are the three places push_back/_Insert_n use
 * _Uninit_fill_n, which is what fixes the name from outside:
 *   0x5027a6  FUN_00502750 (push_back) - count 1 at the old _Mylast,
 *             immediately followed by `add esi,0x12 / mov [edi+8],esi`
 *   0x502cb4  FUN_00502b70 (_Insert_n), realloc arm - n copies at the
 *             address the head Vector_UninitCopy_12 returned
 *   0x502daa  FUN_00502b70, append-overlap arm - the remainder
 *             n - (_Mylast - _Where)/0x12 at the old _Mylast
 *
 * REGISTER ARGUMENTS RECOVERED (2026-10-30). ECX = count (param_1), EDX
 * is a phantom (first touch is the write `movzx edx,cl` at 0x504127),
 * [esp+4] is the allocator word every caller pushes and nobody reads,
 * EAX = destination, EBX = element - both read before written (0x504120
 * `test eax,eax`, 0x504124 `mov cl,[ebx+0x11]`). The port had only the
 * count; all three call sites passed a single wrong value and are
 * corrected.
 */
#include "ghidra_types.h"


void __fastcall Vector_UninitFillN_12(int param_1,undefined4 param_2,undefined4 param_3,
                                    undefined4 *regEax,undefined4 *regEbx)

{
  byte bVar1;
  undefined4 *in_EAX = regEax;
  uint uVar2;
  undefined4 *unaff_EBX = regEbx;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  for (; param_1 != 0; param_1 = param_1 + -1) {
    if (in_EAX != (undefined4 *)0x0) {
      bVar1 = *(byte *)((int)unaff_EBX + 0x11);
      *(byte *)((int)in_EAX + 0x11) = bVar1;
      puVar3 = unaff_EBX;
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
    }
    in_EAX = (undefined4 *)((int)in_EAX + 0x12);
  }
  return;
}

