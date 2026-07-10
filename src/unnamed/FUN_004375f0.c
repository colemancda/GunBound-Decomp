/* FUN_004375f0 - 0x004375f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004375f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,
                 undefined4 param_5,char param_6)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  undefined4 uVar4;
  char *pcVar5;
  code *pcVar6;
  int *piVar7;
  code *pcVar8;
  char *pcVar9;
  undefined4 local_c;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler
   * body wasn't included in this function's own decompile. Same
   * rationale as entry/InitGame.c - see src/README.md. */
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') goto LAB_0043784d;
  param_4 = param_4 & 0x80000007;
  if ((int)param_4 < 0) {
    param_4 = (param_4 - 1 | 0xfffffff8) + 1;
  }
  iVar2 = FUN_00437490();
  while (iVar2 == -1) {
    FUN_00437500();
    iVar2 = FUN_00437490();
  }
  pvVar3 = operator_new(0x441c);
  piVar7 = (int *)0x0;
  local_4 = 0;
  if (pvVar3 != (void *)0x0) {
    piVar7 = (int *)FUN_004977c0(pvVar3);
  }
  pcVar6 = (code *)EnterCriticalSection;
  local_4 = 0xffffffff;
  piVar7[6] = 0x17d2;
  piVar7[0xe] = 0x17d3;
  piVar7[0xe25] = 0x1f4d;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(piVar7 + 0xfed) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_4 = param_4 & 0x80000007;
  piVar7[0xfe7] = iVar2;
  if ((int)param_4 < 0) {
    param_4 = (param_4 - 1 | 0xfffffff8) + 1;
  }
  *(char *)(piVar7 + 0xf) = (char)param_4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004064a0(param_5);
  pcVar8 = (code *)LeaveCriticalSection;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar7[0xfea] = (uint)(param_6 != '\0');
  if (*(char *)(g_clientContext + 0x45578) == '\0') {
    pcVar9 = s_rayonmine_00553c2c;
LAB_00437779:
    iVar2 = FindPreloadedTextureByName(pcVar9);
    pcVar6 = (code *)EnterCriticalSection;
    pcVar8 = (code *)LeaveCriticalSection;
    piVar7[7] = iVar2;
  }
  else if (*(char *)(g_clientContext + 0x45578) == '\x01') {
    pcVar9 = s_rayonevent1_00553c20;
    goto LAB_00437779;
  }
  (**(code **)(*piVar7 + 4))(s_normal_00552230);
  (*pcVar6)(&DAT_005a9068);
  uVar4 = PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  (*pcVar6)(&DAT_005a9068);
  EncodeOutgoingPacketField(uVar4);
  (*pcVar8)(&DAT_005a9068);
  piVar7[0xe26] = DAT_00553c18;
  piVar7[0xe27] = DAT_00553c1c;
  pcVar9 = (char *)((int)piVar7 + 0x3813);
  pcVar5 = PTR_s_72blast_xes_0056d2e8;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    *pcVar9 = cVar1;
    pcVar9 = pcVar9 + 1;
  } while (cVar1 != '\0');
  FUN_0041da80(g_clientContext,piVar7,1,2,0);
  (*pcVar6)(&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  (*pcVar8)(&DAT_005a9068);
  piVar7[0xfeb] = iVar2;
  RegisterActiveObject();
LAB_0043784d:
  return;
}

