/* FUN_0041ef90 - 0x0041ef90 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4
FUN_0041ef90(int param_1,undefined1 param_2,byte param_3,undefined4 param_4,int param_5,
            undefined4 param_6,undefined2 param_7)

{
  char cVar1;
  char *pcVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  undefined2 *puVar9;
  bool bVar10;
  char acStackY_45805 [284637];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8;
  
  if (((7 < param_3) || (param_5 < 0)) || (0x80 < param_5)) {
    return 0;
  }
  if (8 < *(int *)(param_1 + 0x58b60)) {
    FUN_0041ee10();
  }
  uVar5 = (uint)param_3;
  iVar4 = param_1 + uVar5 * 8;
  pcVar2 = (char *)(uVar5 + 0x457a9 + iVar4);
  if (*(char *)(uVar5 + 0x457a9 + iVar4) == '\0') {
    *(undefined1 *)(*(int *)(param_1 + 0x58b60) * 9 + 0x58b64 + param_1) = 0;
  }
  else {
    iVar4 = 7;
    bVar10 = true;
    pcVar7 = pcVar2;
    pcVar8 = &DAT_00551e24;
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar10 = *pcVar7 == *pcVar8;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    } while (bVar10);
    if (bVar10) {
      param_2 = 5;
    }
    puVar3 = (undefined4 *)(*(int *)(param_1 + 0x58b60) * 9 + 0x58b64 + param_1);
    *puVar3 = *(undefined4 *)pcVar2;
    puVar3[1] = *(undefined4 *)(pcVar2 + 4);
    *(char *)(puVar3 + 2) = pcVar2[8];
  }
  pcVar2 = (char *)(uVar5 * 0xd + 0x457f1 + param_1);
  do {
    cVar1 = *pcVar2;
    pcVar2[(int)(acStackY_45805 + (uVar5 * -0xd - param_1))] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  puVar9 = (undefined2 *)&stack0xffffffeb;
  do {
    pcVar2 = (char *)((int)puVar9 + 1);
    puVar9 = (undefined2 *)((int)puVar9 + 1);
  } while (*pcVar2 != '\0');
  iVar4 = *(int *)(param_1 + 0x58b60);
  *puVar9 = DAT_00553620;
  puVar3 = (undefined4 *)((iVar4 + 0x6569) * 0xe + param_1);
  *puVar3 = local_14;
  puVar3[1] = local_10;
  puVar3[2] = local_c;
  *(undefined1 *)(puVar3 + 3) = local_8;
  pcVar2 = (char *)(*(int *)(param_1 + 0x58b60) * 9 + 0x58b64 + param_1);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = (char *)((*(int *)(param_1 + 0x58b60) + 0x6569) * 0xe + param_1);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FUN_0041b410();
  *(undefined4 *)(param_1 + 0x59154 + *(int *)(param_1 + 0x58b60) * 4) = param_6;
  *(undefined1 *)(*(int *)(param_1 + 0x58b60) + 0x58c4a + param_1) = param_2;
  *(undefined2 *)(param_1 + 0x5917c + *(int *)(param_1 + 0x58b60) * 2) = param_7;
  iVar6 = *(int *)(param_1 + 0x58b60) + 1;
  *(int *)(param_1 + 0x58b60) = iVar6;
  if (0 < iVar4) {
    if (8 < iVar6) {
      FUN_0041ee10();
    }
    FUN_0041b410();
    *(undefined4 *)(param_1 + 0x59154 + *(int *)(param_1 + 0x58b60) * 4) = param_6;
    *(undefined1 *)(*(int *)(param_1 + 0x58b60) + 0x58c4a + param_1) = param_2;
    *(undefined2 *)(param_1 + 0x5917c + *(int *)(param_1 + 0x58b60) * 2) = 0;
    *(int *)(param_1 + 0x58b60) = *(int *)(param_1 + 0x58b60) + 1;
    return 2;
  }
  return 1;
}

