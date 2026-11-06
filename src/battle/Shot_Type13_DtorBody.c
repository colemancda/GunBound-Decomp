/* Shot_Type13_DtorBody - 0x0046b670 in the original binary.
 *
 * Destructor body behind Shot_Type13_ScalarDtor (slot 0 of vtable
 * 0x00555e0c, the vtable SpawnShot_Type13 installs on its object): it
 * stores that vtable and then chains to DestroyProjectile; the object
 * arrives in EAX (the wrapper loads it with mov eax,esi before the call;
 * this body begins by storing the vtable through EAX). Reached only from
 * the wrapper. Confidence LIKELY: the class name is inherited from the
 * spawner's naming.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED REGISTER RECOVERED: EAX is the object being destroyed.  This is a
 * destructor body whose scalar-deleting wrapper (Shot_Type13_ScalarDtor) receives the object as
 * its __thiscall param_1 (ECX), never writes EAX, and calls this -- so EAX at
 * this call IS that param_1, traced through the caller by
 * tools/reg_trace_caller.py and passed explicitly now.
 */
#include "ghidra_types.h"


void Shot_Type13_DtorBody(undefined4 *regEax)

{
  *regEax = &PTR_FUN_00555e0c;
  DestroyProjectile(regEax);
  return;
}

