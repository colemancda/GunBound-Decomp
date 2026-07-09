/* RenderReadyRoomChatRow - 0x0050d200 in the original binary.
 *
 * Row renderer (vtable slot 9) for the Ready Room chat-log panel: draws each message with a per-row icon (+0x3f73c) and a message-type byte (+0x3c4d8) that selects one of several RGB565 text colors (white/gray/yellow/red/...) - the same color-coded-chat idiom as the in-battle chat renderer. Indexed via +0x3b97c off g_clientContext. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall RenderReadyRoomChatRow(int param_1)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int local_1c;
  undefined4 local_14;
  int local_10;
  
  if (*(char *)(param_1 + 0x1e) == '\0') {
    FUN_005054b0();
    iVar7 = *(int *)(param_1 + 0x2c) + 0x14;
    local_10 = 0;
    iVar8 = param_1;
    do {
      local_14 = 0x1f;
      iVar10 = (((int)*(uint *)(g_clientContext + 0x3b97c) < 1) - 1 & *(uint *)(g_clientContext + 0x3b97c)
               ) + local_10;
      uVar3 = *(ushort *)(g_clientContext + 0x3f73c + iVar10 * 2);
      if (uVar3 != 0) {
        iVar4 = *(int *)(param_1 + 0x28);
        iVar9 = uVar3 - 1;
        if (((DAT_0079352c != 0) && (-1 < iVar9)) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
          if (*(char *)(iVar5 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x1a,iVar7);
          }
          else {
            BlitSpriteClipped(iVar9);
          }
        }
      }
      switch(*(undefined1 *)(g_clientContext + 0x3c4d8 + iVar10)) {
      case 0:
        iVar8 = 0xffff;
        local_1c = 0xffff;
        local_14 = 0x1f;
        break;
      case 1:
        iVar8 = 0xc618;
        goto LAB_0050d3e9;
      case 2:
        iVar8 = 0;
        local_1c = 0xffe0;
        break;
      case 3:
        iVar8 = 0xf800;
        goto LAB_0050d3e9;
      case 4:
        local_1c = 0xafff;
        iVar8 = 0xf0;
        break;
      case 5:
        iVar8 = 0;
        local_1c = 0xc7f8;
        break;
      case 6:
      case 8:
        iVar8 = 0x8000;
        local_1c = 0xf800;
        break;
      case 7:
        local_1c = 0x78e0;
        iVar8 = 0xfdb4;
        local_14 = 0;
        break;
      case 9:
        iVar8 = 0x400;
        local_1c = 0xfff2;
        break;
      case 10:
        local_1c = 0xf800;
        iVar8 = 0xfebf;
        break;
      case 0xb:
        local_1c = 0xfc20;
        iVar8 = 0x4880;
        break;
      case 0xc:
        local_1c = 0x7e0;
        iVar8 = 0x210a;
        break;
      case 0xd:
        local_1c = 0x1f;
        iVar8 = 0xf6bf;
        break;
      case 0xe:
        local_1c = 0xc018;
        iVar8 = 0xfecf;
        break;
      case 0xf:
        local_1c = 0;
        iVar8 = 0xffff;
        break;
      case 0x10:
        iVar8 = 0;
LAB_0050d3e9:
        local_1c = 0xffff;
      }
      pcVar6 = (char *)(iVar10 * 9 + 0x3b984 + g_clientContext);
      FUN_004eb510(iVar7,local_14);
      BlitRLESprite(iVar7,iVar8);
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      bVar2 = *(byte *)(g_clientContext + 0x3c4d8 + iVar10);
      if ((bVar2 < 2) || (bVar2 == 7)) {
        pcVar6 = (char *)(g_clientContext + (iVar10 * 5 + 0xef42) * 4);
        BlitRLESprite(iVar7,0);
        BlitRLESprite(iVar7,iVar8);
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        BlitRLESprite(iVar7,0);
        iVar10 = iVar8;
      }
      else {
        pcVar6 = (char *)(g_clientContext + (iVar10 * 5 + 0xef42) * 4);
        FUN_004eb510(iVar7,iVar8);
        BlitRLESprite(iVar7,local_1c);
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        FUN_004eb510(iVar7,iVar8);
        iVar10 = local_1c;
      }
      BlitRLESprite(iVar7,iVar10);
      iVar7 = iVar7 + 0xe;
      local_10 = local_10 + 1;
    } while (local_10 < 9);
  }
  return;
}

