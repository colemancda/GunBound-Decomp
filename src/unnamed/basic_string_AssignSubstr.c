/* FUN_0040b9f0 - 0x0040b9f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARG FIX (2026-09-21): __thiscall, ECX=param_1(`this`) + `ret
 * 0xc` = 3 stack dwords (disasm 0x40b9f0-0x40ba37) - the declaration's
 * own shape (param_1..param_4) was already correct; all 3 callers just
 * undercounted by one. This is a std::string-shaped "assign a substring
 * of another/the same string object" helper: `this`=param_1, the SOURCE
 * string object=param_2 (its own +0x14 length / +0x18 capacity /+4
 * buffer fields are read, confirmed at 0x40b9fc `cmp [edi+0x14],esi`),
 * srcPos=param_3, count=param_4. When param_1==param_2 (self-assign) it
 * takes the safe in-place substring-compact path via two FUN_0040bda0
 * calls instead of copying. All 3 sites (FUN_0040bee0.c, FUN_0040b940.c,
 * FUN_00409fd0.c) had the SOURCE-OBJECT argument (param_2) missing
 * entirely, shifting srcPos/count one slot left into param_2/param_3 -
 * see each caller's own header/inline note for its disasm evidence.
 */
#include "ghidra_types.h"


int __thiscall FUN_0040b9f0(int param_1,int param_2,uint param_3,uint param_4)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  int *piVar5;
  
  if (*(uint *)(param_2 + 0x14) < param_3) {
    FUN_00520251();
  }
  uVar3 = *(int *)(param_2 + 0x14) - param_3;
  if (param_4 < uVar3) {
    uVar3 = param_4;
  }
  if (param_1 != param_2) {
    if (uVar3 == 0xffffffff) {
      FUN_00520291();
    }
    if (*(uint *)(param_1 + 0x18) < uVar3) {
      FUN_0040bfd0(param_1,uVar3,*(undefined4 *)(param_1 + 0x14));
    }
    else if (uVar3 == 0) {
      *(undefined4 *)(param_1 + 0x14) = 0;
      if (*(uint *)(param_1 + 0x18) < 0x10) {
        *(undefined1 *)(param_1 + 4) = 0;
        return param_1;
      }
      **(undefined1 **)(param_1 + 4) = 0;
      return param_1;
    }
    if (uVar3 != 0) {
      if (*(uint *)(param_2 + 0x18) < 0x10) {
        param_2 = param_2 + 4;
      }
      else {
        param_2 = *(int *)(param_2 + 4);
      }
      piVar1 = (int *)(param_1 + 4);
      piVar5 = piVar1;
      if (0xf < *(uint *)(param_1 + 0x18)) {
        piVar5 = (undefined4 *)*piVar1;
      }
      puVar4 = (undefined4 *)(param_3 + param_2);
      for (uVar2 = uVar3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *piVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        piVar5 = piVar5 + 1;
      }
      for (uVar2 = uVar3 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)piVar5 = *(undefined1 *)puVar4;
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        piVar5 = (undefined4 *)((int)piVar5 + 1);
      }
      *(uint *)(param_1 + 0x14) = uVar3;
      if (0xf < *(uint *)(param_1 + 0x18)) {
        piVar1 = (int *)*piVar1;
      }
      *(undefined1 *)((int)piVar1 + uVar3) = 0;
    }
    return param_1;
  }
  /* FIXED (2026-09-20): dropped __thiscall ECX arg at both calls - orig
   * 0x40ba1b-0x40ba2c: `mov ecx,ebx` (ebx = this function's own param_1)
   * precedes each call, and the two stack pushes are unchanged (call 1:
   * push -1 then push ebp=uVar3+param_3; call 2: push esi=param_3 then
   * push 0). This self-assign branch erases the tail then the head,
   * leaving the middle [param_3, param_3+uVar3) substring in place. */
  FUN_0040bda0(param_1,uVar3 + param_3,0xffffffff);
  FUN_0040bda0(param_1,0,param_3);
  return param_1;
}

