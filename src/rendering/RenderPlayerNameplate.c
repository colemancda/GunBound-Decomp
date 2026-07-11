/* RenderPlayerNameplate - 0x004dba80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void RenderPlayerNameplate(int param_1)

{
  char *pcVar1;
  int iVar2;
  int in_EAX;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int local_c0 [16];
  char local_80 [128];
  
  iVar4 = g_clientContext;
  iVar5 = (int)*(char *)(in_EAX + 0x4a0 + param_1);
  local_c0[0] = 0x26;
  local_c0[1] = 0xb1;
  local_c0[3] = 0xb1;
  local_c0[2] = 0x26;
  local_c0[5] = 0x27b;
  local_c0[7] = 0x27b;
  local_c0[4] = 0x1f0;
  local_c0[6] = 0x1f0;
  local_c0[8] = 0x8d;
  local_c0[9] = 0x8d;
  local_c0[10] = 0x125;
  local_c0[0xb] = 0x125;
  local_c0[0xc] = 0x8d;
  local_c0[0xd] = 0x8d;
  iVar2 = local_c0[iVar5];
  local_c0[0xe] = 0x125;
  local_c0[0xf] = 0x125;
  iVar5 = local_c0[iVar5 + 8];
  *(int *)(in_EAX + 0x6bc + param_1 * 8) = iVar2 + 0x43;
  *(int *)(in_EAX + 0x6c0 + param_1 * 8) = iVar5 + 0xe;
  iVar3 = 0;
  piVar6 = (int *)(iVar4 + 0x4737c);
  do {
    if (*piVar6 == param_1) goto LAB_004dbb40;
    iVar3 = iVar3 + 1;
    piVar6 = piVar6 + 1;
  } while (iVar3 < 8);
  iVar3 = -1;
LAB_004dbb40:
  if (iVar3 < (int)(uint)*(byte *)(iVar4 + 0x45124)) {
    if (*(char *)(iVar4 + 0x45914 + param_1) == '\0') {
      FUN_004eb890();
      return;
    }
    FUN_004eb890();
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (param_1 == iVar4) {
      if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
        if (*(char *)(iVar4 + 0x18) == '\x01') {
          BlitSprite16bpp(iVar2 + 99,iVar5 + 0x20);
        }
        else {
          BlitSpriteClipped(7);
        }
      }
    }
    FUN_004eb890();
    pcVar1 = (char *)(g_clientContext + param_1 * 9 + 0x457a9);
    if (*pcVar1 != '\0') {
      _sprintf(local_80,s__s__3d__3d__005536b8,pcVar1,
               *(undefined4 *)(g_clientContext + 0x4597c + param_1 * 4),
               *(undefined4 *)(g_clientContext + 0x4599c + param_1 * 4));
      BlitRLESprite(iVar5 + 0x13,0xf800);
    }
    iVar4 = g_clientContext;
    BlitRLESprite(iVar5 + 0x21,0);
    if ((g_bBattleSessionActive == '\0') && (*(char *)(iVar4 + 0x45914 + param_1) == '\x04')) {
      if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
        if (*(char *)(iVar4 + 0x18) != '\x01') {
          BlitSpriteClipped(6);
          return;
        }
        BlitSprite16bpp(iVar2 + 0x69,iVar5 + -0x1e);
        return;
      }
    }
    else {
      FUN_004eb890();
    }
  }
  return;
}

