/* FUN_00432850 - 0x00432850 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_00432850(int param_1,int param_2)

{
  char cVar1;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  char *pcVar9;
  byte bVar10;
  code *pcVar11;
  int *unaff_FS_OFFSET;
  int local_1e24;
  int local_1e10;
  int local_1e0c;
  int local_1df0;
  int iStack_1bd0;
  int local_1bcc;
  undefined1 auStack_19d8 [16];
  int iStack_19c8;
  int local_19a8;
  undefined1 auStack_17b4 [16];
  int iStack_17a4;
  undefined1 auStack_159c [16];
  int iStack_158c;
  undefined1 auStack_1378 [16];
  int iStack_1368;
  undefined1 auStack_114c [16];
  int iStack_113c;
  undefined1 auStack_f34 [16];
  int iStack_f24;
  undefined1 auStack_d08 [16];
  int iStack_cf8;
  undefined1 auStack_aec [16];
  int iStack_adc;
  undefined1 auStack_8c0 [16];
  int iStack_8b0;
  undefined1 auStack_6a8 [68];
  int iStack_664;
  undefined1 auStack_474 [16];
  int iStack_464;
  undefined1 auStack_260 [68];
  int iStack_21c;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  int iStack_18;
  undefined4 uStack_10;
  int local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053cb84;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_c;
  uStack_10 = 0x43286f;
  FUN_0040ada0();
  local_4 = 0;
  FUN_0040ada0();
  local_4 = 1;
  FUN_0040aba0();
  local_4 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 1;
  if (local_19a8 != 0) {
    FUN_0040a240();
    FUN_0040b540();
  }
  local_4 = 0;
  if (local_1bcc != 0) {
    FUN_0040a240();
    FUN_0040b540();
  }
  local_4 = 0xffffffff;
  if (local_1df0 != 0) {
    FUN_0040a240();
    FUN_0040b540();
  }
  FUN_0053753c();
  FUN_0053753c();
  FUN_0040a6e0();
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1e10 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if (local_1df0 != 0) {
    FUN_0040a240();
    FUN_0040b540();
  }
  local_1e0c = 0;
  if (0 < param_2) {
    do {
      pvVar2 = operator_new(0x3f9c);
      local_4 = 4;
      if (pvVar2 == (void *)0x0) {
        piVar3 = (int *)0x0;
      }
      else {
        piVar3 = (int *)FUN_00454dc0();
      }
      iVar4 = DAT_005b3484;
      local_4 = 0xffffffff;
      piVar3[0xfe4] = 0xff;
      if (*(char *)(iVar4 + 0x45578) == '\0') {
        piVar3[6] = 0x1a8e;
        piVar3[0xe] = 0x1a8f;
        piVar3[0xe25] = 0x2013;
        piVar3[0xe26] = s_flame123_00553cec._0_4_;
        piVar3[0xe27] = s_flame123_00553cec._4_4_;
        *(char *)(piVar3 + 0xe28) = s_flame123_00553cec[8];
        iVar4 = FindPreloadedTextureByName();
        piVar3[7] = iVar4;
      }
      else if (*(char *)(iVar4 + 0x45578) == '\x01') {
        piVar3[6] = 6000;
        piVar3[0xe] = 0x17d4;
        piVar3[0xe25] = 8000;
        iVar4 = FindPreloadedTextureByName();
        piVar3[7] = iVar4;
        piVar3[0xe26] = s_flameevent1_00553e2c._0_4_;
        piVar3[0xe27] = s_flameevent1_00553e2c._4_4_;
        piVar3[0xe28] = s_flameevent1_00553e2c._8_4_;
      }
      *(undefined1 *)(piVar3 + 0xf) = *(undefined1 *)(param_1 + 0x3c);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      pcVar11 = (code *)LeaveCriticalSection;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_0053753c();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_0053753c();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_0040a7d0();
      local_4 = 5;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      local_4 = 0xffffffff;
      if (local_1df0 != 0) {
        iVar4 = local_1df0 << 4;
        local_1e24 = 0x10;
        do {
          iVar5 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar5;
          iVar4 = iVar4 + 1;
          local_1e24 = local_1e24 + -1;
        } while (local_1e24 != 0);
        FUN_0040b540();
        pcVar11 = (code *)LeaveCriticalSection;
      }
      FUN_0040a7d0();
      local_4 = 6;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      (*pcVar11)();
      puStack_8 = (undefined1 *)0xffffffff;
      if (iStack_1bd0 != 0) {
        iVar4 = iStack_1bd0 << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540();
        pcVar11 = (code *)LeaveCriticalSection;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      *(char *)((int)piVar3 + 0xf3f) = (char)iVar4;
      iVar4 = _rand();
      *(byte *)(piVar3 + 0x3d0) = (byte)iVar4;
      bVar10 = *(byte *)((int)piVar3 + 0xf3f) & 7;
      bVar10 = ~('\x01' << bVar10) & (byte)iVar4 | (local_1e10 == 0) << bVar10;
      *(byte *)(piVar3 + 0x3d0) = bVar10;
      *(byte *)((int)piVar3 + 0xf41) = bVar10 + *(char *)((int)piVar3 + 0xf3f) + -0x34;
      (*pcVar11)();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      *(char *)((int)piVar3 + 0xf45) = (char)iVar4;
      iVar4 = _rand();
      *(byte *)((int)piVar3 + 0xf46) = (byte)iVar4;
      bVar10 = *(byte *)((int)piVar3 + 0xf45) & 7;
      bVar10 = ~('\x01' << bVar10) & (byte)iVar4 | '\0' << bVar10;
      *(byte *)((int)piVar3 + 0xf46) = bVar10;
      *(byte *)((int)piVar3 + 0xf47) = bVar10 + *(char *)((int)piVar3 + 0xf45) + -0x34;
      (*pcVar11)();
      FUN_00406530();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      (*pcVar11)();
      FUN_00406530();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      (*pcVar11)();
      piVar3[0xfe5] = local_c;
      FUN_00406530();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      EncodeOutgoingPacketField();
      (*pcVar11)();
      (**(code **)(*piVar3 + 4))(s_normal_00552230);
      pcVar7 = (char *)(iStack_18 + 0x3813);
      pcVar9 = PTR_s_121blast_xes_0056d33c;
      do {
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        *pcVar7 = cVar1;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      FUN_0041da80(DAT_005b3484,piVar3,1,1,1);
      uVar8 = FUN_0040ada0(piVar3 + 0x795,auStack_17b4,piVar3 + 0xcf2);
      uStack_20 = 7;
      FUN_0040a8c0(uVar8,auStack_19d8,100);
      uStack_20 = 8;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar8);
      (*pcVar11)(&DAT_005a9068);
      uStack_24 = 7;
      if (iStack_19c8 != 0) {
        iVar4 = iStack_19c8 << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1c4);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uStack_24 = 0xffffffff;
      if (iStack_17a4 != 0) {
        iVar4 = iStack_17a4 << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1c4);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uVar8 = FUN_0040ada0(piVar3 + 0x81e,auStack_114c,piVar3 + 0xcf2);
      uStack_24 = 9;
      FUN_0040a8c0(uVar8,auStack_474,100);
      uStack_24 = 10;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar8);
      (*pcVar11)(&DAT_005a9068);
      uStack_28 = 9;
      if (iStack_464 != 0) {
        iVar4 = iStack_464 << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1c0);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uStack_28 = 0xffffffff;
      if (iStack_113c != 0) {
        iVar4 = iStack_113c << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1c0);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uVar8 = FUN_0040ada0(piVar3 + 0x8a7,auStack_d08,piVar3 + 0xcf2);
      uStack_28 = 0xb;
      FUN_0040a8c0(uVar8,auStack_8c0,100);
      uStack_28 = 0xc;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar8);
      (*pcVar11)(&DAT_005a9068);
      uStack_2c = 0xb;
      if (iStack_8b0 != 0) {
        iVar4 = iStack_8b0 << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1bc);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uStack_2c = 0xffffffff;
      if (iStack_cf8 != 0) {
        iVar4 = iStack_cf8 << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(DAT_0079376c + iVar4) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1bc);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uVar8 = FUN_0040ada0(piVar3 + 0x930,auStack_1378,piVar3 + 0xd7b);
      uStack_2c = 0xd;
      FUN_0040a8c0(uVar8,auStack_159c,100);
      uStack_2c = 0xe;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar8);
      (*pcVar11)(&DAT_005a9068);
      uStack_30 = 0xd;
      if (iStack_158c != 0) {
        iVar4 = iStack_158c << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(DAT_0079376c + iVar4) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1b8);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uStack_30 = 0xffffffff;
      if (iStack_1368 != 0) {
        iVar4 = iStack_1368 << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1b8);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uVar8 = FUN_0040ada0(piVar3 + 0x9b9,auStack_aec,piVar3 + 0xd7b);
      uStack_30 = 0xf;
      FUN_0040a8c0(uVar8,auStack_f34,100);
      uStack_30 = 0x10;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar8);
      (*pcVar11)(&DAT_005a9068);
      uStack_34 = 0xf;
      if (iStack_f24 != 0) {
        iVar4 = iStack_f24 << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1b4);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uStack_34 = 0xffffffff;
      if (iStack_adc != 0) {
        iVar4 = iStack_adc << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540(&stack0xffffe1b4);
        pcVar11 = (code *)LeaveCriticalSection;
      }
      uVar8 = FUN_0040ada0(piVar3 + 0xa42,auStack_260,piVar3 + 0xd7b);
      uStack_34 = 0x11;
      FUN_0040a8c0(uVar8,auStack_6a8,100);
      uStack_34 = 0x12;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar8 = PeekPacketChecksumState();
      EncodeOutgoingPacketField(uVar8);
      (*pcVar11)(&DAT_005a9068);
      local_4 = 0x11;
      if (iStack_664 != 0) {
        iVar4 = iStack_664 << 4;
        local_1e24 = 0x10;
        do {
          iVar5 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar5;
          iVar4 = iVar4 + 1;
          local_1e24 = local_1e24 + -1;
        } while (local_1e24 != 0);
        FUN_0040b540();
      }
      local_4 = 0xffffffff;
      if (iStack_21c != 0) {
        iVar4 = iStack_21c << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + DAT_0079376c) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        FUN_0040b540();
      }
      RegisterActiveObject();
      local_1e10 = local_1e10 + 6;
      local_1e0c = local_1e0c + 1;
    } while (local_1e0c < param_2);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

