/* FUN_0044fff0 - 0x0044fff0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0044fff0(int param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  bool bVar14;
  int local_10;
  int local_8;
  
  local_10 = *(int *)(param_1 + 0x38);
  iVar8 = *(int *)(param_1 + 0x3c);
  if (g_currentGameState == 0xb) {
    local_10 = local_10 + (400 - *(int *)(&g_nCameraX + g_clientContext));
    iVar8 = iVar8 + (0x12a - *(int *)(&g_nCameraY + g_clientContext));
  }
  iVar5 = *(int *)(param_1 + 0x2d4);
  iVar7 = 0;
  if (0 < iVar5) {
    pcVar9 = (char *)(param_1 + 0x2dc);
    local_8 = iVar5;
    do {
      pcVar3 = pcVar9;
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      iVar4 = ((int)pcVar3 - (int)(pcVar9 + 1)) * 6;
      if (iVar4 - iVar7 != 0 && iVar7 <= iVar4) {
        iVar7 = iVar4;
      }
      pcVar9 = pcVar9 + 0x14;
      local_8 = local_8 + -1;
    } while (local_8 != 0);
  }
  iVar11 = ((iVar7 + 5) / 6) * 6;
  iVar4 = (iVar5 * 0xe + 1) / 2;
  iVar13 = iVar4 * 2;
  iVar7 = local_10 - iVar11 / 2;
  iVar5 = iVar11 / 2 + local_10;
  iVar4 = iVar8 + iVar4 * -2;
  iVar10 = iVar4 + -0x1a;
  iVar8 = iVar8 + -0x1a;
  FillScreenRect(iVar11,0xffff);
  if (0 < iVar11) {
    iVar12 = (iVar11 - 1U) / 6 + 1;
    iVar11 = iVar7;
LAB_00450100:
    if (DAT_0079352c != 0) {
      iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar2 = *(uint *)(iVar6 + 4);
      while (uVar2 < 0x271a) {
        if (uVar2 == 0x2719) {
          iVar6 = *(int *)(iVar6 + 0x10);
          uVar2 = *(uint *)(iVar6 + 8);
          if (uVar2 < 2) goto LAB_0045013d;
          break;
        }
        iVar6 = *(int *)(iVar6 + 0x1c);
        uVar2 = *(uint *)(iVar6 + 4);
      }
      goto LAB_00450176;
    }
    goto LAB_004501f4;
  }
LAB_00450202:
  if (0 < iVar13) {
    iVar13 = (iVar13 - 1U >> 1) + 1;
    iVar11 = iVar10;
LAB_00450220:
    if (DAT_0079352c != 0) {
      iVar12 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar2 = *(uint *)(iVar12 + 4);
      while (uVar2 < 0x271a) {
        if (uVar2 == 0x2719) {
          iVar12 = *(int *)(iVar12 + 0x10);
          uVar2 = *(uint *)(iVar12 + 8);
          if (uVar2 < 4) goto LAB_0045025d;
          break;
        }
        iVar12 = *(int *)(iVar12 + 0x1c);
        uVar2 = *(uint *)(iVar12 + 4);
      }
      goto LAB_00450296;
    }
    goto LAB_00450314;
  }
LAB_0045031e:
  if (DAT_0079352c == 0) goto LAB_00450599;
  iVar11 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar2 = *(uint *)(iVar11 + 4);
  while (uVar2 < 0x271a) {
    if (uVar2 == 0x2719) {
      iVar11 = *(int *)(iVar11 + 0x10);
      bVar14 = true;
      if (*(int *)(iVar11 + 8) == 0) goto LAB_00450364;
      break;
    }
    iVar11 = *(int *)(iVar11 + 0x1c);
    uVar2 = *(uint *)(iVar11 + 4);
  }
  goto LAB_00450399;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar2 = *(uint *)(iVar6 + 8);
    if (1 < uVar2) break;
LAB_0045013d:
    if (uVar2 == 1) {
      if (*(char *)(iVar6 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar11,iVar4 + -0x26);
      }
      else {
        BlitSpriteClipped(1);
      }
      break;
    }
  }
LAB_00450176:
  if (DAT_0079352c != 0) {
    iVar6 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar2 = *(uint *)(iVar6 + 4);
    while (uVar2 < 0x271a) {
      if (uVar2 == 0x2719) {
        iVar6 = *(int *)(iVar6 + 0x10);
        uVar2 = *(uint *)(iVar6 + 8);
        if (uVar2 < 7) goto LAB_004501b0;
        break;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar2 = *(uint *)(iVar6 + 4);
    }
  }
LAB_004501f4:
  iVar11 = iVar11 + 6;
  iVar12 = iVar12 + -1;
  if (iVar12 == 0) goto LAB_00450202;
  goto LAB_00450100;
  while( true ) {
    iVar6 = *(int *)(iVar6 + 0x10);
    uVar2 = *(uint *)(iVar6 + 8);
    if (6 < uVar2) break;
LAB_004501b0:
    if (uVar2 == 6) {
      if (*(char *)(iVar6 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar11,iVar8);
      }
      else {
        BlitSpriteClipped(6);
      }
      break;
    }
  }
  goto LAB_004501f4;
  while( true ) {
    iVar12 = *(int *)(iVar12 + 0x10);
    uVar2 = *(uint *)(iVar12 + 8);
    if (3 < uVar2) break;
LAB_0045025d:
    if (uVar2 == 3) {
      if (*(char *)(iVar12 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar7 + -6,iVar11);
      }
      else {
        BlitSpriteClipped(3);
      }
      break;
    }
  }
LAB_00450296:
  if (DAT_0079352c != 0) {
    iVar12 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar2 = *(uint *)(iVar12 + 4);
    while (uVar2 < 0x271a) {
      if (uVar2 == 0x2719) {
        iVar12 = *(int *)(iVar12 + 0x10);
        uVar2 = *(uint *)(iVar12 + 8);
        if (uVar2 < 5) goto LAB_004502d0;
        break;
      }
      iVar12 = *(int *)(iVar12 + 0x1c);
      uVar2 = *(uint *)(iVar12 + 4);
    }
  }
LAB_00450314:
  iVar11 = iVar11 + 2;
  iVar13 = iVar13 + -1;
  if (iVar13 == 0) goto LAB_0045031e;
  goto LAB_00450220;
  while( true ) {
    iVar12 = *(int *)(iVar12 + 0x10);
    uVar2 = *(uint *)(iVar12 + 8);
    if (4 < uVar2) break;
LAB_004502d0:
    if (uVar2 == 4) {
      if (*(char *)(iVar12 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar5,iVar11);
      }
      else {
        BlitSpriteClipped(4);
      }
      break;
    }
  }
  goto LAB_00450314;
  while( true ) {
    iVar11 = *(int *)(iVar11 + 0x10);
    uVar2 = *(uint *)(iVar11 + 8);
    if (2 < uVar2) break;
LAB_004503d7:
    if (uVar2 == 2) {
      if (*(char *)(iVar11 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar5,iVar4 + -0x26);
      }
      else {
        BlitSpriteClipped(2);
      }
      break;
    }
  }
  goto LAB_0045041b;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar2 = *(uint *)(iVar4 + 8);
    if (5 < uVar2) break;
LAB_00450494:
    if (uVar2 == 5) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar7 + -6,iVar8);
      }
      else {
        BlitSpriteClipped(5);
      }
      break;
    }
  }
  goto LAB_0045044f;
  while( true ) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar2 = *(uint *)(iVar7 + 8);
    if (7 < uVar2) break;
LAB_004504e1:
    if (uVar2 == 7) {
      if (*(char *)(iVar7 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar5,iVar8);
      }
      else {
        BlitSpriteClipped(7);
      }
      break;
    }
  }
  goto LAB_00450525;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar2 = *(uint *)(iVar5 + 8);
    if (8 < uVar2) break;
LAB_0045055e:
    if (uVar2 == 8) {
      if (*(char *)(iVar5 + 0x18) == '\x01') {
        BlitSprite16bpp(local_10,iVar8);
      }
      else {
        BlitSpriteClipped(8);
      }
      break;
    }
  }
  goto LAB_00450599;
  while( true ) {
    iVar11 = *(int *)(iVar11 + 0x10);
    bVar14 = *(int *)(iVar11 + 8) == 0;
    if (!bVar14) break;
LAB_00450364:
    if (bVar14) {
      if (*(char *)(iVar11 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar7 + -6,iVar4 + -0x26);
      }
      else {
        BlitSpriteClipped(0);
      }
      break;
    }
  }
LAB_00450399:
  if (DAT_0079352c != 0) {
    iVar11 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar2 = *(uint *)(iVar11 + 4);
    while (uVar2 < 0x271a) {
      if (uVar2 == 0x2719) {
        iVar11 = *(int *)(iVar11 + 0x10);
        uVar2 = *(uint *)(iVar11 + 8);
        if (uVar2 < 3) goto LAB_004503d7;
        break;
      }
      iVar11 = *(int *)(iVar11 + 0x1c);
      uVar2 = *(uint *)(iVar11 + 4);
    }
LAB_0045041b:
    if (DAT_0079352c != 0) {
      iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar2 = *(uint *)(iVar4 + 4);
      while (uVar2 < 0x271a) {
        if (uVar2 == 0x2719) {
          iVar4 = *(int *)(iVar4 + 0x10);
          uVar2 = *(uint *)(iVar4 + 8);
          if (uVar2 < 6) goto LAB_00450494;
          break;
        }
        iVar4 = *(int *)(iVar4 + 0x1c);
        uVar2 = *(uint *)(iVar4 + 4);
      }
LAB_0045044f:
      if (DAT_0079352c != 0) {
        iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar2 = *(uint *)(iVar7 + 4);
        while (uVar2 < 0x271a) {
          if (uVar2 == 0x2719) {
            iVar7 = *(int *)(iVar7 + 0x10);
            uVar2 = *(uint *)(iVar7 + 8);
            if (uVar2 < 8) goto LAB_004504e1;
            break;
          }
          iVar7 = *(int *)(iVar7 + 0x1c);
          uVar2 = *(uint *)(iVar7 + 4);
        }
LAB_00450525:
        if (DAT_0079352c != 0) {
          iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
          uVar2 = *(uint *)(iVar5 + 4);
          while (uVar2 < 0x271a) {
            if (uVar2 == 0x2719) {
              iVar5 = *(int *)(iVar5 + 0x10);
              uVar2 = *(uint *)(iVar5 + 8);
              if (uVar2 < 9) goto LAB_0045055e;
              break;
            }
            iVar5 = *(int *)(iVar5 + 0x1c);
            uVar2 = *(uint *)(iVar5 + 4);
          }
        }
      }
    }
  }
LAB_00450599:
  iVar8 = 0;
  if (0 < *(int *)(param_1 + 0x2d4)) {
    pcVar9 = (char *)(param_1 + 0x2dc);
    pcVar3 = pcVar9;
    do {
      do {
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      /* BlitRLESprite's 1st arg (this/param_1) and 4th arg (rleData) were
       * dropped placeholders. objdump at this call site (0x4505d6) shows:
       *   mov ecx,[esp+0x18]      ; ecx = local_10 (this function's centered
       *                           ;   x-cursor, held in that stack slot
       *                           ;   throughout the function post-prologue)
       *   sub eax,edx             ; eax = strlen("pcVar3's field") * 6
       *   sar eax,1               ; eax = strlen * 3 (half-width)
       *   push 0x0                ; param_3 = color
       *   sub ecx,eax             ; ecx -= half-width  -> centered this
       *   push edi                ; param_2 = iVar10
       *   mov eax,esi             ; rleData = esi = pcVar3 (name field ptr)
       * i.e. this = local_10 - ((pcVar9 - (pcVar3 + 1)) * 6) / 2, matching
       * the same centering idiom already used earlier in this function
       * (iVar7 = local_10 - iVar11/2). */
      BlitRLESprite(local_10 - ((((int)pcVar9 - (int)(pcVar3 + 1)) * 6) / 2),iVar10,0,
                    (byte *)pcVar3);
      iVar8 = iVar8 + 1;
      pcVar9 = pcVar3 + 0x14;
      iVar10 = iVar10 + 0xe;
      pcVar3 = pcVar9;
    } while (iVar8 < *(int *)(param_1 + 0x2d4));
  }
  return;
}

