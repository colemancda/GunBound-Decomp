/* FUN_004f43a0 - 0x004f43a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004f43a0(int param_1,char *param_2)

{
  char cVar1;
  float fVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  void *pvVar7;
  undefined4 *puVar8;
  char local_91;
  int local_90;
  int local_8c;
  undefined1 local_88 [4];
  undefined1 local_84 [3];
  undefined4 uStack_81;
  undefined1 local_7c [124];
  
  iVar4 = FindTextureCacheEntryByName(param_2);
  if (iVar4 != 0) {
    return 1;
  }
  pcVar5 = param_2;
  do {
    cVar1 = *pcVar5;
    pcVar5[(int)&uStack_81 + (1 - (int)param_2)] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  puVar3 = &uStack_81;
  do {
    puVar8 = puVar3;
    puVar3 = (undefined4 *)((int)puVar8 + 1);
  } while (*(char *)((int)puVar8 + 1) != '\0');
  *(undefined4 *)((int)puVar8 + 1) = DAT_00557554;
  *(undefined1 *)((int)puVar8 + 5) = DAT_00557558;
  iVar4 = FUN_004f1390(0);
  if (iVar4 == 0) {
    return 0;
  }
  ReadXFSEntryByte(iVar4,&local_8c);
  ReadXFSEntryByte(iVar4,local_88);
  ReadXFSEntryByte(iVar4,&local_91);
  ReadXFSEntryByte(iVar4,local_84);
  iVar6 = FUN_004f4750(&local_90);
  if (iVar6 == -1) {
    local_90 = FUN_004f4350();
    FUN_004f4170(local_8c);
    iVar6 = 0;
  }
  ReadXFSEntryByte(iVar4,param_1 + 0x401f8);
  FUN_004f41d0(param_1 + 0x401f8,iVar6);
  FUN_004f1460();
  pvVar7 = operator_new(0x9c);
  pcVar5 = param_2;
  do {
    cVar1 = *pcVar5;
    pcVar5[(int)pvVar7 - (int)param_2] = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  *(int *)((int)pvVar7 + 0x94) = local_90;
  fVar2 = (float)local_8c * _DAT_0055801c;
  *(int *)((int)pvVar7 + 0x8c) = iVar6;
  *(float *)((int)pvVar7 + 0x88) = fVar2;
  *(float *)((int)pvVar7 + 0x80) =
       (float)(iVar6 % (int)(0x100 / (longlong)local_8c)) * *(float *)((int)pvVar7 + 0x88);
  local_90 = iVar6 / (int)(0x100 / (longlong)local_8c);
  *(float *)((int)pvVar7 + 0x84) = (float)local_90 * *(float *)((int)pvVar7 + 0x88);
  *(char *)((int)pvVar7 + 0x90) = local_91;
  FUN_004f45d0(pvVar7);
  pcVar5 = (char *)(*(int *)(param_1 + 0x401b8) * 0x200 + 0x1b8 + param_1);
  do {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    *pcVar5 = cVar1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  *(int *)(param_1 + 0x401b8) = *(int *)(param_1 + 0x401b8) + 1;
  return 1;
}

