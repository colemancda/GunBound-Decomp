/* FUN_00463630 - 0x00463630 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 4 argless PeekPacketChecksumState() calls (4 C : 4 orig,
 * goto-free zip).  Two cells are the chained returns of the round's
 * final helper - the x round's DeltaSub(...,0x29) and the y round's
 * DeltaAdd(...,0x26) - both discarded, captured in a new uVar8.  The
 * others are the battle-mode cell at g_clientContext+0x45354 and
 * &DAT_00796aa0.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_00463630(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar8;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  /* RECOVERED (dropped-EAX pass): `iVar7` holds the fill box's top edge
   * (Ghidra's `iVar2` + 1, kept in EBX from orig 0x463991) because
   * `iVar2` is recycled by `iVar2 = param_1 + 0x6db0` before the second
   * and third fills.  `uVar9` holds the width of the FIRST bar fill
   * (orig 0x463b48), which the original keeps in its [esp+0x10] spill
   * slot (E-0x1144) and reads back at 0x463bee to place the SECOND bar
   * (`lea edx,[edx+eax+2]`), while Ghidra's `uVar3` name is reassigned
   * in between. */
  int iVar7;
  undefined4 uVar9;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_1144;
  int local_113c [2];
  int local_1134;
  int local_1130;
  undefined1 local_112c [548];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539ffe;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x46364f;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 != 3) {
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\0') {
      uVar3 = EncodeChecksumDeltaSub(param_1 + 0x90c,local_112c,*(undefined4 *)(&g_nCameraX + g_clientContext))
      ;
      local_4 = 0;
      uVar3 = EncodeChecksumDeltaAdd(uVar3,local_f08,400);
      local_4 = 1;
      uVar8 = EncodeChecksumDeltaSub(uVar3,local_ce4,0x29);
      local_4 = 2;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_1134 = PeekPacketChecksumState((void *)uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 1;
      if ((*(int *)(local_ce4 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_ce4 + 0x14),&g_valueGuardKeyTable);
        TreeLowerBound(local_113c,&g_valueGuardMap);
      }
      local_4 = 0;
      if ((*(int *)(local_f08 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_f08 + 0x14),&g_valueGuardKeyTable);
        TreeLowerBound(local_113c,&g_valueGuardMap);
      }
      local_4 = 0xffffffff;
      if ((*(int *)(local_112c + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_112c + 0x14),&g_valueGuardKeyTable);
        TreeLowerBound(local_113c,&g_valueGuardMap);
      }
      uVar3 = EncodeChecksumDeltaSub(param_1 + 0xb30,local_ce4,*(undefined4 *)(&g_nCameraY + g_clientContext));
      local_4 = 3;
      uVar3 = EncodeChecksumDeltaAdd(uVar3,local_f08,0x10e);
      local_4 = 4;
      uVar8 = EncodeChecksumDeltaAdd(uVar3,local_112c,0x26);
      local_4 = 5;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar2 = PeekPacketChecksumState((void *)uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 4;
      if ((*(int *)(local_112c + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_112c + 0x14),&g_valueGuardKeyTable);
        TreeLowerBound(local_113c,&g_valueGuardMap);
      }
      local_4 = 3;
      if ((*(int *)(local_f08 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_f08 + 0x14),&g_valueGuardKeyTable);
        TreeLowerBound(local_113c,&g_valueGuardMap);
      }
      local_4 = 0xffffffff;
      if ((*(int *)(local_ce4 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_ce4 + 0x14),&g_valueGuardKeyTable);
        TreeLowerBound(local_113c,&g_valueGuardMap);
      }
      if (500 < iVar2) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar4 = PeekPacketChecksumState((void *)&DAT_00796aa0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar2 = iVar2 - iVar4;
      }
      iVar4 = local_1134;
      if ((((g_clipMinX <= local_1134 + 0x53) && (local_1134 <= g_clipMaxX)) &&
          (g_clipMinY <= iVar2 + 0x1f)) && (iVar2 <= g_clipMaxY)) {
        if (*(char *)(g_clientContext + 0x45122) == '\0') {
          PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        }
        if (*(int *)(param_1 + 0x24) != 0xe) {
          FUN_004eb7a0(iVar4 + 1,0x4e,5);
          local_113c[0] = iVar4 + 2;
          iVar7 = iVar2 + 1;
          FillScreenRect(iVar7,local_113c[0],0x4c,0x2965,3);
          iVar2 = param_1 + 0x6db0;
          iVar4 = param_1 + 0x6744;
          uVar3 = EncodeChecksumPairSum(iVar4,local_ac0,iVar2);
          local_4 = 6;
          iVar5 = PeekChecksumStateUnderLock(uVar3);
          if (0 < iVar5) {
            uVar3 = EncodeChecksumPairSum(iVar4,local_ce4,iVar2);
            local_4 = 7;
            local_1144 = PeekChecksumStateUnderLock(uVar3);
          }
          else {
            local_1144 = 1;
          }
          uVar3 = EncodeChecksumDeltaMul(param_1 + 0x6968,local_f08,0x4c);
          local_4 = 8;
          uVar3 = EncodeChecksumDeltaDiv(uVar3,local_112c,local_1144);
          local_4 = 9;
          uVar3 = PeekChecksumStateUnderLock(uVar3);
          local_4 = 8;
          ScrubChecksumGuard();
          local_4 = 7;
          ScrubChecksumGuard();
          local_4 = 6;
          if (0 < iVar5) {
            ScrubChecksumGuard();
          }
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          uVar6 = EncodeChecksumPairSum(iVar4,local_112c,iVar2);
          local_4 = 10;
          uVar6 = EncodeChecksumDeltaDiv(uVar6,local_ac0,3);
          local_4 = 0xb;
          cVar1 = CompareChecksumPair(param_1 + 0x6968,uVar6);
          local_4 = 10;
          local_1130 = (-(uint)(cVar1 != '\0') & 0x5af7) + 0x65a9;
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          uVar9 = uVar3;
          FillScreenRect(iVar7,local_113c[0],uVar3,local_1130,3);
          uVar3 = EncodeChecksumPairSum(iVar4,local_230,iVar2);
          local_4 = 0xc;
          iVar5 = PeekChecksumStateUnderLock(uVar3);
          if (0 < iVar5) {
            uVar3 = EncodeChecksumPairSum(iVar4,local_678,iVar2);
            local_4 = 0xd;
            uVar3 = PeekChecksumStateUnderLock(uVar3);
          }
          else {
            uVar3 = 1;
          }
          uVar6 = EncodeChecksumDeltaMul(param_1 + 0x6fd4,local_454,0x4c);
          local_4 = 0xe;
          uVar3 = EncodeChecksumDeltaDiv(uVar6,local_89c,uVar3);
          uVar6 = 0x21d8;
          local_4 = 0xf;
          uVar3 = PeekChecksumStateUnderLock(uVar3);
          FillScreenRect(iVar7,local_1134 + (int)uVar9 + 2,uVar3,uVar6,3);
          local_4 = 0xe;
          ScrubChecksumGuard();
          local_4 = 0xd;
          ScrubChecksumGuard();
          local_4 = 0xc;
          if (0 < iVar5) {
            ScrubChecksumGuard();
          }
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
        }
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

