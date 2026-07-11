/* FUN_004388e0 - 0x004388e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004388e0(void)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffff740;
  char cVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  char *pcVar7;
  byte bVar8;
  code *pcVar9;
  code *pcVar10;
  undefined4 *unaff_FS_OFFSET;
  int in_stack_00000014;
  int in_stack_00000018;
  undefined *puVar11;
  undefined1 *puStack_8d8;
  undefined1 *puStack_8d4;
  int *piStack_8d0;
  undefined *puVar12;
  char *pcVar13;
  int iStack_8a4;
  int iStack_894;
  int iStack_88c;
  undefined1 auStack_6a4 [12];
  int iStack_698;
  undefined1 auStack_68c [4];
  undefined1 auStack_688 [8];
  int iStack_680;
  int iStack_670;
  int iStack_668;
  undefined1 auStack_498 [84];
  int iStack_444;
  undefined1 auStack_26c [76];
  int iStack_220;
  undefined1 uStack_48;
  undefined4 uStack_40;
  undefined4 uStack_38;
  undefined1 uStack_30;
  undefined4 uStack_28;
  undefined4 uStack_20;
  undefined1 uStack_18;
  undefined1 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca83;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  piVar2 = operator_new(0x3fa4);
  local_4 = 0;
  if (piVar2 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    FUN_00454dc0();
    *piVar2 = (int)&PTR_FUN_00555e0c;
    piVar2[0xfe8] = 0;
  }
  local_4 = 0xffffffff;
  if (*(char *)(g_clientContext + 0x45578) == '\0') {
    piVar2[6] = 0x1a8c;
    piVar2[0xe] = 0x1a8d;
    piVar2[0xe25] = 0x2015;
    iVar3 = FindPreloadedTextureByName();
    piVar2[7] = iVar3;
    piVar2[0xe26] = DAT_00553bb4;
    piVar2[0xe27] = DAT_00553bb8;
    *(undefined1 *)(piVar2 + 0xe28) = DAT_00553bbc;
  }
  else if (*(char *)(g_clientContext + 0x45578) == '\x01') {
    piVar2[6] = 6000;
    piVar2[0xe] = 0x17d4;
    piVar2[0xe25] = 8000;
    iVar3 = FindPreloadedTextureByName();
    piVar2[7] = iVar3;
    piVar2[0xe26] = SUBFIELD(s_flameevent1_00553e2c,0,undefined4);
    piVar2[0xe27] = SUBFIELD(s_flameevent1_00553e2c,4,undefined4);
    piVar2[0xe28] = SUBFIELD(s_flameevent1_00553e2c,8,undefined4);
  }
  pcVar13 = s_normal_00552230;
  (**(code **)(*piVar2 + 4))();
  FloatToInt64();
  FloatToInt64();
  piVar2[0xfe4] = 0xff;
  *(undefined1 *)(piVar2 + 0xf) = *(undefined1 *)(in_stack_00000018 + 0x3c);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FloatToInt64();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FloatToInt64();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FloatToInt64();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = _rand();
  *(char *)((int)piVar2 + 0xf45) = (char)iVar3;
  iVar3 = _rand();
  *(byte *)((int)piVar2 + 0xf46) = (byte)iVar3;
  bVar8 = *(byte *)((int)piVar2 + 0xf45) & 7;
  bVar8 = ~('\x01' << bVar8) & (byte)iVar3 | '\0' << bVar8;
  *(byte *)((int)piVar2 + 0xf46) = bVar8;
  *(byte *)((int)piVar2 + 0xf47) = bVar8 + *(char *)((int)piVar2 + 0xf45) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00406530();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00406530();
  piVar2[0xfe5] = in_stack_00000014;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00406530();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  EncodeOutgoingPacketField();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar7 = (char *)((int)piVar2 + 0x3813);
  pcVar4 = PTR_s_142blast_xes_0056d344;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    *pcVar7 = cVar1;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  piStack_8d0 = (int *)g_clientContext;
  puStack_8d4 = (undefined1 *)0x438df7;
  FUN_0041da80();
  iVar3 = GetPlayerRecordBySlot();
  if ((iVar3 != 0) && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\0')) {
    EncodeChecksumDeltaDiv();
    puStack_8 = (undefined1 *)0x1;
    FUN_0040afb0();
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
    }
    EncodeChecksumDeltaDiv();
    puStack_8 = (undefined1 *)0x2;
    FUN_0040afb0();
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
    }
    EncodeChecksumDeltaDiv();
    puStack_8 = (undefined1 *)0x3;
    FUN_0040afb0();
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
    }
  }
  cVar1 = PeekPacketChecksumBool();
  pcVar9 = (code *)LeaveCriticalSection;
  pcVar10 = (code *)EnterCriticalSection;
  if (cVar1 == '\x01') {
    EncodeChecksumDeltaMul();
    pcVar10 = (code *)EnterCriticalSection;
    puStack_8 = (undefined1 *)0x4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    pcVar9 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaDiv();
    SUBFIELD(puStack_8,0,undefined1) = 5;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),4);
    if (iStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
      pcVar9 = (code *)LeaveCriticalSection;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_668 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
      pcVar9 = (code *)LeaveCriticalSection;
    }
    EncodeChecksumDeltaMul();
    puStack_8 = (undefined1 *)0x6;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar9)();
    piStack_8d0 = (int *)0x4390ad;
    EncodeChecksumDeltaDiv();
    uStack_c = CONCAT31(SUBFIELD(uStack_c,1,undefined3),7);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    PeekPacketChecksumState();
    EncodeOutgoingPacketField();
    (*pcVar9)();
    uStack_10 = CONCAT31(SUBFIELD(uStack_10,1,undefined3),6);
    if (iStack_670 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
      pcVar9 = (code *)LeaveCriticalSection;
    }
    uStack_10 = 0xffffffff;
    if (iStack_894 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
      pcVar9 = (code *)LeaveCriticalSection;
    }
    piStack_8d0 = piVar2 + 0xa42;
    puStack_8d4 = (undefined1 *)0x439172;
    EncodeChecksumDeltaMul();
    uStack_10 = 8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    (*pcVar9)();
    piStack_8d0 = (int *)auStack_688;
    puStack_8d8 = (undefined *)0x4391b4;
    puStack_8d4 = (undefined1 *)uVar5;
    EncodeChecksumDeltaDiv();
    uStack_14 = 9;
    piStack_8d0 = (int *)0x4391c7;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    PeekPacketChecksumState();
    piStack_8d0 = (int *)0x4391e7;
    EncodeOutgoingPacketField();
    piStack_8d0 = (int *)0x4391ee;
    (*pcVar9)();
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),8);
    if (iStack_668 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
      pcVar9 = (code *)LeaveCriticalSection;
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_88c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
      pcVar9 = (code *)LeaveCriticalSection;
    }
  }
  cVar1 = FUN_00406610();
  if (cVar1 != '\0') {
    (*pcVar10)();
    PeekPacketChecksumState();
    (*pcVar9)();
    piStack_8d0 = piVar2 + 0x930;
    puStack_8d4 = (undefined1 *)0x4392c2;
    EncodeChecksumDeltaMul();
    uStack_10 = 10;
    (*pcVar10)();
    puVar6 = (undefined1 *)PeekPacketChecksumState();
    puVar12 = &DAT_005a9068;
    piStack_8d0 = (int *)0x4392ed;
    (*pcVar9)();
    piStack_8d0 = (int *)pcVar13;
    puStack_8d4 = auStack_68c;
    puStack_8d8 = puVar6;
    iVar3 = EncodeChecksumDeltaDiv();
    piStack_8d0 = (int *)&DAT_005a9068;
    uStack_18 = 0xb;
    puStack_8d4 = (undefined1 *)0x439317;
    (*pcVar10)();
    puStack_8d4 = (undefined1 *)0x439320;
    puStack_8d4 = (undefined1 *)PeekPacketChecksumState();
    puStack_8d8 = (undefined1 *)0x439326;
    EncodeOutgoingPacketField();
    puStack_8d4 = &DAT_005a9068;
    puStack_8d8 = (undefined1 *)0x43932d;
    (*pcVar9)();
    uStack_20 = CONCAT31(SUBFIELD(uStack_20,1,undefined3),10);
    if (iStack_680 != 0) {
      puStack_8d8 = (undefined1 *)0x43934c;
      ScrambleChecksumGuardBytes();
      puStack_8d8 = &stack0xfffff740;
      FUN_0040b540();
      pcVar9 = (code *)LeaveCriticalSection;
    }
    uStack_20 = 0xffffffff;
    if (iStack_8a4 != 0) {
      puStack_8d8 = (undefined1 *)0x439388;
      ScrambleChecksumGuardBytes();
      puStack_8d8 = &stack0xfffff740;
      FUN_0040b540();
      pcVar9 = (code *)LeaveCriticalSection;
    }
    puStack_8d8 = &DAT_005a9068;
    (*pcVar10)();
    PeekPacketChecksumState();
    (*pcVar9)(&DAT_005a9068);
    EncodeChecksumDeltaMul(piVar2 + 0x9b9,&stack0xfffff740,puVar12);
    uStack_28 = 0xc;
    (*pcVar10)(&DAT_005a9068);
    piStack_8d0 = (int *)PeekPacketChecksumState();
    puVar11 = &DAT_005a9068;
    (*pcVar9)(&DAT_005a9068);
    puStack_8d4 = (undefined1 *)EncodeChecksumDeltaDiv(piStack_8d0,auStack_6a4,puStack_8d4);
    uStack_30 = 0xd;
    (*pcVar10)(&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    puVar12 = &DAT_005a9068;
    (*pcVar9)(&DAT_005a9068);
    uStack_38 = CONCAT31(SUBFIELD(uStack_38,1,undefined3),0xc);
    if (iStack_698 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&puStack_8d8);
      pcVar9 = (code *)LeaveCriticalSection;
    }
    uStack_38 = 0xffffffff;
    if (iVar3 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(&puStack_8d8);
      pcVar9 = (code *)LeaveCriticalSection;
    }
    (*pcVar10)(&DAT_005a9068);
    PeekPacketChecksumState();
    (*pcVar9)(&DAT_005a9068);
    EncodeChecksumDeltaMul(piVar2 + 0xa42,auStack_26c,puVar11);
    uStack_40 = 0xe;
    (*pcVar10)(&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    (*pcVar9)(&DAT_005a9068);
    EncodeChecksumDeltaDiv(uVar5,auStack_498,puVar12);
    uStack_48 = 0xf;
    (*pcVar10)(&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    (*pcVar9)(&DAT_005a9068);
    puStack_8 = (undefined1 *)CONCAT31(SUBFIELD(puStack_8,1,undefined3),0xe);
    if (iStack_444 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
    }
    puStack_8 = (undefined1 *)0xffffffff;
    if (iStack_220 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540();
    }
  }
  RegisterActiveObject();
  *unaff_FS_OFFSET = uStack_10;
  return;
}

