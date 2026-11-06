/* CrystalShot_ScalarDtor - 0x00464440 in the original binary.
 *
 * Scalar-deleting destructor of the CrystalShot class and slot 0 of
 * vtable 0x00555cf4: __thiscall, one stack argument (ret 4); it calls
 * CrystalShot_DtorBody on the object and then _free's it when bit 0 of
 * the flag argument is set. Evidence: this wrapper is slot 0 of that
 * vtable (read from .data) and the only xref to this function;
 * SpawnCrystalShot installs the same vtable on the object it allocates.
 * Same shape as DropCaseProjectile_ScalarDtor. Confidence LIKELY: the
 * class name is inherited from the spawner's naming.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void * __thiscall CrystalShot_ScalarDtor(void *param_1,int param_2)

{
  FUN_00464460(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

