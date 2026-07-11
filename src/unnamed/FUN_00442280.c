/* FUN_00442280 - 0x00442280 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_00442280(int param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  LRESULT LVar10;
  HIMC pHVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined2 *puVar15;
  int iVar16;
  int *piVar17;
  uint uVar18;
  bool bVar19;
  tagCOMPOSITIONFORM *lpCompForm;
  int iStack_b0;
  int iStack_ac;
  char cStack_a5;
  int iStack_a4;
  int iStack_a0;
  tagCOMPOSITIONFORM tStack_9c;
  char acStack_80 [128];
  
  iStack_a4 = param_1;
  if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(0);
    }
    else {
      BlitSpriteClipped(0);
    }
  }
  if (DAT_00e55a34 == -1) {
    if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
      if (*(char *)(iVar5 + 0x18) == '\x01') {
        BlitSprite16bpp(0x243,0x10c);
      }
      else {
        BlitSpriteClipped(0x17);
      }
    }
    FUN_00442d50(param_1);
  }
  SetClipRect();
  if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(0x6b,0x237);
    }
    else {
      BlitSpriteClipped(0x16);
    }
  }
  SetClipRect();
  bVar2 = *(byte *)(g_clientContext + 0x475c4);
  if ((DAT_0079352c != 0) && (iVar5 = FindSpriteFrame(), iVar5 != 0)) {
    if (*(char *)(iVar5 + 0x18) == '\x01') {
      BlitSprite16bpp(0x1a,0x12);
    }
    else {
      BlitSpriteClipped((uint)bVar2 * 2);
    }
  }
  iStack_a0 = 0;
  iStack_ac = 0;
  iStack_b0 = 499;
LAB_00442440:
  uVar18 = 0x2000 << ((byte)iStack_a0 & 0x1f);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((uVar6 & uVar18) == uVar18) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = iVar5 + 0x10c;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar6)) {
      iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar18 = *(uint *)(iVar5 + 4);
      while (uVar18 < 0x33) {
        if (uVar18 == 0x32) {
          iVar5 = *(int *)(iVar5 + 0x10);
          uVar18 = *(uint *)(iVar5 + 8);
          if (uVar18 <= uVar6) goto LAB_00442525;
          break;
        }
        iVar5 = *(int *)(iVar5 + 0x1c);
        uVar18 = *(uint *)(iVar5 + 4);
      }
    }
  }
  else if (DAT_0079352c != 0) {
    iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar6 = *(uint *)(iVar5 + 4);
    while (uVar6 < 0x33) {
      if (uVar6 == 0x32) {
        iVar5 = *(int *)(iVar5 + 0x10);
        uVar6 = *(uint *)(iVar5 + 8);
        if (uVar6 < 0x10d) goto LAB_00442591;
        break;
      }
      iVar5 = *(int *)(iVar5 + 0x1c);
      uVar6 = *(uint *)(iVar5 + 4);
    }
  }
  goto LAB_004425da;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar6 = *(uint *)(iVar5 + 8);
    if (0x10c < uVar6) break;
LAB_00442591:
    if (uVar6 == 0x10c) {
      if (*(char *)(iVar5 + 0x18) != '\x01') {
        uVar6 = 0x10c;
        goto LAB_004425cd;
      }
      BlitSprite16bpp(iStack_b0,0xe);
      break;
    }
  }
  goto LAB_004425da;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar18 = *(uint *)(iVar5 + 8);
    if (uVar6 < uVar18) break;
LAB_00442525:
    if (uVar18 == uVar6) {
      if (*(char *)(iVar5 + 0x18) == '\x01') {
        BlitSprite16bpp(iStack_b0,0xe);
      }
      else {
LAB_004425cd:
        BlitSpriteClipped(uVar6);
      }
      break;
    }
  }
LAB_004425da:
  iVar5 = iStack_a4;
  iStack_b0 = iStack_b0 + 0x2c;
  iStack_a0 = iStack_a0 + 1;
  iStack_ac = iStack_ac + 0x224;
  if (0x326 < iStack_b0) goto code_r0x00442607;
  goto LAB_00442440;
code_r0x00442607:
  pcVar8 = (char *)(iStack_a4 + 8);
  pcVar7 = pcVar8;
  do {
    cVar3 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar3 != '\0');
  DrawFontString(0x27,0);
  do {
    cVar3 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar3 != '\0');
  BlitRLESprite(0x27,0xffff);
  iVar9 = g_clientContext;
  if (0xd < *(int *)(iVar5 + 4)) {
    iStack_b0 = 0;
    iStack_ac = 0;
    piVar17 = (int *)(iVar5 + 300);
LAB_00442690:
    iVar5 = iStack_b0;
    if (*(char *)(iVar9 + 0x45914 + iStack_b0) != '\0') {
      uVar6 = (uint)(*(char *)(iVar9 + 0x4590c + iStack_b0) == '\0') * 2 + 0x18;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = PeekPacketChecksumState();
      cStack_a5 = iVar9 == iVar5;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (cStack_a5 != '\0') {
        uVar18 = *(int *)(iStack_a4 + 4) / 10 & 0x80000001;
        bVar19 = uVar18 == 0;
        if ((int)uVar18 < 0) {
          bVar19 = (uVar18 - 1 | 0xfffffffe) == 0xffffffff;
        }
        if (bVar19) {
          uVar6 = 0x19;
        }
      }
      if (DAT_0079352c != 0) {
        iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar18 = *(uint *)(iVar5 + 4);
        while (uVar18 < 0x2711) {
          if (uVar18 == 10000) {
            iVar5 = *(int *)(iVar5 + 0x10);
            uVar18 = *(uint *)(iVar5 + 8);
            if (uVar18 <= uVar6) goto LAB_00442760;
            break;
          }
          iVar5 = *(int *)(iVar5 + 0x1c);
          uVar18 = *(uint *)(iVar5 + 4);
        }
      }
      goto LAB_00442790;
    }
    goto LAB_00442805;
  }
LAB_00442831:
  _sprintf(acStack_80,&DAT_00551ed4,*(int *)(iVar9 + 0x44e60) + 1);
  pcVar8 = acStack_80;
  do {
    cVar3 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar3 != '\0');
  iStack_ac = (int)pcVar8 - (int)(acStack_80 + 1);
  if (iStack_ac == 0) {
LAB_00442907:
    iVar9 = g_clientContext;
    pcVar8 = acStack_80;
    do {
      cVar3 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar3 != '\0');
    BlitRLESprite(0x118,0xffff);
    if (*(char *)(iVar9 + 0x44ee4) != '\0') {
      BlitRLESprite(0x117,0xffff);
    }
    FUN_0041bce0(iVar9);
    if (DAT_007933b8 == '\x01') {
      if (*(char *)(DAT_007934e4 + 8) == '\0') {
        iStack_ac = 0;
        iStack_b0 = 0;
      }
      else {
        puVar1 = (undefined4 *)(DAT_007934e4 + 4);
        LVar10 = SendMessageA(*(HWND *)(DAT_007934e4 + 4),0xb0,(WPARAM)&iStack_b0,(LPARAM)&iStack_ac
                             );
        if (LVar10 == -1) {
          iStack_ac = 0;
          iStack_b0 = 0;
        }
        tStack_9c.ptCurrentPos.x = iStack_b0 * 6 + 0xca;
        lpCompForm = &tStack_9c;
        tStack_9c.dwStyle = 2;
        tStack_9c.ptCurrentPos.y = 0x21b;
        pHVar11 = ImmGetContext((HWND)*puVar1);
        ImmSetCompositionWindow(pHVar11,lpCompForm);
      }
      if ((*(char *)(DAT_007934e4 + 8) == '\0') ||
         (iVar5 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),acStack_80,0x80), iVar5 == 0)) {
        acStack_80[0] = '\0';
      }
      iVar5 = iStack_b0;
      if (iStack_b0 == -1) {
        pcVar8 = acStack_80;
        do {
          cVar3 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar3 != '\0');
        iVar5 = (int)pcVar8 - (int)(acStack_80 + 1);
      }
      iVar9 = iStack_ac;
      if (iStack_ac == -1) {
        pcVar8 = acStack_80;
        do {
          cVar3 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar3 != '\0');
        iVar9 = (int)pcVar8 - (int)(acStack_80 + 1);
      }
      iVar12 = iVar9 * 6 + iVar5 * -6 + 2;
      iVar9 = iVar5 * 6 + 0xca;
      if (((DAT_0079352c != 0) && (0x21a < DAT_0056df34)) && (DAT_00793534 < 0x21c)) {
        iVar13 = iVar12;
        iVar14 = iVar9;
        if (iVar9 < DAT_00793530) {
          iVar13 = (iVar9 - DAT_00793530) + iVar12;
          iVar14 = DAT_00793530;
        }
        if (DAT_0056df30 < iVar14 + iVar13) {
          iVar13 = (DAT_0056df30 - iVar14) + 1;
        }
        if (0 < iVar13) {
          FillPixels16(DAT_0079352c + (DAT_005b3620 * 0x21b + iVar14) * 2,0xf800,iVar13);
        }
      }
      if (((DAT_0079352c != 0) && (0x225 < DAT_0056df34)) && (DAT_00793534 < 0x227)) {
        iVar13 = iVar12;
        iVar14 = iVar9;
        if (iVar9 < DAT_00793530) {
          iVar13 = (iVar9 - DAT_00793530) + iVar12;
          iVar14 = DAT_00793530;
        }
        if (DAT_0056df30 < iVar14 + iVar13) {
          iVar13 = (DAT_0056df30 - iVar14) + 1;
        }
        if (0 < iVar13) {
          FillPixels16(DAT_0079352c + (DAT_005b3620 * 0x226 + iVar14) * 2,0xf800,iVar13);
        }
      }
      iVar13 = DAT_0056df34;
      iVar14 = 0xc;
      if (((DAT_0079352c != 0) && (iVar9 <= DAT_0056df30)) && (DAT_00793530 <= iVar9)) {
        iVar16 = 0x21b;
        if (0x21b < DAT_00793534) {
          iVar14 = 0x227 - DAT_00793534;
          iVar16 = DAT_00793534;
        }
        if (DAT_0056df34 < iVar16 + iVar14) {
          iVar14 = (DAT_0056df34 - iVar16) + 1;
        }
        if ((0 < iVar14) &&
           (puVar15 = (undefined2 *)(DAT_0079352c + (iVar16 * DAT_005b3620 + iVar9) * 2), 0 < iVar14
           )) {
          do {
            iVar14 = iVar14 + -1;
            *puVar15 = 0xf800;
            puVar15 = puVar15 + DAT_005b3620;
          } while (iVar14 != 0);
        }
      }
      iVar9 = 0xc;
      iVar12 = iVar5 * 6 + 0xc9 + iVar12;
      if (((DAT_0079352c != 0) && (iVar12 <= DAT_0056df30)) && (DAT_00793530 <= iVar12)) {
        iVar5 = 0x21b;
        if (0x21b < DAT_00793534) {
          iVar9 = 0x227 - DAT_00793534;
          iVar5 = DAT_00793534;
        }
        if (iVar13 < iVar5 + iVar9) {
          iVar9 = (iVar13 - iVar5) + 1;
        }
        if ((0 < iVar9) &&
           (puVar15 = (undefined2 *)(DAT_0079352c + (iVar5 * DAT_005b3620 + iVar12) * 2), 0 < iVar9)
           ) {
          do {
            iVar9 = iVar9 + -1;
            *puVar15 = 0xf800;
            puVar15 = puVar15 + DAT_005b3620;
          } while (iVar9 != 0);
        }
      }
      BlitRLESprite(0x21c,0);
      iVar12 = BlitRLESprite(0x21b,0xffe0);
      iVar5 = iStack_a4;
      iVar9 = g_clientContext;
    }
    else {
      iVar12 = BlitRLESprite(0x208,0xffff);
    }
    if (((*(short *)(&DAT_006aa660 + iVar9) != -1) &&
        (iVar12 = *(int *)(iVar5 + 4) / 0x14, *(int *)(iVar5 + 4) % 0x14 < 10)) &&
       (iVar12 = 0, DAT_0079352c != 0)) {
      iVar12 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar6 = *(uint *)(iVar12 + 4);
      if (uVar6 < 0x2713) {
        while (uVar6 != 0x2712) {
          iVar12 = *(int *)(iVar12 + 0x1c);
          uVar6 = *(uint *)(iVar12 + 4);
          if (0x2712 < uVar6) {
            return iVar12;
          }
        }
        iVar12 = *(int *)(iVar12 + 0x10);
        bVar19 = true;
        if (*(int *)(iVar12 + 8) == 0) {
          while (!bVar19) {
            iVar12 = *(int *)(iVar12 + 0x10);
            bVar19 = *(int *)(iVar12 + 8) == 0;
            if (!bVar19) {
              return iVar12;
            }
          }
          if (*(char *)(iVar12 + 0x18) == '\x01') {
            iVar5 = BlitSprite16bpp(0x1a,0x12);
            return iVar5;
          }
          iVar12 = BlitSpriteClipped(0);
        }
      }
    }
    return iVar12;
  }
  iVar9 = 0x29;
  uVar6 = 0;
LAB_00442870:
  uVar18 = (int)acStack_80[uVar6] + 0xd2;
  if ((DAT_0079352c != 0) && (-1 < (int)uVar18)) {
    iVar12 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar4 = *(uint *)(iVar12 + 4);
    while (uVar4 < 0x33) {
      if (uVar4 == 0x32) {
        iVar12 = *(int *)(iVar12 + 0x10);
        uVar4 = *(uint *)(iVar12 + 8);
        if (uVar4 <= uVar18) goto LAB_004428b2;
        break;
      }
      iVar12 = *(int *)(iVar12 + 0x1c);
      uVar4 = *(uint *)(iVar12 + 4);
    }
  }
  goto LAB_004428eb;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar18 = *(uint *)(iVar5 + 8);
    if (uVar6 < uVar18) break;
LAB_00442760:
    if (uVar18 == uVar6) {
      if (*(char *)(iVar5 + 0x18) == '\x01') {
        BlitSprite16bpp(piVar17[-8] + 0x1a,*piVar17 + 2);
      }
      else {
        BlitSpriteClipped(uVar6);
      }
      break;
    }
  }
LAB_00442790:
  iVar9 = g_clientContext;
  pcVar8 = (char *)(iStack_ac + 0x457f1 + g_clientContext);
  do {
    cVar3 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar3 != '\0');
  DrawFontString(*piVar17 + 5,
               -(uint)(*(char *)(g_clientContext + 0x4590c + iStack_b0) !=
                      *(char *)(g_clientContext + 0x3b6c0)) & 0xfae8);
  BlitRLESprite(*piVar17 + 5,0xffff);
LAB_00442805:
  iStack_ac = iStack_ac + 0xd;
  iStack_b0 = iStack_b0 + 1;
  piVar17 = piVar17 + 1;
  iVar5 = iStack_a4;
  if (0x67 < iStack_ac) goto LAB_00442831;
  goto LAB_00442690;
  while( true ) {
    iVar12 = *(int *)(iVar12 + 0x10);
    uVar4 = *(uint *)(iVar12 + 8);
    if (uVar18 < uVar4) break;
LAB_004428b2:
    if (uVar4 == uVar18) {
      if (*(char *)(iVar12 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar9,0x117);
      }
      else {
        BlitSpriteClipped(uVar18);
      }
      break;
    }
  }
LAB_004428eb:
  pcVar8 = acStack_80;
  uVar6 = uVar6 + 1;
  iVar9 = iVar9 + 8;
  do {
    cVar3 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar3 != '\0');
  if ((uint)((int)pcVar8 - (int)(acStack_80 + 1)) <= uVar6) goto LAB_00442907;
  goto LAB_00442870;
}

