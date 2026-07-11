/* FUN_004e7de0 - 0x004e7de0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e7de0(int param_1,int param_2,undefined4 *param_3)

{
  LPCRITICAL_SECTION lpCriticalSection;
  uint *puVar1;
  byte bVar2;
  undefined2 uVar3;
  char cVar4;
  DWORD DVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint unaff_EBX;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  if (7 < param_2) {
                    /* WARNING: Subroutine does not return */
    FUN_00426460();
  }
  uVar6 = (uint)param_2;
  if (7 < uVar6) {
                    /* WARNING: Subroutine does not return */
    FUN_00426460();
  }
  puVar1 = (uint *)(param_1 + 0x148 + (uint)(param_2 >> 5) * 4);
  *puVar1 = *puVar1 | 1 << (param_2 & 0x1f);
  lpCriticalSection = (LPCRITICAL_SECTION)(param_1 + 0x45264);
  EnterCriticalSection(lpCriticalSection);
  uVar3 = *(undefined2 *)((int)param_3 + 2);
  *(byte *)(param_1 + 0x452a0) = param_2;
  *(undefined2 *)(param_1 + 0x4529c) = uVar3;
  *(short *)(param_1 + 0x4529e) = (short)unaff_EBX;
  puVar10 = (undefined4 *)(param_1 + 0x452a1);
  puVar11 = param_3;
  puVar9 = puVar10;
  for (uVar7 = unaff_EBX >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar9 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar9 = puVar9 + 1;
  }
  for (uVar7 = unaff_EBX & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined1 *)puVar9 = *(undefined1 *)puVar11;
    puVar11 = (undefined4 *)((int)puVar11 + 1);
    puVar9 = (undefined4 *)((int)puVar9 + 1);
  }
  DAT_0056dca7 = *(undefined1 *)(param_1 + 0x452a9);
  DAT_0056dca5 = *(undefined1 *)(param_1 + 0x452a3);
  DAT_0056dcaa = *(undefined1 *)(param_1 + 0x452a4);
  FUN_004e6f20(param_1 + 0x452c2,unaff_EBX);
  iVar8 = 0x21;
  cVar4 = *(char *)(param_1 + 0x452a9) + *(char *)(param_1 + 0x452a3) + *(char *)(param_1 + 0x452a4)
          + -0x34;
  if (0x21 < (int)unaff_EBX) {
    do {
      cVar4 = cVar4 + *(char *)((int)puVar10 + iVar8);
      iVar8 = iVar8 + 1;
    } while (iVar8 < (int)unaff_EBX);
  }
  if (cVar4 != *(char *)(param_1 + 0x452a5)) {
    if (*(uint *)(param_1 + 0x14c) == uVar6) {
      ShowErrorDialog(1);
    }
    LeaveCriticalSection(lpCriticalSection);
    return;
  }
  if ((*(byte *)(param_1 + 0x4529d) & 0x80) != 0) {
    cVar4 = *(char *)(uVar6 + 0x3c0 + param_1);
    if (*(char *)((int)param_3 + 7) != cVar4) {
      *(undefined1 *)(param_1 + 0x4527c) = 9;
      LeaveCriticalSection(lpCriticalSection);
      return;
    }
    DAT_0056d3d8 = 0xffffffff;
    *(char *)(uVar6 + 0x3c0 + param_1) = cVar4 + '\x01';
  }
  if (*(short *)(param_1 + 0x4529c) == -0x6000) {
    Replay_AppendEvent(0xa001);
    FUN_004e7140(*(undefined1 *)((int)param_3 + 5));
  }
  if (*(short *)(param_1 + 0x4529c) == -0x5fff) {
    bVar2 = *(byte *)((int)param_3 + 5);
    DVar5 = timeGetTime();
    *(DWORD *)(param_1 + 0x454c4 + (uint)bVar2 * 4) =
         DVar5 - *(int *)(param_1 + 0x45240 + (uint)bVar2 * 4) >> 1;
  }
  uVar7 = *(uint *)(param_1 + 0x454b8);
  if ((*(uint *)(param_1 + 0x454bc) <= uVar7) && (cVar4 = FUN_004e8fc0(), cVar4 == '\0')) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x8007000e);
  }
  puVar11 = (undefined4 *)(uVar7 * 0x206 + *(int *)(param_1 + 0x454b4));
  if (puVar11 != (undefined4 *)0x0) {
    puVar9 = (undefined4 *)(param_1 + 0x4529c);
    for (iVar8 = 0x81; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar11 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar11 = puVar11 + 1;
    }
    *(undefined2 *)puVar11 = *(undefined2 *)puVar9;
  }
  *(int *)(param_1 + 0x454b8) = *(int *)(param_1 + 0x454b8) + 1;
  LeaveCriticalSection(lpCriticalSection);
  puVar11 = (undefined4 *)(uVar6 * 0x200 + 0x41bd8 + param_1);
  puVar9 = puVar11;
  for (iVar8 = 0x80; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  for (uVar6 = unaff_EBX >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *puVar11 = *puVar10;
    puVar10 = puVar10 + 1;
    puVar11 = puVar11 + 1;
  }
  for (uVar6 = unaff_EBX & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined1 *)puVar11 = *(undefined1 *)puVar10;
    puVar10 = (undefined4 *)((int)puVar10 + 1);
    puVar11 = (undefined4 *)((int)puVar11 + 1);
  }
  return;
}

