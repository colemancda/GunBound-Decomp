/* FUN_00491b40 - 0x00491b40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00491b40(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  void *pvVar6;
  int *piVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_480 [2];
  int local_478;
  int local_474;
  undefined4 local_470;
  undefined4 local_46c;
  undefined4 local_468;
  undefined4 local_464;
  undefined4 local_460;
  undefined4 local_45c;
  undefined4 local_458;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ef67;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  if (*(char *)(param_1 + 0x14) != '\x01') {
    local_474 = param_1 + 0x1178;
    local_478 = param_1 + 0xf54;
    FUN_004262d0(*(undefined4 *)(param_1 + 8),local_474);
    *(undefined1 *)(param_1 + 0x14) = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaSub(param_1 + 0x264,local_454,uVar2);
    local_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_45c = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_468 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_460 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_470 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_464 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_458 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_46c = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_480[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_004e4970(local_480[0],local_46c,local_458,local_464,local_470,local_460,local_468,local_45c)
    ;
    local_4 = 0xffffffff;
    if (local_440 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_480);
    }
    FUN_004e4d00(&DAT_006a7708 + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaSub(param_1 + 0x264,local_454,uVar2);
    local_4 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    if (local_440 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_480);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaSub(param_1 + 0x264,local_454,uVar2);
    local_4 = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00450eb0(uVar3,uVar2,param_1,1,0,0);
    local_4 = 0xffffffff;
    if (local_440 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_480);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaSub(param_1 + 0x264,local_454,uVar2);
    local_4 = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436ac0(uVar3,uVar2);
    local_4 = 0xffffffff;
    if (local_440 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_480);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaSub(param_1 + 0x264,local_230,uVar2);
    local_4 = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_004372f0(*(uint *)(param_1 + 8) & 0xf,uVar3,uVar2,*(undefined4 *)(param_1 + 0x3894),
                 param_1 + 0x3898);
    local_4 = 0xffffffff;
    if (local_21c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(local_480);
    }
    iVar5 = g_clientContext;
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 != '\x01') {
      iVar4 = *(int *)(&DAT_006a7750 + iVar5);
      if (iVar4 < 0x10) {
        iVar4 = 0xf;
      }
      *(int *)(&DAT_006a7750 + iVar5) = iVar4;
      iVar4 = *(int *)(&DAT_006a7754 + iVar5);
      if (iVar4 < 0xb) {
        iVar4 = 10;
      }
      *(int *)(&DAT_006a7754 + iVar5) = iVar4;
    }
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\0') {
      AcquireSoundChannel(0);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\0') {
      pvVar6 = operator_new(0x54);
      if (pvVar6 == (void *)0x0) {
        piVar7 = (int *)0x0;
      }
      else {
        piVar7 = (int *)FUN_0047e940();
      }
      piVar7[0xf] = iVar5;
      piVar7[0xe] = iVar4;
      piVar7[0x11] = 0;
      *(undefined1 *)(piVar7 + 0x14) = 0;
      piVar7[6] = 0x2072;
      iVar5 = FindPreloadedTextureByName(s_ssflame7_00554e94);
      piVar7[7] = iVar5;
      (**(code **)(*piVar7 + 4))(s_flame_00553d2c);
      RegisterActiveObject();
    }
    iVar5 = g_clientContext;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar5) = 0;
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

