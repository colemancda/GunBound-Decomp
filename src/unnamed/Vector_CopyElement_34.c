/* Vector_CopyElement_34 - 0x00503680 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): EAX is the DESTINATION record. The body
 * copies three counted strings out of param_2 into it - at +0, +0x12 and
 * +0x28, with their lengths in the bytes at +0x11, +0x27 and +0x31 - and
 * finishes with the word at +0x32, i.e. a whole 0x34-byte element, which
 * is the stride its two array callers walk.
 *
 * param_1 is a PHANTOM. `push ecx` at 0x503680 is balanced by `pop ecx`
 * at 0x503704 and ECX is written at 0x50368e before any use, so nothing
 * arrives in it; Ghidra declared it only because it typed the function
 * __fastcall. The epilogue is a bare `ret`, so there are no stack
 * arguments either: EAX and EDX are the whole input.
 *
 * This is the innermost member of a std::vector<0x34-byte record>
 * family - Vector_PushBack_34 (push_back) -> Vector_Insert_34 ->
 * Vector_InsertN_34 -> Vector_UninitCopy_34 (range copy) and
 * Vector_UninitFillN_34 (fill n) -> here.
 *
 * NAMED (2026-08-28): the 0x34-byte element's COPY CONSTRUCTOR, i.e.
 * what the two uninitialised-storage helpers reach through
 * `_Al.construct(dest, src)`. Named on the same grounds and in the same
 * shape as CArray_CopyElement_1750 (0x4ff2c0), which is the identical
 * (phantom ECX, source in EDX, destination in EAX) element copy for the
 * 0x1750-byte record: the evidence is the call sites, not the body.
 * All three of them - Vector_UninitFillN_34, Vector_UninitCopy_34 and
 * Vector_InsertN_34's by-value buffer fill - pass a destination that is
 * a slot in a 0x34-strided array or the insert's own 0x34-byte scratch
 * object, so the function is this container's element copy and nothing
 * else reaches it.
 *
 * The element itself is three fixed-width counted name fields plus a
 * trailing word: char[0x11] with its length at +0x11, char[0x15] with
 * its length at +0x27, char[9] with its length at +0x31, then the word
 * at +0x32 - which is why the copy is length-driven rather than a flat
 * 0x34-byte move.
 */
#include "ghidra_types.h"


void __fastcall Vector_CopyElement_34(undefined4 param_1,undefined4 *param_2,undefined4 *regEax)

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
  bVar1 = *(byte *)((int)param_2 + 0x27);
  *(byte *)((int)in_EAX + 0x27) = bVar1;
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
  bVar1 = *(byte *)((int)param_2 + 0x31);
  *(byte *)((int)in_EAX + 0x31) = bVar1;
  puVar3 = param_2 + 10;
  puVar4 = in_EAX + 10;
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
  *(undefined1 *)((uint)bVar1 + (int)(in_EAX + 10)) = 0;
  *(undefined2 *)((int)in_EAX + 0x32) = *(undefined2 *)((int)param_2 + 0x32);
  return;
}

