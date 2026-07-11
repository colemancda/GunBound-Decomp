/* FUN_004e1d50 - 0x004e1d50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004e1d50(int param_1)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005390bc;
  *unaff_FS_OFFSET = &local_c;
  *(undefined1 *)(param_1 + 0x220) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  EncodeOutgoingPacketField(0);
  local_4 = 0;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x224),0x224,3,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 1;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x890),0x224,3,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x1128) = 0;
  *(undefined4 *)(param_1 + 0xf1c) = 0;
  EncodeOutgoingPacketField(0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
  *(undefined4 *)(param_1 + 0xefc) = 0xffffff9c;
  *(undefined4 *)(param_1 + 0xf04) = 1;
  iVar1 = _rand();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(iVar1 % 10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(iVar1 % 10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(iVar1 % 10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

