/* FUN_004d9ae0 - 0x004d9ae0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004d9ae0(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char cVar6;
  int iVar7;
  int *piVar8;
  bool bVar9;
  int iStack_8c;
  int iStack_88;
  CHAR aCStack_80 [128];
  
  if (*(int *)(param_1 + 0x4d4) != -1) {
    uVar2 = *(int *)(param_1 + 0x4d4) / 10 & 0x80000001;
    bVar9 = uVar2 == 0;
    if ((int)uVar2 < 0) {
      bVar9 = (uVar2 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if (((bVar9) && (DAT_0079352c != 0)) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x23b,0x1e5);
      }
      else {
        BlitSpriteClipped(9);
      }
    }
  }
  if (*(int *)(param_1 + 0x6b0) != -1) {
    uVar2 = *(int *)(param_1 + 0x6b0) / 10 & 0x80000001;
    bVar9 = uVar2 == 0;
    if ((int)uVar2 < 0) {
      bVar9 = (uVar2 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if (((bVar9) && (DAT_0079352c != 0)) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x23b,0x1e5);
      }
      else {
        BlitSpriteClipped(9);
      }
    }
  }
  if (g_bBattleSessionActive == '\0') goto LAB_004da2f4;
  FUN_004eadb0();
  if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
    if (*(char *)(iVar3 + 0x18) == '\x01') {
      BlitSprite16bpp(0,0x164);
    }
    else {
      BlitSpriteClipped(0);
    }
  }
  FUN_004eadb0();
  if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
    if (*(char *)(iVar3 + 0x18) == '\x01') {
      BlitSprite16bpp(0x261,0x16d);
    }
    else {
      BlitSpriteClipped(1);
    }
  }
  FUN_004eadb0();
  if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
    if (*(char *)(iVar3 + 0x18) == '\x01') {
      BlitSprite16bpp(0x1a,0x17f);
    }
    else {
      BlitSpriteClipped(0);
    }
  }
  if (2 < *(int *)(param_1 + 0x740)) {
    iStack_8c = 0;
    iStack_88 = 0;
    piVar8 = (int *)(param_1 + 0x768);
    iVar3 = g_clientContext;
    do {
      if ((*(char *)(iVar3 + 0x45914 + iStack_8c) != '\0') &&
         (cVar6 = *(char *)(iVar3 + 0x4590c + iStack_8c), cVar6 != -1)) {
        cVar6 = (cVar6 != *(char *)(iVar3 + 0x3b6c0)) + '\x02';
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar3 == iStack_8c) {
          uVar2 = *(int *)(param_1 + 0x740) / 10 & 0x80000001;
          bVar9 = uVar2 == 0;
          if ((int)uVar2 < 0) {
            bVar9 = (uVar2 - 1 | 0xfffffffe) == 0xffffffff;
          }
          if (bVar9) {
            cVar6 = '\x04';
          }
        }
        iVar3 = *piVar8;
        iVar7 = piVar8[-8];
        if ((DAT_0079352c != 0) && (iVar4 = FindSpriteFrame(), iVar4 != 0)) {
          if (*(char *)(iVar4 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar7 + 0x1a,iVar3 + 2);
          }
          else {
            BlitSpriteClipped(cVar6);
          }
        }
        iVar3 = g_clientContext;
        pcVar5 = (char *)(iStack_88 + 0x457f1 + g_clientContext);
        do {
          cVar6 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar6 != '\0');
        FUN_004eb510(*piVar8 + 5,
                     -(uint)(*(char *)(g_clientContext + 0x4590c + iStack_8c) !=
                            *(char *)(g_clientContext + 0x3b6c0)) & 0xfae8);
        BlitRLESprite(*piVar8 + 5,0xffff);
      }
      iStack_88 = iStack_88 + 0xd;
      iStack_8c = iStack_8c + 1;
      piVar8 = piVar8 + 1;
    } while (iStack_88 < 0x68);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = iVar3 + 7;
  if ((DAT_0079352c != 0) && (-1 < (int)uVar2)) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar1 = *(uint *)(iVar3 + 4);
    while (uVar1 < 0x2718) {
      if (uVar1 == 0x2717) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar1 = *(uint *)(iVar3 + 8);
        if (uVar1 <= uVar2) goto LAB_004d9f58;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
    }
  }
  goto LAB_004d9f98;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar1 = *(uint *)(iVar7 + 8);
    if (uVar2 < uVar1) break;
LAB_004d9fe8:
    if (uVar1 == uVar2) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x193,0xe1);
      }
      else {
        BlitSpriteClipped(uVar2);
      }
      break;
    }
  }
  goto LAB_004da028;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar1 = *(uint *)(iVar7 + 8);
    if (uVar2 < uVar1) break;
LAB_004da070:
    if (uVar1 == uVar2) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(0x13d,0x11d);
      }
      else {
        BlitSpriteClipped(uVar2);
      }
      break;
    }
  }
  goto LAB_004da0b0;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar1 = *(uint *)(iVar3 + 8);
    if (uVar2 < uVar1) break;
LAB_004da0f8:
    if (uVar1 == uVar2) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x193,0xff);
      }
      else {
        BlitSpriteClipped(uVar2);
      }
      break;
    }
  }
  goto LAB_004da138;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar1 = *(uint *)(iVar3 + 8);
    if (uVar2 < uVar1) break;
LAB_004da1a2:
    if (uVar1 == uVar2) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x193,0x11d);
      }
      else {
        BlitSpriteClipped(uVar2);
      }
      break;
    }
  }
  goto LAB_004da1e2;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar1 = *(uint *)(iVar3 + 8);
    if (uVar2 < uVar1) break;
LAB_004da246:
    if (uVar1 == uVar2) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x13d,0xff);
      }
      else {
        BlitSpriteClipped(uVar2);
      }
      break;
    }
  }
  goto LAB_004da286;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar1 = *(uint *)(iVar3 + 8);
    if (uVar2 < uVar1) break;
LAB_004d9f58:
    if (uVar1 == uVar2) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x13d,0xe1);
      }
      else {
        BlitSpriteClipped(uVar2);
      }
      break;
    }
  }
LAB_004d9f98:
  iVar3 = g_clientContext;
  uVar2 = (*(byte *)(g_clientContext + 0x45124) >> 1) + 0x16;
  if (DAT_0079352c != 0) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar1 = *(uint *)(iVar7 + 4);
    while (uVar1 < 0x2718) {
      if (uVar1 == 0x2717) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar1 = *(uint *)(iVar7 + 8);
        if (uVar1 <= uVar2) goto LAB_004d9fe8;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar1 = *(uint *)(iVar7 + 4);
    }
  }
LAB_004da028:
  uVar2 = *(byte *)(iVar3 + 0x45126) + 0xd;
  if (DAT_0079352c != 0) {
    iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar1 = *(uint *)(iVar7 + 4);
    while (uVar1 < 0x2718) {
      if (uVar1 == 0x2717) {
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar1 = *(uint *)(iVar7 + 8);
        if (uVar1 <= uVar2) goto LAB_004da070;
        break;
      }
      iVar7 = *(int *)(iVar7 + 0x1c);
      uVar1 = *(uint *)(iVar7 + 4);
    }
  }
LAB_004da0b0:
  uVar2 = *(byte *)(iVar3 + 0x45127) + 0x10;
  if (DAT_0079352c != 0) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar1 = *(uint *)(iVar3 + 4);
    while (uVar1 < 0x2718) {
      if (uVar1 == 0x2717) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar1 = *(uint *)(iVar3 + 8);
        if (uVar1 <= uVar2) goto LAB_004da0f8;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
    }
  }
LAB_004da138:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = ((int)(iVar3 + -0x28 + (iVar3 + -0x28 >> 0x1f & 0xfU)) >> 4) + 0x14;
  if ((DAT_0079352c != 0) && (-1 < (int)uVar2)) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar1 = *(uint *)(iVar3 + 4);
    while (uVar1 < 0x2718) {
      if (uVar1 == 0x2717) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar1 = *(uint *)(iVar3 + 8);
        if (uVar1 <= uVar2) goto LAB_004da1a2;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
    }
  }
LAB_004da1e2:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = iVar3 + 0x1b;
  if ((DAT_0079352c != 0) && (-1 < (int)uVar2)) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar1 = *(uint *)(iVar3 + 4);
    while (uVar1 < 0x2718) {
      if (uVar1 == 0x2717) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar1 = *(uint *)(iVar3 + 8);
        if (uVar1 <= uVar2) goto LAB_004da246;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
    }
  }
LAB_004da286:
  if ((((*(short *)(&DAT_006aa660 + g_clientContext) != -1) && (*(int *)(param_1 + 0x740) % 0x14 < 10))
      && (DAT_0079352c != 0)) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
    if (*(char *)(iVar3 + 0x18) == '\x01') {
      BlitSprite16bpp(0,0x164);
    }
    else {
      BlitSpriteClipped(0);
    }
  }
LAB_004da2f4:
  if (DAT_007933b8 == '\x01') {
    FUN_0040c8f0(0xca,0x21b,0);
    if ((*(char *)(DAT_007934e4 + 8) == '\0') ||
       (iVar3 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),aCStack_80,0x80), iVar3 == 0)) {
      aCStack_80[0] = '\0';
    }
    if (iStack_88 == -1) {
      pcVar5 = aCStack_80;
      do {
        cVar6 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar6 != '\0');
    }
    if (iStack_8c == -1) {
      pcVar5 = aCStack_80;
      do {
        cVar6 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar6 != '\0');
    }
    FUN_004eb5d0(0xf800);
    FUN_004eb5d0(0xf800);
    FUN_004eb6b0();
    FUN_004eb6b0();
    BlitRLESprite(0x170,0);
    BlitRLESprite(0x16f,0xffe0);
  }
  else {
    BlitRLESprite(0x16f,0xffff);
  }
  FUN_00450860();
  return;
}

