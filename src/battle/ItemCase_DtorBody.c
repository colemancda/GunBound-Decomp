/* ItemCase_DtorBody - 0x00476f70 in the original binary.
 *
 * The ItemCase destructor body -- vtable PTR_FUN_00555fbc, installed only by
 * SpawnItemCase.  See DropCaseProjectile_DtorBody for the pattern.
 *
 DROPPED REGISTER RECOVERED: EAX is the object being destroyed.  This is a
 * destructor body whose scalar-deleting wrapper (ItemCase_ScalarDtor) receives the object as
 * its __thiscall param_1 (ECX), never writes EAX, and calls this -- so EAX at
 * this call IS that param_1, traced through the caller by
 * tools/reg_trace_caller.py and passed explicitly now.
 */
#include "ghidra_types.h"


void ItemCase_DtorBody(undefined4 *regEax)

{
  *regEax = &PTR_FUN_00555fbc;
  DestroyProjectile(regEax);
  return;
}

