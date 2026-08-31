/* DrawWindGauge - 0x00406990 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 36 argless PeekPacketChecksumState() calls.  Ghidra
 * reordered this function heavily -- the `if (iVar2 == 6) goto
 * LAB_00406f80` block, in particular, is emitted at a LOWER address than
 * the C lines above it -- so nothing could be matched by position.  Two
 * independent handles were used instead:
 *
 *   1. This port keeps Ghidra's LAB_004xxxxx / code_r0x004xxxxx labels,
 *      and each of those names the exact address its block starts at.
 *      Bracketing every call site between its enclosing pair of labels
 *      pins 29 of the 36 sites to a unique guard call: e.g. the block at
 *      LAB_00407df7 holds exactly nine sites (C868..C913) and exactly nine
 *      guard calls (0x407e2b..0x407f9e), in order.
 *   2. The other seven read EAX straight out of the delta helper called on
 *      the line above.  Those helpers RETURN THEIR SECOND ARGUMENT, so the
 *      cell is that call's own scratch guard regardless of where the block
 *      landed: local_ce4 (C140), local_89c (C190, C244), local_454 (C265),
 *      local_f08 (C290, C303, C334, C819) and local_230 (C931).  C140's
 *      pairing is independently confirmed by the 2026-07-15 FIXED note
 *      below it, which already named 0x406c13.
 *
 * The two do-loop peeks (C230, C234) are `lea ebx,[esi + <ctx> + 0x39f30]`
 * at 0x40718b / 0x4071c1, and ESI is the loop index the C spells iVar10 --
 * the same one the EncodeChecksumDeltaSub calls below them bias by
 * + 0x39f30 and + 0x3a154 (one 0x224 cell apart).  C925 is
 * `lea edi,[esi + <ctx> + 0x595d8]` with ESI already scaled by 0x224 at
 * 0x407fe6, i.e. exactly the `uVar11 * 0x224 + 0x595d8 + g_clientContext`
 * the encode three lines below it spells out by hand.
 *
 * FIXED (2026-07-15): all 6 SetClipRect calls dropped their 4 corner
 * args (see that file's own header for the recovery method). Two of the
 * six also had their real x2 argument's SOURCE dropped by Ghidra
 * entirely - not just the SetClipRect call, but the whole PeekPacket-
 * ChecksumState() return value the arg depends on (one direct, one via
 * a 3-call arithmetic expression `third*400/divisor+244` that never made
 * it into this decompile at all) - both reconstructed from angr
 * disassembly at their real call sites (iVar13/iVar14 locals added for
 * this).
 */
#include "ghidra_types.h"


void DrawWindGauge(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  uint uVar11;
  code *pcVar12;
  bool bVar13;
  int iVar13;
  int iVar14;
  int iPeekIndex; /* DROPPED-REG FIX 2026-08-28: PeekPacketChecksumState's
                     discarded result at 0x407269 / 0x40735a - the content
                     index, held in ECX at 0x40728d / 0x40737e (stored to
                     [esp+0x10] one push deep at 0x407273 / 0x407364 and read
                     back from the same slot after LeaveCriticalSection) */
  int local_fa0;
  int local_f9c [2];
  uint local_f94;
  undefined1 local_f90 [8];
  char local_f88 [128];
  undefined1 local_f08 [548];
  undefined1 local_ce4 [548];
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  int local_4;
  
  iVar2 = DAT_00ea0e1c;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00538f51) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. local_4
   * is a real, separate local (an exception-cleanup index) reused
   * throughout this function; its `._0_1_`/`._1_3_` partial-field
   * accesses are rewritten as plain int operations, same reasoning as
   * FUN_004174c0.c's fix. */
  g_nCompositorLayer = 3;
  iVar2 = *(int *)(iVar2 + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      bVar13 = true;
      if (*(int *)(iVar2 + 8) == 0) goto LAB_004069e1;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
  goto LAB_00406a12;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    bVar13 = *(int *)(iVar2 + 8) == 0;
    if (!bVar13) break;
LAB_004069e1:
    if (bVar13) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans(0,0,0,0x1b58);
      }
      else {
        QueueTextureRegionSpans(0,0x1b58,0,0);
      }
      break;
    }
  }
LAB_00406a12:
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 < 2) goto LAB_00406a43;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00406a78:
  if (*(char *)(g_clientContext + 0x3b6c0) == -1) {
LAB_00408159:
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 == 1) {
    QueueSpriteSpansByContentId
              ((uint)(*(char *)(g_clientContext + 0x3b6c0) != '\0') + 0xac,7000,0x229,0x299);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 == 3) {
    QueueSpriteSpansByContentId
              ((uint)(*(char *)(g_clientContext + 0x3b6c0) != '\0') + 0xb3,7000,0x227,0x299);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x621e0) + 0x7640));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 < 1) {
    uVar9 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar9 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x621e0) + 0x7640));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  uVar3 = EncodeChecksumDeltaMul(*(int *)(g_clientContext + 0x621e0) + 0x7864,local_89c,0x28);
  local_4 = 0;
  uVar9 = EncodeChecksumDeltaDiv(uVar3,local_678,uVar9);
  local_4 = 1;
  EncodeChecksumDeltaAdd(uVar9,local_ce4,0xf4);
  local_4 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): return value was discarded, but it's SetClipRect's
   * real x2 arg (edi at orig 0x406c13-0x406c25, confirmed via angr). */
  iVar13 = PeekPacketChecksumState((void *)(local_ce4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  SetClipRect(0, iVar13, 0x257, 0);
  local_4 = 1;
  if ((*(int *)(local_ce4 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_ce4 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_f9c,&g_valueGuardMap);
  }
  local_4 = 0;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_f9c,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_f9c,&g_valueGuardMap);
  }
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 < 3) goto LAB_00406d0a;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00406d42:
  SetClipRect(0, 0x31f, 0x257, 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x621e0) + 0x7640));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 < 1) {
    uVar9 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar9 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x621e0) + 0x7640));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  uVar3 = EncodeChecksumDeltaMul(*(int *)(g_clientContext + 0x621e0) + 0x7a88,local_ce4,0x28);
  local_4 = 3;
  uVar9 = EncodeChecksumDeltaDiv(uVar3,local_678,uVar9);
  local_4 = 4;
  EncodeChecksumDeltaAdd(uVar9,local_89c,0xf5);
  local_4 = 5;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar9 = PeekPacketChecksumState((void *)(local_89c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 < 5) goto LAB_00406e61;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00406e95:
  local_4 = 4;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_89c + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_f9c,&g_valueGuardMap);
  }
  local_4 = 3;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_f9c,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_ce4 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_ce4 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_f9c,&g_valueGuardMap);
  }
  if (*param_1 == -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (iVar2 == 6) goto LAB_00406f80;
    iVar2 = 0;
    iVar10 = 0;
    iVar5 = 0x1f5;
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar6 = PeekPacketChecksumState((void *)(g_clientContext + iVar10 + 0x39f30));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      if (iVar6 != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar6 = PeekPacketChecksumState((void *)(g_clientContext + iVar10 + 0x39f30));
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        if (iVar6 == 0xff) {
          uVar9 = EncodeChecksumDeltaSub(iVar10 + 0x3a154 + g_clientContext,local_ce4,1);
          local_4 = 6;
          uVar9 = EncodeChecksumDeltaMul(uVar9,local_678,2);
          local_4 = 7;
          EncodeChecksumDeltaAdd(uVar9,local_89c,iVar2 == *(int *)(g_clientContext + 0xf0374));
          local_4 = 8;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iPeekIndex = PeekPacketChecksumState((void *)(local_89c));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          QueueSpriteSpansByContentId(iPeekIndex,0x1b5a,3,iVar5);
          local_4 = 7;
          ScrubChecksumGuard();
          local_4 = 6;
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
          iVar2 = iVar2 + 1;
          iVar10 = iVar10 + 0x224;
          iVar5 = iVar5 + 0x24;
        }
        else {
          uVar9 = EncodeChecksumDeltaSub(iVar10 + 0x39f30 + g_clientContext,local_f08,1);
          local_4 = 9;
          uVar9 = EncodeChecksumDeltaMul(uVar9,local_ac0,2);
          local_4 = 10;
          EncodeChecksumDeltaAdd(uVar9,local_454,iVar2 == *(int *)(g_clientContext + 0xf0374));
          local_4 = 0xb;
          EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          iPeekIndex = PeekPacketChecksumState((void *)(local_454));
          LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
          QueueSpriteSpansByContentId(iPeekIndex,0x1b59,3,iVar5);
          local_4 = 10;
          ScrubChecksumGuard();
          local_4 = 9;
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
        }
      }
      iVar5 = iVar5 + 0x24;
      iVar2 = iVar2 + 1;
      iVar10 = iVar10 + 0x224;
    } while (iVar5 < 0x2cd);
  }
  else {
LAB_00406f80:
    QueueSpriteSpansByContentId(0xf,7000,0,0x1f5);
  }
  cVar1 = PeekPacketChecksumBool((byte *)(*(int *)(g_clientContext + 0x621e0) + 0x8ba8));
  if (cVar1 != '\0') {
    EncodeChecksumDeltaDiv(*(int *)(g_clientContext + 0x621e0) + 0x8bc4,local_f08,200);
    local_4 = 0xc;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iPeekIndex = PeekPacketChecksumState((void *)(local_f08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    QueueSpriteSpansByContentId(iPeekIndex + 0x92,500,0x2a,0x2bc);
    local_4 = 0xffffffff;
    if ((*(int *)(local_f08 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_f08 + 0x14),&g_valueGuardKeyTable);
      TreeLowerBound(local_f9c,&g_valueGuardMap);
    }
    uVar9 = EncodeChecksumDeltaDiv(*(int *)(g_clientContext + 0x621e0) + 0x8bc4,local_ac0,0x14);
    local_4 = 0xd;
    EncodeChecksumDeltaMod(uVar9,local_f08,10);
    local_4 = 0xe;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iPeekIndex = PeekPacketChecksumState((void *)(local_f08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    QueueSpriteSpansByContentId(iPeekIndex + 0x92,500,0x2a,0x2d9);
    local_4 = 0xd;
    if ((*(int *)(local_f08 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_f08 + 0x14),&g_valueGuardKeyTable);
      TreeLowerBound(local_f9c,&g_valueGuardMap);
    }
    local_4 = 0xffffffff;
    if ((*(int *)(local_ac0 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_ac0 + 0x14),&g_valueGuardKeyTable);
      TreeLowerBound(local_f9c,&g_valueGuardMap);
    }
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1f5) {
      if (uVar11 == 500) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0x9d) goto LAB_004073ee;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
LAB_00407429:
    uVar9 = EncodeChecksumDeltaDiv(*(int *)(g_clientContext + 0x621e0) + 0x8bc4,local_ac0,2);
    local_4 = 0xf;
    EncodeChecksumDeltaMod(uVar9,local_f08,10);
    local_4 = 0x10;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iPeekIndex = PeekPacketChecksumState((void *)(local_f08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    QueueSpriteSpansByContentId(iPeekIndex + 0x9d,500,0x3b,0x2ff);
    local_4 = 0xf;
    if ((*(int *)(local_f08 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_f08 + 0x14),&g_valueGuardKeyTable);
      TreeLowerBound(local_f9c,&g_valueGuardMap);
    }
    local_4 = 0xffffffff;
    if ((*(int *)(local_ac0 + 0x14)) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(local_ac0 + 0x14),&g_valueGuardKeyTable);
      TreeLowerBound(local_f9c,&g_valueGuardMap);
    }
  }
  pcVar12 = (code *)EnterCriticalSection;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar9 = PeekPacketChecksumState((void *)(g_clientContext + 0x5af88));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  _sprintf(local_f88,&g_rowIndexFormat,uVar9);
  pcVar4 = local_f88;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if ((int)pcVar4 - (int)(local_f88 + 1) == 2) {
    iVar10 = 0;
    iVar2 = 0x186;
    do {
      if (local_f88[iVar10] != ' ') {
        QueueSpriteSpansByContentId(local_f88[iVar10] + 0x77,500,0x3c,iVar2);
      }
      iVar2 = iVar2 + 0xb;
      iVar10 = iVar10 + 1;
    } while (iVar2 < 0x19c);
  }
  else {
    QueueSpriteSpansByContentId(local_f88[0] + 0x77,500,0x3c,0x18c);
  }
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1f5) {
    if (uVar11 == 500) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 < 0xb2) goto LAB_004075f6;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00407631:
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x621e0) + 0x60d4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 < 0) {
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1f5) {
      if (uVar11 == 500) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb3) goto LAB_00407694;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
  }
LAB_004076cf:
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x621e0) + 0x60d4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  uVar11 = iVar2 / 10 + 0xb3;
  iVar10 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = *(uint *)(iVar10 + 4);
  while (uVar8 < 0x1f5) {
    if (uVar8 == 500) {
      iVar10 = *(int *)(iVar10 + 0x10);
      uVar8 = *(uint *)(iVar10 + 8);
      if (uVar8 <= uVar11) goto LAB_00407742;
      break;
    }
    iVar10 = *(int *)(iVar10 + 0x1c);
    uVar8 = *(uint *)(iVar10 + 4);
  }
LAB_00407778:
  iVar10 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar11 = iVar2 % 10 + 0xb3;
  uVar8 = *(uint *)(iVar10 + 4);
  while (uVar8 < 0x1f5) {
    if (uVar8 == 500) {
      iVar2 = *(int *)(iVar10 + 0x10);
      uVar8 = *(uint *)(iVar2 + 8);
      if (uVar8 <= uVar11) goto LAB_004077ad;
      break;
    }
    iVar10 = *(int *)(iVar10 + 0x1c);
    uVar8 = *(uint *)(iVar10 + 4);
  }
LAB_004077e3:
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = (byte)(&DAT_005f2f40)[g_clientContext] + 9;
  uVar11 = *(uint *)(iVar2 + 4);
  while (uVar11 < 0x1b59) {
    if (uVar11 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar11 = *(uint *)(iVar2 + 8);
      if (uVar11 <= uVar8) goto LAB_00407823;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
  }
LAB_00407859:
  if ((char)param_1[10] != '\0') {
    QueueSpriteSpansByContentId
              (param_1[12] + 5,7000,((char)param_1[10] == '\x01') * -10 + 0x248,0xa9);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x621e0) + 0x8318));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar13 = 1;
    if (0 < iVar2) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      /* FIXED (2026-07-15): Ghidra decompiled this call's return value as
       * discarded, but it's the divisor SetClipRect's x2 arg needs below
       * (edi at orig 0x4078e8-0x4078f2) - confirmed via angr, the whole
       * `x2 = third*400/divisor + 244` expression was missing from this
       * decompile entirely, not just the SetClipRect args. */
      iVar13 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x621e0) + 0x8318));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* FIXED (2026-07-15): same as above - real value (esi/eax at orig
     * 0x407919-0x40792b), feeds the same missing expression. */
    iVar14 = PeekPacketChecksumState((void *)(*(int *)(g_clientContext + 0x621e0) + 0x853c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    SetClipRect(0, iVar14 * 0x190 / iVar13 + 0xf4, 0x257, 0);
    QueueSpriteSpansByContentId
              (((char)param_1[10] == '\x01') + 7,7000,
               ((char)param_1[10] == '\x01') * -6 + 0x24d,0xf4);
    SetClipRect(0, 0x31f, 0x257, 0);
    pcVar12 = (code *)EnterCriticalSection;
  }
  (*pcVar12)(&g_valueGuardLock);
  uVar9 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  switch(uVar9) {
  case 0:
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb0) goto LAB_004079ff;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
    break;
  case 1:
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb2) goto LAB_00407a7a;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
    break;
  case 2:
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb1) goto LAB_00407af4;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
    break;
  case 3:
    iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar2 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar11 = *(uint *)(iVar2 + 8);
        if (uVar11 < 0xb3) goto LAB_00407b5d;
        break;
      }
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar11 = *(uint *)(iVar2 + 4);
    }
  }
  goto switchD_004079b9_default;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (1 < uVar11) break;
LAB_00406a43:
    if (uVar11 == 1) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans(1,0,0x22c,0x1b58);
      }
      else {
        QueueTextureRegionSpans(1,0x1b58,0,0x22c);
      }
      break;
    }
  }
  goto LAB_00406a78;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (2 < uVar11) break;
LAB_00406d0a:
    if (uVar11 == 2) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans(2,0xf4,0x239,0x1b58);
      }
      else {
        QueueTextureRegionSpans(2,0x1b58,0xf4,0x239);
      }
      break;
    }
  }
  goto LAB_00406d42;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (4 < uVar11) break;
LAB_00406e61:
    if (uVar11 == 4) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans(4,(int)uVar9,0x239,0x1b58);
      }
      else {
        QueueTextureRegionSpans(4,0x1b58,(int)uVar9,0x239);
      }
      break;
    }
  }
  goto LAB_00406e95;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0x9c < uVar11) break;
LAB_004073ee:
    if (uVar11 == 0x9c) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans(0x9c,0x2f7,0x51,0x1f4);
      }
      else {
        QueueTextureRegionSpans(0x9c,0x1f4,0x2f7,0x51);
      }
      break;
    }
  }
  goto LAB_00407429;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb1 < uVar11) break;
LAB_004075f6:
    if (uVar11 == 0xb1) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans(0xb1,0x187,0x4f,0x1f4);
      }
      else {
        QueueTextureRegionSpans(0xb1,0x1f4,0x187,0x4f);
      }
      break;
    }
  }
  goto LAB_00407631;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb2 < uVar11) break;
LAB_00407694:
    if (uVar11 == 0xb2) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans(0xb2,0x8a,0x245,0x1f4);
      }
      else {
        QueueTextureRegionSpans(0xb2,0x1f4,0x8a,0x245);
      }
      break;
    }
  }
  goto LAB_004076cf;
  while( true ) {
    iVar10 = *(int *)(iVar10 + 0x10);
    uVar8 = *(uint *)(iVar10 + 8);
    if (uVar11 < uVar8) break;
LAB_00407742:
    if (uVar8 == uVar11) {
      if (-1 < (int)uVar11) {
        if (*(char *)(iVar10 + 0x18) == '\x01') {
          QueueSpriteFrameSpans((int)uVar11,0x91,0x245,0x1f4);
        }
        else {
          QueueTextureRegionSpans((int)uVar11,0x1f4,0x91,0x245);
        }
      }
      break;
    }
  }
  goto LAB_00407778;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (uVar11 < uVar8) break;
LAB_004077ad:
    if (uVar8 == uVar11) {
      if (-1 < (int)uVar11) {
        if (*(char *)(iVar2 + 0x18) == '\x01') {
          QueueSpriteFrameSpans((int)uVar11,0x99,0x245,0x1f4);
        }
        else {
          QueueTextureRegionSpans((int)uVar11,0x1f4,0x99,0x245);
        }
      }
      break;
    }
  }
  goto LAB_004077e3;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (uVar8 < uVar11) break;
LAB_00407823:
    if (uVar11 == uVar8) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans((int)uVar8,0xab,0x230,0x1b58);
      }
      else {
        QueueTextureRegionSpans((int)uVar8,0x1b58,0xab,0x230);
      }
      break;
    }
  }
  goto LAB_00407859;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb2 < uVar11) break;
LAB_00407b5d:
    if (uVar11 == 0xb2) {
      if (*(char *)(iVar2 + 0x18) != '\x01') goto LAB_00407b8f;
      QueueSpriteFrameSpans(0xb2,0x141,0,0x1b58);
      break;
    }
  }
  goto switchD_004079b9_default;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb0 < uVar11) break;
LAB_00407af4:
    if (uVar11 == 0xb0) {
      if (*(char *)(iVar2 + 0x18) != '\x01') goto LAB_00407b8f;
      QueueSpriteFrameSpans(0xb0,0x141,0,0x1b58);
      break;
    }
  }
  goto switchD_004079b9_default;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xb1 < uVar11) break;
LAB_00407a7a:
    if (uVar11 == 0xb1) {
      if (*(char *)(iVar2 + 0x18) != '\x01') goto LAB_00407b8f;
      QueueSpriteFrameSpans(0xb1,0x141,0,0x1b58);
      break;
    }
  }
  goto switchD_004079b9_default;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar11 = *(uint *)(iVar2 + 8);
    if (0xaf < uVar11) break;
LAB_004079ff:
    if (uVar11 == 0xaf) {
      if (*(char *)(iVar2 + 0x18) == '\x01') {
        QueueSpriteFrameSpans(0xaf,0x141,0,0x1b58);
      }
      else {
LAB_00407b8f:
        QueueTextureRegionSpans((int)uVar11,0x1b58,0x141,0);
      }
      break;
    }
  }
switchD_004079b9_default:
  _sprintf(local_f88,(char *)&PTR_DAT_00551ed0,param_1[0xd]);
  iVar10 = 0;
  iVar2 = 0x15e;
LAB_00407bb4:
  cVar1 = local_f88[iVar10];
  if (cVar1 != ' ') {
    if (cVar1 == '-') {
      iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar11 = *(uint *)(iVar5 + 4);
      while (uVar11 < 0x1f5) {
        if (uVar11 == 500) {
          iVar5 = *(int *)(iVar5 + 0x10);
          uVar11 = *(uint *)(iVar5 + 8);
          if (uVar11 < 0x92) goto LAB_00407c03;
          break;
        }
        iVar5 = *(int *)(iVar5 + 0x1c);
        uVar11 = *(uint *)(iVar5 + 4);
      }
    }
    else {
      iVar5 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar8 = (int)cVar1 + 0x57;
      uVar11 = *(uint *)(iVar5 + 4);
      while (uVar11 < 0x1f5) {
        if (uVar11 == 500) {
          iVar5 = *(int *)(iVar5 + 0x10);
          uVar11 = *(uint *)(iVar5 + 8);
          if (uVar11 <= uVar8) goto LAB_00407c6b;
          break;
        }
        iVar5 = *(int *)(iVar5 + 0x1c);
        uVar11 = *(uint *)(iVar5 + 4);
      }
    }
  }
  goto LAB_00407c9d;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar11 = *(uint *)(iVar5 + 8);
    if (uVar8 < uVar11) break;
LAB_00407c6b:
    if (uVar11 == uVar8) {
      if (-1 < (int)uVar8) {
        if (*(char *)(iVar5 + 0x18) != '\x01') goto LAB_00407c95;
        QueueSpriteFrameSpans((int)uVar8,iVar2,6,0x1f4);
      }
      break;
    }
  }
  goto LAB_00407c9d;
  while( true ) {
    iVar5 = *(int *)(iVar5 + 0x10);
    uVar11 = *(uint *)(iVar5 + 8);
    if (0x91 < uVar11) break;
LAB_00407c03:
    if (uVar11 == 0x91) {
      if (*(char *)(iVar5 + 0x18) == '\x01') {
        QueueSpriteFrameSpans(0x91,iVar2,6,0x1f4);
      }
      else {
LAB_00407c95:
        QueueTextureRegionSpans((int)uVar11,0x1f4,iVar2,6);
      }
      break;
    }
  }
LAB_00407c9d:
  iVar2 = iVar2 + 0x14;
  iVar10 = iVar10 + 1;
  if (0x1c1 < iVar2) goto code_r0x00407cad;
  goto LAB_00407bb4;
code_r0x00407cad:
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 == -1) goto LAB_00407df7;
  EncodeChecksumDeltaMul(g_clientContext + 0xebcbc,local_f08,0x14);
  local_4 = 0x11;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(local_f08));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar11 = param_1[0xf] % 0x14 + 0x19 + iVar2;
  iVar2 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar8 = *(uint *)(iVar2 + 4);
  while (uVar8 < 0x1b59) {
    if (uVar8 == 7000) {
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar8 = *(uint *)(iVar2 + 8);
      if (uVar8 <= uVar11) goto LAB_00407d6b;
      break;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar8 = *(uint *)(iVar2 + 4);
  }
  goto LAB_00407d9e;
  while( true ) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar8 = *(uint *)(iVar2 + 8);
    if (uVar11 < uVar8) break;
LAB_00407d6b:
    if (uVar8 == uVar11) {
      if (-1 < (int)uVar11) {
        if (*(char *)(iVar2 + 0x18) == '\x01') {
          QueueSpriteFrameSpans((int)uVar11,0x53,4,0x1b58);
        }
        else {
          QueueTextureRegionSpans((int)uVar11,0x1b58,0x53,4);
        }
      }
      break;
    }
  }
LAB_00407d9e:
  local_4 = 0xffffffff;
  if ((*(int *)(local_f08 + 0x14)) != 0) {
    iVar2 = (*(int *)(local_f08 + 0x14)) << 4;
    iVar10 = 0x10;
    do {
      iVar5 = _rand();
      *(char *)(iVar2 + g_valueGuardKeyTable) = (char)iVar5;
      iVar2 = iVar2 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    TreeLowerBound(local_f9c,&g_valueGuardMap);
  }
LAB_00407df7:
  SetClipRect(0x7a, 0x129, 0x1e, 5);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar2 + -1 < 0) {
    iVar2 = 0;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = iVar2 + -1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar10 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar10 < 1) {
    iVar10 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar10 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar6 + -1 < 0) {
    iVar6 = 0;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar6 = iVar6 + -1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar7 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar7 < 1) {
    iVar7 = 1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar7 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  local_fa0 = 6;
  local_f94 = iVar6 / iVar7 + 1;
  iVar2 = 0x80 - ((iVar2 % iVar5) * 0x23) / iVar10;
LAB_00407fd0:
  uVar11 = local_f94 & 0x80000007;
  if ((int)uVar11 < 0) {
    uVar11 = (uVar11 - 1 | 0xfffffff8) + 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar10 = PeekPacketChecksumState((void *)(uVar11 * 0x224 + 0x595d8 + g_clientContext));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar10 != -1) {
    EncodeChecksumDeltaAdd(uVar11 * 0x224 + 0x595d8 + g_clientContext,local_230,0xa5);
    local_4 = 0x12;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar8 = PeekPacketChecksumState((void *)(local_230));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar10 = *(int *)(DAT_00ea0e1c + 0x1c);
    uVar11 = *(uint *)(iVar10 + 4);
    while (uVar11 < 0x1b59) {
      if (uVar11 == 7000) {
        iVar10 = *(int *)(iVar10 + 0x10);
        uVar11 = *(uint *)(iVar10 + 8);
        if (uVar11 <= uVar8) goto LAB_0040809a;
        break;
      }
      iVar10 = *(int *)(iVar10 + 0x1c);
      uVar11 = *(uint *)(iVar10 + 4);
    }
    goto LAB_004080ce;
  }
  goto LAB_00408127;
  while( true ) {
    iVar10 = *(int *)(iVar10 + 0x10);
    uVar11 = *(uint *)(iVar10 + 8);
    if (uVar8 < uVar11) break;
LAB_0040809a:
    if (uVar11 == uVar8) {
      if (-1 < (int)uVar8) {
        if (*(char *)(iVar10 + 0x18) == '\x01') {
          QueueSpriteFrameSpans((int)uVar8,iVar2,6,0x1b58);
        }
        else {
          QueueTextureRegionSpans((int)uVar8,0x1b58,iVar2,6);
        }
      }
      break;
    }
  }
LAB_004080ce:
  iVar10 = (*(int *)(local_230 + 0x14));
  local_4 = 0xffffffff;
  if ((*(int *)(local_230 + 0x14)) != 0) {
    iVar5 = (*(int *)(local_230 + 0x14)) << 4;
    iVar6 = 0x10;
    do {
      iVar7 = _rand();
      *(char *)(iVar5 + g_valueGuardKeyTable) = (char)iVar7;
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    local_f9c[0] = iVar10;
    TreeLowerBound(local_f90,&g_valueGuardMap);
  }
LAB_00408127:
  local_f94 = local_f94 + 1;
  iVar2 = iVar2 + 0x23;
  local_fa0 = local_fa0 + -1;
  if (local_fa0 == 0) goto code_r0x00408142;
  goto LAB_00407fd0;
code_r0x00408142:
  SetClipRect(0, 0x31f, 0x257, 0);
  goto LAB_00408159;
}

