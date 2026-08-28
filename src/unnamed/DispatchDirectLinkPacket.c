/* DispatchDirectLinkPacket - 0x004032c0 in the original binary.
 *
 * Dispatches one direct-link packet by its opcode word at packet+4 --
 * 0x1001 / 0x1002 / 0x1004 / 0x2005 and the small-numbered replies -- to the
 * per-opcode handlers, sending through g_directLinkConnection where a reply
 * is due.  param_1 is the packet (ECX), param_2/param_3 the two stack
 * arguments, regEax a 16-byte name record used as the key for case 0x1002.
 *
 * RE-SLOTTED AND EAX RECOVERED (2026-08-24).  `ret 8`: param_1 is ECX (the
 * packet: [esi+4] is the opcode dispatched on), param_2/param_3 the two
 * pushes, EAX (`mov edi,eax` at entry) a 16-byte name record copied into the
 * packet at +4..+0x10 and used as the key in case 0x1002.  Sole call site
 * 0x00403231 in FUN_00403170: ECX = &local_208 (the packet), EAX =
 * [ebp+0x10] = FUN_00403170's THIRD stack parameter -- which its source did
 * not declare although its `ret 0xc` and both of its callers
 * (FUN_00403000.c:44/68, three arguments) say it exists.  Now declared as
 * param_3 there.  The port had passed the packet's owner as the packet.
 */
#include "ghidra_types.h"


void __thiscall DispatchDirectLinkPacket(int param_1,int param_2,undefined4 param_3,undefined4 *regEax)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  byte bVar5;
  char *pcVar6;
  int iVar7;
  undefined1 local_12c [9];
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  char local_10c [264];
  undefined4 uStack_4;
  
  iVar4 = g_directLinkConnection;
  uVar2 = *(uint *)(param_1 + 4);
  if (uVar2 < 0x1005) {
    if (uVar2 == 0x1004) {
      iVar4 = FUN_00401bb0(param_2);
      if ((iVar4 != 0) &&
         (bVar5 = (*(char *)(param_1 + 8) != '1') - 1U & 0x12, *(byte *)(iVar4 + 0x30) = bVar5,
         bVar5 == 0x12)) {
        FUN_00404700(param_2);
        return;
      }
    }
    else if (uVar2 < 0x1001) {
      if (uVar2 == 0x1000) {
        pcVar6 = (char *)(param_1 + 8);
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        FUN_00402400(param_2,(char *)(param_1 + 8),(int)pcVar6 - (param_1 + 9));
        return;
      }
      if (uVar2 == 0) {
        if (g_directLinkConnection == 0) {
          if (*(int **)(param_2 + 0x1bdc) != (int *)0x0) {
            (**(code **)(**(int **)(param_2 + 0x1bdc) + 0x10))();
          }
          FUN_004024f0(param_2,param_1 + 8,param_3);
          return;
        }
        *(undefined4 *)(g_directLinkConnection + 0x2000) = 4;
        *(undefined2 *)(iVar4 + 2) = 0xa110;
        *(undefined4 *)(iVar4 + 4) = *regEax;
        *(undefined4 *)(iVar4 + 8) = regEax[1];
        *(undefined4 *)(iVar4 + 0xc) = regEax[2];
        *(undefined4 *)(iVar4 + 0x10) = regEax[3];
        *(int *)(iVar4 + 0x2000) = *(int *)(iVar4 + 0x2000) + 0x10;
        pcVar6 = (char *)(param_1 + 8);
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        FUN_004059e0((char *)(param_1 + 8));
        FUN_00405a20();
        FUN_004024f0(param_2,param_1 + 8,param_3);
        return;
      }
      if (uVar2 == 1) {
        if (g_directLinkConnection != 0) {
          *(undefined4 *)(g_directLinkConnection + 0x2000) = 4;
          *(undefined2 *)(iVar4 + 2) = 0xa200;
          *(undefined4 *)(iVar4 + 4) = *regEax;
          *(undefined4 *)(iVar4 + 8) = regEax[1];
          *(undefined4 *)(iVar4 + 0xc) = regEax[2];
          *(undefined4 *)(iVar4 + 0x10) = regEax[3];
          iVar7 = *(int *)(iVar4 + 0x2000) + 0x10;
          *(int *)(iVar4 + 0x2000) = iVar7;
          puVar3 = (undefined4 *)(iVar7 + iVar4);
          *puVar3 = 0;
          puVar3[1] = 0;
          puVar3[2] = 0;
          puVar3[3] = 0;
          puVar3[4] = 0;
          *(int *)(iVar4 + 0x2000) = *(int *)(iVar4 + 0x2000) + 0x14;
          FUN_00405a20();
          return;
        }
        if (*(int **)(param_2 + 0x1bdc) != (int *)0x0) {
          (**(code **)(**(int **)(param_2 + 0x1bdc) + 0x20))();
          pcVar6 = (char *)GetLocalizedString(&g_localizedStringTable,0xfa6);
          _sprintf(local_10c,pcVar6,uStack_4);
          BuildItemTooltipPanel(&g_uiPanelManager,local_10c);
          return;
        }
      }
      else if ((uVar2 == 2) && (g_directLinkConnection != 0)) {
        *(undefined4 *)(g_directLinkConnection + 0x2000) = 4;
        *(undefined2 *)(iVar4 + 2) = 0xa112;
        *(undefined4 *)(iVar4 + 4) = *regEax;
        *(undefined4 *)(iVar4 + 8) = regEax[1];
        *(undefined4 *)(iVar4 + 0xc) = regEax[2];
        *(undefined4 *)(iVar4 + 0x10) = regEax[3];
        *(int *)(iVar4 + 0x2000) = *(int *)(iVar4 + 0x2000) + 0x10;
        pcVar6 = (char *)(param_1 + 8);
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        FUN_004059e0((char *)(param_1 + 8));
        FUN_00405a20();
      }
    }
    else {
      if (uVar2 == 0x1001) {
        FUN_00401fa0();
        return;
      }
      if (uVar2 == 0x1002) {
        FUN_00401ee0(param_2,(char *)regEax); /* case 0x1002: the key is this function's own (still dropped) EAX */
        return;
      }
      if (uVar2 == 0x1003) {
        *(undefined4 *)local_12c = *(undefined4 *)(param_1 + 8);
        *(undefined4 *)(local_12c + 4) = *(undefined4 *)(param_1 + 0xc);
        local_12c[8] = 0;
        if (((int)*(uint *)(local_12c + 4) < 0) &&
           (-1 < (char)(*(uint *)(local_12c + 4) >> 0x10))) {
          local_12c[7] = 0;
        }
        local_118 = 0xffffffff;
        local_114 = 0xffffffff;
        local_110 = 0xffffffff;
        local_10c[0] = -1;
        local_10c[1] = -1;
        local_10c[2] = -1;
        local_10c[3] = -1;
        local_10c[4] = -1;
        local_10c[5] = -1;
        local_10c[6] = -1;
        local_10c[7] = -1;
        local_10c[8] = -1;
        local_10c[9] = -1;
        local_10c[10] = -1;
        local_10c[0xb] = -1;
        FUN_00401d50((char *)local_12c,param_2,1,0,*(undefined2 *)(param_1 + 0x10),&local_118,
                     (char *)param_3,(char *)regEax);
        return;
      }
    }
  }
  else {
    switch(uVar2) {
    case 0x2000:
      FUN_00508d00(&g_uiPanelManager);
      return;
    case 0x2001:
      pcVar6 = (char *)GetLocalizedString(&g_localizedStringTable,0xfa3 - (uint)(*(char *)(param_1 + 8) != '\0'));
      _sprintf(local_10c + 0xc,pcVar6);
      BuildItemTooltipPanel(&g_uiPanelManager,local_10c + 0xc);
      return;
    case 0x2002:
      if (g_directLinkConnection != 0) {
        *(undefined4 *)(g_directLinkConnection + 0x2000) = 4;
        *(undefined2 *)(iVar4 + 2) = 0xa251;
        *(undefined4 *)(iVar4 + 4) = *regEax;
        *(undefined4 *)(iVar4 + 8) = regEax[1];
        *(undefined4 *)(iVar4 + 0xc) = regEax[2];
        *(undefined4 *)(iVar4 + 0x10) = regEax[3];
        iVar7 = *(int *)(iVar4 + 0x2000) + 0x10;
        *(int *)(iVar4 + 0x2000) = iVar7;
        *(undefined1 *)(iVar7 + iVar4) = 1;
LAB_0040377c:
        *(int *)(iVar4 + 0x2000) = *(int *)(iVar4 + 0x2000) + 1;
        FUN_00405a20();
        return;
      }
      if (*(int **)(param_2 + 0x1bdc) != (int *)0x0) {
        (**(code **)(**(int **)(param_2 + 0x1bdc) + 0x24))();
        return;
      }
      break;
    case 0x2003:
      if (g_directLinkConnection != 0) {
        *(undefined4 *)(g_directLinkConnection + 0x2000) = 4;
        *(undefined2 *)(iVar4 + 2) = 0xa251;
        *(undefined4 *)(iVar4 + 4) = *regEax;
        *(undefined4 *)(iVar4 + 8) = regEax[1];
        *(undefined4 *)(iVar4 + 0xc) = regEax[2];
        *(undefined4 *)(iVar4 + 0x10) = regEax[3];
        iVar7 = *(int *)(iVar4 + 0x2000) + 0x10;
        *(int *)(iVar4 + 0x2000) = iVar7;
        *(undefined1 *)(iVar7 + iVar4) = 0;
        goto LAB_0040377c;
      }
      if (*(int **)(param_2 + 0x1bdc) != (int *)0x0) {
        (**(code **)(**(int **)(param_2 + 0x1bdc) + 0x24))();
        return;
      }
      break;
    case 0x2004:
      if (g_directLinkConnection == 0) {
        if (*(int **)(param_2 + 0x1bdc) != (int *)0x0) {
          (**(code **)(**(int **)(param_2 + 0x1bdc) + 0x28))();
        }
        FUN_00401ee0(param_2,(char *)param_3 + 1);
        return;
      }
      *(undefined4 *)(g_directLinkConnection + 0x2000) = 4;
      *(undefined2 *)(iVar4 + 2) = 0xa210;
      *(undefined4 *)(iVar4 + 4) = *regEax;
      *(undefined4 *)(iVar4 + 8) = regEax[1];
      *(undefined4 *)(iVar4 + 0xc) = regEax[2];
      *(undefined4 *)(iVar4 + 0x10) = regEax[3];
      *(int *)(iVar4 + 0x2000) = *(int *)(iVar4 + 0x2000) + 0x10;
      FUN_00405a20();
      FUN_00401ee0(param_2,(char *)param_3 + 1);
      return;
    case 0x2005:
      if (*(int **)(param_2 + 0x1bdc) != (int *)0x0) {
        (**(code **)(**(int **)(param_2 + 0x1bdc) + 0x18))();
        return;
      }
    }
  }
  return;
}

