/* FUN_0044a000 - 0x0044a000 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0044a000(int param_1,int param_2)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffffed0;
  undefined stack0xfffffed8;
  undefined stack0xfffffee0;
  undefined stack0xfffffee8;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  undefined4 unaff_EBP;
  undefined3 unaff_ESI;
  code *pcVar6;
  undefined4 unaff_EDI;
  uint uVar7;
  undefined4 uVar8;
  undefined *puVar9;
  undefined *puVar10;
  char cVar11;
  undefined *puVar12;
  char cVar13;
  char cVar14;
  undefined4 uStack_110;
  int local_10c;
  int local_108;
  int local_104;
  char local_100 [120];
  char acStack_88 [136];
  
  iVar4 = (param_2 % 3) * 0xa3;
  local_108 = (param_2 / 3) * 0xa1 + 0x45;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp();
    }
    else {
      BlitSpriteClipped();
    }
  }
  iVar1 = *(int *)(param_1 + 0x44c) * 2;
  if ((iVar1 != 6) &&
     (*(char *)(param_2 + *(int *)(param_1 + 0x450) * 9 + 0x2d54c + param_1) == '\0')) {
    iVar1 = iVar1 + 1;
  }
  if (((DAT_0079352c != 0) && (-1 < iVar1)) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp();
    }
    else {
      BlitSpriteClipped();
    }
  }
  if (*(int *)(param_1 + 0x44c) != 3) {
    if (*(char *)(param_2 + *(int *)(param_1 + 0x450) * 9 + 0x2d54c + param_1) == '\x01') {
      if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
        if (*(char *)(iVar1 + 0x18) == '\x01') {
          BlitSprite16bpp();
        }
        else {
LAB_0044a1b2:
          BlitSpriteClipped();
        }
      }
    }
    else if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) != '\x01') goto LAB_0044a1b2;
      BlitSprite16bpp();
    }
  }
  local_104 = param_2 * 0x17e4 + param_1;
  FUN_004eb510();
  BlitRLESprite();
  if ((*(int *)(param_1 + 0x34790) < 0x15) || (*(int *)(param_1 + 0x3478c) != param_2)) {
    if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp();
      }
      else {
        BlitSpriteClipped();
      }
    }
    pcVar6 = (code *)EnterCriticalSection;
    uVar7 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_10c = local_104 + 0xadc;
    iVar1 = PeekPacketChecksumState();
    pcVar5 = (code *)LeaveCriticalSection;
    SUBFIELD(uStack_110,3,undefined1) = iVar1 != 0;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (SUBFIELD(uStack_110,3,undefined1) != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState();
      SUBFIELD(uStack_110,3,undefined1) = iVar1 < 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (SUBFIELD(uStack_110,3,undefined1) == '\0') {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock();
      }
      else {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock();
      }
      _sprintf(local_100,&DAT_00555654);
      BlitSpriteText();
      uVar7 = 1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
    puVar12 = &DAT_005a9068;
    (*pcVar6)();
    uStack_110 = local_108 + 0x19d8;
    PeekPacketChecksumState();
    cVar11 = '\0';
    (*pcVar5)();
    cVar14 = (char)((uint)unaff_EBP >> 0x18);
    if ((cVar14 != '\0') && (uVar7 < 3)) {
      (*pcVar6)();
      PeekPacketChecksumState();
      (*pcVar5)();
      if (cVar14 == '\0') {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock();
      }
      else {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock();
      }
      _sprintf((char *)&local_108,&DAT_00555654);
      BlitSpriteText(0x28,&local_108);
      uVar7 = uVar7 + 1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
    puVar10 = &DAT_005a9068;
    (*pcVar6)();
    iVar1 = uStack_110;
    iVar2 = uStack_110 + 0xf24;
    iVar3 = PeekPacketChecksumState();
    cVar14 = '\0';
    uVar8 = CONCAT13(iVar3 != 0,unaff_ESI);
    (*pcVar5)();
    cVar13 = (char)((uint)unaff_EDI >> 0x18);
    if ((cVar13 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&DAT_005a9068);
      PeekPacketChecksumState();
      puVar12 = (undefined *)((uint)puVar12 & 0xffffff);
      (*pcVar5)(&DAT_005a9068);
      if (cVar13 == '\0') {
        if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22);
          }
          else {
            BlitSpriteClipped(0xd);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22);
          }
          else {
            BlitSpriteClipped(0xc);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
        iVar2 = -iVar2;
      }
      _sprintf((char *)&uStack_110,&DAT_00555654,iVar2);
      BlitSpriteText(0x28,&uStack_110,2,6);
      uVar7 = uVar7 + 1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
    puVar9 = &DAT_005a9068;
    (*pcVar6)(&DAT_005a9068);
    iVar2 = iVar1 + 0x206c;
    iVar3 = PeekPacketChecksumState();
    cVar13 = '\0';
    uVar8 = CONCAT13(iVar3 != 0,(int3)puVar12);
    (*pcVar5)();
    if ((cVar11 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&DAT_005a9068);
      PeekPacketChecksumState();
      puVar10 = (undefined *)((uint)puVar10 & 0xffffff);
      (*pcVar5)(&DAT_005a9068);
      if (cVar11 == '\0') {
        if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22);
          }
          else {
            BlitSpriteClipped(0xf);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22);
          }
          else {
            BlitSpriteClipped(0xe);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
        iVar2 = -iVar2;
      }
      _sprintf(&stack0xfffffee8,&DAT_00555654,iVar2);
      BlitSpriteText(0x28,&stack0xfffffee8,2,6);
      uVar7 = uVar7 + 1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
    puVar12 = &DAT_005a9068;
    (*pcVar6)(&DAT_005a9068);
    iVar1 = iVar1 + 0x33d8;
    iVar2 = PeekPacketChecksumState();
    cVar11 = '\0';
    uVar8 = CONCAT13(iVar2 != 0,(int3)puVar10);
    (*pcVar5)();
    if ((cVar14 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&DAT_005a9068);
      PeekPacketChecksumState();
      puVar9 = (undefined *)((uint)puVar9 & 0xffffff);
      (*pcVar5)(&DAT_005a9068);
      if (cVar14 == '\0') {
        iVar2 = iVar1 + uVar7 * 0x12;
        if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar2 + 0x22);
          }
          else {
            BlitSpriteClipped(0x11);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        iVar2 = iVar1 + uVar7 * 0x12;
        if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar2 + 0x22);
          }
          else {
            BlitSpriteClipped(0x10);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
        iVar2 = -iVar2;
      }
      _sprintf(&stack0xfffffee0,&DAT_00555654,iVar2);
      BlitSpriteText(0x28,&stack0xfffffee0,2,6);
      uVar7 = uVar7 + 1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
    (*pcVar6)(&DAT_005a9068);
    iVar1 = iVar1 + 0x1590;
    iVar2 = PeekPacketChecksumState();
    uVar8 = CONCAT13(iVar2 != 0,(int3)puVar9);
    (*pcVar5)(&DAT_005a9068);
    if ((cVar13 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&DAT_005a9068);
      PeekPacketChecksumState();
      puVar12 = (undefined *)((uint)puVar12 & 0xffffff);
      (*pcVar5)(&DAT_005a9068);
      if (cVar13 == '\0') {
        iVar2 = iVar1 + uVar7 * 0x12;
        if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar2 + 0x22);
          }
          else {
            BlitSpriteClipped(0x13);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        iVar2 = iVar1 + uVar7 * 0x12;
        if ((DAT_0079352c != 0) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar2 + 0x22);
          }
          else {
            BlitSpriteClipped(0x12);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
        iVar2 = -iVar2;
      }
      _sprintf(&stack0xfffffed8,&DAT_00555654,iVar2);
      BlitSpriteText(0x28,&stack0xfffffed8,2,6);
      uVar7 = uVar7 + 1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
    (*pcVar6)(&DAT_005a9068);
    iVar1 = iVar1 + 0xd00;
    iVar2 = PeekPacketChecksumState();
    uVar8 = CONCAT13(iVar2 != 0,(int3)puVar12);
    (*pcVar5)(&DAT_005a9068);
    if ((cVar11 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&DAT_005a9068);
      PeekPacketChecksumState();
      (*pcVar5)(&DAT_005a9068);
      if (cVar11 == '\0') {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar1 + uVar7 * 0x12 + 0x22);
          }
          else {
            BlitSpriteClipped(0x15);
          }
        }
        iVar1 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar4 + 0x7d,iVar1 + uVar7 * 0x12 + 0x22);
          }
          else {
            BlitSpriteClipped(0x14);
          }
        }
        iVar1 = PeekChecksumStateUnderLock(uVar8);
        iVar1 = -iVar1;
      }
      _sprintf(&stack0xfffffed0,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&stack0xfffffed0,2,6);
      uVar7 = uVar7 + 1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
    (*pcVar6)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar5)(&DAT_005a9068);
    if ((SUBFIELD(uStack_110,3,undefined1) != '\0') && (uVar7 < 3)) {
      (*pcVar6)();
      PeekPacketChecksumState();
      (*pcVar5)();
      if (SUBFIELD(uStack_110,3,undefined1) == '\0') {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock();
      }
      else {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock();
      }
      _sprintf(local_100,&DAT_00555654);
      BlitSpriteText();
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
  }
  else {
    if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp();
      }
      else {
        BlitSpriteClipped();
      }
    }
    iVar1 = 3;
    do {
      BlitRLESprite();
      iVar1 = iVar1 + -1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    } while (iVar1 != 0);
  }
  (*pcVar6)();
  iVar1 = PeekPacketChecksumState();
  (*pcVar5)();
  if (iVar1 == 0) {
    if ((DAT_0079352c == 0) || (iVar1 = FindSpriteFrame(), iVar1 == 0)) goto LAB_0044af5f;
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp();
      goto LAB_0044af5f;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(acStack_88,(char *)&PTR_DAT_00555650);
    FUN_0044c460(iVar4 + 0x23,0x3c,acStack_88,8);
    if ((DAT_0079352c == 0) || (iVar1 = FindSpriteFrame(), iVar1 == 0)) goto LAB_0044af5f;
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp();
      goto LAB_0044af5f;
    }
  }
  BlitSpriteClipped();
LAB_0044af5f:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar1 == 0) {
    if (DAT_0079352c == 0) {
      return;
    }
    iVar4 = FindSpriteFrame();
    if (iVar4 == 0) {
      return;
    }
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp();
      return;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(acStack_88,(char *)&PTR_DAT_00555650);
    FUN_0044c460(iVar4 + 0x23,0x32,acStack_88,8);
    if (DAT_0079352c == 0) {
      return;
    }
    iVar4 = FindSpriteFrame();
    if (iVar4 == 0) {
      return;
    }
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      BlitSprite16bpp();
      return;
    }
  }
  BlitSpriteClipped();
  return;
}

