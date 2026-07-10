/* FUN_004644e0 - 0x004644e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 FUN_004644e0(int param_1)

{
  bool bVar1;
  char cVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  undefined1 local_d11;
  int local_d10;
  uint local_d08 [2];
  uint local_d00 [2];
  uint auStack_cf8 [2];
  uint local_cf0;
  int aiStack_cec [2];
  undefined1 local_ce4 [20];
  uint local_cd0;
  undefined1 local_ac0 [20];
  uint local_aac;
  undefined1 local_89c [20];
  uint local_888;
  undefined1 auStack_678 [20];
  uint uStack_664;
  undefined1 auStack_454 [20];
  uint uStack_440;
  undefined1 auStack_230 [20];
  uint uStack_21c;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053d45f) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  local_d11 = 0;
  local_cf0 = 0;
  do {
    piVar3 = (int *)GetPlayerRecordBySlot(g_clientContext);
    if ((piVar3 != (int *)0x0) && (cVar2 = PeekPacketChecksumBool(), cVar2 != '\x01')) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState();
      local_d08[0] = uVar4;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 != '\0') {
        uVar4 = (int)uVar4 / 2 + uVar4;
      }
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 != '\0') {
        uVar4 = uVar4 + ((int)(uVar4 + ((int)uVar4 >> 0x1f & 3U)) >> 2);
      }
      local_d08[0] = FUN_0040aca0(param_1 + 0x40,local_89c,piVar3 + 0x243);
      local_4 = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      local_d08[0] = local_888;
      if (local_888 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_d00);
      }
      local_d08[0] = FUN_0040aca0(param_1 + 0x264,local_ac0,piVar3 + 0x2cc);
      local_4 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      local_d08[0] = local_aac;
      if (local_aac != 0) {
        FUN_0040a240();
        FUN_0040b540(local_d00);
      }
      if (iVar6 * iVar6 + iVar5 * iVar5 < (int)(uVar4 * uVar4)) {
        FUN_0040aca0(param_1 + 0x40,local_ce4,piVar3 + 0x243);
        local_4 = 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar4 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if (local_cd0 != 0) {
          FUN_0040a240();
          FUN_0040b540(local_d00);
        }
        if (2 < (int)((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar4 = PeekPacketChecksumState();
          local_d08[0] = uVar4;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 < iVar5) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 != 0) goto LAB_004647f7;
LAB_00464824:
            uVar4 = -local_d08[0];
          }
          else {
LAB_004647f7:
            cVar2 = FUN_0040b490(param_1 + 0x40,piVar3 + 0x243);
            if ((cVar2 != '\0') && (cVar2 = PacketChecksumEquals(piVar3 + 0x715,1), cVar2 != '\0'))
            goto LAB_00464824;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)uVar4 <= iVar5) {
            local_d11 = 1;
            piVar3[0x2ff7] = piVar3[0x2ff7] + uVar4 * -3 + 200;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 < piVar3[0x2ff7]) {
              cVar2 = FUN_0040b410(param_1 + 0x40,piVar3 + 0x243);
              if (cVar2 == '\0') {
                iVar5 = FUN_0040a4d0(&DAT_00796aa0);
                SubFromPacketChecksum(piVar3[0x2ff7] / iVar5);
              }
              else {
                iVar5 = FUN_0040a4d0(&DAT_00796aa0);
                AddToPacketChecksum(piVar3[0x2ff7] / iVar5);
              }
              iVar5 = FUN_0040a4d0(&DAT_00796aa0);
              piVar3[0x2ff7] = piVar3[0x2ff7] % iVar5;
              EncodeChecksumState(piVar3 + 0x243);
              iVar5 = g_clientContext + 0x3b49c;
              *(undefined1 *)(piVar3 + 0x2c2b) = *(undefined1 *)(param_1 + 0x3c);
              iVar5 = FUN_0040a4d0(iVar5);
              if ((local_cf0 == iVar5) && (iVar5 = (**(int (**)())(*piVar3 + 0x14))(), 8999 < iVar5)) {
                FUN_00464060();
              }
            }
          }
        }
      }
    }
    local_cf0 = local_cf0 + 1;
    if (7 < (int)local_cf0) {
      FUN_0040ada0(param_1 + 0x33c8,local_ce4,param_1 + 0x33c8);
      local_4 = 3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_d00[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_cd0 != 0) {
        iVar5 = local_cd0 << 4;
        local_d10 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar5 + DAT_0079376c) = (char)iVar6;
          iVar5 = iVar5 + 1;
          local_d10 = local_d10 + -1;
        } while (local_d10 != 0);
        FUN_0040b540(auStack_cf8);
      }
      local_cf0 = 0;
      do {
        iVar5 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
        uVar4 = *(uint *)(iVar5 + 4);
        while (uVar4 < 0x186a4) {
          if (uVar4 == 0x186a3) {
            iVar5 = *(int *)(iVar5 + 0x10);
            uVar4 = *(uint *)(iVar5 + 8);
            if (uVar4 <= local_cf0) goto LAB_00464a63;
            break;
          }
          iVar5 = *(int *)(iVar5 + 0x1c);
          uVar4 = *(uint *)(iVar5 + 4);
        }
LAB_00464ec3:
        local_cf0 = local_cf0 + 1;
      } while ((int)local_cf0 < 0x40);
      FUN_0040ada0(param_1 + 0x33c8,auStack_678,param_1 + 0x33c8);
      local_4 = 7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      local_d00[0] = uStack_664;
      if (uStack_664 != 0) {
        iVar6 = uStack_664 << 4;
        iVar10 = 0x10;
        do {
          iVar7 = _rand();
          *(char *)(iVar6 + DAT_0079376c) = (char)iVar7;
          iVar6 = iVar6 + 1;
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
        FUN_0040b540(auStack_cf8);
      }
      local_cf0 = 0;
      do {
        iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
        uVar4 = *(uint *)(iVar6 + 4);
        while (uVar4 < 0x186a7) {
          if (uVar4 == 0x186a6) {
            iVar6 = *(int *)(iVar6 + 0x10);
            uVar4 = *(uint *)(iVar6 + 8);
            if (uVar4 <= local_cf0) goto LAB_00464fc1;
            break;
          }
          iVar6 = *(int *)(iVar6 + 0x1c);
          uVar4 = *(uint *)(iVar6 + 4);
        }
LAB_00465442:
        local_cf0 = local_cf0 + 1;
        if (7 < (int)local_cf0) {
          return local_d11;
        }
      } while( true );
    }
  } while( true );
LAB_00464a63:
  if (uVar4 != local_cf0) goto code_r0x00464a65;
  FUN_0040aca0(param_1 + 0x40,local_ac0,iVar5 + 0x40);
  local_4 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  aiStack_cec[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_aac != 0) {
    iVar6 = local_aac << 4;
    local_d08[0] = 0x10;
    do {
      iVar10 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar10;
      iVar6 = iVar6 + 1;
      local_d08[0] = local_d08[0] - 1;
    } while (local_d08[0] != 0);
    FUN_0040b540(auStack_cf8);
  }
  FUN_0040aca0(param_1 + 0x264,local_89c,iVar5 + 0x264);
  local_4 = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  auStack_cf8[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_888 != 0) {
    iVar6 = local_888 << 4;
    local_d08[0] = 0x10;
    do {
      iVar10 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar10;
      iVar6 = iVar6 + 1;
      local_d08[0] = local_d08[0] - 1;
    } while (local_d08[0] != 0);
    FUN_0040b540(local_d08);
  }
  if ((int)(aiStack_cec[0] * aiStack_cec[0] + auStack_cf8[0] * auStack_cf8[0]) < (int)local_d00[0])
  {
    auStack_cf8[0] = FUN_0040aca0(param_1 + 0x40,auStack_678,iVar5 + 0x40);
    local_4 = 6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    auStack_cf8[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar9 = (int)auStack_cf8[0] >> 0x1f;
    uVar4 = auStack_cf8[0] ^ uVar9;
    local_4 = 0xffffffff;
    auStack_cf8[0] = uStack_664;
    if (uStack_664 != 0) {
      iVar6 = uStack_664 << 4;
      local_d08[0] = 0x10;
      do {
        iVar10 = _rand();
        *(char *)(iVar6 + DAT_0079376c) = (char)iVar10;
        iVar6 = iVar6 + 1;
        local_d08[0] = local_d08[0] - 1;
      } while (local_d08[0] != 0);
      FUN_0040b540(aiStack_cec);
    }
    if (2 < (int)(uVar4 - uVar9)) {
      local_d10 = *(int *)(iVar5 + 0x3fbc);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      auStack_cf8[0] = PeekPacketChecksumState();
      iVar6 = PeekPacketChecksumState();
      bVar1 = iVar6 < (int)auStack_cf8[0];
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((bVar1) && (*(int *)(iVar5 + 0x3fa8) != 0)) {
LAB_00464d65:
        local_d10 = -local_d10;
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        auStack_cf8[0] = PeekPacketChecksumState();
        iVar6 = PeekPacketChecksumState();
        bVar1 = (int)auStack_cf8[0] < iVar6;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((bVar1) && (*(int *)(iVar5 + 0x3fa8) == 0)) goto LAB_00464d65;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      auStack_cf8[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (local_d10 <= (int)auStack_cf8[0]) {
        local_d11 = 1;
        *(int *)(iVar5 + 0x3fd0) = *(int *)(iVar5 + 0x3fd0) + (100 - local_d10) * 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        auStack_cf8[0] = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((int)auStack_cf8[0] < *(int *)(iVar5 + 0x3fd0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          iVar10 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar4 = PeekPacketChecksumState();
          if (iVar10 < iVar6) {
            auStack_cf8[0] = uVar4;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            auStack_cf8[0] = *(int *)(iVar5 + 0x3fd0) / (int)auStack_cf8[0];
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar6 + auStack_cf8[0]);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          else {
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = *(int *)(iVar5 + 0x3fd0);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar10 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar10 - iVar6 / (int)uVar4);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          *(int *)(iVar5 + 0x3fd0) = *(int *)(iVar5 + 0x3fd0) % iVar6;
        }
      }
    }
  }
  goto LAB_00464ec3;
code_r0x00464a65:
  iVar5 = *(int *)(iVar5 + 0x10);
  uVar4 = *(uint *)(iVar5 + 8);
  if (local_cf0 < uVar4) goto LAB_00464ec3;
  goto LAB_00464a63;
LAB_00464fc1:
  if (uVar4 != local_cf0) goto code_r0x00464fc3;
  FUN_0040aca0(param_1 + 0x40,local_ce4,iVar6 + 0x25c);
  local_4 = 8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  aiStack_cec[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_d00[0] = local_cd0;
  if (local_cd0 != 0) {
    iVar10 = local_cd0 << 4;
    local_d08[0] = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar10 + DAT_0079376c) = (char)iVar7;
      iVar10 = iVar10 + 1;
      local_d08[0] = local_d08[0] - 1;
    } while (local_d08[0] != 0);
    FUN_0040b540(auStack_cf8);
  }
  FUN_0040aca0(param_1 + 0x264,local_ac0,iVar6 + 0x480);
  local_4 = 9;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  auStack_cf8[0] = uVar4;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_d00[0] = local_aac;
  if (local_aac != 0) {
    iVar10 = local_aac << 4;
    local_d08[0] = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar10 + DAT_0079376c) = (char)iVar7;
      iVar10 = iVar10 + 1;
      local_d08[0] = local_d08[0] - 1;
    } while (local_d08[0] != 0);
    FUN_0040b540(local_d08);
    uVar4 = auStack_cf8[0];
  }
  if ((int)(aiStack_cec[0] * aiStack_cec[0] + uVar4 * uVar4) < iVar5) {
    FUN_0040aca0(param_1 + 0x40,local_89c,iVar6 + 0x25c);
    local_4 = 10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    local_d00[0] = local_888;
    if (local_888 != 0) {
      iVar10 = local_888 << 4;
      local_d08[0] = 0x10;
      do {
        iVar7 = _rand();
        *(char *)(iVar10 + DAT_0079376c) = (char)iVar7;
        iVar10 = iVar10 + 1;
        local_d08[0] = local_d08[0] - 1;
      } while (local_d08[0] != 0);
      FUN_0040b540(auStack_cf8);
    }
    if (2 < (int)((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f))) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar10 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_d00[0] = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar10 <= (int)local_d00[0]) {
        local_d11 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        EncodeOutgoingPacketField(iVar7 + (100 - iVar10) * 2);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar10 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar10 < iVar7) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar10 = PeekPacketChecksumState();
          iVar7 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = PeekPacketChecksumState();
          if (iVar7 < iVar10) {
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            FUN_0040a8c0(iVar6 + 0x15ac,auStack_454,uVar8);
            local_4 = 0xb;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_d00[0] = PeekPacketChecksumState();
            iVar6 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar6 + local_d00[0]);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar4 = uStack_440;
          }
          else {
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_d00[0] = FUN_0040a8c0(iVar6 + 0x15ac,auStack_230,uVar8);
            local_4 = 0xc;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            iVar10 = PeekPacketChecksumState();
            EncodeOutgoingPacketField(iVar6 - iVar10);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar4 = uStack_21c;
          }
          local_4 = 0xffffffff;
          if (uVar4 != 0) {
            FUN_0040a240();
            local_d00[0] = uVar4;
            FUN_0040b540(auStack_cf8);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar10 = PeekPacketChecksumState();
          EncodeOutgoingPacketField(iVar10 % iVar6);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
      }
    }
  }
  goto LAB_00465442;
code_r0x00464fc3:
  iVar6 = *(int *)(iVar6 + 0x10);
  uVar4 = *(uint *)(iVar6 + 8);
  if (local_cf0 < uVar4) goto LAB_00465442;
  goto LAB_00464fc1;
}

