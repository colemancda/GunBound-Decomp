/* FUN_0050a320 - 0x0050a320 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_0050a320(int param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined *puVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  uint local_468;
  undefined1 local_45c [1104];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053cf4d) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar2 = g_gameStateVTableArray[7];
  uVar7 = *(uint *)(param_1 + 0x94);
  if (uVar7 != 0xffffffff) {
    uVar1 = *(uint *)(g_gameStateVTableArray[7] + 0x454);
    iVar4 = FUN_0050cdb0();
    local_468 = iVar4 + uVar1;
    if ((local_468 == 0xffffffff) &&
       (((*(int *)(param_1 + 0x2c) + 0x68 <= param_3 || (local_468 = uVar1, uVar1 == 0xffffffff)) &&
        (*(int *)(param_1 + 0x2c) + 0x156 < param_3)))) {
      local_468 = uVar1 + 0xe;
    }
    if (*(int *)(g_clientContext + 0x44e24) - 1U <= local_468) {
      local_468 = *(int *)(g_clientContext + 0x44e24) - 1;
    }
    if (local_468 != uVar7) {
      FUN_00428550(local_45c);
      local_4 = 0;
      if (*(uint *)(g_clientContext + 0x44e24) <= *(uint *)(param_1 + 0x94)) {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      FUN_0044c740();
      FUN_0044c6a0(g_clientContext + 0x44e20);
      FUN_0050cff0(g_clientContext + 0x44e20,local_468,local_45c,1);
      FUN_0044b0b0(puVar2);
      iVar4 = 0;
      do {
        iVar6 = *(int *)(param_1 + 0x94);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar5 == iVar6) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar7 = local_468;
LAB_0050a582:
          EncodeOutgoingPacketField(uVar7);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        else {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)local_468 < iVar6) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar6 + 1);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          iVar6 = *(int *)(param_1 + 0x94);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 < iVar5) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            uVar7 = iVar6 - 1;
            goto LAB_0050a582;
          }
        }
        iVar4 = iVar4 + 0x224;
      } while (iVar4 < 0x890);
      *(undefined1 *)(param_1 + 0x91) = 1;
      local_4 = 0xffffffff;
      FUN_00426810(local_45c);
    }
  }
  *(undefined4 *)(param_1 + 0x94) = 0xffffffff;
  *(undefined1 *)(param_1 + 0x90) = 0;
  cVar3 = Widget_MouseUpChildren(param_2,param_3);
  if ((cVar3 == '\0') &&
     (((*(char *)(param_1 + 0x1e) != '\0' || (param_2 <= *(int *)(param_1 + 0x28))) ||
      ((*(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28) <= param_2 ||
       ((param_3 <= *(int *)(param_1 + 0x2c) ||
        (*(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c) <= param_3)))))))) {
    uVar8 = 0;
  }
  else {
    uVar8 = 1;
  }
  return uVar8;
}

