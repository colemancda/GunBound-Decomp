/* Bitset_ThrowInvalidPosition - 0x00426460 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-21), CERTAIN. Library identity, not application logic:
 * this builds the literal message string "invalid bitset<N> position"
 * (`s_invalid_bitset_N_position_00552c4c`, 0x1a bytes - exactly strlen),
 * hands it to LogicError_ctor (0x409fd0, the shared
 * std::logic_error(const string&) base ctor - see that file's own header
 * for how it was identified), then re-stamps the object's vtable with
 * `&PTR_FUN_00544b74` before throwing via __CxxThrowException_8. That
 * string is MSVC7/Dinkumware's own `<bitset>` internal message, used by
 * exactly one member: `bitset<N>::_Xinv()`, the helper that every
 * `bitset<N>::operator[]`/`test()`/`set()`/`reset()` bounds check calls
 * when the position argument is out of range. It is reached from 16
 * call sites scattered across unrelated network/battle/state-machine
 * files (e.g. ProcessUdpProbeDatagram, BroadcastQueuedEvent,
 * State11_InBattle_OnTick) with no shared subsystem between them - exactly
 * what a generic `bitset<N>::operator[]` bounds-check failure looks like
 * when the template is instantiated in several unrelated places, rather
 * than evidence of any one application purpose. So the name rests on the
 * library string match itself, which is sufficient for a leaf CRT/STL
 * throw helper: the string is compiler/library-generated, not something
 * this codebase authored, and `&PTR_FUN_00544b74` is independently the
 * same vtable the sibling "invalid map/set<T> iterator" throw sites use
 * for their own out_of_range-shaped exception (docs/vtable_census.txt:
 * installs=6, slots=2), consistent with _Xinv throwing out_of_range in
 * real MSVC STL.
 */
#include "ghidra_types.h"


void Bitset_ThrowInvalidPosition(void)

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
  basic_string_AssignCStr((int)local_50,s_invalid_bitset_N_position_00552c4c,0x1a);
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

