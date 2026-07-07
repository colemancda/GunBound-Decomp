/* FUN_0050ae40 - 0x0050ae40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0050ae40(int param_1)

{
  undefined *puVar1;
  char extraout_AH;
  int in_EAX;
  int iVar2;
  undefined *puVar3;
  int unaff_EBX;
  int iVar4;
  int unaff_EBP;
  int unaff_ESI;
  uint uVar5;
  uint uVar6;
  code *pcVar7;
  undefined *unaff_EDI;
  undefined *puVar8;
  undefined *puVar9;
  undefined *local_94;
  int local_90;
  undefined *local_8c;
  int local_88;
  undefined *local_84;
  char local_80 [128];
  
  local_94 = (undefined *)(*(int *)(in_EAX + 0x2c) + 0x68 + param_1 * 0x11);
  iVar4 = *(int *)(in_EAX + 0x28) + 0x13;
  local_84 = g_gameStateVTableArray[7];
  local_88 = iVar4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (((param_1 == iVar2) && (DAT_0079352c != 0)) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
    if (*(char *)(iVar2 + 0x18) == '\x01') {
      BlitSprite16bpp(iVar4,local_94);
    }
    else {
      BlitSpriteClipped(1);
    }
  }
  if (*(uint *)(DAT_005b3484 + 0x44e24) <= (uint)(*(int *)(local_84 + 0x454) + param_1)) {
    return;
  }
  local_90 = 0;
LAB_0050af10:
  iVar2 = *(int *)(local_84 + 0x454);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar4 == iVar2 + param_1) && (DAT_0079352c != 0)) {
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar5 = *(uint *)(iVar2 + 4);
    while (uVar5 < 0x2714) {
      if (uVar5 == 0x2713) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar5 = *(uint *)(iVar2 + 8);
        if (uVar5 < 8) goto LAB_0050af95;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar5 = *(uint *)(iVar2 + 4);
    }
  }
  goto LAB_0050afd2;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar5 = *(uint *)(iVar2 + 8);
    if (7 < uVar5) break;
LAB_0050af95:
    if (uVar5 == 7) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(local_88,local_94 + 4);
      }
      else {
        BlitSpriteClipped(7);
      }
      break;
    }
  }
LAB_0050afd2:
  puVar3 = local_84;
  local_90 = local_90 + 0x224;
  if (0x88f < local_90) goto code_r0x0050afea;
  goto LAB_0050af10;
code_r0x0050afea:
  if (*(uint *)(DAT_005b3484 + 0x44e24) <= (uint)(*(int *)(local_84 + 0x454) + param_1)) {
                    /* WARNING: Subroutine does not return */
    FUN_004010c0(0x80070057);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = iVar2 >> 0x10 & 0xf;
  uVar6 = uVar5 * 2;
  if (uVar5 != 3) {
    if (*(uint *)(DAT_005b3484 + 0x44e24) <= (uint)(*(int *)(puVar3 + 0x454) + param_1)) {
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (-1 < extraout_AH) {
      uVar6 = uVar6 + 1;
    }
  }
  if (DAT_0079352c != 0) {
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar5 = *(uint *)(iVar2 + 4);
    while (uVar5 < 0x2714) {
      if (uVar5 == 0x2713) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar5 = *(uint *)(iVar2 + 8);
        if (uVar5 <= uVar6) goto LAB_0050b0e6;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar5 = *(uint *)(iVar2 + 4);
    }
  }
  goto LAB_0050b11f;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar5 = *(uint *)(iVar2 + 8);
    if (uVar6 < uVar5) break;
LAB_0050b0e6:
    if (uVar5 == uVar6) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(local_88 + 6,local_94 + 2);
      }
      else {
        BlitSpriteClipped(uVar6);
      }
      break;
    }
  }
LAB_0050b11f:
  if ((uint)(*(int *)(local_84 + 0x454) + param_1) < *(uint *)(DAT_005b3484 + 0x44e24)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_84 = local_84 + param_1 * 0x17e4;
    BlitRLESprite(local_94 + 3,(-(uint)((uVar5 & 0x20000000) != 0x20000000) & 0x480d) + 0xb7f2);
    local_90 = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar2 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar2 < 1) {
        iVar2 = local_88 + 0x99;
        if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
          if (*(char *)(iVar4 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar2,local_94 + 2);
          }
          else {
            BlitSpriteClipped(9);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = -iVar2;
      }
      else {
        iVar2 = local_88 + 0x99;
        if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
          if (*(char *)(iVar4 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar2,local_94 + 2);
          }
          else {
            BlitSpriteClipped(8);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(local_80,&DAT_00555654,iVar2);
      FUN_004ed9f0(0x28,local_80,2,6);
      local_90 = 1;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    pcVar7 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar2 != 0) && (local_90 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_8c = (undefined *)(local_90 * 0x19 + local_88);
      puVar3 = local_8c + 0x67;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(puVar3,local_94 + 2);
          }
          else {
            BlitSpriteClipped(10);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = -iVar2;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(puVar3,local_94 + 2);
          }
          else {
            BlitSpriteClipped(0xb);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(local_80,&DAT_00555654,iVar2);
      FUN_004ed9f0(0x28,local_80,2,6);
      local_90 = local_90 + -1;
      pcVar7 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8c = local_84 + 0xe628;
    iVar2 = PeekPacketChecksumState();
    puVar9 = &DAT_005a9068;
    (*pcVar7)(&DAT_005a9068);
    puVar3 = local_94;
    if ((iVar2 != 0) && ((int)local_94 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar7)(&DAT_005a9068);
      if (iVar2 < 0) {
        puVar3 = local_8c + (int)puVar3 * 0x19 + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(puVar3,unaff_EBX + 2);
          }
          else {
            BlitSpriteClipped(0xc);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = -iVar2;
      }
      else {
        puVar3 = local_8c + (int)puVar3 * 0x19 + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(puVar3,unaff_EBX + 2);
          }
          else {
            BlitSpriteClipped(0xd);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_84,&DAT_00555654,iVar2);
      FUN_004ed9f0(0x28,&local_84,2,6);
      local_94 = local_94 + -1;
      pcVar7 = (code *)LeaveCriticalSection;
    }
    puVar3 = local_94;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_90 = local_88 + 0xe84c;
    iVar2 = PeekPacketChecksumState();
    (*pcVar7)(&DAT_005a9068);
    if ((iVar2 != 0) && ((int)puVar3 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar7)(&DAT_005a9068);
      if (iVar2 < 0) {
        iVar2 = (int)puVar3 * 0x19 + local_90;
        if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
          if (*(char *)(iVar4 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar2 + 0x67,unaff_EBP + 2);
          }
          else {
            BlitSpriteClipped(0xe);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = -iVar2;
      }
      else {
        iVar2 = (int)puVar3 * 0x19 + local_90;
        if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
          if (*(char *)(iVar4 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar2 + 0x67,unaff_EBP + 2);
          }
          else {
            BlitSpriteClipped(0xf);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_88,&DAT_00555654,iVar2);
      FUN_004ed9f0(0x28,&local_88,2,6);
      puVar3 = (undefined *)(unaff_EBX + -1);
      pcVar7 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_94 = local_8c + 0xea70;
    iVar2 = PeekPacketChecksumState();
    puVar8 = &DAT_005a9068;
    (*pcVar7)(&DAT_005a9068);
    if ((iVar2 != 0) && ((int)puVar3 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar7)(&DAT_005a9068);
      if (iVar2 < 0) {
        puVar3 = local_94 + (int)puVar3 * 0x19 + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(puVar3,unaff_ESI + 2);
          }
          else {
            BlitSpriteClipped(0x10);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = -iVar2;
      }
      else {
        puVar3 = local_94 + (int)puVar3 * 0x19 + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(puVar3,unaff_ESI + 2);
          }
          else {
            BlitSpriteClipped(0x11);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_8c,&DAT_00555654,iVar2);
      FUN_004ed9f0(0x28,&local_8c,2,6);
      puVar3 = (undefined *)(unaff_EBP + -1);
      pcVar7 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = local_90 + 0xec94;
    iVar4 = PeekPacketChecksumState();
    (*pcVar7)(&DAT_005a9068);
    if ((iVar4 != 0) && ((int)puVar3 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      (*pcVar7)(&DAT_005a9068);
      if (iVar4 < 0) {
        if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
          if (*(char *)(iVar4 + 0x18) == '\x01') {
            BlitSprite16bpp((int)puVar3 * 0x19 + iVar2 + 0x67,unaff_EDI + 2);
          }
          else {
            BlitSpriteClipped(0x12);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = -iVar2;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar4 = FUN_004f30c0(), iVar4 != 0)) {
          if (*(char *)(iVar4 + 0x18) == '\x01') {
            BlitSprite16bpp((int)puVar3 * 0x19 + iVar2 + 0x67,unaff_EDI + 2);
          }
          else {
            BlitSpriteClipped(0x13);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_90,&DAT_00555654,iVar2);
      FUN_004ed9f0(0x28,&local_90,2,6);
      puVar3 = (undefined *)(unaff_ESI + -1);
      pcVar7 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puVar1 = local_94;
    iVar2 = PeekPacketChecksumState();
    (*pcVar7)(&DAT_005a9068);
    if ((iVar2 != 0) && ((int)puVar3 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar7)(&DAT_005a9068);
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(puVar1 + (int)puVar3 * 0x19 + 0xe46b,puVar9 + 2);
          }
          else {
            BlitSpriteClipped(0x14);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = -iVar2;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(puVar1 + (int)puVar3 * 0x19 + 0xe46b,puVar9 + 2);
          }
          else {
            BlitSpriteClipped(0x15);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_94,&DAT_00555654,iVar2);
      FUN_004ed9f0(0x28,&local_94,2,6);
      puVar3 = unaff_EDI + -1;
      pcVar7 = (code *)LeaveCriticalSection;
      unaff_EDI = puVar3;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    (*pcVar7)(&DAT_005a9068);
    if ((iVar2 != 0) && ((int)puVar3 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      (*pcVar7)(&DAT_005a9068);
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(unaff_EDI + (int)puVar3 * 0x19 + 0x67,puVar8 + 2);
          }
          else {
            BlitSpriteClipped(0x16);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = -iVar2;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FUN_004f30c0(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(unaff_EDI + (int)puVar3 * 0x19 + 0x67,puVar8 + 2);
          }
          else {
            BlitSpriteClipped(0x17);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(&stack0xffffff64,&DAT_00555654,iVar2);
      FUN_004ed9f0(0x28,&stack0xffffff64,2,6);
    }
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_004010c0(0x80070057);
}

