/* FUN_004513a0 - 0x004513a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 DROPPED REGISTER RECOVERED: EAX is the object being destroyed.  This is a
 * destructor body whose scalar-deleting wrapper (FUN_00451380) receives the object as
 * its __thiscall param_1 (ECX), never writes EAX, and calls this -- so EAX at
 * this call IS that param_1, traced through the caller by
 * tools/reg_trace_caller.py and passed explicitly now.
 */
#include "ghidra_types.h"


void FUN_004513a0(undefined4 *regEax)

{
  *regEax = &PTR_FUN_00555bd0;
  DestroyProjectile(regEax);
  return;
}

