/* DestroyPrimaryShot_Bullet4 - 0x004a2bc0 in the original binary.
 *
 * Destructor body behind the scalar-deleting wrapper DeletePrimaryShot_Bullet4
 * (0x004a2ba0), slot 0 of vtable 0x5564d0: the wrapper does push this;
 * call 0x004a2bc0 and then frees the object when bit 0 of its flag
 * argument is set.  This body stores 0x5564d0 into *this and chains to
 * DestroyProjectile (0x00455570).  Same split as DestroyShot2_Bullet9 /
 * DeleteShot2_Bullet9, except that the object arrives as a stack argument
 * here (ret 4) rather than in EAX.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void DestroyPrimaryShot_Bullet4(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00539344;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_005564d0;
  local_4 = 3;
  if (param_1[0x118a] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x118a],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 2;
  if (param_1[0x1101] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x1101],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 1;
  if (param_1[0x1078] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x1078],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 0;
  if (param_1[0xfef] != 0) {
    ScrambleChecksumGuardBytes(param_1[0xfef],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  DestroyProjectile(param_1);
  *unaff_FS_OFFSET = local_c;
  return;
}

