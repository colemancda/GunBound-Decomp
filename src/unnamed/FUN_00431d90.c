/* FUN_00431d90 - 0x00431d90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00431e67) */

void __fastcall
FUN_00431d90(int param_1,int param_2,byte param_3,int param_4,uint param_5,undefined4 param_6,
            undefined4 param_7,byte param_8,undefined4 param_9,char param_10)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  undefined4 uVar4;
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
  puStack_8 = &LAB_0053cc82;
  *unaff_FS_OFFSET = &local_c;
  piVar8 = (int *)0x0;
  if ((((-1 < param_2) && (param_2 < *(int *)(&DAT_006a7720 + g_clientContext))) && (-0xc9 < param_1))
     && (param_1 < *(int *)(&DAT_006a7724 + g_clientContext))) {
    pvVar2 = operator_new(0x3fa0);
    local_4 = 0;
    if (pvVar2 != (void *)0x0) {
      piVar8 = (int *)FUN_004aa830();
    }
    local_4 = 0xffffffff;
    piVar8[6] = -1;
    if (param_10 == '\0') {
      iVar3 = ((char)param_5 != '\0') + 8000 + param_4 * 2;
    }
    else {
      iVar3 = param_4 + 0x2008;
    }
    piVar8[0xe25] = iVar3;
    *(byte *)(piVar8 + 0xf) = param_3 & 7;
    piVar8[0xe] = -1;
    uVar4 = QueueOutgoingPacketField(param_2);
    EncodeChecksumState(uVar4);
    QueueOutgoingPacketField(param_1);
    QueueOutgoingPacketField(param_2 << 8);
    QueueOutgoingPacketField(param_1 << 8);
    uVar4 = QueueOutgoingPacketField(0);
    uVar4 = EncodeChecksumState(uVar4);
    uVar4 = EncodeChecksumState(uVar4);
    uVar4 = EncodeChecksumState(uVar4);
    EncodeChecksumState(uVar4);
    FUN_00406500(param_6);
    QueueOutgoingPacketField(param_7);
    FUN_00406500(0);
    QueueOutgoingPacketField(0);
    piVar8[0xfe4] = (uint)param_8;
    if (param_10 == '\0') {
      iVar3 = ((char)param_5 != '\0') + 1;
    }
    else {
      iVar3 = 3;
    }
    _sprintf((char *)(piVar8 + 0xe26),s_flame_d_d_00553e48,param_4 + 1,iVar3);
    pcVar6 = (&PTR_s_11blast_xes_0056d290)[(param_5 & 0xff) * 0x10 + param_4];
    pcVar7 = (char *)((int)piVar8 + 0x3813);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *pcVar7 = cVar1;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    FUN_0041da80(g_clientContext,piVar8,param_5,param_10,1);
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\x01') {
      uVar4 = FUN_0040a7d0(piVar8 + 0x930,local_89c,3);
      local_4 = 1;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_678,uVar5);
      SUBFIELD(local_4,0,undefined1) = 2;
      FUN_0040afb0(uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar4 = FUN_0040a7d0(piVar8 + 0x9b9,local_678,3);
      local_4 = 3;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_89c,uVar5);
      SUBFIELD(local_4,0,undefined1) = 4;
      FUN_0040afb0(uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar4 = FUN_0040a7d0(piVar8 + 0xa42,local_678,3);
      local_4 = 5;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_89c,uVar5);
      SUBFIELD(local_4,0,undefined1) = 6;
      FUN_0040afb0(uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),5);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
    }
    cVar1 = FUN_00406610(*(char *)(g_clientContext + 0x45127) == '\x02');
    if (cVar1 != '\0') {
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e9c578);
      uVar4 = FUN_0040a7d0(piVar8 + 0x930,local_678,uVar4);
      local_4 = 7;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_89c,uVar5);
      SUBFIELD(local_4,0,undefined1) = 8;
      EncodeChecksumState(uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e9c578);
      uVar4 = FUN_0040a7d0(piVar8 + 0x9b9,local_678,uVar4);
      local_4 = 9;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_89c,uVar5);
      SUBFIELD(local_4,0,undefined1) = 10;
      EncodeChecksumState(uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),9);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e9c578);
      uVar4 = FUN_0040a7d0(piVar8 + 0xa42,local_230,uVar4);
      local_4 = 0xb;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_454,uVar5);
      SUBFIELD(local_4,0,undefined1) = 0xc;
      EncodeChecksumState(uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
    }
    FUN_0040ab20();
    FUN_0040ab20();
    FUN_0040ab20();
    FUN_0040ab20();
    FUN_0040ab20();
    FUN_0040ab20();
    (**(code **)(*piVar8 + 8))();
    (**(code **)*piVar8)(1);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

