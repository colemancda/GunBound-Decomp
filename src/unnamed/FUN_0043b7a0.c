/* FUN_0043b7a0 - 0x0043b7a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043b7a0(undefined4 param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 byte param_7)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  byte bVar8;
  int *piVar9;
  undefined1 local_680 [8];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_4;

  iVar5 = g_clientContext;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053ae5c) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  if (param_2 <= *(int *)(&g_nCameraBoundY + iVar5)) {
    if (param_3 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = g_clientContext;
    }
    piVar9 = *(int **)(*(int *)(&DAT_006a7f8c + iVar5) + 0x1c);
    uVar7 = piVar9[1];
    if (uVar7 < 0x186a2) {
LAB_0043b830:
      if (uVar7 != 0x186a1) goto code_r0x0043b838;
      for (piVar1 = (int *)piVar9[4]; piVar9 != piVar1; piVar1 = (int *)piVar1[4]) {
        cVar2 = PeekPacketChecksumBool();
        iVar5 = g_clientContext;
        if (((cVar2 != '\0') && (cVar2 = PeekPacketChecksumBool(), iVar5 = g_clientContext, cVar2 != '\x01')) &&
           (piVar1[9] != 0xe)) {
          cVar2 = PeekPacketChecksumBool();
          iVar6 = param_4;
          if (cVar2 != '\0') {
            iVar6 = param_4 / 5 + param_4;
          }
          cVar2 = DecodeGuardedBool();
          iVar5 = g_clientContext;
          if (cVar2 != '\0') {
            EncodeChecksumDeltaSub(piVar1 + 0x243,local_454,param_1);
            local_4 = 0;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar3 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_4 = 0xffffffff;
            ScrubChecksumGuard();
            EncodeChecksumDeltaSub(piVar1 + 0x2cc,local_678,param_2);
            local_4 = 1;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar4 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_4 = 0xffffffff;
            ScrubChecksumGuard();
            iVar5 = g_clientContext;
            if (iVar4 * iVar4 + iVar3 * iVar3 < iVar6 * iVar6) {
              SetGuardedBool(1,GB_GUARD_UNRECOVERED);
              QueueOutgoingPacketField(param_5);
              QueueOutgoingPacketField(param_6);
              QueueOutgoingPacketField(param_4);
              SetGuardedBool(0,GB_GUARD_UNRECOVERED);
              iVar5 = piVar1[9];
              if (((iVar5 != 0xe) && (iVar5 != 5)) &&
                 ((iVar5 != 6 && ((iVar5 != 8 && (iVar5 != 10)))))) {
                (**(code **)(*piVar1 + 4))(s_shock_00553b80);
              }
              iVar5 = g_clientContext;
              if (param_7 < 8) {
                uVar7 = (uint)param_7;
                if (*(char *)((piVar1[2] & 7U) + 0x4590c + g_clientContext) ==
                    *(char *)(uVar7 + 0x4590c + g_clientContext)) {
                  *(int *)(g_clientContext + 0x5b83c + uVar7 * 4) =
                       *(int *)(g_clientContext + 0x5b83c + uVar7 * 4) + param_5 + param_6;
                  *(undefined1 *)(piVar1 + 0x2c2d) = 1;
                }
                else {
                  *(int *)(g_clientContext + 0x5b81c + uVar7 * 4) =
                       *(int *)(g_clientContext + 0x5b81c + uVar7 * 4) + param_5 + param_6;
                }
              }
            }
          }
        }
      }
    }
LAB_0043ba8e:
    piVar9 = *(int **)(*(int *)(&DAT_006a7f8c + iVar5) + 0x1c);
    uVar7 = piVar9[1];
    while (uVar7 < 0x186a7) {
      if (uVar7 == 0x186a6) {
        for (piVar1 = (int *)piVar9[4]; piVar9 != piVar1; piVar1 = (int *)piVar1[4]) {
          if ((char)piVar1[5] == '\0') {
            EncodeChecksumDeltaSub(piVar1 + 0x97,local_678,param_1);
            local_4 = 2;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar5 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_4 = 0xffffffff;
            if ((*(int *)(local_678 + 0x14)) != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(local_680);
            }
            EncodeChecksumDeltaSub(piVar1 + 0x120,local_230,param_2);
            local_4 = 3;
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar6 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_4 = 0xffffffff;
            if ((*(int *)(local_230 + 0x14)) != 0) {
              ScrambleChecksumGuardBytes();
              TreeLowerBound(local_680);
            }
            if (iVar6 * iVar6 + iVar5 * iVar5 < param_4 * param_4) {
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = _rand();
              *(char *)(piVar1 + 0x3ce) = (char)iVar5;
              iVar5 = _rand();
              *(byte *)((int)piVar1 + 0xf39) = (byte)iVar5;
              bVar8 = '\x01' << (*(byte *)(piVar1 + 0x3ce) & 7);
              bVar8 = ~bVar8 & (byte)iVar5 | bVar8;
              *(byte *)((int)piVar1 + 0xf39) = bVar8;
              *(byte *)((int)piVar1 + 0xf3a) = bVar8 + *(byte *)(piVar1 + 0x3ce) + -0x34;
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              /* FIXED (2026-07-16): dropped `self` args on all 3 calls -
               * angr-confirmed at 0x43bc96/0x43bcbd/0x43bcde: self is
               * esi+0xf40/+0x1164/+0x1388 where esi = piVar1 (the loop
               * object; `int *`, so byte offsets /4 give the int cells
               * 0x3d0/0x459/0x4e2). Values (param_5/param_6/param_4)
               * were already correct. */
              EncodeOutgoingPacketField((void *)(piVar1 + 0x3d0), param_5);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EncodeOutgoingPacketField((void *)(piVar1 + 0x459), param_6);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EncodeOutgoingPacketField((void *)(piVar1 + 0x4e2), param_4);
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              iVar5 = _rand();
              *(char *)((int)piVar1 + 0xf3b) = (char)iVar5;
              iVar5 = _rand();
              *(byte *)(piVar1 + 0x3cf) = (byte)iVar5;
              bVar8 = *(byte *)((int)piVar1 + 0xf3b) & 7;
              bVar8 = ~('\x01' << bVar8) & (byte)iVar5 | '\0' << bVar8;
              *(byte *)(piVar1 + 0x3cf) = bVar8;
              *(byte *)((int)piVar1 + 0xf3d) = bVar8 + *(char *)((int)piVar1 + 0xf3b) + -0x34;
              LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
              (**(code **)(*piVar1 + 4))(s_shock_00553b80);
            }
          }
        }
        break;
      }
      piVar9 = (int *)piVar9[7];
      uVar7 = piVar9[1];
    }
  }
  return;
code_r0x0043b838:
  piVar9 = (int *)piVar9[7];
  uVar7 = piVar9[1];
  if (0x186a1 < uVar7) goto LAB_0043ba8e;
  goto LAB_0043b830;
}

