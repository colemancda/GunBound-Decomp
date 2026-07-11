/* FUN_0043af40 - 0x0043af40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043af40(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 byte param_7)

{
  int *piVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  uint uVar8;
  code *pcVar9;
  int iVar10;
  int *piVar11;
  code *pcVar12;
  undefined4 *unaff_FS_OFFSET;
  bool bVar13;
  undefined4 uStack_8d0;
  int local_8c8;
  int local_8bc;
  int local_8b8 [2];
  undefined1 local_8b0 [4];
  undefined1 auStack_8ac [24];
  int local_894;
  undefined1 local_684 [12];
  int iStack_678;
  undefined1 local_460 [16];
  int iStack_450;
  undefined1 auStack_244 [28];
  int local_228;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined4 local_c;
  
  local_c = 0xffffffff;
  puStack_10 = &LAB_0053ae9c;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  pcVar12 = (code *)EnterCriticalSection;
  if (*(int *)(&DAT_006a7724 + g_clientContext) < param_2) {
    param_2 = *(int *)(&DAT_006a7724 + g_clientContext);
  }
  local_8bc = param_4;
  pcVar9 = (code *)LeaveCriticalSection;
  iVar5 = g_clientContext;
  if (param_3 != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    pcVar9 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_8bc = (param_4 * 7) / iVar5;
    iVar5 = g_clientContext;
  }
  do {
    if (((param_2 < 0) || (param_1 < 0)) || (*(int *)(&DAT_006a7720 + iVar5) <= param_1)) {
      *unaff_FS_OFFSET = local_14;
      return;
    }
    piVar7 = *(int **)(*(int *)(&DAT_006a7f8c + iVar5) + 0x1c);
    uVar8 = piVar7[1];
    if (uVar8 < 0x186a2) {
LAB_0043b008:
      if (uVar8 != 0x186a1) break;
      uVar8 = uStack_8d0;
      for (piVar11 = (int *)piVar7[4]; uStack_8d0 = uVar8, piVar7 != piVar11;
          piVar11 = (int *)piVar11[4]) {
        (*pcVar12)(&DAT_005a9068);
        if ((char)((char)piVar11[0x242] + *(char *)((int)piVar11 + 0x909) + -0x34) !=
            *(char *)((int)piVar11 + 0x90a)) {
          g_valueGuardTamperFlag = 1;
          (*pcVar9)(&DAT_005a9068);
        }
        (*pcVar9)(&DAT_005a9068);
        SUBFIELD(uStack_8d0,3,undefined1) = (char)(uVar8 >> 0x18);
        bVar13 = SUBFIELD(uStack_8d0,3,undefined1) != '\0';
        iVar5 = g_clientContext;
        if (((bVar13) && (cVar2 = PeekPacketChecksumBool(), iVar5 = g_clientContext, cVar2 != '\x01')) &&
           (piVar11[9] != 0xe)) {
          cVar2 = PeekPacketChecksumBool();
          iVar10 = param_4;
          if (cVar2 != '\0') {
            iVar10 = param_4 / 5 + param_4;
          }
          cVar2 = FUN_00406860();
          iVar5 = g_clientContext;
          pcVar12 = (code *)EnterCriticalSection;
          if (cVar2 != '\0') {
            EncodeChecksumDeltaSub(piVar11 + 0x243,local_460,param_1);
            local_c = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            PeekPacketChecksumState();
            (*pcVar9)(&DAT_005a9068);
            puStack_10 = (undefined1 *)0xffffffff;
            if (iStack_450 != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(&local_8bc);
              pcVar9 = (code *)LeaveCriticalSection;
            }
            iVar6 = EncodeChecksumDeltaSub(piVar11 + 0x2cc,auStack_8ac,param_2);
            puStack_10 = (undefined1 *)0x1;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_8bc = PeekPacketChecksumState();
            (*pcVar9)(&DAT_005a9068);
            local_8c8 = local_894;
            local_c = 0xffffffff;
            if (local_894 != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(local_8b0);
              pcVar9 = (code *)LeaveCriticalSection;
            }
            iVar5 = g_clientContext;
            pcVar12 = (code *)EnterCriticalSection;
            if (local_8b8[0] * local_8b8[0] + iVar6 * iVar6 < iVar10 * iVar10) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = _rand();
              *(byte *)((int)piVar11 + 0xb0b5) = (byte)iVar5;
              iVar5 = _rand();
              bVar4 = *(byte *)((int)piVar11 + 0xb0b5);
              *(byte *)((int)piVar11 + 0xb0b6) = (byte)iVar5;
              bVar3 = '\x01' << (bVar4 & 7);
              uStack_8d0 = (uint)bVar3 << 0x18;
              bVar3 = ~bVar3 & (byte)iVar5 | bVar3;
              *(byte *)((int)piVar11 + 0xb0b6) = bVar3;
              *(byte *)((int)piVar11 + 0xb0b7) = bVar4 + bVar3 + -0x34;
              (*pcVar9)(&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EncodeOutgoingPacketField(param_5);
              (*pcVar9)(&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EncodeOutgoingPacketField(param_6);
              (*pcVar9)(&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EncodeOutgoingPacketField(param_4);
              (*pcVar9)(&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = _rand();
              *(char *)(piVar11 + 0x2c2e) = (char)iVar5;
              iVar5 = _rand();
              *(byte *)((int)piVar11 + 0xb0b9) = (byte)iVar5;
              bVar4 = *(byte *)(piVar11 + 0x2c2e) & 7;
              bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
              *(byte *)((int)piVar11 + 0xb0b9) = bVar4;
              *(byte *)((int)piVar11 + 0xb0ba) = *(byte *)(piVar11 + 0x2c2e) + bVar4 + -0x34;
              (*pcVar9)(&DAT_005a9068);
              iVar5 = piVar11[9];
              *(byte *)(piVar11 + 0x2c2b) = param_7;
              if (((iVar5 != 0xe) && (iVar5 != 5)) &&
                 ((iVar5 != 6 && ((iVar5 != 8 && (iVar5 != 10)))))) {
                (**(code **)(*piVar11 + 4))(s_shock_00553b80);
              }
              iVar5 = g_clientContext;
              pcVar12 = (code *)EnterCriticalSection;
              if (param_7 < 8) {
                uVar8 = (uint)param_7;
                if (*(char *)((piVar11[2] & 7U) + 0x4590c + g_clientContext) ==
                    *(char *)(uVar8 + 0x4590c + g_clientContext)) {
                  piVar1 = (int *)(g_clientContext + 0x5b83c + uVar8 * 4);
                  *piVar1 = *piVar1 + param_5 + param_6;
                  pcVar12 = (code *)EnterCriticalSection;
                  *(undefined1 *)(piVar11 + 0x2c2d) = 1;
                }
                else {
                  piVar1 = (int *)(g_clientContext + 0x5b81c + uVar8 * 4);
                  *piVar1 = *piVar1 + param_5 + param_6;
                  pcVar12 = (code *)EnterCriticalSection;
                }
              }
            }
          }
        }
        uVar8 = uStack_8d0;
      }
    }
LAB_0043b408:
    piVar7 = *(int **)(*(int *)(&DAT_006a7f8c + iVar5) + 0x1c);
    uVar8 = piVar7[1];
    while (uVar8 < 0x186a7) {
      if (uVar8 == 0x186a6) {
        piVar11 = (int *)piVar7[4];
        if (piVar7 != piVar11) {
          do {
            if ((char)piVar11[5] == '\0') {
              EncodeChecksumDeltaSub(piVar11 + 0x97,local_684,param_1);
              local_c = 2;
              (*pcVar12)(&DAT_005a9068);
              PeekPacketChecksumState();
              (*pcVar9)(&DAT_005a9068);
              local_14 = 0xffffffff;
              if (iStack_678 != 0) {
                iVar5 = iStack_678 << 4;
                iVar10 = 0x10;
                do {
                  iVar6 = _rand();
                  *(char *)(iVar5 + DAT_0079376c) = (char)iVar6;
                  iVar5 = iVar5 + 1;
                  iVar10 = iVar10 + -1;
                } while (iVar10 != 0);
                TreeLowerBound(local_8b8);
                pcVar9 = (code *)LeaveCriticalSection;
                pcVar12 = (code *)EnterCriticalSection;
              }
              EncodeChecksumDeltaSub(piVar11 + 0x120,auStack_244,param_2);
              local_14 = 3;
              (*pcVar12)(&DAT_005a9068);
              piVar7 = (int *)PeekPacketChecksumState();
              (*pcVar9)(&DAT_005a9068);
              local_c = 0xffffffff;
              if (local_228 != 0) {
                iVar5 = local_228 << 4;
                iVar10 = 0x10;
                do {
                  iVar6 = _rand();
                  *(char *)(iVar5 + DAT_0079376c) = (char)iVar6;
                  iVar5 = iVar5 + 1;
                  iVar10 = iVar10 + -1;
                } while (iVar10 != 0);
                TreeLowerBound(local_8b0);
                pcVar9 = (code *)LeaveCriticalSection;
                pcVar12 = (code *)EnterCriticalSection;
              }
              iVar5 = g_clientContext;
              if (local_8b8[0] * local_8b8[0] + local_8c8 * local_8c8 < param_4 * param_4) {
                (*pcVar12)(&DAT_005a9068);
                iVar5 = _rand();
                *(char *)(piVar11 + 0x3ce) = (char)iVar5;
                uVar8 = _rand();
                uStack_8d0 = uVar8 & 0x800000ff;
                if ((int)uStack_8d0 < 0) {
                  uStack_8d0 = (uStack_8d0 - 1 | 0xffffff00) + 1;
                }
                *(byte *)((int)piVar11 + 0xf39) = (byte)uStack_8d0;
                bVar4 = '\x01' << (*(byte *)(piVar11 + 0x3ce) & 7);
                bVar4 = ~bVar4 & (byte)uStack_8d0 | bVar4;
                *(byte *)((int)piVar11 + 0xf39) = bVar4;
                *(byte *)((int)piVar11 + 0xf3a) = *(byte *)(piVar11 + 0x3ce) + bVar4 + -0x34;
                (*pcVar9)();
                (*pcVar12)(&DAT_005a9068);
                EncodeOutgoingPacketField(param_5);
                (*pcVar9)(&DAT_005a9068);
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                EncodeOutgoingPacketField(param_6);
                (*pcVar9)(&DAT_005a9068);
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                EncodeOutgoingPacketField(param_4);
                (*pcVar9)(&DAT_005a9068);
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                iVar5 = _rand();
                *(char *)((int)piVar11 + 0xf3b) = (char)iVar5;
                iVar5 = _rand();
                *(byte *)(piVar11 + 0x3cf) = (byte)iVar5;
                bVar4 = *(byte *)((int)piVar11 + 0xf3b) & 7;
                bVar4 = ~('\x01' << bVar4) & (byte)iVar5 | '\0' << bVar4;
                *(byte *)(piVar11 + 0x3cf) = bVar4;
                *(byte *)((int)piVar11 + 0xf3d) = *(byte *)((int)piVar11 + 0xf3b) + bVar4 + -0x34;
                (*pcVar9)(&DAT_005a9068);
                (**(code **)(*piVar11 + 4))(s_shock_00553b80);
                iVar5 = g_clientContext;
                pcVar12 = (code *)EnterCriticalSection;
              }
            }
            piVar11 = (int *)piVar11[4];
          } while (piVar7 != piVar11);
        }
        break;
      }
      piVar7 = (int *)piVar7[7];
      uVar8 = piVar7[1];
    }
    param_1 = param_1 + param_3;
    param_2 = param_2 - local_8bc;
  } while( true );
  piVar7 = (int *)piVar7[7];
  uVar8 = piVar7[1];
  if (0x186a1 < uVar8) goto LAB_0043b408;
  goto LAB_0043b008;
}

