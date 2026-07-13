/* RefreshReadyRoomControls - 0x004da460 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-13): InvokeWidget's own dropped widgetId argument
 * fixed at all 43 call sites here (an angr CFG backward-scan gave the
 * exact per-site id; confirmed strictly linear/sequential, no branch
 * reordering, via full disassembly - unlike HandleTurnTimeoutSlot.c/
 * FUN_004ccd10.c). One site did `uVar6 = InvokeWidget(...)` and used
 * `uVar6` afterward - objdump confirms the real code never reads EAX
 * after that call at all (the actual downstream value comes from a
 * completely separate computation chain), so this was always
 * Ghidra-decompiler confusion, not real data flow; dropped the capture
 * rather than invent one, matching the same pattern already applied to
 * FUN_00449250.c and State09_ReadyRoom_OnCommand.c.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004da471) */
/* WARNING: Removing unreachable block (ram,0x004da47b) */

undefined4 RefreshReadyRoomControls(int param_1,undefined4 param_2,uint param_3)

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
  InvokeWidget(0,param_2);
  InvokeWidget(1,param_2);
  InvokeWidget(300,param_2);
  if (((char)param_3 == '\0') || (*(char *)(g_clientContext + 0x45122) == '\0')) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  InvokeWidget(2,uVar3);
  InvokeWidget(100,param_3);
  InvokeWidget(101,param_3);
  InvokeWidget(102,param_3);
  InvokeWidget(103,param_3);
  InvokeWidget(104,param_3);
  InvokeWidget(105,param_3);
  InvokeWidget(106,param_3);
  InvokeWidget(107,param_3);
  InvokeWidget(108,param_3);
  InvokeWidget(109,param_3);
  InvokeWidget(110,param_3);
  InvokeWidget(111,param_3);
  InvokeWidget(112,param_3);
  InvokeWidget(113,param_3);
  InvokeWidget(114,param_3);
  if ((cVar9 == '\0') ||
     (cVar2 = CompareChecksumMatch(g_clientContext + 0x3b49c,g_clientContext + 0x3b6c4), cVar2 == '\0')) {
    cVar2 = '\0';
    bVar10 = false;
  }
  else {
    bVar10 = true;
    cVar2 = '\x01';
  }
  InvokeWidget(4,cVar2);
  InvokeWidget(5,cVar2);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  iVar5 = PeekPacketChecksumState();
  param_3 = iVar4 == iVar5;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  InvokeWidget(8,param_3);
  InvokeWidget(10,cVar2);
  InvokeWidget(11,cVar2);
  InvokeWidget(12,cVar2);
  InvokeWidget(13,cVar2);
  InvokeWidget(20,cVar2);
  InvokeWidget(21,cVar2);
  InvokeWidget(22,cVar2);
  InvokeWidget(23,cVar2);
  InvokeWidget(30,cVar2);
  InvokeWidget(31,cVar2);
  InvokeWidget(32,cVar2);
  InvokeWidget(33,cVar2);
  if ((bVar10) && (*(char *)(g_clientContext + 0x45127) != '\0')) {
    iVar4 = CONCAT31(extraout_var,1);
  }
  else {
    iVar4 = (uint)extraout_var << 8;
  }
  InvokeWidget(50,iVar4);
  if ((bVar10) && (*(char *)(g_clientContext + 0x45127) != '\0')) {
    iVar4 = CONCAT31(extraout_var_00,1);
  }
  else {
    iVar4 = (uint)extraout_var_00 << 8;
  }
  InvokeWidget(51,iVar4);
  if ((bVar10) && (*(char *)(g_clientContext + 0x45127) != '\0')) {
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  InvokeWidget(52,uVar3);
  if ((bVar10) && (*(char *)(g_clientContext + 0x45127) != '\0')) {
    iVar4 = CONCAT31(extraout_var_01,1);
  }
  else {
    iVar4 = (uint)extraout_var_01 << 8;
  }
  InvokeWidget(53,iVar4);
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
  InvokeWidget(60,iVar4);
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
  InvokeWidget(61,iVar4);
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
  InvokeWidget(62,uVar3);
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
  InvokeWidget(70,uVar6);
  if (((cVar11 == '\0') || (*(int *)(&DAT_0056d350 + *(char *)(g_clientContext + 0x44ef8) * 4) < 2)) ||
     (cVar9 == '\0')) {
    iVar4 = (uint)extraout_var_06 << 8;
  }
  else {
    iVar4 = CONCAT31(extraout_var_06,1);
  }
  InvokeWidget(71,iVar4);
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

