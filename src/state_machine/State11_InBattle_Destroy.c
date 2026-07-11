/* State11_InBattle_Destroy - 0x004b4080 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall State11_InBattle_Destroy(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  puStack_8 = &LAB_00537ce3;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &vtable_State11_InBattle;
  local_4 = 1;
  _eh_vector_destructor_iterator_((void *)((int)param_1 + 0x23d7),3,0x10,NoOpMethod);
  local_4 = local_4 & 0xffffff00;
  _eh_vector_destructor_iterator_(param_1 + 0x477,0x224,8,ScrubChecksumGuard);
  *param_1 = &PTR_LAB_00553fb0;
  *unaff_FS_OFFSET = local_c;
  return;
}

