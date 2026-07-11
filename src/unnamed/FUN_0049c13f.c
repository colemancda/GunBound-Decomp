/* FUN_0049c13f - 0x0049c13f in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0049c13f(int param_1)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
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
    PeekChecksumStateUnderLock();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    EncodeChecksumPairDiff();
    EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    PeekChecksumStateUnderLock();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    EncodeChecksumPairDiff();
    EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    PeekChecksumStateUnderLock();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    EncodeChecksumPairDiff();
    EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool();
    goto joined_r0x0049c851;
  case 6:
    if (in_stack_0000248c != 0xb) break;
    QueueOutgoingPacketField();
    PeekChecksumStateUnderLock();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    PeekChecksumStateUnderLock();
    EncodeChecksumDeltaAdd();
    EncodeChecksumPairDiff();
    EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    PeekChecksumStateUnderLock();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    PeekChecksumStateUnderLock();
    EncodeChecksumDeltaSub();
    EncodeChecksumPairDiff();
    EncodeChecksumPairSum();
    PeekPacketChecksumBool();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    SpawnPrimaryShot();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool();
joined_r0x0049c851:
    if (cVar2 == '\0') {
      AcquireSoundChannel();
    }
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) {
LAB_0049c9ad:
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        PeekChecksumStateUnderLock();
        QueueOutgoingPacketField();
      }
      SetGuardedBool();
    }
    break;
  case 8:
    if (in_stack_0000248c != 0xb) break;
    QueueOutgoingPacketField();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\x01') {
      PeekPacketChecksumBool();
    }
    EncodeChecksumPairDiff();
    EncodeChecksumPairSum();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    PeekChecksumStateUnderLock();
    SpawnItemProjectile();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\0') {
      AcquireSoundChannel();
    }
    goto LAB_0049c9ad;
  case 10:
    if (in_stack_0000248c == 0xb) {
      QueueOutgoingPacketField();
      PeekChecksumStateUnderLock();
      PeekChecksumStateUnderLock();
      EncodeChecksumDeltaAdd();
      EncodeChecksumPairDiff();
      EncodeChecksumPairSum();
      PeekPacketChecksumBool();
      PeekPacketChecksumBool();
      PeekChecksumStateUnderLock();
      PeekChecksumStateUnderLock();
      PeekChecksumStateUnderLock();
      PeekChecksumStateUnderLock();
      SpawnSuperShot();
      ScrubChecksumGuard();
      ScrubChecksumGuard();
      ScrubChecksumGuard();
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 == '\0') {
        AcquireSoundChannel();
      }
      cVar2 = FUN_0043a530();
      if (cVar2 == '\0') {
        PeekChecksumStateUnderLock();
        QueueOutgoingPacketField();
        iVar1 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar1) = 0;
        SetGuardedBool();
      }
      else {
        SetGuardedBool();
      }
    }
  }
  *unaff_FS_OFFSET = in_stack_00002478;
  return;
}

