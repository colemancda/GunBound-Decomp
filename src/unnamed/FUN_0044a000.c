/* FUN_0044a000 - 0x0044a000 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 21 argless PeekPacketChecksumState() calls.  All but the
 * first read the per-slot object local_104 = param_2*0x17e4 + param_1
 * (frame[0x1c], built at 0x44a1cc) at ten fixed byte offsets - 0xadc,
 * 0x19d8, 0xf24, 0x1148, 0x136c, 0x1590, 0xd00, 0x17b4 (each peeked
 * twice: the != 0 test then the < 1 test, the second through the pointer
 * the C parks in local_10c / frame[0x14]) and 0x694, 0x8b8 in the tail
 * (peeked twice each, matching the PeekChecksumStateUnderLock(local_104 +
 * 0x19d8 / + 0x17b4) landmarks the file already had).  The first site
 * (0x44a04a) reads param_1 + 4 (`mov eax,[esp+0x124]; add eax,4` -
 * [esp+0x124] is this function's own param_1, four pushes deep).
 *
 * DROPPED-ARG FIX (2026-08-11): the 6 argless PeekChecksumStateUnderLock()
 * calls now pass their guarded-cell pointer, recovered from
 * tools/underlock_push_sites.json + per-site disasm. Every one of this
 * function's 16 Peek sites pushes the frame slot [esp+0x14], which each
 * block refills with base + a per-block offset, where base = the slot
 * [esp+0x1c] = param_2*0x17e4 + param_1 = `local_104` (written once at
 * 0x44a1d9 = the line-86 assignment). Pair 1 (0x44a3c6/0x44a427) passes
 * `local_10c` - the C's own slot copy (`local_10c = local_104 + 0xadc`).
 * Pair 2 (0x44a52b/0x44a596) is base+0x19d8 (0x44a479-0x44a482); note
 * Ghidra's nearby `uStack_110 = local_108 + 0x19d8` mis-aliases the
 * base slot [esp+0x1c] as local_108 (the [esp+0x18] x-coordinate), so
 * these pass `local_104 + 0x19d8` directly. The last pair
 * (0x44ad97/0x44ae04) is base+0x17b4 (0x44ace3-0x44acec), a slot store
 * Ghidra dropped entirely, passed as `local_104 + 0x17b4`.
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
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_1 + 4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
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
  if (((g_screenSurface != 0) && (-1 < iVar1)) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp();
    }
    else {
      BlitSpriteClipped();
    }
  }
  if (*(int *)(param_1 + 0x44c) != 3) {
    if (*(char *)(param_2 + *(int *)(param_1 + 0x450) * 9 + 0x2d54c + param_1) == '\x01') {
      if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
        if (*(char *)(iVar1 + 0x18) == '\x01') {
          BlitSprite16bpp();
        }
        else {
LAB_0044a1b2:
          BlitSpriteClipped();
        }
      }
    }
    else if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) != '\x01') goto LAB_0044a1b2;
      BlitSprite16bpp();
    }
  }
  local_104 = param_2 * 0x17e4 + param_1;
  /* ALL FOUR ARGS RECOVERED (objdump @0x44a1be-0x44a1f0): x/ECX = ebx =
   * ebp + 0x18.  EBP is Ghidra's iVar4 PLUS the 0x15 it dropped from
   * `imul edx,edx,0xa3 / add edx,0x15 / mov ebp,edx` (0x44a026-0x44a034);
   * every other ebp use surfaces in this C 0x15 higher (`lea r,[ebp+0x68]`
   * is the C's iVar4 + 0x7d), so ebp+0x18 is iVar4 + 0x2d.  y = edi =
   * [esp+0x18] + 5 = local_108 + 5 (local_108 is written at 0x44a036 via
   * `mov [esp+0x1c],edi` with esp = entry-0x124; the frame is pinned by
   * [esp+0x124]=param_1 and [esp+0x128]=param_2 at 0x44a1c5/0x44a1be).
   * colour = 0.  string = EAX = esi = local_104 + 0x67c. */
  DrawFontString(iVar4 + 0x2d,local_108 + 5,0,(char *)(local_104 + 0x67c));
  /* BlitRLESprite's args were dropped entirely (Ghidra emitted a bare
   * BlitRLESprite() here) - objdump at 0x44a1ff shows ECX = ebx = ebp +
   * 0x18 and EAX = esi = local_104 + 0x67c, the same pair the
   * DrawFontString above it carries, with `push 0xffff` / `push edi` as
   * its colour and y.
   *
   * CORRECTED 2026-08-28 on both counts. The x was written iVar4 + 0x18,
   * but EBP is not iVar4: `imul edx,edx,0xa3 / add edx,0x15 / mov ebp,edx`
   * at 0x44a026-0x44a034 puts iVar4 + 0x15 in EBP, and Ghidra dropped the
   * 0x15 from the C. Every other EBP use surfaces here 0x15 higher - the
   * `lea r,[ebp+0x68]` sites are this file's own iVar4 + 0x7d - so
   * ebp + 0x18 is iVar4 + 0x2d. The y was written 0, but the pushes are
   * `push 0xffff` (colour, higher address) then `push edi` (y), and EDI
   * is [esp+0x18] + 5 = local_108 + 5. */
  BlitRLESprite(iVar4 + 0x2d,local_108 + 5,0xffff,(byte *)(local_104 + 0x67c));
  if ((*(int *)(param_1 + 0x34790) < 0x15) || (*(int *)(param_1 + 0x3478c) != param_2)) {
    if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp();
      }
      else {
        BlitSpriteClipped();
      }
    }
    pcVar6 = (code *)EnterCriticalSection;
    uVar7 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    local_10c = local_104 + 0xadc;
    iVar1 = PeekPacketChecksumState((void *)(local_104 + 0xadc));
    pcVar5 = (code *)LeaveCriticalSection;
    SUBFIELD(uStack_110,3,undefined1) = iVar1 != 0;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (SUBFIELD(uStack_110,3,undefined1) != '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(local_104 + 0xadc));
      SUBFIELD(uStack_110,3,undefined1) = iVar1 < 1;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (SUBFIELD(uStack_110,3,undefined1) == '\0') {
        if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock(local_10c);
      }
      else {
        if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock(local_10c);
      }
      _sprintf(local_100,&DAT_00555654);
      BlitSpriteText();
      uVar7 = 1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
    puVar12 = &g_valueGuardLock;
    (*pcVar6)();
    uStack_110 = local_108 + 0x19d8;
    PeekPacketChecksumState((void *)(local_104 + 0x19d8));
    cVar11 = '\0';
    (*pcVar5)();
    cVar14 = (char)((uint)unaff_EBP >> 0x18);
    if ((cVar14 != '\0') && (uVar7 < 3)) {
      (*pcVar6)();
      PeekPacketChecksumState((void *)(local_104 + 0x19d8));
      (*pcVar5)();
      if (cVar14 == '\0') {
        if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock(local_104 + 0x19d8);
      }
      else {
        if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock(local_104 + 0x19d8);
      }
      _sprintf((char *)&local_108,&DAT_00555654);
      BlitSpriteText(0x28,&local_108);
      uVar7 = uVar7 + 1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
    puVar10 = &g_valueGuardLock;
    (*pcVar6)();
    iVar1 = uStack_110;
    iVar2 = uStack_110 + 0xf24;
    iVar3 = PeekPacketChecksumState((void *)(local_104 + 0xf24));
    cVar14 = '\0';
    uVar8 = CONCAT13(iVar3 != 0,unaff_ESI);
    (*pcVar5)();
    cVar13 = (char)((uint)unaff_EDI >> 0x18);
    if ((cVar13 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&g_valueGuardLock);
      PeekPacketChecksumState((void *)(local_104 + 0xf24));
      puVar12 = (undefined *)((uint)puVar12 & 0xffffff);
      (*pcVar5)(&g_valueGuardLock);
      if (cVar13 == '\0') {
        if ((g_screenSurface != 0) && (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0xd), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(0xd,iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0xd,iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22,0x2713);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        if ((g_screenSurface != 0) && (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0xc), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(0xc,iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0xc,iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22,0x2713);
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
    puVar9 = &g_valueGuardLock;
    (*pcVar6)(&g_valueGuardLock);
    iVar2 = iVar1 + 0x206c;
    iVar3 = PeekPacketChecksumState((void *)(local_104 + 0x1148));
    cVar13 = '\0';
    uVar8 = CONCAT13(iVar3 != 0,(int3)puVar12);
    (*pcVar5)();
    if ((cVar11 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&g_valueGuardLock);
      PeekPacketChecksumState((void *)(local_104 + 0x1148));
      puVar10 = (undefined *)((uint)puVar10 & 0xffffff);
      (*pcVar5)(&g_valueGuardLock);
      if (cVar11 == '\0') {
        if ((g_screenSurface != 0) && (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0xf), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(0xf,iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0xf,iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22,0x2713);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        if ((g_screenSurface != 0) && (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0xe), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(0xe,iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0xe,iVar4 + 0x7d,iVar2 + uVar7 * 0x12 + 0x22,0x2713);
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
    puVar12 = &g_valueGuardLock;
    (*pcVar6)(&g_valueGuardLock);
    iVar1 = iVar1 + 0x33d8;
    iVar2 = PeekPacketChecksumState((void *)(local_104 + 0x136c));
    cVar11 = '\0';
    uVar8 = CONCAT13(iVar2 != 0,(int3)puVar10);
    (*pcVar5)();
    if ((cVar14 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&g_valueGuardLock);
      PeekPacketChecksumState((void *)(local_104 + 0x136c));
      puVar9 = (undefined *)((uint)puVar9 & 0xffffff);
      (*pcVar5)(&g_valueGuardLock);
      if (cVar14 == '\0') {
        iVar2 = iVar1 + uVar7 * 0x12;
        if ((g_screenSurface != 0) && (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0x11), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(0x11,iVar4 + 0x7d,iVar2 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0x11,iVar4 + 0x7d,iVar2 + 0x22,0x2713);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        iVar2 = iVar1 + uVar7 * 0x12;
        if ((g_screenSurface != 0) && (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0x10), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(0x10,iVar4 + 0x7d,iVar2 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0x10,iVar4 + 0x7d,iVar2 + 0x22,0x2713);
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
    (*pcVar6)(&g_valueGuardLock);
    iVar1 = iVar1 + 0x1590;
    iVar2 = PeekPacketChecksumState((void *)(local_104 + 0x1590));
    uVar8 = CONCAT13(iVar2 != 0,(int3)puVar9);
    (*pcVar5)(&g_valueGuardLock);
    if ((cVar13 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&g_valueGuardLock);
      PeekPacketChecksumState((void *)(local_104 + 0x1590));
      puVar12 = (undefined *)((uint)puVar12 & 0xffffff);
      (*pcVar5)(&g_valueGuardLock);
      if (cVar13 == '\0') {
        iVar2 = iVar1 + uVar7 * 0x12;
        if ((g_screenSurface != 0) && (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0x13), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(0x13,iVar4 + 0x7d,iVar2 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0x13,iVar4 + 0x7d,iVar2 + 0x22,0x2713);
          }
        }
        iVar2 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        iVar2 = iVar1 + uVar7 * 0x12;
        if ((g_screenSurface != 0) && (iVar3 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0x12), iVar3 != 0)) {
          if (*(char *)(iVar3 + 0x18) == '\x01') {
            BlitSprite16bpp(0x12,iVar4 + 0x7d,iVar2 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0x12,iVar4 + 0x7d,iVar2 + 0x22,0x2713);
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
    (*pcVar6)(&g_valueGuardLock);
    iVar1 = iVar1 + 0xd00;
    iVar2 = PeekPacketChecksumState((void *)(local_104 + 0xd00));
    uVar8 = CONCAT13(iVar2 != 0,(int3)puVar12);
    (*pcVar5)(&g_valueGuardLock);
    if ((cVar11 != '\0') && (uVar7 < 3)) {
      (*pcVar6)(&g_valueGuardLock);
      PeekPacketChecksumState((void *)(local_104 + 0xd00));
      (*pcVar5)(&g_valueGuardLock);
      if (cVar11 == '\0') {
        if ((g_screenSurface != 0) && (iVar2 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0x15), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(0x15,iVar4 + 0x7d,iVar1 + uVar7 * 0x12 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0x15,iVar4 + 0x7d,iVar1 + uVar7 * 0x12 + 0x22,0x2713);
          }
        }
        iVar1 = PeekChecksumStateUnderLock(uVar8);
      }
      else {
        if ((g_screenSurface != 0) && (iVar2 = FindSpriteFrame((int)&g_spriteRegistry,0x2713,0x14), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(0x14,iVar4 + 0x7d,iVar1 + uVar7 * 0x12 + 0x22,0x2713);
          }
          else {
            BlitSpriteClipped(0x14,iVar4 + 0x7d,iVar1 + uVar7 * 0x12 + 0x22,0x2713);
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
    (*pcVar6)(&g_valueGuardLock);
    PeekPacketChecksumState((void *)(local_104 + 0x17b4));
    (*pcVar5)(&g_valueGuardLock);
    if ((SUBFIELD(uStack_110,3,undefined1) != '\0') && (uVar7 < 3)) {
      (*pcVar6)();
      PeekPacketChecksumState((void *)(local_104 + 0x17b4));
      (*pcVar5)();
      if (SUBFIELD(uStack_110,3,undefined1) == '\0') {
        if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock(local_104 + 0x17b4);
      }
      else {
        if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp();
          }
          else {
            BlitSpriteClipped();
          }
        }
        PeekChecksumStateUnderLock(local_104 + 0x17b4);
      }
      _sprintf(local_100,&DAT_00555654);
      BlitSpriteText();
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    }
  }
  else {
    if ((g_screenSurface != 0) && (iVar1 = FindSpriteFrame(), iVar1 != 0)) {
      if (*(char *)(iVar1 + 0x18) == '\x01') {
        BlitSprite16bpp();
      }
      else {
        BlitSpriteClipped();
      }
    }
    iVar1 = 3;
    do {
      /* BlitRLESprite's args were dropped entirely here too - objdump at
       * this call site (0x44a2ab) shows ECX = ebp+0xb (this file's own
       * iVar4, recomputed fresh via `lea` each of the 3 loop passes from
       * an unchanged ebp - it does not advance across iterations here),
       * and EAX = esi = param_2*0x78 + param_1 + 0x2d114 (a struct field
       * table indexed by param_2, matching this loop's later
       * `iVar3 + g_clientContext`-style indexing pattern elsewhere in
       * this file). Per real disassembly the rleData/x stack arg do
       * advance by 0x18/0xe each of the 3 passes, but the raw decompile
       * collapsed the loop to a single call-site text with no per-
       * iteration locals to carry that - using the first iteration's
       * values here, which is the most faithful recovery obtainable
       * without inventing new loop state. The 2nd stack arg (x) reads
       * the same uninitialized [esp+0x18]-based local as the other call
       * site, so it's left as a placeholder; color = 0xffff. */
      BlitRLESprite(iVar4 + 0xb,0,0xffff,(byte *)(param_2 * 0x78 + param_1 + 0x2d114));
      iVar1 = iVar1 + -1;
      pcVar5 = (code *)LeaveCriticalSection;
      pcVar6 = (code *)EnterCriticalSection;
    } while (iVar1 != 0);
  }
  (*pcVar6)();
  iVar1 = PeekPacketChecksumState((void *)(local_104 + 0x694));
  (*pcVar5)();
  if (iVar1 == 0) {
    if ((g_screenSurface == 0) || (iVar1 = FindSpriteFrame(), iVar1 == 0)) goto LAB_0044af5f;
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp();
      goto LAB_0044af5f;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(local_104 + 0x694));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(acStack_88,(char *)&PTR_DAT_00555650);
    FUN_0044c460(iVar4 + 0x23,0x3c,acStack_88,8,0xa,4,0x118,0x1f4);
    if ((g_screenSurface == 0) || (iVar1 = FindSpriteFrame(), iVar1 == 0)) goto LAB_0044af5f;
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp();
      goto LAB_0044af5f;
    }
  }
  BlitSpriteClipped();
LAB_0044af5f:
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(local_104 + 0x8b8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 == 0) {
    if (g_screenSurface == 0) {
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
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    PeekPacketChecksumState((void *)(local_104 + 0x8b8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(acStack_88,(char *)&PTR_DAT_00555650);
    FUN_0044c460(iVar4 + 0x23,0x32,acStack_88,8,0xa,4,0x117,0x1f4);
    if (g_screenSurface == 0) {
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

