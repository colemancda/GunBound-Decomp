/* FUN_0044bf00 - 0x0044bf00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 6 argless PeekPacketChecksumState() calls.  The first four
 * are the equipped-avatar cells g_clientContext + 0x3ac08 / 0x3ae2c /
 * 0x3b050 / 0x3b274 (the same four LoadAvatarSprites reads).  The pair in
 * the double loop compares one record from each of the two 0x450-stride
 * catalog arrays: *(ctx+0x44e50) indexed by local_dc (its count is
 * ctx+0x44e54) and *(ctx+0x44e20) indexed by local_d0 (count ctx+0x44e24)
 * - exactly the two bounds the C's own ThrowCxxException guard tests -
 * each at record offset +0x22c, the part-code cell.  Confirmed at
 * 0x44c17e/0x44c164 (`mov esi,[eax+0x44e50]` / `mov edi,[eax+0x44e20]`
 * plus the frame cursors that advance by 0x450).
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
  
  iVar6 = g_connectionContextA;
  if (100 < *(uint *)(g_clientContext + 0x44e24)) {
    ShowErrorDialog(0);
    return;
  }
  *(undefined2 *)(g_connectionContextA + 0x4d4) = 0x6004;
  *(undefined4 *)(iVar6 + 0x44d0) = 6;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ac08));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ae2c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_d8 = CONCAT22(uVar3,uVar2);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b050));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b274));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = g_connectionContextA;
  puVar1 = (undefined4 *)(*(int *)(g_connectionContextA + 0x44d0) + 0x4d0 + g_connectionContextA);
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
  AtlArray_RemoveAll_450((int *)(g_clientContext + 0x44e50));
  FUN_0044c630((int)(g_clientContext + 0x44e50),(int)(g_clientContext + 0x44e30));
  FUN_0044c630((int)(g_clientContext + 0x44e50),(int)(g_clientContext + 0x44e40));
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
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iVar4 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e50) + local_dc * 0x450 + 0x22c));
          iVar5 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + local_d0 * 0x450 + 0x22c));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
  iVar4 = g_connectionContextA;
  uVar7 = 0;
  if (*(uint *)(iVar6 + 0x44e54) != 0) {
    do {
      if (local_64[uVar7] != uVar7) {
        *(undefined2 *)(*(int *)(g_connectionContextA + 0x44d0) + 0x4d0 + g_connectionContextA) =
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
  *(undefined2 *)(*(int *)(g_connectionContextA + 0x44d0) + 0x4d0 + g_connectionContextA) = 0;
  *(int *)(iVar4 + 0x44d0) = *(int *)(iVar4 + 0x44d0) + 2;
LAB_0044c2d6:
  EncodePacketBody(0,iVar4);
  SendOutgoingPacket(iVar4);
  FUN_00449250(param_1,0,0);
  return;
}

