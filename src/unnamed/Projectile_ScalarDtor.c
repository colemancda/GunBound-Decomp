/* Projectile_ScalarDtor - 0x0044d990 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0044d990 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: Slot 0 of 13
 * vtables in docs/vtable_census.txt (vtables whose slot 2 is
 * AnimateProjectileTick or a per-class AnimateSuperShot variant, i.e.
 * projectile classes; 0x55631c, the vtable Projectile_Destructor installs,
 * is one of them). Disasm 0x44d990-0x44d9ad: mov eax,esi / call 0x4ae390
 * (Projectile_Destructor) / test flags,1 / free(this), ret 4 - the
 * standard MSVC scalar deleting destructor shape with the real destructor
 * body in the callee. The sibling class-specific ones
 * (DropCaseProjectile_ScalarDtor, ItemCase_ScalarDtor,
 * KnightFlameShot_ScalarDtor, BlastEffect_ScalarDtor) have the same shape.
 */
#include "ghidra_types.h"


void * __thiscall Projectile_ScalarDtor(void *param_1,int param_2)

{
  Projectile_Destructor((undefined4 *)param_1);
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

