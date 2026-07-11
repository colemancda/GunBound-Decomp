/* State09_ReadyRoom_Destroy - 0x004d3810 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall State09_ReadyRoom_Destroy(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  puStack_8 = &LAB_00537c73;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &vtable_State09_ReadyRoom;
  local_4 = 1;
  if (param_1[0xa0] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = local_4 & 0xffffff00;
  if (param_1[8] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  *param_1 = &PTR_LAB_00553fb0;
  *unaff_FS_OFFSET = local_c;
  return;
}

