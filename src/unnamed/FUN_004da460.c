/* FUN_004da460 - 0x004da460 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004da471) */
/* WARNING: Removing unreachable block (ram,0x004da47b) */

undefined4 FUN_004da460(int param_1,undefined4 param_2,uint param_3)

{
  int *piVar1;
  char cVar2;
  char extraout_AL;
  char extraout_AL_00;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint3 extraout_var;
  uint3 extraout_var_00;
  uint3 extraout_var_01;
  uint3 extraout_var_02;
  undefined4 extraout_EAX;
  uint3 uVar7;
  uint3 extraout_var_03;
  uint3 extraout_var_04;
  undefined4 extraout_EAX_00;
  uint3 extraout_var_05;
  uint uVar6;
  int3 iVar8;
  uint3 extraout_var_06;
  char cVar9;
  bool bVar10;
  char cVar11;
  
  if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
    piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
    uVar6 = piVar1[2];
    while (uVar6 < 4) {
      if (uVar6 == 3) {
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
      uVar6 = piVar1[2];
    }
  }
  cVar9 = (char)param_2;
  DAT_0056d118 = (cVar9 != '\x01') - 1;
  if ((char)param_3 != '\0') {
    /* Ghidra emitted a bare `return;` in a value-returning function;
     * MSVC falls through with whatever's in EAX, gcc 14 rejects it
     * (-Wreturn-mismatch). This path's result is unused by callers -
     * return 0 to satisfy both toolchains without inventing a value. */
    return 0;
  }
  if (cVar9 == '\0') {
LAB_004da4f7:
    param_3 = param_3 & 0xffffff00;
  }
  else {
    param_3 = 1;
    if (*(char *)(param_1 + 0x4cc) != '\0') goto LAB_004da4f7;
  }
  FUN_00406300(param_2);
  FUN_00406300(param_2);
  FUN_00406300(param_2);
  if (((char)param_3 == '\0') || (*(char *)(g_clientContext + 0x45122) == '\0')) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  FUN_00406300(uVar3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  FUN_00406300(param_3);
  if ((cVar9 == '\0') ||
     (cVar2 = FUN_0040b390(g_clientContext + 0x3b49c,g_clientContext + 0x3b6c4), cVar2 == '\0')) {
    cVar2 = '\0';
    bVar10 = false;
  }
  else {
    bVar10 = true;
    cVar2 = '\x01';
  }
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  param_3 = iVar4 == iVar5;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00406300(param_3);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  FUN_00406300(cVar2);
  if ((bVar10) && (*(char *)(g_clientContext + 0x45127) != '\0')) {
    iVar4 = CONCAT31(extraout_var,1);
  }
  else {
    iVar4 = (uint)extraout_var << 8;
  }
  FUN_00406300(iVar4);
  if ((bVar10) && (*(char *)(g_clientContext + 0x45127) != '\0')) {
    iVar4 = CONCAT31(extraout_var_00,1);
  }
  else {
    iVar4 = (uint)extraout_var_00 << 8;
  }
  FUN_00406300(iVar4);
  if ((bVar10) && (*(char *)(g_clientContext + 0x45127) != '\0')) {
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  FUN_00406300(uVar3);
  if ((bVar10) && (*(char *)(g_clientContext + 0x45127) != '\0')) {
    iVar4 = CONCAT31(extraout_var_01,1);
  }
  else {
    iVar4 = (uint)extraout_var_01 << 8;
  }
  FUN_00406300(iVar4);
  uVar7 = extraout_var_02;
  if (bVar10) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = (uint3)((uint)extraout_EAX >> 8);
    if ((iVar4 == 1) ||
       (PacketChecksumNotEquals(g_clientContext + 0x45354,3), uVar7 = extraout_var_03,
       extraout_AL == '\0')) goto LAB_004da901;
    iVar4 = CONCAT31(extraout_var_03,1);
  }
  else {
LAB_004da901:
    iVar4 = (uint)uVar7 << 8;
  }
  FUN_00406300(iVar4);
  uVar7 = extraout_var_04;
  if (bVar10) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = (uint3)((uint)extraout_EAX_00 >> 8);
    if ((iVar4 == 1) ||
       (PacketChecksumNotEquals(g_clientContext + 0x45354,3), uVar7 = extraout_var_05,
       extraout_AL_00 == '\0')) goto LAB_004da964;
    iVar4 = CONCAT31(extraout_var_05,1);
  }
  else {
LAB_004da964:
    iVar4 = (uint)uVar7 << 8;
  }
  FUN_00406300(iVar4);
  cVar11 = '\0';
  if (bVar10) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar11 = cVar2;
    if ((iVar4 == 1) || (cVar2 = PacketChecksumNotEquals(g_clientContext + 0x45354,3), cVar2 == '\0'))
    goto LAB_004da9cb;
    uVar3 = 1;
  }
  else {
LAB_004da9cb:
    uVar3 = 0;
  }
  uVar6 = FUN_00406300(uVar3);
  if (cVar11 != '\0') {
    uVar6 = (uint)*(char *)(g_clientContext + 0x44ef8);
    if (1 < *(int *)(&DAT_0056d350 + uVar6 * 4)) {
      iVar8 = (int3)(*(char *)(g_clientContext + 0x44ef8) >> 7);
      uVar6 = CONCAT31(iVar8,cVar9);
      if (cVar9 != '\0') {
        uVar6 = CONCAT31(iVar8,1);
        goto LAB_004daa0a;
      }
    }
  }
  uVar6 = uVar6 & 0xffffff00;
LAB_004daa0a:
  FUN_00406300(uVar6);
  if (((cVar11 == '\0') || (*(int *)(&DAT_0056d350 + *(char *)(g_clientContext + 0x44ef8) * 4) < 2)) ||
     (cVar9 == '\0')) {
    iVar4 = (uint)extraout_var_06 << 8;
  }
  else {
    iVar4 = CONCAT31(extraout_var_06,1);
  }
  FUN_00406300(iVar4);
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

