/* RenderMobile - 0x00462900 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00462a32) */

void __fastcall RenderMobile(int param_1)

{
  int iVar1;
  int *piVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  char *pcVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  undefined4 *unaff_FS_OFFSET;
  bool bVar15;
  uint local_930;
  undefined4 local_928;
  char local_91c [128];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053a146;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uVar6 = *(uint *)(param_1 + 8);
  uVar4 = uVar6 >> 2 & 1;
  iVar5 = *(int *)(g_clientContext + 0x1fe1c + uVar4 * 4);
  iVar10 = *(int *)(g_clientContext + 0x1fe24 + uVar4 * 4);
  cVar3 = PeekPacketChecksumBool();
  iVar8 = g_clientContext;
  if (cVar3 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 == 2) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((*(uint *)(param_1 + 8) & 7) == uVar6) {
        iVar5 = *(int *)(g_clientContext + 0x1fe2c);
        iVar10 = *(int *)(g_clientContext + 0x1fe30);
        if (iVar5 != 0) {
          BlitSpriteDirect(iVar5,iVar10);
          BlitSpriteDirect(iVar10 / 2 + iVar5,iVar10);
        }
      }
    }
  }
  else {
    uVar4 = *(uint *)(param_1 + 8) >> 2 & 1;
    uVar13 = (uVar6 & 3) / 2;
    iVar14 = (uVar6 & 1) * 2;
    if (*(int *)(param_1 + 0x24) == 0xe) {
      uVar7 = 0xffffffff;
    }
    else {
      uVar7 = *(undefined4 *)(param_1 + 0x18);
    }
    BlitSpriteAttached(uVar7,*(undefined4 *)(param_1 + 0x68),
                 (*(int *)(g_clientContext + 0x1fe4c + uVar4 * 4) * uVar13 + iVar14) * 0x80 +
                 *(int *)(g_clientContext + 0x1fe44 + uVar4 * 4),iVar10);
    uVar6 = *(uint *)(param_1 + 8) >> 2 & 1;
    if (*(int *)(param_1 + 0x24) == 0xe) {
      uVar7 = 0xffffffff;
    }
    else {
      uVar7 = *(undefined4 *)(param_1 + 0x18);
    }
    uVar6 = BlitSpriteAttached(uVar7,*(undefined4 *)(param_1 + 0x68),
                         (*(int *)(iVar8 + 0x1fe5c + uVar6 * 4) * uVar13 + iVar14) * 0x80 +
                         *(int *)(iVar8 + 0x1fe54 + uVar6 * 4),iVar10);
    *(uint *)(iVar8 + ((*(uint *)(param_1 + 8) & 7) + 0x154c) * 0x18) = uVar6 & 0xff;
    if (((iVar5 != 0) && (*(char *)(param_1 + 0xae14) == '\0')) &&
       (cVar3 = PeekPacketChecksumBool(), cVar3 != '\x01')) {
      cVar3 = PeekPacketChecksumBool();
      iVar8 = g_clientContext;
      if (cVar3 != '\0') {
        *(undefined1 *)((*(uint *)(param_1 + 8) & 7) + 0x1fe94 + g_clientContext) = 0;
      }
      *(undefined4 *)(iVar8 + 0x1fe6c + (*(uint *)(param_1 + 8) & 7) * 4) = 1;
      if (*(int *)(param_1 + 0x24) == 0xe) {
        *(undefined4 *)(iVar8 + 0x1fe6c + (*(uint *)(param_1 + 8) & 7) * 4) = 0;
      }
      cVar3 = PeekPacketChecksumBool();
      iVar8 = g_clientContext;
      if (cVar3 != '\0') {
        *(undefined4 *)(g_clientContext + 0x1fe6c + (*(uint *)(param_1 + 8) & 7) * 4) = 2;
      }
      iVar1 = param_1 + 0x90c;
      *(undefined1 *)((*(uint *)(param_1 + 8) & 7) + 0x1fe8c + iVar8) = 1;
      uVar7 = PeekChecksumStateUnderLock(iVar1);
      *(undefined4 *)(g_clientContext + 0x1ff0c + (*(uint *)(param_1 + 8) & 7) * 0x18) = uVar7;
      uVar7 = PeekChecksumStateUnderLock(param_1 + 0xb30);
      *(undefined4 *)(g_clientContext + 0x1ff10 + (*(uint *)(param_1 + 8) & 7) * 0x18) = uVar7;
      if (*(int *)(param_1 + 0x24) == 0xd) {
        iVar8 = 0;
      }
      else {
        iVar8 = PeekChecksumStateUnderLock(param_1 + 0x209c);
        iVar8 = -iVar8;
      }
      *(int *)(g_clientContext + 0x1ff14 + (*(uint *)(param_1 + 8) & 7) * 0x18) = iVar8;
      uVar6 = PacketChecksumEquals(param_1 + 0x1c54,1);
      iVar8 = g_clientContext;
      *(uint *)(g_clientContext + 0x1ff18 + (*(uint *)(param_1 + 8) & 7) * 0x18) = uVar6 & 0xff;
      if (*(int *)(iVar8 + 0x1ff14 + (*(uint *)(param_1 + 8) & 7) * 0x18) < 0) {
        piVar2 = (int *)(iVar8 + 0x1ff14 + (*(uint *)(param_1 + 8) & 7) * 0x18);
        iVar8 = PeekChecksumStateUnderLock(&DAT_00e9bed8);
        *piVar2 = *piVar2 + iVar8;
      }
      iVar9 = PeekChecksumStateUnderLock(param_1 + 0x1a2c);
      iVar8 = g_clientContext;
      *(undefined4 *)(g_clientContext + 0x1ff1c + (*(uint *)(param_1 + 8) & 7) * 0x18) =
           *(undefined4 *)(&DAT_0056d468 + (iVar9 * 0x1e + *(int *)(param_1 + 0x24)) * 4);
      BlitSpriteDirect((uVar13 * iVar10 + iVar14) * 0x80 + iVar5,iVar10);
      if (*(int *)(iVar8 + 0x1fe34 + (*(uint *)(param_1 + 8) >> 2 & 1) * 4) != 0) {
        uVar6 = *(uint *)(param_1 + 8) >> 2 & 1;
        iVar5 = *(int *)(iVar8 + 0x1fe3c + uVar6 * 4);
        BlitSpriteDirect((iVar5 * uVar13 + iVar14) * 0x80 + *(int *)(iVar8 + 0x1fe34 + uVar6 * 4),iVar5)
        ;
      }
      cVar3 = CheckGuardedBoolAnd(*(int *)(param_1 + 0x24) != 0xe);
      iVar5 = g_clientContext;
      if (cVar3 != '\0') {
        *(undefined4 *)(g_clientContext + 0x227a8) = 1;
        uVar7 = EncodeChecksumNegate(param_1 + 0x62f8,local_89c);
        local_4 = 0;
        uVar7 = EncodeChecksumDeltaAdd(uVar7,local_678,0x5a);
        local_4 = 1;
        PeekChecksumStateUnderLock(uVar7);
        FUN_004ead90();
        uVar7 = FloatToInt64();
        uVar7 = EncodeChecksumDeltaAdd(iVar1,local_454,uVar7);
        local_4 = 2;
        uVar7 = PeekChecksumStateUnderLock(uVar7);
        *(undefined4 *)(g_clientContext + 0x227ac) = uVar7;
        local_4 = 1;
        ScrubChecksumGuard();
        local_4 = 0;
        ScrubChecksumGuard();
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        uVar7 = EncodeChecksumNegate(param_1 + 0x62f8,local_454);
        local_4 = 3;
        uVar7 = EncodeChecksumDeltaAdd(uVar7,local_678,0x5a);
        local_4 = 4;
        PeekChecksumStateUnderLock(uVar7);
        FUN_004ead70();
        uVar7 = FloatToInt64();
        uVar7 = EncodeChecksumDeltaSub(param_1 + 0xb30,local_89c,uVar7);
        local_4 = 5;
        uVar7 = PeekChecksumStateUnderLock(uVar7);
        *(undefined4 *)(g_clientContext + 0x227b0) = uVar7;
        local_4 = 4;
        ScrubChecksumGuard();
        local_4 = 3;
        ScrubChecksumGuard();
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        iVar5 = g_clientContext;
        *(undefined4 *)(g_clientContext + 0x227b4) = *(undefined4 *)(param_1 + 0xb094);
        *(int *)(iVar5 + 0x227b8) = *(int *)(param_1 + 0xb098) << 0x18;
        *(undefined4 *)(iVar5 + 0x227bc) = *(undefined4 *)(param_1 + 0xb0a0);
      }
      uVar7 = EncodeChecksumDeltaSub(iVar1,local_454,*(undefined4 *)(&g_nCameraX + iVar5));
      local_4 = 6;
      uVar7 = EncodeChecksumDeltaAdd(uVar7,local_678,400);
      local_4 = 7;
      uVar7 = EncodeChecksumDeltaSub(uVar7,local_89c,0x29);
      local_4 = 8;
      iVar5 = PeekChecksumStateUnderLock(uVar7);
      /* BlitRLESprite's dropped param_1/rleData (below, ~line 353-362)
       * are recovered from this on-screen X position before it gets
       * reused/reassigned for other purposes later in this function
       * (e.g. `iVar5 = param_1 + 0x6db0` at line ~238) - objdump shows
       * the register holding this exact value (stashed at [esp+0x20])
       * still live and unclobbered at every BlitRLESprite call site
       * below. Captured here into iVar15 since Ghidra's `iVar5` name
       * gets recycled for unrelated values before those calls. */
      iVar15 = iVar5;
      local_4 = 7;
      ScrubChecksumGuard();
      local_4 = 6;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar7 = EncodeChecksumDeltaSub(param_1 + 0xb30,local_454,*(undefined4 *)(&g_nCameraY + g_clientContext));
      local_4 = 9;
      uVar7 = EncodeChecksumDeltaAdd(uVar7,local_678,0x10e);
      local_4 = 10;
      uVar7 = EncodeChecksumDeltaAdd(uVar7,local_89c,0x26);
      local_4 = 0xb;
      iVar10 = PeekChecksumStateUnderLock(uVar7);
      local_4 = 10;
      ScrubChecksumGuard();
      local_4 = 9;
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      if (500 < iVar10) {
        iVar8 = PeekChecksumStateUnderLock(&DAT_00796aa0);
        iVar10 = iVar10 - iVar8;
      }
      if (((DAT_00793530 <= iVar5 + 0x53) && (iVar5 <= DAT_0056df30)) &&
         ((DAT_00793534 <= iVar10 + 0x1f && (iVar10 <= DAT_0056df34)))) {
        uVar7 = EncodeChecksumDeltaSub(iVar1,local_678,*(undefined4 *)(&g_nCameraX + g_clientContext));
        local_4 = 0xc;
        uVar7 = EncodeChecksumDeltaAdd(uVar7,local_89c,400);
        local_4 = 0xd;
        PeekChecksumStateUnderLock(uVar7);
        local_4 = 0xc;
        ScrubChecksumGuard();
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        if (*(char *)(g_clientContext + 0x45122) == '\0') {
          iVar8 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
          bVar15 = *(int *)(param_1 + 0xae2c) == iVar8;
        }
        else {
          bVar15 = *(uint *)(param_1 + 0xae2c) == (uint)*(byte *)(g_clientContext + 0x3b6c0);
        }
        if ((*(int *)(param_1 + 0x24) != 0xe) &&
           (cVar3 = PacketChecksumNotEquals(g_clientContext + 0x45354,3), cVar3 != '\0')) {
          FUN_004eb7a0(iVar5 + 1,0x4e,5);
          FillScreenRect(0x4c,0x2965);
          iVar5 = param_1 + 0x6db0;
          iVar8 = param_1 + 0x6744;
          uVar7 = EncodeChecksumPairSum(iVar8,local_230,iVar5);
          local_4 = 0xe;
          iVar14 = PeekChecksumStateUnderLock(uVar7);
          if (0 < iVar14) {
            uVar7 = EncodeChecksumPairSum(iVar8,local_454,iVar5);
            local_4 = 0xf;
            local_928 = PeekChecksumStateUnderLock(uVar7);
          }
          else {
            local_928 = 1;
          }
          uVar7 = EncodeChecksumDeltaMul(param_1 + 0x6968,local_678,0x4c);
          local_4 = 0x10;
          uVar7 = EncodeChecksumDeltaDiv(uVar7,local_89c,local_928);
          local_4 = 0x11;
          uVar7 = PeekChecksumStateUnderLock(uVar7);
          local_4 = 0x10;
          ScrubChecksumGuard();
          local_4 = 0xf;
          ScrubChecksumGuard();
          local_4 = 0xe;
          if (0 < iVar14) {
            ScrubChecksumGuard();
          }
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          uVar11 = EncodeChecksumPairSum(iVar8,local_89c,iVar5);
          local_4 = 0x12;
          uVar11 = EncodeChecksumDeltaDiv(uVar11,local_230,3);
          local_4 = 0x13;
          cVar3 = CompareChecksumPair(param_1 + 0x6968,uVar11);
          local_4 = 0x12;
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          FillScreenRect(uVar7,(-(uint)(cVar3 != '\0') & 0x5af7) + 0x65a9);
          uVar7 = EncodeChecksumPairSum(iVar8,local_454,iVar5);
          local_4 = 0x14;
          iVar14 = PeekChecksumStateUnderLock(uVar7);
          if (0 < iVar14) {
            uVar7 = EncodeChecksumPairSum(iVar8,local_678,iVar5);
            local_4 = 0x15;
            uVar7 = PeekChecksumStateUnderLock(uVar7);
          }
          else {
            uVar7 = 1;
          }
          uVar11 = EncodeChecksumDeltaMul(param_1 + 0x6fd4,local_89c,0x4c);
          local_4 = 0x16;
          uVar7 = EncodeChecksumDeltaDiv(uVar11,local_230,uVar7);
          uVar11 = 0x21d8;
          local_4 = 0x17;
          uVar7 = PeekChecksumStateUnderLock(uVar7);
          FillScreenRect(uVar7,uVar11);
          local_4 = 0x16;
          ScrubChecksumGuard();
          local_4 = 0x15;
          ScrubChecksumGuard();
          local_4 = 0x14;
          if (0 < iVar14) {
            ScrubChecksumGuard();
          }
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
        }
        pcVar12 = (char *)(param_1 + 0xae22);
        if (*(char *)(param_1 + 0xae22) == '\0') {
          /* DrawSprite's arg was dropped as `in_EAX`, left unfixed:
           * objdump at this call site (0x463589) shows it needs
           * `*(int *)(param_1 + 0xae38)`, a field this decompiled
           * source never names anywhere else. See DrawSprite.c's
           * header comment. */
          DrawSprite(0);
          /* BlitRLESprite's dropped param_1 (x-cursor) and rleData were
           * recovered via objdump at this call site (0x4635ea): ECX =
           * iVar15+0x1c, EAX = param_1+0xae15 (a string field distinct
           * from the +0xae22 label - see BlitRLESprite.c's header
           * comment for the recovery method). */
          BlitRLESprite(iVar15 + 0x1c,iVar10 + 10,0,(byte *)(param_1 + 0xae15));
          /* Same recovery as above, at 0x463608: ECX = iVar15+0x1b,
           * EAX = param_1+0xae15 (unchanged from the call above). */
          BlitRLESprite(iVar15 + 0x1b,iVar10 + 9,(-(uint)bVar15 & 0x517) + 0xfae8,
                        (byte *)(param_1 + 0xae15));
        }
        else {
          do {
            cVar3 = *pcVar12;
            pcVar12 = pcVar12 + 1;
          } while (cVar3 != '\0');
          /* BlitRLESprite's dropped param_1 (x-cursor) at the two calls
           * below (0x4635a3/0x4635b4) is this label's on-screen width
           * folded into the base x-position: objdump shows
           * ECX = iVar15 + 2*(3*(strlen-1)+9) = iVar15 + 6*strlen + 12,
           * where strlen = pcVar12-(param_1+0xae22)-1 is the length of
           * the label string just scanned above. Captured into iVar16
           * here before pcVar12 gets reused for the digit buffer below
           * (see BlitRLESprite.c's header comment for the method). */
          iVar16 = iVar15 + (int)pcVar12 * 6 - (param_1 + 0xae22) * 6 + 6;
          iVar5 = *(int *)(param_1 + 0xae34);
          if (0x3e6 < iVar5) {
            iVar5 = 999;
          }
          iVar8 = *(int *)(param_1 + 0xae30);
          if (0x3e6 < iVar8) {
            iVar8 = 999;
          }
          _sprintf(local_91c,s___d__d__00555c88,iVar8,iVar5);
          pcVar12 = local_91c;
          local_930 = 0;
          do {
            cVar3 = *pcVar12;
            pcVar12 = pcVar12 + 1;
          } while (cVar3 != '\0');
          if (pcVar12 != local_91c + 1) {
            do {
              /* DrawSprite's arg was dropped as `in_EAX`, left unfixed:
               * objdump at this call site (0x46350b) shows EAX is one
               * of several loop-carried-register alternatives (keyed
               * on which digit-string char is being drawn) that this
               * decompiled loop body doesn't preserve across
               * iterations. See DrawSprite.c's header comment. */
              DrawSprite(0);
              local_930 = local_930 + 1;
              pcVar12 = local_91c;
              do {
                cVar3 = *pcVar12;
                pcVar12 = pcVar12 + 1;
              } while (cVar3 != '\0');
            } while (local_930 < (uint)((int)pcVar12 - (int)(local_91c + 1)));
          }
          /* BlitRLESprite's dropped param_1 (x-cursor) and rleData were
           * recovered via objdump at this call site (0x46354b): ECX =
           * iVar15+0x12, EAX = param_1+0xae22 (the label field just
           * scanned by the strlen loop above - see BlitRLESprite.c's
           * header comment for the recovery method). */
          BlitRLESprite(iVar15 + 0x12,iVar10 + 8,0,(byte *)(param_1 + 0xae22));
          iVar5 = (-(uint)bVar15 & 0x517) + 0xfae8;
          /* Same recovery as above, at 0x463578: ECX = iVar15+0x11,
           * EAX = param_1+0xae22 (unchanged from the call above). */
          BlitRLESprite(iVar15 + 0x11,iVar10 + 7,iVar5,(byte *)(param_1 + 0xae22));
          /* DrawSprite's arg was dropped as `in_EAX`, left unfixed:
           * objdump at this call site (0x4635cd) shows it needs the
           * same `*(int *)(param_1 + 0xae38)` field as the call above
           * (line ~307). See DrawSprite.c's header comment. */
          DrawSprite(0);
          /* BlitRLESprite's dropped param_1 (x-cursor) and rleData were
           * recovered via objdump at this call site (0x4635a3): ECX =
           * iVar16 (label-width-adjusted x-cursor computed above), EAX
           * = param_1+0xae15 (a string field distinct from the +0xae22
           * label - see BlitRLESprite.c's header comment). */
          BlitRLESprite(iVar16,iVar10 + 0x15,0,(byte *)(param_1 + 0xae15));
          /* Same recovery as above, at 0x4635b4: ECX = iVar16, EAX =
           * param_1+0xae15 (both unchanged from the call above). */
          BlitRLESprite(iVar16,iVar10 + 0x14,iVar5,(byte *)(param_1 + 0xae15));
        }
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

