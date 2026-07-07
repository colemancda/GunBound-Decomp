/* FUN_0040a500 - 0x0040a500 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


int FUN_0040a500(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_238 [28];
  int local_21c;
  undefined1 local_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00538e6a;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_10 = 0;
  local_21c = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 1;
  iVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(-iVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(param_2 + 0x220) = 0;
  *(undefined4 *)(param_2 + 0x14) = 0;
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar2);
  local_4 = local_4 & 0xffffff00;
  if (local_21c != 0) {
    FUN_0040a240();
    FUN_0040b540(local_238);
  }
  *unaff_FS_OFFSET = local_c;
  return param_2;
}

