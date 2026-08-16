/* FUN_004644e0 - 0x004644e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 50 argless sites (44 peeks + 6 encodes).  This function was
 * deferred twice before because Ghidra hoisted whole blocks out of address
 * order; the mapping was finally pinned by bracketing every call site
 * between the pair of LAB_004xxxxx / code_r0x004xxxxx labels this port
 * still carries, then sorting those label blocks by ADDRESS rather than by
 * C line.  Doing that lines the 50 C sites up against the 50 guard calls
 * with the Peek/Encode type sequence matching exactly in every block --
 * including the three badly displaced ones:
 *   LAB_004647f7's body (C115..C185) sits at 0x464836..0x464987,
 *   LAB_00464a63 + code_r0x00464a65 + LAB_00464d65 (C229..C347) form one
 *     contiguous 17-call run at 0x464ab8..0x464ea6, and
 *   LAB_00464fc1 + code_r0x00464fc3 (C353..C477) form one contiguous
 *     21-call run at 0x465008..0x465432.
 *
 * The frame was calibrated off `mov byte [esp+0x1b],al` = local_d11 at
 * 0x46450d, i.e. Ghidra local N sits at esp + (0xd2c - N); that is
 * confirmed four more times over by [esp+0x24] = local_d08,
 * [esp+0x2c] = local_d00, [esp+0x34] = auStack_cf8 and
 * [esp+0x3c] = local_cf0, and it makes [esp+0xd30] the incoming param_1.
 *
 * Most peeks read EAX straight out of the pair/delta helper on the line
 * above (those helpers RETURN THEIR SECOND ARGUMENT), so they are that
 * call's own scratch guard: local_ce4, local_ac0, local_89c, auStack_678,
 * auStack_454, auStack_230.  The piVar3-relative offsets cross-check
 * against the C's own expressions -- 0x90c/4 = 0x243 and 0x1c54/4 = 0x715
 * are exactly the `piVar3 + 0x243` and `piVar3 + 0x715` the surrounding
 * lines already spell out.
 *
 * Two capture locals had to be added because the original reloads a value
 * the C then overwrites before the peek is reached:
 *   - iOldD10: EBX is loaded from local_d10's slot at 0x464cc9, BEFORE
 *     0x464ce8 stores *(iVar5 + 0x3fbc) into it, and the three peeks at
 *     0x464cf0 / 0x464d2f / 0x464df6 all read that stale EBX.
 *   - iObj6: EDI/[esp+0x20] holds the object the C calls iVar6 (stored at
 *     0x465270), but the C reassigns iVar6 from a peek result at C444 and
 *     C454 while the encodes at 0x46535d and 0x4653bd still address the
 *     object.
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
  int iOldD10;
  int iObj6;
  undefined1 local_d11;
  int local_d10;
  uint local_d08 [2];
  uint local_d00 [2];
  uint auStack_cf8 [2];
  uint local_cf0;
  int aiStack_cec [2];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
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
      uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x33c8));
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
      local_d08[0] = EncodeChecksumPairDiff(param_1 + 0x40,local_89c,piVar3 + 0x243);
      local_4 = 0;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(local_d08[0]));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      local_d08[0] = (*(int *)(local_89c + 0x14));
      if ((*(int *)(local_89c + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_d00);
      }
      local_d08[0] = EncodeChecksumPairDiff(param_1 + 0x264,local_ac0,piVar3 + 0x2cc);
      local_4 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState((void *)(local_d08[0]));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      local_d08[0] = (*(int *)(local_ac0 + 0x14));
      if ((*(int *)(local_ac0 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes();
        TreeLowerBound(local_d00);
      }
      if (iVar6 * iVar6 + iVar5 * iVar5 < (int)(uVar4 * uVar4)) {
        EncodeChecksumPairDiff(param_1 + 0x40,local_ce4,piVar3 + 0x243);
        local_4 = 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar4 = PeekPacketChecksumState((void *)(local_ce4));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if ((*(int *)(local_ce4 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_d00);
        }
        if (2 < (int)((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f))) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar4 = PeekPacketChecksumState((void *)(piVar3 + 0x12db));
          local_d08[0] = uVar4;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x40));
          iVar6 = PeekPacketChecksumState((void *)(piVar3 + 0x243));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 < iVar5) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState((void *)(piVar3 + 0x715));
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 != 0) goto LAB_004647f7;
LAB_00464824:
            uVar4 = -local_d08[0];
          }
          else {
LAB_004647f7:
            cVar2 = CompareChecksumPair(param_1 + 0x40,piVar3 + 0x243);
            if ((cVar2 != '\0') && (cVar2 = PacketChecksumEquals(piVar3 + 0x715,1), cVar2 != '\0'))
            goto LAB_00464824;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState((void *)(&DAT_00794e48));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if ((int)uVar4 <= iVar5) {
            local_d11 = 1;
            piVar3[0x2ff7] = piVar3[0x2ff7] + uVar4 * -3 + 200;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 < piVar3[0x2ff7]) {
              cVar2 = CompareChecksumExceeds(param_1 + 0x40,piVar3 + 0x243);
              if (cVar2 == '\0') {
                iVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                SubFromPacketChecksum(piVar3 + 0x243, piVar3[0x2ff7] / iVar5);
              }
              else {
                iVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
                AddToPacketChecksum(piVar3 + 0x243, piVar3[0x2ff7] / iVar5);
              }
              iVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
              piVar3[0x2ff7] = piVar3[0x2ff7] % iVar5;
              EncodeChecksumState(piVar3 + 0x243);
              iVar5 = g_clientContext + 0x3b49c;
              *(undefined1 *)(piVar3 + 0x2c2b) = *(undefined1 *)(param_1 + 0x3c);
              iVar5 = PeekChecksumStateUnderLock(iVar5);
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
      InitGuardedChecksumSlot(param_1 + 0x33c8,local_ce4,param_1 + 0x33c8);
      local_4 = 3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_d00[0] = PeekPacketChecksumState((void *)(local_ce4));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if ((*(int *)(local_ce4 + 0x14)) != 0) {
        iVar5 = (*(int *)(local_ce4 + 0x14)) << 4;
        local_d10 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar5 + DAT_0079376c) = (char)iVar6;
          iVar5 = iVar5 + 1;
          local_d10 = local_d10 + -1;
        } while (local_d10 != 0);
        TreeLowerBound(auStack_cf8);
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
      InitGuardedChecksumSlot(param_1 + 0x33c8,auStack_678,param_1 + 0x33c8);
      local_4 = 7;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(auStack_678));
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
        TreeLowerBound(auStack_cf8);
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
  EncodeChecksumPairDiff(param_1 + 0x40,local_ac0,iVar5 + 0x40);
  local_4 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  aiStack_cec[0] = PeekPacketChecksumState((void *)(local_ac0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_ac0 + 0x14)) != 0) {
    iVar6 = (*(int *)(local_ac0 + 0x14)) << 4;
    local_d08[0] = 0x10;
    do {
      iVar10 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar10;
      iVar6 = iVar6 + 1;
      local_d08[0] = local_d08[0] - 1;
    } while (local_d08[0] != 0);
    TreeLowerBound(auStack_cf8);
  }
  EncodeChecksumPairDiff(param_1 + 0x264,local_89c,iVar5 + 0x264);
  local_4 = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  auStack_cf8[0] = PeekPacketChecksumState((void *)(local_89c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    iVar6 = (*(int *)(local_89c + 0x14)) << 4;
    local_d08[0] = 0x10;
    do {
      iVar10 = _rand();
      *(char *)(iVar6 + DAT_0079376c) = (char)iVar10;
      iVar6 = iVar6 + 1;
      local_d08[0] = local_d08[0] - 1;
    } while (local_d08[0] != 0);
    TreeLowerBound(local_d08);
  }
  if ((int)(aiStack_cec[0] * aiStack_cec[0] + auStack_cf8[0] * auStack_cf8[0]) < (int)local_d00[0])
  {
    auStack_cf8[0] = EncodeChecksumPairDiff(param_1 + 0x40,auStack_678,iVar5 + 0x40);
    local_4 = 6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    auStack_cf8[0] = PeekPacketChecksumState((void *)(auStack_cf8[0]));
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
      TreeLowerBound(aiStack_cec);
    }
    if (2 < (int)(uVar4 - uVar9)) {
      iOldD10 = local_d10;
      local_d10 = *(int *)(iVar5 + 0x3fbc);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      auStack_cf8[0] = PeekPacketChecksumState((void *)(iOldD10));
      iVar6 = PeekPacketChecksumState((void *)(iVar5 + 0x40));
      bVar1 = iVar6 < (int)auStack_cf8[0];
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((bVar1) && (*(int *)(iVar5 + 0x3fa8) != 0)) {
LAB_00464d65:
        local_d10 = -local_d10;
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        auStack_cf8[0] = PeekPacketChecksumState((void *)(iOldD10));
        iVar6 = PeekPacketChecksumState((void *)(iVar5 + 0x40));
        bVar1 = (int)auStack_cf8[0] < iVar6;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((bVar1) && (*(int *)(iVar5 + 0x3fa8) == 0)) goto LAB_00464d65;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      auStack_cf8[0] = PeekPacketChecksumState((void *)(&DAT_00794e48));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (local_d10 <= (int)auStack_cf8[0]) {
        local_d11 = 1;
        *(int *)(iVar5 + 0x3fd0) = *(int *)(iVar5 + 0x3fd0) + (100 - local_d10) * 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        auStack_cf8[0] = PeekPacketChecksumState((void *)(&DAT_00796aa0));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((int)auStack_cf8[0] < *(int *)(iVar5 + 0x3fd0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState((void *)(iOldD10));
          iVar10 = PeekPacketChecksumState((void *)(iVar5 + 0x40));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar4 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
          if (iVar10 < iVar6) {
            auStack_cf8[0] = uVar4;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            auStack_cf8[0] = *(int *)(iVar5 + 0x3fd0) / (int)auStack_cf8[0];
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState((void *)(iVar5 + 0x40));
            EncodeOutgoingPacketField((void *)(iVar5 + 0x40), iVar6 + auStack_cf8[0]);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          else {
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = *(int *)(iVar5 + 0x3fd0);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar10 = PeekPacketChecksumState((void *)(iVar5 + 0x40));
            EncodeOutgoingPacketField((void *)(iVar5 + 0x40), iVar10 - iVar6 / (int)uVar4);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
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
  EncodeChecksumPairDiff(param_1 + 0x40,local_ce4,iVar6 + 0x25c);
  local_4 = 8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  aiStack_cec[0] = PeekPacketChecksumState((void *)(local_ce4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_d00[0] = (*(int *)(local_ce4 + 0x14));
  if ((*(int *)(local_ce4 + 0x14)) != 0) {
    iVar10 = (*(int *)(local_ce4 + 0x14)) << 4;
    local_d08[0] = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar10 + DAT_0079376c) = (char)iVar7;
      iVar10 = iVar10 + 1;
      local_d08[0] = local_d08[0] - 1;
    } while (local_d08[0] != 0);
    TreeLowerBound(auStack_cf8);
  }
  EncodeChecksumPairDiff(param_1 + 0x264,local_ac0,iVar6 + 0x480);
  local_4 = 9;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(local_ac0));
  auStack_cf8[0] = uVar4;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  local_d00[0] = (*(int *)(local_ac0 + 0x14));
  if ((*(int *)(local_ac0 + 0x14)) != 0) {
    iVar10 = (*(int *)(local_ac0 + 0x14)) << 4;
    local_d08[0] = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar10 + DAT_0079376c) = (char)iVar7;
      iVar10 = iVar10 + 1;
      local_d08[0] = local_d08[0] - 1;
    } while (local_d08[0] != 0);
    TreeLowerBound(local_d08);
    uVar4 = auStack_cf8[0];
  }
  if ((int)(aiStack_cec[0] * aiStack_cec[0] + uVar4 * uVar4) < iVar5) {
    EncodeChecksumPairDiff(param_1 + 0x40,local_89c,iVar6 + 0x25c);
    local_4 = 10;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(local_89c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 0xffffffff;
    local_d00[0] = (*(int *)(local_89c + 0x14));
    if ((*(int *)(local_89c + 0x14)) != 0) {
      iVar10 = (*(int *)(local_89c + 0x14)) << 4;
      local_d08[0] = 0x10;
      do {
        iVar7 = _rand();
        *(char *)(iVar10 + DAT_0079376c) = (char)iVar7;
        iVar10 = iVar10 + 1;
        local_d08[0] = local_d08[0] - 1;
      } while (local_d08[0] != 0);
      TreeLowerBound(auStack_cf8);
    }
    if (2 < (int)((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f))) {
      iObj6 = iVar6;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar10 = PeekPacketChecksumState((void *)(iVar6 + 0xaf0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_d00[0] = PeekPacketChecksumState((void *)(&DAT_00794e48));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar10 <= (int)local_d00[0]) {
        local_d11 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState((void *)(iVar6 + 0x15ac));
        EncodeOutgoingPacketField((void *)(iVar6 + 0x15ac), iVar7 + (100 - iVar10) * 2);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar10 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState((void *)(iVar6 + 0x15ac));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar10 < iVar7) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar10 = PeekPacketChecksumState((void *)(param_1 + 0x40));
          iVar7 = PeekPacketChecksumState((void *)(iVar6));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
          if (iVar7 < iVar10) {
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeChecksumDeltaDiv(iVar6 + 0x15ac,auStack_454,uVar8);
            local_4 = 0xb;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_d00[0] = PeekPacketChecksumState((void *)(iVar6));
            iVar6 = PeekPacketChecksumState((void *)(auStack_454));
            EncodeOutgoingPacketField((void *)(iObj6), iVar6 + local_d00[0]);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar4 = uStack_440;
          }
          else {
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_d00[0] = EncodeChecksumDeltaDiv(iVar6 + 0x15ac,auStack_230,uVar8);
            local_4 = 0xc;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState((void *)(iVar6));
            iVar10 = PeekPacketChecksumState((void *)(auStack_230));
            EncodeOutgoingPacketField((void *)(iObj6), iVar6 - iVar10);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            uVar4 = uStack_21c;
          }
          local_4 = 0xffffffff;
          if (uVar4 != 0) {
            ScrambleChecksumGuardBytes();
            local_d00[0] = uVar4;
            TreeLowerBound(auStack_cf8);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar10 = PeekPacketChecksumState((void *)(local_d10));
          EncodeOutgoingPacketField((void *)(local_d10), iVar10 % iVar6);
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

