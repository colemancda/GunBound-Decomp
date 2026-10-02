/* FUN_005030a0 - 0x005030a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_005030a0(void)

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

