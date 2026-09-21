/* FUN_004e8b10 - 0x004e8b10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REGISTER-ARGUMENT FIX (2026-09-20, no-prototype sweep). This is
 * a std::_Tree::_Insert-style rebalance helper: `ret 0xc` at the epilogue
 * (orig 0x4e8cab) confirms 3 STACK arguments (still param_3/param_4/
 * param_5 below), plus ECX (param_1, `this` - the "where" tree node) = 4
 * total, matching what was already declared. But the body ALSO reads
 * `unaff_EDI` throughout (the tree/set object itself, e.g.
 * `*(int*)(unaff_EDI+8)`, `*(int*)(unaff_EDI+4)`) - a genuine SECOND
 * register argument Ghidra couldn't attach to the signature, since
 * registers don't show up in `ret N`. Both call sites (FUN_004e86f0.c,
 * orig 0x4e8747-0x4e8749 and 0x4e8781-0x4e8783) confirm it: ECX is always
 * `esi` (that caller's own traversal-local `param_1`), but EDI is NEVER
 * reloaded before either call - it still holds the value set once at
 * FUN_004e86f0's own entry (`mov edi,eax` @0x4e86f8), which is that
 * function's own `param_2` (the tree/set - see FUN_004e86f0.c's header:
 * "the set arrived in EAX ... now a real parameter"). So the true
 * parameter count is 5 (ECX + EDI + 3 stack), one more than the 4
 * previously declared. Promoted `unaff_EDI` to a real second parameter;
 * both callers now pass their own `param_2` (the set) there.
 *
 * Also corrected the return type from `void` to `undefined4 *`: both
 * callers cast-and-dereference the call result
 * (`puVar2=(undefined4*)FUN_004e8b10(...); *puVar1=*puVar2;`), which only
 * compiled at all because no prototype existed to catch the void-to-
 * pointer cast (C2069 once one was added). The asm confirms a real
 * return value: the function has a SINGLE exit (the do-loop's only
 * `return` and the post-loop fallthrough are the same code path, both
 * reached via `jne 0x4e8c8c`/`je 0x4e8c81` into one epilogue), and right
 * before `ret 0xc` at orig 0x4e8cab, `mov eax,[esp+0x5c]; mov [eax],ecx`
 * (0x4e8c95-0x4e8c99) leaves EAX holding the SAME address that was just
 * written through - i.e. `param_3` (the out-slot pointer), matching
 * `return param_3;`.
 */
#include "ghidra_types.h"


undefined4 * __thiscall
FUN_004e8b10(undefined4 *param_1,int treeSet,undefined4 *param_3,char param_4,undefined4 param_5)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int unaff_EDI = treeSet;
  undefined1 local_50 [4];
  undefined1 local_4c;
  undefined4 local_3c;
  undefined4 local_38;
  undefined **local_34 [10];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537a38) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (0x7ffffffd < *(uint *)(unaff_EDI + 8)) {
    local_38 = 0xf;
    local_3c = 0;
    local_4c = 0;
    FUN_0040bee0((int)local_50,s_map_set_T_too_long_00551fec,0x13);
    local_4 = 0;
    FUN_00409fd0(local_50);
    local_34[0] = &PTR_FUN_00544b68;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_34,&DAT_0055841c);
  }
  piVar3 = (int *)FUN_004e8e30(*(undefined4 *)(unaff_EDI + 4),param_1,*(undefined4 *)(unaff_EDI + 4)
                               ,param_5,0);
  *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 1;
  if (param_1 == *(undefined4 **)(unaff_EDI + 4)) {
    (*(undefined4 **)(unaff_EDI + 4))[1] = piVar3;
    **(undefined4 **)(unaff_EDI + 4) = piVar3;
    *(int **)(*(int *)(unaff_EDI + 4) + 8) = piVar3;
  }
  else if (param_4 == '\0') {
    param_1[2] = piVar3;
    if (param_1 == *(undefined4 **)(*(int *)(unaff_EDI + 4) + 8)) {
      *(int **)(*(int *)(unaff_EDI + 4) + 8) = piVar3;
    }
  }
  else {
    *param_1 = piVar3;
    if (param_1 == (undefined4 *)**(int **)(unaff_EDI + 4)) {
      **(int **)(unaff_EDI + 4) = (int)piVar3;
    }
  }
  cVar1 = *(char *)(piVar3[1] + 0xe);
  piVar6 = piVar3;
  do {
    if (cVar1 != '\0') {
      *(undefined1 *)(*(int *)(*(int *)(unaff_EDI + 4) + 4) + 0xe) = 1;
      *param_3 = piVar3;
      return param_3;
    }
    piVar4 = piVar6 + 1;
    piVar2 = (int *)*piVar4;
    piVar5 = *(int **)piVar2[1];
    if (piVar2 == piVar5) {
      piVar5 = (int *)((undefined4 *)piVar2[1])[2];
      if (*(char *)((int)piVar5 + 0xe) == '\0') {
LAB_004e8c05:
        *(undefined1 *)(*piVar4 + 0xe) = 1;
        *(undefined1 *)((int)piVar5 + 0xe) = 1;
        *(undefined1 *)(*(int *)(*piVar4 + 4) + 0xe) = 0;
        piVar6 = *(int **)(*piVar4 + 4);
      }
      else {
        if (piVar6 == (int *)piVar2[2]) {
          FUN_004e8cb0(unaff_EDI);
          piVar6 = piVar2;
        }
        *(undefined1 *)(piVar6[1] + 0xe) = 1;
        *(undefined1 *)(*(int *)(piVar6[1] + 4) + 0xe) = 0;
        FUN_004e8d50(unaff_EDI);
      }
    }
    else {
      if (*(char *)((int)piVar5 + 0xe) == '\0') goto LAB_004e8c05;
      if (piVar6 == (int *)*piVar2) {
        FUN_004e8d50(unaff_EDI);
        piVar6 = piVar2;
      }
      *(undefined1 *)(piVar6[1] + 0xe) = 1;
      *(undefined1 *)(*(int *)(piVar6[1] + 4) + 0xe) = 0;
      FUN_004e8cb0(unaff_EDI);
    }
    cVar1 = *(char *)(piVar6[1] + 0xe);
  } while( true );
}

