/* Vector_ThrowTooLong - 0x005030a0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-21), CERTAIN. Builds the literal message string
 * "vector<T> too long" (`s_vector_T_too_long_00557260`, 0x12 bytes -
 * exactly strlen), hands it to LogicError_ctor, then re-stamps the
 * thrown object's vtable with `&PTR_FUN_00544b68` before
 * __CxxThrowException_8 - this is MSVC7/Dinkumware's own `<vector>`
 * internal message, used by exactly one member: `vector<T,A>::_Xlen()`.
 * Confirmed from outside: all four call sites that reach it
 * (Vector_InsertN_8.c, Vector_InsertN_1e.c, Vector_InsertN_34.c - already-
 * named instantiations of the same vector-insert template, one per node
 * stride - plus the still-unnamed FUN_00502b70.c, stride 0x12) guard the
 * call with `<capacity bound> - <current size> < <count>` (the bound
 * itself varies per instantiation - 0x1fffffff, 0x8888888, 0x4ec4ec4,
 * 0xe38e38e - exactly max_size() for that element stride), exactly
 * libstdc++/Dinkumware's `_Xlen` capacity-overflow guard (`max_size() -
 * size() < count`), and `&PTR_FUN_00544b68` is
 * independently the same vtable the sibling "map/set<T> too long" throw
 * sites (orig 0x40bae0, 0x4e8b10) use for their own length_error-shaped
 * exception (docs/vtable_census.txt: installs=5, slots=2).
 */
#include "ghidra_types.h"


undefined4 Vector_ThrowTooLong(void)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_50 [4];
  undefined1 local_4c;
  undefined4 local_3c;
  undefined4 local_38;
  undefined **local_34 [10];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537a38;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_38 = 0xf;
  local_3c = 0;
  local_4c = 0;
  basic_string_AssignCStr((int)local_50,s_vector_T_too_long_00557260,0x12);
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

