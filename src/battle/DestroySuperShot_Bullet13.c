/* DestroySuperShot_Bullet13 - 0x00485760 in the original binary.
 *
 * Destructor body behind the scalar-deleting wrapper DeleteSuperShot_Bullet13
 * (0x00485740), slot 0 of vtable 0x55620c: the wrapper does push this;
 * call 0x00485760 and then frees the object when bit 0 of its flag
 * argument is set.  This body stores 0x55620c, then 0x55631c, into *this
 * and chains to DestroyProjectile (0x00455570).  Same split as
 * DestroyShot2_Bullet9 / DeleteShot2_Bullet9, except that the object
 * arrives as a stack argument here (ret 4) rather than in EAX.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void DestroySuperShot_Bullet13(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0053c218;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_0055620c;
  local_4 = 0;
  if (param_1[0xfee] != 0) {
    ScrambleChecksumGuardBytes(param_1[0xfee],&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  *param_1 = &PTR_FUN_0055631c;
  DestroyProjectile(param_1);
  *unaff_FS_OFFSET = local_c;
  return;
}

