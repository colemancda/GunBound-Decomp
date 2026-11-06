/* DestroyProjectileLightningHazard - 0x004a69f0 in the original binary.
 *
 * Destructor body behind DeleteProjectileLightningHazard (slot 0 of
 * vtable 0x00556510, installed by InitProjectileLightningHazard): the
 * object arrives as a stack argument, the body stores the vtable,
 * scrambles and re-registers the guard cells with the value-guard map,
 * and finishes by storing the base vtable 0x0055752c, as DestroyJewel
 * does. It does not chain to DestroyProjectile. Reached only from the
 * wrapper.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void DestroyProjectileLightningHazard(undefined4 *param_1)

{
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537d93) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  *param_1 = &PTR_FUN_00556510;
  local_4 = 1;
  if (param_1[0x9c] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x9c],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = local_4 & 0xffffff00;
  if (param_1[0x13] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x13],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  *param_1 = &PTR_LAB_0055752c;
  return;
}

