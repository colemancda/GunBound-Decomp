/* FUN_0044bf00 - 0x0044bf00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0044bf00(int param_1)

{
  undefined4 *puVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  char *pcVar11;
  byte *pbVar12;
  uint local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  uint local_d0;
  char local_c8 [100];
  byte local_64 [100];
  
  iVar6 = DAT_007934e8;
  if (100 < *(uint *)(g_clientContext + 0x44e24)) {
    ShowErrorDialog(0);
    return;
  }
  *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x6004;
  *(undefined4 *)(iVar6 + 0x44d0) = 6;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_d8 = CONCAT22(uVar3,uVar2);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = DAT_007934e8;
  puVar1 = (undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8);
  *puVar1 = local_d8;
  local_d4 = CONCAT22(uVar3,uVar2);
  puVar1[1] = local_d4;
  iVar6 = *(int *)(iVar4 + 0x44d0);
  *(int *)(iVar4 + 0x44d0) = iVar6 + 8;
  if (*(char *)(param_1 + 0x32f92) == '\0') {
    *(undefined1 *)(iVar6 + 0x4d8 + iVar4) = 0;
    iVar6 = *(int *)(iVar4 + 0x44d0) + 1;
  }
  else {
    *(undefined1 *)(iVar6 + 0x4d8 + iVar4) = 1;
    iVar6 = *(int *)(iVar4 + 0x44d0);
    *(int *)(iVar4 + 0x44d0) = iVar6 + 1;
    *(undefined4 *)(iVar6 + 0x4d1 + iVar4) = *(undefined4 *)(param_1 + 0x32f98);
    iVar6 = *(int *)(iVar4 + 0x44d0);
    *(int *)(iVar4 + 0x44d0) = iVar6 + 4;
    *(undefined4 *)(iVar6 + 0x4d4 + iVar4) = *(undefined4 *)(param_1 + 0x32f94);
    iVar6 = *(int *)(iVar4 + 0x44d0) + 4;
  }
  *(int *)(iVar4 + 0x44d0) = iVar6;
  _qsort(*(void **)(g_clientContext + 0x44e40),*(size_t *)(g_clientContext + 0x44e44),0x450,FUN_0044be40);
  FUN_0044c5f0();
  FUN_0044c630();
  FUN_0044c630();
  pcVar11 = local_c8;
  for (iVar6 = 0x19; iVar6 != 0; iVar6 = iVar6 + -1) {
    pcVar11[0] = '\0';
    pcVar11[1] = '\0';
    pcVar11[2] = '\0';
    pcVar11[3] = '\0';
    pcVar11 = pcVar11 + 4;
  }
  local_dc = 0;
  iVar6 = g_clientContext;
  if (*(int *)(g_clientContext + 0x44e54) != 0) {
    do {
      local_d0 = 0;
      if (*(int *)(iVar6 + 0x44e24) != 0) {
        do {
          if ((*(uint *)(iVar6 + 0x44e24) <= local_d0) || (*(uint *)(iVar6 + 0x44e54) <= local_dc))
          {
                    /* WARNING: Subroutine does not return */
            ThrowCxxException(0x80070057);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar4 = PeekPacketChecksumState();
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = g_clientContext;
          if ((iVar4 == iVar5) && (local_c8[local_d0] == '\0')) {
            local_64[local_dc] = (byte)local_d0;
            local_c8[local_d0] = '\x01';
            break;
          }
          local_d0 = local_d0 + 1;
        } while (local_d0 < *(uint *)(g_clientContext + 0x44e24));
      }
      local_dc = local_dc + 1;
    } while (local_dc < *(uint *)(iVar6 + 0x44e54));
  }
  iVar4 = DAT_007934e8;
  uVar7 = 0;
  if (*(uint *)(iVar6 + 0x44e54) != 0) {
    do {
      if (local_64[uVar7] != uVar7) {
        *(undefined2 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) =
             *(undefined2 *)(iVar6 + 0x44e24);
        iVar5 = *(int *)(iVar4 + 0x44d0);
        *(int *)(iVar4 + 0x44d0) = iVar5 + 2;
        uVar7 = *(uint *)(iVar6 + 0x44e24);
        uVar8 = ((int)uVar7 < 0) - 1 & uVar7;
        pbVar10 = local_64;
        pbVar12 = (byte *)(iVar5 + 0x4d2 + iVar4);
        for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(undefined4 *)pbVar12 = *(undefined4 *)pbVar10;
          pbVar10 = pbVar10 + 4;
          pbVar12 = pbVar12 + 4;
        }
        for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
          *pbVar12 = *pbVar10;
          pbVar10 = pbVar10 + 1;
          pbVar12 = pbVar12 + 1;
        }
        *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + uVar7;
        goto LAB_0044c2d6;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)(iVar6 + 0x44e54));
  }
  *(undefined2 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = 0;
  *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 2;
LAB_0044c2d6:
  FUN_004d25e0();
  FUN_004d2680();
  FUN_00449250(param_1,0,0);
  return;
}

