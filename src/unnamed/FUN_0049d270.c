/* FUN_0049d270 - 0x0049d270 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell Ghidra dropped from all 52 argless PeekPacketChecksumState() and
 * all 10 one-arg EncodeOutgoingPacketField() calls (both lists "clean"
 * in tools/guard_worklist.json).  Cells derived with
 * tools/guard_cell_resolve.py over 0x49d270-0x49e460 and checked per
 * site; the decompile is goto-shuffled, so nothing was order-zipped -
 * the C body's first sites (lines ~61-105) live at the function's LAST
 * addresses (0x49dfa9-0x49e0c7) and the C tail runs 0x49d362 onward.
 *
 * This is the third detonation twin of DetonateProjectile (0x4572b0)
 * and DetonateSuperShot_Bullet9, both already swept, and its two big tail blocks
 * carry the identical cell sequence offset for offset - the crater
 * block's 0x6ac/0x488/0x2f74/0x2d50/0x2b2c/0x2908/0x26e4/0x24c0/
 * 0x1178/0xf54, then the 0x1178+0xf54 pairs, 0x15c0, and
 * 0x5b85c/0x3920/0x8d0/0x488, 0xf54/0x3b48.  That cross-check is what
 * pins the mapping; the per-site landmarks agree (LAB_0049d99e ==
 * `*(char *)(piStack_ad8 + 5) = 1` == 0x49d99e's `mov byte
 * [ebx+0x14],1`, and CompareChecksumPair(piStack_ad8 + 0xed2, + 0xf5b)
 * == 0x49dece's [ebx+0x3b48]/[ebx+0x3d6c]).
 *
 * The object arrives in ECX and is spilled once, at 0x49d2a4, to the
 * frame slot Ghidra calls local_ad4; every later block reloads it from
 * there (0x49d99e / 0x49db16 / 0x49dcda / 0x49e095).  Expressed through
 * whichever alias the surrounding C already uses - param_1, piVar9 or
 * piStack_ad8 - since all three hold that same pointer in their
 * respective regions.  Do NOT use local_ad4 itself: Ghidra reuses that
 * name for two other frame slots (lines ~229 and ~405 assign Peek
 * RESULTS to it, which the machine code stores 4 bytes away), so by the
 * tail the C variable no longer holds the object.  That 4-byte skew is
 * systematic in this decompile - the scratch guard cells really live at
 * esp+0x44 and esp+0x268 while Ghidra names them auStack_ac4 and
 * auStack_8a0 - so cell identity was taken from each cell's own +0x220
 * flag byte and +0x14 handle zero-stores (uStack_8a4/iStack_ab0 pair
 * with auStack_ac4; uStack_680/uStack_88c with auStack_8a0), not from
 * the names.
 *
 * Two cells were chained returns the decompile discarded: the
 * EncodeChecksumDeltaShr calls at 0x49dfa9 and 0x49e024 return their
 * dest cell in EAX (`mov edi,eax`) and the paired Peek re-reads it.
 * Captured in a new uVar21 rather than reusing a live temporary.
 */
#include "ghidra_types.h"


void __fastcall FUN_0049d270(int *param_1)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  byte bVar14;
  byte *pbVar15;
  undefined4 *unaff_FS_OFFSET;
  bool bVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined4 *puStack_af0;
  int local_ae8;
  undefined4 uStack_adc;
  int *piStack_ad8;
  int *local_ad4;
  undefined4 *apuStack_ad0 [2];
  int iStack_ac8;
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 uStack_8a4;
  undefined1 auStack_8a0 [20];
  undefined4 uStack_88c;
  undefined1 uStack_680;
  undefined1 auStack_67c [548];
  undefined1 auStack_458 [548];
  undefined1 auStack_234 [548];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053e1c3;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_ad4 = param_1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x10));
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x122));
  EncodeOutgoingPacketField((void *)(param_1 + 0x10), iVar6 + iVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x99));
  iVar6 = PeekPacketChecksumState((void *)(param_1 + 0x1ab));
  EncodeOutgoingPacketField((void *)(param_1 + 0x99), iVar6 + iVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 == '\0') {
    uVar21 = EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)uVar21);
    EncodeOutgoingPacketField((void *)(param_1 + 0x3d5), uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(apuStack_ad0);
      param_1 = piStack_ad8;
    }
    uVar21 = EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac4,8);
    puStack_8 = (undefined1 *)0x6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)uVar21);
    EncodeOutgoingPacketField((void *)(param_1 + 0x45e), uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)0xffffffff;
    piVar9 = param_1;
    if (iStack_ab0 != 0) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(apuStack_ad0);
      piVar9 = piStack_ad8;
    }
    cVar4 = CheckGuardedBoolAnd(piVar9[0x3d2] != 0);
    if (cVar4 == '\0') {
      EmitChecksumSum(piVar9 + 0x122, piVar9 + 0x2bd);
      EmitChecksumSum(piVar9 + 0x1ab, piVar9 + 0x346);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar13 = PeekPacketChecksumState((void *)(piVar9 + 0x122));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((int)((uVar13 ^ (int)uVar13 >> 0x1f) - ((int)uVar13 >> 0x1f)) < 200) {
        cVar4 = PacketChecksumLessThan(piVar9 + 0x122,0);
        if (cVar4 == '\0') {
          uVar8 = 200;
        }
        else {
          uVar8 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar8);
      }
      uVar8 = EncodeChecksumDeltaDiv(piVar9[0x3d2] + 0x25c,auStack_67c,4);
      puStack_8 = (undefined1 *)0x7;
      uVar8 = EncodeChecksumPairDiff(piVar9[0x3d2] + 0x38,auStack_458,uVar8);
      puStack_8 = (undefined1 *)0x8;
      bVar2 = false;
      bVar16 = false;
      cVar4 = CompareChecksumPair(piVar9 + 0x3d5,uVar8);
      if (cVar4 == '\0') {
        uVar8 = EncodeChecksumDeltaDiv(piVar9[0x3d2] + 0x25c,auStack_8a0,4);
        puStack_8 = (undefined1 *)0x9;
        uVar8 = EncodeChecksumPairSum(piVar9[0x3d2] + 0x38,auStack_ac4,uVar8);
        puStack_8 = (undefined1 *)0xa;
        bVar2 = true;
        bVar16 = true;
        cVar4 = CompareChecksumPair(uVar8,piVar9 + 0x3d5);
        bVar3 = false;
        if (cVar4 != '\0') goto LAB_0049e1d8;
      }
      else {
LAB_0049e1d8:
        bVar3 = true;
      }
      puStack_8 = (undefined1 *)0x9;
      if (bVar16) {
        ScrubChecksumGuard();
      }
      puStack_8 = (undefined1 *)0x8;
      if (bVar2) {
        ScrubChecksumGuard();
      }
      puStack_8 = (undefined1 *)0x7;
      ScrubChecksumGuard();
      puStack_8 = (undefined1 *)0xffffffff;
      ScrubChecksumGuard();
      if (bVar3) {
        iVar5 = piVar9[0x3d4];
        piVar9[0x3d4] = iVar5 + 1;
        if (iVar5 + 1 < 3) {
          uVar8 = EncodeChecksumNegate(piVar9 + 0x122,auStack_234);
          puStack_8 = (undefined1 *)0xb;
          EncodeChecksumState(uVar8);
          puStack_8 = (undefined1 *)0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piVar9 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (-1 < iVar5) {
      iVar5 = *(int *)(&g_nCameraBoundX + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState((void *)(piVar9 + 0x3d5));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (((iVar6 < iVar5) &&
          (cVar4 = PacketChecksumGreaterEqual(param_1 + 0x45e,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
          cVar4 == '\0')) && (cVar4 = PacketChecksumLessThan(param_1 + 0x45e,0xfffffc18), cVar4 == '\0'))
      goto LAB_0049e3fe;
    }
    *(undefined1 *)(piVar9 + 5) = 1;
    cVar4 = PeekPacketChecksumBool();
    if ((cVar4 != '\0') && (cVar4 = InitChecksumSeed(), cVar4 == '\0')) {
      iVar5 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
      if ((iVar5 == 5) || (uVar8 = 2, iVar5 == 6)) {
        uVar8 = 0x19;
      }
      QueueOutgoingPacketField(uVar8);
      iVar5 = g_clientContext;
      if (*(int *)(&DAT_005f3768 + g_clientContext) != 0) {
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar5) = 0;
      }
    }
    goto LAB_0049e3fe;
  }
  SyncOutgoingChecksumField(param_1[2],param_1 + 0x45e);
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((-1 < iVar5) && (iVar5 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
      pcVar7 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
      puStack_af0 = (undefined4 *)0x0;
      if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
        do {
          if (*pcVar7 != '\0') goto LAB_0049d3ba;
          pcVar7 = pcVar7 + *(int *)(&g_nCameraBoundX + g_clientContext);
          puStack_af0 = (undefined4 *)((int)puStack_af0 + 1);
        } while ((int)puStack_af0 < *(int *)(&g_nCameraBoundY + g_clientContext));
      }
    }
    puStack_af0 = (undefined4 *)0x2710;
LAB_0049d3ba:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar8,puStack_af0);
    local_ae8 = 1;
    if (0 < param_1[0xfe5]) {
      local_ae8 = param_1[0xfe5];
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_ad4 = (int *)PeekPacketChecksumState((void *)&DAT_007949c8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_adc = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_0043af40(uStack_adc,puStack_af0,0,local_ad4,iVar5 / local_ae8,uVar8,(char)param_1[0xf]);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x5f9));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(param_1 + 0x3d5));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar20 = 0;
    uVar19 = 2;
    uVar18 = 0xff;
    uVar17 = 0;
    PeekPacketChecksumBool(0,uVar8,0xff,2,0);
    FUN_00431d90((char)param_1[0xf],7,0,uVar17,uVar8,uVar18,uVar19,uVar20);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar9 = (int *)PeekPacketChecksumState((void *)(param_1 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = g_clientContext;
  iStack_ac8 = param_1[2];
  uStack_adc = uVar8;
  local_ad4 = piVar9;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0xebcbc));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar6 == 4) {
    puStack_af0 = operator_new(0x3fbc);
    puStack_8 = (undefined1 *)0x0;
    apuStack_ad0[0] = puStack_af0;
    if (puStack_af0 == (undefined4 *)0x0) {
      puStack_af0 = (undefined4 *)0x0;
    }
    else {
      InitProjectile(puStack_af0,0x186a9);
      *puStack_af0 = &PTR_FUN_0055658c;
      puStack_af0[0xfe7] = 0xffffffff;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    iVar6 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar13 = *(uint *)(iVar6 + 4);
    while (uVar13 < 0x186ab) {
      if (uVar13 == 0x186aa) {
        piVar9 = *(int **)(iVar6 + 0x10);
        bVar16 = true;
        if (piVar9[2] == 0) goto LAB_0049d635;
        break;
      }
      iVar6 = *(int *)(iVar6 + 0x1c);
      uVar13 = *(uint *)(iVar6 + 4);
    }
  }
  goto LAB_0049d99e;
  while( true ) {
    piVar9 = (int *)piVar9[4];
    bVar16 = piVar9[2] == 0;
    if (!bVar16) break;
LAB_0049d635:
    if (bVar16) {
      apuStack_ad0[0] = (undefined4 *)piVar9[0xf];
      iVar6 = piVar9[0xe];
      iVar10 = CalculateAngleFromDelta();
      iVar11 = FloatToInt64();
      iVar12 = FloatToInt64();
      iVar12 = (int)apuStack_ad0[0] - iVar12;
      (**(code **)(*piVar9 + 4))(&DAT_00553b90);
      piVar9[0x11] = iVar10;
      apuStack_ad0[0] = (undefined4 *)(&DAT_006a7f74 + iVar5);
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
        uStack_680 = 0;
        uStack_88c = 0;
        EncodeOutgoingPacketField((void *)auStack_8a0, 0);
        puStack_8 = (undefined1 *)0x3;
        uStack_8a4 = 0;
        iStack_ab0 = 0;
        EncodeOutgoingPacketField((void *)auStack_ac4, 0);
        SUBFIELD(puStack_8,0,undefined1) = 4;
        SyncOutgoingChecksumField(iStack_ac8 + 0x10,auStack_ac4);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState((void *)auStack_ac4);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar8 = PeekPacketChecksumState((void *)auStack_8a0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar5 = param_1[0xfe5];
        uVar20 = 0;
        uVar19 = 0xff;
        uVar18 = 100;
        uVar17 = 0;
        PeekPacketChecksumBool(uVar8,0,100,0xff,iVar5,0);
        FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar17,uVar18,uVar19,iVar5,uVar20);
        puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),3);
        ScrubChecksumGuard();
LAB_0049d8fd:
        puStack_8 = (undefined1 *)0xffffffff;
        ScrubChecksumGuard();
      }
      else {
        cVar4 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&uStack_adc,&local_ad4,2,1,1);
        if (cVar4 != '\0') {
          uStack_8a4 = 0;
          iStack_ab0 = 0;
          EncodeOutgoingPacketField((void *)auStack_ac4, 0);
          puStack_8 = (undefined1 *)0x1;
          uStack_680 = 0;
          uStack_88c = 0;
          EncodeOutgoingPacketField((void *)auStack_8a0, 0);
          SUBFIELD(puStack_8,0,undefined1) = 2;
          QueueOutgoingPacketField(uStack_adc);
          QueueOutgoingPacketField(local_ad4);
          SyncOutgoingChecksumField(iStack_ac8 + 0x10,auStack_8a0);
          iVar5 = param_1[0xfe5];
          uVar20 = 0;
          uVar19 = 0xff;
          uVar18 = 100;
          uVar17 = 0;
          PeekChecksumStateUnderLock(auStack_8a0);
          uVar8 = PeekChecksumStateUnderLock(auStack_ac4);
          PeekPacketChecksumBool(uVar8,uVar17,uVar18,uVar19,iVar5,uVar20);
          FUN_00432320((char)param_1[0xf],1,1,uVar8,uVar17,uVar18,uVar19,iVar5,uVar20);
          puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
          ScrubChecksumGuard();
          goto LAB_0049d8fd;
        }
      }
      puStack_af0[0xfea] = iVar6 - iVar11;
      puStack_af0[0xfeb] = iVar12;
      puStack_af0[0xfec] = uStack_adc;
      puStack_af0[0xfed] = local_ad4;
      puStack_af0[0xfee] = iVar10;
      /* FIXED (2026-07-15): dropped `self` args - angr-confirmed EDI at
       * 0x49d949/0x49d95a. Disasm reload (`mov 0x28(%esp),%edi`) traces
       * back to the `piVar9 = (int *)piVar9[4];` list-walk above; piVar9
       * is never reassigned in between. */
      uVar8 = FUN_004ac4d0(piVar9);
      puStack_af0[0xfe9] = uVar8;
      iVar5 = FUN_004ac400(piVar9);
      puStack_af0[0xfe8] = iVar5 * param_1[0xfe5];
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
        RegisterActiveObject(0, 0, (undefined4 *)0);
      }
      else {
        (**(code **)*puStack_af0)(1);
      }
      break;
    }
  }
LAB_0049d99e:
  *(undefined1 *)(piStack_ad8 + 5) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x1ab));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x122));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piStack_ad8 + 0xbdd));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xb54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar19 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xacb));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar20 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xa42));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_ad4 = (int *)PeekPacketChecksumState((void *)(piStack_ad8 + 0x9b9));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uStack_adc = PeekPacketChecksumState((void *)(piStack_ad8 + 0x930));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iStack_ac8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  ApplyCraterExcavation(uStack_adc,local_ad4,uVar20,uVar19,uVar18,apuStack_ad0[0],uVar17,uVar8);
  RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar9 = piStack_ad8;
  uVar8 = PeekPacketChecksumState((void *)(piVar9 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piVar9 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(apuStack_ad0[0],uVar8,piVar9,1,0,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piVar9 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)(piVar9 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar17,uVar8);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piVar9 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  apuStack_ad0[0] = (undefined4 *)PeekPacketChecksumState((void *)(piVar9 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(piVar9[2],apuStack_ad0[0],uVar8,piVar9[0xe25],piVar9 + 0xe26);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(piVar9 + 0x570));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar17 = PeekPacketChecksumState((void *)(piVar9 + 0x45e));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar18 = PeekPacketChecksumState((void *)(piVar9 + 0x3d5));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar18,uVar17,0x3c,uVar8);
  iVar5 = g_clientContext;
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 != '\x01') {
    iVar6 = *(int *)(&DAT_006a7750 + iVar5);
    if (iVar6 < 0x10) {
      iVar6 = 0xf;
    }
    *(int *)(&DAT_006a7750 + iVar5) = iVar6;
    iVar6 = *(int *)(&DAT_006a7754 + iVar5);
    if (iVar6 < 0xb) {
      iVar6 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar5) = iVar6;
  }
  cVar4 = PeekPacketChecksumBool();
  if (cVar4 == '\0') {
    AcquireSoundChannel(0);
  }
  cVar4 = PeekPacketChecksumBool();
  if ((cVar4 != '\0') && (cVar4 = InitChecksumSeed(), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(g_clientContext + 0x621e8), 0x1e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = g_clientContext;
    if (*(int *)(&DAT_005f3768 + g_clientContext) != 0) {
      *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
      *(undefined4 *)(&DAT_005f376c + iVar5) = 0;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x5b85c));
  iVar6 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xe48));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar4 = CheckGuardedBoolAnd(iVar5 < iVar6);
  if (cVar4 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar8 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xe48));
    EncodeOutgoingPacketField((void *)(g_clientContext + 0x5b85c), uVar8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x234));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 < 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x122));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar5 < 1) goto LAB_0049de1f;
LAB_0049de6b:
    cVar4 = PeekPacketChecksumBool();
    if (cVar4 == '\0') {
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
  }
  else {
LAB_0049de1f:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x234));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (0 < iVar5) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x122));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar5 < 0) goto LAB_0049de6b;
    }
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
  iVar6 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xed2));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar6 <= iVar5) ||
     (cVar4 = CompareChecksumPair(piStack_ad8 + 0xed2,piStack_ad8 + 0xf5b), cVar4 == '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(piStack_ad8 + 0x3d5));
    iVar6 = PeekPacketChecksumState((void *)(piStack_ad8 + 0xed2));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((iVar5 <= iVar6) ||
       ((cVar4 = CompareChecksumExceeds(piStack_ad8 + 0xed2,piStack_ad8 + 0xf5b), cVar4 == '\0' ||
        (piStack_ad8[0xed1] < 6)))) goto LAB_0049e3fe;
  }
  iVar5 = g_clientContext;
  pbVar15 = (byte *)(g_clientContext + 0x62143);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = _rand();
  *pbVar15 = (byte)iVar6;
  iVar6 = _rand();
  bVar1 = *pbVar15;
  *(byte *)(iVar5 + 0x62144) = (byte)iVar6;
  bVar14 = '\x01' << (bVar1 & 7);
  bVar14 = ~bVar14 & (byte)iVar6 | bVar14;
  *(byte *)(iVar5 + 0x62144) = bVar14;
  *(byte *)(iVar5 + 0x62145) = bVar14 + bVar1 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
LAB_0049e3fe:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

