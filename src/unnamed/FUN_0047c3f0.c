/* FUN_0047c3f0 - 0x0047c3f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 15 argless PeekPacketChecksumState() calls.  Cells:
 * g_clientContext+0x45354, the GetPlayerRecordBySlot record iVar2+0x90c,
 * the caller-supplied object regEsi + 0x40/+0x264 (the same base the
 * file's already-fixed Encodes use), the globals 0x796aa0 / 0x794e48 /
 * 0x7949c8 / 0xe55ab8, and the delta helpers' arg2 scratch cells
 * auStack_458 / auStack_ac4 / auStack_234 / auStack_684 / auStack_8ac
 * (0x40a5f0 / 0x40a6e0 return arg2 - see tools/sweep_guard_instructions.md;
 * two of those returns were parked in frame[0x1c] at 0x47c500 and
 * frame[0xc] at 0x47c6c5 before being peeked).  TWO FOLDED SELECTS: the
 * peeks at 0x47c945 and 0x47c9dd each follow a `*(iVar2+0x651c)` test
 * whose arms load DIFFERENT globals (0x796aa0/0x794e48 and 0x7949c8/
 * 0xe55ab8) into EAX before falling into one shared call - Ghidra emitted
 * the two empty `if/else` blocks but dropped the loads, so the cell is
 * written here as the ternary the branch really is.
 *
 * DEFINITION COMPLETED AND ESI RECOVERED (2026-08-24, workflow-analysed,
 * hand-checked).  `ret 8` says two stack arguments, which the sole caller
 * already passes; the definition declared fewer.  ESI is the caller's iVar8
 * (`mov esi,edi` immediately before the call), the projectile object.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0047c3f0(int param_1,int param_2,int *regEsi)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff524;
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined *puVar6;
  int iVar7;
  int unaff_EDI;
  code *pcVar8;
  int *unaff_FS_OFFSET;
  float10 fVar9;
  uint uStack_ad4;
  int aiStack_acc [2];
  undefined1 auStack_ac4 [20];
  int iStack_ab0;
  undefined1 auStack_8ac [16];
  int iStack_89c;
  undefined1 auStack_684 [12];
  int iStack_678;
  undefined1 auStack_458 [20];
  int iStack_444;
  undefined1 auStack_234 [4];
  int iStack_230;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  int iStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00539b25;
  iStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&iStack_c;
  regEsi[0xfef] = 3;
  (**(code **)(*regEsi + 4))();
  iVar2 = GetPlayerRecordBySlot(g_clientContext);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
    pcVar8 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (iVar3 != 1) {
      *(undefined1 *)(regEsi + 5) = 1;
      goto LAB_0047ca25;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar4 = PeekPacketChecksumState((void *)(iVar2 + 0x90c));
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47c4a2
     * (`lea edi,[esi + 0x40]`, esi = regEsi, the function's own "this"
     * projectile object, e.g. regEsi[0xfef]=3 above): regEsi+0x40
     * matches InitProjectile.c's own cell #1 (param_2+0x40, tableHandle
     * (+0x14)=param_2[0x15], activeFlag(+0x220) both zeroed together
     * there), confirming the same CProjectile cell layout. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)regEsi + 0x40, uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)((int)regEsi + 0x40));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    regEsi[0xfed] = iVar3;
    aiStack_acc[0] =
         EncodeChecksumDeltaAdd(iVar2 + 0xb30,auStack_458,
                      (-(uint)((char)regEsi[0xfe8] != '\0') & 0xffffff38) - 200);
    puStack_8 = (undefined1 *)0x0;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    aiStack_acc[0] = PeekPacketChecksumState((void *)(auStack_458));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(&g_nCameraBoundY + g_clientContext) + iVar3 < aiStack_acc[0]) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = *(int *)(&g_nCameraBoundY + g_clientContext) + iVar3;
    }
    else {
      EncodeChecksumDeltaAdd(iVar2 + 0xb30,auStack_ac4,
                   (-(uint)((char)regEsi[0xfe8] != '\0') & 0xffffff38) - 200);
      puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
      uStack_ad4 = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)(auStack_ac4));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47c5e6
     * (`lea edi,[esi + 0x264]`, esi = regEsi): matches InitProjectile.c's
     * cell #2 (param_2+0x264). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)regEsi + 0x264, iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)((int)regEsi + 0x264));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    puStack_8 = (undefined1 *)0x0;
    regEsi[0xfee] = iVar3;
    if (((uStack_ad4 & 1) != 0) && (uStack_ad4 = uStack_ad4 & 0xfffffffe, iStack_ab0 != 0)) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(aiStack_acc,&g_valueGuardMap);
    }
    puStack_8 = (undefined1 *)0xffffffff;
    pcVar8 = (code *)LeaveCriticalSection;
    if (iStack_444 != 0) {
      ScrambleChecksumGuardBytes(iStack_444,&g_valueGuardKeyTable);
      TreeLowerBound(aiStack_acc,&g_valueGuardMap);
      pcVar8 = (code *)LeaveCriticalSection;
    }
  }
  iVar3 = iVar2 + 0xb30;
  *(undefined1 *)(regEsi + 0xff9) = 0;
  *(undefined1 *)(regEsi + 0xff2) = 1;
  EncodeChecksumDeltaSub(iVar3,auStack_234,400);
  puStack_8 = (undefined1 *)0x2;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  aiStack_acc[0] = PeekPacketChecksumState((void *)(&DAT_00796aa0));
  (*pcVar8)(&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(auStack_234));
  (*pcVar8)(&g_valueGuardLock);
  if ((int)(*(int *)(&g_nCameraBoundY + g_clientContext) + uStack_ad4) < unaff_EDI) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar5 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
    (*pcVar8)(&g_valueGuardLock);
    puVar6 = &DAT_00553f90 + *(int *)(&g_nCameraBoundY + g_clientContext);
  }
  else {
    EncodeChecksumDeltaSub(iVar3,auStack_684,400);
    iStack_10 = CONCAT31(SUBFIELD(iStack_10,1,undefined3),3);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar5 = PeekPacketChecksumState((void *)(auStack_684));
    (*pcVar8)(&g_valueGuardLock);
    puVar6 = &DAT_00553f90;
  }
  EncodeChecksumDeltaSub(iVar3,auStack_8ac,puVar6);
  uStack_14 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar3 = PeekPacketChecksumState((void *)(auStack_8ac));
  (*pcVar8)(&g_valueGuardLock);
  uStack_18 = CONCAT31(SUBFIELD(uStack_18,1,undefined3),3);
  regEsi[0xff3] = iVar3;
  if (iStack_89c != 0) {
    ScrambleChecksumGuardBytes(iStack_89c,&g_valueGuardKeyTable);
    TreeLowerBound(&stack0xfffff524,&g_valueGuardMap);
  }
  uStack_18 = 2;
  if (((uVar5 & 2) != 0) && (iStack_678 != 0)) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffff524,&g_valueGuardMap);
  }
  uStack_18 = 0xffffffff;
  if (iStack_230 != 0) {
    ScrambleChecksumGuardBytes(iStack_230,&g_valueGuardKeyTable);
    TreeLowerBound(&stack0xfffff524,&g_valueGuardMap);
  }
  fVar9 = (float10)_DAT_00558070;
  regEsi[0xff4] = 1;
  fptan(fVar9);
  iVar3 = FloatToInt64();
  if (iStack_c < 0) {
    iVar7 = iVar3 / 2 + iVar3 + iStack_10;
    iVar3 = -iVar3;
    regEsi[0xff7] = 0x108;
    regEsi[0xff8] = 4;
  }
  else {
    iVar7 = (iStack_10 - iVar3 / 2) - iVar3;
    regEsi[0xff7] = 0x114;
    regEsi[0xff8] = -4;
  }
  regEsi[0xff6] = iVar3;
  regEsi[0xff5] = iVar7;
  regEsi[0xfed] = iVar7;
  if (cRam0055a4ac == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  iVar3 = PeekPacketChecksumState((void *)(*(char *)(iVar2 + 0x651c) == '\x01' ? &DAT_00796aa0 : &DAT_00794e48));
  (*pcVar8)(&g_valueGuardLock);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar3 = iVar3 + (iVar3 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar3 = iVar3 + (iVar3 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    if (*(char *)(iVar2 + 0x651c) == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    iVar2 = PeekPacketChecksumState((void *)(*(char *)(iVar2 + 0x651c) == '\x01' ? &DAT_007949c8 : &DAT_00e55ab8));
    (*pcVar8)(&g_valueGuardLock);
    iVar3 = iVar3 + iVar2;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47ca01
   * (`lea edi,[esi + 0x139c]`, esi = regEsi): a later cell on the same
   * projectile object, already initialized during the object's
   * InitProjectile-style construction and reused here for the final
   * damage value. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)regEsi + 0x139c, iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  CopyGuardedBool((byte *)((int)regEsi + 0x3918),(byte *)GB_GUARD_UNRECOVERED);
LAB_0047ca25:
  *unaff_FS_OFFSET = iStack_10;
  return;
}

