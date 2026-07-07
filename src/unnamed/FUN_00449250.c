/* FUN_00449250 - 0x00449250 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0044929c) */
/* WARNING: Removing unreachable block (ram,0x004492a6) */
/* WARNING: Removing unreachable block (ram,0x0044936e) */
/* WARNING: Removing unreachable block (ram,0x00449378) */

void FUN_00449250(int param_1,char param_2,char param_3)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  char cVar4;
  undefined4 uVar5;
  uint3 uVar7;
  int iVar6;
  uint3 extraout_var;
  undefined4 extraout_EAX;
  uint3 extraout_var_00;
  bool bVar8;
  
  if (param_2 == '\x01') {
    DAT_0056d118 = 0xffffffff;
LAB_00449272:
    cVar3 = '\x01';
    if (*(char *)(param_1 + 0x32f90) == '\0') goto LAB_00449285;
  }
  else {
    DAT_0056d118 = 0;
    if (param_2 != '\0') goto LAB_00449272;
LAB_00449285:
    cVar3 = '\0';
  }
  if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
    piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
    uVar2 = piVar1[2];
    while (uVar2 < 3) {
      if (uVar2 == 2) {
        if ((piVar1[9] == 3) || (piVar1[9] == -1)) {
          if ((char)piVar1[0x13] == '\x01') {
            (**(code **)(*piVar1 + 4))(s_active_00551e58);
          }
          else {
            (**(code **)(*piVar1 + 4))(s_ready_00551e80);
          }
        }
        break;
      }
      piVar1 = (int *)piVar1[4];
      uVar2 = piVar1[2];
    }
  }
  if (param_3 == '\0') {
    FUN_00406300(cVar3);
    FUN_00406300(cVar3);
    FUN_00406300(cVar3);
    FUN_00406300(cVar3);
    FUN_00406300(cVar3);
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
      piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
      uVar2 = piVar1[2];
      while (uVar2 < 0xf) {
        if (uVar2 == 0xe) {
          (**(code **)(*piVar1 + 4))(s_disable_00551e68);
          break;
        }
        piVar1 = (int *)piVar1[4];
        uVar2 = piVar1[2];
      }
    }
    FUN_00406300(cVar3);
    uVar5 = FUN_00406300(cVar3);
    uVar7 = (uint3)((uint)uVar5 >> 8);
    if (cVar3 == '\0') {
LAB_004493f8:
      iVar6 = (uint)uVar7 << 8;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = extraout_var;
      if (iVar6 == -1) goto LAB_004493f8;
      iVar6 = CONCAT31(extraout_var,1);
    }
    FUN_00406300(iVar6);
  }
  bVar8 = false;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = extraout_EAX;
  if (iVar6 != -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar4 = FUN_00406610(*(char *)(iVar6 + *(int *)(param_1 + 0x450) * 9 + 0x2d54c + param_1) ==
                         '\x01');
    bVar8 = cVar4 != '\0';
    uVar5 = FUN_00406860();
    if ((char)uVar5 != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar4 = *(char *)(iVar6 + *(int *)(param_1 + 0x450) * 9 + 0x2d54c + param_1);
      uVar5 = CONCAT31((int3)((uint)*(int *)(param_1 + 0x450) >> 8),cVar4);
      if (cVar4 == '\0') {
        bVar8 = true;
      }
    }
    if (*(int *)(param_1 + 0x44c) == 3) {
      bVar8 = true;
    }
  }
  uVar7 = (uint3)((uint)uVar5 >> 8);
  if (cVar3 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = extraout_var_00;
    if ((iVar6 != -1) && (bVar8)) {
      iVar6 = CONCAT31(extraout_var_00,1);
      goto LAB_0044951d;
    }
  }
  iVar6 = (uint)uVar7 << 8;
LAB_0044951d:
  FUN_00406300(iVar6);
  return;
}

