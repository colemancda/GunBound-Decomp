/* CreateMobile - 0x0042b0b0 in the original binary.
 *
 * The battle-mobile factory. `switch(mobileType)` over ids 0..0xF, each
 * `operator_new(0xd1d4)` (the ~53 KB mobile object) + a per-type vtable
 * (PTR_FUN_00555af8, 0x556230, 0x5562a8, ...) sharing base ctor InitMobile;
 * `default` falls back to type 0. It then loads the mobile's "avata"/"tank%d"
 * textures, copies the player name (and a second string) into the object,
 * primes its animation state, and registers it into the client context
 * (FUN_0041c360) and the global active-object list (RegisterActiveObject) - so
 * it constructs AND spawns the mobile into the running battle. Called once per
 * active room slot by State11_InBattle_OnEnter. The interleaved
 * EncodeOutgoingPacketField calls thread the spawn through the lockstep/replay
 * sync stream.
 *
 * Function IDENTITY is confirmed (16-way type->class factory); the BODY is
 * still a raw/near-verbatim Ghidra port (register-args reconstruction, so the
 * param list is unreliable) and not hand-verified. See src/README.md's
 * "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall
CreateMobile(undefined4 param_1,uint param_2,int param_3,undefined4 param_4,int param_5,int param_6,
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
  cVar1 = PeekPacketChecksumBool();
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
      InitMobile(piVar3,param_2);
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
      InitMobile(piVar3,param_2);
      *piVar3 = (int)&PTR_FUN_00556230;
    }
    local_4 = 0xffffffff;
    SetGuardedBool(0);
    goto LAB_0042b60a;
  case 2:
    piVar3 = operator_new(0xd1d4);
    local_4 = 2;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    InitMobile(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_005562a8;
    break;
  case 3:
    piVar3 = operator_new(0xd1d4);
    local_4 = 3;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    InitMobile(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_005566a0;
    break;
  case 4:
    piVar3 = operator_new(0xd1d4);
    local_4 = 4;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    InitMobile(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00556264;
    break;
  case 5:
    piVar3 = operator_new(0xd1d4);
    local_4 = 5;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    InitMobile(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00555c14;
    break;
  case 6:
    piVar3 = operator_new(0xd1d4);
    local_4 = 6;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    InitMobile(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00556448;
    break;
  case 7:
    piVar3 = operator_new(0xd1d4);
    local_4 = 7;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    InitMobile(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_005561ec;
    break;
  case 8:
    piVar3 = operator_new(0xd1d4);
    local_4 = 8;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    InitMobile(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00555d34;
    break;
  case 9:
    piVar3 = operator_new(0xd1d4);
    local_4 = 9;
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      InitMobile(piVar3,param_2);
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
    InitMobile(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00555f7c;
    break;
  case 0xb:
    piVar3 = operator_new(0xd1d4);
    local_4 = 0xb;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    InitMobile(piVar3,param_2);
    *piVar3 = (int)&PTR_FUN_00556640;
    break;
  case 0xc:
    piVar3 = operator_new(0xd1d4);
    local_4 = 0xc;
    if (piVar3 == (int *)0x0) goto LAB_0042b5ad;
    InitMobile(piVar3,param_2);
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
      InitMobile(piVar3,param_2);
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
    InitMobile(piVar3,param_2);
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
      InitMobile(piVar3,param_2);
      *piVar3 = (int)&PTR_FUN_00555af8;
    }
  }
  local_4 = 0xffffffff;
LAB_0042b60a:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
   * 0x42b61e/0x42b645/0x42b666/0x42b687/0x42b6ab/0x42b6cc/0x42b795 (a
   * run of `lea edi,[ebp+N]`, ebp = this function's own piVar3 - the
   * freshly-allocated mobile object) 6 distinct CValueGuard cells at
   * (int)piVar3+0x1a2c/0x90c/0x15e4/0xb30/0x1808/0x1c54 (0xb30 is
   * reused for both the param_5 encode and the following vtable-call
   * result encode). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar3 + 0x1a2c, param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)piVar3 + 0x90c, param_4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((int)piVar3 + 0x15e4, uVar4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)piVar3 + 0xb30, param_5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = (**(code **)(*piVar3 + 0x14))();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)piVar3 + 0xb30, uVar4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((int)piVar3 + 0x1808, uVar4);
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
  EncodeGuardedBool(param_12);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42b795
   * (`lea edi,[ebp+0x1c54]`, ebp = piVar3) the cell is
   * (int)piVar3+0x1c54. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar3 + 0x1c54, 1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(iVar5 == unaff_retaddr);
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
  FUN_0041c360(g_clientContext,piVar3);
  if ((char)param_12 == '\0') {
    EncodeChecksumDeltaDiv(piVar3 + 0x19d1,auStack_454,2);
    local_4 = 0x11;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
     * 0x42b8da/0x42b95b (`lea edi,[ebp+0x6968]` / `lea edi,[ebp+0x6fd4]`,
     * ebp = piVar3) two FRESH CValueGuard cells distinct from the
     * EncodeChecksumDeltaDiv source cell just above (piVar3+0x19d1 /
     * +0x1b6c) - Peek() here reads back EncodeChecksumDeltaDiv's own
     * return value, not the LEA'd cell, so the LEA only supplies self for
     * this EncodeOutgoingPacketField. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)piVar3 + 0x6968, uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (iStack_440 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(auStack_4dc);
    }
    EncodeChecksumDeltaDiv(piVar3 + 0x1b6c,auStack_454,2);
    local_4 = 0x12;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField((int)piVar3 + 0x6fd4, uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (iStack_440 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(auStack_4dc);
    }
    EncodeChecksumDeltaDiv(piVar3 + 0x1ae3,auStack_454,2);
    local_4 = 0x13;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
     * 0x42b9d6/0x42ba51 (`lea edi,[ebp+0x6b8c]` / `lea edi,[ebp+0x71f8]`,
     * ebp = piVar3) - here the LEA'd address IS the same cell passed as
     * EncodeChecksumDeltaDiv's own source arg just above (piVar3+0x1ae3 /
     * +0x1c7e), reused as self since nothing overwrites EDI in between.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)piVar3 + 0x6b8c, uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (iStack_440 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(auStack_4dc);
    }
    EncodeChecksumDeltaDiv(piVar3 + 0x1c7e,auStack_230,2);
    local_4 = 0x14;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField((int)piVar3 + 0x71f8, uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (iStack_21c != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(auStack_4dc);
    }
  }
  RegisterActiveObject(0, 0, (undefined4 *)0);
LAB_0042bab0:
  *unaff_FS_OFFSET = local_c;
  return;
}

