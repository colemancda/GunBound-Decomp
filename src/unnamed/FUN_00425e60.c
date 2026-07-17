/* FUN_00425e60 - 0x00425e60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall
FUN_00425e60(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 local_45c [8];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  iVar3 = g_clientContext;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053aef6) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  iVar3 = *(int *)(*(int *)(&DAT_006a7f8c + iVar3) + 0x1c);
  uVar1 = *(uint *)(iVar3 + 4);
  if (uVar1 < 0x186a4) {
    while (uVar1 != 0x186a3) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
      if (0x186a3 < uVar1) {
        return 0;
      }
    }
    uVar1 = *(uint *)(iVar3 + 0x10);
    uVar2 = *(uint *)(uVar1 + 8);
    while (uVar2 <= param_2) {
      if (uVar2 == param_2) {
        EncodeChecksumDeltaSub(uVar1 + 0x40,local_454,param_3);
        local_4 = 0;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if ((*(int *)(local_454 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_45c);
        }
        EncodeChecksumDeltaSub(uVar1 + 0x264,local_230,param_4);
        local_4 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if ((*(int *)(local_230 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_45c);
        }
        return (param_5 * param_5 <= iVar3 * iVar3 + iVar4 * iVar4) - 1 & uVar1;
      }
      uVar1 = *(uint *)(uVar1 + 0x10);
      uVar2 = *(uint *)(uVar1 + 8);
    }
  }
  return 0;
}

