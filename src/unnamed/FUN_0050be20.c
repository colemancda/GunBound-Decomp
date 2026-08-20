/* FUN_0050be20 - 0x0050be20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 36 argless PeekPacketChecksumState() calls (worklist 36:36).
 * Twin of FUN_0050ae40 with the state object's own slot arrays: frame
 * [esp+0x18] = local_84 = g_gameStateVTableArray[7] (written at 0x50be34,
 * `mov [esp+0x10],eax` two pushes deep - the older BlitRLESprite note
 * below that says the slot is never written missed the push depth; its
 * 4th arg is therefore local_84+0x331c4 (0x50c138) and is now passed).
 * Cells: g_clientContext + local_88 + 0x5f4ab8 (equipped array,
 * 0x50beae); the catalog record *(ctx+0x44e20) + *(param_1+0x94)*0x450 at
 * +0x22c (0x50bfbd/0x50c019/0x50c0f4); then eight 4-peek blocks on
 * local_84 + 0x33624/0x34520/0x33a6c/0x33c90/0x33eb4/0x340d8/0x33848/
 * 0x342fc (address order, confirmed by the BlitSpriteClipped ids 8..0x17
 * the C keeps; each block's follow-up peeks re-read EDI, which holds the
 * block's cell for the whole block).
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
  if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame((int)&DAT_00ea0e18,0x2712,1), iVar1 != 0)) {
    if (*(char *)(iVar1 + 0x18) == '\x01') {
      BlitSprite16bpp(param_2,param_3);
    }
    else {
      BlitSpriteClipped(1,param_2,param_3,0x2712);
    }
  }
  local_88 = 0;
LAB_0050be92:
  iVar1 = *(int *)(param_1 + 0x94);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + local_88 + 0x5f4ab8));
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
        BlitSpriteClipped(7,param_2,param_3 + 4,0x2713);
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
  iVar1 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + *(int *)(param_1 + 0x94) * 0x450 + 0x22c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = iVar1 >> 0x10 & 0xf;
  uVar4 = uVar3 * 2;
  if (uVar3 != 3) {
    if (*(uint *)(g_clientContext + 0x44e24) <= *(uint *)(param_1 + 0x94)) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + *(int *)(param_1 + 0x94) * 0x450 + 0x22c));
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
    uVar3 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x44e20) + *(int *)(param_1 + 0x94) * 0x450 + 0x22c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* BlitRLESprite's `this` (1st arg) recovered via objdump at this call
     * site (orig 0x50c142): ECX is loaded from [esp+0xa4] (this file's own
     * param_2) then `add ecx,0x18` right before the call - so `this` is
     * param_2+0x18, matching the surrounding code's x-cursor-offset style
     * (BlitSprite16bpp calls just above/below use param_2+/-offsets too).
     * The 4th arg (rleData) could NOT be recovered with confidence: EAX is
     * loaded from `[esp+0x18]` at 0x50c10d, but tracing every write to the
     * stack frame in this function (objdump 0x50be20-0x50c220) shows that
     * exact slot (ESP0+0x8, ESP0 = esp right after the prologue's
     * `sub esp,0x8c`) is never written anywhere - it's left as whatever
     * was on the stack before this function's own prologue ran (a true
     * uninitialized/leftover value, not a resolvable local or stack arg;
     * confirmed by cross-checking sibling reads at the same call site -
     * ECX/EDX at [esp+0xa4]/[esp+0xa8] cleanly resolve to param_2/param_3,
     * but nothing in this disassembly window ever targets [esp+0x18]).
     * Left as a placeholder per the recovery methodology's "genuine
     * ambiguity" exception. */
    BlitRLESprite(param_2 + 0x18,param_3 + 3,(-(uint)((uVar3 & 0x20000000) != 0x20000000) & 0x480d) + 0xb7f2,(byte *)(local_84 + 0x331c4));
    local_8c = 2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33624));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar1 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33624));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar1 < 1) {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,9), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp(param_2 + 0x99,param_3 + 2);
          }
          else {
            BlitSpriteClipped(9,param_2 + 0x99,param_3 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33624));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar1 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,8), iVar1 != 0)) {
          if (*(char *)(iVar1 + 0x18) == '\x01') {
            BlitSprite16bpp(param_2 + 0x99,param_3 + 2);
          }
          else {
            BlitSpriteClipped(8,param_2 + 0x99,param_3 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33624));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(local_80,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,local_80,2,6);
      local_8c = 1;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x34520));
    pcVar5 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar1 != 0) && (local_8c < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x34520));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_88 = local_8c * 0x19 + param_2;
      if (iVar1 < 0) {
        iVar1 = local_88 + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0xa), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1,param_3 + 2);
          }
          else {
            BlitSpriteClipped(10,iVar1,param_3 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x34520));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        iVar1 = local_88 + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0xb), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1,param_3 + 2);
          }
          else {
            BlitSpriteClipped(0xb,iVar1,param_3 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x34520));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(local_80,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,local_80,2,6);
      local_8c = local_8c + -1;
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33a6c));
    puVar8 = &DAT_005a9068;
    (*pcVar5)();
    if ((iVar1 != 0) && (unaff_EBX < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33a6c));
      (*pcVar5)(&DAT_005a9068);
      local_8c = unaff_EBX * 0x19 + param_1;
      if (iVar1 < 0) {
        iVar1 = local_8c + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0xc), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1,param_2 + 2);
          }
          else {
            BlitSpriteClipped(0xc,iVar1,param_2 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33a6c));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        iVar1 = local_8c + 0x67;
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0xd), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1,param_2 + 2);
          }
          else {
            BlitSpriteClipped(0xd,iVar1,param_2 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33a6c));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_84,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&local_84,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33c90));
    puVar7 = &DAT_005a9068;
    (*pcVar5)();
    if ((iVar1 != 0) && (unaff_EBP < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState((void *)(local_84 + 0x33c90));
      (*pcVar5)(&DAT_005a9068);
      iVar1 = unaff_EBP * 0x19 + unaff_retaddr;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0xe), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,param_1 + 2);
          }
          else {
            BlitSpriteClipped(0xe,iVar1 + 0x67,param_1 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33c90));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0xf), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,param_1 + 2);
          }
          else {
            BlitSpriteClipped(0xf,iVar1 + 0x67,param_1 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33c90));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_88,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&local_88,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33eb4));
    puVar6 = &DAT_005a9068;
    (*pcVar5)(&DAT_005a9068);
    if ((iVar1 != 0) && (unaff_ESI < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState((void *)(local_84 + 0x33eb4));
      (*pcVar5)(&DAT_005a9068);
      iVar1 = unaff_ESI * 0x19 + iStack_4;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0x10), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,unaff_retaddr + 2);
          }
          else {
            BlitSpriteClipped(0x10,iVar1 + 0x67,unaff_retaddr + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33eb4));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0x11), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,unaff_retaddr + 2);
          }
          else {
            BlitSpriteClipped(0x11,iVar1 + 0x67,unaff_retaddr + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33eb4));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf((char *)&local_8c,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&local_8c,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x340d8));
    (*pcVar5)(&DAT_005a9068);
    if ((iVar1 != 0) && (unaff_EDI < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState((void *)(local_84 + 0x340d8));
      (*pcVar5)(&DAT_005a9068);
      iVar1 = unaff_EDI * 0x19 + iStack_8;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0x12), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_4 + 2);
          }
          else {
            BlitSpriteClipped(0x12,iVar1 + 0x67,iStack_4 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x340d8));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0x13), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_4 + 2);
          }
          else {
            BlitSpriteClipped(0x13,iVar1 + 0x67,iStack_4 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x340d8));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(&stack0xffffff70,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&stack0xffffff70,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33848));
    (*pcVar5)(&DAT_005a9068);
    if ((iVar1 != 0) && ((int)puVar8 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState((void *)(local_84 + 0x33848));
      (*pcVar5)(&DAT_005a9068);
      iVar1 = (int)puVar8 * 0x19 + iStack_c;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0x14), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_8 + 2);
          }
          else {
            BlitSpriteClipped(0x14,iVar1 + 0x67,iStack_8 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33848));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0x15), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_8 + 2);
          }
          else {
            BlitSpriteClipped(0x15,iVar1 + 0x67,iStack_8 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x33848));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      _sprintf(&stack0xffffff6c,&DAT_00555654,iVar1);
      BlitSpriteText(0x28,&stack0xffffff6c,2,6);
      pcVar5 = (code *)LeaveCriticalSection;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x342fc));
    (*pcVar5)(&DAT_005a9068);
    if ((iVar1 != 0) && ((int)puVar7 < 3)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState((void *)(local_84 + 0x342fc));
      (*pcVar5)(&DAT_005a9068);
      iVar1 = (int)puVar6 * 0x19 + iStack_14;
      if (iVar2 < 0) {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0x16), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_10 + 2);
          }
          else {
            BlitSpriteClipped(0x16,iVar1 + 0x67,iStack_10 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x342fc));
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = -iVar1;
      }
      else {
        if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame((int)&DAT_00ea0e18,0x2713,0x17), iVar2 != 0)) {
          if (*(char *)(iVar2 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar1 + 0x67,iStack_10 + 2);
          }
          else {
            BlitSpriteClipped(0x17,iVar1 + 0x67,iStack_10 + 2,0x2713);
          }
        }
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar1 = PeekPacketChecksumState((void *)(local_84 + 0x342fc));
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

