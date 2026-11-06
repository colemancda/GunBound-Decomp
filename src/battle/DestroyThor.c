/* DestroyThor - 0x004abcc0 in the original binary.
 *
 * Destructor body behind DeleteThor (slot 0 of vtable 0x005565cc,
 * installed by InitThor): the object arrives as a stack argument, the
 * body stores the vtable, scrambles and re-registers the guard cells
 * with the value-guard map, and finishes by storing the base vtable
 * 0x0055752c, as DestroyJewel does. It does not chain to
 * DestroyProjectile. Reached only from the wrapper.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void DestroyThor(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00537d71;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_005565cc;
  local_4 = 2;
  if (param_1[0x12a] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x12a],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 1;
  if (param_1[0xa1] != 0) {
    ScrambleChecksumGuardBytes(param_1[0xa1],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 0;
  if (param_1[0x18] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x18],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  *param_1 = &PTR_LAB_0055752c;
  *unaff_FS_OFFSET = local_c;
  return;
}

