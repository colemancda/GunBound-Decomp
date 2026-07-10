/* FUN_0050a640 - 0x0050a640 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_0050a640(int param_1,int param_2,int param_3)

{
  undefined *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int local_8;
  
  puVar1 = g_gameStateVTableArray[7];
  iVar3 = *(int *)(param_1 + 0x2c) + 0x68;
  if ((*(int *)(param_1 + 0x28) + 0x13 < param_2) && (param_2 < *(int *)(param_1 + 0x28) + 0xc3)) {
    iVar9 = 0;
    iVar8 = *(int *)(param_1 + 0x2c) + 0x79;
    do {
      if ((iVar3 < param_3) && (param_3 < iVar8)) {
        if ((iVar9 != -1) &&
           ((uint)(*(int *)(g_gameStateVTableArray[7] + 0x454) + iVar9) <
            *(uint *)(g_clientContext + 0x44e24))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar9 == iVar3) {
            iVar3 = 0;
            local_8 = 0;
            goto LAB_0050a700;
          }
        }
        break;
      }
      iVar3 = iVar3 + 0x11;
      iVar8 = iVar8 + 0x11;
      iVar9 = iVar9 + 1;
    } while (iVar9 < 0xe);
  }
  goto LAB_0050a8b0;
  while( true ) {
    local_8 = local_8 + 1;
    iVar3 = iVar3 + 0x224;
    if (0x88f < iVar3) break;
LAB_0050a700:
    iVar8 = *(int *)(puVar1 + 0x454);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar4 == iVar8 + iVar9) break;
  }
  if (local_8 != 4) {
    FUN_0044b330(puVar1);
    goto LAB_0050a8b0;
  }
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(puVar1 + 0x454) + iVar9)) {
                    /* WARNING: Subroutine does not return */
    FUN_004010c0(0x80070057);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(puVar1 + 0x454) + iVar9)) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((uVar6 & 0x8000) != 0) goto LAB_0050a89a;
  }
  else {
    if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(puVar1 + 0x454) + iVar9)) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((uVar6 & 0x8000) == 0) {
LAB_0050a89a:
      if ((uVar5 & 0x30000) != 0x30000) goto LAB_0050a8b0;
    }
  }
  EquipAvatarPart(puVar1);
LAB_0050a8b0:
  uVar7 = 0;
  if ((((*(char *)(param_1 + 0x1e) == '\0') && (*(int *)(param_1 + 0x28) < param_2)) &&
      (param_2 < *(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28))) &&
     ((*(int *)(param_1 + 0x2c) < param_3 &&
      (param_3 < *(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c))))) {
    uVar7 = 1;
  }
  return uVar7;
}

