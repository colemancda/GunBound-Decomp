/* FUN_0049c13f - 0x0049c13f in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARG FIX (2026-08-11): all 39 argless PeekChecksumStateUnderLock()
 * calls now pass their guarded-cell pointer, recovered from
 * tools/underlock_push_sites.json + full disasm of the original
 * function (this file and FUN_0049c120.c are two Ghidra decompiles of
 * the SAME split original at 0x49c120/0x49c13f; this one is fully
 * value-stripped, so sites were mapped in cluster order against the
 * disasm, cross-checked against FUN_0049c120.c's artifact-bearing
 * decompile of the shared paths). Per weapon-case cluster the args are:
 * the mode cell ([esi+0x651c]==1 ? 0x796aa0 : 0x794e48 - the original's
 * two-way push that this decompile dropped entirely, restored as a
 * ternary), &DAT_00794bf0/&DAT_007949c8 literal cells, param_1+0x7864 /
 * param_1+0x4d90, and the returns of the preceding EncodeChecksum*
 * helper calls, which this decompile discarded - those are now captured
 * in new locals uVar4/uVar5/uVar6 solely to feed the Peek calls
 * (verified per site: e.g. `mov ebp,eax` after `call 0x40aca0` then
 * `push ebp` at 0x49c4e4, `mov ebx,eax` after `call 0x40aba0` then
 * `push ebx` at 0x49c4eb, stack-slot reloads at 0x49c2aa/0x49c2b6 etc.).
 */
#include "ghidra_types.h"


void __fastcall FUN_0049c13f(int param_1)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined4 in_stack_00002478;
  undefined4 in_stack_00002488;
  int in_stack_0000248c;
  
  FUN_0045f840();
  switch(in_stack_00002488) {
  case 1:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      uVar3 = AcquireSoundChannel();
      *(undefined4 *)(param_1 + 0xb0a4) = uVar3;
    }
    break;
  default:
    iVar1 = *(int *)(param_1 + 0xb0a4);
    if (DAT_00793549 != '\0') {
      if (iVar1 != -1) {
        (**(code **)(**(int **)(DAT_00793554 + iVar1 * 4) + 0xc))();
      }
      if (iVar1 == 0) {
        DAT_00793568 = 0;
      }
    }
    *(undefined4 *)(param_1 + 0xb0a4) = 0xffffffff;
    break;
  case 4:
    if (*(int *)(param_1 + 0xb0a4) == -1) {
      uVar3 = AcquireSoundChannel();
      *(undefined4 *)(param_1 + 0xb0a4) = uVar3;
    }
    break;
  case 5:
    if (in_stack_0000248c != 0xb) break;
    QueueOutgoingPacketField();
    PeekChecksumStateUnderLock((*(char *)(param_1 + 0x651c) == '\x01') ? (void *)&DAT_00796aa0 : (void *)&DAT_00794e48);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    uVar4 = EncodeChecksumPairDiff();
    uVar5 = EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock(param_1 + 0x7864);
    PeekChecksumStateUnderLock(param_1 + 0x4d90);
    PeekChecksumStateUnderLock(uVar4);
    PeekChecksumStateUnderLock(uVar5);
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    PeekChecksumStateUnderLock((*(char *)(param_1 + 0x651c) == '\x01') ? (void *)&DAT_00796aa0 : (void *)&DAT_00794e48);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    uVar4 = EncodeChecksumPairDiff();
    uVar5 = EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock(param_1 + 0x7864);
    PeekChecksumStateUnderLock(param_1 + 0x4d90);
    PeekChecksumStateUnderLock(uVar4);
    PeekChecksumStateUnderLock(uVar5);
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    PeekChecksumStateUnderLock((*(char *)(param_1 + 0x651c) == '\x01') ? (void *)&DAT_00796aa0 : (void *)&DAT_00794e48);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    uVar4 = EncodeChecksumPairDiff();
    uVar5 = EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock(param_1 + 0x7864);
    PeekChecksumStateUnderLock(param_1 + 0x4d90);
    PeekChecksumStateUnderLock(uVar4);
    PeekChecksumStateUnderLock(uVar5);
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
    goto joined_r0x0049c851;
  case 6:
    if (in_stack_0000248c != 0xb) break;
    QueueOutgoingPacketField();
    PeekChecksumStateUnderLock((*(char *)(param_1 + 0x651c) == '\x01') ? (void *)&DAT_00796aa0 : (void *)&DAT_00794e48);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    PeekChecksumStateUnderLock(&DAT_00794bf0);
    uVar4 = EncodeChecksumDeltaAdd();
    uVar5 = EncodeChecksumPairDiff();
    uVar6 = EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock(uVar4);
    PeekChecksumStateUnderLock(param_1 + 0x4d90);
    PeekChecksumStateUnderLock(uVar5);
    PeekChecksumStateUnderLock(uVar6);
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    PeekChecksumStateUnderLock((*(char *)(param_1 + 0x651c) == '\x01') ? (void *)&DAT_00796aa0 : (void *)&DAT_00794e48);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    PeekChecksumStateUnderLock(&DAT_00794bf0);
    uVar4 = EncodeChecksumDeltaSub();
    uVar5 = EncodeChecksumPairDiff();
    uVar6 = EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock(uVar4);
    PeekChecksumStateUnderLock(param_1 + 0x4d90);
    PeekChecksumStateUnderLock(uVar5);
    PeekChecksumStateUnderLock(uVar6);
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
joined_r0x0049c851:
    if (cVar2 == '\0') {
      AcquireSoundChannel();
    }
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) {
LAB_0049c9ad:
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField();
      }
      SetGuardedBool(0,GB_GUARD_UNRECOVERED) /* value+ptr both dropped; unrecovered */;
    }
    break;
  case 8:
    if (in_stack_0000248c != 0xb) break;
    QueueOutgoingPacketField();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    uVar4 = EncodeChecksumPairDiff();
    uVar5 = EncodeChecksumPairSum();
    PeekChecksumStateUnderLock(param_1 + 0x7864);
    PeekChecksumStateUnderLock(param_1 + 0x4d90);
    PeekChecksumStateUnderLock(uVar4);
    PeekChecksumStateUnderLock(uVar5);
    SpawnItemProjectile();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
    if (cVar2 == '\0') {
      AcquireSoundChannel();
    }
    goto LAB_0049c9ad;
  case 10:
    if (in_stack_0000248c == 0xb) {
      QueueOutgoingPacketField();
      PeekChecksumStateUnderLock((*(char *)(param_1 + 0x651c) == '\x01') ? (void *)&DAT_00796aa0 : (void *)&DAT_00794e48);
      PeekChecksumStateUnderLock(&DAT_00794bf0);
      uVar4 = EncodeChecksumDeltaAdd();
      uVar5 = EncodeChecksumPairDiff();
      uVar6 = EncodeChecksumPairSum();
      PeekPacketChecksumBool();
      PeekPacketChecksumBool();
      PeekChecksumStateUnderLock(uVar4);
      PeekChecksumStateUnderLock(param_1 + 0x4d90);
      PeekChecksumStateUnderLock(uVar5);
      PeekChecksumStateUnderLock(uVar6);
      SpawnSuperShot();
      ScrubChecksumGuard();
      ScrubChecksumGuard();
      ScrubChecksumGuard();
      cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if (cVar2 == '\0') {
        AcquireSoundChannel();
      }
      cVar2 = InitChecksumSeed();
      if (cVar2 == '\0') {
        PeekChecksumStateUnderLock(&DAT_007949c8);
        QueueOutgoingPacketField();
        iVar1 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar1) = 0;
        SetGuardedBool(0,GB_GUARD_UNRECOVERED) /* value+ptr both dropped; unrecovered */;
      }
      else {
        SetGuardedBool(0,GB_GUARD_UNRECOVERED) /* value+ptr both dropped; unrecovered */;
      }
    }
  }
  *unaff_FS_OFFSET = in_stack_00002478;
  return;
}

