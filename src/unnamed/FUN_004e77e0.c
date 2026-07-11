/* FUN_004e77e0 - 0x004e77e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e77e0(int param_1)

{
  uint *puVar1;
  char *pcVar2;
  byte bVar3;
  int *piVar4;
  char cVar5;
  int in_EAX;
  int iVar6;
  DWORD DVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  bool bVar12;
  uint local_210;
  int *local_20c;
  undefined4 *local_208;
  undefined4 *local_204;
  undefined4 local_200;
  byte local_1fa;
  char local_1f9;
  undefined4 local_1eb;
  undefined4 local_1e7;
  undefined4 local_1e3;
  
  iVar6 = FUN_004e7740();
  if (iVar6 != in_EAX) {
    return;
  }
  if ((*(int *)(param_1 + 0x44ff0) != 0) && (in_EAX == 1)) {
    FUN_004e5dc0(1,0);
  }
  cVar5 = FUN_004e7660(&local_200,&local_210);
  if (cVar5 != '\x01') {
    return;
  }
  DVar7 = timeGetTime();
  uVar8 = local_210;
  *(DWORD *)(param_1 + 0x4522c) = DVar7;
  if (local_210 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x17c));
    *(undefined4 *)(param_1 + 0x44de4) = 0;
    *(undefined4 *)(param_1 + 0x44de8) = 0;
    *(undefined4 *)(param_1 + 0x13c) = 0;
    uVar8 = 0;
    local_208 = (undefined4 *)(param_1 + 0x40bd8);
    local_20c = (int *)(param_1 + 0x38);
    local_210 = param_1 + 0x58;
    local_204 = (undefined4 *)(param_1 + 0x78);
    *(undefined4 *)(param_1 + 0x144) = 0;
    *(undefined4 *)(param_1 + 0x138) = 0;
    bVar12 = true;
    do {
      piVar4 = local_20c;
      if (!bVar12) goto LAB_004e79e6;
      bVar3 = (byte)uVar8;
      uVar9 = 1 << (bVar3 & 0x1f);
      iVar6 = (uVar8 >> 5) * 4;
      if ((*(uint *)(iVar6 + 0x140 + param_1) & uVar9) != 0) {
        puVar1 = (uint *)(iVar6 + 0x138 + param_1);
        *puVar1 = *puVar1 | uVar9;
        puVar1 = (uint *)(iVar6 + 0x144 + param_1);
        *puVar1 = *puVar1 | uVar9;
        *(short *)(local_210 + 0x4522c) = SUBFIELD(local_200,2,undefined2);
        local_1f9 = *(char *)(uVar8 + 0x3c8 + param_1);
        *(char *)(uVar8 + 0x3c8 + param_1) = local_1f9 + '\x01';
        *(char *)(uVar8 + 0x45294 + param_1) = local_1f9;
        local_1eb = *local_204;
        local_1e7 = local_204[1];
        local_1e3 = local_204[2];
        local_1fa = bVar3;
        if (*(char *)(uVar8 + 0x454e4 + param_1) == '\0') {
          SendUdpDatagram(&local_200,(undefined2)local_200);
          if (*piVar4 != -1) {
            SendUdpDatagram(&local_200,(undefined2)local_200);
          }
        }
        else {
          puVar1 = (uint *)(iVar6 + 0x13c + param_1);
          *puVar1 = *puVar1 | uVar9;
          FUN_004e8040(uVar8);
        }
        puVar10 = &local_200;
        puVar11 = local_208;
        for (iVar6 = 0x80; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar11 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar11 = puVar11 + 1;
        }
        if (SUBFIELD(local_200,2,undefined2) == -0x6000) {
          DVar7 = timeGetTime();
          local_20c[0x11482] = DVar7;
        }
        InterlockedExchange((LONG *)(param_1 + 0x44de0),1);
      }
      uVar8 = uVar8 + 1;
      local_204 = local_204 + 6;
      local_210 = local_210 + 2;
      local_20c = local_20c + 1;
      local_208 = local_208 + 0x80;
      bVar12 = uVar8 < 8;
    } while ((int)uVar8 < 8);
  }
  else {
    if (7 < local_210) {
LAB_004e79e6:
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
    bVar3 = (byte)local_210;
    uVar9 = 1 << (bVar3 & 0x1f);
    iVar6 = (local_210 >> 5) * 4;
    if ((*(uint *)(iVar6 + 0x140 + param_1) & uVar9) == 0) goto LAB_004e7b47;
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x17c));
    *(undefined4 *)(param_1 + 0x44de4) = 0;
    *(undefined4 *)(param_1 + 0x44de8) = 0;
    *(undefined4 *)(param_1 + 0x13c) = 0;
    *(undefined4 *)(param_1 + 0x144) = 0;
    *(undefined4 *)(param_1 + 0x138) = 0;
    *(uint *)(iVar6 + 0x13c + param_1) = *(uint *)(iVar6 + 0x13c + param_1) & ~uVar9;
    puVar1 = (uint *)(iVar6 + 0x138 + param_1);
    *puVar1 = *puVar1 | uVar9;
    puVar1 = (uint *)(iVar6 + 0x144 + param_1);
    *puVar1 = *puVar1 | uVar9;
    *(short *)(param_1 + 0x45284 + uVar8 * 2) = SUBFIELD(local_200,2,undefined2);
    local_1f9 = *(char *)(uVar8 + 0x3c8 + param_1);
    pcVar2 = (char *)(uVar8 + 0x3c8 + param_1);
    *pcVar2 = *pcVar2 + '\x01';
    *(char *)(uVar8 + 0x45294 + param_1) = local_1f9;
    puVar10 = (undefined4 *)(param_1 + (uVar8 * 3 + 0xf) * 8);
    local_1eb = *puVar10;
    local_1e7 = puVar10[1];
    local_1e3 = puVar10[2];
    local_1fa = bVar3;
    if (*(char *)(uVar8 + 0x454e4 + param_1) == '\0') {
      SendUdpDatagram(&local_200,(undefined2)local_200);
      if (*(int *)(param_1 + 0x38 + uVar8 * 4) != -1) {
        SendUdpDatagram(&local_200,(undefined2)local_200);
      }
    }
    else {
      FUN_004e8040(uVar8);
      puVar1 = (uint *)(iVar6 + 0x13c + param_1);
      *puVar1 = *puVar1 | uVar9;
    }
    puVar10 = &local_200;
    puVar11 = (undefined4 *)(uVar8 * 0x200 + 0x40bd8 + param_1);
    for (iVar6 = 0x80; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar11 = puVar11 + 1;
    }
    InterlockedExchange((LONG *)(param_1 + 0x44de0),1);
    if (SUBFIELD(local_200,2,undefined2) == -0x6000) {
      DVar7 = timeGetTime();
      *(DWORD *)(param_1 + 0x45240 + uVar8 * 4) = DVar7;
    }
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x17c));
LAB_004e7b47:
  *(undefined4 *)(param_1 + 0x45280) = 0;
  return;
}

