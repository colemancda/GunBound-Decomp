/* TreeErase - 0x0040b600 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * VC7 STL _Tree::erase(iterator): the same "invalid map/set<T> iterator"
 * throw guard as TreeEraseRange, then node-unlink (splicing in
 * TreeSubtreeMin for a two-child node) with TreeIteratorIncrement called
 * first to compute the returned successor, rebalance via the rotation
 * helpers (0x40bc80/0x40bd20) shared with TreeInsertRebalance, free the
 * node, and decrement _Mysize at container+8. Container identity is
 * external and exact: TreeEraseRange's own header names this as "the
 * single-iterator erase overload" its erase(first,last) loop calls, and
 * its only other caller is CValueGuard::EncodeOutgoingPacketField
 * (src/cxx/ValueGuard.cpp / src/network/EncodeOutgoingPacketField.c),
 * which passes &g_valueGuardMap as param_1 - the same map
 * TreeInsertRebalance/TreeEraseRange/TreeFind all already walk.
 *
 * DROPPED-ARG FIX (2026-10-26): the rotation helpers are now named
 * TreeRotateLeft/TreeRotateRight (0x40bc80/0x40bd20) and have real 2-arg
 * prototypes. All 6 calls below were short by one argument (passing only
 * this function's own param_1, the container, into the callee's NODE
 * slot) - each call site now also passes its disassembly-confirmed pivot
 * node; see the comment at each call for which original instruction
 * fixed that pivot.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0040b717) */
/* WARNING: Removing unreachable block (ram,0x0040b727) */
/* WARNING: Removing unreachable block (ram,0x0040b731) */
/* WARNING: Removing unreachable block (ram,0x0040b734) */
/* WARNING: Removing unreachable block (ram,0x0040b723) */
/* WARNING: Removing unreachable block (ram,0x0040b742) */
/* WARNING: Removing unreachable block (ram,0x0040b74f) */
/* WARNING: Removing unreachable block (ram,0x0040b75a) */
/* WARNING: Removing unreachable block (ram,0x0040b756) */
/* WARNING: Removing unreachable block (ram,0x0040b74a) */
/* WARNING: Removing unreachable block (ram,0x0040b75d) */

void TreeErase(int param_1,undefined4 *param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  undefined1 local_50 [4];
  undefined1 local_4c;
  undefined4 local_3c;
  undefined4 local_38;
  undefined **local_34 [10];
  undefined4 local_4;

  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537a38) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (*(char *)((int)param_3 + 0x11) != '\0') {
    local_38 = 0xf;
    local_3c = 0;
    local_4c = 0;
    basic_string_AssignCStr((int)local_50,s_invalid_map_set_T_iterator_00552000,0x1b);
    local_4 = 0;
    /* DROPPED-ARG FIX (2026-10-02): LogicError_ctor is __thiscall(this,
       msgObj) - disasm confirms ECX=&local_34 (the exception object
       whose vtable is stamped right below, the standard base-ctor-then-
       derived-vtable-stamp sequence) and the stack arg=&local_50 (the
       message string just built above), matching what the C already
       had; only the leading `this` was missing. */
    LogicError_ctor((undefined4 *)local_34,(undefined4)local_50);
    local_34[0] = &PTR_FUN_00544b74;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(local_34,&DAT_00558458);
  }
  TreeIteratorIncrement();
  piVar6 = (int *)*param_3;
  if (*(char *)((int)piVar6 + 0x11) == '\0') {
    if (*(char *)(param_3[2] + 0x11) == '\0') {
      piVar6 = (int *)param_3[2];
    }
  }
  else {
    piVar6 = (int *)param_3[2];
  }
  piVar5 = (int *)param_3[1];
  if (*(char *)((int)piVar6 + 0x11) == '\0') {
    piVar6[1] = (int)piVar5;
  }
  if (*(int **)(*(int *)(param_1 + 4) + 4) == param_3) {
    *(int **)(*(int *)(param_1 + 4) + 4) = piVar6;
  }
  else if ((int *)*piVar5 == param_3) {
    *piVar5 = (int)piVar6;
  }
  else {
    piVar5[2] = (int)piVar6;
  }
  puVar1 = *(undefined4 **)(param_1 + 4);
  if ((int *)*puVar1 == param_3) {
    piVar3 = piVar5;
    if (*(char *)((int)piVar6 + 0x11) == '\0') {
      /* TreeSubtreeMin is void-returning (see its own definition) - this
       * call site's return-value use is a Ghidra per-call-site
       * decompilation inconsistency, same class as entry/WinMain.c's
       * FUN_004058c0 fix. piVar3 keeps its prior value (piVar5) as a
       * result. */
      TreeSubtreeMin(piVar6);
    }
    *puVar1 = piVar3;
  }
  iVar2 = *(int *)(param_1 + 4);
  if (*(int **)(iVar2 + 8) == param_3) {
    if (*(char *)((int)piVar6 + 0x11) == '\0') {
      /* FUN_0040bce0 is void-returning (see its own definition) - this
       * call site's return-value use is a Ghidra per-call-site
       * decompilation inconsistency, same class as entry/WinMain.c's
       * FUN_004058c0 fix. uVar4 is left uninitialized here as a
       * result. */
      FUN_0040bce0((int)piVar6);
      *(undefined4 *)(iVar2 + 8) = uVar4;
    }
    else {
      *(int **)(iVar2 + 8) = piVar5;
    }
  }
  if ((char)param_3[4] == '\x01') {
    if (piVar6 != *(int **)(*(int *)(param_1 + 4) + 4)) {
      do {
        piVar3 = piVar5;
        if ((char)piVar6[4] != '\x01') break;
        piVar5 = (int *)*piVar3;
        if (piVar6 == piVar5) {
          piVar5 = (int *)piVar3[2];
          if ((char)piVar5[4] == '\0') {
            *(undefined1 *)(piVar5 + 4) = 1;
            *(undefined1 *)(piVar3 + 4) = 0;
            /* orig 0x40b7ad `mov ecx,esi` right before the call - the
             * pivot is piVar3, not param_1. */
            TreeRotateLeft((int)piVar3,param_1);
            piVar5 = (int *)piVar3[2];
          }
          if (*(char *)((int)piVar5 + 0x11) == '\0') {
            if ((*(char *)(*piVar5 + 0x10) != '\x01') || (*(char *)(piVar5[2] + 0x10) != '\x01')) {
              if (*(char *)(piVar5[2] + 0x10) == '\x01') {
                *(undefined1 *)(*piVar5 + 0x10) = 1;
                *(undefined1 *)(piVar5 + 4) = 0;
                /* orig 0x40b7e3 - ECX is still piVar5 here (last loaded
                 * at 0x40b7b8 `mov ecx,[esi+8]`, never reassigned before
                 * this call), not piVar3. */
                TreeRotateRight(piVar5,param_1);
                piVar5 = (int *)piVar3[2];
              }
              *(char *)(piVar5 + 4) = (char)piVar3[4];
              *(undefined1 *)(piVar3 + 4) = 1;
              *(undefined1 *)(piVar5[2] + 0x10) = 1;
              /* orig 0x40b7fd `mov ecx,esi` right before the call - back
               * to piVar3. */
              TreeRotateLeft((int)piVar3,param_1);
              break;
            }
LAB_0040b832:
            *(undefined1 *)(piVar5 + 4) = 0;
          }
        }
        else {
          if ((char)piVar5[4] == '\0') {
            *(undefined1 *)(piVar5 + 4) = 1;
            *(undefined1 *)(piVar3 + 4) = 0;
            /* orig 0x40b80f `mov ecx,esi` right before the call - the
             * pivot is piVar3, not param_1. */
            TreeRotateRight(piVar3,param_1);
            piVar5 = (int *)*piVar3;
          }
          if (*(char *)((int)piVar5 + 0x11) == '\0') {
            if ((*(char *)(piVar5[2] + 0x10) == '\x01') && (*(char *)(*piVar5 + 0x10) == '\x01'))
            goto LAB_0040b832;
            if (*(char *)(*piVar5 + 0x10) == '\x01') {
              *(undefined1 *)(piVar5[2] + 0x10) = 1;
              *(undefined1 *)(piVar5 + 4) = 0;
              /* orig 0x40b85d - ECX is still piVar5 here (last loaded at
               * 0x40b81a `mov ecx,[esi]`, never reassigned before this
               * call), not piVar3. */
              TreeRotateLeft((int)piVar5,param_1);
              piVar5 = (int *)*piVar3;
            }
            *(char *)(piVar5 + 4) = (char)piVar3[4];
            *(undefined1 *)(piVar3 + 4) = 1;
            *(undefined1 *)(*piVar5 + 0x10) = 1;
            /* orig 0x40b875 `mov ecx,esi` right before the call - back to
             * piVar3. */
            TreeRotateRight(piVar3,param_1);
            break;
          }
        }
        piVar5 = (int *)piVar3[1];
        piVar6 = piVar3;
      } while (piVar3 != *(int **)(*(int *)(param_1 + 4) + 4));
    }
    *(undefined1 *)(piVar6 + 4) = 1;
  }
  _free(param_3);
  if (*(int *)(param_1 + 8) != 0) {
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  }
  *param_2 = param_3;
  return;
}

