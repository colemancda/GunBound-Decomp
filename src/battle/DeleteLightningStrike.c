/* DeleteLightningStrike - 0x00482060 in the original binary.
 *
 * Scalar-deleting destructor of the lightning-strike object (class key
 * 0x1f7), slot 0 of vtable 0x00556194: __thiscall, one stack argument
 * (ret 4); it calls DestroyLightningStrike and then _free's the object
 * when bit 0 of the flag argument is set. Evidence: this wrapper is slot
 * 0 of that vtable (read from .data) and the only xref to this function;
 * InitLightningStrike installs the same vtable. Spelled Delete/Destroy
 * like DeleteJewel and DeleteLightningHazard, because the body is the
 * non-projectile shape (no DestroyProjectile).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void * __thiscall DeleteLightningStrike(void *param_1,int param_2)

{
  DestroyLightningStrike(param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

