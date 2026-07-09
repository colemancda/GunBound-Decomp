/* FUN_004d2680 - 0x004d2680 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004d2680(void)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  int unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_45c [8];
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00540806;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  iVar1 = *(int *)(unaff_ESI + 0x44d0);
  *(undefined2 *)(unaff_ESI + 0x4d0) = *(undefined2 *)(unaff_ESI + 0x44d0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar3 + iVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = FUN_0040a7d0(unaff_ESI + 0x84,local_230,0x343fd);
  local_4 = 0;
  FUN_0040a5f0(uVar4,local_454,0x269ec3);
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  *(undefined2 *)(unaff_ESI + 0x4d2) = uVar2;
  if (local_440 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_45c);
  }
  local_4 = 0xffffffff;
  if (local_21c != 0) {
    FUN_0040a240();
    FUN_0040b540(local_45c);
  }
  FUN_004e5ac0(*(undefined4 *)(unaff_ESI + 0x84e0),*(undefined4 *)(unaff_ESI + 0x44d0));
  *(undefined4 *)(unaff_ESI + 0x84ec) = 0;
  *unaff_FS_OFFSET = local_c;
  return;
}

