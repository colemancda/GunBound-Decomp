/* ReplayContext_ScalarDeletingDestructor - 0x004e6030 in the original
 * binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), CERTAIN - companion to ReplayContext_Destructor
 * (0x4e6050), named alongside it on the same evidence. Shape is the
 * textbook MSVC scalar-deleting-destructor thunk: `__thiscall(this,
 * flags)`, calls the base destructor then frees `this` iff `flags & 1`.
 * include/functions.h already uses this exact naming for other classes
 * (CGameState_ScalarDeletingDestructor, CInputDevice_ScalarDeletingDestructor)
 * - followed here for consistency.
 */
#include "ghidra_types.h"


void * __thiscall ReplayContext_ScalarDeletingDestructor(void *param_1,int param_2)

{
  ReplayContext_Destructor(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}
