/* TreeInsertRebalance - 0x0040bae0 in the original binary.
 *
 * TreeLowerBound, cited below by name, by its 0x40b540 address and by
 * its old filename (src/registry/TreeLowerBound.c), is now named
 * TreeInsert (src/registry/TreeInsert.c) - this note is what first made
 * that identity case, and is left verbatim below.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-21), CERTAIN. The node-link-plus-rebalance half of
 * std::_Tree::_Insert over &g_valueGuardMap (the CValueGuard guard-cell
 * map), the same instantiation TreeFind/TreeEraseRange/TreeLowerBound
 * walk - identical node shape (0x14-byte node from the allocator at
 * 0x40bea0: _Left/_Parent/_Right, int key at +0xc, colour at +0x10,
 * _Isnil at +0x11) and the same throw guard shape ("map/set<T> too
 * long") the sibling TurnEventSet_InsertRebalance uses for its own,
 * differently-shaped (0x10-byte, ushort-keyed) tree.
 *
 * The container identity comes from the ORIGINAL binary's two call
 * sites, both inside the function at orig 0x40b540 (`tools/
 * callsite_regs.py 0x40bae0`: both at orig 0x40b598/0x40b5d0, ECX=esi
 * uniformly). That function is currently ported as TreeLowerBound, whose
 * own header documents it as the CValueGuard guard-cell map and its
 * dispatcher as a deliberate bring-up NEUTER (src/registry/
 * TreeLowerBound.c) - the real body, which is what actually calls this
 * function, was replaced wholesale rather than ported, so this function
 * currently has no live caller in the compiled source tree. That does
 * not weaken the container identity: the evidence is read off the
 * original binary's disassembly, independent of the neuter. Disassembly
 * at orig 0x40b58e-0x40b5e4 shows the classic VC7 `_Tree::insert`
 * shape - descend, decide left/right-of-parent, call this helper, store
 * the pair<iterator,bool> result - matching TurnEventSet_Insert's own
 * shape one-for-one.
 *
 * This function's own `unaff_EDI` (the tree/map object) is NOT promoted
 * to a real parameter here, unlike its TurnEventSet sibling - left as-is
 * since there is no live call site to thread a value through; this is a
 * naming note only, not a dropped-register fix.
 */
#include "ghidra_types.h"


void __thiscall
TreeInsertRebalance(undefined4 *param_1,undefined4 *param_2,char param_3,undefined4 param_4)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int unaff_EDI;
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
  if (0x3ffffffd < *(uint *)(unaff_EDI + 8)) {
    local_38 = 0xf;
    local_3c = 0;
    local_4c = 0;
    basic_string_AssignCStr((int)local_50,s_map_set_T_too_long_00551fec,0x13);
    local_4 = 0;
    /* DROPPED-ARG FIX (2026-10-02): LogicError_ctor is __thiscall(this,
       msgObj) - disasm confirms ECX=&local_34 (the exception object
       whose vtable is stamped right below, the standard base-ctor-then-
       derived-vtable-stamp sequence) and the stack arg=&local_50 (the
       message string just built above), matching what the C already
       had; only the leading `this` was missing. */
    LogicError_ctor((undefined4 *)local_34,(undefined4)local_50);
    local_34[0] = &PTR_FUN_00544b68;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_34,&DAT_0055841c);
  }
  piVar3 = (int *)FUN_0040bea0(*(undefined4 *)(unaff_EDI + 4),param_1,*(undefined4 *)(unaff_EDI + 4)
                               ,param_4,0);
  *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 1;
  if (param_1 == *(undefined4 **)(unaff_EDI + 4)) {
    (*(undefined4 **)(unaff_EDI + 4))[1] = piVar3;
    **(undefined4 **)(unaff_EDI + 4) = piVar3;
    *(int **)(*(int *)(unaff_EDI + 4) + 8) = piVar3;
  }
  else if (param_3 == '\0') {
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
  cVar1 = *(char *)(piVar3[1] + 0x10);
  piVar6 = piVar3;
  do {
    if (cVar1 != '\0') {
      *(undefined1 *)(*(int *)(*(int *)(unaff_EDI + 4) + 4) + 0x10) = 1;
      *param_2 = piVar3;
      return;
    }
    piVar4 = piVar6 + 1;
    piVar2 = (int *)*piVar4;
    piVar5 = *(int **)piVar2[1];
    if (piVar2 == piVar5) {
      piVar5 = (int *)((undefined4 *)piVar2[1])[2];
      if ((char)piVar5[4] == '\0') {
LAB_0040bbd5:
        *(undefined1 *)(*piVar4 + 0x10) = 1;
        *(undefined1 *)(piVar5 + 4) = 1;
        *(undefined1 *)(*(int *)(*piVar4 + 4) + 0x10) = 0;
        piVar6 = *(int **)(*piVar4 + 4);
      }
      else {
        if (piVar6 == (int *)piVar2[2]) {
          FUN_0040bc80(unaff_EDI);
          piVar6 = piVar2;
        }
        *(undefined1 *)(piVar6[1] + 0x10) = 1;
        *(undefined1 *)(*(int *)(piVar6[1] + 4) + 0x10) = 0;
        FUN_0040bd20(unaff_EDI);
      }
    }
    else {
      if ((char)piVar5[4] == '\0') goto LAB_0040bbd5;
      if (piVar6 == (int *)*piVar2) {
        FUN_0040bd20(unaff_EDI);
        piVar6 = piVar2;
      }
      *(undefined1 *)(piVar6[1] + 0x10) = 1;
      *(undefined1 *)(*(int *)(piVar6[1] + 4) + 0x10) = 0;
      FUN_0040bc80(unaff_EDI);
    }
    cVar1 = *(char *)(piVar6[1] + 0x10);
  } while( true );
}

