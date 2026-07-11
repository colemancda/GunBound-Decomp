/* FUN_0043bda0 - 0x0043bda0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043bda0(void)

{
  int *piVar1;
  int *piVar2;
  byte bVar3;
  int *piVar4;
  int *piVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  undefined4 uVar12;
  int *piVar13;
  byte bVar14;
  code *pcVar15;
  int *piVar16;
  bool bVar17;
  int local_698;
  undefined1 local_68c [8];
  undefined1 local_684 [20];
  int local_670;
  undefined1 local_460 [548];
  undefined1 local_23c [552];
  undefined4 local_c;

  local_c = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped (local_14/
   * puStack_10/unaff_FS_OFFSET) - handler body (LAB_0053c9c1) wasn't
   * included in this function's own decompile. Same rationale as
   * entry/InitGame.c - see src/README.md. local_c is a real, separate
   * local reused elsewhere in this function, kept as-is. */
  do {
    piVar4 = *(int **)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar11 = piVar4[1];
    bVar6 = false;
    while( true ) {
      if (0x186a1 < uVar11) goto LAB_0043c3a3;
      if (uVar11 == 0x186a1) break;
      piVar4 = (int *)piVar4[7];
      uVar11 = piVar4[1];
    }
    FUN_0043a5f0();
    piVar16 = (int *)piVar4[4];
    if (piVar4 == piVar16) break;
    do {
      pcVar15 = (code *)EnterCriticalSection;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      bVar14 = *(byte *)(piVar16 + 0x2c2e);
      bVar3 = *(byte *)((int)piVar16 + 0xb0b9);
      bVar17 = (byte)(bVar14 + bVar3 + -0x34) != *(char *)((int)piVar16 + 0xb0ba);
      if (bVar17) {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (bVar17 || (bVar3 >> (bVar14 & 7) & 1) != 1) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        bVar14 = *(byte *)((int)piVar16 + 0x9ced);
        bVar3 = *(byte *)((int)piVar16 + 0x9cee);
        bVar17 = (byte)(bVar14 + bVar3 + -0x34) != *(char *)((int)piVar16 + 0x9cef);
        if (bVar17) {
          g_valueGuardTamperFlag = 1;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (bVar17 || (bVar3 >> (bVar14 & 7) & 1) != 1) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          bVar14 = *(byte *)(piVar16 + 0x242);
          bVar3 = *(byte *)((int)piVar16 + 0x909);
          bVar17 = (byte)(bVar14 + bVar3 + -0x34) == *(char *)((int)piVar16 + 0x90a);
          if (!bVar17) {
            g_valueGuardTamperFlag = 1;
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (bVar17 && (bVar3 >> (bVar14 & 7) & 1) == 1) {
            iVar9 = *(int *)(&g_nCameraBoundY + g_clientContext);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar8 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar8 < iVar9) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              bVar14 = *(byte *)((int)piVar16 + 0xbff7);
              bVar3 = *(byte *)(piVar16 + 0x2ffe);
              bVar17 = (byte)(bVar14 + bVar3 + -0x34) != *(char *)((int)piVar16 + 0xbff9);
              if (bVar17) {
                g_valueGuardTamperFlag = 1;
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              }
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              if (bVar17 || (bVar3 >> (bVar14 & 7) & 1) != 1) {
                bVar6 = true;
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                iVar9 = _rand();
                *(char *)(piVar16 + 0x2c2e) = (char)iVar9;
                iVar9 = _rand();
                *(byte *)((int)piVar16 + 0xb0b9) = (byte)iVar9;
                bVar14 = '\x01' << (*(byte *)(piVar16 + 0x2c2e) & 7);
                bVar14 = ~bVar14 & (byte)iVar9 | bVar14;
                *(byte *)((int)piVar16 + 0xb0b9) = bVar14;
                *(byte *)((int)piVar16 + 0xb0ba) = *(byte *)(piVar16 + 0x2c2e) + bVar14 + -0x34;
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                InitGuardedChecksumSlot(piVar16 + 0x2d41,local_684,piVar16 + 0x2d41);
                local_c = 0;
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                iVar9 = PeekPacketChecksumState();
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                local_c = 0xffffffff;
                if (local_670 != 0) {
                  iVar8 = local_670 << 4;
                  local_698 = 0x10;
                  do {
                    iVar10 = _rand();
                    *(char *)(iVar8 + DAT_0079376c) = (char)iVar10;
                    iVar8 = iVar8 + 1;
                    local_698 = local_698 + -1;
                  } while (local_698 != 0);
                  TreeLowerBound(local_68c);
                }
                piVar13 = *(int **)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
                uVar11 = piVar13[1];
                if (uVar11 < 0x186a2) {
LAB_0043c0e0:
                  if (uVar11 != 0x186a1) goto code_r0x0043c0e7;
                  for (piVar5 = (int *)piVar13[4]; piVar13 != piVar5; piVar5 = (int *)piVar5[4]) {
                    (*pcVar15)(&DAT_005a9068);
                    bVar14 = *(byte *)((int)piVar5 + 0xb0b5);
                    bVar3 = *(byte *)((int)piVar5 + 0xb0b6);
                    bVar17 = (byte)(bVar14 + bVar3 + -0x34) != *(char *)((int)piVar5 + 0xb0b7);
                    if (bVar17) {
                      g_valueGuardTamperFlag = 1;
                      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                    }
                    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                    if ((((bVar17 || (bVar3 >> (bVar14 & 7) & 1) != 1) &&
                         (cVar7 = DecodeGuardedBool(), cVar7 != '\0')) &&
                        (cVar7 = DecodeGuardedBool(), cVar7 != '\0')) &&
                       ((piVar5 != piVar16 && (cVar7 = PeekPacketChecksumBool(), cVar7 == '\x01')))) {
                      iVar8 = *(int *)(&g_nCameraBoundY + g_clientContext);
                      (*pcVar15)(&DAT_005a9068);
                      iVar10 = PeekPacketChecksumState();
                      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
                      pcVar15 = (code *)EnterCriticalSection;
                      if ((iVar10 < iVar8) &&
                         ((cVar7 = PeekPacketChecksumBool(), pcVar15 = (code *)EnterCriticalSection,
                          cVar7 == '\0' && (piVar5[9] != 0xe)))) {
                        uVar12 = EncodeChecksumPairDiff(piVar5 + 0x243,local_460,piVar16 + 0x243);
                        local_c = 1;
                        iVar8 = PeekChecksumStateUnderLock(uVar12);
                        local_c = 0xffffffff;
                        ScrubChecksumGuard();
                        uVar12 = EncodeChecksumPairDiff(piVar5 + 0x2cc,local_23c,piVar16 + 0x2cc);
                        local_c = 2;
                        iVar10 = PeekChecksumStateUnderLock(uVar12);
                        local_c = 0xffffffff;
                        ScrubChecksumGuard();
                        pcVar15 = (code *)EnterCriticalSection;
                        if (iVar10 * iVar10 + iVar8 * iVar8 < iVar9) {
                          SetGuardedBool(1);
                          QueueOutgoingPacketField(0);
                          piVar1 = piVar16 + 0x2cb8;
                          EncodeChecksumState(piVar1);
                          EncodeChecksumState(piVar16 + 0x2d41);
                          SetGuardedBool(0);
                          *(char *)(piVar5 + 0x2c2b) = (char)piVar16[0x2c2b];
                          iVar8 = piVar5[9];
                          if ((((iVar8 != 0xe) && (iVar8 != 5)) && (iVar8 != 6)) &&
                             ((iVar8 != 8 && (iVar8 != 10)))) {
                            (**(code **)(*piVar5 + 4))(s_shock_00553b80);
                          }
                          pcVar15 = (code *)EnterCriticalSection;
                          if (*(byte *)(piVar16 + 0x2c2b) < 8) {
                            if (*(char *)((piVar5[2] & 7U) + 0x4590c + g_clientContext) ==
                                *(char *)(*(byte *)(piVar16 + 0x2c2b) + 0x4590c + g_clientContext)) {
                              piVar2 = (int *)(g_clientContext + 0x5b83c +
                                              (uint)*(byte *)(piVar16 + 0x2c2b) * 4);
                              iVar8 = PeekChecksumStateUnderLock(piVar1);
                              *piVar2 = *piVar2 + iVar8;
                              *(undefined1 *)(piVar5 + 0x2c2d) = 1;
                              pcVar15 = (code *)EnterCriticalSection;
                            }
                            else {
                              piVar2 = (int *)(g_clientContext + 0x5b81c +
                                              (uint)*(byte *)(piVar16 + 0x2c2b) * 4);
                              iVar8 = PeekChecksumStateUnderLock(piVar1);
                              *piVar2 = *piVar2 + iVar8;
                              pcVar15 = (code *)EnterCriticalSection;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
LAB_0043c38a:
      piVar16 = (int *)piVar16[4];
    } while (piVar4 != piVar16);
  } while (bVar6);
LAB_0043c3a3:
  return;
code_r0x0043c0e7:
  piVar13 = (int *)piVar13[7];
  uVar11 = piVar13[1];
  if (0x186a1 < uVar11) goto LAB_0043c38a;
  goto LAB_0043c0e0;
}

