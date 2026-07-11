/* FUN_00479910 - 0x00479910 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00479910(int *param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined1 auStack_45c [8];
  undefined1 auStack_454 [20];
  int iStack_440;
  undefined1 auStack_230 [20];
  int iStack_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053aef6) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\0') {
    (**(code **)(*param_1 + 4))(s_shock_00553b80);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(byte *)(param_1 + 0x3ce) = (byte)iVar3;
    iVar3 = _rand();
    bVar1 = *(byte *)(param_1 + 0x3ce);
    *(byte *)((int)param_1 + 0xf39) = (byte)iVar3;
    bVar8 = bVar1 & 7;
    bVar8 = ~('\x01' << bVar8) & (byte)iVar3 | '\0' << bVar8;
    *(byte *)((int)param_1 + 0xf39) = bVar8;
    *(byte *)((int)param_1 + 0xf3a) = bVar8 + bVar1 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumPairSum(param_1 + 0x459,auStack_454,param_1 + 0x3d0);
    uStack_4 = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uStack_4 = 0xffffffff;
    if (iStack_440 != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(auStack_45c);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar4 + iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeChecksumDeltaSub(param_1 + 0x120,auStack_230,0xf);
    uStack_4 = 1;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\0') {
      puVar7 = operator_new(0x50);
      if (puVar7 == (undefined4 *)0x0) {
        puVar7 = (undefined4 *)0x0;
      }
      else {
        puVar7[1] = 0x30d54;
        puVar7[2] = 0xffffffff;
        puVar7[3] = 0;
        puVar7[4] = 0;
        *(undefined1 *)(puVar7 + 5) = 0;
        *(undefined1 *)((int)puVar7 + 0x15) = 0;
        puVar7[6] = 0xffffffff;
        puVar7[7] = 0;
        *(undefined1 *)(puVar7 + 8) = 0;
        puVar7[10] = 0;
        puVar7[0xb] = 0;
        puVar7[9] = 0xffffffff;
        *puVar7 = &PTR_FUN_00555d98;
        puVar7[0x10] = 0;
        puVar7[0x13] = 0;
        puVar7[0x11] = 0;
      }
      puVar7[0x12] = -iVar3;
      puVar7[0xe] = uVar6;
      puVar7[0xf] = uVar5;
      RegisterActiveObject();
    }
    uStack_4 = 0xffffffff;
    if (iStack_21c != 0) {
      ScrambleChecksumGuardBytes();
      FUN_0040b540(auStack_45c);
    }
  }
  return;
}

