/* DropCaseProjectile_DtorBody - 0x0046af00 in the original binary.
 *
 * The DropCaseProjectile destructor body.  Class identity comes from the
 * vtable it installs: `*obj = &PTR_FUN_00555dec`, and the only constructor in
 * the tree installing that same vtable is SpawnDropCaseProjectile (line 53).
 * The wrapper DropCaseProjectile_ScalarDtor supplies the object in EAX and
 * frees it when the low delete-flag bit is set.
 *
 DROPPED REGISTER RECOVERED: EAX is the object being destroyed.  This is a
 * destructor body whose scalar-deleting wrapper (DropCaseProjectile_ScalarDtor) receives the object as
 * its __thiscall param_1 (ECX), never writes EAX, and calls this -- so EAX at
 * this call IS that param_1, traced through the caller by
 * tools/reg_trace_caller.py and passed explicitly now.
 */
#include "ghidra_types.h"


void DropCaseProjectile_DtorBody(undefined4 *regEax)

{
  *regEax = &PTR_FUN_00555dec;
  DestroyProjectile(regEax);
  return;
}

