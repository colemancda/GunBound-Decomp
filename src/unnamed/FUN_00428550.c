/* FUN_00428550 - 0x00428550 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


int FUN_00428550(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005380ab;
  *unaff_FS_OFFSET = &local_c;
  FUN_00406440();
  *(undefined1 *)(param_1 + 0x228) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x44c) = 0;
  *(undefined4 *)(param_1 + 0x240) = 0;
  EncodeOutgoingPacketField(0);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

