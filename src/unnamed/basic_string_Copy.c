/* basic_string_Copy - 0x0040bfd0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the MSVC 7.1 dinkumware
 * basic_string::_Copy(newsize, oldlen) growth policy, member for member.
 * The requested capacity is rounded up with | 0xf, and when newres / 3 <
 * oldres / 2 and oldres is not near the maximum the 1.5x growth
 * substitutes (newres = oldres + oldres / 2). It then allocates newres + 1
 * bytes, copies oldlen bytes of the old contents, frees the old buffer
 * only when the old capacity exceeded the 0xf small-string threshold,
 * stores the new pointer, capacity and size, and NUL-terminates. Callers
 * are the two string assign routines, basic_string_AssignSubstr and
 * basic_string_AssignCStr, which call it when the source does not fit the
 * current capacity.
 *
 * (FUN_0040bee0 in the note below is basic_string_AssignCStr's old
 * symbol; FUN_0040b9f0 is basic_string_AssignSubstr's.)
 *
 * DROPPED-ARGUMENT FIX (2026-09-20): __thiscall with 3 real params
 * (ECX=`this` + ret 8 = 2 stack dwords, disasm 0x40bfd0-0x40c0d8); the
 * declared shape was already correct. Both of the 2 call sites
 * (FUN_0040b9f0.c, FUN_0040bee0.c) wrote only the 2 stack args and
 * dropped `this` entirely - confirmed at both (orig 0x40ba46-0x40ba54 and
 * 0x40bf42-0x40bf50): `mov ecx,ebx; call 0x40bfd0` with ebx = that
 * caller's own `this`/param_1, pushed alongside the same 2 values the C
 * already had (`*(param_1+0x14)`, the new-capacity local). Fix: prepend
 * the caller's own param_1 at both sites.
 */
#include "ghidra_types.h"


void __thiscall basic_string_Copy(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537850) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  uVar4 = param_2 | 0xf;
  if (uVar4 != 0xffffffff) {
    uVar1 = *(uint *)(param_1 + 0x18);
    uVar3 = uVar1 >> 1;
    param_2 = uVar4;
    if ((uVar4 / 3 < uVar3) && (uVar1 <= -uVar3 - 2)) {
      param_2 = uVar3 + uVar1;
    }
  }
  local_8 = 0;
  puVar2 = operator_new(param_2 + 1);
  if (param_3 != 0) {
    if (*(uint *)(param_1 + 0x18) < 0x10) {
      puVar5 = (undefined4 *)(param_1 + 4);
    }
    else {
      puVar5 = *(undefined4 **)(param_1 + 4);
    }
    puVar6 = puVar2;
    for (uVar4 = param_3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (uVar4 = param_3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
  }
  if (0xf < *(uint *)(param_1 + 0x18)) {
    _free(*(void **)(param_1 + 4));
  }
  puVar5 = (undefined4 *)(param_1 + 4);
  *(undefined1 *)puVar5 = 0;
  *puVar5 = puVar2;
  *(uint *)(param_1 + 0x18) = param_2;
  *(uint *)(param_1 + 0x14) = param_3;
  if (0xf < param_2) {
    puVar5 = puVar2;
  }
  *(undefined1 *)((int)puVar5 + param_3) = 0;
  return;
}

