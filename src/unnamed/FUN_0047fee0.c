/* FUN_0047fee0 - 0x0047fee0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 8 argless PeekPacketChecksumState() calls.  Cells:
 * g_clientContext+0x45354, the global 0x796aa0, and the delta helpers'
 * arg2 scratch cells - aiStack_688[0] (the DeltaSub at C55 whose return
 * the C already captures), auStack_458 (C70) and local_67c (C77); those
 * helpers return their arg2, see tools/sweep_guard_instructions.md.
 *
 * TWO FOLDED SELECTS: the peeks at 0x480194 and 0x48022c each sit after a
 * `*(iVar2+0x651c)` test whose two arms load DIFFERENT globals into EAX
 * (0x796aa0/0x794e48 at 0x480186/0x48018f, and 0x7949c8/0xe55ab8 at
 * 0x48021e/0x480227) before falling into one shared call.  Ghidra emitted
 * both as empty if/else blocks and dropped the loads entirely, so each
 * cell is written here as the ternary the branch really is - the same
 * shape already documented in FUN_0047c3f0.c.
 *
 * DEFINITION COMPLETED AND ESI RECOVERED (2026-08-24, workflow-analysed,
 * hand-checked).  `ret 8` says two stack arguments, which the sole caller
 * already passes; the definition declared fewer.  ESI is the caller's iVar8
 * (`mov esi,edi` immediately before the call), the projectile object.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0047fee0(int param_1,int param_2,int *regEsi)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *unaff_FS_OFFSET;
  int unaff_retaddr;
  int aiStack_688 [2];
  uint uStack_680;
  undefined4 local_67c [0x89]; /* CValueGuard cell: 0x89*4 = 0x224 bytes */
  int iStack_668;
  undefined1 auStack_458 [20];
  int iStack_444;
  undefined1 auStack_234 [20];
  int iStack_220;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_00539a68;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  local_67c[0] = 0;
  regEsi[0xfef] = 3;
  (**(code **)(*regEsi + 4))(&DAT_00553f90);
  iVar2 = GetPlayerRecordBySlot(g_clientContext);
  if (iVar2 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (iVar3 != 1) {
      *(undefined1 *)(regEsi + 5) = 1;
      goto LAB_004802f3;
    }
  }
  iVar3 = iVar2 + 0xb30;
  *(undefined1 *)(regEsi + 0xff8) = 0;
  *(undefined1 *)(regEsi + 0xff1) = 1;
  aiStack_688[0] = EncodeChecksumDeltaSub(iVar3,auStack_234,400);
  puStack_8 = (undefined1 *)0x0;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  aiStack_688[0] = PeekPacketChecksumState((void *)(aiStack_688[0]));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (*(int *)(&g_nCameraBoundY + g_clientContext) + iVar4 < aiStack_688[0]) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = *(int *)(&g_nCameraBoundY + g_clientContext) + iVar4;
  }
  else {
    EncodeChecksumDeltaSub(iVar3,auStack_458,400);
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
    uStack_680 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = PeekPacketChecksumState((void *)(auStack_458));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  EncodeChecksumDeltaSub(iVar3,local_67c,iVar4);
  puStack_8 = (undefined1 *)0x2;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar3 = PeekPacketChecksumState((void *)(local_67c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),1);
  regEsi[0xff2] = iVar3;
  if (iStack_668 != 0) {
    ScrambleChecksumGuardBytes(iStack_668,&g_valueGuardKeyTable);
    TreeLowerBound(aiStack_688,&g_valueGuardMap);
  }
  puStack_8 = (undefined1 *)0x0;
  if (((uStack_680 & 1) != 0) && (iStack_444 != 0)) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(aiStack_688,&g_valueGuardMap);
  }
  puStack_8 = (undefined1 *)0xffffffff;
  if (iStack_220 != 0) {
    ScrambleChecksumGuardBytes(iStack_220,&g_valueGuardKeyTable);
    TreeLowerBound(aiStack_688,&g_valueGuardMap);
  }
  regEsi[0xff3] = 1;
  if (*(char *)(iVar2 + 0x651c) == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  iVar3 = PeekPacketChecksumState((void *)(*(char *)(iVar2 + 0x651c) == '\0' ? &DAT_00796aa0 : &DAT_00794e48));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = iVar3 + iVar2;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x480250
   * (`lea edi,[esi+0x139c]`, esi = this file's own regEsi, confirmed
   * by objdump of orig/GunBound.gme: esi is never reassigned anywhere in
   * this function, so it's the same register-carried cell base already
   * used throughout as regEsi). regEsi is `int *` (scales by 4), so
   * the byte offset is taken via `(int)regEsi + 0x139c` (same twin-cell
   * offset as FUN_0047c040.c's identical call site). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)regEsi + 0x139c, iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  fptan((float10)_DAT_00558070);
  iVar2 = FloatToInt64();
  if (param_1 < 0) {
    iVar3 = iVar2 / 2 + iVar2 + unaff_retaddr;
    iVar2 = -iVar2;
    regEsi[0xff6] = 0x108;
    regEsi[0xff7] = 4;
  }
  else {
    iVar3 = (unaff_retaddr - iVar2 / 2) - iVar2;
    regEsi[0xff6] = 0x114;
    regEsi[0xff7] = -4;
  }
  regEsi[0xff4] = iVar3;
  regEsi[0xfed] = iVar3;
  regEsi[0xff5] = iVar2;
  RescrambleGuardedBool();
LAB_004802f3:
  *unaff_FS_OFFSET = uStack_10;
  return;
}

