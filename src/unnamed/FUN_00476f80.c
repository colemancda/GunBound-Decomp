/* FUN_00476f80 - 0x00476f80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00476f80(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *unaff_FS_OFFSET;
  int local_464;
  undefined1 local_45c [8];
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053aef6;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_464 = 0;
  do {
    iVar2 = GetPlayerRecordBySlot(g_clientContext);
    if (((iVar2 != 0) && (*(int *)(iVar2 + 0x24) != 0xe)) &&
       (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) {
      FUN_0040aca0(param_1 + 0x40,local_454,iVar2 + 0x90c);
      local_4 = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_440 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_45c);
      }
      FUN_0040aca0(param_1 + 0x264,local_230,iVar2 + 0xb30);
      local_4 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_21c != 0) {
        FUN_0040a240();
        FUN_0040b540(local_45c);
      }
      if (iVar4 * iVar4 + iVar3 * iVar3 < 0x640) {
        *(undefined1 *)(param_1 + 0x14) = 1;
        FUN_00461a20(iVar2);
        goto LAB_0047711f;
      }
    }
    local_464 = local_464 + 1;
    if (7 < local_464) {
LAB_0047711f:
      *unaff_FS_OFFSET = local_c;
      return;
    }
  } while( true );
}

