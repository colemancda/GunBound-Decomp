/* FUN_0045d640 - 0x0045d640 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_0045d640(int param_1,int param_2)

{
  int *piVar1;
  char cVar2;
  undefined1 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  uint3 uVar8;
  uint3 extraout_var;
  uint3 extraout_var_00;
  uint3 extraout_var_01;
  uint3 extraout_var_02;
  int *unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  undefined1 auStack_ac8 [8];
  undefined1 auStack_ac0 [20];
  int iStack_aac;
  undefined1 auStack_89c [20];
  int iStack_888;
  undefined1 auStack_678 [20];
  int iStack_664;
  undefined1 auStack_454 [548];
  undefined1 auStack_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int iStack_4;
  
  local_c = *unaff_FS_OFFSET;
  iStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053c429;
  *unaff_FS_OFFSET = &local_c;
  uVar4 = PeekPacketChecksumBool();
  if ((char)uVar4 == '\0') {
LAB_0045d679:
    *unaff_FS_OFFSET = local_c;
    return uVar4 & 0xffffff00;
  }
  uVar4 = PeekPacketChecksumBool();
  if ((char)uVar4 == '\x01') goto LAB_0045d679;
  uVar5 = EncodeChecksumDeltaDiv(unaff_EDI + 0x355,auStack_89c,2);
  iStack_4 = 0;
  uVar5 = EncodeChecksumPairDiff(unaff_EDI + 0x243,auStack_678,uVar5);
  SUBFIELD(iStack_4,0,undefined1) = 1;
  uVar6 = FUN_0045f300(unaff_EDI);
  EncodeChecksumDeltaAdd(uVar5,auStack_ac0,uVar6);
  SUBFIELD(iStack_4,0,undefined1) = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  SUBFIELD(iStack_4,0,undefined1) = 1;
  if (iStack_aac != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(auStack_ac8);
  }
  iStack_4 = (uint)SUBFIELD(iStack_4,1,undefined3) << 8;
  if (iStack_664 != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(auStack_ac8);
  }
  iStack_4 = 0xffffffff;
  uVar5 = 0;
  if (iStack_888 != 0) {
    ScrambleChecksumGuardBytes();
    uVar5 = FUN_0040b540(auStack_ac8);
  }
  uVar8 = (uint3)((uint)uVar5 >> 8);
  if (iVar7 <= param_1) {
    uVar5 = EncodeChecksumDeltaDiv(unaff_EDI + 0x355,auStack_ac0,2);
    iStack_4 = 3;
    uVar5 = EncodeChecksumPairSum(unaff_EDI + 0x243,auStack_678,uVar5);
    SUBFIELD(iStack_4,0,undefined1) = 4;
    uVar6 = FUN_0045f300(unaff_EDI);
    uVar5 = EncodeChecksumDeltaAdd(uVar5,auStack_89c,uVar6);
    SUBFIELD(iStack_4,0,undefined1) = 5;
    cVar2 = FUN_0040b330(uVar5,param_1);
    SUBFIELD(iStack_4,0,undefined1) = 4;
    ScrubChecksumGuard();
    iStack_4 = CONCAT31(SUBFIELD(iStack_4,1,undefined3),3);
    ScrubChecksumGuard();
    iStack_4 = 0xffffffff;
    ScrubChecksumGuard();
    uVar8 = extraout_var;
    if (cVar2 == '\0') {
      piVar1 = unaff_EDI + 0x2cc;
      uVar5 = EncodeChecksumPairDiff(piVar1,auStack_ac0,unaff_EDI + 0x3de);
      iStack_4 = 6;
      uVar5 = EncodeChecksumPairDiff(uVar5,auStack_678,unaff_EDI + 0x4f0);
      SUBFIELD(iStack_4,0,undefined1) = 7;
      uVar6 = FUN_0045f5d0();
      uVar5 = EncodeChecksumDeltaAdd(uVar5,auStack_89c,uVar6);
      SUBFIELD(iStack_4,0,undefined1) = 8;
      iVar7 = PeekChecksumStateUnderLock(uVar5);
      SUBFIELD(iStack_4,0,undefined1) = 7;
      ScrubChecksumGuard();
      iStack_4 = CONCAT31(SUBFIELD(iStack_4,1,undefined3),6);
      ScrubChecksumGuard();
      iStack_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar8 = extraout_var_00;
      if (iVar7 <= param_2) {
        uVar5 = EncodeChecksumPairDiff(piVar1,auStack_230,unaff_EDI + 0x4f0);
        iStack_4 = 9;
        uVar6 = FUN_0045f5d0();
        uVar5 = EncodeChecksumDeltaAdd(uVar5,auStack_454,uVar6);
        SUBFIELD(iStack_4,0,undefined1) = 10;
        cVar2 = FUN_0040b330(uVar5,param_2);
        iStack_4 = CONCAT31(SUBFIELD(iStack_4,1,undefined3),9);
        ScrubChecksumGuard();
        iStack_4 = 0xffffffff;
        ScrubChecksumGuard();
        uVar8 = extraout_var_01;
        if (cVar2 == '\0') {
          if (DAT_0079352a != '\0') {
            Replay_AppendEvent(0xf001);
            (&g_replayEventBuffer)[g_replayEventCursor] = (char)unaff_EDI[2];
            g_replayEventCursor = g_replayEventCursor + 1;
            uVar3 = PeekChecksumStateUnderLock(unaff_EDI + 0x68b);
            (&g_replayEventBuffer)[g_replayEventCursor] = uVar3;
            g_replayEventCursor = g_replayEventCursor + 1;
            uVar5 = PeekChecksumStateUnderLock(unaff_EDI + 0x18be);
            *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
            g_replayEventCursor = g_replayEventCursor + 4;
            uVar5 = PeekChecksumStateUnderLock(unaff_EDI + 0x243);
            *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
            g_replayEventCursor = g_replayEventCursor + 4;
            uVar5 = PeekChecksumStateUnderLock(piVar1);
            *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
            g_replayEventCursor = g_replayEventCursor + 4;
            uVar5 = (**(code **)(*unaff_EDI + 0x14))();
            *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
            g_replayEventCursor = g_replayEventCursor + 4;
            uVar5 = PeekChecksumStateUnderLock(unaff_EDI + 0x2261);
            *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
            g_replayEventCursor = g_replayEventCursor + 4;
            uVar5 = FUN_0045f300(unaff_EDI);
            *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
            g_replayEventCursor = g_replayEventCursor + 4;
            uVar5 = FUN_0045f5d0();
            *(undefined4 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
            g_replayEventCursor = g_replayEventCursor + 4;
            Replay_FlushEvent();
            uVar8 = extraout_var_02;
          }
          uVar4 = CONCAT31(uVar8,1);
          goto LAB_0045dafa;
        }
      }
    }
  }
  uVar4 = (uint)uVar8 << 8;
LAB_0045dafa:
  *unaff_FS_OFFSET = local_c;
  return uVar4;
}

