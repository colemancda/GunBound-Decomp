/* FUN_0047fad0 - 0x0047fad0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 10 argless PeekPacketChecksumState() calls (peek status
 * "clean", 10 C : 10 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x47fad0-0x47fee5.
 *
 * Bases: regEsi is the object (ESI is live-in here, and the +0x264
 * cell sits next to the Encode site the 2026-07-15 sweep already fixed
 * at that offset); frame[0x10] is iVar2, the GetPlayerRecordBySlot
 * return spilled at 0x47fb2f, which the PeekBool cells at +0xbfc4/
 * +0xbfc7/+0xbfd3 corroborate; the rest are globals.
 *
 * Two cells are EncodeChecksumDeltaAdd returns.  The one at 0x47fbee is
 * ALREADY captured by the decompile into aiStack_464[0], so the Peek at
 * 0x47fc29 just uses that variable and its statement is untouched - the
 * assignment on that same line overwrites it, but the argument is
 * evaluated first.  The one at 0x47fca6 is discarded and is now caught
 * in a new uVar9.
 *
 * CORRECTION (2026-08-13, same day): the resolver's CROSSES-BRANCH-TARGET
 * flags on the &DAT_00794e48 and &DAT_00e55ab8 reads were NOT harmless.
 * Ghidra rendered `cmp byte [rec+0x651c],1 / jne` as an if/else whose
 * arms both call EnterCriticalSection and then one shared Peek - but
 * each arm loads a DIFFERENT cell first (equal -> &DAT_00796aa0 /
 * &DAT_007949c8, not-equal -> &DAT_00794e48 / &DAT_00e55ab8).  The
 * first pass passed only the fall-through cell; now written as the
 * ternary on the real `== 1` test.  Caught while sweeping FUN_0045f840,
 * which has the identical idiom.
 *
 * DEFINITION COMPLETED AND ESI RECOVERED (2026-08-24, workflow-analysed,
 * hand-checked).  `ret 0x10` says four stack arguments; Ghidra declared
 * three, while the sole caller already passes four -- so param_4 is added to
 * the definition rather than an argument dropped from the call.  ESI is the
 * caller's iVar8 (`mov esi,edi` right before the call, EDI loaded from the
 * spill slot the caller's own source names), the projectile object this
 * function reads as a C++ object.
 */
#include "ghidra_types.h"


void FUN_0047fad0(int param_1,int param_2,int param_3,int param_4,int *regEsi)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar9;
  int unaff_EBX;
  code *pcVar5;
  undefined4 *unaff_FS_OFFSET;
  int unaff_retaddr;
  int aiStack_464 [2];
  uint uStack_45c;
  undefined4 local_458 [0x89]; /* CValueGuard cell: 0x89*4 = 0x224 bytes (see src/network/SendOutgoingPacket.c) */
  int iStack_444;
  undefined1 auStack_234 [20];
  int iStack_220;
  undefined4 uStack_18;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00539aad;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_458[0] = 0;
  regEsi[0xfef] = ((char)param_3 != '\0') + 1;
  (**(code **)(*regEsi + 4))(&DAT_00553f90);
  iVar2 = GetPlayerRecordBySlot(g_clientContext);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
    pcVar5 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (iVar3 != 1) {
      *(undefined1 *)(regEsi + 5) = 1;
    }
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar4 = PeekPacketChecksumState((void *)(iVar2 + 0x90c));
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47fb8d
     * (`lea edi,[esi + 0x40]`, esi = regEsi, the function's own "this"
     * projectile object, e.g. regEsi[0xfef]=... above): regEsi+0x40
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
    if (((char)regEsi[0xfe8] != '\0') || (uVar4 = 0xffffff38, (char)regEsi[0xff1] != '\0')) {
      uVar4 = 0xfffffdda;
    }
    aiStack_464[0] = EncodeChecksumDeltaAdd(iVar2 + 0xb30,auStack_234,uVar4);
    puStack_8 = (undefined1 *)0x0;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    unaff_EBX = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    aiStack_464[0] = PeekPacketChecksumState((void *)aiStack_464[0]);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(&g_nCameraBoundY + g_clientContext) + unaff_EBX < aiStack_464[0]) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      unaff_EBX = PeekPacketChecksumState((void *)&DAT_00796aa0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = *(int *)(&g_nCameraBoundY + g_clientContext) + unaff_EBX;
    }
    else {
      if (((char)regEsi[0xfe8] != '\0') || (uVar4 = 0xffffff38, (char)regEsi[0xff1] != '\0'))
      {
        uVar4 = 0xfffffdda;
      }
      uVar9 = EncodeChecksumDeltaAdd(iVar2 + 0xb30,local_458,uVar4);
      puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
      uStack_45c = 1;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)uVar9);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47fce2
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
    if (((uStack_45c & 1) != 0) && (iStack_444 != 0)) {
      ScrambleChecksumGuardBytes();
      TreeLowerBound(aiStack_464,&g_valueGuardMap);
      unaff_EBX = iStack_444;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    pcVar5 = (code *)LeaveCriticalSection;
    if (iStack_220 != 0) {
      ScrambleChecksumGuardBytes(iStack_220,&g_valueGuardKeyTable);
      TreeLowerBound(aiStack_464,&g_valueGuardMap);
      pcVar5 = (code *)LeaveCriticalSection;
      unaff_EBX = iStack_220;
    }
  }
  regEsi[0xfea] = unaff_retaddr;
  regEsi[0xfeb] = param_1;
  *(undefined1 *)(regEsi + 0xff1) = 0;
  *(undefined1 *)(regEsi + 0xfe8) = param_2;
  regEsi[0xfe9] = param_3;
  if (*(char *)(iVar2 + 0x651c) == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  iVar2 = PeekPacketChecksumState((void *)(*(char *)(iVar2 + 0x651c) == '\x01' ? (void *)&DAT_00796aa0 : (void *)&DAT_00794e48));
  (*pcVar5)(&g_valueGuardLock);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    if (*(char *)(unaff_EBX + 0x651c) == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    iVar3 = PeekPacketChecksumState((void *)(*(char *)(unaff_EBX + 0x651c) == '\x01' ? (void *)&DAT_007949c8 : (void *)&DAT_00e55ab8));
    (*pcVar5)(&g_valueGuardLock);
    iVar2 = iVar2 + iVar3;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x47fea5
   * (`lea edi,[esi + 0x139c]`, esi = regEsi): a later cell on the same
   * projectile object, already initialized during the object's
   * InitProjectile-style construction and reused here for the final
   * damage value. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)regEsi + 0x139c, iVar2);
  (*pcVar5)(&g_valueGuardLock);
  RescrambleGuardedBool();
  *unaff_FS_OFFSET = uStack_18;
  return;
}

