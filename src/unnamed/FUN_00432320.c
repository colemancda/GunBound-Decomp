/* FUN_00432320 - 0x00432320 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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
  if ((((-1 < param_5) && (param_5 < *(int *)(&DAT_006a7720 + g_clientContext))) && (-0xc9 < param_1))
     && (param_1 < *(int *)(&DAT_006a7724 + g_clientContext))) {
    pvVar2 = operator_new(0x3fa0);
    local_4 = 0;
    if (pvVar2 != (void *)0x0) {
      piVar8 = (int *)FUN_004aa830();
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
    FUN_00406500(param_6);
    QueueOutgoingPacketField(param_7);
    FUN_00406500(0);
    QueueOutgoingPacketField(0);
    piVar8[0xfe4] = (uint)param_8;
    FUN_00406500(1);
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
    iVar4 = FUN_004f30c0();
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
    FUN_00406500(0);
    FUN_00406500(1);
    FUN_00406500(0);
    FUN_00406500(0);
    QueueOutgoingPacketField(0);
    QueueOutgoingPacketField(0);
    cVar1 = FUN_00406610(*(char *)(g_clientContext + 0x45127) == '\x02');
    if (cVar1 != '\0') {
      uVar3 = FUN_0040a4d0(&DAT_00e9c578);
      uVar3 = FUN_0040a7d0(piVar8 + 0x930,local_89c,uVar3);
      local_4 = 1;
      uVar5 = FUN_0040a4d0(&DAT_00796aa0);
      uVar3 = FUN_0040a8c0(uVar3,local_678,uVar5);
      local_4 = 2;
      EncodeChecksumState(uVar3);
      local_4 = 1;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      uVar3 = FUN_0040a4d0(&DAT_00e9c578);
      uVar3 = FUN_0040a7d0(piVar8 + 0x9b9,local_678,uVar3);
      local_4 = 3;
      uVar5 = FUN_0040a4d0(&DAT_00796aa0);
      uVar3 = FUN_0040a8c0(uVar3,local_89c,uVar5);
      local_4 = 4;
      EncodeChecksumState(uVar3);
      local_4 = 3;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      uVar3 = FUN_0040a4d0(&DAT_00e9c578);
      uVar3 = FUN_0040a7d0(piVar8 + 0xa42,local_230,uVar3);
      local_4 = 5;
      uVar5 = FUN_0040a4d0(&DAT_00796aa0);
      uVar3 = FUN_0040a8c0(uVar3,local_454,uVar5);
      local_4 = 6;
      EncodeChecksumState(uVar3);
      local_4 = 5;
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
    }
    FUN_0040ab20();
    FUN_0040ab20();
    FUN_0040ab20();
    (**(code **)(*piVar8 + 8))();
    (**(code **)*piVar8)(1);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

