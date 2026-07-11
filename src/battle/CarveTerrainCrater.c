/* CarveTerrainCrater - 0x004e4450 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void CarveTerrainCrater(int param_1,int param_2,int param_3)

{
  int iVar1;
  char cVar2;
  int in_EAX;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int unaff_ESI;
  int iVar9;
  undefined4 *puVar10;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  iVar8 = in_EAX / 2;
  local_38 = 1 - iVar8;
  iVar9 = iVar8 * -2 + 5;
  local_34 = 0;
  local_2c = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_18 = iVar8 * param_3;
  uVar5 = (local_18 / iVar3) * 2;
  iVar3 = param_1 - local_18 / iVar3;
  if ((-1 < param_2) && (param_2 < *(int *)(unaff_ESI + 0x1c))) {
    if (iVar3 < 0) {
      uVar5 = uVar5 + iVar3;
      iVar3 = 0;
    }
    if (*(int *)(unaff_ESI + 0x18) < (int)(uVar5 + iVar3)) {
      uVar5 = *(int *)(unaff_ESI + 0x18) - iVar3;
    }
    puVar10 = (undefined4 *)
              (*(int *)(unaff_ESI + 0x18) * param_2 + *(int *)(unaff_ESI + 0x34) + iVar3);
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined1 *)puVar10 = 0;
      puVar10 = (undefined4 *)((int)puVar10 + 1);
    }
  }
  if (-1 < iVar8) {
    local_1c = param_2 + iVar8;
    local_14 = param_2;
    local_28 = param_2 - iVar8;
    local_20 = 0;
    local_30 = iVar8;
    do {
      local_34 = local_34 + 1;
      local_20 = local_20 + param_3;
      local_14 = local_14 + 1;
      param_2 = param_2 + -1;
      iVar4 = iVar9;
      iVar3 = local_2c;
      if (-1 < local_38) {
        local_30 = local_30 + -1;
        local_1c = local_1c + -1;
        local_28 = local_28 + 1;
        local_18 = local_18 - param_3;
        iVar4 = iVar9 + 2;
        iVar3 = iVar9;
      }
      local_38 = local_38 + iVar3;
      local_2c = local_2c + 2;
      iVar9 = iVar4 + 2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = (local_20 / iVar3) * 2;
      iVar3 = param_1 - local_20 / iVar3;
      if ((-1 < local_1c) && (local_1c < *(int *)(unaff_ESI + 0x1c))) {
        iVar4 = iVar3;
        uVar6 = uVar5;
        if (iVar3 < 0) {
          uVar6 = uVar5 + iVar3;
          iVar4 = 0;
        }
        iVar1 = *(int *)(unaff_ESI + 0x18);
        if (iVar1 < (int)(uVar6 + iVar4)) {
          uVar6 = iVar1 - iVar4;
        }
        puVar10 = (undefined4 *)(local_1c * iVar1 + *(int *)(unaff_ESI + 0x34) + iVar4);
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined1 *)puVar10 = 0;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
      }
      if ((-1 < local_28) && (local_28 < *(int *)(unaff_ESI + 0x1c))) {
        if (iVar3 < 0) {
          uVar5 = uVar5 + iVar3;
          iVar3 = 0;
        }
        iVar4 = *(int *)(unaff_ESI + 0x18);
        if (iVar4 < (int)(iVar3 + uVar5)) {
          uVar5 = iVar4 - iVar3;
        }
        puVar10 = (undefined4 *)(local_28 * iVar4 + *(int *)(unaff_ESI + 0x34) + iVar3);
        for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar10 = 0;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = (local_18 / iVar3) * 2;
      iVar3 = param_1 - local_18 / iVar3;
      if ((-1 < local_14) && (local_14 < *(int *)(unaff_ESI + 0x1c))) {
        iVar4 = iVar3;
        uVar6 = uVar5;
        if (iVar3 < 0) {
          uVar6 = uVar5 + iVar3;
          iVar4 = 0;
        }
        iVar1 = *(int *)(unaff_ESI + 0x18);
        if (iVar1 < (int)(uVar6 + iVar4)) {
          uVar6 = iVar1 - iVar4;
        }
        puVar10 = (undefined4 *)(local_14 * iVar1 + *(int *)(unaff_ESI + 0x34) + iVar4);
        for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined1 *)puVar10 = 0;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
      }
      if ((-1 < param_2) && (param_2 < *(int *)(unaff_ESI + 0x1c))) {
        if (iVar3 < 0) {
          uVar5 = uVar5 + iVar3;
          iVar3 = 0;
        }
        iVar4 = *(int *)(unaff_ESI + 0x18);
        if (iVar4 < (int)(iVar3 + uVar5)) {
          uVar5 = iVar4 - iVar3;
        }
        puVar10 = (undefined4 *)(param_2 * iVar4 + *(int *)(unaff_ESI + 0x34) + iVar3);
        for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *puVar10 = 0;
          puVar10 = puVar10 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)puVar10 = 0;
          puVar10 = (undefined4 *)((int)puVar10 + 1);
        }
      }
    } while (local_34 <= local_30);
  }
  cVar2 = PeekPacketChecksumBool();
  if ((cVar2 != '\x01') && ((&DAT_005f2f54)[g_clientContext] != '\x01')) {
    local_30 = iVar8 + 3;
    local_38 = 1 - local_30;
    local_34 = 0;
    iVar8 = local_30 * -2 + 5;
    local_2c = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_10 = local_30 * param_3;
    DarkenTerrainScorchRow((local_10 / iVar3) * 2);
    if (-1 < local_30) {
      iVar3 = 0;
      do {
        local_34 = local_34 + 1;
        iVar3 = iVar3 + param_3;
        iVar4 = iVar8;
        iVar9 = local_2c;
        if (-1 < local_38) {
          local_30 = local_30 + -1;
          local_10 = local_10 - param_3;
          iVar4 = iVar8 + 2;
          iVar9 = iVar8;
        }
        local_38 = local_38 + iVar9;
        local_2c = local_2c + 2;
        iVar8 = iVar4 + 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar9 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar9 = (iVar3 / iVar9) * 2;
        DarkenTerrainScorchRow(iVar9);
        DarkenTerrainScorchRow(iVar9);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar9 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar9 = (local_10 / iVar9) * 2;
        DarkenTerrainScorchRow(iVar9);
        DarkenTerrainScorchRow(iVar9);
      } while (local_34 <= local_30);
    }
    puVar10 = (undefined4 *)(unaff_ESI + 0x51);
    for (iVar3 = 0x200; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
  }
  return;
}

