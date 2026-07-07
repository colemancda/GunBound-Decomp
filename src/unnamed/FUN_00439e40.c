/* FUN_00439e40 - 0x00439e40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00439e40(int param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte bVar10;
  byte bVar11;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = *(int *)(DAT_005b3484 + 0x621e4);
  if (iVar4 != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)(iVar4 + 0x8ba8) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)(iVar4 + 0x8ba9) = (byte)iVar3;
    bVar10 = *(byte *)(iVar4 + 0x8ba8) & 7;
    bVar10 = ~('\x01' << bVar10) & (byte)iVar3 | '\0' << bVar10;
    *(byte *)(iVar4 + 0x8ba9) = bVar10;
    *(byte *)(iVar4 + 0x8baa) = *(byte *)(iVar4 + 0x8ba8) + bVar10 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = *(int *)(DAT_005b3484 + 0x621e4);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(byte *)(iVar4 + 0x8bae) = (byte)iVar3;
    iVar3 = _rand();
    bVar10 = *(byte *)(iVar4 + 0x8bae);
    *(byte *)(iVar4 + 0x8baf) = (byte)iVar3;
    bVar11 = bVar10 & 7;
    bVar11 = ~('\x01' << bVar11) & (byte)iVar3 | '\0' << bVar11;
    *(byte *)(iVar4 + 0x8baf) = bVar11;
    *(byte *)(iVar4 + 0x8bb0) = bVar10 + bVar11 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = *(int *)(DAT_005b3484 + 0x621e4);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(byte *)(iVar4 + 0x8bb1) = (byte)iVar3;
    iVar3 = _rand();
    bVar10 = *(byte *)(iVar4 + 0x8bb1);
    *(byte *)(iVar4 + 0x8bb2) = (byte)iVar3;
    bVar11 = bVar10 & 7;
    bVar11 = ~('\x01' << bVar11) & (byte)iVar3 | '\0' << bVar11;
    *(byte *)(iVar4 + 0x8bb2) = bVar11;
    *(byte *)(iVar4 + 0x8bb3) = bVar10 + bVar11 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = *(int *)(DAT_005b3484 + 0x621e4);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(byte *)(iVar4 + 0x8bb4) = (byte)iVar3;
    iVar3 = _rand();
    bVar10 = *(byte *)(iVar4 + 0x8bb4);
    *(byte *)(iVar4 + 0x8bb5) = (byte)iVar3;
    bVar11 = bVar10 & 7;
    bVar11 = ~('\x01' << bVar11) & (byte)iVar3 | '\0' << bVar11;
    *(byte *)(iVar4 + 0x8bb5) = bVar11;
    *(byte *)(iVar4 + 0x8bb6) = bVar10 + bVar11 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar4 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar4 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
  }
  FUN_0043a670();
  iVar4 = GetPlayerRecordBySlot(DAT_005b3484);
  *(int *)(DAT_005b3484 + 0x621e4) = iVar4;
  if ((((iVar4 != 0) && (cVar2 = FUN_004065a0(), cVar2 != '\0')) &&
      (cVar2 = FUN_004065a0(), cVar2 != '\x01')) &&
     ((uVar6 = FUN_0040a4d0(DAT_005b3484 + 0x3b49c), param_1 != uVar6 ||
      ((cVar2 = FUN_0040b360(*(int *)(DAT_005b3484 + 0x621e0) + 0x6968,0), cVar2 == '\0' &&
       (iVar4 = (**(code **)(**(int **)(DAT_005b3484 + 0x621e0) + 0x14))(), iVar4 < 9000)))))) {
    FUN_00406500(1);
    FUN_00406500(0);
    FUN_00406500(1);
    FUN_00406500(1);
    FUN_00406500(0);
    *(undefined4 *)(*(int *)(DAT_005b3484 + 0x621e4) + 0xae10) = 0;
    QueueOutgoingPacketField(0);
    QueueOutgoingPacketField(400);
    iVar4 = FUN_0040a4d0(*(int *)(DAT_005b3484 + 0x621e4) + 0x1a2c);
    uVar5 = EncodeChecksumState(iVar4 * 0xb1ac + 0xf3b2c + DAT_005b3484);
    EncodeChecksumState(uVar5);
    iVar4 = DAT_005b3484;
    *(undefined1 *)(*(int *)(DAT_005b3484 + 0x621e4) + 0xae68) = 0;
    *(undefined4 *)(*(int *)(iVar4 + 0x621e4) + 0xb094) = 0;
    *(undefined4 *)(*(int *)(iVar4 + 0x621e4) + 0xb098) = 0xff;
    *(undefined4 *)(*(int *)(iVar4 + 0x621e4) + 0xb09c) = 0xfffffff0;
    *(undefined4 *)(*(int *)(iVar4 + 0x621e4) + 0xb0a0) = 0x3c0;
    *(undefined4 *)(*(int *)(iVar4 + 0x621e4) + 0xbfe0) = 200;
    if (*(int *)(*(int *)(iVar4 + 0x621e4) + 0xc2ac) == 0) {
      iVar4 = FUN_0040a4d0(*(int *)(iVar4 + 0x621e4) + 0x741c);
      iVar3 = FUN_0040a4d0((uint)param_1 * 0x1120 + 0x50f18 + DAT_005b3484);
      AddToPacketChecksum(iVar4 + iVar3);
      cVar2 = FUN_0040b410(*(int *)(DAT_005b3484 + 0x621e4) + 0x6fd4,
                           *(int *)(DAT_005b3484 + 0x621e4) + 0x6db0);
      if (cVar2 != '\0') {
        EncodeChecksumState(*(int *)(DAT_005b3484 + 0x621e4) + 0x6db0);
      }
    }
    else {
      piVar1 = (int *)(*(int *)(iVar4 + 0x621e4) + 0xc2ac);
      *piVar1 = *piVar1 + -1;
    }
    QueueOutgoingPacketField(0xffffffff);
    QueueOutgoingPacketField(0xffffffff);
    QueueOutgoingPacketField(2);
    cVar2 = FUN_00406610(*(char *)(DAT_005b3484 + 0x45127) == '\x01');
    if (cVar2 != '\0') {
      FUN_00406500(1);
    }
    cVar2 = FUN_004065a0();
    if ((cVar2 != '\0') && (iVar4 = FUN_004f2f90(), iVar4 != 0)) {
      for (iVar3 = *(int *)(iVar4 + 0x10); iVar3 != iVar4; iVar3 = *(int *)(iVar3 + 0x10)) {
        if (*(char *)(DAT_005b3484 + 0x45127) == '\x03') {
          uVar5 = 5;
        }
        else {
          uVar5 = 0;
        }
        QueueOutgoingPacketField(uVar5);
      }
    }
    iVar3 = FUN_0040a4d0(*(int *)(DAT_005b3484 + 0x621e4) + 0xb30);
    iVar7 = FUN_0040a4d0(*(int *)(DAT_005b3484 + 0x621e4) + 0x90c);
    iVar4 = DAT_005b3484;
    cVar2 = FUN_004065a0();
    if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar4] != '\0')) {
      iVar9 = 400;
      if (399 < iVar7) {
        iVar9 = iVar7;
      }
      iVar8 = *(int *)(&DAT_006a7720 + iVar4) + -400;
      if ((iVar9 <= iVar8) && (iVar8 = iVar7, iVar7 < 400)) {
        iVar8 = 400;
      }
      iVar7 = -0x14;
      if (-0x15 < iVar3) {
        iVar7 = iVar3;
      }
      iVar9 = *(int *)(&DAT_006a7724 + iVar4) + -0x104;
      if ((iVar7 <= *(int *)(&DAT_006a7724 + iVar4) + -0x104) && (iVar9 = -0x14, -0x15 < iVar3)) {
        iVar9 = iVar3;
      }
      *(int *)(&DAT_006a7718 + iVar4) = iVar8;
      *(int *)(&DAT_006a771c + iVar4) = iVar9;
    }
    return 0;
  }
  return 1;
}

