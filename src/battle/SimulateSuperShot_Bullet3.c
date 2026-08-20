/* SimulateSuperShot_Bullet3 - 0x0048b7f0 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_0048b7f0): CProjectile virtual slot 5
 * (SimulateProjectileFrame, base impl 0x455cc0) override for mobile type
 * 2's super shot (texture bullet3p; vtable 0x556284, ctor FUN_0048b3f0
 * reached only through SpawnSuperShot's case 2). Type/role CONFIRMED via
 * vtable geometry (tools/projectile_class_map.py); the mobile NAME is not
 * confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-GUARD-CELL FIX (2026-08-11): all 38 argless
 * PeekPacketChecksumState() calls and all 30 one-arg
 * EncodeOutgoingPacketField() calls had lost their CValueGuard cell
 * pointer (EAX resp. EDI at the original call sites). Recovered every
 * cell from tools/guard_worklist.json plus capstone disasm of
 * 0x48b7f0-0x48d102, matched by landmark (goto-shuffled: the
 * LAB_0048bc2e/LAB_0048c664 blocks and the duplicated encode tails
 * LAB_0048c475/LAB_0048c494 + their 0x48ce23/0x48cf09/0x48cfef
 * copies are out of address order in the decompile; alignment locked
 * via the delta-buffer landmarks local_89c/local_454/local_ce4/
 * local_112c/local_230/local_678/local_ac0/local_f08 and the
 * per-path encode values, spot-verified at 0x48b81b-0x48b850/
 * 0x48bcc6/0x48c098-0x48c0f3/0x48c2fa-0x48c30e/0x48c6fb-0x48c700/
 * 0x48cd4a-0x48cdb2). Twelve peeks (after each EncodeChecksumDeltaShr/
 * EncodeChecksumDeltaAdd) take that helper's just-returned cell
 * pointer, which the decompile discarded - now captured in
 * iVar3/iVar5/uVar2. The remaining cells are conn-object fields:
 * local_15b4 (param_1/this) + 0x24c0/0x1178/0xf54/0x6ac/0x488 for
 * the peeks, + 0x40/0x264/0xf54/0x1178 for the encode tails
 * (original keeps this in [esp+0x28], reloaded into ebx/edi per
 * block), and local_15a8 (= param_1+0x15c0) for the two uVar2
 * encodes at 0x48bcc8/0x48c700 (asm slot [esp+0x34]; the worklist's
 * "[esp+0x38]" for 0x48c700 is pre-push - the value push shifts esp
 * by 4 before the load at 0x48c6fc). PeekPacketChecksumBool/
 * DecodeGuardedBool sites are out of this sweep's scope and stay
 * argless.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __thiscall SimulateSuperShot_Bullet3(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  undefined4 *unaff_FS_OFFSET;
  int local_15c4;
  uint local_15c0;
  int local_15bc;
  int local_15b8;
  int local_15b4;
  char local_15ad;
  uint local_15ac;
  int local_15a8;
  int local_15a4;
  int local_15a0;
  int local_159c;
  uint local_1598 [2];
  int local_1590;
  int local_158c;
  int local_1588;
  int local_1584;
  int local_1580 [2];
  int local_1578;
  undefined1 local_1574 [548];
  undefined1 local_1350 [548];
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
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053f194;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x48b80f;
  local_1578 = param_1 + 0x40;
  local_15c0 = 0;
  local_15ad = '\0';
  local_15b4 = param_1;
  iVar3 = EncodeChecksumDeltaShr(local_1578,local_1574,8);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_159c = PeekPacketChecksumState((void *)iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  local_1584 = param_1 + 0x264;
  iVar3 = EncodeChecksumDeltaShr(local_1584,local_1574,8);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_15a4 = PeekPacketChecksumState((void *)iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  uVar2 = EncodeChecksumPairDiff(local_1578,local_1350,param_1 + 0x488);
  local_4 = 2;
  uVar2 = EncodeChecksumDeltaShr(uVar2,local_1574,8);
  SUBFIELD(local_4,0,undefined1) = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1590 = PeekPacketChecksumState((void *)uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_1350 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  uVar2 = EncodeChecksumPairDiff(local_1584,local_1574,local_15b4 + 0x6ac);
  local_4 = 4;
  uVar2 = EncodeChecksumDeltaShr(uVar2,local_1350,8);
  SUBFIELD(local_4,0,undefined1) = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),4);
  if ((*(int *)(local_1350 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_1574 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_1598);
  }
  uVar8 = local_1590 - local_159c >> 0x1f;
  iVar5 = (local_1590 - local_159c ^ uVar8) - uVar8;
  uVar8 = iVar3 - local_15a4 >> 0x1f;
  iVar9 = (iVar3 - local_15a4 ^ uVar8) - uVar8;
  local_1578 = iVar5 + 1;
  iVar10 = iVar9 + 1;
  if (iVar10 < local_1578) {
    local_1578 = ((local_15a4 - iVar3) * 0x10000) / local_1578;
    local_1588 = iVar3 << 0x10;
    if (local_159c < local_1590) {
      local_15b8 = local_1590 + -1;
      local_1590 = -1;
    }
    else {
      local_15b8 = local_1590 + 1;
      local_1590 = 1;
    }
    local_15ac = iVar5 + param_2;
    local_15a4 = 0;
    if (0 < (int)local_15ac) {
      local_1584 = local_1578 * param_2;
      local_15a8 = local_15b4 + 0x15c0;
      local_1580[0] = local_1590 * param_2;
      local_159c = local_15b8;
      do {
        local_1588 = local_1588 + local_1584;
        local_15bc = local_1588 >> 0x10;
        local_15c4 = local_15b8;
        if ((local_15ad == '\0') &&
           (iVar5 = FUN_004510f0(local_15b8), iVar3 = local_15a8, iVar5 != 0)) {
          iVar5 = EncodeChecksumDeltaAdd(local_15a8,local_89c,param_2);
          local_4 = 6;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState((void *)iVar5);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar5 < 0x14) {
LAB_0048bc2e:
            iVar5 = EncodeChecksumDeltaAdd(iVar3,local_ce4,param_2);
            local_4 = 8;
            local_15c0 = local_15c0 | 2;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState((void *)iVar5);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 < 0x14) {
              uVar2 = 0x14;
            }
            else {
              iVar5 = EncodeChecksumDeltaAdd(iVar3,local_112c,param_2);
              local_4 = 9;
              local_15c0 = local_15c0 | 4;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar2 = PeekPacketChecksumState((void *)iVar5);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            iVar5 = EncodeChecksumDeltaAdd(iVar3,local_454,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
            local_15c0 = local_15c0 | 1;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState((void *)iVar5);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar5 < 0x65) goto LAB_0048bc2e;
            uVar2 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((void *)local_15a8,uVar2);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_4 = 8;
          if (((local_15c0 & 4) != 0) && (local_15c0 = local_15c0 & 0xfffffffb, (*(int *)(local_112c + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1598);
          }
          local_4 = 7;
          if (((local_15c0 & 2) != 0) && (local_15c0 = local_15c0 & 0xfffffffd, (*(int *)(local_ce4 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1598);
          }
          local_4 = 6;
          if (((local_15c0 & 1) != 0) && (local_15c0 = local_15c0 & 0xfffffffe, (*(int *)(local_454 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1598);
          }
          local_4 = 0xffffffff;
          if ((*(int *)(local_89c + 0x14)) != 0) {
            ScrambleChecksumGuardBytes();
            TreeLowerBound(local_1598);
          }
          local_15ad = '\x01';
        }
        iVar3 = local_15b4;
        pbVar11 = (byte *)(local_15b4 + 0xf4c);
        cVar1 = DecodeGuardedBool();
        if ((cVar1 != '\0') && (*(char *)(iVar3 + 0x3f9c) == '\0')) {
          iVar5 = FUN_00451030(local_15b8);
          *(int *)(iVar3 + 0xf48) = iVar5;
          if (iVar5 != 0) {
            *(undefined4 *)(iVar3 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *pbVar11 = (byte)iVar5;
            iVar5 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar3 + 0xf4d) = (byte)iVar5;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar6 = ~bVar6 & (byte)iVar5 | bVar6;
            *(byte *)(iVar3 + 0xf4d) = bVar6;
            *(byte *)(iVar3 + 0xf4e) = bVar6 + bVar7 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = g_clientContext;
            pbVar11 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *pbVar11 = (byte)iVar5;
            iVar5 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar3 + 0x62141) = (byte)iVar5;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar7 = *pbVar11;
            bVar6 = ~bVar6 & (byte)iVar5 | bVar6;
            *(byte *)(iVar3 + 0x62141) = bVar6;
            *(byte *)(iVar3 + 0x62142) = bVar6 + bVar7 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
          }
        }
        cVar1 = PeekPacketChecksumBool((byte *)(iVar3 + 0x3918));
        if ((cVar1 == '\0') && (iVar5 = FUN_004511b0(local_15b8), iVar5 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *(byte *)(iVar3 + 0x3918) = (byte)iVar5;
          iVar5 = _rand();
          bVar7 = *(byte *)(iVar3 + 0x3918);
          *(byte *)(iVar3 + 0x3919) = (byte)iVar5;
          bVar6 = '\x01' << (bVar7 & 7);
          bVar6 = ~bVar6 & (byte)iVar5 | bVar6;
          *(byte *)(iVar3 + 0x3919) = bVar6;
          *(byte *)(iVar3 + 0x391a) = bVar6 + bVar7 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar2 = PeekPacketChecksumState((void *)local_15a8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15b8,local_15bc,uVar2);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState((void *)local_15a8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar3 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = PeekPacketChecksumState((void *)(local_15b4 + 0x6ac));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState((void *)(local_15b4 + 0x488));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15b8 - (iVar5 >> 8),local_15bc - (iVar3 >> 8),
                       *(undefined4 *)(local_15b4 + 0x1e50));
        }
        cVar1 = PeekPacketChecksumBool((byte *)(local_15b4 + 0x3918));
        if (cVar1 != '\0') {
          FUN_00436ec0(local_15b8,local_15bc);
        }
        cVar1 = FUN_00450e10(local_15bc);
        iVar3 = local_15b4;
        if (cVar1 != '\0') {
          FUN_00458920(&local_15c4,&local_15bc,local_159c,local_15a4,local_1590,local_1578,
                       local_1588,0,1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = local_15b4;
          EncodeOutgoingPacketField((void *)(local_15b4 + 0x40),local_15c4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((void *)(local_15b4 + 0x264),local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = local_15c4;
LAB_0048c475:
          EncodeOutgoingPacketField((void *)(local_15b4 + 0xf54),iVar5);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_0048c494:
          EncodeOutgoingPacketField((void *)(local_15b4 + 0x1178),local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *(char *)(iVar3 + 0xf45) = (char)iVar5;
          iVar5 = _rand();
          *(byte *)(iVar3 + 0xf46) = (byte)iVar5;
          bVar7 = '\x01' << (*(byte *)(iVar3 + 0xf45) & 7);
          bVar7 = ~bVar7 & (byte)iVar5 | bVar7;
          *(byte *)(iVar3 + 0xf46) = bVar7;
          *(byte *)(iVar3 + 0xf47) = bVar7 + *(char *)(iVar3 + 0xf45) + -0x34;
LAB_0048d0e3:
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          break;
        }
        local_15c4 = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState((void *)(local_15b4 + 0x24c0));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_158c = PeekPacketChecksumState((void *)(local_15b4 + 0x1178));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState((void *)(local_15b4 + 0xf54));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = HitTestLocalMobile(g_clientContext,local_15a0,local_158c,iVar5 / *(int *)(iVar3 + 0x3fa4));
          if (((iVar5 != 0) && (cVar1 = PeekPacketChecksumBool((byte *)(iVar5 + 0x908)), cVar1 != '\0')) &&
             (cVar1 = PeekPacketChecksumBool((byte *)(iVar5 + 0xbff7)), cVar1 != '\x01')) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x40),local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x264),local_15bc << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0xf54),local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            goto LAB_0048c494;
          }
          local_15c4 = local_15c4 + 1;
        } while (local_15c4 < 8);
        local_15c4 = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState((void *)(local_15b4 + 0x24c0));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_158c = PeekPacketChecksumState((void *)(local_15b4 + 0x1178));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar2 = PeekPacketChecksumState((void *)(local_15b4 + 0xf54));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          /* RECOVERED (2026-08-19): the dropped EDX argument - the 0..7 SLOT
           * index this loop is walking - plus the resulting two-position shift.
           * HitTestJewel is the layer-100006 twin of HitTestLocalMobile:
           * it looks up the entity at slot EDX and guard-computes
           * (entityX - x, entityY - y) from its +0x25c/+0x480 cells.  param_1 is
           * a PHANTOM (Ghidra marks the function __fastcall, but ECX is written
           * before it is ever read - orig 0x425caa mov ecx,[eax+0x6a7f8c]), so it is passed 0. */
          iVar5 = HitTestJewel(0,local_15c4,uVar2,local_158c,local_15a0 / *(int *)(iVar3 + 0x3fa4));
          if (iVar5 != 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x40),local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x264),local_15bc << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0xf54),local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            goto LAB_0048c494;
          }
          local_15c4 = local_15c4 + 1;
        } while (local_15c4 < 8);
        local_15c4 = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState((void *)(local_15b4 + 0x24c0));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_158c = PeekPacketChecksumState((void *)(local_15b4 + 0x1178));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar2 = PeekPacketChecksumState((void *)(local_15b4 + 0xf54));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          /* RECOVERED (2026-08-19): the dropped EDX argument - the 0..7 SLOT
           * index this loop is walking - plus the resulting two-position shift.
           * FUN_00425e60 is the layer-100003 twin of HitTestLocalMobile:
           * it looks up the entity at slot EDX and guard-computes
           * (entityX - x, entityY - y) from its +0x25c/+0x480 cells.  param_1 is
           * a PHANTOM (Ghidra marks the function __fastcall, but ECX is written
           * before it is ever read - orig 0x425e7a mov ecx,[eax+0x6a7f8c]), so it is passed 0. */
          iVar5 = FUN_00425e60(0,local_15c4,uVar2,local_158c,local_15a0 / *(int *)(iVar3 + 0x3fa4));
          if (iVar5 != 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x40),local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x264),local_15bc << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = local_15b8;
            goto LAB_0048c475;
          }
          local_15c4 = local_15c4 + 1;
        } while (local_15c4 < 0x40);
        local_15b8 = local_15b8 + local_1580[0];
        local_15a4 = local_15a4 + param_2;
      } while (local_15a4 < (int)local_15ac);
    }
  }
  else {
    local_1578 = ((local_159c - local_1590) * 0x10000) / iVar10;
    local_1588 = local_1590 << 0x10;
    if (local_15a4 < iVar3) {
      local_15b8 = iVar3 + -1;
      local_1590 = -1;
    }
    else {
      local_15b8 = iVar3 + 1;
      local_1590 = 1;
    }
    local_1598[0] = iVar9 + param_2;
    local_15a4 = 0;
    if (0 < (int)local_1598[0]) {
      local_1584 = local_1578 * param_2;
      local_15a8 = local_15b4 + 0x15c0;
      local_158c = local_1590 * param_2;
      local_159c = local_15b8;
      do {
        local_1588 = local_1588 + local_1584;
        iVar3 = local_1588 >> 0x10;
        local_15bc = local_15b8;
        local_15c4 = iVar3;
        if ((local_15ad == '\0') && (iVar5 = FUN_004510f0(iVar3), iVar5 != 0)) {
          iVar3 = EncodeChecksumDeltaAdd(local_15a8,local_230,param_2);
          local_4 = 10;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = PeekPacketChecksumState((void *)iVar3);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar3 < 0x14) {
LAB_0048c664:
            iVar3 = EncodeChecksumDeltaAdd(local_15a8,local_ac0,param_2);
            local_4 = 0xc;
            local_15c0 = local_15c0 | 0x10;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = PeekPacketChecksumState((void *)iVar3);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar3 < 0x14) {
              uVar2 = 0x14;
            }
            else {
              iVar3 = EncodeChecksumDeltaAdd(local_15a8,local_f08,param_2);
              local_4 = 0xd;
              local_15c0 = local_15c0 | 0x20;
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              uVar2 = PeekPacketChecksumState((void *)iVar3);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            }
          }
          else {
            iVar3 = EncodeChecksumDeltaAdd(local_15a8,local_678,param_2);
            local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
            local_15c0 = local_15c0 | 8;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = PeekPacketChecksumState((void *)iVar3);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar3 < 0x65) goto LAB_0048c664;
            uVar2 = 100;
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((void *)local_15a8,uVar2);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar8 = (*(int *)(local_f08 + 0x14));
          local_4 = 0xc;
          if (((local_15c0 & 0x20) != 0) && (local_15c0 = local_15c0 & 0xffffffdf, (*(int *)(local_f08 + 0x14)) != 0))
          {
            ScrambleChecksumGuardBytes();
            local_15ac = uVar8;
            TreeLowerBound(local_1580);
          }
          uVar8 = (*(int *)(local_ac0 + 0x14));
          local_4 = 0xb;
          if (((local_15c0 & 0x10) != 0) && (local_15c0 = local_15c0 & 0xffffffef, (*(int *)(local_ac0 + 0x14)) != 0))
          {
            ScrambleChecksumGuardBytes();
            local_15ac = uVar8;
            TreeLowerBound(local_1580);
          }
          uVar8 = (*(int *)(local_678 + 0x14));
          local_4 = 10;
          if (((local_15c0 & 8) != 0) && (local_15c0 = local_15c0 & 0xfffffff7, (*(int *)(local_678 + 0x14)) != 0)) {
            ScrambleChecksumGuardBytes();
            local_15ac = uVar8;
            TreeLowerBound(local_1580);
          }
          uVar8 = (*(int *)(local_230 + 0x14));
          local_4 = 0xffffffff;
          if ((*(int *)(local_230 + 0x14)) != 0) {
            ScrambleChecksumGuardBytes();
            local_15ac = uVar8;
            TreeLowerBound(local_1580);
          }
          local_15ad = '\x01';
          iVar3 = local_15c4;
        }
        iVar5 = local_15b4;
        pbVar11 = (byte *)(local_15b4 + 0xf4c);
        cVar1 = DecodeGuardedBool();
        if ((cVar1 != '\0') && (*(char *)(local_15b4 + 0x3f9c) == '\0')) {
          iVar9 = FUN_00451030(iVar3);
          *(int *)(local_15b4 + 0xf48) = iVar9;
          if (iVar9 != 0) {
            *(undefined4 *)(local_15b4 + 0xf50) = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = _rand();
            *pbVar11 = (byte)iVar3;
            iVar3 = _rand();
            bVar7 = *pbVar11;
            *(byte *)(iVar5 + 0xf4d) = (byte)iVar3;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar6 = ~bVar6 & (byte)iVar3 | bVar6;
            *(byte *)(iVar5 + 0xf4d) = bVar6;
            *(byte *)(iVar5 + 0xf4e) = bVar7 + bVar6 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = g_clientContext;
            pbVar11 = (byte *)(g_clientContext + 0x62140);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *pbVar11 = (byte)iVar5;
            local_15ac = _rand();
            local_15ac = local_15ac & 0x800000ff;
            if ((int)local_15ac < 0) {
              local_15ac = (local_15ac - 1 | 0xffffff00) + 1;
            }
            bVar7 = *pbVar11;
            *(byte *)(iVar3 + 0x62141) = (byte)local_15ac;
            bVar6 = '\x01' << (bVar7 & 7);
            bVar6 = ~bVar6 & (byte)local_15ac | bVar6;
            *(byte *)(iVar3 + 0x62141) = bVar6;
            *(byte *)(iVar3 + 0x62142) = bVar7 + bVar6 + -0x34;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15c4;
          }
        }
        iVar5 = local_15b4;
        pbVar11 = (byte *)(local_15b4 + 0x3918);
        cVar1 = PeekPacketChecksumBool((byte *)(local_15b4 + 0x3918));
        if ((cVar1 == '\0') && (iVar3 = FUN_004511b0(iVar3), iVar3 != 0)) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = _rand();
          *pbVar11 = (byte)iVar3;
          iVar3 = _rand();
          bVar7 = *pbVar11;
          *(byte *)(iVar5 + 0x3919) = (byte)iVar3;
          bVar6 = '\x01' << (bVar7 & 7);
          bVar6 = ~bVar6 & (byte)iVar3 | bVar6;
          *(byte *)(iVar5 + 0x3919) = bVar6;
          *(byte *)(iVar5 + 0x391a) = bVar7 + bVar6 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar2 = PeekPacketChecksumState((void *)local_15a8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        FUN_00436dc0(local_15c4,local_15b8,uVar2);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState((void *)local_15a8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar3 == 0) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = PeekPacketChecksumState((void *)(local_15b4 + 0x6ac));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15ac = PeekPacketChecksumState((void *)(local_15b4 + 0x488));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          FUN_00436bd0(local_15c4 - ((int)local_15ac >> 8),local_15b8 - (iVar3 >> 8),
                       *(undefined4 *)(local_15b4 + 0x1e50));
        }
        cVar1 = PeekPacketChecksumBool((byte *)(local_15b4 + 0x3918));
        if (cVar1 != '\0') {
          FUN_00436ec0(local_15c4,local_15b8);
        }
        cVar1 = FUN_00450e10(local_15b8);
        iVar3 = local_15b4;
        if (cVar1 != '\0') {
          FUN_00458a00(&local_15c4,&local_15bc,local_159c,local_15a4,local_1590,local_1578,
                       local_1588,0,1);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar3 = local_15b4;
          EncodeOutgoingPacketField((void *)(local_15b4 + 0x40),local_15c4 << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((void *)(local_15b4 + 0x264),local_15bc << 8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((void *)(local_15b4 + 0xf54),local_15c4);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((void *)(local_15b4 + 0x1178),local_15bc);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = _rand();
          *(char *)(iVar3 + 0xf45) = (char)iVar5;
          local_1598[0] = _rand();
          local_1598[0] = local_1598[0] & 0x800000ff;
          if ((int)local_1598[0] < 0) {
            local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
          }
          bVar7 = *(byte *)(iVar3 + 0xf45);
          *(byte *)(iVar3 + 0xf46) = (byte)local_1598[0];
          bVar6 = '\x01' << (bVar7 & 7);
          bVar4 = ~bVar6 & (byte)local_1598[0];
LAB_0048d0d0:
          *(byte *)(iVar3 + 0xf46) = bVar4 | bVar6;
          *(byte *)(iVar3 + 0xf47) = bVar7 + (bVar4 | bVar6) + -0x34;
          goto LAB_0048d0e3;
        }
        local_15bc = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15ac = PeekPacketChecksumState((void *)(local_15b4 + 0x24c0));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1580[0] = PeekPacketChecksumState((void *)(local_15b4 + 0x1178));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState((void *)(local_15b4 + 0xf54));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = HitTestLocalMobile(g_clientContext,local_15a0,local_1580[0],
                               (int)local_15ac / *(int *)(iVar3 + 0x3fa4));
          if (((iVar5 != 0) && (cVar1 = PeekPacketChecksumBool((byte *)(iVar5 + 0x908)), cVar1 != '\0')) &&
             (cVar1 = PeekPacketChecksumBool((byte *)(iVar5 + 0xbff7)), cVar1 != '\x01')) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x40),local_15c4 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x264),local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0xf54),local_15c4);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x1178),local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *(char *)(iVar3 + 0xf45) = (char)iVar5;
            local_1598[0] = _rand();
            local_1598[0] = local_1598[0] & 0x800000ff;
            if ((int)local_1598[0] < 0) {
              local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
            }
            bVar7 = *(byte *)(iVar3 + 0xf45);
            *(byte *)(iVar3 + 0xf46) = (byte)local_1598[0];
            bVar6 = '\x01' << (bVar7 & 7);
            bVar4 = ~bVar6 & (byte)local_1598[0];
            goto LAB_0048d0d0;
          }
          local_15bc = local_15bc + 1;
        } while (local_15bc < 8);
        local_15bc = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15ac = PeekPacketChecksumState((void *)(local_15b4 + 0x24c0));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1580[0] = PeekPacketChecksumState((void *)(local_15b4 + 0x1178));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState((void *)(local_15b4 + 0xf54));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          /* RECOVERED (2026-08-19): the dropped EDX argument - the 0..7 SLOT
           * index this loop is walking - plus the resulting two-position shift.
           * HitTestJewel is the layer-100006 twin of HitTestLocalMobile:
           * it looks up the entity at slot EDX and guard-computes
           * (entityX - x, entityY - y) from its +0x25c/+0x480 cells.  param_1 is
           * a PHANTOM (Ghidra marks the function __fastcall, but ECX is written
           * before it is ever read - orig 0x425caa mov ecx,[eax+0x6a7f8c]), so it is passed 0. */
          iVar5 = HitTestJewel(0,local_15bc,local_15a0,local_1580[0],(int)local_15ac / *(int *)(iVar3 + 0x3fa4));
          if (iVar5 != 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x40),local_15c4 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x264),local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0xf54),local_15c4);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x1178),local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *(char *)(iVar3 + 0xf45) = (char)iVar5;
            local_1598[0] = _rand();
            local_1598[0] = local_1598[0] & 0x800000ff;
            if ((int)local_1598[0] < 0) {
              local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
            }
            bVar7 = *(byte *)(iVar3 + 0xf45);
            *(byte *)(iVar3 + 0xf46) = (byte)local_1598[0];
            bVar6 = '\x01' << (bVar7 & 7);
            bVar4 = ~bVar6 & (byte)local_1598[0];
            goto LAB_0048d0d0;
          }
          local_15bc = local_15bc + 1;
        } while (local_15bc < 8);
        local_15bc = 0;
        do {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15ac = PeekPacketChecksumState((void *)(local_15b4 + 0x24c0));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_1580[0] = PeekPacketChecksumState((void *)(local_15b4 + 0x1178));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          local_15a0 = PeekPacketChecksumState((void *)(local_15b4 + 0xf54));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          /* RECOVERED (2026-08-19): the dropped EDX argument - the 0..7 SLOT
           * index this loop is walking - plus the resulting two-position shift.
           * FUN_00425e60 is the layer-100003 twin of HitTestLocalMobile:
           * it looks up the entity at slot EDX and guard-computes
           * (entityX - x, entityY - y) from its +0x25c/+0x480 cells.  param_1 is
           * a PHANTOM (Ghidra marks the function __fastcall, but ECX is written
           * before it is ever read - orig 0x425e7a mov ecx,[eax+0x6a7f8c]), so it is passed 0. */
          iVar5 = FUN_00425e60(0,local_15bc,local_15a0,local_1580[0],(int)local_15ac / *(int *)(iVar3 + 0x3fa4));
          if (iVar5 != 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = local_15b4;
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x40),local_15c4 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x264),local_15b8 << 8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0xf54),local_15c4);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField((void *)(local_15b4 + 0x1178),local_15b8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = _rand();
            *(char *)(iVar3 + 0xf45) = (char)iVar5;
            local_1598[0] = _rand();
            local_1598[0] = local_1598[0] & 0x800000ff;
            if ((int)local_1598[0] < 0) {
              local_1598[0] = (local_1598[0] - 1 | 0xffffff00) + 1;
            }
            bVar7 = *(byte *)(iVar3 + 0xf45);
            *(byte *)(iVar3 + 0xf46) = (byte)local_1598[0];
            bVar6 = '\x01' << (bVar7 & 7);
            bVar4 = ~bVar6 & (byte)local_1598[0];
            goto LAB_0048d0d0;
          }
          local_15bc = local_15bc + 1;
        } while (local_15bc < 0x40);
        local_15b8 = local_15b8 + local_158c;
        local_15a4 = local_15a4 + param_2;
      } while (local_15a4 < (int)local_1598[0]);
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

