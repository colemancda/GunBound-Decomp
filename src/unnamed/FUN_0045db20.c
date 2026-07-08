/* FUN_0045db20 - 0x0045db20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
FUN_0045db20(int param_1,int *param_2,int param_3,undefined4 param_4,char param_5,int param_6)

{
  bool bVar1;
  char *pcVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  undefined4 *puVar13;
  char *pcVar14;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_31d4;
  undefined4 local_31cc;
  undefined1 local_31c8 [3];
  char acStack_31c5 [125];
  undefined1 local_3148 [548];
  undefined1 local_2f24 [548];
  undefined1 local_2d00 [548];
  undefined1 local_2adc [548];
  undefined1 local_28b8 [548];
  undefined1 local_2694 [548];
  undefined1 local_2470 [548];
  undefined1 local_224c [548];
  undefined1 local_2028 [548];
  undefined1 local_1e04 [548];
  undefined1 local_1be0 [548];
  undefined1 local_19bc [548];
  undefined1 local_1798 [548];
  undefined1 local_1574 [548];
  undefined1 local_1350 [548];
  undefined1 local_112c [548];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 auStack_230 [544];
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053a377;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x45db3f;
  cVar3 = FUN_004065a0();
  if ((((cVar3 != '\0') || (param_2[9] == 0xe)) || (cVar3 = FUN_004065a0(), cVar3 == '\0')) ||
     (cVar3 = FUN_004065a0(), cVar3 == '\x01')) goto LAB_0045ea1c;
  local_31cc = param_3;
  uVar4 = FUN_0040a6e0(param_2 + 0x243,local_224c,param_3);
  local_4 = 0;
  uVar5 = FUN_0045f300(param_2);
  uVar4 = FUN_0040a5f0(uVar4,local_2470,uVar5);
  local_4._0_1_ = 1;
  param_3 = FUN_0040a4d0(uVar4);
  local_4 = (uint)local_4._1_3_ << 8;
  FUN_0040a2a0();
  local_4 = 0xffffffff;
  FUN_0040a2a0();
  iVar6 = FUN_0040a4d0(g_clientContext + 0x475c8);
  iVar6 = FUN_0040a4d0((iVar6 * 0xb + (uint)*(byte *)(g_clientContext + 0x475c4)) * 0x7d28 + 0x1a1f48 +
                       g_clientContext);
  if (iVar6 == 0) {
    uVar4 = FUN_0040a8c0(param_1 + 0x24c0,local_2694,2);
    local_4 = 2;
    uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
    uVar4 = FUN_0040a5f0(uVar4,local_2adc,uVar5);
    local_4._0_1_ = 3;
    iVar7 = FUN_0040a4d0(uVar4);
    local_4 = CONCAT31(local_4._1_3_,2);
    FUN_0040a2a0();
    local_4 = 0xffffffff;
    FUN_0040a2a0();
    iVar6 = param_1 + 0x2b2c;
    iVar8 = FUN_0040a4d0(iVar6);
    if (iVar8 < 1) {
      iVar6 = 1;
    }
    else {
LAB_0045de1d:
      iVar6 = FUN_0040a4d0(iVar6);
    }
LAB_0045de25:
    iVar8 = FUN_0040a4d0(&DAT_00796aa0);
    param_3 = (iVar8 * param_3) / iVar6;
  }
  else {
    if (iVar6 == 1) {
      uVar4 = FUN_0040a8c0(param_1 + 0x26e4,local_2d00,2);
      local_4 = 4;
      uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar4 = FUN_0040a5f0(uVar4,local_2028,uVar5);
      local_4._0_1_ = 5;
      iVar7 = FUN_0040a4d0(uVar4);
      local_4 = CONCAT31(local_4._1_3_,4);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      iVar6 = param_1 + 0x2d50;
      iVar8 = FUN_0040a4d0(iVar6);
      if (0 < iVar8) goto LAB_0045de1d;
      iVar6 = 1;
      goto LAB_0045de25;
    }
    iVar7 = local_31cc;
    if (iVar6 == 2) {
      uVar4 = FUN_0040a8c0(param_1 + 0x2908,local_28b8,2);
      local_4 = 6;
      uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar4 = FUN_0040a5f0(uVar4,local_2f24,uVar5);
      local_4._0_1_ = 7;
      iVar7 = FUN_0040a4d0(uVar4);
      local_4 = CONCAT31(local_4._1_3_,6);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      iVar6 = param_1 + 0x2f74;
      iVar8 = FUN_0040a4d0(iVar6);
      if (0 < iVar8) goto LAB_0045de1d;
      iVar6 = 1;
      goto LAB_0045de25;
    }
  }
  iVar6 = FUN_0040a4d0(param_2 + 0x3de);
  iVar8 = FUN_0040a4d0(param_2 + 0x4f0);
  uVar4 = FUN_0040a6e0(param_2 + 0x2cc,local_2028,(iVar6 - iVar8) / 2);
  local_4 = 8;
  uVar5 = FUN_0040a4d0(param_2 + 0x4f0);
  uVar4 = FUN_0040a6e0(uVar4,local_2d00,uVar5);
  local_4._0_1_ = 9;
  uVar4 = FUN_0040a6e0(uVar4,local_2adc,param_4);
  local_4._0_1_ = 10;
  uVar5 = FUN_0045f5d0();
  uVar4 = FUN_0040a5f0(uVar4,local_2694,uVar5);
  local_4._0_1_ = 0xb;
  iVar6 = FUN_0040a4d0(uVar4);
  local_4._0_1_ = 10;
  FUN_0040a2a0();
  local_4._0_1_ = 9;
  FUN_0040a2a0();
  local_4 = CONCAT31(local_4._1_3_,8);
  FUN_0040a2a0();
  local_4 = 0xffffffff;
  FUN_0040a2a0();
  if (param_3 * param_3 + iVar6 * iVar6 < iVar7 * iVar7) {
    iVar6 = FUN_0040a4d0(g_clientContext + 0x475c8);
    iVar6 = FUN_0040a4d0((iVar6 * 0xb + (uint)*(byte *)(g_clientContext + 0x475c4)) * 0x7d28 + 0x1a1f48
                         + g_clientContext);
    if (iVar6 == 0) {
      uVar4 = FUN_0040a8c0(param_1 + 0x24c0,local_f08,2);
      local_4 = 0xc;
      uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar4 = FUN_0040a5f0(uVar4,local_1350,uVar5);
      local_4._0_1_ = 0xd;
      uVar5 = FUN_0040a8c0(param_1 + 0x24c0,local_1798,2);
      local_4._0_1_ = 0xe;
      uVar9 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar5 = FUN_0040a5f0(uVar5,local_19bc,uVar9);
      local_4._0_1_ = 0xf;
      FUN_0040a4d0(uVar4);
      FUN_0040a4d0(uVar5);
      uVar4 = FUN_0053753c();
      local_4._0_1_ = 0xe;
      FUN_0040a2a0();
      local_4._0_1_ = 0xd;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0xc);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      uVar4 = FUN_0040a7d0(param_1 + 0x1e54,local_3148,uVar4);
      local_4 = 0x10;
      uVar4 = FUN_0040a8c0(uVar4,local_1e04,1000);
      local_4._0_1_ = 0x11;
      local_31d4 = FUN_0040a4d0(uVar4);
      local_4 = CONCAT31(local_4._1_3_,0x10);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
    }
    else if (iVar6 == 1) {
      uVar4 = FUN_0040a8c0(param_1 + 0x26e4,local_454,2);
      local_4 = 0x12;
      uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar4 = FUN_0040a5f0(uVar4,local_1574,uVar5);
      local_4._0_1_ = 0x13;
      uVar5 = FUN_0040a8c0(param_1 + 0x26e4,local_ce4,2);
      local_4._0_1_ = 0x14;
      uVar9 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar5 = FUN_0040a5f0(uVar5,local_678,uVar9);
      local_4._0_1_ = 0x15;
      FUN_0040a4d0(uVar4);
      FUN_0040a4d0(uVar5);
      uVar4 = FUN_0053753c();
      local_4._0_1_ = 0x14;
      FUN_0040a2a0();
      local_4._0_1_ = 0x13;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x12);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      uVar4 = FUN_0040a7d0(param_1 + 0x2078,local_89c,uVar4);
      local_4 = 0x16;
      uVar4 = FUN_0040a8c0(uVar4,local_112c,1000);
      local_4._0_1_ = 0x17;
      local_31d4 = FUN_0040a4d0(uVar4);
      local_4 = CONCAT31(local_4._1_3_,0x16);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
    }
    else {
      if (iVar6 != 2) goto LAB_0045e442;
      uVar4 = FUN_0040a8c0(param_1 + 0x2908,local_2470,2);
      local_4 = 0x18;
      uVar5 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar4 = FUN_0040a5f0(uVar4,local_224c,uVar5);
      local_4._0_1_ = 0x19;
      uVar5 = FUN_0040a8c0(param_1 + 0x2908,local_2f24,2);
      local_4._0_1_ = 0x1a;
      uVar9 = FUN_0040a4d0(&DAT_00e9ba40);
      uVar5 = FUN_0040a5f0(uVar5,local_28b8,uVar9);
      local_4._0_1_ = 0x1b;
      FUN_0040a4d0(uVar4);
      FUN_0040a4d0(uVar5);
      uVar4 = FUN_0053753c();
      local_4._0_1_ = 0x1a;
      FUN_0040a2a0();
      local_4._0_1_ = 0x19;
      FUN_0040a2a0();
      local_4 = CONCAT31(local_4._1_3_,0x18);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
      uVar4 = FUN_0040a7d0(param_1 + 0x229c,local_1be0,uVar4);
      local_4 = 0x1c;
      uVar4 = FUN_0040a8c0(uVar4,local_ac0,1000);
      local_4._0_1_ = 0x1d;
      local_31d4 = FUN_0040a4d0(uVar4);
      local_4 = CONCAT31(local_4._1_3_,0x1c);
      FUN_0040a2a0();
      local_4 = 0xffffffff;
      FUN_0040a2a0();
    }
  }
  else {
LAB_0045e442:
    local_31d4 = 0;
  }
  uVar4 = FUN_0040a7d0(param_1 + 0x17e4,local_1e04,local_31d4);
  local_4 = 0x1e;
  uVar5 = FUN_0040a4d0(&DAT_00796aa0);
  uVar4 = FUN_0040a8c0(uVar4,local_3148,uVar5);
  local_4._0_1_ = 0x1f;
  iVar6 = FUN_0040a4d0(uVar4);
  local_4 = CONCAT31(local_4._1_3_,0x1e);
  FUN_0040a2a0();
  local_4 = 0xffffffff;
  FUN_0040a2a0();
  uVar4 = FUN_0040a8c0(param_1 + 0x15c0,local_3148,2);
  local_4 = 0x20;
  iVar7 = FUN_0040a4d0(param_1 + 0x139c);
  iVar8 = FUN_0040a4d0(&DAT_00796aa0);
  iVar10 = FUN_0040a4d0(uVar4);
  iVar11 = FUN_0040a4d0(&DAT_00796aa0);
  iVar11 = ((iVar7 + iVar8 + iVar10) * iVar6) / iVar11;
  local_4 = 0xffffffff;
  FUN_0040a2a0();
  if (iVar11 != 0) {
    iVar6 = FUN_0040a4d0(param_2 + 0x1948);
    cVar3 = FUN_004065a0();
    if (cVar3 != '\0') {
      uVar4 = FUN_0040a8c0(param_2 + 0x1948,local_3148,5);
      local_4 = 0x21;
      iVar7 = FUN_0040a4d0(uVar4);
      iVar6 = iVar6 - iVar7;
      local_4 = 0xffffffff;
      FUN_0040a2a0();
    }
    cVar3 = FUN_004065a0();
    if (cVar3 == '\x01') {
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
        iVar6 = iVar6 + -4;
      }
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
        iVar6 = iVar6 + 4;
      }
    }
    cVar3 = FUN_004065a0();
    if (cVar3 == '\x01') {
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
        iVar6 = iVar6 + -4;
      }
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
        iVar6 = iVar6 + 4;
      }
    }
    cVar3 = FUN_004065a0();
    if (cVar3 == '\x01') {
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
        iVar6 = iVar6 + 4;
      }
      cVar3 = FUN_004065a0();
      if (cVar3 == '\x01') {
        iVar6 = iVar6 + -4;
      }
    }
    iVar7 = FUN_0040a4d0(&DAT_00796aa0);
    iVar7 = (iVar6 * iVar11) / iVar7;
    cVar3 = FUN_004065a0();
    if (cVar3 == '\x01') {
      iVar6 = FUN_0040a4d0(param_2 + 0x2dca);
      iVar8 = FUN_0040a4d0(&DAT_00796aa0);
      iVar10 = FUN_0040a4d0(&DAT_00796aa0);
      iVar7 = ((iVar6 + iVar8) * iVar7) / iVar10;
    }
    cVar3 = FUN_004065a0();
    if (cVar3 == '\x01') {
      iVar6 = FUN_0040a4d0(param_2 + 0x2e53);
      iVar8 = FUN_0040a4d0(&DAT_00796aa0);
      iVar10 = FUN_0040a4d0(&DAT_00796aa0);
      iVar7 = ((iVar6 + iVar8) * iVar7) / iVar10;
    }
    cVar3 = FUN_004065a0();
    if (cVar3 == '\x01') {
      iVar6 = FUN_0040a4d0(param_2 + 0x2edc);
      iVar8 = FUN_0040a4d0(&DAT_00796aa0);
      iVar10 = FUN_0040a4d0(&DAT_00796aa0);
      iVar7 = ((iVar6 + iVar8) * iVar7) / iVar10;
    }
    cVar3 = FUN_004065a0();
    if (cVar3 == '\x01') {
      iVar6 = FUN_0040a4d0(param_2 + 0x2f65);
      iVar8 = FUN_0040a4d0(&DAT_00796aa0);
      iVar10 = FUN_0040a4d0(&DAT_00796aa0);
      iVar7 = ((iVar6 + iVar8) * iVar7) / iVar10;
    }
    if (0 < iVar7) {
      if (param_6 != 0) {
        iVar6 = 0;
        piVar12 = param_2 + 0x2dca;
        do {
          iVar8 = FUN_0040a4d0(piVar12);
          if (iVar8 + *(int *)(param_6 + iVar6 * 4) < 0x32) {
            iVar8 = FUN_0040a4d0(piVar12);
            iVar8 = iVar8 + *(int *)(param_6 + iVar6 * 4);
          }
          else {
            iVar8 = 0x32;
          }
          QueueOutgoingPacketField(iVar8);
          iVar6 = iVar6 + 1;
          piVar12 = piVar12 + 0x89;
        } while (iVar6 < 4);
      }
      _local_31c8 = (undefined *)((uint)_local_31c8 & 0xffffff00);
      puVar13 = (undefined4 *)((int)local_31c8 + 1);
      for (iVar6 = 0x1f; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar13 = 0;
        puVar13 = puVar13 + 1;
      }
      *(undefined2 *)puVar13 = 0;
      *(undefined1 *)((int)puVar13 + 2) = 0;
      if (param_5 == '\0') {
        uVar4 = FUN_0040a6e0(param_2 + 0x243,local_3148,local_31cc);
        local_4 = 0x22;
        iVar6 = FUN_0040a4d0(uVar4);
        local_4 = 0xffffffff;
        FUN_0040a2a0();
        cVar3 = PacketChecksumEquals(param_2 + 0x715,0);
        if (cVar3 == '\0') {
          bVar1 = iVar6 < 1;
        }
        else {
          bVar1 = 0 < iVar6;
        }
        _local_31c8 = (undefined *)CONCAT31(stack0xffffce39,bVar1 * '\x04' + 'b');
        pcVar2 = (char *)((int)&local_31cc + 3);
        do {
          pcVar14 = pcVar2;
          pcVar2 = pcVar14 + 1;
        } while (pcVar14[1] != '\0');
        *(undefined4 *)(pcVar14 + 1) = s_damage_00555cc0._0_4_;
        *(undefined2 *)(pcVar14 + 5) = s_damage_00555cc0._4_2_;
        pcVar14[7] = s_damage_00555cc0[6];
      }
      else {
        _local_31c8 = &DAT_00656369;
      }
      iVar6 = param_2[9];
      if (((iVar6 != 5) && (iVar6 != 6)) && ((iVar6 != 8 && (iVar6 != 10)))) {
        (**(code **)(*param_2 + 4))(local_31c8);
      }
      cVar3 = PacketChecksumEquals(g_clientContext + 0x45354,3);
      if (cVar3 == '\0') {
        uVar4 = FUN_0040a6e0(param_2 + 0x1bf5,local_3148,iVar7);
        local_4 = 0x23;
        iVar6 = FUN_0040a4d0(uVar4);
        local_4 = 0xffffffff;
        FUN_0040a2a0();
        if (iVar6 < 1) {
          QueueOutgoingPacketField(0);
        }
        else {
          QueueOutgoingPacketField(iVar6);
          iVar6 = 0;
        }
        AddToPacketChecksum(iVar6);
        uVar4 = FUN_0040a6e0(param_2 + 0x2cc,auStack_230,0xf);
        local_4 = 0x24;
        uVar4 = FUN_0040a4d0(uVar4);
        uVar5 = FUN_0040a4d0(param_2 + 0x243);
        FUN_00436860(uVar5,uVar4);
        local_4 = 0xffffffff;
        FUN_0040a2a0();
        *(undefined1 *)(param_2 + 0x2c2b) = *(undefined1 *)(param_1 + 0x3c);
        if (*(byte *)(param_1 + 0x3c) < 8) {
          if (*(char *)(*(byte *)(param_1 + 0x3c) + 0x4590c + g_clientContext) ==
              *(char *)((param_2[2] & 7U) + 0x4590c + g_clientContext)) {
            piVar12 = (int *)(g_clientContext + 0x5b83c + (uint)*(byte *)(param_1 + 0x3c) * 4);
            *piVar12 = *piVar12 + iVar7;
            *(undefined1 *)(param_2 + 0x2c2d) = 1;
          }
          else {
            *(int *)(g_clientContext + 0x5b81c + (uint)*(byte *)(param_1 + 0x3c) * 4) =
                 *(int *)(g_clientContext + 0x5b81c + (uint)*(byte *)(param_1 + 0x3c) * 4) + iVar7;
          }
        }
        cVar3 = FUN_004065a0();
        if ((cVar3 == '\x01') && (iVar6 = FUN_004f30c0(), iVar6 != 0)) {
          AddToPacketChecksum(iVar7);
        }
      }
    }
  }
LAB_0045ea1c:
  *unaff_FS_OFFSET = local_c;
  return;
}

