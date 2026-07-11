/* FUN_00411b40 - 0x00411b40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Type propagation algorithm not settling */

void __fastcall FUN_00411b40(uint *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  ushort in_AX;
  uint *puVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined1 *puVar9;
  uint local_158;
  uint local_154;
  uint local_150;
  undefined1 local_14c;
  uint local_148;
  uint local_144;
  undefined1 local_140;
  uint local_13c;
  uint local_138;
  uint local_134;
  uint local_130;
  undefined1 local_12c;
  int local_128;
  uint local_124;
  uint local_120;
  uint local_11c;
  uint local_118;
  uint local_114;
  undefined2 local_110;
  undefined1 local_10e;
  undefined1 local_108 [3];
  undefined1 uStack_105;
  uint local_104;
  uint local_100;
  uint local_fc;
  uint local_f8;
  undefined1 local_f4;
  
  iVar7 = g_clientContext;
  if (in_AX < 0xa251) {
    if (in_AX == 0xa250) {
      local_13c = *param_1;
      local_138 = param_1[1];
      local_134 = param_1[2];
      local_130 = param_1[3];
      local_158 = param_1[4];
      local_150 = param_1[6];
      local_154 = param_1[5];
      local_12c = 0;
      local_14c = 0;
      FUN_00426620(&DAT_006aa41c + g_clientContext,&local_13c);
      FUN_00426620(&DAT_006aa44c + iVar7,&local_158);
      FUN_00508d00(&g_uiPanelManager);
      return;
    }
    if (in_AX < 0xa101) {
      if (in_AX == 0xa100) {
        FUN_00402300(param_2);
        return;
      }
      if (in_AX == 0x1fff) {
        if (DAT_007934f4 != 0) {
          FUN_004059a0();
          return;
        }
      }
      else if (in_AX == 0xa001) {
        FUN_00405b20();
        SetGuardedBool(*(char *)((int)param_1 + 2) == '\x01');
        iVar7 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x3b96b) = *(undefined4 *)((int)param_1 + 3);
        *(undefined4 *)(iVar7 + 0x3b96f) = *(undefined4 *)((int)param_1 + 7);
        *(undefined4 *)(iVar7 + 0x3b973) = *(undefined4 *)((int)param_1 + 0xb);
        *(undefined4 *)(iVar7 + 0x3b977) = *(undefined4 *)((int)param_1 + 0xf);
        local_158 = *(uint *)((int)param_1 + 0x13);
        local_154 = *(uint *)((int)param_1 + 0x17);
        puVar4 = &local_158;
        local_150 = *(uint *)((int)param_1 + 0x1b);
        local_14c = 0;
        iVar7 = (iVar7 + 0x23330) - (int)puVar4;
        do {
          uVar5 = *puVar4;
          *(char *)((int)puVar4 + iVar7) = (char)uVar5;
          puVar4 = (uint *)((int)puVar4 + 1);
        } while ((char)uVar5 != '\0');
        local_124 = (uint)*(ushort *)((int)param_1 + 0x29);
        param_1 = (uint *)((int)param_1 + 0x2b);
        local_128 = 0;
        if (local_124 != 0) {
          do {
            /* _local_108: Ghidra's overlapping-symbol convention (same
             * idiom as _DAT_/DAT_ pairs, but for a local this time) - a
             * 4-byte view of the same stack slot as local_108[3]. */
            *(uint *)local_108 = *param_1;
            local_104 = param_1[1];
            local_100 = param_1[2];
            local_fc = param_1[3];
            local_f8 = param_1[4];
            local_f4 = 0;
            puVar4 = param_1 + 5;
            FUN_00401cb0();
            puVar8 = (undefined4 *)local_108;
            for (iVar7 = 0x20; iVar7 != 0; iVar7 = iVar7 + -1) {
              *puVar8 = 0xffffffff;
              puVar8 = puVar8 + 1;
            }
            param_1 = (uint *)((int)param_1 + 0x16);
            iVar7 = g_clientContext;
            for (uVar5 = (uint)(ushort)*puVar4; g_clientContext = iVar7, uVar5 != 0; uVar5 = uVar5 - 1)
            {
              local_13c = *param_1;
              local_138 = param_1[1];
              local_134 = param_1[2];
              local_158 = param_1[4];
              local_154 = param_1[5];
              local_150 = param_1[6];
              local_12c = 0;
              local_14c = 0;
              FUN_00426620(&DAT_006aa41c + iVar7,&local_13c);
              FUN_00426620(&DAT_006aa44c + iVar7,&local_158);
              local_144 = param_1[8];
              local_148 = param_1[7];
              local_140 = 0;
              if (((int)local_144 < 0) && (-1 < (char)(local_144 >> 0x10))) {
                local_144 = local_144 & 0xffffff;
              }
              puVar4 = param_1 + 9;
              param_1 = (uint *)((int)param_1 + 0x26);
              FUN_00401d50(&DAT_00e53e88,1,local_128,(short)*puVar4,local_108,&local_13c);
              iVar7 = g_clientContext;
            }
            local_128 = local_128 + 1;
          } while (local_128 < (int)local_124);
        }
        cVar3 = CheckGuardedBoolAnd(g_currentGameState == 2);
        iVar7 = DAT_007934f0;
        if ((cVar3 != '\0') && (*(char *)(DAT_007934f0 + 0x84e5) == '\x01')) {
          *(undefined4 *)(DAT_007934f0 + 0x44d0) = 6;
          *(undefined2 *)(iVar7 + 0x4d4) = 0x1100;
          *(undefined1 *)(iVar7 + 0x4d6) = 0;
          iVar1 = *(int *)(iVar7 + 0x44d0);
          *(int *)(iVar7 + 0x44d0) = iVar1 + 1;
          iVar2 = g_clientContext;
          *(undefined1 *)(iVar1 + 0x4d1 + iVar7) = 0;
          iVar1 = *(int *)(iVar7 + 0x44d0);
          *(int *)(iVar7 + 0x44d0) = iVar1 + 1;
          *(ushort *)(iVar1 + 0x4d1 + iVar7) = *(ushort *)(iVar2 + 0x3b96b) / 10;
          *(int *)(iVar7 + 0x44d0) = *(int *)(iVar7 + 0x44d0) + 2;
          SendOutgoingPacket();
          return;
        }
      }
    }
    else if (in_AX == 0xa101) {
      *(uint *)local_108 = *(uint *)local_108 & 0xffffff00;
      puVar8 = (undefined4 *)((int)local_108 + 1);
      for (iVar7 = 0x3f; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar8 = 0;
        puVar8 = puVar8 + 1;
      }
      *(undefined2 *)puVar8 = 0;
      param_2 = param_2 + -4;
      iVar7 = 0;
      *(undefined1 *)((int)puVar8 + 2) = 0;
      uVar6 = 4;
      if (0 < param_2) {
        param_1 = param_1 + 1;
        do {
          cVar3 = (char)*param_1;
          if (cVar3 == '\n') {
            (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))
                      (local_108,3,uVar6);
            uVar6 = 0;
            puVar8 = (undefined4 *)local_108;
            for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
              *puVar8 = 0;
              puVar8 = puVar8 + 1;
            }
            iVar7 = 0;
          }
          else if (cVar3 != '\r') {
            local_108[iVar7] = cVar3;
            iVar7 = iVar7 + 1;
          }
          param_1 = (uint *)((int)param_1 + 1);
          param_2 = param_2 + -1;
        } while (param_2 != 0);
      }
      (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_108,3,uVar6);
      return;
    }
  }
  else if (in_AX == 0xa2f0) {
    local_13c = *param_1;
    local_138 = param_1[1];
    local_134 = param_1[2];
    local_130 = param_1[3];
    local_158 = param_1[4];
    local_154 = param_1[5];
    local_150 = param_1[6];
    local_120 = param_1[7];
    local_11c = param_1[8];
    local_118 = param_1[9];
    local_114 = param_1[10];
    local_110 = (undefined2)param_1[0xb];
    local_148 = *(undefined4 *)((int)param_1 + 0x2e);
    local_144 = *(uint *)((int)param_1 + 0x32);
    local_12c = 0;
    local_14c = 0;
    local_10e = 0;
    local_140 = 0;
    if (((int)local_144 < 0) && (-1 < (char)(local_144 >> 0x10))) {
      local_144 = local_144 & 0xffffff;
    }
    puVar8 = (undefined4 *)local_108;
    for (iVar7 = 0x20; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar8 = 0xffffffff;
      puVar8 = puVar8 + 1;
    }
    uVar5 = (uint)*(ushort *)((int)param_1 + 0x36);
    puVar4 = &local_13c;
    puVar9 = local_108;
    uVar6 = FUN_00401ce0(&local_120);
    FUN_00401d50(&DAT_00e53e88,1,uVar6,uVar5,puVar9,puVar4);
    FUN_00401fa0();
  }
  else {
    if (in_AX == 0xa2f1) {
      local_13c = *param_1;
      local_138 = param_1[1];
      local_134 = param_1[2];
      local_130 = param_1[3];
      local_158 = param_1[4];
      local_150 = param_1[6];
      local_154 = param_1[5];
      local_12c = 0;
      local_14c = 0;
      FUN_00401ee0(&DAT_00e53e88);
      return;
    }
    if (in_AX == 0xa300) {
      local_13c = *param_1;
      local_138 = param_1[1];
      local_134 = param_1[2];
      local_130 = param_1[3];
      local_158 = param_1[4];
      local_154 = param_1[5];
      local_150 = param_1[6];
      local_12c = 0;
      local_14c = 0;
      FUN_00401fa0();
      return;
    }
  }
  return;
}

