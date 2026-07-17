/* FUN_00477140 - 0x00477140 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00477140(void)

{
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
  undefined4 unaff_EBP;
  int unaff_ESI;
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
  *(undefined1 *)(unaff_ESI + 0x14) = 1;
  EncodeChecksumDeltaSub(unaff_ESI + 0x264,local_454,10);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_458 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_468 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_460 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_45c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_464 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_470 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_46c = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_478[0] = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  ApplyCraterExcavation(local_478[0],local_46c,local_470,local_464,local_45c,local_460,local_468,local_458);
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_478);
  }
  RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477342
   * (`lea edi,[esi + 0xf54]`, esi = this file's own `unaff_ESI`,
   * already used as a base pointer throughout, e.g. `unaff_ESI + 0x264`
   * above): cell is unaff_ESI+0xf54. `unaff_ESI` is plain `int`, so byte
   * offsets add directly. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(unaff_ESI + 0xf54, uVar3);
  pcVar6 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeChecksumDeltaSub(unaff_ESI + 0x264,local_454,10);
  local_4 = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x477389
   * (`lea edi,[esi + 0x1178]`, esi = unaff_ESI): cell is
   * unaff_ESI+0x1178. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(unaff_ESI + 0x1178, uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_478);
    pcVar6 = (code *)LeaveCriticalSection;
  }
  EncodeChecksumDeltaSub(unaff_ESI + 0x264,local_454,10);
  local_4 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  puVar7 = &DAT_005a9068;
  (*pcVar6)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar6)(&DAT_005a9068);
  FUN_00450eb0(unaff_EBP,uVar3,unaff_ESI,1,0,0);
  local_c = 0xffffffff;
  if (iStack_448 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffffb80);
    pcVar6 = (code *)LeaveCriticalSection;
  }
  EncodeChecksumDeltaSub(unaff_ESI + 0x264,&local_45c,10);
  local_c = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  (*pcVar6)(&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  (*pcVar6)(&DAT_005a9068);
  FUN_00436ac0(puVar7,uVar3);
  uStack_14 = 0xffffffff;
  if (iStack_450 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffffb78);
  }
  EncodeChecksumDeltaSub(unaff_ESI + 0x264,auStack_240,10);
  uStack_14 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(*(uint *)(unaff_ESI + 8) & 0xf,uVar4,uVar3,*(undefined4 *)(unaff_ESI + 0x3894),
               unaff_ESI + 0x3898);
  uStack_14 = 0xffffffff;
  if (iStack_22c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(&stack0xfffffb78);
  }
  iVar1 = g_clientContext;
  cVar2 = PeekPacketChecksumBool();
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
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    AcquireSoundChannel(0);
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}

