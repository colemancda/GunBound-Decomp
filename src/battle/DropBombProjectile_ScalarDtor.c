/* DropBombProjectile_ScalarDtor - 0x0046a4a0 in the original binary.
 *
 * Scalar-deleting destructor of the DropBombProjectile class and slot 0
 * of vtable 0x00555dcc: __thiscall, one stack argument (ret 4); it calls
 * DropBombProjectile_DtorBody on the object and then _free's it when bit
 * 0 of the flag argument is set. Evidence: this wrapper is slot 0 of
 * that vtable (read from .data) and the only xref to this function;
 * SpawnDropBombProjectile installs the same vtable on the object it
 * allocates. Same shape as DropCaseProjectile_ScalarDtor.
 * SpawnEventProjectile (0x00434160) also installs this vtable (same
 * operator_new size 0x3f9c, textured drophammer or bulletevent1), so the
 * event projectile is the same class: the name follows the primary
 * spawner and is not a claim that event shots are bombs. Confidence
 * LIKELY: the class name is inherited from the spawner's naming.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void * __thiscall DropBombProjectile_ScalarDtor(void *param_1,int param_2)

{
  FUN_0046a4c0((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

