/* FUN_00432320 - 0x00432320 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * 2026-09-02: FindSpriteFrame's register args recovered from orig
 * 0x43254a-0x43255b - see the site comment.
 *
 * DROPPED-REGISTER-ARG FIX (2026-09-20, 26-file / 52-call-site sweep).
 * This is InitBlastEffect's documented sibling of SpawnBlastEffect
 * (same table, same "flame%d%d" state) - but unlike SpawnBlastEffect
 * (__fastcall, 2 register args) this one is __thiscall with exactly
 * ONE register argument: `ret 0x24` = 9 stack dwords popped, and the
 * entry (0x432320-0x432349) reads only ECX (`mov ebx,ecx`), never EDX.
 * So the true call is 1 register + 9 stack = 10 arguments, matching
 * this file's OWN 10-parameter signature below (param_1 = ECX,
 * param_2..param_10 = the 9 stack slots) - Ghidra decompiled the
 * CALLEE correctly.  Every one of the ~26 caller files instead called
 * it as an ordinary 9-argument C function (no prototype was in scope -
 * Ghidra puts `void __thiscall` on its own line above the name, and
 * functions.h's auto-generator only matches single-line signatures),
 * so ECX arrived as whatever the register happened to hold and every
 * caller's own first listed argument silently became param_1 in its
 * place, shifting nothing else - all 9 existing stack arguments at
 * every site already matched param_2..param_10 position-for-position.
 *
 * SEMANTICS of param_1 (ECX): y, the terrain ROW.  Bounded `> -0xc9`
 * and `< [ctx+0x6a7724]` (g_nCameraBoundY) at 0x432362-0x432374,
 * exactly mirroring SpawnBlastEffect's param_1/y.  param_5 (the 4th
 * stack slot) is x, the terrain COLUMN, bounded against
 * g_nCameraBoundX at 0x432356 - the position confirmed by disasm
 * (`mov ebp,[esp+0x8b8]` at 0x43233d, delta 8 -> esp0+0x8b0 -> stack
 * slot 4).
 *
 * RECOVERY per call site: every site immediately precedes the call
 * with a `SyncOutgoingChecksumField(bufA, ..., bufB)` + two-Peek
 * idiom where one Peek's return feeds x (already used, e.g. uVar8)
 * and the OTHER Peek's return was a bare, dropped statement - that
 * dropped return is y.  E.g. DetonateShot1_Bullet9_16.c:410-415 syncs
 * auStack_8a0/auStack_ac4; `PeekPacketChecksumState((void*)auStack_ac4)`
 * at line 412 was dropped and uVar8 = Peek(auStack_8a0) at 415 was
 * kept for x - so auStack_ac4's return is y, now captured into a new
 * `iVarBlastY` local and passed as the new leading argument.
 * DetonateShot2_Bullet8.c:1009/1070 follow the identical
 * auStack_8b4/auStack_adc pair without the outer SyncOutgoingChecksumField
 * wrapper text.  4 sites (DetonateShot2_Bullet7.c:638,
 * DetonateShot2_Bullet2.c:638, DetonatePrimaryShot_Bullet4.c:645,
 * DetonateShot2_Bullet12.c:656) don't have a nearby dropped Peek at
 * all - Bullet7/Bullet2/PrimaryShot_Bullet4 instead have a direct
 * `param_1 + 0x45e` peek (the same y guard cell paired with the
 * `param_1 + 0x3d5` x cell used throughout these files, confirmed at
 * DetonateShot1_Bullet9_16.c:346-349 and this file's own header,
 * `+0x1178 = +0x45e`) whose result gets clobbered for another purpose
 * before reaching the call, so a fresh `PeekPacketChecksumState(
 * (void*)(param_1 + 0x45e))` was inserted inline; Bullet12 instead
 * still has `iImpactY` (the ground-row scan result, same role as
 * `puStack_af0` elsewhere) alive and unclobbered, reused directly.
 * FUN_004513b0.c:740 similarly reuses its own already-valid
 * `ppuStack_b38` (a kept `param_1 + 0x45e` peek from line 645).
 * src/cxx/Projectile.cpp carries a second, file-local extern
 * declaration of this function (its own forward-declared C shim list)
 * which also needed the new leading parameter.
 *
 * OPEN FOLLOW-UP (not fixed here, out of scope for the dropped-arg
 * bug): param_9 is declared but unread anywhere in this body, while
 * the 3 `EncodeDividedChecksum(piVar8 + N, param_10)` calls near the
 * end (matching esp0+0x8c0, i.e. arg8/param_9's own stack slot per
 * the delta-tracked disasm) may actually be misreading param_9's cell
 * under param_10's name - SpawnBlastEffect's analogous 6 calls all
 * genuinely share one flag, so this may just be a real difference
 * between the two siblings rather than a bug; left as param_10 since
 * changing it without a live oracle risks trading a confirmed dropped-
 * arg bug for an unconfirmed one.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00432404) */

void __thiscall
FUN_00432320(int param_1,byte param_2,int param_3,byte param_4,int param_5,undefined4 param_6,
            undefined4 param_7,byte param_8,undefined4 param_9,char param_10)

{
  char cVar1;
  void *pvVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *pcVar7;
  int *piVar8;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053cbe0;
  *unaff_FS_OFFSET = &local_c;
  piVar8 = (int *)0x0;
  if ((((-1 < param_5) && (param_5 < *(int *)(&g_nCameraBoundX + g_clientContext))) && (-0xc9 < param_1))
     && (param_1 < *(int *)(&g_nCameraBoundY + g_clientContext))) {
    pvVar2 = operator_new(0x3fa0);
    local_4 = 0;
    if (pvVar2 != (void *)0x0) {
      piVar8 = (int *)InitBlastEffect((undefined4 *)pvVar2);
    }
    local_4 = 0xffffffff;
    piVar8[6] = -1;
    if (param_10 == '\0') {
      piVar8[0xe25] = (param_4 != 0) + 8000 + param_3 * 2;
    }
    else {
      piVar8[0xe25] = param_3 + 0x2008;
    }
    piVar8[0xe] = -1;
    *(byte *)(piVar8 + 0xf) = param_2 & 7;
    uVar3 = QueueOutgoingPacketField(param_5);
    EncodeChecksumState(uVar3);
    QueueOutgoingPacketField(param_1);
    QueueOutgoingPacketField(param_5 << 8);
    QueueOutgoingPacketField(param_1 << 8);
    uVar3 = QueueOutgoingPacketField(0);
    uVar3 = EncodeChecksumState(uVar3);
    uVar3 = EncodeChecksumState(uVar3);
    uVar3 = EncodeChecksumState(uVar3);
    EncodeChecksumState(uVar3);
    SetGuardedBool(param_6,GB_GUARD_UNRECOVERED);
    QueueOutgoingPacketField(param_7);
    SetGuardedBool(0,GB_GUARD_UNRECOVERED);
    QueueOutgoingPacketField(0);
    piVar8[0xfe4] = (uint)param_8;
    SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    if (param_10 == '\0') {
      iVar4 = (param_4 != 0) + 1;
    }
    else {
      iVar4 = 3;
    }
    _sprintf((char *)(piVar8 + 0xe26),s_flame_d_d_00553e48,param_3 + 1,iVar4);
    pcVar6 = (&PTR_s_11blast_xes_0056d290)[(uint)param_4 * 0x10 + param_3];
    pcVar7 = (char *)((int)piVar8 + 0x3813);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *pcVar7 = cVar1;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    /* RECOVERED (2026-09-02), orig 0x43254a-0x43255b: EAX =
     * [0x5b3484]+0x6a7f88 = g_clientContext + 0x6a7f88 (the active-object
     * layer registry, class-id keyed), EDX = 0x186aa (class id), ESI = 0
     * (frame, `xor esi,esi` @0x432554).  Cached scan: tools/
     * findspriteframe_sites.json call_addr 0x43255b. */
    iVar4 = FindSpriteFrame(g_clientContext + 0x6a7f88,0x186aa,0);
    if (iVar4 != 0) {
      uVar3 = FUN_004ac260();
      QueueOutgoingPacketField(uVar3);
      uVar3 = FUN_004ac260();
      QueueOutgoingPacketField(uVar3);
      uVar3 = FUN_004ac260();
      QueueOutgoingPacketField(uVar3);
      uVar3 = FUN_004ac330();
      QueueOutgoingPacketField(uVar3);
      uVar3 = FUN_004ac330();
      QueueOutgoingPacketField(uVar3);
      uVar3 = FUN_004ac330();
      QueueOutgoingPacketField(uVar3);
    }
    QueueOutgoingPacketField(0x96);
    QueueOutgoingPacketField(0x96);
    QueueOutgoingPacketField(0x96);
    QueueOutgoingPacketField(100);
    SetGuardedBool(0,GB_GUARD_UNRECOVERED);
    SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    SetGuardedBool(0,GB_GUARD_UNRECOVERED);
    SetGuardedBool(0,GB_GUARD_UNRECOVERED);
    QueueOutgoingPacketField(0);
    QueueOutgoingPacketField(0);
    cVar1 = CheckGuardedBoolAnd(*(char *)(g_clientContext + 0x45127) == '\x02');
    if (cVar1 != '\0') {
      uVar3 = PeekChecksumStateUnderLock(&DAT_00e9c578);
      uVar3 = EncodeChecksumDeltaMul(piVar8 + 0x930,local_89c,uVar3);
      local_4 = 1;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      uVar3 = EncodeChecksumDeltaDiv(uVar3,local_678,uVar5);
      local_4 = 2;
      EncodeChecksumState(uVar3);
      local_4 = 1;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar3 = PeekChecksumStateUnderLock(&DAT_00e9c578);
      uVar3 = EncodeChecksumDeltaMul(piVar8 + 0x9b9,local_678,uVar3);
      local_4 = 3;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      uVar3 = EncodeChecksumDeltaDiv(uVar3,local_89c,uVar5);
      local_4 = 4;
      EncodeChecksumState(uVar3);
      local_4 = 3;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar3 = PeekChecksumStateUnderLock(&DAT_00e9c578);
      uVar3 = EncodeChecksumDeltaMul(piVar8 + 0xa42,local_230,uVar3);
      local_4 = 5;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      uVar3 = EncodeChecksumDeltaDiv(uVar3,local_454,uVar5);
      local_4 = 6;
      EncodeChecksumState(uVar3);
      local_4 = 5;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
    }
    EncodeDividedChecksum(piVar8 + 0x795, param_10);
    EncodeDividedChecksum(piVar8 + 0x81e, param_10);
    EncodeDividedChecksum(piVar8 + 0x8a7, param_10);
    (**(code **)(*piVar8 + 8))();
    (**(code **)*piVar8)(1);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

