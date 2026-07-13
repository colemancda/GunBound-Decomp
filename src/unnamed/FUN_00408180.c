/* FUN_00408180 - 0x00408180 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Type propagation algorithm not settling */

void FUN_00408180(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  code *pcVar12;
  int iVar13;
  uint uVar14;
  undefined4 *unaff_FS_OFFSET;
  bool bVar15;
  undefined **_Format;
  int local_1028;
  int local_1024 [2];
  uint local_101c;
  int local_1018 [2];
  undefined4 local_1010 [2];
  CHAR local_1008;
  char local_1007 [127];
  char local_f88 [128];
  undefined1 local_f08 [20];
  int local_ef4;
  undefined1 local_ce4 [20];
  int local_cd0;
  undefined1 local_ac0 [20];
  int local_aac;
  undefined1 local_89c [20];
  uint local_888;
  undefined1 local_678 [20];
  uint local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  uint local_21c;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053cf2a;
  *unaff_FS_OFFSET = &local_c;
  uStack_10 = 0x40819f;
  if (*(char *)(g_clientContext + 0x3b6c0) == -1) goto LAB_00409972;
  if ((((*(int *)(g_clientContext + 0x227bc) == 0xc0) ||
       (*(int *)(g_clientContext + 0x621e4) != *(int *)(g_clientContext + 0x621e0))) &&
      (cVar1 = PeekPacketChecksumBool(), cVar1 == '\x01')) && (cVar1 = PeekPacketChecksumBool(), cVar1 == '\0')) {
    cVar1 = PacketChecksumLessThan(*(int *)(g_clientContext + 0x621e0) + 0x60d4,0);
    if (cVar1 != '\0') {
      iVar3 = *(int *)(param_1 + 0x44);
      iVar13 = *(int *)(param_1 + 0x40);
      if ((DAT_0079352c != 0) && (iVar2 = FindSpriteFrame(), iVar2 != 0)) {
        if (*(char *)(iVar2 + 0x18) == '\x01') {
          BlitSprite16bpp(iVar13 + 4,iVar3 + 0x17);
        }
        else {
          BlitSpriteClipped(0xe2);
        }
      }
    }
    /* Both DrawSprite() calls below are missing their arg (dropped as
     * `in_EAX`), left unfixed here: objdump at 0x4082c6/0x4082e2 shows
     * both need the return value of the PeekChecksumStateUnderLock()
     * call just above, which this decompiled source discards - fixing
     * that call's own dropped return is a prerequisite. See
     * DrawSprite.c's header comment. */
    PeekChecksumStateUnderLock(*(int *)(g_clientContext + 0x621e0) + 0x60d4);
    DrawSprite(0);
    DrawSprite(0);
  }
  if (DAT_007933b8 == '\x01') {
    FUN_0040c8f0(0xca,0x21b,0);
    if ((*(char *)(DAT_007934e4 + 8) == '\0') ||
       (iVar3 = GetWindowTextA(*(HWND *)(DAT_007934e4 + 4),&local_1008,0x80), iVar3 == 0)) {
      local_1008 = '\0';
    }
    iVar3 = local_1024[0];
    if (local_1024[0] == -1) {
      pcVar4 = &local_1008;
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      iVar3 = (int)pcVar4 - (int)local_1007;
    }
    if (local_1018[0] == -1) {
      pcVar4 = &local_1008;
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      local_1018[0] = (int)pcVar4 - (int)local_1007;
    }
    FUN_004eb7a0(iVar3 * 6 + 0xca,local_1018[0] * 6 + iVar3 * -6 + 2,0xc);
    /* BlitRLESprite's 1st/4th args (this/rleData) were dropped in the raw
     * port - objdump at this call site (0x4083ac/0x4083a8) shows
     * ECX=0xcb (constant x-cursor) and EAX=&local_1008 (the edit-box
     * text buffer filled by GetWindowTextA above). */
    BlitRLESprite(0xcb,0x21c,0,(byte *)&local_1008);
    /* Same site, second call (0x4083c0/0x4083bc): ECX=0xca, EAX is still
     * the unclobbered &local_1008 pointer from the call above. */
    BlitRLESprite(0xca,0x21b,0xffe0,(byte *)&local_1008);
  }
  else {
    /* objdump at 0x4083df/0x4083da shows ECX=0xcb, EAX=&DAT_007933c0 -
     * the same chat-input text buffer used by GetWindowTextA/
     * SetWindowTextA elsewhere (FUN_00506e70.c/FUN_00507e30.c/
     * FUN_00507dc0.c). */
    BlitRLESprite(0xcb,0x21c,0,(byte *)&DAT_007933c0);
    /* Same site, second call (0x4083f8/0x4083f3): ECX=0xca, EAX still
     * &DAT_007933c0 (unclobbered). */
    BlitRLESprite(0xca,0x21b,0xffff,(byte *)&DAT_007933c0);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 == 1) {
    if (*(char *)(g_clientContext + 0x3b6c0) == '\x01') {
      /* The 3 DrawSprite() calls below (through LAB_0040855d) all have
       * the same dropped-arg/missing-prerequisite-fix shape as the pair
       * above: objdump (0x408491/0x40851b/0x40856c) shows each needs
       * `PeekChecksumStateUnderLock(...)`'s return value + 0xbd, which
       * this decompiled source discards every time. See DrawSprite.c's
       * header comment. */
      if ((*(int *)(param_1 + 0x3c) % 0x14 < 10) ||
         (cVar1 = PacketChecksumNotEquals(&DAT_0067e3d0 + g_clientContext,1), cVar1 != '\0')) {
        PeekChecksumStateUnderLock(&DAT_0067e3d0 + g_clientContext);
        DrawSprite(0);
      }
      if ((*(int *)(param_1 + 0x3c) % 0x14 < 10) ||
         (cVar1 = PacketChecksumNotEquals(&DAT_0067e5f4 + g_clientContext,1), cVar1 != '\0')) {
        PeekChecksumStateUnderLock(&DAT_0067e5f4 + g_clientContext);
LAB_0040855d:
        DrawSprite(0);
      }
    }
    else {
      if ((*(int *)(param_1 + 0x3c) % 0x14 < 10) ||
         (cVar1 = PacketChecksumNotEquals(&DAT_0067e3d0 + g_clientContext,1), cVar1 != '\0')) {
        PeekChecksumStateUnderLock(&DAT_0067e3d0 + g_clientContext);
        DrawSprite(0);
      }
      if ((*(int *)(param_1 + 0x3c) % 0x14 < 10) ||
         (cVar1 = PacketChecksumNotEquals(&DAT_0067e5f4 + g_clientContext,1), cVar1 != '\0')) {
        PeekChecksumStateUnderLock(&DAT_0067e5f4 + g_clientContext);
        goto LAB_0040855d;
      }
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 == 3) {
    if (*(char *)(g_clientContext + 0x3b6c0) == '\0') {
      uVar5 = PeekChecksumStateUnderLock(&DAT_0067e818 + g_clientContext);
      _sprintf(&local_1008,(char *)&PTR_DAT_00551ecc,uVar5);
      iVar3 = 1;
      iVar13 = 0x2b4;
      do {
        if (((((&local_1008)[iVar3] != ' ') &&
             (iVar2 = (&local_1008)[iVar3] + 0x8d, DAT_0079352c != 0)) && (-1 < iVar2)) &&
           (iVar6 = FindSpriteFrame(), iVar6 != 0)) {
          if (*(char *)(iVar6 + 0x18) == '\x01') {
            BlitSprite16bpp(iVar13,0x239);
          }
          else {
            BlitSpriteClipped(iVar2);
          }
        }
        iVar13 = iVar13 + 0x14;
        iVar3 = iVar3 + 1;
      } while (iVar13 < 0x2dc);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (((iVar13 <= iVar3) && (DAT_0079352c != 0)) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
        if (*(char *)(iVar3 + 0x18) == '\x01') {
          BlitSprite16bpp(0x2ac,0x239);
        }
        else {
          BlitSpriteClipped(199);
        }
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      _sprintf(&local_1008,(char *)&PTR_DAT_00551ecc,uVar5);
      iVar13 = 1;
      iVar3 = 0x2ed;
LAB_00408a10:
      if ((((&local_1008)[iVar13] != ' ') &&
          (uVar7 = (int)(&local_1008)[iVar13] + 0x8d, DAT_0079352c != 0)) && (-1 < (int)uVar7)) {
        iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
        uVar11 = *(uint *)(iVar2 + 4);
        while (uVar11 < 0x1f5) {
          if (uVar11 == 500) {
            iVar2 = *(int *)(iVar2 + 0x10);
            uVar11 = *(uint *)(iVar2 + 8);
            if (uVar11 <= uVar7) goto LAB_00408a62;
            break;
          }
          iVar2 = *(int *)(iVar2 + 0x1c);
          uVar11 = *(uint *)(iVar2 + 4);
        }
      }
      goto LAB_00408a9b;
    }
    uVar5 = PeekChecksumStateUnderLock(&DAT_0067e818 + g_clientContext);
    _sprintf(&local_1008,(char *)&PTR_DAT_00551ecc,uVar5);
    iVar3 = 1;
    iVar13 = 0x2ed;
    do {
      if (((((&local_1008)[iVar3] != ' ') &&
           (iVar2 = (&local_1008)[iVar3] + 0x8d, DAT_0079352c != 0)) && (-1 < iVar2)) &&
         (iVar6 = FindSpriteFrame(), iVar6 != 0)) {
        if (*(char *)(iVar6 + 0x18) == '\x01') {
          BlitSprite16bpp(iVar13,0x239);
        }
        else {
          BlitSpriteClipped(iVar2);
        }
      }
      iVar13 = iVar13 + 0x14;
      iVar3 = iVar3 + 1;
    } while (iVar13 < 0x315);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar13 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (((iVar13 <= iVar3) && (DAT_0079352c != 0)) && (iVar3 = FindSpriteFrame(), iVar3 != 0)) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x2e6,0x239);
      }
      else {
        BlitSpriteClipped(199);
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    _sprintf(&local_1008,(char *)&PTR_DAT_00551ecc,uVar5);
    iVar13 = 1;
    iVar3 = 0x2b4;
LAB_00408730:
    if ((((&local_1008)[iVar13] != ' ') &&
        (uVar7 = (int)(&local_1008)[iVar13] + 0x8d, DAT_0079352c != 0)) && (-1 < (int)uVar7)) {
      iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
      while (uVar11 < 0x1f5) {
        if (uVar11 == 500) {
          iVar2 = *(int *)(iVar2 + 0x10);
          uVar11 = *(uint *)(iVar2 + 8);
          if (uVar11 <= uVar7) goto LAB_00408782;
          break;
        }
        iVar2 = *(int *)(iVar2 + 0x1c);
        uVar11 = *(uint *)(iVar2 + 4);
      }
    }
    goto LAB_004087bb;
  }
  goto LAB_00408b80;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (uVar7 < uVar11) break;
LAB_00408a62:
    if (uVar11 == uVar7) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar3,0x239);
      }
      else {
        BlitSpriteClipped(uVar7);
      }
      break;
    }
  }
LAB_00408a9b:
  iVar3 = iVar3 + 0x14;
  iVar13 = iVar13 + 1;
  if (0x314 < iVar3) goto code_r0x00408aab;
  goto LAB_00408a10;
code_r0x00408aab:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar13 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar3 <= iVar13) && (DAT_0079352c != 0)) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar7 = *(uint *)(iVar3 + 4);
    while (uVar7 < 0x1f5) {
      if (uVar7 == 500) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar7 = *(uint *)(iVar3 + 8);
        if (uVar7 < 200) goto LAB_00408b33;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar7 = *(uint *)(iVar3 + 4);
    }
  }
  goto LAB_00408b80;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar7 = *(uint *)(iVar3 + 8);
    if (199 < uVar7) break;
LAB_00408b33:
    if (uVar7 == 199) {
      if (*(char *)(iVar3 + 0x18) != '\x01') goto LAB_00408b6e;
      BlitSprite16bpp(0x2e6,0x239);
      break;
    }
  }
  goto LAB_00408b80;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (uVar7 < uVar11) break;
LAB_00408782:
    if (uVar11 == uVar7) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(iVar3,0x239);
      }
      else {
        BlitSpriteClipped(uVar7);
      }
      break;
    }
  }
LAB_004087bb:
  iVar3 = iVar3 + 0x14;
  iVar13 = iVar13 + 1;
  if (0x2db < iVar3) goto code_r0x004087cb;
  goto LAB_00408730;
code_r0x004087cb:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar13 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar3 <= iVar13) && (DAT_0079352c != 0)) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar7 = *(uint *)(iVar3 + 4);
    while (uVar7 < 0x1f5) {
      if (uVar7 == 500) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar7 = *(uint *)(iVar3 + 8);
        if (uVar7 < 200) goto LAB_0040885f;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar7 = *(uint *)(iVar3 + 4);
    }
  }
  goto LAB_00408b80;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar7 = *(uint *)(iVar3 + 8);
    if (199 < uVar7) break;
LAB_0040885f:
    if (uVar7 == 199) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(0x2ac,0x239);
      }
      else {
LAB_00408b6e:
        BlitSpriteClipped(199);
      }
      break;
    }
  }
LAB_00408b80:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar3 == 2) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = GetPlayerRecordBySlot(g_clientContext);
    iVar3 = 0x42;
    local_101c = uVar7;
    if (((DAT_0079352c != 0) && (0x248 < DAT_0056df34)) && (DAT_00793534 < 0x24a)) {
      iVar13 = 0x2d4;
      if (0x2d4 < DAT_00793530) {
        iVar3 = 0x316 - DAT_00793530;
        iVar13 = DAT_00793530;
      }
      if (DAT_0056df30 < iVar13 + iVar3) {
        iVar3 = (DAT_0056df30 - iVar13) + 1;
      }
      if (0 < iVar3) {
        FillPixels16(DAT_0079352c + (DAT_005b3620 * 0x249 + iVar13) * 2,0xffff,iVar3);
      }
    }
    iVar3 = 0x42;
    if (((DAT_0079352c != 0) && (0x24e < DAT_0056df34)) && (DAT_00793534 < 0x250)) {
      iVar13 = 0x2d4;
      if (0x2d4 < DAT_00793530) {
        iVar3 = 0x316 - DAT_00793530;
        iVar13 = DAT_00793530;
      }
      if (DAT_0056df30 < iVar13 + iVar3) {
        iVar3 = (DAT_0056df30 - iVar13) + 1;
      }
      if (0 < iVar3) {
        FillPixels16(DAT_0079352c + (DAT_005b3620 * 0x24f + iVar13) * 2,0xffff,iVar3);
      }
    }
    DrawVLine();
    DrawVLine();
    FillScreenRect(0x40,0x2965);
    iVar3 = uVar7 + 0x6db0;
    iVar13 = uVar7 + 0x6744;
    EncodeChecksumPairSum(iVar13,local_f08,iVar3);
    local_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar2) {
      EncodeChecksumPairSum(iVar13,local_ce4,iVar3);
      local_4 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else {
      uVar5 = 1;
    }
    uVar8 = EncodeChecksumDeltaMul(uVar7 + 0x6968,local_454,0x40);
    local_4 = 2;
    EncodeChecksumDeltaDiv(uVar8,local_ac0,uVar5);
    local_4 = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_1010[0] = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 2;
    if (local_aac != 0) {
      local_1024[0] = local_aac << 4;
      local_1018[0] = 0x10;
      do {
        iVar6 = _rand();
        *(char *)(local_1024[0] + DAT_0079376c) = (char)iVar6;
        local_1024[0] = local_1024[0] + 1;
        local_1018[0] = local_1018[0] + -1;
      } while (local_1018[0] != 0);
      local_1024[0] = local_aac;
      TreeLowerBound(local_1018);
    }
    local_4 = 1;
    local_1018[0] = local_440;
    if (local_440 != 0) {
      iVar6 = local_440 << 4;
      local_1024[0] = 0x10;
      do {
        iVar9 = _rand();
        *(char *)(iVar6 + DAT_0079376c) = (char)iVar9;
        iVar6 = iVar6 + 1;
        local_1024[0] = local_1024[0] + -1;
      } while (local_1024[0] != 0);
      local_1024[0] = local_1018[0];
      TreeLowerBound(local_1018);
    }
    local_4 = 0;
    if ((0 < iVar2) && (local_cd0 != 0)) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(local_1024);
    }
    local_4 = 0xffffffff;
    local_1024[0] = local_ef4;
    if (local_ef4 != 0) {
      iVar2 = local_ef4 << 4;
      local_1028 = 0x10;
      do {
        iVar6 = _rand();
        *(char *)(iVar2 + DAT_0079376c) = (char)iVar6;
        iVar2 = iVar2 + 1;
        local_1028 = local_1028 + -1;
      } while (local_1028 != 0);
      TreeLowerBound(local_1024);
    }
    uVar5 = EncodeChecksumPairSum(iVar13,local_ce4,iVar3);
    local_4 = 4;
    EncodeChecksumDeltaDiv(uVar5,local_f08,3);
    local_4 = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    iVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = 4;
    if (local_ef4 != 0) {
      local_1028 = local_ef4 << 4;
      local_1024[0] = 0x10;
      do {
        iVar9 = _rand();
        *(char *)(local_1028 + DAT_0079376c) = (char)iVar9;
        local_1028 = local_1028 + 1;
        local_1024[0] = local_1024[0] + -1;
      } while (local_1024[0] != 0);
      TreeLowerBound(local_1024);
    }
    local_4 = 0xffffffff;
    local_1024[0] = local_cd0;
    if (local_cd0 != 0) {
      iVar9 = local_cd0 << 4;
      local_1028 = 0x10;
      do {
        iVar10 = _rand();
        *(char *)(iVar9 + DAT_0079376c) = (char)iVar10;
        iVar9 = iVar9 + 1;
        local_1028 = local_1028 + -1;
      } while (local_1028 != 0);
      TreeLowerBound(local_1024);
    }
    FillScreenRect(local_1010[0],(-(uint)(iVar2 < iVar6) & 0x5af7) + 0x65a9);
    uVar5 = EncodeChecksumPairSum(iVar13,local_230,iVar3);
    local_4 = 6;
    uVar8 = EncodeChecksumDeltaMul(local_101c + 0x6fd4,local_678,0x40);
    local_4 = 7;
    FUN_0040aea0(uVar8,local_89c,uVar5);
    local_4 = 8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FillScreenRect(uVar5,0x21d8);
    local_4 = 7;
    if (local_888 != 0) {
      iVar3 = local_888 << 4;
      iVar13 = 0x10;
      do {
        iVar2 = _rand();
        *(char *)(iVar3 + DAT_0079376c) = (char)iVar2;
        iVar3 = iVar3 + 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
      local_101c = local_888;
      TreeLowerBound(local_1010);
    }
    local_4 = 6;
    if (local_664 != 0) {
      iVar3 = local_664 << 4;
      iVar13 = 0x10;
      do {
        iVar2 = _rand();
        *(char *)(iVar3 + DAT_0079376c) = (char)iVar2;
        iVar3 = iVar3 + 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
      local_101c = local_664;
      TreeLowerBound(local_1010);
    }
    local_4 = 0xffffffff;
    if (local_21c != 0) {
      iVar3 = local_21c << 4;
      iVar13 = 0x10;
      do {
        iVar2 = _rand();
        *(char *)(iVar3 + DAT_0079376c) = (char)iVar2;
        iVar3 = iVar3 + 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
      local_101c = local_21c;
      TreeLowerBound(local_1010);
    }
  }
  iVar3 = 0;
  local_1018[0] = 0x216;
  iVar13 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar2 == -1) {
      iVar3 = iVar3 + 1;
    }
    iVar13 = iVar13 + 0x224;
  } while (iVar13 < 0x1120);
  local_1024[0] = 7;
LAB_00409310:
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar13 = PeekPacketChecksumState();
  pcVar12 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_101c = iVar13 * 0x224;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 != -1) {
    if (*(char *)(g_clientContext + 0x45122) == '\0') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      pcVar12 = (code *)LeaveCriticalSection;
      bVar15 = iVar2 == iVar13;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else {
      bVar15 = *(char *)(iVar13 + 0x4590c + g_clientContext) == *(char *)(g_clientContext + 0x3b6c0);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    (*pcVar12)(&DAT_005a9068);
    if (iVar13 == iVar2) {
      FillScreenRect(0x82,0x5327);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    (*pcVar12)(&DAT_005a9068);
    uVar7 = ((((iVar13 != iVar2) - 1 & 0xfffffff6) + 0x10d) - iVar3) + local_1024[0];
    if ((DAT_0079352c != 0) && (-1 < (int)uVar7)) {
      iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
      while (uVar11 < 0x1f5) {
        if (uVar11 == 500) {
          iVar2 = *(int *)(iVar2 + 0x10);
          uVar11 = *(uint *)(iVar2 + 8);
          if (uVar11 <= uVar7) goto LAB_00409499;
          break;
        }
        iVar2 = *(int *)(iVar2 + 0x1c);
        uVar11 = *(uint *)(iVar2 + 4);
      }
    }
    goto LAB_004094da;
  }
  goto LAB_004098e3;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (uVar7 < uVar11) break;
LAB_00409499:
    if (uVar11 == uVar7) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(6,local_1018[0]);
      }
      else {
        BlitSpriteClipped(uVar7);
      }
      break;
    }
  }
LAB_004094da:
  uVar7 = (uint)*(ushort *)(g_clientContext + 0x50116 + iVar13 * 2);
  if (DAT_0079352c != 0) {
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x66) {
      if (uVar11 == 0x65) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 <= uVar7) goto LAB_00409520;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
  }
LAB_00409561:
  iVar2 = local_1018[0] + 3;
  DrawFontString(iVar2,0);
  /* BlitRLESprite's 1st/4th args (this/rleData) were dropped in the raw
   * port - objdump at this call site (0x40959b/0x409589-0x409577) shows
   * ECX=0x2f (constant x-cursor, same as the just-preceding, also-
   * unfixed DrawFontString call's own dropped this) and EAX=esi,
   * unclobbered since the DrawFontString call above computed it as
   * (byte *)(g_clientContext + iVar13*0xd + 0x457f1) - the per-slot
   * player-name table entry (iVar13 is this function's running slot
   * index, see the *(ushort*)(g_clientContext+0x50116+iVar13*2) lookup
   * just above). */
  BlitRLESprite(0x2f,iVar2,(-(uint)bVar15 & 0x517) + 0xfae8,
                (byte *)(g_clientContext + iVar13 * 0xd + 0x457f1));
  local_1018[0] = local_1018[0] + -0xf;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_101c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (uVar7 != 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar2 == iVar13) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar13 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (*(char *)(*(int *)(g_clientContext + 0x621e0) + 0xae68) == '\0') {
        iVar13 = FUN_0045d150();
        iVar13 = iVar13 / 10;
      }
      _Format = &PTR_DAT_00551ed0;
    }
    else {
      uVar11 = (uint)((ulonglong)uVar7 * 0xcccccccd >> 0x20);
      uVar14 = local_101c / 10;
      if (*(char *)(*(int *)(g_clientContext + 0x621e0) + 0xae68) == '\0') {
        iVar13 = FUN_0045d150();
        uVar11 = (uint)((ulonglong)(iVar13 + uVar7) * 0xcccccccd >> 0x20);
      }
      iVar13 = uVar14 - (uVar11 >> 3);
      _Format = (undefined **)&DAT_00551ec4;
    }
    _sprintf(local_f88,(char *)_Format,iVar13);
    iVar13 = local_1018[0];
    iVar2 = 0;
    iVar6 = 0x7b;
LAB_00409741:
    cVar1 = local_f88[iVar2];
    if (cVar1 != ' ') {
      if (cVar1 == '-') {
        uVar7 = (uint)bVar15 * 2 + 0xdd;
        if (DAT_0079352c != 0) {
          iVar9 = *(int *)(DAT_00ea0e1c + 0x1c);
          uVar11 = *(uint *)(iVar9 + 4);
          while (uVar11 < 0x1f5) {
            if (uVar11 == 500) {
              iVar9 = *(int *)(iVar9 + 0x10);
              uVar11 = *(uint *)(iVar9 + 8);
              if (uVar11 <= uVar7) goto LAB_004097ba;
              break;
            }
            iVar9 = *(int *)(iVar9 + 0x1c);
            uVar11 = *(uint *)(iVar9 + 4);
          }
        }
      }
      else if (cVar1 == '+') {
        uVar7 = (uint)bVar15 * 2 + 0xdc;
        if (DAT_0079352c != 0) {
          iVar9 = *(int *)(DAT_00ea0e1c + 0x1c);
          uVar11 = *(uint *)(iVar9 + 4);
          while (uVar11 < 0x1f5) {
            if (uVar11 == 500) {
              iVar9 = *(int *)(iVar9 + 0x10);
              uVar11 = *(uint *)(iVar9 + 8);
              if (uVar11 <= uVar7) goto LAB_0040983a;
              break;
            }
            iVar9 = *(int *)(iVar9 + 0x1c);
            uVar11 = *(uint *)(iVar9 + 4);
          }
        }
      }
      else {
        uVar7 = (-(uint)bVar15 & 10) + 0x98 + (int)cVar1;
        if ((DAT_0079352c != 0) && (-1 < (int)uVar7)) {
          iVar9 = *(int *)(DAT_00ea0e1c + 0x1c);
          uVar11 = *(uint *)(iVar9 + 4);
          while (uVar11 < 0x1f5) {
            if (uVar11 == 500) {
              iVar9 = *(int *)(iVar9 + 0x10);
              uVar11 = *(uint *)(iVar9 + 8);
              if (uVar11 <= uVar7) goto LAB_004098b8;
              break;
            }
            iVar9 = *(int *)(iVar9 + 0x1c);
            uVar11 = *(uint *)(iVar9 + 4);
          }
        }
      }
    }
    goto LAB_004098d3;
  }
LAB_004098e3:
  local_1024[0] = local_1024[0] + -1;
  if (local_1024[0] < 0) goto code_r0x004098ed;
  goto LAB_00409310;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (uVar7 < uVar11) break;
LAB_00409520:
    if (uVar11 == uVar7) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        BlitSprite16bpp(0x13,local_1018[0]);
      }
      else {
        BlitSpriteClipped(uVar7);
      }
      break;
    }
  }
  goto LAB_00409561;
  while( true ) {
    iVar9 = *(int *)(iVar9 + 0x10);
    uVar11 = *(uint *)(iVar9 + 8);
    if (uVar7 < uVar11) break;
LAB_004098b8:
    if (uVar11 == uVar7) goto LAB_0040984b;
  }
  goto LAB_004098d3;
  while( true ) {
    iVar9 = *(int *)(iVar9 + 0x10);
    uVar11 = *(uint *)(iVar9 + 8);
    if (uVar7 < uVar11) break;
LAB_0040983a:
    if (uVar11 == uVar7) goto LAB_0040984b;
  }
  goto LAB_004098d3;
  while( true ) {
    iVar9 = *(int *)(iVar9 + 0x10);
    uVar11 = *(uint *)(iVar9 + 8);
    if (uVar7 < uVar11) break;
LAB_004097ba:
    if (uVar11 == uVar7) goto LAB_0040984b;
  }
LAB_004098d3:
  iVar6 = iVar6 + 5;
  iVar2 = iVar2 + 1;
  if (0x93 < iVar6) goto LAB_004098e3;
  goto LAB_00409741;
LAB_0040984b:
  if (*(char *)(iVar9 + 0x18) == '\x01') {
    BlitSprite16bpp(iVar6,iVar13 + 0x18);
  }
  else {
    BlitSpriteClipped(uVar7);
  }
  goto LAB_004098d3;
code_r0x004098ed:
  if (DAT_0079352c != 0) {
    iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar7 = *(uint *)(iVar3 + 4);
    while (uVar7 < 0x1b59) {
      if (uVar7 == 7000) {
        iVar3 = *(int *)(iVar3 + 0x10);
        uVar7 = *(uint *)(iVar3 + 8);
        if (uVar7 < 4) goto LAB_00409934;
        break;
      }
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar7 = *(uint *)(iVar3 + 4);
    }
  }
  goto LAB_00409972;
  while( true ) {
    iVar3 = *(int *)(iVar3 + 0x10);
    uVar7 = *(uint *)(iVar3 + 8);
    if (3 < uVar7) break;
LAB_00409934:
    if (uVar7 == 3) {
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        BlitSprite16bpp(*(undefined4 *)(g_clientContext + 0xebee8),0x239);
      }
      else {
        BlitSpriteClipped(3);
      }
      break;
    }
  }
LAB_00409972:
  *unaff_FS_OFFSET = local_c;
  return;
}

