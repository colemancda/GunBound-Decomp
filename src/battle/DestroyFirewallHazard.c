/* DestroyFirewallHazard - 0x00471470 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  CFirewallHazard's destructor proper: it
 * installs 0x555edc on entry - the vtable src/cxx/Hazards.h assigns to that
 * class - and is reached through DeleteFirewallHazard, its scalar-deleting
 * wrapper in slot 0.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void DestroyFirewallHazard(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00537eb1;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_00555edc;
  local_4 = 2;
  if (param_1[0x127] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x127],&DAT_0079376c);
    TreeLowerBound(local_14,&DAT_00793770);
  }
  SUBFIELD(local_4,0,undefined1) = 1;
  if (param_1[0x9d] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x9d],&DAT_0079376c);
    TreeLowerBound(local_14,&DAT_00793770);
  }
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if (param_1[0x14] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x14],&DAT_0079376c);
    TreeLowerBound(local_14,&DAT_00793770);
  }
  *param_1 = &PTR_LAB_0055752c;
  *unaff_FS_OFFSET = local_c;
  return;
}

