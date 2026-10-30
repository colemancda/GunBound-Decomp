/* State07_AvatarStore_Delete - 0x00443da0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00443da0).  Slot 0 of State07's
 * vtable 0x5555f8 (read from the original's .rdata; the table
 * FUN_00443c20, the state's constructor, stamps), the slot every
 * sibling state fills with its deleting destructor:
 * CGameState_ScalarDeletingDestructor (0x4e5320) in States 03/05/10,
 * State09_ReadyRoom_Delete (0x4d37f0) and State11_InBattle_Delete
 * (0x4b4060).  It is byte-for-byte the shape of those two named
 * siblings: run the destructor, `test byte [esp+8],1`, free on the
 * flag, return this, `ret 4`.
 *
 * `this` RESTORED (2026-10-30): the destructor call at 0x443da3 is
 * `mov esi,ecx` (0x443da1) then `call 0x443ed0` with ECX untouched, so
 * State07_AvatarStore_Destroy receives this function's own `this`
 * (param_1) in ECX - it is __fastcall and reads it as param_1.  The
 * port called it with no arguments.  (The same argless call survives
 * in State09_ReadyRoom_Delete and State11_InBattle_Delete; not touched
 * here.)
 */
#include "ghidra_types.h"


void * __thiscall State07_AvatarStore_Delete(void *param_1,int param_2)

{
  State07_AvatarStore_Destroy((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}
