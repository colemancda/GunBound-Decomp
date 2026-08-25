/* FUN_00477140 - 0x00477140 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 18 argless PeekPacketChecksumState() calls (peek status
 * "clean", 18 C : 18 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x477140-0x4775a8; no gotos, straight-line, so the sites order-zip.
 * The object is ESI, which this decompile already models as `regEsi`
 * and uses as a base throughout (`regEsi + 0x264`), and which the
 * 2026-07-15 Encode sweep independently confirmed for the two Encode
 * cells here.
 *
 * Five cells are chained returns the decompile discarded: each of the
 * five EncodeChecksumDeltaSub(regEsi + 0x264, ...) calls returns its
 * dest cell in EAX and the Peek that follows re-reads it (0x477170,
 * 0x477362, 0x4773df, 0x47748a, 0x47752f).  Captured in a new uVar11.
 * The remaining cells are the ten-cell crater block and five reads of
 * regEsi+0x40.
 */
#include "ghidra_types.h"


void FUN_00477140(int regEsi)

{
  int iCraterX;
  int iCraterY;
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffffb78;
  undefined stack0xfffffb80;
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  code *pcVar6;
  undefined4 uVar11;
  undefined4 unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar7;
  undefined4 local_478 [2];
  undefined4 local_470;
  undefined4 local_46c;
  undefined4 local_468;
  undefined4 local_464;
  undefined4 local_460;
  undefined4 local_45c;
  undefined4 local_458;
  undefined1 local_454 [548];
  int iStack_450;
  int iStack_448;
  undefined1 auStack_240 [20];
  int iStack_22c;
  undefined4 uStack_1c;
  undefined4 uStack_14;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ef67;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *(undefined1 *)(regEsi + 0x14) = 1;
  uVar11 = EncodeChecksumDeltaSub(regEsi + 0x264,local_454,10);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_458 = PeekPacketChecksumState((void *)(regEsi + 0x6ac));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_468 = PeekPacketChecksumState((void *)(regEsi + 0x488));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_460 = PeekPacketChecksumState((void *)(regEsi + 0x2f74));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_45c = PeekPacketChecksumState((void *)(regEsi + 0x2d50));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_464 = PeekPacketChecksumState((void *)(regEsi + 0x2b2c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_470 = PeekPacketChecksumState((void *)(regEsi + 0x2908));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_46c = PeekPacketChecksumState((void *)(regEsi + 0x26e4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_478[0] = PeekPacketChecksumState((void *)(regEsi + 0x24c0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iCraterY = PeekPacketChecksumState((void *)uVar11);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iCraterX = PeekPacketChecksumState((void *)(regEsi + 0x40));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  ApplyCraterExcavation(local_478[0],local_46c,local_470,local_464,local_45c,local_460,local_468,local_458,
                 (int)(&DAT_006a7708 + g_clientContext),(int)iCraterX,(int)iCraterY);
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_478,&g_valueGuardMap);
  }
  RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)(regEsi + 0x40));
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477342
   * (`lea edi,[esi + 0xf54]`, esi = this file's own `regEsi`,
   * already used as a base pointer throughout, e.g. `regEsi + 0x264`
   * above): cell is regEsi+0xf54. `regEsi` is plain `int`, so byte
   * offsets add directly. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(regEsi + 0xf54, uVar3);
  pcVar6 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar11 = EncodeChecksumDeltaSub(regEsi + 0x264,local_454,10);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)uVar11);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477389
   * (`lea edi,[esi + 0x1178]`, esi = regEsi): cell is
   * regEsi+0x1178. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(regEsi + 0x1178, uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&g_valueGuardKeyTable);
    TreeLowerBound(local_478,&g_valueGuardMap);
    pcVar6 = (code *)LeaveCriticalSection;
  }
  uVar11 = EncodeChecksumDeltaSub(regEsi + 0x264,local_454,10);
  local_4 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)uVar11);
  puVar7 = &g_valueGuardLock;
  (*pcVar6)(&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(regEsi + 0x40));
  (*pcVar6)(&g_valueGuardLock);
  FUN_00450eb0(unaff_EBP,uVar3,regEsi,1,0,0);
  local_c = 0xffffffff;
  if (iStack_448 != 0) {
    ScrambleChecksumGuardBytes(iStack_448,&g_valueGuardKeyTable);
    TreeLowerBound(&stack0xfffffb80,&g_valueGuardMap);
    pcVar6 = (code *)LeaveCriticalSection;
  }
  uVar11 = EncodeChecksumDeltaSub(regEsi + 0x264,&local_45c,10);
  local_c = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)uVar11);
  (*pcVar6)(&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(regEsi + 0x40));
  (*pcVar6)(&g_valueGuardLock);
  FUN_00436ac0(puVar7,uVar3);
  uStack_14 = 0xffffffff;
  if (iStack_450 != 0) {
    ScrambleChecksumGuardBytes(iStack_450,&g_valueGuardKeyTable);
    TreeLowerBound(&stack0xfffffb78,&g_valueGuardMap);
  }
  uVar11 = EncodeChecksumDeltaSub(regEsi + 0x264,auStack_240,10);
  uStack_14 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = PeekPacketChecksumState((void *)uVar11);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar4 = PeekPacketChecksumState((void *)(regEsi + 0x40));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  SpawnFlameEffect(*(uint *)(regEsi + 8) & 0xf,uVar4,uVar3,*(undefined4 *)(regEsi + 0x3894),
               regEsi + 0x3898);
  uStack_14 = 0xffffffff;
  if (iStack_22c != 0) {
    ScrambleChecksumGuardBytes(iStack_22c,&g_valueGuardKeyTable);
    TreeLowerBound(&stack0xfffffb78,&g_valueGuardMap);
  }
  iVar1 = g_clientContext;
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar2 != '\x01') {
    iVar5 = *(int *)(&DAT_006a7750 + iVar1);
    if (iVar5 < 0x10) {
      iVar5 = 0xf;
    }
    *(int *)(&DAT_006a7750 + iVar1) = iVar5;
    iVar5 = *(int *)(&DAT_006a7754 + iVar1);
    if (iVar5 < 0xb) {
      iVar5 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar1) = iVar5;
  }
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar2 == '\0') {
    AcquireSoundChannel(0);
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}

