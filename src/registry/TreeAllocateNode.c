/* TreeAllocateNode - 0x0040bea0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * VC7 STL _Tree::_Buynode: allocate one 0x14-byte node (operator_new) and,
 * if the allocation succeeded, construct it - _Left=param_1, _Parent=
 * param_2, _Right=param_3, the key copied by value from *param_4 (the
 * value_type const-ref argument), _Color=param_5, _Isnil=0. This is the
 * exact allocator TreeInsertRebalance.c's own header already cites by
 * address ("the allocator at 0x40bea0") for the same 0x14-byte
 * &g_valueGuardMap node TreeFind/TreeErase/TreeRotateLeft/TreeRotateRight
 * all already walk.
 *
 * All 5 parameters are plain stack arguments (ret 0x14, no register
 * arguments) - confirmed off the entry disassembly, which reads every
 * field straight from [esp+n] with no register read before a write.
 *
 * RETURN VALUE RECOVERED (2026-10-26): Ghidra decompiled this void, but
 * EAX holds `puVar1` (operator_new's result) from the allocation call all
 * the way to `ret 0x14` on both the success and the allocation-failure
 * path - nothing between them ever writes EAX again - so the original
 * genuinely returns the new node (or NULL on failure), matching VC7
 * STL's actual `_Buynode` signature. Its only call site,
 * TreeInsertRebalance.c, already casts the call's result to `(int *)`
 * and assigns it, the same per-call-site decompilation inconsistency
 * already documented for TreeSubtreeMin/FUN_0040bce0 in TreeErase.c.
 */
#include "ghidra_types.h"


undefined4 * TreeAllocateNode(undefined4 param_1,undefined4 param_2,undefined4 param_3,
                 undefined4 *param_4,undefined1 param_5)

{
  undefined4 *puVar1;

  puVar1 = operator_new(0x14);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_1;
    puVar1[1] = param_2;
    puVar1[2] = param_3;
    puVar1[3] = *param_4;
    *(undefined1 *)(puVar1 + 4) = param_5;
    *(undefined1 *)((int)puVar1 + 0x11) = 0;
  }
  return puVar1;
}

