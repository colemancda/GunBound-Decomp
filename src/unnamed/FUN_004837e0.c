/* FUN_004837e0 - 0x004837e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004837e0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  byte *pbVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  char local_19;
  int local_18;
  int local_10;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004373c0(uVar3,uVar2,0x2073,s_ssflame8_00554dd0);
  local_18 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = FUN_00425ac0(g_clientContext,uVar4,uVar3,uVar2);
    if ((((iVar5 != 0) && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\0')) &&
        (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
       (cVar1 = PeekPacketChecksumBool(), (*(int *)(iVar5 + 0xae2c) == 1) != (bool)cVar1)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((-1 < iVar5) && (iVar5 < *(int *)(&DAT_006a7720 + g_clientContext))) {
        pcVar6 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
        local_10 = 0;
        if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
          do {
            if (*pcVar6 != '\0') goto LAB_0048398a;
            pcVar6 = pcVar6 + *(int *)(&DAT_006a7720 + g_clientContext);
            local_10 = local_10 + 1;
          } while (local_10 < *(int *)(&DAT_006a7724 + g_clientContext));
        }
      }
      local_10 = 10000;
LAB_0048398a:
      FUN_00436070(&DAT_006a7f70 + g_clientContext,iVar5,local_10);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_0043af40(iVar5,local_10,0,uVar4,uVar3,uVar2,*(undefined1 *)(param_1 + 0x3c));
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar9 = 1;
      uVar8 = 1;
      uVar4 = 0xff;
      uVar3 = 0;
      PeekPacketChecksumBool(0,uVar2,0xff,1,1);
      FUN_00431d90(*(undefined1 *)(param_1 + 0x3c),7,0,uVar3,uVar2,uVar4,uVar8,uVar9);
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 == '\0') {
        AcquireSoundChannel(0);
      }
    }
    local_18 = local_18 + 1;
  } while (local_18 < 8);
  local_18 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = FUN_00425c90(uVar4,uVar3,uVar2);
    if (iVar5 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((-1 < iVar5) && (iVar5 < *(int *)(&DAT_006a7720 + g_clientContext))) {
        pcVar6 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
        local_10 = 0;
        if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
          do {
            if (*pcVar6 != '\0') goto LAB_00483b89;
            pcVar6 = pcVar6 + *(int *)(&DAT_006a7720 + g_clientContext);
            local_10 = local_10 + 1;
          } while (local_10 < *(int *)(&DAT_006a7724 + g_clientContext));
        }
      }
      local_10 = 10000;
LAB_00483b89:
      FUN_00436070(&DAT_006a7f70 + g_clientContext,iVar5,local_10);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_0043af40(iVar5,local_10,0,uVar4,uVar3,uVar2,*(undefined1 *)(param_1 + 0x3c));
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((char)(*(char *)(param_1 + 0xf3c) + *(char *)(param_1 + 0xf3d) + -0x34) !=
          *(char *)(param_1 + 0xf3e)) {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_00431d90(*(undefined1 *)(param_1 + 0x3c),7,0,0,uVar2,0xff,1,1);
      iVar5 = g_clientContext;
      pbVar7 = &DAT_006a7f74 + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((byte)(*pbVar7 + (&DAT_006a7f75)[iVar5] + -0x34) == (&DAT_006a7f76)[iVar5]) {
        local_19 = '\x01' - (((byte)(&DAT_006a7f75)[iVar5] >> (*pbVar7 & 7) & 1) != 1);
      }
      else {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_19 = '\0';
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (local_19 == '\0') {
        AcquireSoundChannel(0);
      }
    }
    local_18 = local_18 + 1;
  } while (local_18 < 8);
  local_18 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = FUN_00425e60(uVar4,uVar3,uVar2);
    if (iVar5 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((-1 < iVar5) && (iVar5 < *(int *)(&DAT_006a7720 + g_clientContext))) {
        pcVar6 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
        local_10 = 0;
        if (0 < *(int *)(&DAT_006a7724 + g_clientContext)) {
          do {
            if (*pcVar6 != '\0') goto LAB_00483e2e;
            pcVar6 = pcVar6 + *(int *)(&DAT_006a7720 + g_clientContext);
            local_10 = local_10 + 1;
          } while (local_10 < *(int *)(&DAT_006a7724 + g_clientContext));
        }
      }
      local_10 = 10000;
LAB_00483e2e:
      FUN_00436070(&DAT_006a7f70 + g_clientContext,iVar5,local_10);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_0043af40(iVar5,local_10,0,uVar4,uVar3,uVar2,*(undefined1 *)(param_1 + 0x3c));
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((char)(*(char *)(param_1 + 0xf3c) + *(char *)(param_1 + 0xf3d) + -0x34) !=
          *(char *)(param_1 + 0xf3e)) {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_00431d90(*(undefined1 *)(param_1 + 0x3c),7,0,0,uVar2,0xff,1,1);
      iVar5 = g_clientContext;
      pbVar7 = &DAT_006a7f74 + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((byte)(*pbVar7 + (&DAT_006a7f75)[iVar5] + -0x34) == (&DAT_006a7f76)[iVar5]) {
        local_19 = '\x01' - (((byte)(&DAT_006a7f75)[iVar5] >> (*pbVar7 & 7) & 1) != 1);
      }
      else {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_19 = '\0';
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (local_19 == '\0') {
        AcquireSoundChannel(0);
      }
    }
    local_18 = local_18 + 1;
    if (0x3f < local_18) {
      return;
    }
  } while( true );
}

