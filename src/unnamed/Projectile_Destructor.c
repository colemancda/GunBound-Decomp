/* Projectile_Destructor - 0x004ae390 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004ae390 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: Disasm
 * 0x4ae390-0x4ae39c: stores vtable 0x55631c in the object (EAX) and calls
 * DestroyProjectile (0x455570) - the base-class destructor idiom (reset
 * the vtable to this class, then run the class teardown). Its only caller
 * is Projectile_ScalarDtor (0x44d990), the slot-0 scalar deleting
 * destructor of the projectile vtables, which is how the object arrives in
 * EAX.
 *
 DROPPED REGISTER RECOVERED: EAX is the object being destroyed.  This is a
 * destructor body whose scalar-deleting wrapper (FUN_0044d990) receives the object as
 * its __thiscall param_1 (ECX), never writes EAX, and calls this -- so EAX at
 * this call IS that param_1, traced through the caller by
 * tools/reg_trace_caller.py and passed explicitly now.
 */
#include "ghidra_types.h"


void Projectile_Destructor(undefined4 *regEax)

{
  *regEax = &PTR_FUN_0055631c;
  DestroyProjectile(regEax);
  return;
}

