/* FUN_0048d8e0 - 0x0048d8e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0048d8e0(int param_1)

{
  int *piVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  int local_240;
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053df6b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_004373c0(uVar4,uVar3,0x206d,s_ssflame2_00555320);
    local_240 = 0;
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      piVar6 = (int *)FUN_00425ac0(g_clientContext,uVar5,uVar4,uVar3);
      if (piVar6 != (int *)0x0) {
        cVar2 = PeekPacketChecksumBool();
        if (cVar2 != '\0') {
          cVar2 = PeekPacketChecksumBool();
          if ((cVar2 != '\x01') && (piVar6[9] != 0xe)) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            iVar7 = PeekPacketChecksumState();
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            if (iVar7 != 3) {
              cVar2 = PacketChecksumNotEquals(piVar6 + 0x1bf5,0);
              if (cVar2 != '\0') {
                iVar7 = piVar6[0x2c2a];
                piVar6[0x2c2a] = iVar7 + 1;
                uVar3 = FUN_0040a6e0(piVar6 + 0x2cc,local_230,iVar7 * 0xf);
                local_4 = 0;
                FUN_0040a4d0(piVar6 + 0x1bf5);
                uVar3 = FUN_0040a4d0(uVar3);
                uVar4 = FUN_0040a4d0(piVar6 + 0x243);
                FUN_00436860(uVar4,uVar3);
                local_4 = 0xffffffff;
                FUN_0040a2a0();
                if (*(byte *)(param_1 + 0x3c) < 8) {
                  if (*(char *)(*(byte *)(param_1 + 0x3c) + 0x4590c + g_clientContext) ==
                      *(char *)((piVar6[2] & 7U) + 0x4590c + g_clientContext)) {
                    piVar1 = (int *)(g_clientContext + 0x5b83c + (uint)*(byte *)(param_1 + 0x3c) * 4);
                    iVar7 = FUN_0040a4d0(piVar6 + 0x1bf5);
                    *piVar1 = *piVar1 + iVar7;
                    *(undefined1 *)(piVar6 + 0x2c2d) = 1;
                  }
                  else {
                    piVar1 = (int *)(g_clientContext + 0x5b81c + (uint)*(byte *)(param_1 + 0x3c) * 4);
                    iVar7 = FUN_0040a4d0(piVar6 + 0x1bf5);
                    *piVar1 = *piVar1 + iVar7;
                  }
                }
              }
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EncodeOutgoingPacketField(0);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            piVar6[0x30ab] = 4;
            (**(code **)(*piVar6 + 4))(s_shield_005562ec);
          }
        }
      }
      local_240 = local_240 + 1;
    } while (local_240 < 8);
    FUN_0048de60();
  }
  return;
}

