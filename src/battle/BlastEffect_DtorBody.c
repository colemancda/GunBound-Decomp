/* BlastEffect_DtorBody - 0x004aa8e0 in the original binary.
 *
 * The BlastEffect destructor body -- vtable PTR_FUN_0055656c, installed only
 * by InitBlastEffect.  See DropCaseProjectile_DtorBody.
 *
 DROPPED REGISTER RECOVERED: EAX is the object being destroyed.  This is a
 * destructor body whose scalar-deleting wrapper (BlastEffect_ScalarDtor) receives the object as
 * its __thiscall param_1 (ECX), never writes EAX, and calls this -- so EAX at
 * this call IS that param_1, traced through the caller by
 * tools/reg_trace_caller.py and passed explicitly now.
 */
#include "ghidra_types.h"


void BlastEffect_DtorBody(undefined4 *regEax)

{
  *regEax = &PTR_FUN_0055656c;
  DestroyProjectile(regEax);
  return;
}

