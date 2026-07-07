/* FUN_004cea70 - 0x004cea70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004cea70(int param_1)

{
  undefined *puVar1;
  byte bVar2;
  uint uVar3;
  int *piVar4;
  char in_AL;
  char cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte bVar11;
  uint uVar12;
  
  if (in_AL != '\0') {
    *(undefined1 *)(param_1 + 0x10bd) = 1;
    *(undefined4 *)(param_1 + 0x10c0) = 0;
  }
  uVar12 = *(uint *)(param_1 + 0x10c0);
  do {
    if (0x3f < (int)uVar12) {
LAB_004ceb04:
      if (uVar12 != 0x40) {
        if (uVar12 != *(uint *)(param_1 + 0x10c0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar8 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = DAT_005b3484;
          cVar5 = FUN_004065a0();
          if ((cVar5 == '\0') && ((&DAT_006a7758)[iVar6] != '\0')) {
            iVar10 = 400;
            if (399 < iVar8) {
              iVar10 = iVar8;
            }
            iVar9 = *(int *)(&DAT_006a7720 + iVar6) + -400;
            if ((iVar10 <= iVar9) && (iVar9 = iVar8, iVar8 < 400)) {
              iVar9 = 400;
            }
            iVar8 = -0x14;
            if (-0x15 < iVar7) {
              iVar8 = iVar7;
            }
            iVar10 = *(int *)(&DAT_006a7724 + iVar6) + -0x104;
            if ((iVar8 <= *(int *)(&DAT_006a7724 + iVar6) + -0x104) &&
               (iVar10 = -0x14, -0x15 < iVar7)) {
              iVar10 = iVar7;
            }
            *(int *)(&DAT_006a7718 + iVar6) = iVar9;
            *(int *)(&DAT_006a771c + iVar6) = iVar10;
          }
        }
        *(uint *)(param_1 + 0x10c0) = uVar12;
        return;
      }
      *(undefined1 *)(param_1 + 0x10bd) = 0;
      FUN_0043c3c0();
      if (*(int *)(DAT_005b3484 + 0x621e0) != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar6 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (((iVar6 < 1) && (cVar5 = FUN_004065a0(), cVar5 != '\0')) &&
           (cVar5 = FUN_004065a0(), cVar5 == '\0')) {
          iVar6 = *(int *)(DAT_005b3484 + 0x621e0);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = _rand();
          *(byte *)(iVar6 + 0x8bc0) = (byte)iVar7;
          iVar7 = _rand();
          bVar2 = *(byte *)(iVar6 + 0x8bc0);
          *(byte *)(iVar6 + 0x8bc1) = (byte)iVar7;
          bVar11 = '\x01' << (bVar2 & 7);
          bVar11 = ~bVar11 & (byte)iVar7 | bVar11;
          *(byte *)(iVar6 + 0x8bc1) = bVar11;
          *(byte *)(iVar6 + 0x8bc2) = bVar11 + bVar2 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar8 = DAT_007934e8;
          iVar7 = DAT_005b3484;
          *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
          *(undefined2 *)(iVar8 + 0x4d4) = 0x4100;
          *(undefined4 *)(iVar8 + 0x4d6) = *(undefined4 *)(*(int *)(iVar7 + 0x621e0) + 0xb0b0);
          iVar6 = *(int *)(iVar8 + 0x44d0);
          *(int *)(iVar8 + 0x44d0) = iVar6 + 4;
          *(undefined1 *)(iVar6 + 0x4d4 + iVar8) =
               *(undefined1 *)(*(int *)(iVar7 + 0x621e0) + 0xb0ac);
          *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 1;
          FUN_004d2680();
          Replay_AppendEvent(0xc304);
          iVar6 = DAT_005b3484;
          *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) =
               *(undefined4 *)(*(int *)(DAT_005b3484 + 0x621e0) + 0xb0b0);
          puVar1 = &DAT_00e9aad0 + g_replayEventCursor;
          g_replayEventCursor = g_replayEventCursor + 4;
          *puVar1 = *(undefined1 *)(*(int *)(iVar6 + 0x621e0) + 0xb0ac);
          g_replayEventCursor = g_replayEventCursor + 1;
          Replay_FlushEvent();
        }
      }
      FUN_004cee30(param_1);
      return;
    }
    iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + DAT_005b3484) + 0x1c);
    uVar3 = *(uint *)(iVar6 + 4);
    while (uVar3 < 0x186a4) {
      if (uVar3 == 0x186a3) {
        piVar4 = *(int **)(iVar6 + 0x10);
        uVar3 = piVar4[2];
        goto joined_r0x004cead6;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar3 = *(uint *)(iVar6 + 4);
    }
LAB_004ceafa:
    uVar12 = uVar12 + 1;
  } while( true );
joined_r0x004cead6:
  if (uVar12 < uVar3) goto LAB_004ceafa;
  if (uVar3 == uVar12) {
    cVar5 = (**(code **)(*piVar4 + 0x24))(*(undefined4 *)(param_1 + 0x10a0));
    if (cVar5 != '\0') goto LAB_004ceb04;
    goto LAB_004ceafa;
  }
  piVar4 = (int *)piVar4[4];
  uVar3 = piVar4[2];
  goto joined_r0x004cead6;
}

