/* FUN_0042b0b0 - 0x0042b0b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall
FUN_0042b0b0(undefined4 param_1,uint param_2,int param_3,undefined4 param_4,int param_5,int param_6,
            int param_7,char *param_8,char *param_9,undefined4 param_10,int param_11,int param_12,
            char param_13)

{
  char cVar1;
  void *pvVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *unaff_FS_OFFSET;
  int unaff_retaddr;
  undefined1 auStack_4dc [4];
  char acStack_4d8 [132];
  undefined1 auStack_454 [20];
  int iStack_440;
  undefined1 auStack_230 [20];
  int iStack_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053defa;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') goto LAB_0042bab0;
  switch(param_3) {
  case 0:
    piVar3 = operator_new(0xd1d4);
    local_4 = 0;
    if (piVar3 == (int *)0x0) {
LAB_0042b5ad:
      piVar3 = (int *)0x0;
    }
    else {
      FUN_00458b80(piVar3,param_2);
      *piVar3 = (int)&PTR_FUN_00555af8;
    }
    break;
  case 1:
    piVar3 = operator_new(0xd1d4);
    local_4 = 1;
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      FUN_00458b80(piVar3,param_2);
      *piVar3 = (int)&PTR_FUN_00556230;
    }
    local_4 = 0xffffffff;
    FUN_00406500(0);
    goto LAB_0042b60a;
  case 2:
    piVar3 = operator_new(0xd1d4);
    local_4 = 2;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_005562a8;
    break;
  case 3:
    piVar3 = operator_new(0xd1d4);
    local_4 = 3;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_005566a0;
    break;
  case 4:
    piVar3 = operator_new(0xd1d4);
    local_4 = 4;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00556264;
    break;
  case 5:
    piVar3 = operator_new(0xd1d4);
    local_4 = 5;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00555c14;
    break;
  case 6:
    piVar3 = operator_new(0xd1d4);
    local_4 = 6;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00556448;
    break;
  case 7:
    piVar3 = operator_new(0xd1d4);
    local_4 = 7;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_005561ec;
    break;
  case 8:
    piVar3 = operator_new(0xd1d4);
    local_4 = 8;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00555d34;
    break;
  case 9:
    piVar3 = operator_new(0xd1d4);
    local_4 = 9;
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      FUN_00458b80(piVar3,param_2);
      *piVar3 = (int)&PTR_FUN_005560f0;
    }
    local_4 = 0xffffffff;
    if (param_13 != '\0') {
      uVar6 = param_2 & 0x80000007;
      if ((int)uVar6 < 0) {
        uVar6 = (uVar6 - 1 | 0xfffffff8) + 1;
      }
      FUN_00437f70(param_1,param_4,param_5 + -200,uVar6,param_6 != 0);
    }
    goto LAB_0042b60a;
  case 10:
    piVar3 = operator_new(0xd1d4);
    local_4 = 10;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00555f7c;
    break;
  case 0xb:
    piVar3 = operator_new(0xd1d4);
    local_4 = 0xb;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00556640;
    break;
  case 0xc:
    piVar3 = operator_new(0xd1d4);
    local_4 = 0xc;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00555f18;
    break;
  case 0xd:
    pvVar2 = operator_new(0xd1d4);
    local_4 = 0xd;
    if (pvVar2 == (void *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)FUN_0046cb60();
    }
    break;
  case 0xe:
    piVar3 = operator_new(0xd1d4);
    local_4 = 0xe;
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      FUN_00458b80(piVar3,param_2);
      *piVar3 = (int)&PTR_FUN_00556038;
    }
    local_4 = 0xffffffff;
    if (param_13 != '\0') {
      uVar6 = param_2 & 0x80000007;
      if ((int)uVar6 < 0) {
        uVar6 = (uVar6 - 1 | 0xfffffff8) + 1;
      }
      FUN_00438100(param_1,param_4,param_5 + -200,uVar6,param_6 != 0);
    }
    goto LAB_0042b60a;
  case 0xf:
    piVar3 = operator_new(0xd1d4);
    local_4 = 0xf;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    FUN_00458b80(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00555d54;
    break;
  default:
    param_3 = 0;
    piVar3 = operator_new(0xd1d4);
    local_4 = 0x10;
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      FUN_00458b80(piVar3,param_2);
      *piVar3 = (int)&PTR_FUN_00555af8;
    }
  }
  local_4 = 0xffffffff;
LAB_0042b60a:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = (**(code **)(*piVar3 + 0x14))();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar3[6] = param_3 + 5000;
  piVar3[0x241] = param_3 + 0x13ec;
  piVar3[0x2b8c] = param_11;
  piVar3[0x2b8d] = param_12;
  piVar3[0x2b8b] = param_6;
  piVar3[0x2b8e] = param_7;
  piVar3[0x2b8f] = (int)param_8;
  iVar5 = FindPreloadedTextureByName(s_avata_00553fa8);
  piVar3[0x15] = iVar5;
  (**(code **)(piVar3[0xe] + 4))(s_normal_00552230);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004064a0(param_12);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004064a0(iVar5 == unaff_retaddr);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = 0xae15 - (int)param_8;
  do {
    cVar1 = *param_8;
    param_8[(int)piVar3 + iVar5] = cVar1;
    param_8 = param_8 + 1;
  } while (cVar1 != '\0');
  iVar5 = 0xae22 - (int)param_9;
  do {
    cVar1 = *param_9;
    param_9[(int)piVar3 + iVar5] = cVar1;
    param_9 = param_9 + 1;
  } while (cVar1 != '\0');
  _sprintf(acStack_4d8,s_tank_d_00553fa0,param_2 + 1);
  iVar5 = FindPreloadedTextureByName(acStack_4d8);
  piVar3[7] = iVar5;
  if ((char)param_12 == '\0') {
    (**(code **)(*piVar3 + 4))(s_tnormal_00553604);
  }
  else {
    (**(code **)(*piVar3 + 4))(s_normal_00552230);
  }
  FUN_0041c360(DAT_005b3484,piVar3);
  if ((char)param_12 == '\0') {
    FUN_0040a8c0(piVar3 + 0x19d1,auStack_454,2);
    local_4 = 0x11;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (iStack_440 != 0) {
      FUN_0040a240();
      FUN_0040b540(auStack_4dc);
    }
    FUN_0040a8c0(piVar3 + 0x1b6c,auStack_454,2);
    local_4 = 0x12;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (iStack_440 != 0) {
      FUN_0040a240();
      FUN_0040b540(auStack_4dc);
    }
    FUN_0040a8c0(piVar3 + 0x1ae3,auStack_454,2);
    local_4 = 0x13;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (iStack_440 != 0) {
      FUN_0040a240();
      FUN_0040b540(auStack_4dc);
    }
    FUN_0040a8c0(piVar3 + 0x1c7e,auStack_230,2);
    local_4 = 0x14;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (iStack_21c != 0) {
      FUN_0040a240();
      FUN_0040b540(auStack_4dc);
    }
  }
  RegisterActiveObject();
LAB_0042bab0:
  *unaff_FS_OFFSET = local_c;
  return;
}

