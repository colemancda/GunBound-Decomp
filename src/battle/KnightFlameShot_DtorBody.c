/* KnightFlameShot_DtorBody - 0x0047aaf0 in the original binary.
 *
 * The KnightFlameShot destructor body -- vtable PTR_FUN_00556008, installed
 * only by SpawnKnightFlameShot.  See DropCaseProjectile_DtorBody.
 *
 DROPPED REGISTER RECOVERED: EAX is the object being destroyed.  This is a
 * destructor body whose scalar-deleting wrapper (KnightFlameShot_ScalarDtor) receives the object as
 * its __thiscall param_1 (ECX), never writes EAX, and calls this -- so EAX at
 * this call IS that param_1, traced through the caller by
 * tools/reg_trace_caller.py and passed explicitly now.
 */
#include "ghidra_types.h"


void KnightFlameShot_DtorBody(undefined4 *regEax)

{
  *regEax = &PTR_FUN_00556008;
  DestroyProjectile(regEax);
  return;
}

