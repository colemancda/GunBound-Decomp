/* FUN_00437b40 - 0x00437b40 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00437b40(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,
                 undefined4 param_5,char param_6)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  char *pcVar6;
  int *piVar7;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053795b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  FUN_00437ae0();
  piVar2 = operator_new(0x3fd4);
  local_4 = 0;
  if (piVar2 == (int *)0x0) {
    piVar7 = (int *)0x0;
  }
  else {
    FUN_00454dc0(piVar2,0x186a4);
    *piVar2 = (int)&PTR_FUN_00555cf4;
    *(undefined1 *)(piVar2 + 0xfed) = 0;
    piVar2[0xfec] = 0;
    piVar2[0xff0] = 0;
    *(undefined1 *)(piVar2 + 0xff1) = 0;
    piVar2[0xff4] = -1;
    piVar2[0xff3] = 0;
    piVar7 = piVar2;
  }
  local_4 = 0xffffffff;
  piVar7[6] = 0x17d0;
  piVar7[0xe] = 0x17d1;
  piVar7[0xe25] = 0x1f4d;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_4 = param_4 & 0x80000007;
  piVar7[0xfe7] = iVar3;
  if ((int)param_4 < 0) {
    param_4 = (param_4 - 1 | 0xfffffff8) + 1;
  }
  *(char *)(piVar7 + 0xf) = (char)param_4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeGuardedBool(param_5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar7[0xfea] = (uint)(param_6 != '\0');
  iVar3 = FindPreloadedTextureByName(s_crystal_00553bfc);
  piVar7[7] = iVar3;
  (**(code **)(*piVar7 + 4))(s_normal_00552230);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar7[0xe26] = DAT_00553bf4;
  piVar7[0xe27] = DAT_00553bf8;
  pcVar6 = (char *)((int)piVar7 + 0x3813);
  pcVar5 = PTR_s_92blast_xes_0056d2f0;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    *pcVar6 = cVar1;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  FUN_0041da80(g_clientContext,piVar7,1,1,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar7[0xfeb] = iVar3;
  RegisterActiveObject();
  return;
}

