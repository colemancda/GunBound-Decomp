/* FUN_0050be20 - 0x0050be20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0050be20(int param_1,int param_2,int param_3)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffff64;
  undefined stack0xffffff6c;
  undefined stack0xffffff70;
  int iVar1;
  int iVar2;
  int unaff_EBX;
  int unaff_EBP;
  int unaff_ESI;
  uint uVar3;
  uint uVar4;
  code *pcVar5;
  int unaff_EDI;
  int unaff_retaddr;
  undefined *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  int local_8c;
  int local_88;
  undefined *local_84;
  char local_80 [108];
  int iStack_14;
  int iStack_10;
  int iStack_c;
  int iStack_8;
  int iStack_4;
  
  local_84 = g_gameStateVTableArray[7];
  if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp(param_2,param_3);
    }
    else {
      BlitSpriteClipped(1);
    }
  }
  local_88 = 0;
LAB_0050be92:
  iVar1 = *(int *)(param_1 + 0x94);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar2 == iVar1) && (DAT_0079352c != 0)) {
    iVar1 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar3 = *(uint *)(iVar1 + 4);
    while (uVar3 < 0x2714) {
      if (uVar3 == 0x2713) {
        iVar1 = *(int *)(iVar1 + 0x10);
        uVar3 = *(uint *)(iVar1 + 8);
        if (uVar3 < 8) goto LAB_0050bf1b;
        break;
      }
      iVar1 = *(int *)(iVar1 + 0x1c);
      uVar3 = *(uint *)(iVar1 + 4);
    }
  }
  goto LAB_0050bf63;
  while( true ) {
    iVar1 = *(int *)(iVar1 + 0x10);
    uVar3 = *(uint *)(iVar1 + 8);
    if (7 < uVar3) break;
LAB_0050bf1b:
    if (uVar3 == 7) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(param_2,param_3 + 4);
      }
      else {
        BlitSpriteClipped(7);
      }
      break;
    }
  }
LAB_0050bf63:
  local_88 = local_88 + 0x224;
  if (0x88f < local_88) goto code_r0x0050bf7b;
  goto LAB_0050be92;
code_r0x0050bf7b:
  if (*(uint *)(g_clientContext + 0x44e24) <= *(uint *)(param_1 + 0x94)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = iVar1 >> 0x10 & 0xf;
  uVar4 = uVar3 * 2;
  if (uVar3 != 3) {
    if (*(uint *)(g_clientContext + 0x44e24) <= *(uint *)(param_1 + 0x94)) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((uVar3 & 0x8000) == 0) {
      uVar4 = uVar4 + 1;
    }
  }
  if (DAT_0079352c != 0) {
    iVar1 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar3 = *(uint *)(iVar1 + 4);
    while (uVar3 < 0x2714) {
      if (uVar3 == 0x2713) {
        iVar1 = *(int *)(iVar1 + 0x10);
        uVar3 = *(uint *)(iVar1 + 8);
        if (uVar3 <= uVar4) goto LAB_0050c076;
        break;
      }
      iVar1 = *(int *)(iVar1 + 0x1c);
      uVar3 = *(uint *)(iVar1 + 4);
    }
  }
  goto LAB_0050c0b2;
  while( true ) {
    iVar1 = *(int *)(iVar1 + 0x10);
    uVar3 = *(uint *)(iVar1 + 8);
    if (uVar4 < uVar3) break;
LAB_0050c076:
    if (uVar3 == uVar4) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp(param_2 + 6,param_3 + 2);
      }
      else {
        BlitSpriteClipped(uVar4);
      }
      break;
    }
  }
LAB_0050c0b2:
  if (*(uint *)(param_1 + 0x94) < *(uint *)(g_clientContext + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    BlitRLESprite(0,param_3 + 3,(-(uint)((uVar3 & 0x20000000) != 0x20000000) & 0x480d) + 0xb7f2,(byte *)0);
    local_8c = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar1 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar1 < 1) {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp(param_2 + 0x99,param_3 + 2);
          }
          else {
            BlitSpriteClipped(9);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp(param_2 + 0x99,param_3 + 2);
          }
          else {
            BlitSpriteClipped(8);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(local_80,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,local_80,2,6);
      local_8c = 1;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    pcVar5 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar1 != 0) && (local_8c < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_88 = local_8c * 0x19 + param_2;
      if (iVar1 < 0) {
        iVar1 = local_88 + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1,param_3 + 2);
          }
          else {
            BlitSpriteClipped(10);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        iVar1 = local_88 + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1,param_3 + 2);
          }
          else {
            BlitSpriteClipped(0xb);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(local_80,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,local_80,2,6);
      local_8c = local_8c + -1;
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    puVar8 = &DAT_005a9068;
    (*pcVar5)();
    if ((iVar1 != 0) && (unaff_EBX < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      (*pcVar5)(&DAT_005a9068);
      local_8c = unaff_EBX * 0x19 + param_1;
      if (iVar1 < 0) {
        iVar1 = local_8c + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1,param_2 + 2);
          }
          else {
            BlitSpriteClipped(0xc);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        iVar1 = local_8c + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1,param_2 + 2);
          }
          else {
            BlitSpriteClipped(0xd);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_84,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&local_84,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    puVar7 = &DAT_005a9068;
    (*pcVar5)();
    if ((iVar1 != 0) && (unaff_EBP < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar5)(&DAT_005a9068);
      iVar1 = unaff_EBP * 0x19 + unaff_retaddr;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,param_1 + 2);
          }
          else {
            BlitSpriteClipped(0xe);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,param_1 + 2);
          }
          else {
            BlitSpriteClipped(0xf);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_88,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&local_88,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    puVar6 = &DAT_005a9068;
    (*pcVar5)(&DAT_005a9068);
    if ((iVar1 != 0) && (unaff_ESI < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar5)(&DAT_005a9068);
      iVar1 = unaff_ESI * 0x19 + iStack_4;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,unaff_retaddr + 2);
          }
          else {
            BlitSpriteClipped(0x10);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,unaff_retaddr + 2);
          }
          else {
            BlitSpriteClipped(0x11);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_8c,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&local_8c,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    (*pcVar5)(&DAT_005a9068);
    if ((iVar1 != 0) && (unaff_EDI < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar5)(&DAT_005a9068);
      iVar1 = unaff_EDI * 0x19 + iStack_8;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_4 + 2);
          }
          else {
            BlitSpriteClipped(0x12);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_4 + 2);
          }
          else {
            BlitSpriteClipped(0x13);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(&stack0xffffff70,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&stack0xffffff70,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    (*pcVar5)(&DAT_005a9068);
    if ((iVar1 != 0) && ((int)puVar8 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar5)(&DAT_005a9068);
      iVar1 = (int)puVar8 * 0x19 + iStack_c;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_8 + 2);
          }
          else {
            BlitSpriteClipped(0x14);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_8 + 2);
          }
          else {
            BlitSpriteClipped(0x15);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(&stack0xffffff6c,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&stack0xffffff6c,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    (*pcVar5)(&DAT_005a9068);
    if ((iVar1 != 0) && ((int)puVar7 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar5)(&DAT_005a9068);
      iVar1 = (int)puVar6 * 0x19 + iStack_14;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_10 + 2);
          }
          else {
            BlitSpriteClipped(0x16);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_10 + 2);
          }
          else {
            BlitSpriteClipped(0x17);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(&stack0xffffff64,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&stack0xffffff64,2,6);
    }
    return;
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

