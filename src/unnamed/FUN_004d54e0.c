/* FUN_004d54e0 - 0x004d54e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __thiscall FUN_004d54e0(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  DWORD DVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  undefined1 uVar11;
  char *pcVar12;
  char *pcVar13;
  bool bVar14;
  HWND hWnd;
  
  if (param_2 != 0) {
    if (param_2 == 10) {
      pcVar4 = (char *)FUN_0040cfe0();
      pcVar13 = (char *)(param_1 + 0x62d);
      pcVar12 = pcVar13;
      do {
        cVar2 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        *pcVar12 = cVar2;
        pcVar12 = pcVar12 + 1;
      } while (cVar2 != '\0');
      if ((*pcVar13 != '\0') &&
         (cVar2 = FUN_00415b00(pcVar13), iVar10 = DAT_007934e8, cVar2 == '\0')) {
        *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3104;
        *(undefined4 *)(iVar10 + 0x44d0) = 6;
        pcVar12 = pcVar13;
        do {
          cVar2 = *pcVar12;
          pcVar12 = pcVar12 + 1;
        } while (cVar2 != '\0');
        FUN_004d2530(pcVar13);
        uVar3 = FUN_004d2680();
        return uVar3;
      }
      if (DAT_00e9c104 != 0) {
        FUN_0040ccf0();
      }
      DAT_00e9c104 = 0;
      FUN_004f3060(&DAT_00e9c0fc);
      hWnd = *(HWND *)(DAT_007934e4 + 4);
    }
    else {
      if (param_2 - 0xbU != 0) {
        return param_2 - 0xbU;
      }
      if (DAT_00e9c104 != 0) {
        FUN_0040ccf0();
      }
      DAT_00e9c104 = 0;
      FUN_004f3060(&DAT_00e9c0fc);
      hWnd = *(HWND *)(DAT_007934e4 + 4);
    }
    SendMessageA(hWnd,0xc5,0x3c,0);
    *(undefined1 *)(param_1 + 0x62c) = 0;
    uVar3 = FUN_004da460(param_1,1,0);
    return uVar3;
  }
  if (0x48 < param_4) {
    if (300 < param_4) {
      if (param_4 != 500) {
        return 0;
      }
      bVar1 = *(byte *)(*(int *)(param_1 + 0x788) + 0x1e);
      *(bool *)(*(int *)(param_1 + 0x788) + 0x1e) = bVar1 == 0;
      return (uint)bVar1;
    }
    if (param_4 == 300) {
      uVar3 = FUN_00509110();
      return uVar3;
    }
    if (param_4 < 100) {
      return 0;
    }
    if (param_4 < 0x72) {
      iVar10 = FUN_0040a4d0(g_clientContext + 0x3b49c);
      if (((int)*(char *)(g_clientContext + 0x458fc + iVar10 * 2) == param_4 - 100) ||
         ((cVar2 = PacketChecksumEquals(g_clientContext + 0x45354,2), cVar2 != '\0' &&
          (iVar10 = FUN_0040a4d0(g_clientContext + 0x3b49c),
          (int)*(char *)(g_clientContext + 0x458fd + iVar10 * 2) == param_4 - 100)))) {
        uVar3 = FUN_00406380(1);
        return uVar3;
      }
      FUN_004da460(param_1,0,0);
      iVar10 = DAT_007934e8;
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3200;
      *(undefined4 *)(iVar10 + 0x44d0) = 6;
      cVar2 = PacketChecksumNotEquals(g_clientContext + 0x45354,2);
      if (cVar2 != '\0') {
        *(undefined4 *)(param_1 + 0x268) = 0;
      }
      cVar2 = FUN_0040a4d0(&DAT_00796aa0);
      *(char *)(*(int *)(param_1 + 0x268) + 0x259 + param_1) = (char)param_4 - cVar2;
      if (*(int *)(param_1 + 0x268) == 0) {
        *(undefined1 *)(param_1 + 0x25a) = 0xff;
      }
      iVar10 = DAT_007934e8;
      uVar3 = *(int *)(param_1 + 0x268) + 1U & 0x80000001;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
      }
      *(uint *)(param_1 + 0x268) = uVar3;
      *(undefined1 *)(*(int *)(iVar10 + 0x44d0) + 0x4d0 + iVar10) = *(undefined1 *)(param_1 + 0x259)
      ;
      iVar8 = *(int *)(iVar10 + 0x44d0);
      *(int *)(iVar10 + 0x44d0) = iVar8 + 1;
      *(undefined1 *)(iVar8 + 0x4d1 + iVar10) = *(undefined1 *)(param_1 + 0x25a);
    }
    else {
      if (param_4 != 0x72) {
        return 0;
      }
      FUN_004da460(param_1,0,0);
      iVar10 = DAT_007934e8;
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3200;
      *(undefined4 *)(iVar10 + 0x44d0) = 6;
      cVar2 = PacketChecksumNotEquals(g_clientContext + 0x45354,2);
      if (cVar2 != '\0') {
        *(undefined4 *)(param_1 + 0x268) = 0;
      }
      *(undefined1 *)(*(int *)(param_1 + 0x268) + 0x259 + param_1) = 0xff;
      if (*(int *)(param_1 + 0x268) == 0) {
        *(undefined1 *)(param_1 + 0x25a) = 0xff;
      }
      iVar10 = DAT_007934e8;
      uVar3 = *(int *)(param_1 + 0x268) + 1U & 0x80000001;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
      }
      *(uint *)(param_1 + 0x268) = uVar3;
      *(undefined1 *)(*(int *)(iVar10 + 0x44d0) + 0x4d0 + iVar10) = *(undefined1 *)(param_1 + 0x259)
      ;
      iVar8 = *(int *)(iVar10 + 0x44d0);
      *(int *)(iVar10 + 0x44d0) = iVar8 + 1;
      *(undefined1 *)(iVar8 + 0x4d1 + iVar10) = *(undefined1 *)(param_1 + 0x25a);
    }
    goto LAB_004d5661;
  }
  if (0x45 < param_4) {
    FUN_004da460(param_1,0,0);
    iVar8 = FUN_0040a4d0(g_clientContext + 0x4557c);
    iVar10 = *(int *)(&DAT_0056d350 + *(char *)(g_clientContext + 0x44ef8) * 4);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xfffcffff | (iVar8 + 1) % iVar10 << 0x10);
    goto LAB_004d5ecb;
  }
  switch(param_4) {
  case 0:
    FUN_004da460(param_1,0,0);
    iVar10 = DAT_007934e8;
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    *(undefined2 *)(iVar10 + 0x4d4) = 0x3230;
    bVar14 = *(char *)(param_1 + 0x4cc) == '\0';
    *(bool *)(param_1 + 8) = bVar14;
    *(bool *)(*(int *)(iVar10 + 0x44d0) + 0x4d0 + iVar10) = bVar14;
    goto LAB_004d5661;
  case 1:
    cVar2 = FUN_004db4b0();
    if (cVar2 == '\0') {
      Replay_AppendEvent(0x9002);
      uVar3 = Replay_FlushEvent();
      return uVar3;
    }
    FUN_004da460(param_1,0,0);
    iVar10 = DAT_007934e8;
    *(undefined4 *)(param_1 + 0x6b0) = 0xffffffff;
    *(undefined2 *)(iVar10 + 0x4d4) = 0x3430;
    *(undefined4 *)(iVar10 + 0x44d0) = 6;
    DVar5 = GetTickCount();
    iVar10 = DAT_007934e8;
    *(DWORD *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = DVar5;
    iVar8 = g_clientContext + 0x45354;
    *(int *)(iVar10 + 0x44d0) = *(int *)(iVar10 + 0x44d0) + 4;
    cVar2 = PacketChecksumEquals(iVar8,3);
    if (cVar2 != '\0') {
      iVar10 = 6;
      do {
        iVar6 = _rand();
        iVar8 = DAT_007934e8;
        *(short *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = (short)iVar6;
        *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 2;
        iVar6 = FUN_0040a4d0(&DAT_00796aa0);
        iVar7 = _rand();
        iVar8 = DAT_007934e8;
        *(char *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = (char)(iVar7 % iVar6);
        iVar10 = iVar10 + -1;
        *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 1;
      } while (iVar10 != 0);
      uVar3 = FUN_004d2680();
      return uVar3;
    }
    uVar3 = FUN_004d2680();
    return uVar3;
  case 2:
    FUN_004da460(param_1,0,0);
    iVar8 = DAT_007934e8;
    iVar10 = g_clientContext;
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    *(undefined2 *)(iVar8 + 0x4d4) = 0x3210;
    bVar14 = *(char *)(iVar10 + 0x3b6c0) != '\x01';
    *(bool *)(param_1 + 0x25b) = bVar14;
    *(bool *)(*(int *)(iVar8 + 0x44d0) + 0x4d0 + iVar8) = bVar14;
    *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 1;
    uVar3 = FUN_004d2680();
    return uVar3;
  case 3:
    FUN_004da460(param_1,0,0);
    iVar10 = DAT_007934e8;
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    *(undefined2 *)(iVar10 + 0x4d4) = 0x2000;
    *(undefined2 *)(iVar10 + 0x4d6) = 0xffff;
    *(int *)(iVar10 + 0x44d0) = *(int *)(iVar10 + 0x44d0) + 2;
    uVar3 = FUN_004d2680();
    return uVar3;
  case 4:
    FUN_004da460(param_1,0,0);
    iVar10 = DAT_007934e8;
    iVar8 = g_clientContext;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3100;
    *(undefined4 *)(iVar10 + 0x44d0) = 6;
    iVar8 = *(char *)(iVar8 + 0x44ef8) + 10;
    goto LAB_004d588d;
  case 5:
    FUN_004da460(param_1,0,0);
    iVar10 = DAT_007934e8;
    iVar8 = g_clientContext;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3100;
    *(undefined4 *)(iVar10 + 0x44d0) = 6;
    iVar8 = *(char *)(iVar8 + 0x44ef8) + 1;
LAB_004d588d:
    uVar11 = (undefined1)(iVar8 % 0xb);
    *(undefined1 *)(param_1 + 9) = uVar11;
    *(undefined1 *)(*(int *)(iVar10 + 0x44d0) + 0x4d0 + iVar10) = uVar11;
    goto LAB_004d5661;
  case 6:
    iVar10 = (*(int *)(param_1 + 0x61c) + 8) / 9;
    iVar8 = 1;
    if (0 < iVar10) {
      iVar8 = iVar10;
    }
    iVar10 = *(int *)(param_1 + 0x620) + -1 + iVar10;
    *(int *)(param_1 + 0x620) = iVar10 % iVar8;
    return iVar10 / iVar8;
  case 7:
    iVar10 = (*(int *)(param_1 + 0x61c) + 8) / 9;
    iVar8 = 1;
    if (0 < iVar10) {
      iVar8 = iVar10;
    }
    iVar10 = *(int *)(param_1 + 0x620) + 1;
    *(int *)(param_1 + 0x620) = iVar10 % iVar8;
    return iVar10 / iVar8;
  case 8:
    if (*(char *)(param_1 + 0x62c) != '\0') {
      iVar10 = FUN_0050f000();
      if (iVar10 != 0) {
        pcVar12 = *(char **)(iVar10 + 0x50);
        pcVar13 = (char *)(param_1 + 0x62d);
        do {
          cVar2 = *pcVar12;
          pcVar12 = pcVar12 + 1;
          *pcVar13 = cVar2;
          pcVar13 = pcVar13 + 1;
        } while (cVar2 != '\0');
      }
      iVar10 = DAT_007934e8;
      *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3104;
      *(undefined4 *)(iVar10 + 0x44d0) = 6;
      pcVar13 = (char *)(param_1 + 0x62d);
      do {
        cVar2 = *pcVar13;
        pcVar13 = pcVar13 + 1;
      } while (cVar2 != '\0');
      FUN_004d2530((char *)(param_1 + 0x62d));
      FUN_004d2680();
      FUN_0050ef10(&g_uiPanelManager);
      uVar3 = FUN_00406300(1);
      return uVar3;
    }
    *(undefined1 *)(param_1 + 0x62c) = 1;
    FUN_00406300(0);
    uVar3 = FUN_00508a50(&g_uiPanelManager,g_clientContext + 0x44e64);
    return uVar3;
  case 9:
    FUN_00406300(1);
    uVar3 = FUN_0050ef10(&g_uiPanelManager);
    return uVar3;
  case 10:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    uVar3 = uVar3 & 0xff47ffff | 0x440000;
    goto LAB_004d5a42;
  case 0xb:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xff0bffff | 0x80000);
    break;
  case 0xc:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    uVar3 = uVar3 & 0xff0fffff | 0xc0000;
    goto LAB_004d5a42;
  case 0xd:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xff03ffff);
    break;
  default:
    return 0;
  case 0x14:
    FUN_004da460(param_1,0,0);
    iVar10 = DAT_007934e8;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3103;
    *(undefined4 *)(iVar10 + 0x44d0) = 6;
    cVar2 = '\x04';
    goto LAB_004d5bde;
  case 0x15:
    FUN_004da460(param_1,0,0);
    iVar10 = DAT_007934e8;
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    *(undefined2 *)(iVar10 + 0x4d4) = 0x3103;
    *(undefined1 *)(param_1 + 0x230) = 6;
    *(undefined1 *)(*(int *)(iVar10 + 0x44d0) + 0x4d0 + iVar10) = 6;
    goto LAB_004d5661;
  case 0x16:
    FUN_004da460(param_1,0,0);
    iVar10 = DAT_007934e8;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3103;
    *(undefined4 *)(iVar10 + 0x44d0) = 6;
    cVar2 = '\b';
    goto LAB_004d5bde;
  case 0x17:
    if (6 < *(byte *)(g_clientContext + 0x45125)) {
      return (uint)*(byte *)(g_clientContext + 0x45125);
    }
    FUN_004da460(param_1,0,0);
    iVar10 = DAT_007934e8;
    iVar8 = g_clientContext;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3103;
    *(undefined4 *)(iVar10 + 0x44d0) = 6;
    cVar2 = (char)((*(byte *)(iVar8 + 0x45125) + 1) / 2) << 1;
LAB_004d5bde:
    *(char *)(param_1 + 0x230) = cVar2;
    *(char *)(*(int *)(iVar10 + 0x44d0) + 0x4d0 + iVar10) = cVar2;
LAB_004d5661:
    *(int *)(iVar10 + 0x44d0) = *(int *)(iVar10 + 0x44d0) + 1;
    uVar3 = FUN_004d2680();
    return uVar3;
  case 0x1e:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xfffff1ff | 0x100);
    break;
  case 0x1f:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    uVar3 = uVar3 & 0xfffff2ff | 0x200;
    goto LAB_004d5a42;
  case 0x20:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xfffff3ff | 0x300);
    break;
  case 0x21:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    uVar3 = uVar3 & 0xfffff0ff;
    goto LAB_004d5a42;
  case 0x28:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xfffffff1 | 1);
    break;
  case 0x29:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    uVar3 = uVar3 & 0xfffffff2 | 2;
    goto LAB_004d5a42;
  case 0x2a:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xfffffff0);
    break;
  case 0x32:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    uVar3 = uVar3 & 0xffffdfff | 0x1000;
    goto LAB_004d5a42;
  case 0x33:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xffffefff | 0x2000);
    break;
  case 0x34:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    uVar3 = uVar3 | 0x3000;
    goto LAB_004d5a42;
  case 0x35:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xffffdfff | 0x1000);
    break;
  case 0x3c:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    uVar3 = uVar3 & 0xffff7fff | 0x4000;
LAB_004d5a42:
    QueueOutgoingPacketField(uVar3);
    iVar10 = DAT_007934e8;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3101;
    *(undefined4 *)(iVar10 + 0x44d0) = 6;
    uVar9 = FUN_0040a4d0(param_1 + 0xc);
    iVar10 = DAT_007934e8;
    *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar9;
    *(int *)(iVar10 + 0x44d0) = *(int *)(iVar10 + 0x44d0) + 4;
    uVar3 = FUN_004d2680();
    return uVar3;
  case 0x3d:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xffffbfff | 0x8000);
    break;
  case 0x3e:
    FUN_004da460(param_1,0,0);
    uVar3 = FUN_0040a4d0(param_1 + 0x26c);
    QueueOutgoingPacketField(uVar3 & 0xffff7fff | 0x4000);
    iVar10 = DAT_007934e8;
    *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3101;
    *(undefined4 *)(iVar10 + 0x44d0) = 6;
    uVar9 = FUN_0040a4d0(param_1 + 0xc);
    iVar10 = DAT_007934e8;
    *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar9;
    *(int *)(iVar10 + 0x44d0) = *(int *)(iVar10 + 0x44d0) + 4;
    uVar3 = FUN_004d2680();
    return uVar3;
  }
LAB_004d5ecb:
  iVar10 = DAT_007934e8;
  *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x3101;
  *(undefined4 *)(iVar10 + 0x44d0) = 6;
  uVar9 = FUN_0040a4d0(param_1 + 0xc);
  iVar10 = DAT_007934e8;
  *(undefined4 *)(*(int *)(DAT_007934e8 + 0x44d0) + 0x4d0 + DAT_007934e8) = uVar9;
  *(int *)(iVar10 + 0x44d0) = *(int *)(iVar10 + 0x44d0) + 4;
  uVar3 = FUN_004d2680();
  return uVar3;
}

