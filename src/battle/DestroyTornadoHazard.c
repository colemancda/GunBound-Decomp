/* DestroyTornadoHazard - 0x004ac670 in the original binary.
 *
 * NAMED 2026-08-19 (was a FUN_ name).  CTornadoHazard's destructor proper: it
 * installs 0x5565e4 on entry - the vtable src/cxx/Hazards.h assigns to that
 * class - and is reached through DeleteTornadoHazard, its scalar-deleting
 * wrapper in slot 0.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void DestroyTornadoHazard(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_00537d41;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_005565e4;
  local_4 = 2;
  if (param_1[0x126] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x126],&DAT_0079376c);
    TreeLowerBound(local_14,&DAT_00793770);
  }
  SUBFIELD(local_4,0,undefined1) = 1;
  if (param_1[0x9c] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x9c],&DAT_0079376c);
    TreeLowerBound(local_14,&DAT_00793770);
  }
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if (param_1[0x13] != 0) {
    ScrambleChecksumGuardBytes(param_1[0x13],&DAT_0079376c);
    TreeLowerBound(local_14,&DAT_00793770);
  }
  *param_1 = &PTR_LAB_0055752c;
  *unaff_FS_OFFSET = local_c;
  return;
}

