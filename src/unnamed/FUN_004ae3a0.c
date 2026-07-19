/* FUN_004ae3a0 - 0x004ae3a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ae3a0(int *param_1)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar18;
  char *pcVar19;
  undefined1 auStack_ac0 [548];
  undefined1 auStack_89c [548];
  undefined1 auStack_678 [548];
  undefined1 auStack_454 [548];
  undefined1 auStack_230 [548];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053e429;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  if ((param_1[0xfe7] != -1) && (iVar7 = param_1[0xfe7] + 1, param_1[0xfe7] = iVar7, iVar7 == 0x2c))
  {
    param_1[0xfe7] = -1;
    (**(code **)(*param_1 + 4))(s_change_00555af0);
  }
  if ((char)param_1[0xd] == '\x01') {
    if (param_1[9] == 1) {
      FUN_00432850(param_1,6);
      *(undefined1 *)(param_1 + 5) = 1;
      *unaff_FS_OFFSET = uStack_c;
      return;
    }
  }
  else if (param_1[9] == 1) goto LAB_004aece0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4ae458
   * (`mov edi,ebp`, ebp = `lea ebp,[esi+0x40]` at 0x4ae436, esi = this
   * file's own param_1) the cell is param_1+0x10 (scaled int* units,
   * byte offset 0x40) - the same cell EncodeChecksumDeltaShr(param_1 +
   * 0x10, ...) below already addresses, confirming the mapping. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_1 + 0x10, iVar8 + iVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4ae492
   * (`mov edi,ebx`, ebx = `lea ebx,[esi+0x264]` at 0x4ae46d) the cell is
   * param_1+0x99 (scaled), the same cell EncodeChecksumDeltaShr(param_1
   * + 0x99, ...) below already addresses. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  iVar8 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_1 + 0x99, iVar8 + iVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  (**(code **)(*param_1 + 0x14))(8);
  cVar6 = PeekPacketChecksumBool();
  if (cVar6 == '\0') {
    EncodeChecksumDeltaShr(param_1 + 0x10,auStack_ac0,8);
    uStack_4 = 0;
    piVar2 = param_1 + 0x3d5;
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x4ae806 (`mov edi,ebp`, ebp = `lea ebp,[esi+0xf54]` at 0x4ae7f0)
     * the cell is param_1+0x3d5 (scaled), same as piVar2 = param_1 +
     * 0x3d5 immediately above. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(param_1 + 0x3d5, uVar11);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_4 = 0xffffffff;
    ScrubChecksumGuard();
    EncodeChecksumDeltaShr(param_1 + 0x99,auStack_ac0,8);
    piVar1 = param_1 + 0x45e;
    uStack_4 = 1;
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x4ae863 (`mov edi,ebx`, ebx = `lea ebx,[esi+0x1178]` at
     * 0x4ae839) the cell is param_1+0x45e (scaled), same as piVar1 =
     * param_1 + 0x45e immediately above. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar11 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(param_1 + 0x45e, uVar11);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_4 = 0xffffffff;
    ScrubChecksumGuard();
    cVar6 = CheckGuardedBoolAnd(param_1[0x3d2] != 0);
    if (cVar6 == '\0') {
      EmitChecksumSum(param_1 + 0x2bd);
      EmitChecksumSum(param_1 + 0x346);
    }
    else {
      uVar13 = PeekChecksumStateUnderLock(param_1 + 0x122);
      if ((int)((uVar13 ^ (int)uVar13 >> 0x1f) - ((int)uVar13 >> 0x1f)) < 200) {
        cVar6 = PacketChecksumLessThan(param_1 + 0x122,0);
        if (cVar6 == '\0') {
          uVar11 = 200;
        }
        else {
          uVar11 = 0xffffff38;
        }
        QueueOutgoingPacketField(uVar11);
      }
      uVar11 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_678,4);
      uStack_4 = 2;
      uVar11 = EncodeChecksumPairDiff(param_1[0x3d2] + 0x38,auStack_89c,uVar11);
      bVar4 = false;
      bVar3 = false;
      uStack_4 = 3;
      cVar6 = CompareChecksumPair(piVar2,uVar11);
      if (cVar6 == '\0') {
        uVar11 = EncodeChecksumDeltaDiv(param_1[0x3d2] + 0x25c,auStack_454,4);
        uStack_4 = 4;
        uVar11 = EncodeChecksumPairSum(param_1[0x3d2] + 0x38,auStack_ac0,uVar11);
        uStack_4 = 5;
        bVar4 = true;
        bVar3 = true;
        cVar6 = CompareChecksumPair(uVar11,piVar2);
        bVar5 = false;
        if (cVar6 != '\0') goto LAB_004ae9a8;
      }
      else {
LAB_004ae9a8:
        bVar5 = true;
      }
      uStack_4 = 4;
      if (bVar3) {
        ScrubChecksumGuard();
      }
      uStack_4 = 3;
      if (bVar4) {
        ScrubChecksumGuard();
      }
      uStack_4 = 2;
      ScrubChecksumGuard();
      uStack_4 = 0xffffffff;
      ScrubChecksumGuard();
      if (bVar5) {
        iVar7 = param_1[0x3d4];
        param_1[0x3d4] = iVar7 + 1;
        if (iVar7 + 1 < 3) {
          uVar11 = EncodeChecksumNegate(param_1 + 0x122,auStack_230);
          uStack_4 = 6;
          EncodeChecksumState(uVar11);
          uStack_4 = 0xffffffff;
          ScrubChecksumGuard();
        }
        else {
          SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        }
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((((iVar7 < 0) ||
         (cVar6 = PacketChecksumGreaterEqual(piVar2,*(undefined4 *)(&g_nCameraBoundX + g_clientContext)), cVar6 != '\0')
         ) || (cVar6 = PacketChecksumGreaterEqual(piVar1,*(undefined4 *)(&g_nCameraBoundY + g_clientContext)),
              cVar6 != '\0')) || (cVar6 = PacketChecksumLessThan(piVar1,0xfffffc18), cVar6 != '\0')) {
      *(undefined1 *)(param_1 + 5) = 1;
      cVar6 = PeekPacketChecksumBool();
      if ((cVar6 != '\0') && (cVar6 = InitChecksumSeed(), cVar6 == '\0')) {
        iVar7 = *(int *)(*(int *)(g_clientContext + 0x621e4) + 0x24);
        if ((iVar7 == 5) || (uVar11 = 2, iVar7 == 6)) {
          uVar11 = 0x19;
        }
        QueueOutgoingPacketField(uVar11);
        iVar7 = g_clientContext;
        *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
        *(undefined4 *)(&DAT_005f376c + iVar7) = 0;
      }
    }
    cVar6 = CheckBothGuardedBools();
    if (cVar6 != '\0') {
      iVar8 = PeekChecksumStateUnderLock(piVar1);
      iVar14 = PeekChecksumStateUnderLock(piVar2);
      iVar7 = g_clientContext;
      piVar2 = (int *)(&DAT_006a7708 + g_clientContext);
      cVar6 = PeekPacketChecksumBool();
      if ((cVar6 == '\0') && ((&DAT_006a7758)[iVar7] != '\0')) {
        if (((&DAT_006a7736)[iVar7] == '\x01') &&
           ((uVar13 = iVar8 - *(int *)(&g_nCameraY + iVar7) >> 0x1f,
            200 < (int)((iVar8 - *(int *)(&g_nCameraY + iVar7) ^ uVar13) - uVar13) ||
            (uVar13 = iVar14 - *(int *)(&g_nCameraX + iVar7) >> 0x1f,
            300 < (int)((iVar14 - *(int *)(&g_nCameraX + iVar7) ^ uVar13) - uVar13))))) {
          (&DAT_006a7736)[iVar7] = 0;
        }
        iVar16 = 400;
        if (399 < iVar14) {
          iVar16 = iVar14;
        }
        iVar15 = *(int *)(&g_nCameraBoundX + iVar7) + -400;
        if ((iVar16 <= iVar15) && (iVar15 = iVar14, iVar14 < 400)) {
          iVar15 = 400;
        }
        iVar14 = -0x14;
        if (-0x15 < iVar8) {
          iVar14 = iVar8;
        }
        iVar16 = *(int *)(&g_nCameraBoundY + iVar7) + -0x104;
        if ((iVar14 <= iVar16) && (iVar16 = -0x14, -0x15 < iVar8)) {
          iVar16 = iVar8;
        }
        iVar8 = *piVar2 - iVar15;
        *(int *)(&g_nCameraScrollY + iVar7) = iVar16;
        if (((*(int *)(&DAT_006a770c + iVar7) - iVar16) * (*(int *)(&DAT_006a770c + iVar7) - iVar16)
             + iVar8 * iVar8 < 40000) &&
           (((&DAT_006a7734)[iVar7] == '\x01' || ((&DAT_006a7f6c)[iVar7] == '\0')))) {
          *(int *)(&g_nCameraX + iVar7) = iVar15;
          *piVar2 = iVar15;
          *(int *)(&g_nCameraY + iVar7) = iVar16;
          *(int *)(&DAT_006a770c + iVar7) = iVar16;
        }
        if ((((&DAT_006a7734)[iVar7] == '\0') && ((&DAT_006a7f6c)[iVar7] == '\x01')) &&
           ((&DAT_006a7736)[iVar7] == '\0')) {
          iVar8 = *(int *)(&DAT_006a7730 + iVar7);
          iVar14 = iVar8;
          if (iVar15 <= iVar8) {
            iVar14 = iVar15;
          }
          iVar17 = *(int *)(&DAT_006a772c + iVar7);
          if ((iVar17 <= iVar14) && (iVar17 = iVar8, iVar15 <= iVar8)) {
            iVar17 = iVar15;
          }
          *(int *)(&g_nCameraScrollX + iVar7) = iVar17;
        }
        if ((&DAT_006a7734)[iVar7] == '\x01') {
          *(int *)(&g_nCameraScrollX + iVar7) = iVar15;
          *(int *)(&g_nCameraScrollY + iVar7) = iVar16;
        }
      }
    }
    goto LAB_004aece0;
  }
  piVar2 = param_1 + 0x3d5;
  SyncOutgoingChecksumField(param_1[2],param_1 + 0x45e);
  cVar6 = PeekPacketChecksumBool();
  if (cVar6 != '\0') {
    uVar12 = PeekChecksumStateUnderLock(piVar2);
    /* FIXED (2026-07-15): dropped terrain/x/y args - angr-confirmed at
     * 0x4ae505 (x=EDI from PeekChecksumStateUnderLock(piVar2) just
     * above, captured here as uVar12 - previously discarded; y=EAX was
     * `xor eax,eax`, i.e. a literal 0). uVar12 is otherwise free here
     * (next real use is the reassignment at the PeekChecksumStateUnderLock
     * call further below). */
    uVar9 = FindGroundHeightAtColumn(0,(int)(&DAT_006a7708 + g_clientContext),(int)uVar12,0);
    uVar11 = uVar9;
    uVar10 = PeekChecksumStateUnderLock(piVar2);
    FUN_00436070(&DAT_006a7f70 + g_clientContext,uVar10,uVar11);
    iVar7 = 1;
    if (0 < param_1[0xfe5]) {
      iVar7 = param_1[0xfe5];
    }
    uVar13 = (uint)*(byte *)(param_1 + 0xf);
    uVar11 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
    iVar8 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
    iVar8 = iVar8 / iVar7;
    uVar10 = PeekChecksumStateUnderLock(&DAT_007949c8);
    uVar18 = 0;
    uVar12 = PeekChecksumStateUnderLock(piVar2);
    FUN_0043af40(uVar12,uVar9,uVar18,uVar10,iVar8,uVar11,uVar13);
    uVar18 = 0;
    uVar12 = 2;
    uVar10 = 0xff;
    uVar11 = PeekChecksumStateUnderLock(param_1 + 0x5f9);
    uVar9 = 0;
    PeekChecksumStateUnderLock(piVar2);
    PeekPacketChecksumBool(uVar9,uVar11,uVar10,uVar12,uVar18);
    FUN_00431d90((char)param_1[0xf],7,0,uVar9,uVar11,uVar10,uVar12,uVar18);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar9 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004398e0(&DAT_006a7f70 + g_clientContext,param_1[2],uVar9,uVar11,param_1,0);
  *(undefined1 *)(param_1 + 5) = 1;
  (**(code **)(*param_1 + 0x20))();
  if (param_1[9] == 0) {
    pcVar19 = s_ssflame12_005549c8;
    uVar10 = 0x2077;
    uVar11 = PeekChecksumStateUnderLock(param_1 + 0x45e);
    uVar9 = PeekChecksumStateUnderLock(piVar2);
    FUN_004373c0(uVar9,uVar11,uVar10,pcVar19);
  }
  cVar6 = PeekPacketChecksumBool();
  iVar7 = g_clientContext;
  if ((cVar6 != '\0') && (cVar6 = InitChecksumSeed(), iVar7 = g_clientContext, cVar6 == '\0')) {
    uVar11 = PeekChecksumStateUnderLock(&DAT_007949c8);
    QueueOutgoingPacketField(uVar11);
    iVar7 = g_clientContext;
    *(undefined4 *)(&DAT_005f3768 + g_clientContext) = 5;
    *(undefined4 *)(&DAT_005f376c + iVar7) = 0;
  }
  uVar11 = CompareChecksumPair(iVar7 + 0x5b85c,param_1 + 0xe48);
  cVar6 = CheckGuardedBoolAnd(uVar11);
  if (cVar6 != '\0') {
    EncodeChecksumState(param_1 + 0xe48);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar7 < 0) && (cVar6 = PacketChecksumGreaterThan(param_1 + 0x122,0), cVar6 != '\0')) {
LAB_004ae748:
    cVar6 = PeekPacketChecksumBool();
    if (cVar6 == '\0') {
      SetGuardedBool(1,GB_GUARD_UNRECOVERED);
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((0 < iVar7) && (cVar6 = PacketChecksumLessThan(param_1 + 0x122,0), cVar6 != '\0')) goto LAB_004ae748;
  }
  piVar1 = param_1 + 0xed2;
  cVar6 = CompareChecksumPair(piVar2,piVar1);
  if (((cVar6 != '\0') && (cVar6 = CompareChecksumPair(piVar1,param_1 + 0xf5b), cVar6 != '\0')) ||
     ((cVar6 = CompareChecksumExceeds(piVar2,piVar1), cVar6 != '\0' &&
      ((cVar6 = CompareChecksumExceeds(piVar1,param_1 + 0xf5b), cVar6 != '\0' && (5 < param_1[0xed1])))))) {
    SetGuardedBool(1,GB_GUARD_UNRECOVERED);
  }
LAB_004aece0:
  *unaff_FS_OFFSET = uStack_c;
  return;
}

