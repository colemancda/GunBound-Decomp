/* RenderWorldListRow - 0x0050dc80 in the original binary.
 *
 * Draws one server ("world") row of the WORLD LIST, given the row index in a
 * register. Called once per server by the panel's render slot (0x50dc40),
 * which loops the server count at g_clientContext+0x3f808. Layout is a
 * 2-column grid: x = (i%2)*0xf7 + 0x16 + panelX, y = (i/2)*0x49 + 0x2d +
 * panelY. Draws: a row-background sprite whose state reflects selection
 * (state 3 when i == g_gameStateVTableArray[2]+8, the highlighted slot; state
 * 2 when i == +0xc); the server number (sprintf serverId+1, via BlitRLESprite
 * white); the name + two description lines (BlitRLESprite, colour 0xb77f); and
 * a population gauge (currentPlayers*100/maxCapacity bucketed via thresholds at
 * g_fullnessGaugeThresholds -> gauge sprite, the F/E dial). Reads the SoA
 * (serverId +0x3f81a, onlineFlag +0x3f809, players +0x410ca, capacity +0x410ea).
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall RenderWorldListRow(int param_1)

{
  int iVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  uint in_EAX;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  int local_84;
  char local_80 [128];
  
  uVar5 = in_EAX & 0x80000001;
  if ((int)uVar5 < 0) {
    uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
  }
  iVar1 = uVar5 * 0xf7 + 0x16 + *(int *)(param_1 + 0x28);
  iVar2 = ((int)in_EAX / 2) * 0x49 + 0x2d + *(int *)(param_1 + 0x2c);
  cVar8 = (-(*(char *)(g_clientContext + 0x3f809 + in_EAX) != '\x01') & 3U) + 1;
  if (*(uint *)(g_gameStateVTableArray[2] + 0xc) == in_EAX) {
    cVar8 = '\x02';
  }
  if (*(uint *)(g_gameStateVTableArray[2] + 8) == in_EAX) {
    cVar8 = '\x03';
  }
  if ((DAT_0079352c != 0) && (iVar6 = FUN_004f30c0(), iVar6 != 0)) {
    if (*(char *)(iVar6 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar1,iVar2);
    }
    else {
      BlitSpriteClipped(cVar8);
    }
  }
  _sprintf(local_80,&DAT_00551ed4,*(ushort *)(g_clientContext + 0x3f81a + in_EAX * 2) + 1);
  pcVar7 = local_80;
  do {
    cVar3 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar3 != '\0');
  FUN_004ed9f0(0xf8,local_80,(int)pcVar7 - (int)(local_80 + 1),8);
  pcVar7 = local_80;
  do {
    cVar3 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar3 != '\0');
  FUN_004eb510(iVar2 + 9,0);
  pcVar7 = local_80;
  do {
    cVar3 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar3 != '\0');
  BlitRLESprite(iVar2 + 9,0xffff);
  iVar6 = iVar2 + 0x1e;
  local_84 = 2;
  do {
    BlitRLESprite(iVar6,0xb77f);
    iVar6 = iVar6 + 0xe;
    local_84 = local_84 + -1;
  } while (local_84 != 0);
  iVar6 = 5;
  if (cVar8 == '\x04') {
    iVar6 = 6;
  }
  iVar10 = iVar6;
  if (*(char *)(g_clientContext + 0x3f809 + in_EAX) == '\x01') {
    iVar9 = 0;
    do {
      iVar10 = iVar9;
      if ((int)((ulonglong)((uint)*(ushort *)(g_clientContext + 0x410ca + in_EAX * 2) * 100) /
               (ulonglong)(longlong)(int)(uint)*(ushort *)(g_clientContext + 0x410ea + in_EAX * 2)) <
          (int)g_fullnessGaugeThresholds[iVar9]) break;
      iVar9 = iVar9 + 1;
      iVar10 = iVar6;
    } while (iVar9 < 5);
  }
  uVar5 = iVar10 + 5;
  if ((DAT_0079352c != 0) && (-1 < (int)uVar5)) {
    iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar4 = *(uint *)(iVar6 + 4);
    if (uVar4 < 0x2712) {
      while (uVar4 != 0x2711) {
        iVar6 = *(int *)(iVar6 + 0x1c);
        uVar4 = *(uint *)(iVar6 + 4);
        if (0x2711 < uVar4) {
          return;
        }
      }
      iVar6 = *(int *)(iVar6 + 0x10);
      uVar4 = *(uint *)(iVar6 + 8);
      if (uVar4 <= uVar5) {
        while (uVar4 != uVar5) {
          iVar6 = *(int *)(iVar6 + 0x10);
          uVar4 = *(uint *)(iVar6 + 8);
          if (uVar5 < uVar4) {
            return;
          }
        }
        if (*(char *)(iVar6 + 0x18) == '\x01') {
          BlitSprite16bpp(iVar1 + 0xb5,iVar2);
          return;
        }
        BlitSpriteClipped(uVar5);
      }
    }
  }
  return;
}

